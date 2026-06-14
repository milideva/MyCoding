#include <cassert>
#include <iostream>
#include <queue>
#include <list>
#include <string>
#include <vector>

// g++ -std=c++26 stl_queue.c++; ./a.out

using namespace std;

void queue_init() {
  cout << "--- 1. Initialization ---" << endl;

  // Empty queue (default container is deque)
  queue<int> empty_q;
  assert(empty_q.empty());

  // Initializing with elements is not as direct as list/vector
  // because queue is an adapter. We can initialize the underlying container.
  deque<int> d = {1, 2, 3, 4, 5};
  queue<int> init_q(d);
  assert(init_q.size() == 5);
  assert(init_q.front() == 1);

  // Queue using a different underlying container (list)
  list<int> l = {10, 20, 30};
  queue<int, list<int>> list_q(l);
  assert(list_q.size() == 3);
  assert(list_q.front() == 10);

  cout << "Initialization checks passed." << endl;
}

void queue_operations() {
  cout << "\n--- 2. Basic Operations (FIFO) ---" << endl;

  queue<string> q;

  // push
  q.push("First");
  q.push("Second");
  q.push("Third");
  // Queue: [First, Second, Third] -> (front)

  assert(q.size() == 3);
  assert(q.front() == "First");
  assert(q.back() == "Third");

  // pop (removes the front element)
  q.pop();
  // Queue: [Second, Third]
  assert(q.front() == "Second");
  assert(q.size() == 2);

  // front() and back() provide references
  q.front() = "New Second";
  assert(q.front() == "New Second");

  cout << "Basic operations checks passed." << endl;
}

struct Item {
  int id;
  string name;

  Item(int i, string n) : id(i), name(n) {
    cout << "    Item Constructed (" << id << ")" << endl;
  }
  Item(const Item& other) : id(other.id), name(other.name) {
    cout << "    Item Copy Constructed (" << id << ")" << endl;
  }
  Item(Item&& other) noexcept : id(other.id), name(move(other.name)) {
    cout << "    Item Move Constructed (" << id << ")" << endl;
  }
};

void queue_emplace_comparison() {
  cout << "\n--- 3. push vs emplace ---" << endl;
  queue<Item> q;

  cout << "  [push]: Creates a temporary Item, then moves/copies it into the underlying container." << endl;
  q.push(Item(1, "Old"));

  cout << "\n  [emplace]: Constructs Item directly in-place inside the underlying container." << endl;
  q.emplace(2, "New");

  assert(q.size() == 2);
  cout << "Emplace comparison demonstrated." << endl;
}

void queue_swap() {
  cout << "\n--- 4. Swap Operation ---" << endl;
  queue<int> q1, q2;
  q1.push(1);
  q1.push(2);
  q2.push(10);

  q1.swap(q2);

  assert(q1.size() == 1);
  assert(q1.front() == 10);
  assert(q2.size() == 2);
  assert(q2.front() == 1);

  cout << "Swap operation checks passed." << endl;
}

int main() {
  cout << "=== std::queue Demonstration ===" << endl;
  queue_init();
  queue_operations();
  queue_emplace_comparison();
  queue_swap();
  return 0;
}
