# Equal-Cost Multi-Path (ECMP) Constraints & Limitations

Equal-Cost Multi-Path (ECMP) is a routing technique that enables load balancing and path redundancy by distributing packets along multiple equal-cost paths to a destination. While highly effective, ECMP has several fundamental constraints, architectural limitations, and hardware-specific requirements that must be carefully managed.

---

## 1. Core Constraints & Hashing Limitations

### Per-Flow vs. Per-Packet Hashing (Packet Reordering)
*   **The Constraint:** To achieve perfectly balanced traffic, routers would need to load balance on a per-packet basis. However, doing so introduces massive **packet reordering**, which severely degrades TCP performance.
*   **The Impact:** Routers are forced to load balance **per-flow** (using a hash of Layer 3/Layer 4 headers). This guarantees that packets belonging to the same flow traverse the same path, avoiding reordering at the cost of imperfect load distribution.

### Inefficient Load Distribution (Elephant Flows)
*   **The Constraint:** Because hashing is traffic-load blind, it does not take into account the actual bandwidth consumption of individual flows.
*   **The Impact:** A few heavy, long-running flows ("elephant flows") can easily saturate a single path, while other equal-cost paths remain completely underutilized or idle ("mice flows").

### Hash Polarization
*   **The Constraint:** When multiple routers in a multi-hop path use the same hashing algorithm, hash input fields, or seed keys, they will produce identical hash results.
*   **The Impact:** All traffic matching a specific hash is funneled onto a single next-hop path at consecutive stages (polarization), leaving alternative links completely unused and leading to severe network-wide congestion.

### Strict Equal-Cost (Metric) Requirement
*   **The Constraint:** Traditional ECMP can only load-balance traffic over paths that share the **exact same routing metric** (cost) in the routing table.
*   **The Impact:** Sub-optimal or unequal paths cannot be utilized for load sharing or failover, even if they have substantial available bandwidth.

### Disruption on Path Failures
*   **The Constraint:** Standard modulo-N hashing shifts boundaries when a path in the group fails or is added.
*   **The Impact:** Adding or removing a path triggers a remapping of nearly all active flows in the group, resulting in massive flow migration, packet reordering, and TCP retransmissions. 

---

## 2. Link-Speed Agnosticism

*   **The Constraint:** Traditional ECMP is **completely agnostic to physical link speed**. It treats all next-hops with equal metric costs as identical, irrespective of their capacity.
*   **The Impact:** If a 10G link and a 100G link are assigned equal costs, ECMP will distribute traffic in a strict 50/50 split. The 10G link will quickly become congested and drop packets while the 100G link sits mostly idle.
*   **Mitigation:** Solving this requires the use of **Weighted ECMP (WECMP)** or **Unequal Cost Multi-Path (UCMP)** to allocate hash buckets proportionally to the link capacity.

---

## 3. uRPF (Unicast Reverse Path Forwarding) Incompatibility

*   **The Constraint:** Standard **strict-mode uRPF** is incompatible with asymmetric routing topologies commonly produced by ECMP.
*   **The Impact:** Under strict-mode uRPF, the router checks if the incoming packet's source IP is reachable via the exact interface it arrived on. In asymmetric ECMP environments, return traffic might legitimately arrive on Interface B, while the router’s preferred path back to the source is Interface A. The router will identify this as spoofed traffic and drop it.
*   **Mitigation:** Multi-path networks must either disable strict uRPF entirely or utilize **loose-mode uRPF** (which only verifies that some route to the source exists, regardless of the interface) or an **ECMP-aware uRPF** implementation.

---

## 4. Power-of-2 Hardware Boundaries

*   **The Constraint:** Hardware hashing groups (ECMP tables) on network ASICs have historically been optimized for **powers of 2** (e.g., 2, 4, 8, 16, 32, 64, 128 next-hops).
*   **The Impact:** Modulo operations are mathematically trivial in binary hardware when the divisor is a power of 2 (e.g., `hash AND (N-1)`). If the active path count is not a power of 2 (e.g., 3, 5, or 7 next-hops), simpler ASICs can suffer from **modulo-skewing**, where hash buckets are unevenly mapped to the available ports, causing natural load imbalance.
*   **Mitigation:** Modern high-end ASICs implement more advanced consistent hashing schemes (such as HRW or resilient hashing) to minimize this imbalance, but power-of-two group sizes remain the most optimal for raw hardware efficiency.
