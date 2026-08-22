// Compilation: g++ -std=c++26 -Wall DataStructures/LinkedList/singly_linked_list_ops.c++ -o /tmp/singly_linked_list_ops_test && /tmp/singly_linked_list_ops_test

#include <print>
#include <vector>

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
  - `isPalindrome` (LeetCode 234): Checking if a linked list is a palindrome 
    using both iterative (vector) and recursive approaches.

  Complexity Analysis:
  - Insertion (Sorted): O(N)
  - Insertion (Beginning): O(1)
  - Search/Middle: O(N)
  - Reversal: O(N)
  - Odd-Even Grouping: O(N) time, O(1) auxiliary space complexity.
  - Palindrome (Iterative): O(N) time, O(N) space.
  - Palindrome (Recursive): O(N) time, O(N) stack space.
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
        clear();
    }

    void clear() {
        ListNode *curr = head;
        while (curr) {
            ListNode *next = curr->next;
            delete curr;
            curr = next;
        }
        head = nullptr;
    }

    ListNode* getHead() const { return head; }
    
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

    /*
      LeetCode 234: Palindrome Linked List (Iterative Approach)
      Time Complexity: O(N)
      Space Complexity: O(N) to store values in a vector.
    */
    bool isPalindromeIterative(ListNode* head) {
        vector <int> vec;
        ListNode* node = head;
        while (node) {
            vec.push_back(node->val);
            node = node->next;
        }
        
        int sz = vec.size();
        int l = 0, r = sz -1;
        while (l < r) {
            if (vec[l++] != vec[r--]) {
                return false;
            }
        }
        return true;
    }

    bool isPalindromeIterative() {
        return isPalindromeIterative(head);
    }

private:
    /*
      Helper for recursive palindrome check.

      Why recursion is used here:
      - By using the system call stack, we can traverse to the end of the list first,
        and then check elements from back-to-front as the call stack unwinds, while 
        simultaneously advancing a front pointer forward.
      - Advantage: This avoids allocating explicit auxiliary space on the heap (like 
        creating a vector/array), which is highly beneficial if we want to avoid 
        additional dynamic memory allocations or memory fragmentation when dealing with 
        millions of entries.
      - Disadvantage: While it saves heap memory, it still uses O(N) call stack space, 
        which can lead to stack overflow on very large lists (millions of elements) 
        unless the environment supports optimized call stacks or tail call optimization.
    */
    bool checkPalindrome(ListNode*& frontPointer, ListNode* currentNode) {
        if (currentNode != nullptr) {
            // Recurse to the end of the list
            if (!checkPalindrome(frontPointer, currentNode->next)) {
                return false;
            }
            
            // Compare values as the call stack unwinds
            if (frontPointer->val != currentNode->val) {
                return false;
            }
            
            // Move front pointer one step forward
            frontPointer = frontPointer->next;
        }
        return true;
    }

public:
    /*
      LeetCode 234: Palindrome Linked List (Recursive Approach)
      Time Complexity: O(N)
      Space Complexity: O(N) stack space.
    */
    bool isPalindrome(ListNode* head) {
        ListNode* frontPointer = head;
        return checkPalindrome(frontPointer, head);
    }

    bool isPalindrome() {
        return isPalindrome(head);
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

    println("\n--- Testing Palindrome Functions ---");
    SinglyLinkedList palList;
    palList.insertAtBeginning(1);
    palList.insertAtBeginning(2);
    palList.insertAtBeginning(3);
    palList.insertAtBeginning(2);
    palList.insertAtBeginning(1);
    print("Palindrome List: ");
    palList.display();
    println("Is Palindrome (Iterative): {}", palList.isPalindromeIterative());
    println("Is Palindrome (Recursive): {}", palList.isPalindrome());

    SinglyLinkedList nonPalList;
    nonPalList.insertAtBeginning(1);
    nonPalList.insertAtBeginning(2);
    nonPalList.insertAtBeginning(3);
    nonPalList.insertAtBeginning(4);
    print("Non-Palindrome List: ");
    nonPalList.display();
    println("Is Palindrome (Iterative): {}", nonPalList.isPalindromeIterative());
    println("Is Palindrome (Recursive): {}", nonPalList.isPalindrome());
}

int main() {
    test();
    return 0;
}
