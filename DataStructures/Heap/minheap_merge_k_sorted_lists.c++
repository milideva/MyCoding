#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/*
  LeetCode 23: Merge k Sorted Lists

  Problem Description:
  You are given an array of k linked-lists lists, each linked-list is 
  sorted in ascending order. Merge all the linked-lists into one 
  sorted linked-list and return it.

  Algorithm: Min-Heap (K-Way Merge)
  1. Create a Min-Heap and push the head of each non-empty list into it.
  2. While the heap is not empty:
     - Extract the smallest node (top of the heap).
     - Append this node to the merged list.
     - If the extracted node has a next node, push the next node into 
       the heap.
  3. The heap ensures that we always pick the smallest available element 
     across all K lists.

  Complexity Analysis:
  - Time Complexity: O(N log K)
    Reason: N is the total number of nodes across all lists. Each of the 
    N nodes is pushed and popped from the heap exactly once, and heap 
    operations take O(log K).
  - Space Complexity: O(K)
    Reason: The heap stores at most one node from each of the K lists.

  Alternative Approaches:
  - Merge Lists One by One:
    - Logic: Merge list 1 and 2, then merge result with list 3, etc.
    - Time: O(K * N).
  - Divide and Conquer:
    - Logic: Merge pairs of lists recursively.
    - Time: O(N log K), Space: O(log K) for recursion.
    - Comparison: Divide and Conquer is equally efficient in time and 
      doesn't require a heap data structure.

  Brute Force comparison:
  - Collect all node values into an array, sort the array, and create 
    a new linked list.
  - Time: O(N log N).
  - Comparison: The Min-Heap approach is better as it utilizes the fact 
    that individual lists are already sorted.
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto compare = [](ListNode* a, ListNode* b) { return a->val > b->val; };
        priority_queue<ListNode*, vector<ListNode*>, decltype(compare)> minHeap(compare);

        for (auto node : lists) {
            if (node) minHeap.push(node);
        }

        ListNode dummy(0);
        ListNode *curr = &dummy;

        while (!minHeap.empty()) {
            ListNode *node = minHeap.top();
            minHeap.pop();
            
            if (node->next) {
                minHeap.push(node->next);
            }
            
            curr->next = node;
            curr = node;
        }
        return dummy.next;
    }
};

//=========================================================================
// Test Code
//=========================================================================

ListNode* createList(const vector<int>& values) {
    ListNode dummy(0);
    ListNode* curr = &dummy;
    for (int v : values) {
        curr->next = new ListNode(v);
        curr = curr->next;
    }
    return dummy.next;
}

void printList(ListNode* list) {
    while (list) {
        cout << list->val << (list->next ? " -> " : "");
        list = list->next;
    }
    cout << endl;
}

void destroyList(ListNode* list) {
    while (list) {
        ListNode* temp = list;
        list = list->next;
        delete temp;
    }
}

int main() {
    cout << "Testing: Merge K Sorted Lists" << endl;
    vector<ListNode*> lists;
    lists.push_back(createList({1, 4, 5}));
    lists.push_back(createList({1, 3, 4}));
    lists.push_back(createList({2, 6}));

    cout << "Input Lists:" << endl;
    for (auto l : lists) printList(l);

    Solution sol;
    ListNode* merged = sol.mergeKLists(lists);
    
    cout << "Merged List:" << endl;
    printList(merged);

    destroyList(merged);
    return 0;
}
