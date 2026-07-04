#include <vector>
#include <cassert>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

/*
  LeetCode 208: Implement Trie (Prefix Tree)

  Problem Description:
  Implement a Trie with `insert`, `search`, and `startsWith` methods.

  Algorithm: Trie Tree using Smart Pointers
  1. Each `TrieNode` contains:
     - `children[26]`: Pointers to next level nodes.
     - `isEndOfWord`: Boolean flag.
  2. Use `std::shared_ptr` for automatic memory management.

  Complexity Analysis:
  - Time Complexity: O(L) for all operations.
  - Space Complexity: O(Total characters in all words * 26).
*/

struct TrieNode {
    vector<shared_ptr<TrieNode>> children;
    bool isEndOfWord;

    TrieNode() : children(26, nullptr), isEndOfWord(false) {}
};

class Trie {
    shared_ptr<TrieNode> root;

    shared_ptr<TrieNode> find(const string& prefix) {
        shared_ptr<TrieNode> curr = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!curr->children[idx]) return nullptr;
            curr = curr->children[idx];
        }
        return curr;
    }

public:
    Trie() : root(make_shared<TrieNode>()) {}

    void insert(const string& word) {
        shared_ptr<TrieNode> curr = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!curr->children[idx]) {
                curr->children[idx] = make_shared<TrieNode>();
            }
            curr = curr->children[idx];
        }
        curr->isEndOfWord = true;
    }

    bool search(const string& word) {
        shared_ptr<TrieNode> node = find(word);
        return node != nullptr && node->isEndOfWord;
    }

    bool startsWith(const string& prefix) {
        return find(prefix) != nullptr;
    }
};

void test() {
    Trie trie;
    trie.insert("apple");
    cout << "Search \"apple\": " << boolalpha << trie.search("apple") << " (Expected: true)" << endl;
    cout << "Search \"app\":   " << boolalpha << trie.search("app") << " (Expected: false)" << endl;
    cout << "Prefix \"app\":   " << boolalpha << trie.startsWith("app") << " (Expected: true)" << endl;
    trie.insert("app");
    cout << "Search \"app\":   " << boolalpha << trie.search("app") << " (Expected: true)" << endl;
}

int main() {
    test();
    return 0;
}
