#include <iostream>

/*

24. Swap Nodes in Pairs

Given a linked list, swap every two adjacent nodes and return its head. You must solve the problem without modifying the values in the list's nodes (i.e., only nodes themselves may be changed.)

 
Example 1:


Input: head = [1,2,3,4]
Output: [2,1,4,3]
Example 2:

Input: head = []
Output: []
Example 3:

Input: head = [1]
Output: [1]
 

Constraints:

The number of nodes in the list is in the range [0, 100].
0 <= Node.val <= 100


*/
 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 
// Helper function to create a linked list manually
ListNode* createList(const int* values, int size) {
    ListNode* dummyHead = new ListNode();
    ListNode* current = dummyHead;

    for (int i = 0; i < size; ++i) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }

    return dummyHead->next;
}

// Helper function to delete a linked list
void deleteList(ListNode* head) {
    ListNode* temp;
    while (head) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

// Helper function to print a linked list (for verifying results)
void printList(ListNode* head) {
    while (head) {
        std::cout << head->val << " -> ";
        head = head->next;
    }
    std::cout << "NULL\n";
}

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (!head) return head;
        ListNode *dummy = new ListNode(0, head);
        ListNode* prev = dummy;
        while (head and head->next) {
            ListNode *n1 = head;
            ListNode *n2 = head->next;

            prev->next = n2;
            n1->next = n2->next;
            n2->next = n1;
            
            prev = n1;
            head = n1->next;
        }
        ListNode *newHead = dummy->next;
        delete dummy;
        return newHead;            
    }
};

// Main function with your test cases
int main() {
    Solution solution;

    // Test 1: Input: head = [1,2,3,4]
    int values1[] = {1, 2, 3, 4};
    ListNode *head1 = createList(values1, 4);
    std::cout << "Test 1 - Input: ";  printList(head1);

    ListNode* result1 = solution.swapPairs(head1);
    std::cout << "Test 1 - Output: "; printList(result1);
    deleteList(head1);
    deleteList(result1); 

    // Test 2: Input: head = []
    ListNode* result2 = solution.swapPairs(nullptr); 
    std::cout << "Test 2 - Input: NULL\n"; 
    std::cout << "Test 2 - Output: "; printList(result2); 

    // Test 3: Input: head = [1]
    int values3[] = {1};
    ListNode* head3 = createList(values3, 1);
    std::cout << "Test 3 - Input: "; printList(head3);

    ListNode* result3 = solution.swapPairs(head3); 
    std::cout << "Test 3 - Output: "; printList(result3); 
    deleteList(head3);
    deleteList(result3); 

    return 0;
}
