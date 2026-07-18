# High-Performance Bloom Filter Design for IPv4 Address Tracking
## Optimized for NPU, ASIC, FPGA, and SmartNIC Architectures

A Bloom filter is a space-efficient probabilistic data structure used to test whether an element is a member of a set. False positive matches are possible, but false negatives are not—a query returns either "Possibly in set" or "Definitely not in set."

This document presents a comprehensive, hardware-optimized system design for a Bloom filter engineered to track $n = 1 \text{ million}$ unique IPv4 addresses with a target false positive rate of $p = 0.1\%$ ($1$ in $1000$), optimized for sub-nanosecond line-rate packet processing.

---

## 1. Real-World Applications of Bloom Filters

Bloom filters are utilized across high-performance systems to perform extremely fast, low-overhead set membership checks, serving as a critical gatekeeper for both hardware and software systems.

### 1.1 High-Speed Networking Applications
In high-speed networking devices (ASICs, SmartNICs, NPUs), memory access is the ultimate bottleneck. Bloom filters act as single-cycle filters placed ahead of slower, more expensive table searches:

1. **DDoS Mitigation & Traffic Filtering:**
   During a DDoS attack, a network device is bombarded with millions of malformed or malicious packets. A Bloom filter storing a blacklist of known malicious IPs can filter out these packets at line rate before the ASIC allocates any connection state, buffers, or CPU processing, preventing resource exhaustion.
2. **Flow Cache Gatekeeping:**
   When a packet arrives, the router must determine if it belongs to an active, accelerated flow. By checking a Bloom filter first, the router can instantly determine if a flow is *not* active. This bypasses slower, multi-cycle lookup tables (like large hash tables or external DRAM routing tables) for new or unknown flows.
3. **Network Loop Detection (e.g., multicast routing):**
   To prevent packet looping in multicast routing, routers track recently forwarded packet IDs. Storing a Bloom filter of packet signatures in fast SRAM allows the card to discard looped packets within nanoseconds.

### 1.2 Database Query Optimization (The "Absent-Key" Performance Saver)
In modern databases (such as **Google Bigtable, Apache Cassandra, RocksDB, and PostgreSQL**), checking for the existence of a key that *does not exist* is a major performance killer.

#### The Problem: Slower than a hit
When querying an existing key, the database can fetch the data and return. However, when querying a *non-existent* key, the database engine must traverse B-tree indices, search multiple disk blocks, or check multiple index pages just to confirm that the key is absent. This triggers random disk I/O (SSD/HDD access) which takes milliseconds—completely stalling database thread pools.

#### The Solution: In-Memory Bloom Gatekeeping
To prevent this performance degradation, databases store a small, highly compressed Bloom filter of all valid keys directly in RAM:

```
                  +--------------------------------+
                  |  Query for Non-Existent Key X  |
                  +---------------+----------------+
                                  |
                                  v
                    +-----------------------------+
                    | In-Memory Bloom Filter Check|
                    +-------------+---------------+
                                  |
            +---------------------+---------------------+
            | (Yes - Probable)                          | (No - Definite)
            v                                           v
+-----------------------+                    +-----------------------+
| Search Index on Disk  |                    | Instantly Return      |
| (Expensive Disk I/O)  |                    | "Key Not Found"       |
+-----------------------+                    | (0 Disk Accesses!)    |
                                             +-----------------------+
```

1. **Instant "Not Found" Returns:**
   When a query for key `X` arrives, the system checks the in-memory Bloom filter. If the filter returns `False`, the database instantly returns a "Key Not Found" result with **zero disk accesses**. 
2. **LSM-Tree (Log-Structured Merge-tree) SSTable Skipping:**
   In LSM-tree engines (RocksDB, Cassandra), database writes are stored on disk in read-only files called SSTables. A single key lookup might normally require searching *every single SSTable file* on disk sequentially. By placing a separate in-memory Bloom filter in front of each SSTable, the engine can instantly skip 95%+ of the SSTable files, reducing the number of disk accesses to essentially a single disk read.

---

## 2. Design Parameters & Mathematical Foundations

### 2.1 Standard Optimal Bloom Filter Formula
Using classical Bloom filter theory, the optimal bit array size $m$ and the number of hash functions $k$ for a given capacity $n$ and acceptable error rate $p$ are derived as follows:

1. **Required Bit Array Size ($m$):**
   $$m = -\frac{n \ln p}{(\ln 2)^2}$$
   For $n = 1,000,000$ and $p = 0.001$:
   $$m = -\frac{1,000,000 \cdot \ln(0.001)}{0.480453} \approx 14,377,588 \text{ bits}$$
   This translates to **14.38 Megabits (Mb)** or approximately **1.8 Megabytes (MB)**.

2. **Optimal Number of Hash Functions ($k$):**
   $$k = \frac{m}{n} \ln 2 = 14.377 \cdot 0.6931 \approx 9.96 \approx 10 \text{ hash functions}$$

---

### 2.2 The Hardware Dilemma: The Modulo Bottleneck
In general-purpose software, mapping a 32-bit hash value to an index in the range $[0, m-1]$ is performed using the modulo operator:
$$\text{index} = \text{hash}(\text{IP}) \pmod{14,377,588}$$

**In ASIC/FPGA hardware, modulo by an arbitrary number is extremely expensive.** Integer division requires large pipelined divider circuits, consuming substantial silicon area (logic gates) and introducing tens of clock cycles of latency. This is incompatible with line-rate processing at 100 Gbps+ or 400 Gbps+.

### 2.3 Hardware Co-Design Optimization: Power-of-Two Sizing
By rounding the bit-array size $m$ up to the nearest power of two, we can eliminate the division logic entirely.
* Let $m = 2^{24} = 16,777,216 \text{ bits}$ (Exactly **2.0 Megabytes**).
* Sizing up to $2^{24}$ increases memory usage by only **0.2 MB** (+11% relative to optimal), which is negligible for modern on-chip SRAM.
* **The Modulo Trick:** Modulo by $2^{24}$ is replaced by a simple **bitwise AND** operation with a mask:
  $$\text{index} = \text{hash}(\text{IP}) \ \text{AND} \ (2^{24} - 1)$$
  In hardware, a bitwise AND requires zero clock cycles and zero active gate logic (it is simply a hardwired routing connection to ignore the upper bits of the 32-bit hash).

### 2.4 Improved Accuracy Analysis
By increasing $m$ to $2^{24}$, we also improve the false positive rate. Let's recalculate the false positive probability $p$ with $m = 16,777,216$, $n = 1,000,000$, and keeping $k = 10$:
$$p \approx \left(1 - e^{-k n / m}\right)^k = \left(1 - e^{-10 \cdot 1,000,000 / 16,777,216}\right)^{10} \approx \left(1 - e^{-0.596}\right)^{10} \approx (0.449)^{10} \approx 0.00034$$

**Result:** The actual false positive rate drops from **0.1% to 0.034% (a 3x improvement in accuracy)** for a negligible increase in memory!

---

## 3. Memory Subsystem Architecture: SRAM vs. DRAM

At 100 Gbps, processing minimum-size Ethernet packets (84 bytes on the wire including inter-packet gap and preamble) permits only **6.72 nanoseconds** of processing budget per packet. At 400 Gbps, this drops to **1.68 nanoseconds**.

```
                           +------------------------+
                           | Incoming IPv4 Header   |
                           +-----------+------------+
                                       |
                                       v
                             +-------------------+
                             |  Unified Hashing  |
                             | (CRC32/MurmurHash)|
                             +---------+---------+
                                       |
                   +-------------------+-------------------+
                   |                   |                   |
                   v                   v                   v
             +-----------+       +-----------+       +-----------+
             | g_0(IP)   |       | g_1(IP)   |       | g_9(IP)   |
             +-----+-----+       +-----+-----+       +-----+-----+
                   |                   |                   |
                   v                   v                   v
             +-----------+       +-----------+       +-----------+
             | SRAM Bank0|       | SRAM Bank1| ...   | SRAM Bank9|
             | (1.67 Mb) |       | (1.67 Mb) |       | (1.67 Mb) |
             +-----+-----+       +-----+-----+       +-----+-----+
                   |                   |                   |
                   +-------------------+-------------------+
                                       |
                                       v
                             +-------------------+
                             |  AND Decision Gate| ---> True/False
                             +-------------------+
```

| Memory Type | Latency | Access Characteristics | Suitability for Bloom Filter at Line Rate |
| :--- | :--- | :--- | :--- |
| **External DRAM (DDR4/DDR5)** | 30 - 50 ns | Row/column burst access; extremely slow random accesses. | **Unsuitable.** Will cause severe head-of-line blocking and packet drops. |
| **On-Chip SRAM** | < 1 ns | Single-cycle random access; high parallel bandwidth. | **Ideal.** Easily fits the 2.0 MB filter. Supports line-rate single-cycle reads/writes. |

### 3.1 Bandwidth Bottleneck: Multi-port SRAM Limitations
A single SRAM block typically has a maximum of 2 physical access ports (Dual-Port SRAM). If we must verify $k = 10$ distinct bit locations per packet, a standard single SRAM block would require 5 clock cycles (if dual-ported) to read all bits. This is a massive latency bottleneck.

### 3.2 Solution: SRAM Bank Partitioning (Partitioned Bloom Filter)
Instead of allocating one giant 16.78 Mb SRAM block, we split the memory into $k = 10$ independent physical SRAM banks:
* Each bank size: $m_{bank} = \frac{16,777,216}{10} \approx 1.68 \text{ Megabits}$ (approx. **210 Kilobytes**).
* To make bank sizing hardware-friendly and ensure fast masking, we can round each bank to a power-of-two: $2^{21} = 2,097,152 \text{ bits}$ per bank. This creates 10 banks of **256 KB each** (total **2.5 MB**), allowing independent power-of-two masking for each bank.
* **Parallel Lookup:** Each hash function $g_i(\text{IP})$ maps to exactly one SRAM bank $i$. This allows the hardware to fire and read all $k = 10$ bits **simultaneously in a single clock cycle**.

---

## 4. Cache-Localized / Blocked Bloom Filters (For CPU/SmartNIC)

While SRAM partitioning works perfectly in ASICs, general-purpose CPUs and SmartNICs with processor cores (such as ARM-based DPUs) suffer from **cache line bouncing** and **cache misses** when accessing random bits across a 2.0 MB buffer. A single packet query could trigger up to 10 separate L2/L3 cache misses.

### 4.1 Blocked Bloom Filter (BBF) Design
To solve this, we implement a **Blocked Bloom Filter**:
1. **Block Structure:** Divide the Bloom filter into blocks of exactly **64 bytes** (512 bits), matching the standard CPU cache line size.
2. **Block Selection:** Use a primary hash $h_{block}(\text{IP})$ to select exactly one 64-byte block.
3. **Local Evaluation:** Fetch that single 64-byte block into the CPU cache / register file.
4. **Local Hashes:** Use secondary hashes to set/check $k$ bits *only* within that fetched 512-bit block.

```
Incoming IP ---> [ h_block(IP) ] ---> Maps to Block #42 (64 Bytes)
                                             |
                                             v
                             +-------------------------------+
                             |    Cache Line (512 bits)      |
                             | [0........................511] |
                             +--+----+-------+-----+------+--+
                                |    |       |     |      |
                                v    v       v     v      v
                             Checks k bits strictly within cache line
```

* **Advantage:** Exactly **one memory access** per lookup. The remaining $k-1$ lookups occur instantly inside the CPU registers or L1 cache, accelerating software lookup performance by 3x–5x.
* **Trade-off:** Slower local saturation. If many keys hash to the same block, the local false positive rate rises. To offset this, increase the overall memory size by roughly 15% to maintain a strict $0.1\%$ false positive rate.

---

## 5. Hardware-Efficient Combinatorial Hashing

Generating 10 fully independent cryptographic hashes (e.g., SHA-256) in hardware is prohibitively expensive in terms of power, silicon area, and clock speed.

### 5.1 Combinatorial Hashing Scheme
As proven by Kirsch and Mitzenmacher, we can generate an arbitrary number of hash values $g_i(x)$ using just **two base hash functions** $h_1(x)$ and $h_2(x)$ with zero asymptotic loss in false positive performance:
$$g_i(x) = \left(h_1(x) + i \cdot h_2(x)\right) \pmod{m}$$
Where $i \in [0, k-1]$.

### 5.2 Hardware Synthesis Optimizations
1. **Base Hash Functions:**
   * **CRC32-C (Castagnoli Polynomial):** Implemented in dedicated hardware instructions (`_mm_crc32_u64` on Intel/AMD or `__crc32d` on ARMv8). Consumes only 1 clock cycle.
   * **MurmurHash3 (32-bit):** Non-cryptographic, fast, outstanding distribution properties, and very simple logic (mostly shifts, multiplies, and XORs).
2. **Pipelined Multiplier-Free Combinatorial Loop:**
   In hardware, we avoid the multiplier $i \cdot h_2(x)$ by using an accumulator register in a pipeline to yield one new bit address per clock cycle using only a single **adder** and **bitwise mask**:
   * **Cycle 0:** `Accumulator = h_1(x)`
   * **Cycle 1:** `index_0 = Accumulator AND Mask; Accumulator = Accumulator + h_2(x)`
   * **Cycle 2:** `index_1 = Accumulator AND Mask; Accumulator = Accumulator + h_2(x)`

---

## 6. Optimized Hashing for 32-Bit Keys (IPv4)

Because IPv4 addresses are native 32-bit (4-byte) integers, hashing them is highly efficient and avoids any complex serialization or prefix mapping.

### 6.1 Base Hash Generators
To generate the two independent 32-bit base hashes $h_1(\text{IP})$ and $h_2(\text{IP})$ directly from a 32-bit IPv4 address:
1. **First Hash ($h_1$):** Run a standard hardware CRC32 instruction on the raw 32-bit IP:
   $$h_1(\text{IP}) = \text{CRC32}(\text{IP})$$
2. **Second Hash ($h_2$):** Run a second CRC32 instruction using a hardware-friendly bitwise XOR salt (constant rotation):
   $$h_2(\text{IP}) = \text{CRC32}(\text{IP} \ \oplus \ \text{0x55555555})$$
   *Alternatively*, MurmurHash3 with a different seed can be used in software contexts. This ensures complete independence of $h_1$ and $h_2$ without any hardware penalty.

---

## 7. Managing State and Timeouts (Sliding Window Bloom Filter)

Standard Bloom filters are accumulate-only; they do not support deletions. Over time, as more unique IPs are seen, the bit array eventually fills with 1s, causing the false positive rate to degrade to 100%.

In network tracking (e.g., DDoS mitigation, state tracking, or IP reputation), we care about IPs seen within a **sliding time window** (e.g., "seen in the last 24 hours").

### 7.1 Why Counting Bloom Filters (CBF) Fall Short
A Counting Bloom Filter replaces each bit with a 4-bit counter. When an IP is added, we increment the counters; when it expires, we decrement them.
* **Drawback:** Memory footprint increases by **4x** (from 2.0 MB to 8.0 MB).
* **Drawback:** Decrementing requires knowing *exactly* which IP expired, requiring an external database of IP timestamps, which defeats the purpose of a space-saving Bloom filter.

### 7.2 Solution: Double Buffering (Generational Bloom Filter)
Instead of counting, maintain **two** distinct Bloom Filters: `BF_Active` and `BF_Standby`, each of size $m$.

```
Time Interval: T_0 -> T_1
+--------------------------+     +--------------------------+
|  BF_Active (Write/Read)  |     |  BF_Standby (Read Only)  |
|  Accumulating current IPs|     |  Has previous interval's |
+--------------------------+     +--------------------------+
                                               |
                                               v (At interval end, swap)
Time Interval: T_1 -> T_2                      |
+--------------------------+     +-------------+------------+
|  BF_Active (Write/Read)  |     |  BF_Standby (CLEARED)    |
|  (This was BF_Standby)   |     |  (This was BF_Active)    |
+--------------------------+     +--------------------------+
```

#### Operations:
1. **Querying:** An IP is considered "seen" if it exists in `BF_Active` **OR** `BF_Standby`.
2. **Inserting:** New incoming IPs are written **only** to `BF_Active`.
3. **Ageing/Rotation:** Every $T$ minutes/hours (e.g., 1 hour):
   * Flush/clear `BF_Standby` to all zeros.
   * Swap the pointers: `BF_Standby` becomes `BF_Active`, and the old `BF_Active` becomes `BF_Standby`.
4. **Benefits:**
   * Memory is only $2 \times m$ (4.0 MB total, much lower than the 8.0 MB required by Counting Bloom Filters).
   * **Zero division/subtraction overhead.** Swapping pointers is instant and constant-time $O(1)$.
   * Guarantees that any IP not seen for at least $2T$ time is completely purged.

---

## 8. Reference Implementations

### 8.1 Python Simulation
This production-grade Python simulation showcases the power-of-two size optimization, direct 32-bit IPv4 hashing, and combinatorial hashing.

```python
import math
import struct
import binascii

class IPv4BloomFilter:
    def __init__(self, capacity=1000000, target_fpr=0.001):
        self.n = capacity
        
        # Calculate optimal m
        optimal_m = - (self.n * math.log(target_fpr)) / (math.log(2) ** 2)
        
        # Round up to the nearest power of two
        self.num_bits_exponent = math.ceil(math.log2(optimal_m))
        self.m = 1 << self.num_bits_exponent  # 2^exponent
        self.mask = self.m - 1
        
        # Calculate optimal k
        self.k = round((self.m / self.n) * math.log(2))
        
        # Initialize bit array (using bytearray for efficiency)
        self.bit_array = bytearray(self.m // 8)
        
        print(f"Initialized IPv4 Bloom Filter:")
        print(f"  Target Capacity: {self.n:,} IPs")
        print(f"  Bit Array Size (m): {self.m:,} bits ({self.m / 8 / 1024 / 1024:.2f} MB)")
        print(f"  Optimal Hash Functions (k): {self.k}")
        print(f"  Theoretical False Positive Rate: {self.get_theoretical_fpr():.5%}")

    def get_theoretical_fpr(self):
        return (1 - math.exp(-self.k * self.n / self.m)) ** self.k

    def _serialize_ip(self, ip_str: str) -> bytes:
        """Serializes dotted IPv4 string directly into a 4-byte big-endian representation."""
        import socket
        return socket.inet_pton(socket.AF_INET, ip_str)

    def _get_hashes(self, ipv4_bytes: bytes) -> tuple:
        """Generates two independent 32-bit base hashes from the 32-bit IPv4."""
        # Base Hash 1: Direct CRC32 of IPv4 address
        h1 = binascii.crc32(ipv4_bytes) & 0xffffffff
        
        # Base Hash 2: CRC32 of IPv4 address salted/XORed with 0x55555555
        # (simulates a different hardware-friendly polynomial/constant rotation)
        ip_val = struct.unpack("!I", ipv4_bytes)[0]
        salted_ip_bytes = struct.pack("!I", ip_val ^ 0x55555555)
        h2 = binascii.crc32(salted_ip_bytes) & 0xffffffff
        
        return h1, h2

    def add(self, ip_str: str):
        """Inserts an IPv4 address into the Bloom filter."""
        ipv4_bytes = self._serialize_ip(ip_str)
        h1, h2 = self._get_hashes(ipv4_bytes)
        
        # Combinatorial hashing loop
        for i in range(self.k):
            index = (h1 + i * h2) & self.mask
            byte_idx = index >> 3        # index // 8
            bit_offset = index & 7       # index % 8
            self.bit_array[byte_idx] |= (1 << bit_offset)

    def contains(self, ip_str: str) -> bool:
        """Queries if an IPv4 address has been seen."""
        ipv4_bytes = self._serialize_ip(ip_str)
        h1, h2 = self._get_hashes(ipv4_bytes)
        
        for i in range(self.k):
            index = (h1 + i * h2) & self.mask
            byte_idx = index >> 3
            bit_offset = index & 7
            if not (self.bit_array[byte_idx] & (1 << bit_offset)):
                return False
        return True

# --- Verification & Demo ---
if __name__ == "__main__":
    bf = IPv4BloomFilter()
    
    # Test IPs
    ipv4_test = "192.168.1.1"
    ipv4_test2 = "172.16.254.1"
    not_seen = "10.0.0.1"
    
    # Add IPs
    bf.add(ipv4_test)
    bf.add(ipv4_test2)
    
    # Check status
    assert bf.contains(ipv4_test) is True, "Error: IPv4 lookup failed!"
    assert bf.contains(ipv4_test2) is True, "Error: IPv4 lookup failed!"
    assert bf.contains(not_seen) is False, "Error: False positive on clean array!"
    
    print("\nVerification Successful!")
    print(f"  Checked '{ipv4_test}': {bf.contains(ipv4_test)}")
    print(f"  Checked '{ipv4_test2}': {bf.contains(ipv4_test2)}")
    print(f"  Checked '{not_seen}': {bf.contains(not_seen)}")
```

---

### 8.2 Hardware-Friendly Simulated C++ Core Lookup
This snippet demonstrates the cycle-accurate combinatorial logic with power-of-two masking designed for hardware pipelines.

```cpp
#include <iostream>
#include <cstdint>
#include <vector>

// 2.0 Megabytes bit array size (2^24 bits)
constexpr uint32_t EXPONENT = 24;
constexpr uint32_t M = 1 << EXPONENT;
constexpr uint32_t MASK = M - 1;
constexpr uint32_t K = 12; // Optimal k for 2^24 size and 1M capacity

// Mock 2MB bit array
std::vector<uint8_t> bit_array(M / 8, 0);

// Simulated single-cycle lookup pipeline
bool query_ip_hardware(uint32_t h1, uint32_t h2) {
    uint32_t accumulator = h1;
    
    for (uint32_t i = 0; i < K; ++i) {
        // Fast power-of-two index masking
        uint32_t index = accumulator & MASK;
        
        uint32_t byte_idx = index >> 3;  // shift instead of division
        uint8_t bit_offset = index & 7;  // bitwise AND instead of modulo 8
        
        // If any bit is 0, the IP is definitively NOT seen
        if (!(bit_array[byte_idx] & (1 << bit_offset))) {
            return false;
        }
        
        // Single adder cycle (combinatorial lookup)
        accumulator += h2;
    }
    return true; // Match found (Probabilistic)
}

int main() {
    std::cout << "Hardware Bloom Filter Engine Initialized." << std::endl;
    std::cout << "  Bit array size: " << M << " bits (" << (M / 8 / 1024) << " KB)" << std::endl;
    std::cout << "  Hash iterations (K): " << K << std::endl;
    return 0;
}
```

---

## 9. Summary of Engineering Enhancements Over Standard Designs

1. **ASIC Division Elimination:** Rounding $m$ up to $2^{24}$ changes costly division operations to a $0$-latency bitwise AND mask, while simultaneously reducing the false positive rate by **3x** (from $0.1\%$ to $0.034\%$).
2. **SRAM Bank Partitioning:** Eliminates multi-port memory access overhead by splitting the filter into $k$ independent physical SRAM banks. Allows all bit checks to occur in parallel within a single clock cycle.
3. **Blocked Bloom Filter (BBF):** Resolves cache-line misses on general-purpose CPUs and SmartNICs by packing evaluations strictly within a single 64-byte boundary.
4. **Optimized 32-bit Key Processing:** Eliminates unified IP structure alignment overhead, using direct 32-bit hardware-accelerated instructions and simple bitwise salts to generate extremely fast base hashes.
5. **Time-Aware Double Buffering:** Resolves memory saturation without the 4x overhead and CPU complexity of Counting Bloom Filters, guaranteeing $O(1)$ constant-time cleanups.
