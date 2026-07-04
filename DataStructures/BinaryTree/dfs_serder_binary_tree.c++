/**
 * Problem: Serialize and Deserialize Binary Tree
 * Design an algorithm to serialize and deserialize a binary tree.
 * 
 * Strategy: DFS (Pre-order) with NULL Markers
 * - Serialization: Pre-order traversal, append "null" for nullptr, comma-delimited.
 * - Deserialization: Split string by comma into a queue/list, recursively 
 *   reconstruct using pre-order logic.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Codec {
    void serializeHelper(TreeNode* root, stringstream& ss) {
        if (!root) {
            ss << "null,";
            return;
        }
        ss << root->val << ",";
        serializeHelper(root->left, ss);
        serializeHelper(root->right, ss);
    }

    TreeNode* deserializeHelper(queue<string>& q) {
        string val = q.front();
        q.pop();

        if (val == "null") {
            return nullptr;
        }

        TreeNode* root = new TreeNode(stoi(val));
        root->left = deserializeHelper(q);
        root->right = deserializeHelper(q);
        return root;
    }

public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        stringstream ss;
        serializeHelper(root, ss);
        return ss.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        queue<string> q;
        stringstream ss(data);
        string item;
        while (getline(ss, item, ',')) {
            q.push(item);
        }
        return deserializeHelper(q);
    }
};

/**
 * Utility to print in-order traversal.
 */
void printInOrder(TreeNode* root) {
    if (!root) return;
    printInOrder(root->left);
    cout << root->val << " ";
    printInOrder(root->right);
}

int main() {
    // Test Case 1: [1,2,3,null,null,4,5]
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);

    Codec codec;
    string serialized = codec.serialize(root);
    cout << "Serialized: " << serialized << endl;

    TreeNode* deserialized = codec.deserialize(serialized);
    cout << "Deserialized (In-order): ";
    printInOrder(deserialized);
    cout << endl << endl;

    // Test Case 2 (from tree.txt): [20, 8, 22, 4, 12]
    TreeNode* root2 = new TreeNode(20);
    root2->left = new TreeNode(8);
    root2->right = new TreeNode(22);
    root2->left->left = new TreeNode(4);
    root2->left->right = new TreeNode(12);

    string serialized2 = codec.serialize(root2);
    cout << "Serialized 2: " << serialized2 << endl;
    TreeNode* deserialized2 = codec.deserialize(serialized2);
    cout << "Deserialized 2 (In-order): ";
    printInOrder(deserialized2);
    cout << endl;

    return 0;
}
