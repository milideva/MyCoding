// Compilation: g++ -std=c++26 -Wall DataStructures/LinkedList/singly_linked_list_ops.c++ -o /tmp/singly_linked_list_ops_test && /tmp/singly_linked_list_ops_test

#include <print>

using namespace std;

/*
  Problem: Singly Linked List Operations (C++ Class Implementation)

  Problem Description:
  A C++26 implementation of a Singly Linked List class with common 
  functionalities:
  - `insertSorted`: Maintaining a sorted list.
  - `insertAtBeginning`: O(1) head insertion.
  - `middleOfLinkedList`: Finding the middle node in one pass.
  - `reverseLinkedList`: In-place iterative reversal.
  - `oddEvenList` (LeetCode 328): Grouping all odd-indexed nodes together 
    followed by the even-indexed nodes.

  Complexity Analysis:
  - Insertion (Sorted): O(N)
  - Insertion (Beginning): O(1)
  - Search/Middle: O(N)
  - Reversal: O(N)
  - Odd-Even Grouping: O(N) time, O(1) auxiliary space complexity.
  - Space Complexity: O(1) auxiliary for all primary operations.

  Comparison:
  - Using a class encapsulation simplifies state management and 
    memory cleanup (via destructors).
*/

// Definition for singly-linked list from LeetCode.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class SinglyLinkedList {
    ListNode *head;
public:
    SinglyLinkedList (): head(nullptr) {}
    ~SinglyLinkedList () {
        ListNode *curr = head;
        while (curr) {
            ListNode *next = curr->next;
            delete curr;
            curr = next;
        }
    }
    
    void insertAtBeginning (int val) {
        ListNode *newNode = new ListNode(val);
        newNode->next = head;
        head = newNode;
    }
    
    void insertSorted (int val) {
        ListNode *newNode = new ListNode(val);
        if (!head || head->val >= val) {
            newNode->next = head;
            head = newNode;
            return;
        }
        ListNode *curr = head;
        while (curr->next && curr->next->val < val) {
            curr = curr->next;
        }
        newNode->next = curr->next;
        curr->next = newNode;
    }
    
    ListNode* middleOfLinkedList () {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }
    
    void reverseLinkedList () {
        ListNode *curr = head, *prev = nullptr;
        while (curr) {
            ListNode *next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    /*
      LeetCode 328: Odd Even Linked List
      
      Problem Description:
      Given the head of a singly linked list, group all the nodes with odd 
      indices together followed by the nodes with even indices, and return 
      the reordered list.

      The first node is considered odd, and the second node is even, and so on.
      Note that the relative order inside both the even and odd groups should 
      remain as it was in the input.

      You must solve the problem in O(1) extra space complexity and O(n) time 
      complexity.
    */
    void oddEvenList () {
        if (!head || !head->next) return;

        ListNode *odd = head;
        ListNode *even = head->next;
        ListNode *evenHead = even;
        while (even && even->next) {
            odd->next = even->next;
            odd = odd->next;

            even->next = odd->next;
            even = even->next;
        }
        
        odd->next = evenHead;
    }
    
    void display () const {
        ListNode* temp = head;
        while (temp != nullptr) {
            print("{} -> ", temp->val);
            temp = temp->next;
        }
        println("nullptr");
    }
};

void test() {
    println("Testing C++ Singly Linked List");
    SinglyLinkedList list;
    list.insertSorted(3);
    list.insertSorted(1);
    list.insertSorted(4);
    list.insertSorted(2);
    list.display();

    ListNode* mid = list.middleOfLinkedList();
    if (mid) println("Middle: {}", mid->val);

    list.reverseLinkedList();
    print("Reversed: ");
    list.display();

    list.oddEvenList();
    print("After Odd-Even grouping: ");
    list.display();
}

int main() {
    test();
    return 0;
}
