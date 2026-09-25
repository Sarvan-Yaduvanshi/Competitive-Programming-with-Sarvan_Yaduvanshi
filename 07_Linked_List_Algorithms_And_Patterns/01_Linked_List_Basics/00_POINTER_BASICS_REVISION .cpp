/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                    00 — POINTER BASICS REVISION                              ║
║           From Zero to Grandmaster — Complete Foundation                     ║
║           (Tree → Graph → Recursion all get easier once this is automatic)   ║
╚══════════════════════════════════════════════════════════════════════════════╝

CORE MENTAL MODEL (memorize this line):
────────────────────────────────────────
  A pointer stores an address.  *  follows an address.  &  gets an address.

TABLE OF CONTENTS:
──────────────────
 PART A — Core Operators            : *, &, ->, . vs ->
 PART B — nullptr & Null Safety     : nullptr, NULL, 0
 PART C — References                : &ref, pointer vs reference
 PART D — Pointer-to-Pointer        : Node*&, Node**
 PART E — const with Pointers       : 3 forms + memory trick
 PART F — Arrays & Pointer Arithmetic
 PART G — Dynamic Memory            : new, delete, dangling, leaks
 PART H — static keyword            : functions, locals, arrays
 PART I — Stack vs Heap
 PART J — Pointer Patterns          : Linked List → Tree → Graph
 PART K — Bug Checklist             : red flags to recognize instantly
 PART L — Syntax Reference Table
 PART M — Master Mental Model
*/

/*
        ═══════════════════════════════════════════════════════════════════════════
        PART A — CORE OPERATORS:  *  (dereference)   &  (address-of)   ->  (arrow)
        ═══════════════════════════════════════════════════════════════════════════

  A1. WHAT IS A POINTER?
  ───────────────────────
  A pointer is just a variable whose VALUE is an ADDRESS.

    x
    ┌───────┐
    │  10   │            x lives at address 1000
    └───────┘
    address = 1000

    p
    ┌───────┐
    │ 1000  │ ─────────→ x
    └───────┘             │
                          ▼
                         10

  p does not hold 10. p holds the ADDRESS of x (1000).

  // int x = 10;
  // int* p = &x;      // p now stores the address of x


  A2. &  —  ADDRESS-OF OPERATOR
  ───────────────────────────────
  &x  reads as:  "give me the address of x."

  // int x = 10;
  // cout << &x;        // prints x's address, e.g. 0x7ffee...
  // int* p = &x;       // p stores the address of x

  Two different things are happening in one line:
    int* p     →  p is declared as "pointer to int"
    &x         →  the address-of x, used to initialize p


  A3. *  —  DEREFERENCE OPERATOR   (the most important pointer operation)
  ─────────────────────────────────────────────────────────────────────
  *p  reads as:  "go to the address stored in p, and access the value there."

  // int x = 10;
  // int* p = &x;
  // cout << p;         // prints the ADDRESS (1000)
  // cout << *p;         // prints the VALUE at that address (10)

    p
    │  contains address
    ▼
    ┌─────────┐
    │  1000   │
    └─────────┘
         │
         ▼   address 1000
    ┌─────────┐
    │   10    │
    └─────────┘

  Therefore:  *p == 10


  A4. THE SAME *  HAS TWO DIFFERENT MEANINGS  (this trips up almost everyone)
  ─────────────────────────────────────────────────────────────────────────
  // int* p;      →  DECLARATION meaning: "p is a pointer"
  // *p = 20;     →  DEREFERENCE meaning: "store 20 at the address p points to"

  int* p = &x;   and   *p = 20;   use * in two completely different roles.


  A5. WHY POINTERS ARE POWERFUL — MODIFYING DATA THROUGH AN ADDRESS
  ────────────────────────────────────────────────────────────────
  // int x = 10;
  // int* p = &x;
  // *p = 50;          // this changes x itself, not just p
  // cout << x;         // prints 50

    p ─────────→ x            p ─────────→ x
                 10    *p=50               50

  This — modifying the original variable by writing through its address —
  is the entire foundation of everything pointers are used for.

  A6. &  AND  *  ARE INVERSES OF EACH OTHER
  ───────────────────────────────────────────
  // int x = 10;
  // int* p = &x;
  //
  // *p       == x                 (dereferencing p gives back x)
  // &p       == address of p      (the pointer variable itself has an address)
  // *(&x)    == x                 (address-of, then dereference, cancels out)

  &x → address of x
  *(&x) → x

  Rule to internalize:   *&anything == anything

  A7. POINTER DECLARATIONS FOR DIFFERENT TYPES
  ───────────────────────────────────────────────
  // int*    p;     // pointer to int
  // double* p;     // pointer to double
  // char*   p;     // pointer to char
  // Node*   p;     // pointer to Node   ← this is what Linked Lists use

  For a Linked List:
  // Node* next;     // "next" stores the address of another Node

  That single line is WHY this chain is possible:

    [10 | next] ───→ [20 | next] ───→ [30 | NULL]


  A8. .  vs  ->    (object access vs pointer access)
  ──────────────────────────────────────────────────
  If you HOLD the object directly, use  .
  // Node n(10);
  // n.data;             // direct member access

  If you HOLD a pointer TO the object, use  ->
  // Node* p = &n;
  // p->data;            // pointer member access, same as (*p).data

  RULE:
    object   →  .
    pointer  →  ->

  Why -> exists:
  // Node* head = new Node(10);
  // cout << head->data;      // go to the Node pointed to by head, read data
  //
  // p->data   is identical to   (*p).data

    head
     ↓
    Node
     ├── data
     └── next

      ═══════════════════════════════════════════════════════════════════════════
                          PART B — nullptr & NULL SAFETY
      ═══════════════════════════════════════════════════════════════════════════

  B1. NEVER LEAVE A POINTER WITH AN UNKNOWN VALUE
  ─────────────────────────────────────────────────
  // Node* p;              // ❌ BAD — p holds garbage/indeterminate address
  // Node* p = nullptr;    // ✅ GOOD — p explicitly points to nothing

  // Node* head = nullptr;   // this represents an EMPTY linked list

    head
     │
     ▼
    NULL

  nullptr always means: "no valid object is being pointed to."


  B2. nullptr  vs  NULL  vs  0
  ────────────────────────────
  // Node* p = nullptr;   // ✅ Modern C++ — PREFERRED, type-safe
  // Node* p = NULL;      // older C/C++ style, works but less type-safe
  // Node* p = 0;         // oldest style, avoid in modern code

  Always reach for nullptr in new C++ code.


      ═══════════════════════════════════════════════════════════════════════════
            PART C — REFERENCES  (&  as a declaration, not address-of)
      ═══════════════════════════════════════════════════════════════════════════

  C1. REFERENCE &   —  ANOTHER NAME FOR AN EXISTING VARIABLE
  ─────────────────────────────────────────────────────────
  // int x = 10;
  // int& ref = x;     // ref is now just an alias for x — NOT a new variable

    x
    │
    └────→ 10
     ^
     |
    ref

  // ref = 20;          // this changes x itself
  // cout << x;          // prints 20


  C2. POINTER  vs  REFERENCE — the conceptual split
  ───────────────────────────────────────────────────
  // int* p = &x;     // POINTER: stores an address, CAN be reassigned/null
  // int& r = x;      // REFERENCE: alias for x, CANNOT be reassigned/null

  pointer    →  stores an address (can point elsewhere later, can be null)
  reference  →  permanent alias for one existing object (must bind at creation)

    ═══════════════════════════════════════════════════════════════════════════
            PART D — POINTER-TO-POINTER:  Node*&  and  Node**
    ═══════════════════════════════════════════════════════════════════════════

  D1. WHY A PLAIN POINTER PARAMETER DOESN'T LET YOU MODIFY THE CALLER'S POINTER
  ────────────────────────────────────────────────────────────────────────────
  // Node* head = node1;
  //
  // void foo(Node* head) {
  //     head = nullptr;      // only changes the LOCAL copy of the pointer
  // }
  // foo(head);                // caller's head is UNCHANGED

  The pointer itself was passed BY VALUE — a copy — so reassigning it inside
  the function does nothing to the original.


  D2. Node*&  —  REFERENCE TO A POINTER  (fixes the problem above)
  ──────────────────────────────────────────────────────────────────
  // void foo(Node*& head) {
  //     head = nullptr;      // this DOES change the caller's head
  // }
  // foo(head);

  // void deleteList(Node*& head)     // classic real-world signature
  //     can modify the caller's head, e.g. setting it to nullptr after
  //     freeing every node.

  Mental model:
    Node* head    =  a pointer
    Node*& head   =  a reference TO that pointer (an alias for the pointer var)


  D3. Node**  —  POINTER TO A POINTER  (the older/C-style equivalent)
  ─────────────────────────────────────────────────────────────────────
  // void change(Node** p) {
  //     *p = nullptr;         // dereference once to reach the actual pointer
  // }
  // change(&head);            // pass the ADDRESS of the head pointer

  Because:
    head       →  Node*             (a pointer)
    &head      →  address of Node*  (a pointer to a pointer)

  You'll encounter ** in:
    - classic linked-list implementations (C-style)
    - dynamic memory / 2D dynamic arrays
    - C APIs
    - some tree algorithms

  Modern C++ generally prefers Node*& — it reads cleaner than Node**.

        ═══════════════════════════════════════════════════════════════════════════
                  PART E — const WITH POINTERS  (three distinct forms)
        ═══════════════════════════════════════════════════════════════════════════

  E1. FORM A — POINTER TO CONST DATA  (pointer can move, data can't change)
  ───────────────────────────────────────────────────────────────────────
  // const int* p;      // or equivalently: int const* p;
  //
  // p = &a;            // ✅ OK — reassigning the pointer is fine
  // p = &b;            // ✅ OK
  // *p = 20;           // ❌ ERROR — can't modify the value through p

    ┌─────────┐
    │ pointer │ ───→ const data
    └─────────┘


  E2. FORM B — CONST POINTER  (pointer is fixed, data can change)
  ───────────────────────────────────────────────────────────────
  // int* const p = &x;
  //
  // *p = 20;           // ✅ OK — modifying the pointed-to value is fine
  // p = &y;            // ❌ ERROR — can't repoint a const pointer

    fixed pointer ───→ mutable data


  E3. FORM C — CONST POINTER TO CONST DATA  (nothing can change)
  ─────────────────────────────────────────────────────────────────
  // const int* const p = &x;
  //
  // *p = 20;           // ❌ ERROR
  // p = &y;            // ❌ ERROR

    fixed pointer ───→ read-only data


  E4. EASY RULE TO REMEMBER WHICH IS WHICH
  ────────────────────────────────────────
  Look at what sits immediately to the LEFT of const.

  // const int* p;        // "int" is const     → can't modify DATA through p
  // int* const p;        // "p" is const        → can't reassign the POINTER
  // const int* const p;  // both are const      → neither is allowed


  E5. WHY const Node*  IN TRAVERSAL FUNCTIONS
  ──────────────────────────────────────────────
  // static void printList(const Node* head) {
  //     const Node* curr = head;
  //     while (curr != nullptr) {
  //         cout << curr->data;      // ✅ reading is fine
  //         curr = curr->next;       // ✅ moving the pointer is fine
  //         // curr->data = 50;      // ❌ ERROR — can't modify through curr
  //     }
  // }

  This is exactly the contract a print/read-only traversal function should
  make explicit: "I promise not to mutate the list you gave me."


     ═══════════════════════════════════════════════════════════════════════════
            PART F — ARRAYS & POINTER ARITHMETIC
     ═══════════════════════════════════════════════════════════════════════════

  F1. ARRAY NAME DECAYS TO A POINTER TO ITS FIRST ELEMENT
  ────────────────────────────────────────────────────────
  // int arr[] = {10, 20, 30};
  // int* p = arr;            // arr decays to &arr[0]; this is valid
  //
  // cout << *p;                // 10
  // cout << *(p + 1);          // 20
  // cout << *(p + 2);          // 30


  F2. POINTER ARITHMETIC MOVES BY ELEMENT SIZE, NOT BY BYTE
  ─────────────────────────────────────────────────────────
  // *p          → arr[0]
  // *(p + 1)    → arr[1]
  // *(p + 2)    → arr[2]

  p + 1 does NOT mean "+1 byte" — it means "advance by one int-sized step."

    p
     ↓
    [10][20][30][40]

  p + 1 points to [20], not to the second byte of [10].


  F3. ARRAY INDEXING IS JUST POINTER ARITHMETIC IN DISGUISE
  ────────────────────────────────────────────────────────────
  // arr[i]  is exactly equivalent to  *(arr + i)
  //
  // arr[3]   conceptually means   *(arr + 3)

  Internalizing this equivalence is one of the deepest "aha" moments in C++.

      ═══════════════════════════════════════════════════════════════════════════
        PART G — DYNAMIC MEMORY:  new / delete / dangling pointers / leaks
      ═══════════════════════════════════════════════════════════════════════════

  G1. new  —  ALLOCATE ON THE HEAP
  ───────────────────────────────────
  // Node* p = new Node(10);
  //
  //   1. Create a Node dynamically (on the heap).
  //   2. Return its address.
  //   3. Store that address in p (p itself lives on the stack).

    Stack                    Heap
    p                        ┌─────────────────┐
    │                        │ data = 10        │
    └──────────────────────▶ │ next = nullptr   │
                              └─────────────────┘

  The node lives in dynamic memory; p is just the stack variable holding
  its address. This is why the node survives beyond the current scope.


  G2. delete  —  RELEASE HEAP MEMORY
  ──────────────────────────────────────
  // Node* p = new Node(10);
  // ...
  // delete p;             // releases the dynamically allocated object
  //
  // After delete p;  never use  *p  again — the object no longer exists.


  G3. DANGLING POINTER
  ────────────────────────
  // Node* p = new Node(10);
  // delete p;
  // cout << p->data;      // ❌ BAD — p still holds the OLD address,
  //                        //    but that memory is no longer valid

  Safer pattern:
  // delete p;
  // p = nullptr;          // now p explicitly points to nothing

    p → nullptr      // prevents accidentally treating a stale address as valid


  G4. MEMORY LEAK
  ────────────────────
  // Node* p = new Node(10);
  // p = new Node(20);     // ❌ the FIRST node is now unreachable — leaked

    First node                    p
    [10]  ← nothing points here   └───→ [20]

  The 10-node can never be delete'd again; its address was overwritten
  before being freed. In linked-list code, losing a node reference
  without deleting it first is exactly how leaks happen.


  G5. PUTTING IT TOGETHER — LINKED LIST CONSTRUCTION
  ──────────────────────────────────────────────────────
  // Node* head = new Node(arr[0]);   // head is a pointer
  // Node* tail = head;
  //
  // tail->next = new Node(arr[1]);   // dynamically create + link in one step
  // tail = tail->next;               // move tail forward

  Every piece:
    Node* head        → head is a pointer
    new Node(arr[0])   → dynamically create a node, return its address
    tail->next         → access next THROUGH a pointer
    tail = tail->next  → move the pointer itself to the next node

  This is precisely why solid pointer fundamentals make Linked Lists,
  Trees, and Graphs dramatically easier later.

      ═══════════════════════════════════════════════════════════════════════════
              PART H — static KEYWORD  (functions, locals, arrays)
      ═══════════════════════════════════════════════════════════════════════════

  H1. static ON A FUNCTION (file/global scope) — INTERNAL LINKAGE, NOT "static pointer"
  ────────────────────────────────────────────────────────────────────────────────────
  // static Node* buildList(...);
  //
  // At global/namespace scope, static does NOT mean "the pointer is static."
  // It gives the FUNCTION internal linkage — usable only within this
  // source file / translation unit.
  //
  // For CP purposes, read it as: "file-local helper function."
  // This is a different meaning from static on a local variable (below).


  H2. static LOCAL VARIABLE — LIFETIME EXTENDS FOR THE WHOLE PROGRAM
  ──────────────────────────────────────────────────────────────────────
  // void foo() {
  //     static int x = 0;
  //     ++x;
  //     cout << x << '\n';
  // }
  //
  // foo(); foo(); foo();     // prints: 1  2  3

  Normally a local variable dies when its function returns. A `static`
  local variable instead keeps its value between calls — it's initialized
  only once, and persists for the entire program's lifetime.


  H3. static ARRAY
  ────────────────────
  // static int arr[MAX_SIZE];
  //
  //   - has static storage duration (not a stack-only, scope-bound array)
  //   - zero-initialized automatically if not explicitly initialized
  //   - perfectly standard in CP when MAX_SIZE is a known upper bound


      ═══════════════════════════════════════════════════════════════════════════
                      PART I — STACK vs HEAP
      ═══════════════════════════════════════════════════════════════════════════

  I1. STACK  —  automatic storage, scope-bound
  ─────────────────────────────────────────────
  // int x = 10;
  // Node node;             // lives on the stack, auto-destroyed at scope end


  I2. HEAP  —  dynamic storage, manually managed
  ──────────────────────────────────────────────────
  // Node* p = new Node(10);   // lives on the heap until explicitly deleted

    STACK                    HEAP
    ----------------         ----------------
    head                     Node
    curr                     Node
    x                        Node
    ----------------         ----------------

  Key idea: the POINTER VARIABLE can live on the stack while the OBJECT
  it points to lives on the heap. This split is exactly what lets heap
  objects outlive the function scope that created them — critical for
  every linked structure (list, tree, graph).


        ═══════════════════════════════════════════════════════════════════════════
                PART J — POINTER PATTERNS: LINKED LIST → TREE → GRAPH
        ═══════════════════════════════════════════════════════════════════════════

  J1. LINKED LIST POINTER PATTERN
  ───────────────────────────────────
  // Node* head = nullptr;             // empty list

    head
     ↓
    [10] → [20] → [30] → nullptr

  // Node* curr = head;
  // while (curr != nullptr) {
  //     cout << curr->data;
  //     curr = curr->next;
  // }

  Three pointer roles at play:
    head       →  first node
    curr       →  current node during traversal
    curr->next →  the next node in the chain


  J2. TREE POINTER PATTERN  (same idea, two links instead of one)
  ─────────────────────────────────────────────────────────────────
  // struct TreeNode {
  //     int data;
  //     TreeNode* left;
  //     TreeNode* right;
  // };

            [10]
           /    \
         [5]    [20]

  // root->left    → address of the 5-node
  // root->right   → address of the 20-node

  root->left / root->right are the EXACT same pointer concept as head->next
  — just two links per node instead of one.


  J3. GRAPH POINTER CONNECTION
  ─────────────────────────────────
  // vector<Node*> neighbors;      // or dynamically allocated graph nodes

  Same underlying idea again: pointer = address/reference to another object.

  Once *, &, ->, nullptr, references, and const are automatic, the chain

        Linked List → Tree → Graph

  gets dramatically easier, because every one of them is just "nodes
  connected by addresses" with a different connection shape.

        ═══════════════════════════════════════════════════════════════════════════
                    PART K — BUG CHECKLIST: RECOGNIZE THESE INSTANTLY
        ═══════════════════════════════════════════════════════════════════════════

  K1. UNINITIALIZED POINTER
  // Node* p;
  // p->data;                 // ❌ don't dereference — value is garbage

  K2. NULL DEREFERENCE
  // Node* p = nullptr;
  // p->data;                 // ❌ invalid — p points to nothing

  K3. DANGLING POINTER
  // delete p;
  // p->data;                 // ❌ invalid — object no longer exists

  K4. MEMORY LEAK
  // p = new Node(10);
  // p = new Node(20);        // ❌ first node leaked, unreachable now

  K5. LOST HEAD (not always a bug, but a common trap)
  // head = head->next;       // ⚠ dangerous if the old head was needed
                               //   and wasn't saved somewhere first

          ═══════════════════════════════════════════════════════════════════════════
                    PART L — SYNTAX REFERENCE TABLE
          ═══════════════════════════════════════════════════════════════════════════

  ┌────────────────────────┬──────────────────────────────────────────┐
  │ Syntax                 │ Meaning                                  │
  ├────────────────────────┼──────────────────────────────────────────┤
  │ int* p                 │ p is a pointer to int                    │
  │ &x                     │ address of x                             │
  │ *p                     │ value/object pointed to by p             │
  │ int& r                 │ reference to int                         │
  │ p->x                   │ access member through a pointer          │
  │ p == nullptr           │ pointer points to nothing                │
  │ new Node(...)          │ dynamically create an object             │
  │ delete p               │ destroy a dynamically allocated object   │
  │ Node*& p               │ reference to a Node*                     │
  │ Node** p               │ pointer to a Node*                       │
  │ const Node* p          │ cannot modify the Node through p         │
  │ Node* const p          │ cannot change the pointer p              │
  │ const Node* const p    │ neither is allowed through p             │
  └────────────────────────┴──────────────────────────────────────────┘

        ═══════════════════════════════════════════════════════════════════════════
              PART M — MASTER MENTAL MODEL  (the 10 lines to make automatic)
        ═══════════════════════════════════════════════════════════════════════════

  M1. THE TEN LINES
  ───────────────────
  // int x = 10;
  //
  // int* p = &x;        // pointer stores address
  // *p = 20;             // modify x through the pointer
  //
  // int& r = x;          // reference / alias
  // r = 30;               // modifies x directly
  //
  // int* q = nullptr;    // points to nothing
  //
  // Node* node = new Node(10);
  // node->data;           // access through pointer
  // node->next;           // access next pointer
  //
  // delete node;          // free the object
  // node = nullptr;       // avoid a dangling pointer
  //
  // void f(Node*& head);  // "let this function change the caller's Node*"


  M2. THE ONE DIAGRAM THAT EXPLAINS EVERYTHING
  ───────────────────────────────────────────────
  Whenever you see:

  // Node* p;

  think:

    p
    │
    │  stores an address
    ▼
    ┌────────────────┐
    │ Node            │
    │ data            │
    │ next ───────────┼──→ another Node
    └────────────────┘

  Then:
    p->data   →  go to the Node stored at p, then read data
    *p        →  access the whole object stored at that address
    &p        →  the address of the POINTER VARIABLE p itself
                 (this last one is exactly what makes Node** click)
*/
