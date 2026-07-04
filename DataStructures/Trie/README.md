# Trie (Prefix Tree): Efficient String Retrieval

A Trie, also called digital tree or prefix tree, is a type of search tree used for locating specific keys from within a set. These keys are most often strings.

## 🏗️ Structure

Each node in a Trie consists of:
- An array of pointers (usually 26 for English lowercase letters) to its children.
- A boolean flag `isEndOfWord` (or `isTerminal`) to indicate if the node represents the end of a complete word.

```text
       (root)
      /   |   \
     a    b    c
    / \   |    |
   n   t  y    a
  /    |  |    |
 t     e  e    t
(isEnd) (isEnd) (isEnd)
```

---

## 🚀 Key Operations

### 1. Insertion
- For each character in the word:
  - If the character exists as a child, move to it.
  - Otherwise, create a new node.
- Mark the last node as `isEndOfWord`.

### 2. Search
- Traverse the tree following the characters of the word.
- If a character is missing, the word is not in the Trie.
- If all characters match, check the `isEndOfWord` flag.

### 3. Prefix Search (startsWith)
- Similar to search, but you don't check the `isEndOfWord` flag at the end.

---

## 📈 Complexity Analysis

| Operation | Time Complexity | Space Complexity |
| :--- | :--- | :--- |
| **Insert** | $O(L)$ | $O(N \cdot L \cdot \Sigma)$ |
| **Search** | $O(L)$ | $O(1)$ |
| **Prefix Search** | $O(L)$ | $O(1)$ |

- **$L$**: Length of the word.
- **$N$**: Total number of words.
- **$\Sigma$**: Size of the alphabet (e.g., 26).

---

## 🔗 Useful Resources
- [GeeksforGeeks: Trie Data Structure](https://www.geeksforgeeks.org/trie-insert-and-search/)
- [Visualgo: Trie Visualization](https://visualgo.net/en/trie)
- [LeetCode Explore: Trie](https://leetcode.com/explore/learn/card/trie/)
