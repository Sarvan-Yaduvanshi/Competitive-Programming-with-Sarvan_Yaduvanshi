/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           05 — MEMORY LAYOUT: ARRAY vs LINKED LIST COMPARISON              ║
║           From Zero to Grandmaster — Understanding Memory                  ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Array vs Linked List — Memory Layout
 2. Cache Friendliness
 3. When to Use Array vs Linked List
 4. Linked List Class (OOP Encapsulation)

MEMORY LAYOUT COMPARISON:
────────────────────────
  ARRAY (Contiguous Memory):
  ┌─────┬─────┬─────┬─────┬─────┐
  │  10 │  20 │  30 │  40 │  50 │    Elements stored side by side
  ├─────┼─────┼─────┼─────┼─────┤
  │0x100│0x104│0x108│0x10C│0x110│    Fixed stride = sizeof(element)
  └─────┴─────┴─────┴─────┴─────┘
  ✅ Cache-friendly (sequential reads)
  ✅ O(1) random access
  ❌ Fixed size / expensive resize
  ❌ O(n) insert/delete in middle

  LINKED LIST (Scattered Memory):
  ┌─────┬──────┐     ┌─────┬──────┐     ┌─────┬──────┐
  │ 10  │0x2F0 │────▶│ 20  │0x8A4 │────▶│ 30  │ NULL │
  ├─────┼──────┤     ├─────┼──────┤     ├─────┼──────┤
  │0x100│      │     │0x2F0│      │     │0x8A4│      │
  └─────┴──────┘     └─────┴──────┘     └─────┴──────┘
  ✅ Dynamic size
  ✅ O(1) insert/delete at known position
  ❌ Cache-unfriendly (pointer chasing)
  ❌ Extra 8 bytes per node (pointer)
  ❌ O(n) random access

CACHE FRIENDLINESS:
──────────────────
  CPU loads memory in CACHE LINES (typically 64 bytes).

  Array: Loading arr[0] also loads arr[1], arr[2], ... into cache
         → Next accesses are FREE (cache hits!)

  Linked List: Loading node1 does NOT load node2 (different location)
               → Every access is a CACHE MISS (slow!)

  In practice: Array traversal is 5-10x faster than LL traversal
  for sequential access, even though both are O(n).

WHEN TO USE WHAT:
┌─────────────────────────────┬──────────┬──────────────┐
│ Need                        │ Array    │ Linked List  │
├─────────────────────────────┼──────────┼──────────────┤
│ Random access               │ ✅ O(1)  │ ❌ O(n)     │
│ Sequential access           │ ✅ Fast  │ ❌ Slow     │
│ Insert at beginning         │ ❌ O(n)  │ ✅ O(1)     │
│ Insert in middle            │ ❌ O(n)  │ ✅ O(1)*    │
│ Delete from middle          │ ❌ O(n)  │ ✅ O(1)*    │
│ Known size at compile time  │ ✅       │ Not needed  │
│ Unknown/changing size       │ ❌       │ ✅          │
│ LRU/LFU Cache               │ ❌       │ ✅ (DLL)    │
│ Stack/Queue implementation  │ ✅       │ ✅          │
│ Binary search               │ ✅ O(lgn)│ ❌ O(n lgn) │
│ Sorting                     │ ✅       │ Merge sort  │
└─────────────────────────────┴──────────┴──────────────┘
  * O(1) if you already have a pointer to the node
*/

#include <iostream>
#include <chrono>
#include <vector>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// LINKED LIST CLASS (OOP Encapsulation with Templates)
// ═══════════════════════════════════════════════════════════════
/*
  A clean, reusable linked list class.
  Encapsulates all operations behind methods.
  Uses templates for type generality.
*/

template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };

    Node* head;
    int sz;

public:
    LinkedList() : head(nullptr), sz(0) {}

    ~LinkedList() {
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }

    void pushFront(T val) {
        Node* node = new Node(val);
        node->next = head;
        head = node;
        sz++;
    }

    void pushBack(T val) {
        Node* node = new Node(val);
        if (!head) { head = node; sz++; return; }
        Node* curr = head;
        while (curr->next) curr = curr->next;
        curr->next = node;
        sz++;
    }

    bool popFront() {
        if (!head) return false;
        Node* temp = head;
        head = head->next;
        delete temp;
        sz--;
        return true;
    }

    T front() const {
        if (!head) throw runtime_error("Empty list");
        return head->data;
    }

    int size() const { return sz; }
    bool empty() const { return sz == 0; }

    bool contains(T val) const {
        Node* curr = head;
        while (curr) {
            if (curr->data == val) return true;
            curr = curr->next;
        }
        return false;
    }

    void print() const {
        Node* curr = head;
        while (curr) {
            cout << curr->data;
            if (curr->next) cout << " -> ";
            curr = curr->next;
        }
        cout << " -> NULL\n";
    }

    // Iterator support for range-based for loops
    class Iterator {
        Node* ptr;
    public:
        Iterator(Node* p) : ptr(p) {}
        T& operator*() { return ptr->data; }
        Iterator& operator++() { ptr = ptr->next; return *this; }
        bool operator!=(const Iterator& other) { return ptr != other.ptr; }
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};

// ═══════════════════════════════════════════════════════════════
// PERFORMANCE BENCHMARK: Array vs Linked List Traversal
// ═══════════════════════════════════════════════════════════════

void benchmarkTraversal() {
    const int N = 100000;

    // Array traversal
    vector<int> arr(N);
    for (int i = 0; i < N; i++) arr[i] = i;

    auto start = chrono::high_resolution_clock::now();
    long long sum1 = 0;
    for (int i = 0; i < N; i++) sum1 += arr[i];
    auto end = chrono::high_resolution_clock::now();
    auto arrayTime = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Linked list traversal
    struct Node { int data; Node* next; };
    Node* head = nullptr;
    for (int i = N - 1; i >= 0; i--) {
        Node* n = new Node{i, head};
        head = n;
    }

    start = chrono::high_resolution_clock::now();
    long long sum2 = 0;
    Node* curr = head;
    while (curr) { sum2 += curr->data; curr = curr->next; }
    end = chrono::high_resolution_clock::now();
    auto llTime = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "  Array traversal (" << N << " elements): " << arrayTime << " μs\n";
    cout << "  LL traversal    (" << N << " elements): " << llTime << " μs\n";
    cout << "  Ratio (LL/Array): ~" << (llTime > 0 ? llTime / max(1LL, arrayTime) : 0) << "x slower\n";
    cout << "  Both sums: " << sum1 << " == " << sum2 << " ✅\n";

    // Cleanup
    while (head) { Node* t = head; head = head->next; delete t; }
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  MEMORY LAYOUT & LINKED LIST CLASS                     ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // OOP Linked List class
    cout << "═══ LINKED LIST CLASS (Templates) ═══\n";
    LinkedList<int> list;
    list.pushBack(10);
    list.pushBack(20);
    list.pushBack(30);
    list.pushFront(5);
    cout << "List: "; list.print();
    cout << "Size: " << list.size() << "\n";
    cout << "Front: " << list.front() << "\n";
    cout << "Contains 20: " << (list.contains(20) ? "YES" : "NO") << "\n";

    // Range-based for loop
    cout << "Range-based for: ";
    for (auto& val : list) cout << val << " ";
    cout << "\n";

    // String linked list
    cout << "\nLinkedList<string>: ";
    LinkedList<string> strList;
    strList.pushBack("Hello");
    strList.pushBack("World");
    strList.pushBack("!");
    strList.print();

    // Benchmark
    cout << "\n═══ PERFORMANCE BENCHMARK ═══\n";
    benchmarkTraversal();

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "KEY TAKEAWAY:\n";
    cout << "  Arrays are faster for sequential access (cache-friendly)\n";
    cout << "  Linked Lists win for frequent insert/delete at known pos\n";
    cout << "  In CP: Use arrays/vectors unless you NEED LL properties\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

