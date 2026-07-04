# Strings: Processing and Manipulation

Strings are sequences of characters. In C, they are null-terminated char arrays. In C++, `std::string` provides a dynamic and feature-rich interface.

## 🚀 Key Patterns

### 1. Sliding Window
Crucial for substring problems where we need to find a window satisfying a property (e.g., all unique characters).
- **Problem examples**: `slidingwindow_longest_substring_without_repeating_characters`, `slidingwindow_find_all_anagrams_in_a_string`.

### 2. Two Pointers
Used for palindrome checks or in-place character swaps.
- **Problem examples**: `string_is_palindrome`, `string_reverse_string`.

### 3. Hash Map / Frequency Array
Tracking character counts for anagram detection or character uniqueness.
- **Problem examples**: `hashmap_valid_anagram`, `string_has_all_unique_characters`.

### 4. String Matching
Algorithms to find a pattern within a text.
- **Algorithms**: Naive (O(NM)), KMP (O(N+M)), Rabin-Karp (Rolling Hash).
- **Problem examples**: `string_naive_pattern_matching`.

---

## 🏗️ Common Operations

| Operation | C (Legacy) | C++ (Modern) |
| :--- | :--- | :--- |
| **Length** | `strlen(s)` | `s.length()` |
| **Compare** | `strcmp(s1, s2)` | `s1 == s2` |
| **Concat** | `strcat(s1, s2)` | `s1 += s2` |
| **Substring** | Pointer arithmetic | `s.substr(pos, len)` |

---

## 📈 Complexity Analysis

| Operation | Time Complexity | Space Complexity |
| :--- | :--- | :--- |
| **Access (Index)** | $O(1)$ | $O(1)$ |
| **Search (Naive)** | $O(N \cdot M)$ | $O(1)$ |
| **Reverse** | $O(N)$ | $O(1)$ |
| **Anagram Check** | $O(N)$ | $O(1)$ (fixed alphabet) |

---

## 🔗 Useful Resources
- [GeeksforGeeks: String Data Structure](https://www.geeksforgeeks.org/string-data-structure/)
- [LeetCode Explore: Strings](https://leetcode.com/explore/interview/card/top-interview-questions-easy/127/strings/)
- [C++ String Reference](https://en.cppreference.com/w/cpp/string/basic_string)
