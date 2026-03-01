/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — SINGLY LINKED LIST: NODE STRUCTURE & FUNDAMENTALS             ║
║           From Zero to Grandmaster — Complete Foundation                     ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. What is a Linked List?
 2. Node Structure (Singly Linked List)
 3. Creating Nodes Manually
 4. Building a Linked List
 5. Traversal & Printing
 6. Memory Layout Visualization
 7. Head Pointer Concept
 8. Null Pointer Handling

WHAT IS A LINKED LIST?
──────────────────────
A Linked List is a linear data structure where elements (nodes) are stored
in non-contiguous memory locations. Each node contains:
  • Data — The actual value
  • Pointer — Address of the next node

Unlike arrays:
  ✅ Dynamic size (no pre-allocation needed)
  ✅ O(1) insert/delete at known position
  ❌ No random access (must traverse from head)
  ❌ Extra memory for pointers

NODE STRUCTURE:
──────────────
  ┌───────┬──────────┐
  │ data  │  next ───┼──▶ (points to next node or NULL)
  └───────┴──────────┘

  struct Node {
      int data;
      Node* next;
  };

MEMORY LAYOUT:
─────────────
  ARRAY:   [10][20][30][40][50]   ← Contiguous memory
            0x100 0x104 0x108...

  LINKED LIST:
  ┌────┬──────┐     ┌────┬──────┐     ┌────┬──────┐
  │ 10 │ 0x2F0│────▶│ 20 │ 0x8A4│────▶│ 30 │ NULL │
  └────┴──────┘     └────┴──────┘     └────┴──────┘
   @0x100            @0x2F0            @0x8A4
   (scattered in memory — not contiguous!)

HEAD POINTER:
────────────
  The head pointer stores the address of the FIRST node.
  Without head, we lose access to the entire list!

  head ──▶ [10|next] ──▶ [20|next] ──▶ [30|NULL]

  If head = NULL → list is empty

NULL POINTER:
────────────
  The last node's next pointer is NULL (nullptr in C++).
  This signals the END of the list.
  Always check for NULL before dereferencing a pointer!

  DANGER: node->next->data  ← CRASH if node->next is NULL!
  SAFE:   if (node->next != nullptr) { ... }
*/

#include <iostream>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: NODE STRUCTURE
// ═══════════════════════════════════════════════════════════════
/*
  The fundamental building block of a singly linked list.

  ┌───────────────────┐
  │    Node           │
  │  ┌──────┬───────┐ │
  │  │ data │ next  │ │
  │  │ int  │ Node* │ │
  │  └──────┴───────┘ │
  └───────────────────┘
*/

struct Node {
    int data;       // Stores the actual value
    Node* next;     // Pointer to the next node

    // Constructor for easy node creation
    Node(int val) : data(val), next(nullptr) {}

    // Constructor with next pointer
    Node(int val, Node* nxt) : data(val), next(nxt) {}
};

// ═══════════════════════════════════════════════════════════════
// SECTION 2: CREATING NODES MANUALLY
// ═══════════════════════════════════════════════════════════════
/*
  DRY RUN — Creating 3 nodes and linking them:

  Step 1: Node* a = new Node(10);
          a ──▶ [10 | NULL]

  Step 2: Node* b = new Node(20);
          a ──▶ [10 | NULL]    b ──▶ [20 | NULL]

  Step 3: Node* c = new Node(30);
          a ──▶ [10 | NULL]    b ──▶ [20 | NULL]    c ──▶ [30 | NULL]

  Step 4: a->next = b;
          a ──▶ [10 | ──]──▶ [20 | NULL]    c ──▶ [30 | NULL]

  Step 5: b->next = c;
          a ──▶ [10 | ──]──▶ [20 | ──]──▶ [30 | NULL]

  Final:  head = a
          head ──▶ [10] ──▶ [20] ──▶ [30] ──▶ NULL
*/

void demonstrateNodeCreation() {
    cout << "═══ SECTION 2: CREATING NODES MANUALLY ═══\n\n";

    // Method 1: Using new keyword (heap allocation)
    Node* a = new Node(10);
    Node* b = new Node(20);
    Node* c = new Node(30);

    // Link them together
    a->next = b;
    b->next = c;
    // c->next is already NULL (from constructor)

    // head points to the first node
    Node* head = a;

    // Traverse and print
    cout << "Linked List: ";
    Node* curr = head;
    while (curr != nullptr) {
        cout << curr->data;
        if (curr->next != nullptr) cout << " -> ";
        curr = curr->next;
    }
    cout << " -> NULL\n";

    // Show memory addresses
    cout << "\nMemory Addresses:\n";
    curr = head;
    while (curr != nullptr) {
        cout << "  Node(" << curr->data << ") at address: " << curr
             << ", next points to: " << curr->next << "\n";
        curr = curr->next;
    }

    // Cleanup
    delete a;
    delete b;
    delete c;

    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: BUILDING A LIST FROM ARRAY
// ═══════════════════════════════════════════════════════════════
/*
  DRY RUN — Building list from array [5, 10, 15, 20]:

  Step 1: head = new Node(5)
          head ──▶ [5 | NULL]
          tail = head

  Step 2: tail->next = new Node(10), tail = tail->next
          head ──▶ [5 | ──]──▶ [10 | NULL]
                                  ↑ tail

  Step 3: tail->next = new Node(15), tail = tail->next
          head ──▶ [5 | ──]──▶ [10 | ──]──▶ [15 | NULL]
                                               ↑ tail

  Step 4: tail->next = new Node(20), tail = tail->next
          head ──▶ [5 | ──]──▶ [10 | ──]──▶ [15 | ──]──▶ [20 | NULL]
                                                            ↑ tail

  Time: O(n)  Space: O(n) for n nodes
*/

Node* buildFromArray(int arr[], int n) {
    if (n == 0) return nullptr;

    Node* head = new Node(arr[0]);
    Node* tail = head;

    for (int i = 1; i < n; i++) {
        tail->next = new Node(arr[i]);
        tail = tail->next;
    }
    return head;
}

void printList(Node* head) {
    Node* curr = head;
    while (curr != nullptr) {
        cout << curr->data;
        if (curr->next != nullptr) cout << " -> ";
        curr = curr->next;
    }
    cout << " -> NULL\n";
}

void deleteList(Node* head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void demonstrateBuildFromArray() {
    cout << "═══ SECTION 3: BUILD LIST FROM ARRAY ═══\n\n";

    int arr[] = {5, 10, 15, 20, 25};
    int n = 5;

    Node* head = buildFromArray(arr, n);

    cout << "Array:       [5, 10, 15, 20, 25]\n";
    cout << "Linked List: ";
    printList(head);

    deleteList(head);
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: HEAD POINTER & NULL HANDLING
// ═══════════════════════════════════════════════════════════════
/*
  HEAD POINTER RULES:
  ──────────────────
  1. head == nullptr → Empty list
  2. head->next == nullptr → Only one node
  3. Always update head when inserting/deleting at front
  4. Never dereference a NULL pointer!

  COMMON MISTAKES:
  ┌─────────────────────────────────────────────────┐
  │ ❌ head->data           (head might be NULL!)   │
  │ ✅ if (head) head->data                         │
  │                                                 │
  │ ❌ curr->next->data     (next might be NULL!)   │
  │ ✅ if (curr->next) curr->next->data             │
  │                                                 │
  │ ❌ Forgetting to set head = newNode             │
  │ ✅ Always return/update head after modification │
  └─────────────────────────────────────────────────┘
*/

void demonstrateNullHandling() {
    cout << "═══ SECTION 4: HEAD POINTER & NULL HANDLING ═══\n\n";

    // Case 1: Empty list
    Node* head = nullptr;
    cout << "Empty list check: head is " << (head == nullptr ? "NULL" : "NOT NULL") << "\n";

    // Safe access pattern
    if (head != nullptr) {
        cout << "Head data: " << head->data << "\n";
    } else {
        cout << "Cannot access data — list is empty!\n";
    }

    // Case 2: Single node
    head = new Node(42);
    cout << "\nSingle node: ";
    printList(head);
    cout << "head->next is " << (head->next == nullptr ? "NULL" : "NOT NULL") << "\n";
    cout << "This is the only node in the list.\n";

    // Case 3: Check before accessing next's data
    if (head->next != nullptr) {
        cout << "Second node data: " << head->next->data << "\n";
    } else {
        cout << "No second node exists!\n";
    }

    delete head;
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: POINTER BASICS REVISION
// ═══════════════════════════════════════════════════════════════
/*
  POINTER REFRESHER:
  ─────────────────
  int x = 10;
  int* p = &x;    // p stores ADDRESS of x
  cout << *p;     // Dereference: prints VALUE at that address (10)
  cout << p;      // Prints the ADDRESS itself (e.g., 0x7fff...)

  Node* head;     // head stores ADDRESS of a Node
  head->data;     // Same as (*head).data — access data through pointer
  head->next;     // Same as (*head).next — access next through pointer

  new Node(10);   // Allocates memory on HEAP, returns address
  delete ptr;     // Frees HEAP memory (prevents memory leaks!)

  STACK vs HEAP:
  ┌──────────────────────────────────────────┐
  │ Stack:  Node n(10);    // Auto cleanup   │
  │ Heap:   Node* p = new Node(10); // Manual│
  │         delete p;       // Must free!    │
  └──────────────────────────────────────────┘

  For linked lists, we ALWAYS use HEAP allocation (new/delete)
  because nodes must persist beyond function scope.
*/

void demonstratePointers() {
    cout << "═══ SECTION 5: POINTER BASICS REVISION ═══\n\n";

    // Basic pointer
    int x = 42;
    int* p = &x;
    cout << "Value of x:      " << x << "\n";
    cout << "Address of x:    " << &x << "\n";
    cout << "Pointer p:       " << p << " (same as &x)\n";
    cout << "Dereference *p:  " << *p << " (same as x)\n\n";

    // Node pointer
    Node* node = new Node(100);
    cout << "Node address:    " << node << "\n";
    cout << "node->data:      " << node->data << "\n";
    cout << "node->next:      " << node->next << " (NULL)\n";
    cout << "(*node).data:    " << (*node).data << " (same as node->data)\n";

    delete node;
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 6: DYNAMIC MEMORY ALLOCATION
// ═══════════════════════════════════════════════════════════════
/*
  WHY DYNAMIC ALLOCATION?
  ──────────────────────
  • Arrays need size at compile time → Linked list grows dynamically
  • Each node allocated separately on heap
  • Nodes can be anywhere in memory (non-contiguous)

  new    → Allocates memory on heap, returns pointer
  delete → Frees memory (MUST do this to avoid memory leaks!)

  MEMORY LEAK EXAMPLE:
  ┌──────────────────────────────────────────┐
  │ Node* a = new Node(10);                  │
  │ a = new Node(20);  // ❌ LEAK! Old node  │
  │                     //    at address lost│
  │                                          │
  │ CORRECT:                                 │
  │ Node* a = new Node(10);                  │
  │ delete a;           // ✅ Free first     │
  │ a = new Node(20);   // Then reassign     │
  └──────────────────────────────────────────┘
*/

void demonstrateDynamicAllocation() {
    cout << "═══ SECTION 6: DYNAMIC MEMORY ALLOCATION ═══\n\n";

    // Allocate nodes
    cout << "Allocating 5 nodes on heap...\n";
    Node* nodes[5];
    for (int i = 0; i < 5; i++) {
        nodes[i] = new Node((i + 1) * 10);
        cout << "  Node(" << nodes[i]->data << ") allocated at: " << nodes[i] << "\n";
    }

    // Link them
    for (int i = 0; i < 4; i++) {
        nodes[i]->next = nodes[i + 1];
    }

    cout << "\nLinked List: ";
    printList(nodes[0]);

    // Proper cleanup
    cout << "\nDeallocating all nodes...\n";
    for (int i = 0; i < 5; i++) {
        cout << "  Deleting Node(" << nodes[i]->data << ") at: " << nodes[i] << "\n";
        delete nodes[i];
    }

    cout << "\nAll memory freed successfully!\n\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  SINGLY LINKED LIST: NODE STRUCTURE & FUNDAMENTALS       ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    demonstrateNodeCreation();
    demonstrateBuildFromArray();
    demonstrateNullHandling();
    demonstratePointers();
    demonstrateDynamicAllocation();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE PROBLEMS:\n";
    cout << "───────────────────\n";
    cout << "1. Create a linked list of 10 nodes with values 1-10\n";
    cout << "2. Print the address of each node and its next pointer\n";
    cout << "3. Build a list from user input (until -1 is entered)\n";
    cout << "4. Count total nodes in a linked list\n";
    cout << "5. Find the sum of all elements in a linked list\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

