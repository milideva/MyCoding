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
| find(key)    | O(log n)          | O(n)            | O(h)          |
| insert(key)  | O(log n)          | O(n)            | O(h)          |
| erase(key)   | O(log n)          | O(n)            | O(h)          |
| Min/Max      | O(log n)          | O(n)            | O(h)          |

*Note on Space Complexity:* The space complexity is for the recursive call stack. `h` is O(log n) for a balanced tree (average case) and O(n) for a skewed tree (worst case). Iterative implementations use O(1) space.

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

    // --- Insertion (O(log n)) ---
    // insert() takes a value.
    bst_set.insert(8);
    bst_set.insert(3);
    bst_set.insert(10);

    // emplace() constructs the element in-place, which can be more efficient for complex types.
    bst_set.emplace(1);

    // Note on updating: You cannot directly change an element in a set as it would
    // violate the sorted order. You must erase the old element and insert the new one.
    bst_set.erase(10);
    bst_set.insert(11);

    // --- Search and Bounds (O(log n)) ---
    // find() returns an iterator to the element, or .end() if not found.
    if (bst_set.find(3) != bst_set.end()) {
        std::cout << "Found 3" << std::endl;
    } else {
        std::cout << "Did not find 3" << std::endl;
    }

    //std::lower_bound - returns iterator to first element in the given range which is EQUAL_TO or Greater than val. basically >= val.

    // std::upper_bound - returns iterator to first element in the given range which is strictly Greater than val. basically > val.

/* 
    value a a a m m m s s s
    index 0 1 2 3 4 5 6 7 8
    bound       l     u
    l is lower bound of m
    u is upper bound of m

    When the key b does not exist in the list, the upper and lower bound would be the first element bigger than b, which in this case is m at index 3.
*/
    // lower_bound() returns an iterator to the first element not less than the given key.
    auto it_lower = bst_set.lower_bound(4); // Will point to 8
    std::cout << "Lower bound of 4 is: " << *it_lower << std::endl;

    // upper_bound() returns an iterator to the first element greater than the given key.
    auto it_upper = bst_set.upper_bound(8); // Will point to 11
    std::cout << "Upper bound of 8 is: " << *it_upper << std::endl;

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

    // --- Insertion and Update (O(log n)) ---
    // operator[] is a convenient way to insert or update.
    // If the key doesn't exist, it inserts a default-constructed value, then assigns.
    bst_map[8] = "Eight";

    // insert() takes a std::pair. It will not overwrite an existing key.
    bst_map.insert({3, "Three"});

    // emplace() constructs the pair in-place, avoiding a copy. More efficient.
    bst_map.emplace(10, "Ten");

    // To update a value, simply use operator[] again.
    bst_map[8] = "New Eight";

    // --- Search and Bounds (O(log n)) ---
    // find() returns an iterator to the element, or .end() if not found.
    if (bst_map.find(3) != bst_map.end()) {
        std::cout << "Found key 3 with value: " << bst_map.at(3) << std::endl;
    }

    // lower_bound() returns an iterator to the first element with a key not less than the given key.
    auto it_lower = bst_map.lower_bound(9); // Will point to the pair {10, "Ten"}
    std::cout << "Lower bound of 9 is key: " << it_lower->first << std::endl;

    // upper_bound() returns an iterator to the first element with a key greater than the given key.
    auto it_upper = bst_map.upper_bound(8); // Will point to the pair {10, "Ten"}
    std::cout << "Upper bound of 8 is key: " << it_upper->first << std::endl;

    // In-order traversal by key
    std::cout << "Map contents:" << std::endl;
    for (const auto& pair : bst_map) {
        std::cout << pair.first << ": " << pair.second << std.endl;
    }

    return 0;
}
```


* Core BST Concepts
    98. Validate Binary Search Tree
    230. Kth Smallest Element in a BST
    235. Lowest Common Ancestor of a Binary Search Tree
    700. Search in a Binary Search Tree

* Construction and Modification

    450. Delete Node in a BST
    701. Insert into a Binary Search Tree
    108. Convert Sorted Array to Binary Search Tree

* Advanced Problems & Follow-ups

    285. Inorder Successor in BST
    272. Closest Binary Search Tree Value II
    1382. Balance a Binary Search Tree
