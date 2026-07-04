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

  Complexity Analysis:
  - Add: O(k) where k is the number of hash functions.
  - Query: O(k).
  - Space Complexity: O(m) bits.
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
