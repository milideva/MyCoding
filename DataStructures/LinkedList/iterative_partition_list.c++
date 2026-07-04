#include <iostream>
#include <vector>

using namespace std;

/*
  LeetCode 86: Partition List

  Problem Description:
  Given the head of a linked list and a value x, partition it such 
  that all nodes less than x come before nodes greater than or 
  equal to x.

  You should preserve the original relative order of the nodes in 
  each of the two partitions.

  Example 1:
  Input: head = [1,4,3,2,5,2], x = 3
  Output: [1,2,2,4,3,5]

  Algorithm: Two Pointer Technique with Dummy Nodes
  1. Create two separate dummy nodes, `lessHead` and `greaterHead`.
  2. Use two pointers, `lessTail` and `greaterTail`, to build two 
     sub-lists.
  3. Traverse the original list:
     - If `curr->val < x`, append to the `lessTail`.
     - Else, append to the `greaterTail`.
  4. Connect `lessTail->next` to `greaterHead.next`.
  5. Set `greaterTail->next = nullptr` to avoid cycles.
  6. Return `lessHead.next`.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We traverse the original list exactly once.
  - Space Complexity: O(1) auxiliary space.
    Reason: We reorganize existing nodes; no new nodes are created 
    except for the two dummy nodes.

  Brute Force comparison:
  - Collect all values in an array, sort them based on the partition 
    rule (keeping relative order), and create new nodes.
  - Time: O(N log N) or O(N), Space: O(N).
  - The dummy-node approach is superior as it works in-place and 
    maintains relative order in O(1) extra space.
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode lessHead(0), greaterHead(0);
        ListNode *lessTail = &lessHead, *greaterTail = &greaterHead;

        while (head) {
            if (head->val < x) {
                lessTail->next = head;
                lessTail = lessTail->next;
            } else {
                greaterTail->next = head;
                greaterTail = greaterTail->next;
            }
            head = head->next;
        }

        lessTail->next = greaterHead.next;
        greaterTail->next = nullptr;

        return lessHead.next;
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

void test(const string& label, const vector<int>& input, int x) {
    cout << "Testing: " << label << " (x: " << x << ")" << endl;
    ListNode* head = createList(input);
    Solution sol;
    ListNode* result = sol.partition(head, x);
    printList(result);
    destroyList(result);
}

int main() {
    test("Example 1", {1, 4, 3, 2, 5, 2}, 3);
    test("Example 2", {2, 1}, 2);
    test("All Less", {1, 2, 3}, 5);
    test("All Greater", {10, 20, 30}, 5);
    return 0;
}
