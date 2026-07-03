#include <vector>
#include <list>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

/*

Serialization is the process of converting a data structure or object into a
sequence of bits so that it can be stored in a file or memory buffer, or
transmitted across a network connection link to be reconstructed later in the
same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no
restriction on how your serialization/deserialization algorithm should work. You
just need to ensure that a binary tree can be serialized to a string and this
string can be deserialized to the original tree structure.

Example 1:

Input: root = [1,2,3,null,null,4,5]
Output: [1,2,3,null,null,4,5]

Example 2:

Input: root = []
Output: []

Example 3:

Input: root = [1]
Output: [1]

Example 4:

Input: root = [1,2]
Output: [1,2]

*/

// MARKER is a sentinel value used to represent a null/empty node in the level-order input vector.
const int MARKER = -1;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Codec {
public:
  void helperSer (TreeNode* root, string &res) {
    if (!root) {
      res += "null,";
      return;
    }
    res += to_string(root->val) + ",";
    helperSer(root->left, res);
    helperSer(root->right, res);
  }
  // Encodes a tree to a single string.
  string serialize(TreeNode* root) {
    string ser = "";
    helperSer(root, ser);
    return ser;
  }

  TreeNode * helperDeser(list <string>& lStr) {
    if (lStr.front() == "null") {
      lStr.pop_front();
      return nullptr;
    }
    TreeNode* root = new TreeNode(stoi(lStr.front()));
    lStr.pop_front();
    root->left = helperDeser(lStr);
    root->right = helperDeser(lStr);
    return root;
  }


  TreeNode* deserialize(string data) {
    list <string> lStr;
    string tmp = "";
    // remove delimiter ,
    for (size_t i = 0; i < data.size(); i++) {
      if (data[i] == ',') {
        lStr.push_back(tmp);
        tmp = "";
      } else {
        tmp +=  data[i];
      }
    }

    TreeNode *root = helperDeser(lStr);
    return root;
  }
};

// Builds a tree from a standard LeetCode-style level-order vector.
TreeNode* createTreeFromLevelOrder(const vector<int>& arr) {
    if (arr.empty() || arr[0] == MARKER) return nullptr;

    TreeNode* root = new TreeNode(arr[0]);
    queue<TreeNode*> q;
    q.push(root);

    size_t i = 1;
    while (!q.empty() && i < arr.size()) {
        TreeNode* current = q.front();
        q.pop();

        // We process next two nodes, left first and then right
        // Process Left Child
        if (i < arr.size() && arr[i] != MARKER) {
            TreeNode *left = new TreeNode(arr[i]);
            current->left = left;
            q.push(left);
        }

        // Move to the next element for the next child
        i++;

        // Process Right Child
        if (i < arr.size() && arr[i] != MARKER) {
            TreeNode *right = new TreeNode(arr[i]);
            current->right = right;
            q.push(right);
        }

        // Move to the next element for the next node
        i++;
    }

    return root;
}

static void inorder (TreeNode *root)  {
    if (root) {
        inorder(root->left);
        printf("%d ", root->val);
        inorder(root->right);
    }
}

void print_inorder (TreeNode *n) {
    printf("print_inorder: ");
    inorder(n);
    printf("\n");
}

void destroyTree(TreeNode* node) {
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

int main (void) {

    // root = [1,2,3,null,null,4,5]
    vector<int> nodes = {1, 2, 3, MARKER, MARKER, 4, 5};
    TreeNode *root = createTreeFromLevelOrder(nodes);
    print_inorder(root);

    Codec cdc;

    string ser = cdc.serialize(root);
    cout << "Serialized string: " << ser << endl;

    TreeNode *deserRoot = cdc.deserialize(ser);

    cout << "Deserialized ";
    print_inorder(deserRoot);

    destroyTree(root);
    destroyTree(deserRoot);

    return 0;
}
