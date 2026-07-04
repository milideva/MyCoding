#include <vector>
#include <iostream>
#include <cassert>
using namespace std;

/* 
  LeetCode 82: Remove Duplicates from Sorted List II

  Problem Description:
  Given the head of a sorted linked list, delete all nodes that have 
  duplicate numbers, leaving only distinct numbers from the original 
  list. Return the linked list sorted as well.

  Algorithm: Iterative with Dummy Node
  1. Use a dummy node pointing to the head to handle deletions of the 
     actual head node.
  2. Maintain a `prev` pointer (initially dummy) and a `curr` pointer 
     (initially head).
  3. While `curr` and its next node exist:
     - If `curr->val == curr->next->val`:
       - Skip all nodes with this value.
       - Link `prev->next` to the node after the last duplicate.
     - Else:
       - Move `prev` to `curr`.
     - Move `curr` to the next potential distinct node.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: Each node is visited at most twice.
  - Space Complexity: O(1) auxiliary space (excluding the dummy node).

  Alternative Approaches:
  - Recursive:
    - Logic: If current node is part of a duplicate sublist, return 
      `deleteDuplicates(next_distinct_node)`. Otherwise, link 
      `head->next` to the recursive call result.
    - Time: O(N), Space: O(N) for recursion stack.
  
  Brute Force comparison:
  - Count frequencies using a hash map, then rebuild the list.
  - Time: O(N), Space: O(N).
  - The iterative O(1) space approach is more efficient as it works in-place.
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head) return head;
        
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        
        ListNode *prev = dummy, *curr = head;
        while (curr) {
            if (curr->next && curr->val == curr->next->val) {
                int duplicateVal = curr->val;
                while (curr && curr->val == duplicateVal) {
                    ListNode *temp = curr;
                    curr = curr->next;
                    delete temp;
                }
                prev->next = curr;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
};

//=========================================================================
// Utility functions for testing
//=========================================================================

ListNode* createLinkedList(vector<int> vals) {
    if (vals.empty()) return nullptr;
    ListNode* head = new ListNode(vals[0]);
    ListNode* current = head;
    for (size_t i = 1; i < vals.size(); ++i) {
        current->next = new ListNode(vals[i]);
        current = current->next;
    }
    return head;
}

vector<int> linkedListToVector(ListNode* head) {
    vector<int> result;
    while (head) {
        result.push_back(head->val);
        head = head->next;
    }
    return result;
}

void deleteLinkedList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void test(const string& label, vector<int> input, vector<int> expected) {
    cout << "Testing: " << label << endl;
    ListNode* head = createLinkedList(input);
    Solution sol;
    ListNode* result = sol.deleteDuplicates(head);
    vector<int> resultVec = linkedListToVector(result);
    
    if (resultVec == expected) {
        cout << "  [PASS]" << endl;
    } else {
        cout << "  [FAIL] Result: ";
        for (int v : resultVec) cout << v << " ";
        cout << " (Expected: ";
        for (int v : expected) cout << v << " ";
        cout << ")" << endl;
    }
    deleteLinkedList(result);
}

int main() {
    test("Example 1", {1,2,3,3,4,4,5}, {1,2,5});
    test("Example 2", {1,1,1,2,3}, {2,3});
    test("All duplicates", {1,1,1}, {});
    test("Empty list", {}, {});
    test("No duplicates", {1,2,3}, {1,2,3});
    return 0;
}
