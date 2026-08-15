#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

/*
  LeetCode 297/449: Serialize and Deserialize Binary Tree / BST

  Algorithm: Level-Order (BFS)
  1. Serialization:
     - Use a queue to perform level-order traversal.
     - For each node, append its value to the string.
     - If a node is null, append a marker (e.g., "null").
  2. Deserialization:
     - Split the string into tokens.
     - Use a queue to reconstruct the tree level by level.
     - For each parent in the queue, assign the next two tokens 
       as its left and right children.

  Complexity Analysis:
  - Time Complexity: O(N)
  - Space Complexity: O(N).
*/

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Codec {
public:
    string serialize(TreeNode* root) {
        if (!root) return "";
        string s = "";
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();
            if (curr) {
                s += to_string(curr->val) + ",";
                q.push(curr->left);
                q.push(curr->right);
            } else {
                s += "null,";
            }
        }
        return s;
    }

    TreeNode* deserialize(string data) {
        if (data.empty()) return nullptr;
        stringstream ss(data);
        string item;
        getline(ss, item, ',');
        TreeNode* root = new TreeNode(stoi(item));
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();

            if (getline(ss, item, ',')) {
                if (item != "null") {
                    curr->left = new TreeNode(stoi(item));
                    q.push(curr->left);
                }
            }
            if (getline(ss, item, ',')) {
                if (item != "null") {
                    curr->right = new TreeNode(stoi(item));
                    q.push(curr->right);
                }
            }
        }
        return root;
    }
};

void inorder(TreeNode* root) {
    if (root) {
        inorder(root->left);
        cout << root->val << " ";
        inorder(root->right);
    }
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);

    Codec codec;
    string serialized = codec.serialize(root);
    cout << "Serialized: " << serialized << endl;

    TreeNode* deserialized = codec.deserialize(serialized);
    cout << "Inorder of Deserialized: ";
    inorder(deserialized);
    cout << endl;

    return 0;
}
