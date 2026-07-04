#include <stdio.h>

/*
  Problem: C Bit Fields Usage

  Problem Description:
  Demonstrate the usage of bit fields in C to store multiple 
  Boolean or small integer values in a single memory word.

  Details:
  - Bit fields allow you to specify the exact number of bits for 
    struct members.
  - Useful for memory-constrained environments or mapping to 
    hardware registers.
  - The compiler packs these fields into adjacent bits if possible.

  Caution:
  - Behavior like ordering (endianness) and padding is 
    implementation-defined.
*/

struct Flags {
    unsigned int isReady : 1;
    unsigned int hasError : 1;
    unsigned int mode : 3;      // 0 to 7
    unsigned int priority : 4;  // 0 to 15
};

int main() {
    struct Flags f = {0};
    
    f.isReady = 1;
    f.mode = 5;
    f.priority = 10;
    
    printf("Size of struct Flags: %zu bytes\n", sizeof(struct Flags));
    printf("Ready: %u, Mode: %u, Priority: %u\n", f.isReady, f.mode, f.priority);
    
    // Test overflow
    f.mode = 8; // 8 is 1000, only 3 bits (000) will be stored
    printf("After setting Mode=8 (overflow): %u\n", f.mode);
    
    return 0;
}
