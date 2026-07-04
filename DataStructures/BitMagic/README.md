# BitMagic: Low-Level Optimization

Bit manipulation involves operating directly on the bits of a binary number. It's often used for performance-critical tasks and compact data representation.

## 🛠️ Essential Operators

- **AND (`&`)**: Sets bit to 1 only if both bits are 1.
- **OR (`\|`)**: Sets bit to 1 if at least one bit is 1.
- **XOR (`^`)**: Sets bit to 1 if only one of the bits is 1. (Useful for toggling and finding unique elements).
- **NOT (`~`)**: Inverts all bits.
- **Left Shift (`<<`)**: Multiplies by 2.
- **Right Shift (`>>`)**: Divides by 2.

---

## 🚀 Common Tricks

| Operation | Bitwise Expression |
| :--- | :--- |
| **Check if Even** | `(n & 1) == 0` |
| **Power of 2 Check** | `n > 0 && (n & (n - 1)) == 0` |
| **Clear Lowest Set Bit** | `n & (n - 1)` |
| **Get Lowest Set Bit** | `n & -n` |
| **Swap `x` and `y`** | `x ^= y; y ^= x; x ^= y;` |
| **Multiply by 2^k** | `n << k` |
| **Divide by 2^k** | `n >> k` |

---

## 📈 Complexity Analysis

All bitwise operations are **$O(1)$** at the hardware level, making them extremely fast.

---

## 🔗 Useful Resources
- [Bit Manipulation Handbook](https://github.com/ashishps1/bit-manipulation-handbook)
- [GeeksforGeeks: Bit Magic](https://www.geeksforgeeks.org/bit-magic/)
- [Hacker's Delight](http://www.hackersdelight.org/) (The "bible" of bit manipulation)
