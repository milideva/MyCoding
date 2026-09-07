#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

/*
  Problem: Bloom Filter Implementation in C

  Problem Description:
  A Bloom filter is a space-efficient probabilistic data structure 
  used to test whether an element is a member of a set. 
  - False positive matches are possible.
  - False negatives are NOT possible.

  Algorithm:
  1. Use a bit array of size `m`.
  2. Use `k` different hash functions.
  3. To add an element:
     - Apply each of the `k` hash functions to the element.
     - Set the bits at the resulting indices to 1.
  4. To query an element:
     - Apply each of the `k` hash functions.
     - If ANY of the bits at the indices is 0, the element is 
       definitely NOT in the set.
     - If ALL bits are 1, the element MIGHT be in the set.

  -------------------------------------------------------------------------
  PRACTICAL SIZING FOR IPV4 ADDRESS BLOOM FILTERS:
  -------------------------------------------------------------------------
  To design an IPv4 Bloom filter in practice, the bit array size (m) and 
  the number of hash functions (k) are mathematically calculated using:
  - n: Expected number of unique elements (IPs) to insert.
  - p: Acceptable false-positive error rate (e.g., 1% or 0.1%).

  Sizing Formulas:
  - m = - (n * ln(p)) / (ln(2)^2) ≈ -2.08 * n * ln(p) (Required bits)
  - k = (m / n) * ln(2) ≈ 0.7 * (m / n)               (Optimal hash functions)

  Sizing Table for IPv4 Address Databases:
  +-----------------------+-----------------------+---------------------+-------------------+----------------------------+
  | Expected Unique IPs(n)| False-Positive Rate(p)| Required Bits (m)   | Required Memory   | Optimal Hash Functions (k) |
  +-----------------------+-----------------------+---------------------+-------------------+----------------------------+
  | 10,000                | 1% (0.01)             | 95,850 bits         | 1.17 KB           | 7                          |
  | 10,000                | 0.1% (0.001)          | 143,776 bits        | 1.75 KB           | 10                         |
  | 100,000               | 1% (0.01)             | 958,505 bits        | 117 KB            | 7                          |
  | 100,000               | 0.1% (0.001)          | 1,437,760 bits      | 175.5 KB          | 10                         |
  | 1,000,000             | 1% (0.01)             | 9,585,058 bits      | 1.14 MB           | 7                          |
  | 1,000,000             | 0.1% (0.001)          | 14,377,604 bits     | 1.71 MB           | 10                         |
  +-----------------------+-----------------------+---------------------+-------------------+----------------------------+

  Key Sizing Takeaways:
  - In practice, we need roughly 9.6 bits per element for a 1% false positive rate 
    and 14.4 bits per element for a 0.1% false positive rate.
  - Filtering 1 Million IPs with a highly accurate 0.1% error rate requires only 
    1.71 MB of RAM, which easily fits inside a CPU's L2/L3 cache!

  -------------------------------------------------------------------------
  PRACTICAL IPV4 DESIGN OPTIMIZATIONS:
  -------------------------------------------------------------------------
  1. Store IPs as uint32_t (Not Strings):
     - Comparing/hashing IP strings (e.g., "192.168.1.1") is slow and takes up 
       to 15 bytes.
     - Converting IPs to standard 32-bit integers (e.g., 192.168.1.1 is 0xC0A80101) 
       using inet_pton() allows hashing extremely fast 4-byte primitives.

  2. Fast Double Hashing (Kirsch-Mitzenmacher Optimization):
     - Computing k independent cryptographic hashes is highly CPU-intensive.
     - We can instead generate any number of virtual hash values using only 
       TWO base hash functions (hash1 and hash2) via the linear combination:
       hash_i(x) = (hash1(x) + i * hash2(x)) % m
     - This evaluates 'k' hashes in O(1) time using simple additions.

  3. Use MurmurHash3:
     - Basic string hashes (like djb2/sdbm) have higher collision rates on 
       structured binary data like uint32_t IP integers.
     - MurmurHash3 (32-bit) is the industry standard for Bloom filters as it 
       is extremely fast and distributes bits with near-cryptographic uniformity.

  -------------------------------------------------------------------------
  Complexity Analysis:
  -------------------------------------------------------------------------
  - Time Complexity:
    - Add: O(k) where k is the number of hash functions.
    - Query: O(k).
    Reason: We compute k hash positions and read/write the bit positions in O(1) time.
  - Space Complexity:
    - O(m) bits to store the filter (where m is the size of the bit array).
*/

typedef uint32_t (*hash_func_t)(const char*);

typedef struct {
    uint8_t* bits;
    size_t numBits;
    hash_func_t* hashFuncs;
    int numHashFuncs;
} BloomFilter;

BloomFilter* bloomAlloc(size_t numBits, int numHashFuncs, hash_func_t funcs[]) {
    BloomFilter* bf = (BloomFilter*)malloc(sizeof(BloomFilter));
    bf->numBits = numBits;
    bf->bits = (uint8_t*)calloc((numBits + 7) / 8, sizeof(uint8_t));
    bf->numHashFuncs = numHashFuncs;
    bf->hashFuncs = (hash_func_t*)malloc(numHashFuncs * sizeof(hash_func_t));
    memcpy(bf->hashFuncs, funcs, numHashFuncs * sizeof(hash_func_t));
    return bf;
}

void bloomFree(BloomFilter* bf) {
    if (bf) {
        free(bf->bits);
        free(bf->hashFuncs);
        free(bf);
    }
}

void bloomAdd(BloomFilter* bf, const char* str) {
    for (int i = 0; i < bf->numHashFuncs; i++) {
        uint32_t h = bf->hashFuncs[i](str) % bf->numBits;
        bf->bits[h / 8] |= (1 << (h % 8));
    }
}

bool bloomCheck(BloomFilter* bf, const char* str) {
    for (int i = 0; i < bf->numHashFuncs; i++) {
        uint32_t h = bf->hashFuncs[i](str) % bf->numBits;
        if (!(bf->bits[h / 8] & (1 << (h % 8)))) return false;
    }
    return true;
}

// Simple Hash Functions
uint32_t djb2(const char* str) {
    uint32_t hash = 5381;
    int c;
    while ((c = *str++)) hash = ((hash << 5) + hash) + c;
    return hash;
}

uint32_t sdbm(const char* str) {
    uint32_t hash = 0;
    int c;
    while ((c = *str++)) hash = c + (hash << 6) + (hash << 16) - hash;
    return hash;
}

int main() {
    hash_func_t funcs[] = {djb2, sdbm};
    BloomFilter* bf = bloomAlloc(1024, 2, funcs);

    bloomAdd(bf, "apple");
    bloomAdd(bf, "banana");

    printf("Check apple:  %s\n", bloomCheck(bf, "apple") ? "Exists" : "No");
    printf("Check banana: %s\n", bloomCheck(bf, "banana") ? "Exists" : "No");
    printf("Check cherry: %s\n", bloomCheck(bf, "cherry") ? "Exists" : "No");

    bloomFree(bf);
    return 0;
}
