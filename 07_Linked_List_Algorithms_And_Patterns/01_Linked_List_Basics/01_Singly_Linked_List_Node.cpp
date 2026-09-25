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

/*
	═══════════════════════════════════════════════════════════════
					SECTION 1: NODE STRUCTURE
    ═══════════════════════════════════════════════════════════════

  The fundamental building block of a singly linked list.
  ┌───────────────────┐
  │    Node           │
  │  ┌──────┬───────┐ │
  │  │ data │ next  │ │
  │  │ int  │ Node* │ │
  │  └──────┴───────┘ │
  └───────────────────┘
struct Node {
    int data;       // Stores the actual value
    Node* next;     // Pointer to the next node

    // Constructor for easy node creation
    Node(int val) : data(val), next(nullptr) {}

    // Constructor with next pointer
    Node(int val, Node* nxt) : data(val), next(nxt) {}
};

A Node is a struct/class holding:
	- data : the payload (int, or any type T in a generic version)
	- next : a self-referential pointer to another Node of the same type

  Two constructor variants a GM-level implementation typically provides:
	a) Node(val)          → initializes data, sets next = nullptr
							 (used for tail/leaf nodes, or single insert)
	b) Node(val, nextPtr) → initializes data AND wires next in one shot
							 (avoids a second statement, useful when
							 prepending to an existing list:
							 newNode = Node(val, head); head = newNode;)

	═══════════════════════════════════════════════════════════════
				SECTION 2: CREATING NODES MANUALLY
    ═══════════════════════════════════════════════════════════════

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

STRUCTURE SKETCH (pseudo-form, not real/compilable code):
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

	═══════════════════════════════════════════════════════════════
				SECTION 3: BUILDING A LIST FROM ARRAY
	═══════════════════════════════════════════════════════════════

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

GM-LEVEL NOTES:
  ───────────────
  • This is the "tail pointer" technique — the single most important
	optimization for list-building. Without maintaining `tail`, appending
	the i-th element requires re-traversing from head each time,
	degrading total construction to O(n²).
  • Interview trap: if you forget to advance `tail` after each insert,
	every new node overwrites the same `next` slot, silently corrupting
	the list (classic off-by-one / dangling-reference bug).
  • Edge case: building from an EMPTY array must special-case head = nullptr
	— there is no first element to seed `head` and `tail` with.

STRUCTURE SKETCH (pseudo-form, not real/compilable code):
  ───────────────────────────────────────────────────────
  Node* buildFromArray(arr[], n):
	  if n == 0: return NULL

	  head = new Node(arr[0])
	  tail = head

	  for i = 1 to n-1:
		  tail->next = new Node(arr[i])
		  tail = tail->next

	  return head

Note: if you see more details code so check linked problem solving folder
	  13_Linked_List_Problem_Solving/01_BUILDING_A_LIST_FROM_ARRAY.cpp

	═══════════════════════════════════════════════════════════════
			 SECTION 4: HEAD POINTER & NULL HANDLING
	═══════════════════════════════════════════════════════════════

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
WALKTHROUGH OF THE THREE DEMONSTRATED CASES:
  ─────────────────────────────────────────────
  Case 1 — Empty list:
	head is explicitly nullptr. Any check `head == nullptr` correctly
	identifies an empty structure. This is the base case every
	recursive/iterative list algorithm must handle first.

  Case 2 — Single node:
	head points to one heap-allocated node whose `next` is nullptr
	(guaranteed by the single-arg constructor convention).
	Printing confirms exactly one element; checking `head->next == nullptr`
	is the standard way to detect "list has exactly one node" without
	a separate size counter.

  Case 3 — Guarded second-node access:
	Before touching `head->next->data`, first confirm `head->next` isn't
	null. This two-level guard pattern (`curr && curr->next`) recurs
	constantly in linked-list algorithms: reversal, cycle detection,
	merging, middle-node finding (slow/fast pointers), etc.

  GM-LEVEL NOTE: the single most common runtime crash in linked-list
  code across interviews is a NULL dereference from skipping exactly
  this kind of guard — especially inside loops that advance two pointers
  at different speeds (e.g., Floyd's cycle detection, finding the
  middle element).

  STRUCTURE SKETCH (pseudo-form, not real/compilable code):
  ───────────────────────────────────────────────────────
  Node* head = NULL              // Case 1: empty list
  if head == NULL: print "empty"

  head = new Node(42)            // Case 2: single node
  if head->next == NULL: print "only one node"

  if head->next != NULL:         // Case 3: guarded 2-level access
	  print head->next->data
  else:
	  print "no second node"


	═══════════════════════════════════════════════════════════════
			SECTION 5: DYNAMIC MEMORY ALLOCATION
	═══════════════════════════════════════════════════════════════

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

STRUCTURE SKETCH (pseudo-form, not real/compilable code):
  ───────────────────────────────────────────────────────
  Node* nodes[5]
  for i = 0 to 4:
	  nodes[i] = new Node((i+1) * 10)

  for i = 0 to 3:
	  nodes[i]->next = nodes[i+1]

  printList(nodes[0])

  for i = 0 to 4:
	  delete nodes[i]
*/


