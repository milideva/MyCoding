#include <iostream>
#include <vector>
#include <climits>
#include <cassert>

using namespace std;

/*
  Problem: Custom BitVector (Bitset) Implementation

  Problem Description:
  Implement a BitVector class that stores bits efficiently using a 
  byte array. Support operations like `Set`, `UnSet`, and `isSet`.

  Algorithm: Bitwise Manipulation
  1. Each byte stores `CHAR_BIT` (usually 8) bits.
  2. Indexing:
     - `byteIndex = index / 8`
     - `bitOffset = index % 8`
  3. Set: `arr[byteIndex] |= (1 << bitOffset)`
  4. Unset: `arr[byteIndex] &= ~(1 << bitOffset)`
  5. Check: `(arr[byteIndex] & (1 << bitOffset)) != 0`

  Complexity Analysis:
  - All operations (Set, UnSet, isSet): O(1).
  - Space Complexity: O(N/8) bytes for N bits.

  Comparison:
  - `std::vector<bool>`: Often specialized for space but has 
    implementation-defined behaviors.
  - `std::bitset<N>`: Size must be known at compile time.
  - Custom BitVector: Allows dynamic sizing while maintaining bit-level 
    space efficiency.
*/

class BitVector {
    unsigned char* byteArray;
    size_t numBits;
    size_t numBytes;

public:
    explicit BitVector(size_t sz) : numBits(sz) {
        numBytes = (sz + CHAR_BIT - 1) / CHAR_BIT;
        byteArray = new unsigned char[numBytes](); // Initialize to zero
    }

    ~BitVector() {
        delete[] byteArray;
    }

    void set(size_t index) {
        assert(index < numBits);
        byteArray[index / CHAR_BIT] |= (1 << (index % CHAR_BIT));
    }

    void unset(size_t index) {
        assert(index < numBits);
        byteArray[index / CHAR_BIT] &= ~(1 << (index % CHAR_BIT));
    }

    bool isSet(size_t index) const {
        assert(index < numBits);
        return (byteArray[index / CHAR_BIT] & (1 << (index % CHAR_BIT))) != 0;
    }

    size_t size() const { return numBits; }
};

void test() {
    cout << "Testing: Custom BitVector" << endl;
    BitVector bv(40);
    
    bv.set(25);
    cout << "  Bit 25 is set: " << boolalpha << bv.isSet(25) << " (Expected: true)" << endl;
    
    bv.unset(25);
    cout << "  Bit 25 is set: " << boolalpha << bv.isSet(25) << " (Expected: false)" << endl;
    
    bv.set(0);
    cout << "  Bit 0 is set: " << boolalpha << bv.isSet(0) << " (Expected: true)" << endl;
}

int main() {
    test();
    return 0;
}
