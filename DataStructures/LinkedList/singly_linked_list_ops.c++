#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

/*
  Problem: Singly Linked List Operations (C++ Class Implementation)

  Problem Description:
  A C++ implementation of a Singly Linked List class with common 
  functionalities:
  - `insertSorted`: Maintaining a sorted list.
  - `insertAtBeginning`: O(1) head insertion.
  - `middleOfLinkedList`: Finding the middle node in one pass.
  - `reverseLinkedList`: In-place iterative reversal.
  - `oddEvenList` (LeetCode 328): Grouping all odd-indexed nodes together 
    followed by the even-indexed nodes.
  - `setRandom`: Randomly assigning 'random' pointers for practice 
    with complex structures.

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

struct Node {
    int val;
    Node *next;
    Node *random;
    Node (int v) : val(v), next(nullptr), random(nullptr) {}
};

class SinglyLinkedList {
    Node *head;
public:
    SinglyLinkedList (): head(nullptr) {}
    ~SinglyLinkedList () {
        Node *curr = head;
        while (curr) {
            Node *next = curr->next;
            delete curr;
            curr = next;
        }
    }
    
    void insertAtBeginning (int val) {
        Node *newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }
    
    void insertSorted (int val) {
        Node *newNode = new Node(val);
        if (!head || head->val >= val) {
            newNode->next = head;
            head = newNode;
            return;
        }
        Node *curr = head;
        while (curr->next && curr->next->val < val) {
            curr = curr->next;
        }
        newNode->next = curr->next;
        curr->next = newNode;
    }
    
    Node* middleOfLinkedList () {
        Node *slow = head, *fast = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }
    
    void reverseLinkedList () {
        Node *curr = head, *prev = nullptr;
        while (curr) {
            Node *next = curr->next;
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

        Node *odd = head;
        Node *even = head->next;
        Node *evenHead = even;
        while (even && even->next) {
            odd->next = even->next;
            odd = odd->next;

            even->next = odd->next;
            even = even->next;
        }
        
        odd->next = evenHead;
    }
    
    void display () const {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->val;
            if (temp->random) cout << " R{" << temp->random->val << "}";   
            cout << " -> ";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }

    void setRandom () {
        if (!head) return;
        vector<Node*> nodes;
        Node* curr = head;
        while (curr) {
            nodes.push_back(curr);
            curr = curr->next;
        }
        random_device rd;
        mt19937 g(rd());
        shuffle(nodes.begin(), nodes.end(), g);
        curr = head;
        for (size_t i = 0; i < nodes.size(); ++i) {
            curr->random = nodes[i];
            curr = curr->next;
        }
    }
};

void test() {
    cout << "Testing C++ Singly Linked List" << endl;
    SinglyLinkedList list;
    list.insertSorted(3);
    list.insertSorted(1);
    list.insertSorted(4);
    list.insertSorted(2);
    list.display();

    Node* mid = list.middleOfLinkedList();
    if (mid) cout << "Middle: " << mid->val << endl;

    list.reverseLinkedList();
    cout << "Reversed: ";
    list.display();

    list.oddEvenList();
    cout << "After Odd-Even grouping: ";
    list.display();
}

int main() {
    test();
    return 0;
}
