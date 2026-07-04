#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*
  Problem: Bit Array (Bitset) Implementation in C

  Problem Description:
  Implement a dynamic bit array that can store a large number of bits 
  using an underlying array of long integers.

  Algorithm:
  1. Each element in the `bits` array (type `unsigned long`) stores 
     `BITS_PER_ELEM` bits.
  2. Allocation: `BITS_TO_ELEMS(n)` gives the number of long integers 
     needed to store `n` bits.
  3. Set Bit `n`:
     - Element index: `n / BITS_PER_ELEM`
     - Bit index within element: `n % BITS_PER_ELEM`
     - `bits[elem_idx] |= (1UL << bit_idx)`
  4. Clear Bit `n`:
     - `bits[elem_idx] &= ~(1UL << bit_idx)`

  Complexity Analysis:
  - Allocation: O(bits / word_size).
  - Set/Clear/Get: O(1).
  - Space Complexity: O(bits).
*/

typedef unsigned long bitlist_elem_t;
#define BITS_PER_ELEM (sizeof(bitlist_elem_t) * CHAR_BIT)

typedef struct {
    bitlist_elem_t* bits;
    unsigned int maxBits;
} BitList;

BitList* bitListAlloc(unsigned int numBits) {
    BitList* bl = (BitList*)malloc(sizeof(BitList));
    if (!bl) return NULL;
    
    unsigned int numElems = (numBits + BITS_PER_ELEM - 1) / BITS_PER_ELEM;
    bl->bits = (bitlist_elem_t*)calloc(numElems, sizeof(bitlist_elem_t));
    if (!bl->bits) {
        free(bl);
        return NULL;
    }
    bl->maxBits = numBits;
    return bl;
}

void bitListFree(BitList* bl) {
    if (bl) {
        free(bl->bits);
        free(bl);
    }
}

void bitListSet(BitList* bl, unsigned int bit) {
    if (bl && bit < bl->maxBits) {
        bl->bits[bit / BITS_PER_ELEM] |= (1UL << (bit % BITS_PER_ELEM));
    }
}

void bitListClear(BitList* bl, unsigned int bit) {
    if (bl && bit < bl->maxBits) {
        bl->bits[bit / BITS_PER_ELEM] &= ~(1UL << (bit % BITS_PER_ELEM));
    }
}

bool bitListGet(BitList* bl, unsigned int bit) {
    if (bl && bit < bl->maxBits) {
        return (bl->bits[bit / BITS_PER_ELEM] & (1UL << (bit % BITS_PER_ELEM))) != 0;
    }
    return false;
}

int main() {
    printf("Testing Dynamic Bit Array\n");
    BitList* bl = bitListAlloc(100);
    
    bitListSet(bl, 7);
    bitListSet(bl, 65); // Second long element if 64-bit
    
    printf("  Bit 7 is set: %s\n", bitListGet(bl, 7) ? "Yes" : "No");
    printf("  Bit 65 is set: %s\n", bitListGet(bl, 65) ? "Yes" : "No");
    printf("  Bit 10 is set: %s\n", bitListGet(bl, 10) ? "Yes" : "No");
    
    bitListClear(bl, 7);
    printf("  After clearing, Bit 7 is set: %s\n", bitListGet(bl, 7) ? "Yes" : "No");
    
    bitListFree(bl);
    return 0;
}
