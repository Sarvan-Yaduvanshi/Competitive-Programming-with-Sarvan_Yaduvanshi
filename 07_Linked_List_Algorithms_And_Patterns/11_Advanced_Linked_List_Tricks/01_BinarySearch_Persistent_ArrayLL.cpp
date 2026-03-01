/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — ADVANCED LINKED LIST TRICKS FOR CP                          ║
║           Binary Search on LL, Persistent LL, Skip List, Memory Tricks     ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Binary Search on Linked List (Concept)
 2. Persistent Linked List (Immutable versions)
 3. Linked List as Adjacency List for Graphs
 4. Euler Tour Using Linked Structure
 5. Memory-Constrained Problems
 6. Pointer Compression Tricks (Array-based LL for CP)

BINARY SEARCH ON LINKED LIST:
────────────────────────────
  Regular binary search needs O(1) random access → doesn't work on LL!
  But we CAN do it with slow/fast pointer to find middle.

  Complexity: O(n log n) — worse than array binary search O(log n)
  Each "find middle" takes O(n/2), done log(n) times.

  When useful: When data is already in a sorted linked list and you
  can't convert to array (memory constraints).

DRY RUN — Binary Search on sorted LL [1→3→5→7→9→11→13]:
────────────────────────────────────────────────────────
  Target = 7

  Round 1: Find middle of [1→3→5→7→9→11→13] → mid = 7
           7 == 7 → FOUND! ✅

  Target = 3
  Round 1: mid = 7, 3 < 7 → search left half [1→3→5]
  Round 2: mid = 3, 3 == 3 → FOUND! ✅

PERSISTENT LINKED LIST:
──────────────────────
  Creates new versions of the list without modifying old versions.
  Each "modification" returns a new head while keeping the old list intact.
  Used in functional programming and version control systems.

  Version 0: 1 → 2 → 3
  insert(0, 4):
  Version 1: 4 → 1 → 2 → 3  (Version 0 still exists!)

  Implementation: Don't modify nodes, create new paths.

ARRAY-BASED LINKED LIST (CP TRICK):
──────────────────────────────────
  Instead of pointers, use arrays with indices.
  Much faster due to cache-friendliness and no malloc overhead.

  val[]:  [_, 10, 20, 30, 40, 50]
  nxt[]:  [_, 2,  3,  4,  5,  -1]
  head = 1

  Equivalent to: 10 → 20 → 30 → 40 → 50 → NULL

  Why faster?
  • No memory allocation per node
  • Cache-friendly (arrays are contiguous)
  • No pointer overhead
  • Pre-allocate once, use indices
*/

#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

Node* buildSortedList(int arr[], int n) {
    if (n == 0) return nullptr;
    Node* head = new Node(arr[0]);
    Node* tail = head;
    for (int i = 1; i < n; i++) { tail->next = new Node(arr[i]); tail = tail->next; }
    return head;
}

void freeList(Node* head) { while (head) { Node* t = head; head = head->next; delete t; } }

// ═══════════════════════════════════════════════════════════════
// 1. BINARY SEARCH ON SORTED LINKED LIST
// ═══════════════════════════════════════════════════════════════

Node* findMiddle(Node* start, Node* end) {
    if (!start) return nullptr;
    Node* slow = start;
    Node* fast = start;
    while (fast != end && fast->next != end) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

bool binarySearchLL(Node* head, int target) {
    Node* start = head;
    Node* end = nullptr;

    while (start != end) {
        Node* mid = findMiddle(start, end);
        if (!mid) return false;

        if (mid->data == target) return true;
        else if (mid->data < target) start = mid->next;
        else end = mid;
    }
    return false;
}

// ═══════════════════════════════════════════════════════════════
// 2. PERSISTENT LINKED LIST (Immutable Insert)
// ═══════════════════════════════════════════════════════════════

struct PNode {
    int data;
    PNode* next;
    PNode(int val, PNode* n = nullptr) : data(val), next(n) {}
};

// Insert at head — returns NEW head, doesn't modify original
PNode* persistentInsertHead(PNode* head, int val) {
    return new PNode(val, head);
    // Original list is UNCHANGED!
}

// Insert at position — path copying
PNode* persistentInsertAt(PNode* head, int val, int pos) {
    if (pos == 0) return new PNode(val, head);

    // Copy nodes up to position
    PNode* newHead = new PNode(head->data);
    PNode* newCurr = newHead;
    PNode* oldCurr = head->next;

    for (int i = 1; i < pos && oldCurr; i++) {
        newCurr->next = new PNode(oldCurr->data);
        newCurr = newCurr->next;
        oldCurr = oldCurr->next;
    }

    // Insert new node
    PNode* newNode = new PNode(val);
    newCurr->next = newNode;
    newNode->next = oldCurr;  // Share the rest of the old list!

    return newHead;
}

void printPList(PNode* head, string label) {
    cout << label << ": ";
    while (head) { cout << head->data; if (head->next) cout << " -> "; head = head->next; }
    cout << " -> NULL\n";
}

// ═══════════════════════════════════════════════════════════════
// 3. ARRAY-BASED LINKED LIST (CP Speed Trick)
// ═══════════════════════════════════════════════════════════════

class ArrayLinkedList {
    static const int MAXN = 100005;
    int val[MAXN], nxt[MAXN];
    int head, sz, freeIdx;

public:
    ArrayLinkedList() : head(-1), sz(0), freeIdx(0) {
        for (int i = 0; i < MAXN - 1; i++) nxt[i] = i + 1;
        nxt[MAXN - 1] = -1;
    }

    int allocate() {
        int idx = freeIdx;
        freeIdx = nxt[freeIdx];
        return idx;
    }

    void deallocate(int idx) {
        nxt[idx] = freeIdx;
        freeIdx = idx;
    }

    void insertHead(int v) {
        int idx = allocate();
        val[idx] = v;
        nxt[idx] = head;
        head = idx;
        sz++;
    }

    int deleteHead() {
        if (head == -1) return -1;
        int v = val[head];
        int old = head;
        head = nxt[head];
        deallocate(old);
        sz--;
        return v;
    }

    void print() {
        cout << "ArrayLL: ";
        int curr = head;
        while (curr != -1) {
            cout << val[curr];
            if (nxt[curr] != -1) cout << " -> ";
            curr = nxt[curr];
        }
        cout << " -> NULL\n";
    }

    int size() { return sz; }
};

// ═══════════════════════════════════════════════════════════════
// 4. MEMORY POOL TRICK (Arena Allocation for CP)
// ═══════════════════════════════════════════════════════════════
/*
  Pre-allocate a pool of nodes. Use pool index instead of new/delete.
  Eliminates malloc overhead — critical for tight TL problems.

  const int POOL_SIZE = 1e6;
  Node pool[POOL_SIZE];
  int poolIdx = 0;

  Node* getNode(int val) {
      pool[poolIdx].data = val;
      pool[poolIdx].next = nullptr;
      return &pool[poolIdx++];
  }

  // No need to free! Pool is on stack / global.
  // Reset: poolIdx = 0; for new test case
*/

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  ADVANCED LINKED LIST TRICKS FOR CP                    ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Binary Search on LL
    cout << "═══ BINARY SEARCH ON SORTED LL ═══\n";
    int arr[] = {1, 3, 5, 7, 9, 11, 13};
    Node* head = buildSortedList(arr, 7);
    cout << "List: 1 -> 3 -> 5 -> 7 -> 9 -> 11 -> 13\n";
    for (int t : {7, 3, 13, 6}) {
        cout << "Search " << t << ": " << (binarySearchLL(head, t) ? "FOUND" : "NOT FOUND") << "\n";
    }
    freeList(head);

    // Persistent LL
    cout << "\n═══ PERSISTENT LINKED LIST ═══\n";
    PNode* v0 = new PNode(1, new PNode(2, new PNode(3)));
    printPList(v0, "Version 0");

    PNode* v1 = persistentInsertHead(v0, 0);
    printPList(v1, "Version 1 (insert 0 at head)");
    printPList(v0, "Version 0 (unchanged!)");

    PNode* v2 = persistentInsertAt(v0, 99, 1);
    printPList(v2, "Version 2 (insert 99 at pos 1)");
    printPList(v0, "Version 0 (still unchanged!)");

    // Array-based LL
    cout << "\n═══ ARRAY-BASED LINKED LIST (CP SPEED TRICK) ═══\n";
    ArrayLinkedList all;
    all.insertHead(50);
    all.insertHead(40);
    all.insertHead(30);
    all.insertHead(20);
    all.insertHead(10);
    all.print();
    cout << "Delete head: " << all.deleteHead() << "\n";
    all.print();

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "CP SPEED TIPS:\n";
    cout << "  1. Use array-based LL for tight TL problems\n";
    cout << "  2. Pre-allocate node pool (arena allocation)\n";
    cout << "  3. Avoid new/delete in CP — use global arrays\n";
    cout << "  4. Reset pool index between test cases\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

