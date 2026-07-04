#include <iostream>
#include <vector>

using namespace std;

/*
  LeetCode 24: Swap Nodes in Pairs

  Problem Description:
  Given a linked list, swap every two adjacent nodes and return its 
  head. You must solve the problem without modifying the values in 
  the list's nodes (i.e., only nodes themselves may be changed.)

  Example 1:
  Input: head = [1,2,3,4]
  Output: [2,1,4,3]

  Algorithm 1: Iterative with Dummy Node
  1. Use a `dummy` node pointing to `head`.
  2. Maintain a `prev` pointer (initially `dummy`).
  3. While `head` and `head->next` exist:
     - Identify `n1 = head` and `n2 = head->next`.
     - Re-link: `prev->next = n2`, `n1->next = n2->next`, `n2->next = n1`.
     - Move `prev` to `n1` and `head` to `n1->next`.

  Algorithm 2: Recursive
  1. Base case: If `head` or `head->next` is null, return `head`.
  2. Let `nextPairHead = head->next->next`.
  3. Let `newHead = head->next`.
  4. `newHead->next = head`.
  5. `head->next = swapPairsRecursive(nextPairHead)`.
  6. Return `newHead`.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We visit every node once.
  - Space Complexity:
    - Iterative: O(1).
    - Recursive: O(N) for the recursion stack.

  Brute Force comparison:
  - Collect values in an array, swap values, and update nodes.
  - Time: O(N), Space: O(N).
  - The in-place pointer manipulation (Algorithm 1) is the most efficient.
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *n) : val(x), next(n) {}
};

class Solution {
public:
    ListNode* swapPairsIterative(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode dummy(0, head);
        ListNode* prev = &dummy;
        
        while (head && head->next) {
            ListNode* n1 = head;
            ListNode* n2 = head->next;

            prev->next = n2;
            n1->next = n2->next;
            n2->next = n1;
            
            prev = n1;
            head = n1->next;
        }
        return dummy.next;
    }

    ListNode* swapPairsRecursive(ListNode* head) {
        if (!head || !head->next) return head;

        ListNode* n1 = head;
        ListNode* n2 = head->next;

        n1->next = swapPairsRecursive(n2->next);
        n2->next = n1;

        return n2;
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

void test(const string& label, const vector<int>& input) {
    cout << "Testing: " << label << endl;
    Solution sol;
    
    ListNode* head1 = createList(input);
    ListNode* res1 = sol.swapPairsIterative(head1);
    cout << "  Iterative: "; printList(res1);
    destroyList(res1);

    ListNode* head2 = createList(input);
    ListNode* res2 = sol.swapPairsRecursive(head2);
    cout << "  Recursive: "; printList(res2);
    destroyList(res2);
}

int main() {
    test("Example 1", {1, 2, 3, 4});
    test("Empty List", {});
    test("Single Node", {1});
    test("Odd Number of Nodes", {1, 2, 3, 4, 5});
    return 0;
}
