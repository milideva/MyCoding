# Binary Search Tree (BST)

A Binary Search Tree is a node-based binary tree data structure which has the following properties:
- The left subtree of a node contains only nodes with keys lesser than the node's key.
- The right subtree of a node contains only nodes with keys greater than the node's key.
- The left and right subtree each must also be a binary search tree.
- There must be no duplicate nodes.

## Operations & Complexity

Let 'n' be the number of nodes in the BST and 'h' be the height of the BST.
The height of a balanced BST is O(log n). The height of a skewed (unbalanced) BST is O(n).

| Operation    | Average Case Time | Worst Case Time | Space (Worst) |
|--------------|-------------------|-----------------|---------------|
| Search(key)  | O(log n)          | O(n)            | O(h) or O(log n) for recursive stack |
| Insert(key)  | O(log n)          | O(n)            | O(h) or O(log n) for recursive stack |
| Delete(key)  | O(log n)          | O(n)            | O(h) or O(log n) for recursive stack |
| Min/Max      | O(log n)          | O(n)            | O(h) or O(log n) for recursive stack |

## Visual Representation

### 1. Balanced BST

```
         8
       /   \
      3     10
     / \      \
    1   6      14
       / \    /
      4   7  13
```

In this tree, for any node, all values in its left subtree are smaller,
and all values in its right subtree are larger. The height is roughly log(n).

### 2. Unbalanced (Skewed) BST

This can happen when inserting elements in a sorted order (e.g., 1, 2, 3, 4, 5).
The tree becomes equivalent to a linked list.

```
     1
      \
       2
        \
         3
          \
           4
            \
             5
```

In this worst-case scenario, the height of the tree is 'n', and the time complexity
for operations degrades to O(n). This is why self-balancing BSTs like AVL trees
or Red-Black Trees are often used in practice.

## Applications of BST

- **Database Indexing:** Used to structure the indexes in database systems to speed up queries.
- **Associative Containers:** The underlying data structure for implementing `map` and `set` objects in many standard libraries.
- **Symbol Tables:** Used in compilers to store information about symbols like variable names, function names, etc.
- **Search Autocompletion:** Can be used to store a dictionary and efficiently find words with a given prefix.
- **Network Routing:** Can be used to store routing tables in routers.

## Pros and Cons

### Pros
- **Efficient Operations:** On average, search, insert, and delete operations are very fast (O(log n)).
- **Ordered Data:** Keeps elements sorted, which allows for efficient in-order traversal to retrieve items in a sorted manner, and enables range queries (finding all items between two values).
- **Simple to Implement:** Compared to self-balancing trees, a basic BST is relatively easy to code.

### Cons
- **Worst-Case Performance:** The major disadvantage is that performance degrades to O(n) for all operations if the tree becomes unbalanced. This happens when inserting data that is already sorted or nearly sorted.
- **No Constant Time:** No operation is guaranteed O(1). A hash table might be better if you need constant-time lookups and order is not important.

## When Should You NOT Use a BST?

- **When data is sorted:** If you are inserting items in a sorted (or nearly sorted) order, you will create a skewed tree. In this case, a **self-balancing BST** (like an AVL Tree or Red-Black Tree) is a much better choice.
- **When you need guaranteed performance:** If you cannot risk the O(n) worst-case scenario, use a self-balancing BST.
- **When you need O(1) lookups:** If your primary need is fast key-based lookups and you don't need the data to be sorted, use a **Hash Table**.

## BST in C++ STL

The C++ Standard Template Library (STL) does not provide a direct `std::bst` class. However, it provides `std::set` and `std::map`, which are typically implemented using a **Red-Black Tree**, a type of self-balancing BST.

This means you get the benefits of a balanced BST (guaranteed O(log n) operations) without having to implement the balancing logic yourself.

- Use `std::set` when you just need to store a collection of unique, sorted keys.
- Use `std::map` when you need to store key-value pairs, sorted by key.

### `std::set` Example

```cpp
#include <iostream>
#include <set>

int main() {
    std::set<int> bst_set;

    // Insert elements (O(log n))
    bst_set.insert(8);
    bst_set.insert(3);
    bst_set.insert(10);
    bst_set.insert(1);

    // Search for an element (O(log n))
    if (bst_set.find(3) != bst_set.end()) {
        std::cout << "Found 3" << std::endl;
    } else {
        std::cout << "Did not find 3" << std::endl;
    }

    // In-order traversal (prints sorted elements)
    std::cout << "Set contents: ";
    for (int key : bst_set) {
        std::cout << key << " ";
    }
    std::cout << std::endl;

    // Delete an element (O(log n))
    bst_set.erase(3);

    return 0;
}
```

### `std::map` Example

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<int, std::string> bst_map;

    // Insert key-value pairs (O(log n))
    bst_map[8] = "Eight";
    bst_map.insert({3, "Three"});
    bst_map.emplace(10, "Ten");

    // Search for a key (O(log n))
    if (bst_map.find(3) != bst_map.end()) {
        std::cout << "Found key 3 with value: " << bst_map.at(3) << std::endl;
    }

    // In-order traversal by key
    std::cout << "Map contents:" << std::endl;
    for (const auto& pair : bst_map) {
        std::cout << pair.first << ": " << pair.second << std.endl;
    }

    return 0;
}
```