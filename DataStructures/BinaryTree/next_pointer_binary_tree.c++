#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/*
  LeetCode 116 / 117: Populating Next Right Pointers in Each Node

  Problem: Connect each node to its next right neighbor at the same height.

  Algorithm: Breadth-First Search (BFS) / Level Order Traversal
  We use a queue to process the tree level by level. For each node in a 
  level, we point its `next` pointer to the node currently at the front 
  of the queue (unless it is the last node of the level).

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: Every node in the tree is visited exactly once.
  - Space Complexity: O(W) or O(N)
    Reason: The queue holds at most one level of nodes. For a perfect 
    binary tree, the maximum width W is N/2.

  Alternative Approaches:
  - O(1) Space (Iterative DFS/BFS variant): If the tree is perfect (LC 116), 
    we can use the `next` pointers established in the level above to 
    connect the current level without using a queue.
    - Logic: `curr->left->next = curr->right;` 
             `if (curr->next) curr->right->next = curr->next->left;`
  
  Comparison:
  - The BFS approach is the most general and works for both perfect and
    non-perfect binary trees (LC 117). The O(1) space approach is highly
    optimized but harder to generalize to arbitrary trees.

  Brute Force Approach:
  - 1. For every level i, collect all nodes in an array.
  - 2. Iterate through the array and link node[j]->next = node[j+1].
  - Time: O(N), Space: O(N) to store all nodes level by level.
  - Comparison: BFS with a queue is O(N) time and O(W) space, which is 
    generally better than storing all nodes at once.
*/

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode *next;
  TreeNode() : val(0), left(nullptr), right(nullptr), next(nullptr){}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}
};

// MARKER is a sentinel value used to represent a null/empty node in the level-order input vector.
const int MARKER = -1;

class Solution {

public:
  TreeNode* connect(TreeNode* root) {
    if (!root) return nullptr;
    // This is a Simple BFS
    queue <TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
      int size = q.size();
      while (size--) {
	      TreeNode *n = q.front(); q.pop();
	      if (size == 0) {
	        n->next = nullptr;
	      } else {
	        n->next = q.front();
	      }
	      if (n->left)
	        q.push(n->left);
	      if (n->right)
	        q.push(n->right);
      }
    }
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

void printLevelsWithNext(TreeNode* root) {
    TreeNode* levelStart = root;
    while (levelStart) {
        TreeNode* curr = levelStart;
        while (curr) {
            cout << curr->val << (curr->next ? " -> " : " -> NULL");
            curr = curr->next;
        }
        cout << endl;
        // Move to the next level. Note: for perfect binary trees, this is levelStart->left.
        // For general trees, we'd need a BFS approach to find the first node of the next level.
        TreeNode* nextLevel = nullptr;
        curr = levelStart;
        while (curr && !nextLevel) {
            if (curr->left) nextLevel = curr->left;
            else if (curr->right) nextLevel = curr->right;
            curr = curr->next;
        }
        levelStart = nextLevel;
    }
}

void destroyTree(TreeNode* node) {
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

int main () {
  vector<int> nodes = {1, 2, 3, 4, 5, 6, 7};
  TreeNode *root = createTreeFromLevelOrder(nodes);

  Solution sol;
  root = sol.connect(root);

  cout << "Connections using 'next' pointers:" << endl;
  printLevelsWithNext(root);

  destroyTree(root);
  return 0;
}
