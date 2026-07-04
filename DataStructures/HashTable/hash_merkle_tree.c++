#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

using namespace std;

/*
  Problem: Merkle Tree (Hash Tree) Implementation

  Problem Description:
  A Merkle tree is a tree in which every leaf node is labelled with 
  the cryptographic hash of a data block, and every non-leaf node is 
  labelled with the hash of the labels of its child nodes. 
  It is used to verify the integrity of data efficiently.

  Algorithm:
  1. Create leaf nodes for each data block, containing `hash(data)`.
  2. Pair up the nodes and create parent nodes containing 
     `hash(left_child_hash ^ right_child_hash)`.
  3. If there is an odd number of nodes, duplicate the last node or 
     promote it (this implementation promotes).
  4. Repeat until only one node (the Merkle Root) remains.

  Complexity Analysis:
  - Tree Construction: O(N) where N is the number of data blocks.
  - Integrity Verification: O(log N) to provide a Merkle proof.
  - Space Complexity: O(N) to store the tree nodes.
*/

struct Node {
    size_t hashValue;
    Node *left, *right;
    Node(size_t h) : hashValue(h), left(nullptr), right(nullptr) {}
};

class MerkleTree {
    Node* root;

    Node* buildTree(vector<Node*>& nodes) {
        if (nodes.size() == 1) return nodes[0];

        vector<Node*> parents;
        for (size_t i = 0; i < nodes.size(); i += 2) {
            if (i + 1 < nodes.size()) {
                // Combine two children
                size_t h = hash<size_t>{}(nodes[i]->hashValue ^ nodes[i+1]->hashValue);
                Node* p = new Node(h);
                p->left = nodes[i];
                p->right = nodes[i+1];
                parents.push_back(p);
            } else {
                // Odd one out, promote to parent level
                parents.push_back(nodes[i]);
            }
        }
        return buildTree(parents);
    }

    void deleteTree(Node* n) {
        if (!n) return;
        deleteTree(n->left);
        deleteTree(n->right);
        delete n;
    }

public:
    MerkleTree(const vector<string>& data) {
        vector<Node*> leaves;
        for (const string& s : data) {
            leaves.push_back(new Node(hash<string>{}(s)));
        }
        root = buildTree(leaves);
    }

    ~MerkleTree() { deleteTree(root); }

    size_t getRootHash() const { return root ? root->hashValue : 0; }
};

int main() {
    vector<string> data = {"block1", "block2", "block3", "block4"};
    MerkleTree tree(data);
    cout << "Merkle Root Hash: " << tree.getRootHash() << endl;

    vector<string> data2 = {"block1", "block2", "block3", "blockX"};
    MerkleTree tree2(data2);
    cout << "Modified Merkle Root Hash: " << tree2.getRootHash() << endl;

    return 0;
}
