/*
 * Author  : Sarvan Yaduvanshi
 * Created : 2026-10-12
 *
 * ============================================================================
 *  LINKED LIST FUNDAMENTALS  -  WHAT IS A LINKED LIST?
 *  Folder : 01_Linked_List_Basics
 *  Level  : Zero -> Advanced (concepts shared by EVERY type of linked list)
 * ============================================================================
 *
 *  SCOPE OF THIS FILE
 *    This file explains the ideas that all linked lists share: what a linked
 *    list is, what a node is, what next and prev pointers do, how lists sit in
 *    memory, the types of linked lists, and how they compare with arrays.
 *    Operation-level details live in the type-specific notes:
 *        Singly   : 01_Singly_Linked_List_Node.cpp
 *        Doubly   : 02_Doubly_Linked_List_Node.cpp
 *        Circular : 03_Circular_Linked_List.cpp
 *
 *  PSEUDOCODE LEGEND (used in all notes)
 *      a <- b        assign b to a
 *      NULL          the null pointer (nullptr in C++)
 *      p.next        the next field of the node that p points to  (p->next)
 *      Node(v)       create a node holding v with all pointers NULL
 *
 *  CONTENTS
 *     1. Why linked lists exist (the problem with arrays)
 *     2. Definition of a linked list
 *     3. Anatomy of a node: data, next, prev
 *     4. List-level handles: head, tail, size (and invariants)
 *     5. Memory: layout, cost, cache behaviour, lifecycle
 *     6. Types of linked lists
 *     7. Operations at a glance and the O(1) insertion misconception
 *     8. Linked list vs array vs vector vs deque
 *     9. Real-world uses
 *    10. Core ideas to master (the toolkit)
 *    11. Common pitfalls
 *    12. Edge case checklist
 *    13. Roadmap: zero to grandmaster
 *    14. Glossary
 *    15. Quick revision Q&A and key takeaways
 *
 *
 * ============================================================================
 *  1. WHY LINKED LISTS EXIST
 * ============================================================================
 *
 *  THE ARRAY AND ITS LIMITS
 *    An array stores its elements in ONE contiguous block of memory. Because
 *    every element has the same size, the address of element i is computed:
 *
 *        address(i) = base + i * sizeof(element)
 *
 *    This gives O(1) access by index. The price is that the ORDER of elements
 *    is encoded by their POSITION in memory, which causes three problems:
 *
 *      1. Insert / delete in the front or middle must SHIFT every later element.
 *      2. Capacity is fixed at creation. Growing means allocating a bigger block
 *         and copying everything (a dynamic array hides this, but it still
 *         happens).
 *      3. It needs one large contiguous block. Memory can be plentiful in total
 *         but too fragmented to hold the block.
 *
 *    EXAMPLE: insert 25 between 20 and 30 in an array
 *
 *        before : [10][20][30][40]
 *        shift  : 30 and 40 each move one slot right   (2 moves, O(n) in general)
 *        after  : [10][20][25][30][40]
 *
 *  THE LINKED LIST IDEA
 *    Stop encoding order by position. Instead make every element remember WHERE
 *    THE NEXT ELEMENT IS. Then elements can live anywhere in memory, each
 *    allocated on its own, and "inserting" means changing a couple of pointers.
 *
 *        before :  10 -> 20 -> 30 -> 40
 *        create :  25
 *        rewire :  20 -> 25 -> 30            (two pointer updates, no shifting)
 *        after  :  10 -> 20 -> 25 -> 30 -> 40
 *
 *  WHAT YOU GIVE UP
 *    The address of element i is no longer computable. To reach the i-th element
 *    you must follow links from the start: access by index becomes O(n).
 *
 *    Linked lists trade fast indexing for cheap restructuring.
 *
 *
 * ============================================================================
 *  2. DEFINITION OF A LINKED LIST
 * ============================================================================
 *
 *  DEFINITION
 *   A Linked List is a linear data structure where elements (nodes) are stored
	 in non-contiguous memory locations. Each node contains:
			• Data — The actual value
			• Pointer — Address of the next node
 *
 *  RECURSIVE DEFINITION (very useful for recursion problems)
 *      A linked list is either
 *          - empty (NULL), or
 *          - one node followed by a (smaller) linked list.
 *    So list = node + list. This is why many list algorithms have a natural
 *    recursive form, with "empty list" as the base case.
 *
 *  ANALOGIES
 *    - Treasure hunt  : each clue tells you where the next clue is. You cannot
 *                       jump to clue 7; you must follow clues 1 to 6.
 *    - Train          : each coach is coupled to the next. Adding or removing a
 *                       coach only changes couplings, not the other coaches.
 *    - Playlist       : each song knows which song plays next.
 *
 *  EXAMPLE 1 : a list holding 10, 20, 30
 *
 *      head
 *       |
 *       v
 *     +----+---+     +----+---+     +----+------+
 *     | 10 | o-+---->| 20 | o-+---->| 30 | NULL |
 *     +----+---+     +----+---+     +----+------+
 *       data next       data next       data next
 *
 *  EXAMPLE 2 : an empty list and a one-node list
 *
 *      empty :   head = NULL                      (no nodes exist)
 *
 *      one node :  head
 *                   |
 *                   v
 *                 +----+------+
 *                 | 42 | NULL |      head.next == NULL means "exactly one node"
 *                 +----+------+
 *
 *  KEY PROPERTIES
 *    - Linear         : one element follows another (unlike a tree or a graph).
 *    - Dynamic size   : grows and shrinks one node at a time; no capacity limit
 *                       other than available memory.
 *    - Non-contiguous : nodes can be scattered in memory.
 *    - Sequential access : reaching an element means walking from a known node.
 *    - Pointer-based  : all structure lives in the links.
 *
 *
 * ============================================================================
 *  3. ANATOMY OF A NODE
 * ============================================================================
 *
 *  A node is the building block of every linked list. It is a small record
 *  (a struct or class) with these fields:
 *
 *    3.1  data  : the payload. An int in these notes; in general any type T
 *                 (a generic list uses a template parameter).
 *
 *    3.2  next  : a pointer holding the ADDRESS of the node that comes AFTER
 *                 this one. Following it moves you forward by one node.
 *                   - In the last node of a linear list, next is NULL: this is
 *                     the signal "the list ends here".
 *                   - In a circular list, the last node's next points back to the
 *                     first node, so no node has a NULL next.
 *
 *    3.3  prev  : (doubly lists only) a pointer holding the ADDRESS of the node
 *                 that comes BEFORE this one. Following it moves you backward.
 *                   - In the first node of a linear doubly list, prev is NULL.
 *                   - In a circular doubly list, the first node's prev points to
 *                     the last node.
 *
 *  NODE SHAPES
 *
 *      singly node :   +------+------+
 *                      | data | next |
 *                      +------+------+
 *
 *      doubly node :   +------+------+------+
 *                      | prev | data | next |
 *                      +------+------+------+
 *
 *  PSEUDOCODE
 *      Node (singly):   data, next
 *      Node (doubly):   data, prev, next
 *      Node(v):         data <- v;  prev <- NULL;  next <- NULL
 *
 *  3.4  WHY next IS A POINTER TO A NODE (self-referential structure)
 *    A node contains a link to another node of the SAME type. If next were a
 *    whole Node stored inside the node, the size would be infinite (a node inside
 *    a node inside a node ...), which the compiler rejects. A POINTER has a fixed
 *    size (8 bytes on a typical 64-bit system), so the type is finite:
 *
 *        a node = data + (address of another node)
 *
 *  3.5  WHAT "FOLLOWING A POINTER" MEANS (worked example)
 *    Suppose three nodes live at these made-up addresses:
 *
 *        address    data   next
 *        0x1000     10     0x1F40
 *        0x1F40     20     0x2B80
 *        0x2B80     30     NULL
 *
 *    With head = 0x1000:
 *        head.data        = 10            (read the node at 0x1000)
 *        head.next        = 0x1F40        (the address of the second node)
 *        head.next.data   = 20            (hop to 0x1F40, read its data)
 *        head.next.next   = 0x2B80
 *        head.next.next.next = NULL       (the end)
 *
 *    Every list algorithm is some pattern of "read a field, hop to the node it
 *    points to". A pointer variable that walks the list is often called cur,
 *    curr or temp.
 *
 *  3.6  NODE CONSTRUCTOR
 *    A constructor sets data and initialises every pointer to NULL. Without it
 *    the pointers hold garbage, and the last node would not be NULL-terminated,
 *    so traversal would run into random memory. Some designs also offer
 *    Node(v, nextPtr), which sets data and wires next in one step.
 *
 *  3.7  NODE SIZE (typical 64-bit platform)
 *      singly node : int (4) + padding (4) + pointer (8)             = 16 bytes
 *      doubly node : int (4) + padding (4) + pointer (8) + pointer (8) = 24 bytes
 *    The padding keeps the 8-byte pointer aligned. The pointers cost more than
 *    the data itself for small payloads (see Section 5).
 *
 *  3.8  CHANGING THE HEAD FROM INSIDE A FUNCTION
 *    A function that inserts or deletes at the front changes which node is the
 *    head. A pointer passed BY VALUE is only a copy, so the caller's head would
 *    not change. Either RETURN the new head, or take the head BY REFERENCE
 *    (Node*& head). Forgetting this is one of the most common beginner bugs.
 *
 *
 * ============================================================================
 *  4. LIST-LEVEL HANDLES: HEAD, TAIL, SIZE
 * ============================================================================
 *
 *  The nodes alone are not the list. The list is reached through "handles":
 *
 *    head : pointer to the FIRST node. It is the only entry point. If you lose
 *           the head (overwrite it without saving), every node becomes
 *           unreachable and the memory leaks. head == NULL means an EMPTY list.
 *    tail : (optional) pointer to the LAST node. It makes appending at the back
 *           O(1) instead of walking the whole list.
 *    size : (optional) a cached count of nodes. It makes length queries and
 *           bounds checks O(1) instead of O(n).
 *
 *  COMMON HANDLE CHOICES
 *      head only          : smallest; append is O(n).
 *      head + tail        : both ends are O(1) to insert at.
 *      tail only          : used by circular singly lists (head = tail.next).
 *      head only          : used by circular doubly lists (tail = head.prev).
 *      + a size counter   : optional with any of the above.
 *
 *  INVARIANTS (facts that must stay true after EVERY operation)
 *    I1. An empty list has head == NULL (and tail == NULL, size == 0 if kept).
 *    I2. Starting at head and following next reaches every node exactly once.
 *    I3. A LINEAR list ends: following next eventually reaches NULL.
 *    I4. If tail is stored, tail is the node whose next is NULL.
 *    I5. If size is stored, it equals the number of nodes.
 *    I6. (Doubly) Mutual links: if A.next == B then B.prev == A.
 *
 *    Almost every linked list bug is one of these invariants being broken. When
 *    you write an operation, ask: "Which invariants can this break, and which
 *    pointers must I fix to restore them?"
 *
 *
 * ============================================================================
 *  5. MEMORY
 * ============================================================================
 *
 *  5.1  LAYOUT: ARRAY vs LINKED LIST
 *
 *      ARRAY (one block, elements side by side)
 *        address :  0x1000  0x1004  0x1008  0x100C  0x1010
 *        value   :  [ 10 ]  [ 20 ]  [ 30 ]  [ 40 ]  [ 50 ]
 *
 *      LINKED LIST (separate allocations, scattered)
 *        @0x1000          @0x1F40          @0x2B80
 *        +----+--------+  +----+--------+  +----+------+
 *        | 10 | 0x1F40 |->| 20 | 0x2B80 |->| 30 | NULL |
 *        +----+--------+  +----+--------+  +----+------+
 *
 *    WHERE EVERYTHING LIVES
 *      - The pointer variable head is an ordinary local variable (stack).
 *      - Each node is created with  new  and lives on the HEAP, so it survives
 *        after the function that created it returns.
 *      - Nothing guarantees the nodes are near each other, or in list order.
 *
 *  5.2  MEMORY COST
 *    Each node stores pointers in addition to the data, and the allocator adds
 *    bookkeeping per allocation:
 *
 *      Structure holding 10^6 ints          Payload only    Typical total
 *      -----------------------------------  --------------  ------------------
 *      array / vector                       4 MB            about 4 MB
 *      singly linked list (16-byte nodes)   16 MB           16 MB or more
 *      doubly linked list (24-byte nodes)   24 MB           24 MB or more
 *
 *    The "or more" comes from the allocator: each separate allocation carries
 *    its own header and is rounded up (for example, glibc commonly serves a 16-
 *    or 24-byte request from a 32-byte chunk, so the real figure can be about
 *    32 MB for either node type). Exact numbers depend on the platform, so use
 *    them as estimates, not guarantees.
 *
 *    Rule of thumb: for small elements, the links and allocator overhead cost
 *    several times more memory than the data they organise.
 *
 *  5.3  CACHE BEHAVIOUR (why lists are slower than their Big-O suggests)
 *    CPUs load memory in cache lines (typically 64 bytes) and prefetch ahead
 *    when they see sequential access.
 *
 *      - Array traversal reads neighbouring addresses. One cache line holds 16
 *        ints, and the prefetcher predicts the next line: fast.
 *      - List traversal is "pointer chasing": the address of the next node is
 *        known only after the current node has been loaded, and nodes are
 *        scattered. The CPU cannot prefetch, and every hop can be a cache miss
 *        that waits on main memory.
 *
 *    Both traversals are O(n), but the list has a much larger constant factor.
 *    This is why, for many ordinary sizes, a vector can beat a linked list even
 *    at middle insertion and deletion. Linked lists win when elements are large
 *    or expensive to move, when pointers/iterators must stay valid, or when you
 *    already hold a pointer to the position.
 *
 *  5.4  ALLOCATION COST AND THE ARRAY-BASED LIST (competitive programming)
 *    One new / delete per node is relatively slow and fragments the heap. A
 *    common remedy in competitive programming is the ARRAY-BASED (static)
 *    linked list: store the nodes in preallocated arrays and use INDICES as
 *    links instead of pointers.
 *
 *        val  : [ 10, 20, 30, ... ]       value of node i
 *        nxt  : [  1,  2, -1, ... ]       index of the node after i  (-1 = NULL)
 *        head <- 0                        index of the first node
 *        walk : i <- head;  while i != -1:  visit(val[i]);  i <- nxt[i]
 *
 *    Benefits: no per-node allocation, contiguous memory, easy to reset, and a
 *    4-byte index instead of an 8-byte pointer. The "forward star" adjacency
 *    list used for graphs (head[u], nxt[e], to[e]) is exactly this idea.
 *
 *  5.5  MEMORY LIFECYCLE AND THE FOUR CLASSIC ERRORS
 *      new     : allocate a node on the heap, get its address.
 *      delete  : release that node. Every new needs exactly one delete.
 *
 *      ERROR              WHAT HAPPENS                             HOW IT ARISES
 *      -----------------  ---------------------------------------  ------------------------
 *      Memory leak        memory never freed                       lose the head, or never delete
 *      Dangling pointer   pointer still holds a freed address      keep using a pointer after delete
 *      Use after free     read / write freed memory (undefined)    delete cur; then read cur.next
 *      Double free        delete the same node twice (crash)       two owners, or delete twice
 *      Null dereference   read through NULL (crash)                access .next of a NULL pointer
 *
 *    GOLDEN RULES
 *      - Save cur.next BEFORE deleting cur.
 *      - Unlink a node from the list BEFORE deleting it.
 *      - Set pointers to NULL after deleting them when they stay in scope.
 *      - One clear owner for every node (usually the list object); give it a
 *        destructor that frees all nodes, and forbid or deep-copy on copy.
 *
 *    ADVANCED NOTE : std::unique_ptr<Node> next looks safe, but destroying a very
 *    long list frees nodes recursively (each destructor frees the next) and can
 *    overflow the stack for around 10^5 to 10^6 nodes. Long lists need an
 *    iterative destructor that unlinks and frees nodes in a loop.
 *
 *
 * ============================================================================
 *  6. TYPES OF LINKED LISTS
 * ============================================================================
 *
 *  6.1  SINGLY LINKED LIST      (node: data, next)
 *
 *      head
 *       |
 *       v
 *      [10|o]-->[20|o]-->[30|o]-->[40|NULL]
 *
 *      One link per node; you can only move forward. Smallest per-node
 *      overhead. Last node's next is NULL.
 *
 *  6.2  DOUBLY LINKED LIST      (node: prev, data, next)
 *
 *      head                                  tail
 *       |                                     |
 *       v                                     v
 *  NULL <- [10] <-> [20] <-> [30] <-> [40] -> NULL
 *
 *      Two links per node; you can move forward AND backward. Removing a known
 *      node and removing from the back are O(1).
 *
 *  6.3  CIRCULAR SINGLY LINKED LIST
 *
 *             +----------------------------------+
 *             v                                  |
 *      head: [10] --> [20] --> [30] --> [40] ----+
 *
 *      The last node points back to the first instead of NULL. There is no end,
 *      so traversals must stop by count or by returning to the start. Natural
 *      for round-robin processes.
 *
 *  6.4  CIRCULAR DOUBLY LINKED LIST
 *
 *             +--------------------------------------+
 *             v                                      |
 *      head: [10] <-> [20] <-> [30] <-> [40]         |
 *             |                                      |
 *             +--------------------------------------+
 *
 *      Ring in both directions: last.next = head and head.prev = last. The tail
 *      is reachable from the head in O(1), so both ends are O(1).
 *
 *  6.5  VARIANTS AND ADVANCED STRUCTURES
 *      Sentinel (dummy) node list : permanent dummy nodes at the front (and back)
 *                                   remove empty / first / last special cases.
 *      XOR linked list            : each node stores (prev XOR next) in ONE field,
 *                                   giving doubly-list traversal at singly-list
 *                                   memory cost. Relies on address arithmetic;
 *                                   unsafe, non-portable and mostly educational.
 *      Unrolled linked list       : each node holds a small ARRAY of elements, so
 *                                   fewer pointers and much better cache use.
 *      Skip list                  : several layers of linked lists; upper layers
 *                                   skip ahead, giving expected O(log n) search
 *                                   (used, for example, in Redis sorted sets).
 *      Multilevel list            : nodes may also point to a child list
 *                                   (the "flatten a multilevel list" problem).
 *      List with a random pointer : each node has an extra pointer to any node
 *                                   (the "copy list with random pointer" problem).
 *      Self-organising list       : moves recently used nodes towards the front.
 *
 *  6.6  COMPARISON OF THE FOUR MAIN TYPES
 *
 *   Feature                  Singly        Doubly         Circular singly  Circular doubly
 *   -----------------------  ------------  -------------  ---------------  ---------------
 *   Pointers per node        1 (next)      2 (prev,next)  1 (next)         2 (prev,next)
 *   Typical node size        16 bytes      24 bytes       16 bytes         24 bytes
 *   End of list              next == NULL  next == NULL   none (ring)      none (ring)
 *   Move backward            no            yes            no               yes
 *   Insert / remove front    O(1)          O(1)           O(1)             O(1)
 *   Insert back              O(1) w/ tail  O(1) w/ tail   O(1) (tail ptr)  O(1)
 *   Remove back              O(n)          O(1)           O(n)             O(1)
 *   Remove a given node      O(n)          O(1)           O(n)             O(1)
 *   Loop stop condition      cur == NULL   cur == NULL    count / start    count / start
 *   Main risk                NULL deref    wrong prev     infinite loop    infinite loop
 *   Typical use              stacks,       caches,        round-robin,     kernel lists,
 *                            hash chains   editors        queues           heaps
 *
 *  6.7  HOW TO CHOOSE
 *      Only move forward, memory matters      -> singly
 *      Need backward moves or O(1) delete     -> doubly
 *      Repeating / cyclic process             -> circular
 *      Tired of head/tail special cases       -> add sentinel nodes
 *
 *
 * ============================================================================
 *  7. OPERATIONS AT A GLANCE
 * ============================================================================
 *
 *  THE STANDARD OPERATIONS
 *      Traversal   : visit every node by following links from the head.
 *      Access      : get the value at index i (must walk i steps).
 *      Search      : find the first node holding a given value.
 *      Insert      : at the front, at the back, after a node, at index i.
 *      Delete      : from the front, from the back, a given node, at index i.
 *      Update      : change a node's data in place.
 *      Advanced    : reverse, merge, sort, detect cycle, find middle, rotate.
 *
 *  THE TWO REWIRING PATTERNS (every insert and delete is one of these)
 *
 *    INSERT a new node N after node P:
 *        N.next <- P.next        // 1. wire the NEW node first (it still sees the rest)
 *        P.next <- N             // 2. only then redirect the neighbour
 *    Doing step 2 first loses the rest of the list, because P.next is overwritten
 *    before you saved it. (In a doubly list also fix N.prev and the next node's prev.)
 *
 *    DELETE the node X after node P:
 *        X <- P.next             // remember it
 *        P.next <- X.next        // bypass X (unlink)
 *        free X                  // delete last
 *
 *  COMPLEXITY TABLE   (n = number of elements)
 *
 *   Operation                    Array/vector  Singly       Singly        Doubly
 *                                                (head only)  (head+tail)   (head+tail)
 *   ---------------------------  ------------  -----------  ------------  -----------
 *   Access by index              O(1)          O(n)         O(n)          O(n)
 *   Search by value              O(n)          O(n)         O(n)          O(n)
 *   Insert at front              O(n)          O(1)         O(1)          O(1)
 *   Insert at back               O(1) amort.   O(n)         O(1)          O(1)
 *   Insert after a known node    O(n)          O(1)         O(1)          O(1)
 *   Insert at index i            O(n)          O(n)         O(n)          O(n)
 *   Delete at front              O(n)          O(1)         O(1)          O(1)
 *   Delete at back               O(1)          O(n)         O(n)          O(1)
 *   Delete a known node          O(n)          O(n)         O(n)          O(1)
 *   Delete at index i            O(n)          O(n)         O(n)          O(n)
 *   Extra memory per element     none          1 pointer    1 pointer     2 pointers
 *
 *  THE O(1) INSERTION MISCONCEPTION
 *    "Linked list insertion is O(1)" is only true when you ALREADY HOLD a
 *    pointer to the position. Inserting at a given INDEX or after a given VALUE
 *    first needs O(n) to find that node, so the total is O(n). The advantage over
 *    arrays is that the rewiring itself does not shift elements.
 *    Why "Delete a known node" is O(n) in a singly list: you need the node before
 *    it, and a singly node cannot look backwards. A doubly node can (prev).
 *
 *
 * ============================================================================
 *  8. LINKED LIST vs ARRAY vs VECTOR vs DEQUE
 * ============================================================================
 *
 *   Feature                     array/vector     std::deque     std::list /
 *                                                               std::forward_list
 *   --------------------------  ---------------  -------------  --------------------
 *   Memory layout               contiguous       chunked        scattered nodes
 *   Random access               O(1)             O(1)           O(n)
 *   Insert / erase at front     O(n)             O(1)           O(1)
 *   Insert / erase at back      O(1) amortised   O(1)           O(1)
 *   Insert / erase in middle    O(n)             O(n)           O(1) given an iterator
 *   Memory overhead / element   none             small          1 or 2 pointers + allocator
 *   Cache friendliness          excellent        good           poor
 *   Pointers / iterators after  invalidated on   mostly         stay valid (only the erased
 *     insert or erase           growth / shifts  invalidated    element's are invalidated)
 *
 *  STANDARD LIBRARY
 *      std::list          : a doubly linked list (commonly implemented as a ring
 *                           with a sentinel node).
 *      std::forward_list  : a singly linked list; smaller, forward-only.
 *
 *  PREFER A LINKED LIST WHEN
 *      - you hold positions (iterators / pointers) and insert or erase there often;
 *      - elements are large or expensive to move and you want to avoid copies;
 *      - pointers or iterators to elements must stay valid across changes;
 *      - you need to splice, move, or merge nodes by relinking (no element copies);
 *      - building blocks like an LRU cache (hash map + doubly linked list).
 *
 *  PREFER AN ARRAY / VECTOR WHEN
 *      - you need random access by index;
 *      - elements are small and traversal speed matters (cache locality);
 *      - memory overhead matters;
 *      - the size is stable or grows mainly at the back.
 *
 *  PRACTICAL ADVICE
 *    Default to vector. Choose a linked list when its specific strengths (stable
 *    references, O(1) relinking at known positions, cheap splicing) match the
 *    problem. In interviews, linked lists are about pointer manipulation skill.
 *
 *
 * ============================================================================
 *  9. REAL-WORLD USES
 * ============================================================================
 *
 *    - OS / kernel structures : the Linux kernel's list_head is a circular doubly
 *                               linked list used for tasks, queues and more.
 *    - Hash tables            : separate chaining keeps a short list per bucket.
 *    - LRU cache              : hash map + doubly linked list; moving a node to the
 *                               front and evicting the tail are both O(1).
 *    - Memory allocators      : free lists link the free blocks together.
 *    - File systems           : linked allocation (e.g. the FAT idea) chains the
 *                               disk blocks of a file.
 *    - Stacks and queues      : push/pop and enqueue/dequeue as O(1) list operations.
 *    - Graph adjacency lists  : the neighbours of each vertex.
 *    - Polynomials / sparse   : each non-zero term is a node.
 *      structures
 *    - Navigation features    : browser back/forward, undo/redo, music playlist
 *                               next/previous (doubly or circular lists).
 *    - Schedulers and games   : round-robin processes and turn order (circular).
 *    - Concept in blockchains : each block references the previous one, which is
 *                               conceptually a linked list.
 *
 *
 * ============================================================================
 *  10. CORE IDEAS TO MASTER (THE TOOLKIT)
 * ============================================================================
 *
 *    1. DRAW BEFORE YOU CODE. Sketch nodes, arrows, head and tail, and track each
 *       pointer through every step. Most bugs are visible on paper.
 *    2. NEVER LOSE THE HEAD. Walk with a copy (cur <- head), not with head itself.
 *    3. REWIRING ORDER. Wire the new node first, then update neighbours; unlink
 *       before delete; save a pointer before overwriting it.
 *    4. PREDECESSOR TRACKING. Deleting or inserting after a node needs the node
 *       BEFORE it. Keep a trailing pointer (prev) or stop one node early.
 *    5. DUMMY NODE. Place a throw-away node before the head so the first node is
 *       no longer a special case (the result is dummy.next).
 *    6. TWO POINTERS. A slow and a fast pointer find the middle and detect cycles;
 *       two pointers spaced k apart find the k-th node from the end.
 *    7. RECURSIVE VIEW. list = node + list. Base case: NULL.
 *    8. INVARIANTS. State what must stay true and check it after each operation.
 *    9. GUARD EVERY DEREFERENCE. Before cur.next, check cur != NULL; before
 *       cur.next.next, check both. The pattern  while (cur && cur.next)  is
 *       everywhere in list code.
 *   10. COUNT-BOUNDED vs NULL-BOUNDED LOOPS. Linear lists stop at NULL; circular
 *       lists stop by count or by returning to the start.
 *
 *
 * ============================================================================
 *  11. COMMON PITFALLS
 * ============================================================================
 *
 *   Pitfall                                   Symptom                  Fix
 *   ----------------------------------------  -----------------------  ---------------------
 *   Dereferencing NULL (cur.next.data)        crash                    guard with a check
 *   Losing the head                           leak, list vanishes      walk with a copy
 *   Forgetting to advance the tail            only last value kept     tail <- tail.next
 *   Forgetting tail on first / last insert    crash on later push      set head AND tail
 *   Overwriting a pointer before saving it    rest of list lost        save, then overwrite
 *   Using a node after delete                 undefined behaviour      save next first
 *   Passing head by value to a modifier       caller's head unchanged  return or use Node*&
 *   Updating next but not prev (doubly)       broken backward walk     fix all four links
 *   Accidental cycle (bad rewiring)           infinite loop            draw and re-check
 *   Off-by-one in index loops                 wrong node / crash       test index 0, size-1
 *   Modifying while traversing                skipped or missed nodes  save next first
 *   Leaking on early return / exception       memory not freed         free or use RAII
 *
 *
 * ============================================================================
 *  12. EDGE CASE CHECKLIST (test every list operation against these)
 * ============================================================================
 *
 *    [ ] Empty list                      (head == NULL)
 *    [ ] Exactly one node                (head.next == NULL)
 *    [ ] Exactly two nodes               (smallest case with a distinct head and tail)
 *    [ ] First node (head) affected
 *    [ ] Last node (tail) affected
 *    [ ] Middle node affected
 *    [ ] Invalid index                   (negative, or >= size)
 *    [ ] Duplicate values                (first match? all matches?)
 *    [ ] Value not found
 *    [ ] Very long list                  (loop vs recursion depth, performance)
 *    [ ] Cycle present                   (loop bounds; detection)
 *    [ ] Head / tail / size updated      (every path, including early returns)
 *
 *
 * ============================================================================
 *  13. ROADMAP: ZERO TO GRANDMASTER
 * ============================================================================
 *
 *   LEVEL 0  Prerequisites     pointers, address, dereference, new / delete,
 *                              references          -> 00_POINTER_BASICS_REVISION
 *   LEVEL 1  Foundations       this file; node and singly / doubly / circular lists
 *                              -> 01_Singly ... 03_Circular, 04_Traversal_And_Counting,
 *                                 05_Memory_Layout_And_LL_Class
 *   LEVEL 2  Basic operations  insert, delete, search, update, length, edge cases
 *                              -> 02_Basic_Operations
 *   LEVEL 3  Core patterns     reversal, slow / fast pointers, merge and sort,
 *                              dummy node, structural modification
 *                              -> 03_Reversal_Patterns, 04_Fast_Slow_Pointer_Techniques,
 *                                 05_Merge_And_Sort_Patterns, and the folders after them
 *   LEVEL 4  Advanced          LRU cache, copy list with random pointer, flatten a
 *                              multilevel list, k-group reversal, cycle start,
 *                              intersection of two lists
 *   LEVEL 5  Grandmaster       skip list, XOR list, unrolled list, array-based
 *                              lists, memory-efficient and cache-aware designs,
 *                              iterative destructors, proofs of Floyd's algorithm
 *
 *
 * ============================================================================
 *  14. GLOSSARY
 * ============================================================================
 *
 *    Node          one element of the list: data plus one or more pointers.
 *    Link          a pointer connecting two nodes.
 *    next          pointer to the following node.
 *    prev          pointer to the preceding node (doubly lists).
 *    Head          pointer to the first node; the list's entry point.
 *    Tail          pointer to (or the identity of) the last node.
 *    NULL          the null pointer: "points to nothing".
 *    Successor     the node after a given node.   Predecessor: the node before it.
 *    Traversal     visiting the nodes in order by following links.
 *    Pointer chasing  loading a node only to learn where the next one is.
 *    Sentinel / dummy node   a placeholder node that holds no real data.
 *    Self-referential struct a struct containing a pointer to its own type.
 *    Circular list a list whose last node links back to the first.
 *    Cycle         a link path that loops back to an earlier node.
 *    Dangling pointer    a pointer to memory that has been freed.
 *    Memory leak   allocated memory that can no longer be reached or freed.
 *    Invariant     a condition that must hold after every operation.
 *
 *
 * ============================================================================
 *  15. QUICK REVISION Q&A AND KEY TAKEAWAYS
 * ============================================================================
 *
 *  Q1  What is a linked list?
 *      Nodes connected by pointers; order is defined by links, not by memory
 *      position. Accessed through the head.
 *  Q2  Why can't a node contain another node of the same type?
 *      The size would be infinite. It holds a POINTER (fixed size) instead.
 *  Q3  What does the last node's next hold?
 *      NULL in a linear list; the head in a circular list.
 *  Q4  What is head, and why must it never be lost?
 *      The only entry point. Losing it makes every node unreachable (a leak).
 *  Q5  Why is access by index O(n) in a linked list?
 *      There is no address formula; you must follow i links from the head.
 *  Q6  Is linked list insertion O(1)?
 *      Only if you already hold the position. Finding it is O(n).
 *  Q7  Why is pop_back O(n) in a singly list but O(1) in a doubly list?
 *      You need the second-to-last node: singly must walk to find it, doubly has
 *      tail.prev.
 *  Q8  Why are linked lists often slower than vectors even when Big-O says
 *      otherwise?
 *      Scattered nodes cause cache misses and pointer chasing; arrays are
 *      contiguous and prefetch well.
 *  Q9  How do you avoid memory leaks in a list class?
 *      One owner, a destructor that frees every node (saving next before each
 *      delete), and no accidental copies.
 *  Q10 When do you choose a linked list over a vector?
 *      Stable iterators / references, frequent relinking at known positions,
 *      large elements, splicing, LRU-style structures.
 *  Q11 Why use a dummy node?
 *      It makes the head a normal node, removing "is this the first node?" cases.
 *  Q12 How do you know a list is circular?
 *      Following next from the head returns to the head; no node is NULL.
 *
 *  KEY TAKEAWAYS
 *    - Linked list = nodes + links. A node has data, next, and (doubly) prev.
 *    - Order lives in the links, so nodes can be anywhere; insert and delete just
 *      rewire pointers.
 *    - You lose O(1) indexing and cache locality; you gain cheap restructuring and
 *      stable references.
 *    - Four main types: singly, doubly, circular singly, circular doubly. Variants:
 *      sentinel, XOR, unrolled, skip, multilevel.
 *    - Head is the entry point: never lose it. Walk with a copy.
 *    - Order of pointer updates matters; save before you overwrite; unlink before
 *      you delete.
 *    - Always test: empty, one node, two nodes, head, tail, middle, invalid index.
 *    - Draw it first, then code it.
 *
 *  Related files
 *      Previous : 00_POINTER_BASICS_REVISION.cpp
 *      Next     : 01_Singly_Linked_List_Node.cpp
 *                 02_Doubly_Linked_List_Node.cpp
 *                 03_Circular_Linked_List.cpp
 *      Code     : 13_Linked_List_Implementation/
 */

// Notes-only file. Empty main() keeps the file buildable as a standalone target.
int main() {
    return 0;
}