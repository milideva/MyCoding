#include <iostream>
#include <vector>

using namespace std;

/*
  LeetCode 92: Reverse Linked List II

  Problem Description:
  Given the head of a singly linked list and two integers `left` and 
  `right` where `left <= right`, reverse the nodes of the list from 
  position `left` to position `right`, and return the reversed list.

  Example 1:
  Input: head = [1,2,3,4,5], left = 2, right = 4
  Output: [1,4,3,2,5]

  Algorithm: Iterative In-place Reversal
  1. Use a `dummy` node pointing to `head` to handle cases where `left=1`.
  2. Traverse the list to find the node just before the reversal range 
     (`beforeRev`).
  3. The reversal range starts at `curr = beforeRev->next`.
  4. Perform the reversal using a "moving next" strategy:
     - For `right - left` times:
       - Take the node AFTER `curr` (`target`).
       - Remove `target` from its position.
       - Re-insert `target` immediately after `beforeRev`.
  5. This strategy avoids the need for a separate stack and reverses 
     the range in a single pass.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We traverse the list once up to the `right` position.
  - Space Complexity: O(1) auxiliary space.

  Brute Force comparison:
  - Collect the nodes in the range [left, right] into an array/stack, 
    reverse their values, and update the nodes. 
  - Time: O(N), Space: O(N) for the temporary storage.
  - The iterative in-place approach is superior as it only uses 
    constant extra space.
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (!head || left == right) return head;

        ListNode dummy(0);
        dummy.next = head;
        ListNode *beforeRev = &dummy;

        // 1. Reach the node just before the start of the reversal range
        for (int i = 0; i < left - 1; ++i) {
            beforeRev = beforeRev->next;
        }

        // 2. Perform the reversal by moving 'target' nodes one by one
        ListNode *curr = beforeRev->next;
        for (int i = 0; i < right - left; ++i) {
            ListNode *target = curr->next;
            curr->next = target->next;
            target->next = beforeRev->next;
            beforeRev->next = target;
        }

        return dummy.next;
    }
};

//=========================================================================
// Test Code
//=========================================================================

ListNode* createList(const vector<int>& vals) {
    ListNode dummy(0);
    ListNode* curr = &dummy;
    for (int v : vals) {
        curr->next = new ListNode(v);
        curr = curr->next;
    }
    return dummy.next;
}

void printList(ListNode* head) {
    while (head) {
        cout << head->val << (head->next ? " -> " : "");
        head = head->next;
    }
    cout << endl;
}

void destroyList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void test(const string& label, const vector<int>& input, int left, int right) {
    cout << "Testing: " << label << " (Range: [" << left << "," << right << "])" << endl;
    ListNode* head = createList(input);
    Solution sol;
    ListNode* result = sol.reverseBetween(head, left, right);
    printList(result);
    destroyList(result);
}

int main() {
    test("Example 1", {1, 2, 3, 4, 5}, 2, 4);
    test("Full Range", {1, 2, 3}, 1, 3);
    test("Single Element Range", {1, 2, 3}, 2, 2);
    test("Start at 1", {1, 2, 3}, 1, 2);
    return 0;
}
