#include <iostream>
#include <vector>

using namespace std;

/*
  LeetCode 708: Insert into a Sorted Circular Linked List

  Problem Description:
  Given a node from a Circular Linked List which is sorted in ascending 
  order, write a function to insert a value `insertVal` into the list 
  such that it remains a sorted circular list. The given node can be 
  a reference to any single node in the list.

  If the list is empty, create a new single circular list. 
  If there are multiple suitable places, choose any.

  Algorithm: Single Pass Iterative
  1. If `head` is null, create a new node, point its `next` to itself, 
     and return it.
  2. Traverse the list with `prev` and `curr` pointers.
  3. Cases for insertion:
     - Case 1: `prev->val <= insertVal <= curr->val`. Standard middle 
       insertion.
     - Case 2: `curr->val < prev->val`. This is the tail-to-head link.
       Insert here if `insertVal >= prev->val` (largest) or 
       `insertVal <= curr->val` (smallest).
     - Case 3: Completed a full circle without finding Case 1 or 2. 
       This happens if all nodes have the same value. Insert anywhere.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: In the worst case, we traverse the entire circular list once.
  - Space Complexity: O(1) auxiliary space.

  Brute Force comparison:
  - Find the minimum node first (O(N)), then find the insertion point 
    as if it were a linear list (O(N)).
  - The current approach is more efficient as it finds the insertion 
    point in a single pass from an arbitrary starting node.
*/

class Node {
public:
    int val;
    Node* next;
    Node(int _val) : val(_val), next(nullptr) {}
    Node(int _val, Node* _next) : val(_val), next(_next) {}
};

class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        Node* newNode = new Node(insertVal);
        if (!head) {
            newNode->next = newNode;
            return newNode;
        }

        Node *prev = head, *curr = head->next;
        bool found = false;

        do {
            if (prev->val <= insertVal && insertVal <= curr->val) {
                found = true;
            } else if (prev->val > curr->val) {
                // Potential tail/head link
                if (insertVal >= prev->val || insertVal <= curr->val) {
                    found = true;
                }
            }

            if (found) {
                prev->next = newNode;
                newNode->next = curr;
                return head;
            }

            prev = curr;
            curr = curr->next;
        } while (prev != head);

        // Case 3: All nodes have same value
        prev->next = newNode;
        newNode->next = curr;
        return head;
    }
};

//=========================================================================
// Test Code
//=========================================================================

void printList(Node* head) {
    if (!head) {
        cout << "Empty" << endl;
        return;
    }
    Node* curr = head;
    do {
        cout << curr->val << " -> ";
        curr = curr->next;
    } while (curr != head);
    cout << "(head)" << endl;
}

void destroyList(Node* head) {
    if (!head) return;
    Node* curr = head->next;
    while (curr != head) {
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
    delete head;
}

void test(const string& label, const vector<int>& vals, int insertVal) {
    cout << "Testing: " << label << " (Insert: " << insertVal << ")" << endl;
    Node* head = nullptr;
    if (!vals.empty()) {
        head = new Node(vals[0]);
        Node* curr = head;
        for (size_t i = 1; i < vals.size(); ++i) {
            curr->next = new Node(vals[i]);
            curr = curr->next;
        }
        curr->next = head;
    }

    Solution sol;
    head = sol.insert(head, insertVal);
    printList(head);
    destroyList(head);
}

int main() {
    test("Example 1", {3, 4, 1}, 2);
    test("Example 2", {}, 1);
    test("Single Node", {1}, 0);
    test("Duplicate Values", {3, 3, 3}, 4);
    test("Tail Insertion", {1, 3, 5}, 6);
    return 0;
}
