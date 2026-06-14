#include <cassert>
#include <iostream>
#include <list>
#include <string>

// g++ -std=c++26 stl_list.c++; ./a.out

using namespace std;

void list_init() {
  cout << "--- 1. Initialization ---" << endl;

  // Empty list
  list<int> empty_list;
  assert(empty_list.empty());

  // List with initializer list
  list<int> init_list = {1, 2, 3, 4, 5};
  assert(init_list.size() == 5);

  // Fill constructor (4 copies of value 10)
  list<int> fill_list(4, 10);
  assert(fill_list.size() == 4);
  assert(fill_list.front() == 10);

  // Copy constructor
  list<int> copy_list(init_list);
  assert(copy_list == init_list);

  cout << "Initialization checks passed." << endl;
}

void list_add() {
  cout << "\n--- 2. Adding Elements ---" << endl;

  list<string> fruits;

  // push_back and push_front
  fruits.push_back("Apple");
  fruits.push_front("Banana");
  fruits.push_back("Cherry");
  // List is now: Banana, Apple, Cherry
  assert(fruits.front() == "Banana");
  assert(fruits.back() == "Cherry");

  // insert (insert before the second element)
  auto it = fruits.begin();
  ++it;  // iterator points to "Apple"
  fruits.insert(it, "Orange");
  // List is now: Banana, Orange, Apple, Cherry

  // emplace (in-place construction)
  fruits.emplace_back("Grape");

  assert(fruits.size() == 5);
  cout << "Adding elements checks passed." << endl;
}

void list_remove() {
  cout << "\n--- 3. Removing Elements ---" << endl;

  list<int> numbers = {10, 20, 30, 40, 50, 60, 30};

  // pop_front and pop_back
  numbers.pop_front();  // removes 10
  numbers.pop_back();   // removes 30 at the end
  // List is now: 20, 30, 40, 50, 60
  assert(numbers.front() == 20);
  assert(numbers.back() == 60);

  // erase specific element (erase 30)
  auto it = numbers.begin();
  ++it;  // points to 30
  numbers.erase(it);
  // List is now: 20, 40, 50, 60

  // remove by value (removes all occurrences of a value)
  numbers.push_back(40);  // List: 20, 40, 50, 60, 40
  numbers.remove(40);     // removes both 40s
  // List is now: 20, 50, 60
  assert(numbers.size() == 3);

  // clear
  numbers.clear();
  assert(numbers.empty());
  cout << "Removing elements checks passed." << endl;
}

void list_advanced() {
  cout << "\n--- 4. Advanced Operations ---" << endl;

  list<int> list1 = {5, 9, 1, 3, 3, 7};

  // sort
  list1.sort();
  // List: 1, 3, 3, 5, 7, 9
  assert(list1.front() == 1 && list1.back() == 9);

  // unique (removes consecutive duplicates)
  list1.unique();
  // List: 1, 3, 5, 7, 9
  assert(list1.size() == 5);

  // reverse
  list1.reverse();
  // List: 9, 7, 5, 3, 1
  assert(list1.front() == 9);

  // splice (transfer elements from another list without copying)
  list<int> list2 = {100, 200};
  // Transfer all elements of list2 to the front of list1
  list1.splice(list1.begin(), list2);
  assert(list2.empty());
  assert(list1.front() == 100);

  cout << "Advanced operations checks passed." << endl;
}

// Demonstrates that std::list is doubly-linked (bidirectional).
void list_doubly_linked() {
  cout << "\n--- 5. Proof of Doubly-Linked List (Bidirectional Iteration) ---"
       << endl;

  // Initialize with 10 unsorted elements containing duplicates.
  list<int> journey = {40, 10, 30, 20, 30, 10, 50, 40, 20, 10};

  // Sort the list so it becomes: 10 10 10 20 20 30 30 40 40 50
  journey.sort();

  // 1. Bidirectional Iteration: We can step forward (++) and backward (--).
  // This is impossible in a singly-linked list like std::forward_list.
  auto it = journey.end();
  --it;  // Step back from end() to the tail element (50)
  assert(*it == 50);

  --it;  // Step back again to 40
  assert(*it == 40);

  ++it;  // Step forward to 50
  assert(*it == 50);

  // 2. Reverse Iterators: Walk the entire list backwards using rbegin()/rend().
  cout << "Iterating backwards with rbegin()/rend(): ";
  for (auto rit = journey.rbegin(); rit != journey.rend(); ++rit) {
    cout << *rit << " ";
  }
  cout << endl;

  // 3. O(1) Push and Pop at both ends (push_back and pop_back require tail
  // links).
  journey.push_back(60);
  journey.pop_back();

  cout << "Doubly-linked properties demonstrated successfully." << endl;
}

// A custom class that logs its constructor calls.
struct Gadget {
  int id;
  string name;

  Gadget(int i, string n) : id(i), name(n) {
    cout << "    Gadget Constructed (" << id << ")" << endl;
  }
  Gadget(const Gadget& other) : id(other.id), name(other.name) {
    cout << "    Gadget Copy Constructed (" << id << ")" << endl;
  }
  Gadget(Gadget&& other) noexcept : id(other.id), name(move(other.name)) {
    cout << "    Gadget Move Constructed (" << id << ")" << endl;
  }
};

// Highlights the efficiency gain of emplace vs insert/push.
void list_emplace_comparison() {
  cout << "\n--- 6. Difference between push_back and emplace_back ---" << endl;
  list<Gadget> inventory;

  cout << "  [push_back]: Creates a temporary Gadget, then moves/copies it."
       << endl;
  // Requires constructing a temporary Gadget(1, "Phone") and moving it in.
  inventory.push_back(Gadget(1, "Phone"));

  cout << "\n  [emplace_back]: Constructs Gadget directly in-place inside the "
          "list."
       << endl;
  // No temporary object is created! The constructor args are forwarded.
  inventory.emplace_back(2, "Laptop");

  cout << "Emplace comparison demonstrated successfully." << endl;
}

int main() {
  cout << "=== std::list Demonstration ===" << endl;
  list_init();
  list_add();
  list_remove();
  list_advanced();
  list_doubly_linked();
  list_emplace_comparison();
  return 0;
}
