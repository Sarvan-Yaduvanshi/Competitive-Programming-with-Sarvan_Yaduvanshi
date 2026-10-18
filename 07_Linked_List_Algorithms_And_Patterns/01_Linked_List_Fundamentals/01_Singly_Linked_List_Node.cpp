/*
 * Author  : Sarvan Yaduvanshi
 * Created : 2026-10-17
 *
 * ============================================================================
 *  SINGLY LINKED LIST  -  NOTES + PSEUDOCODE
 *  Folder : 01_Linked_List_Fundamentals
 *  Level  : Basic -> Expert (definition, comparison, every operation, edge cases)
 * ============================================================================
 *
 *  HOW EACH OPERATION IS EXPLAINED
 *      IDEA -> DRY RUN (worked example) -> PSEUDOCODE -> EDGE CASES -> COMPLEXITY
 *
 *  PSEUDOCODE LEGEND
 *      a <- b      assign b to a            NULL   the null pointer (nullptr)
 *      p.next      next field of the node p points to  (p->next in C++)
 *
 *  CONTENTS
 *    1. What is a singly linked list?
 *    2. Singly linked list vs array vs doubly linked list
 *    3. Design of the implementation (what the class stores and why)
 *    4. Operations, step by step
 *         4.1  push_front          4.7   search_ll
 *         4.2  push_back           4.8   getElementAtIndex
 *         4.3  pop_front           4.9   print
 *         4.4  pop_back            4.10  size
 *         4.5  insert_middle       4.11  destructor + deleted copy
 *         4.6  deleteAtIndex
 *    5. Edge case master table
 *    6. Common bugs and how to avoid them
 *    7. Complexity summary
 *    8. Full dry run
 *    9. Key takeaways
 *
 *
 * ============================================================================
 *  1. WHAT IS A SINGLY LINKED LIST?
 * ============================================================================
 *
 *  DEFINITION
 *    A singly linked list (SLL) is a linear data structure made of nodes
 *    connected in ONE direction. Every node stores two things:
 *
 *        +------+------+
 *        | data | next |
 *        +------+------+
 *
 *      data : the value stored in the node
 *      next : pointer to the following node (NULL for the last node)
 *
 *    The list keeps a pointer to the first node (head). In this implementation
 *    it also keeps a pointer to the last node (tail) and the element count
 *    (_size). You can only move FORWARD (head -> tail): a node knows its
 *    successor but not its predecessor.
 *
 *            head                              tail
 *             |                                  |
 *             v                                  v
 *           [ 5 ] --> [ 10 ] --> [ 15 ] --> [ 20 ] --> NULL
 *
 *  Nodes are NOT stored side by side in memory (unlike an array). Each lives at
 *  an arbitrary heap address and is connected only by its next pointer.
 *
 *  CONCRETE EXAMPLE (addresses are made up)
 *
 *      address 0x100 : [ data=10 | next=0x200 ]
 *      address 0x200 : [ data=20 | next=0x300 ]
 *      address 0x300 : [ data=30 | next=NULL  ]
 *
 *      head = 0x100,  tail = 0x300,  size = 3
 *      Walk : 0x100 -> 0x200 -> 0x300 -> NULL     (prints 10, 20, 30)
 *
 *      An empty list has head == NULL and tail == NULL.
 *      A one-node list has head == tail and head.next == NULL.
 *
 *  INVARIANTS  (facts that must be true after EVERY operation)
 *    S1. Empty list      : head == NULL, tail == NULL, size == 0.
 *    S2. Non-empty list  : tail.next == NULL, and following next from head
 *                          reaches tail after exactly size - 1 steps.
 *    S3. One node        : head == tail exactly when size == 1.
 *    S4. Size is exact   : size equals the number of nodes reachable from head.
 *    S5. No cycles       : following next never returns to an earlier node.
 *
 *    Almost every linked list bug is one of these invariants being broken. When
 *    you design an operation, ask: "Which invariants can this break, and which
 *    pointers must I fix to restore them?"
 *
 *  REAL-WORLD USES
 *    Stacks and queues, hash table chaining (a short list per bucket), graph
 *    adjacency lists, polynomial terms, memory-allocator free lists, and any
 *    place where cheap insert/delete at the front matters and backward movement
 *    is not needed.
 *
 *
 * ============================================================================
 *  2. SINGLY LINKED LIST vs ARRAY vs DOUBLY LINKED LIST
 * ============================================================================
 *
 *   Feature                    Array / vector     Singly (head+tail)  Doubly (head+tail)
 *   -------------------------  -----------------  ------------------  ------------------
 *   Memory layout              contiguous         scattered nodes     scattered nodes
 *   Access by index            O(1)               O(n)                O(n)
 *   Insert / delete at front   O(n) (shift)       O(1)                O(1)
 *   Insert at back             O(1) amortised     O(1)                O(1)
 *   Delete at back             O(1)               O(n)                O(1)
 *   Delete a known node        O(n)               O(n)                O(1)
 *   Traversal direction        either             forward only        forward and backward
 *   Node size (typical 64-bit) 4 bytes per int    16 bytes            24 bytes
 *   Pointers updated, middle   -                  2                   4
 *     insert
 *   Cache friendliness         excellent          poor                poor
 *
 *  WHY pop_back IS O(n) IN A SINGLY LIST
 *    To remove the last node, the SECOND-TO-LAST node must become the new tail.
 *    A singly node cannot look backwards, so you walk from head until
 *    node.next == tail. A doubly list reads tail.prev in one step.
 *
 *  WHEN TO CHOOSE A SINGLY LIST
 *    You only move forward, memory per node matters, and most work happens at
 *    the front (stack) or back (queue with a tail pointer). Choose a doubly list
 *    when you need backward moves or O(1) removal from the back or of a known node.
 *
 *
 * ============================================================================
 *  3. DESIGN OF THE IMPLEMENTATION
 * ============================================================================
 *
 *  Members
 *    head   : pointer to the first node (NULL when empty)
 *    tail   : pointer to the last node  (NULL when empty)
 *    _size  : cached element count
 *
 *  Why these choices
 *    - tail pointer  : makes push_back O(1). Without it every append walks the
 *                      whole list (O(n), and O(n^2) to build n elements).
 *    - _size cache   : bounds checks (pos < 0 || pos > size) cost O(1) instead of
 *                      walking the list to count.
 *    - private Node  : callers never touch raw pointers, so they cannot break the
 *                      invariants from outside.
 *    - explicit Node(int) : next starts as NULL, never garbage, and an int cannot
 *                      silently convert into a Node.
 *    - exceptions    : empty pop -> std::underflow_error, bad index ->
 *                      std::out_of_range. A silent return or a magic value such as
 *                      -1 hides errors (and -1 could be real data).
 *    - const methods : search_ll, getElementAtIndex, print and size do not modify
 *                      the list, so they are const and use const Node* walkers.
 *    - deleted copy  : see 4.11.
 *
 *  POINTER-ORDER RULE (the most important habit)
 *    1. Create the new node (its next starts as NULL).
 *    2. Wire the NEW node first, then update the neighbour that points to it.
 *    3. Never overwrite a pointer before saving what it pointed to.
 *    4. Unlink a node BEFORE deleting it, and never read it after delete.
 *
 *
 * ============================================================================
 *  4. OPERATIONS
 * ============================================================================
 *
 * ----------------------------------------------------------------------------
 *  4.1  push_front(val)  -  insert at the front
 * ----------------------------------------------------------------------------
 *  IDEA
 *    The new node becomes the head. Its next is the old head. If the list was
 *    empty, the new node is both head AND tail.
 *
 *  DRY RUN 1   list: 10 -> 20,   push_front(5)
 *      start    : head -> [10] -> [20] -> NULL         tail -> [20]
 *      newNode  : [5 | NULL]
 *      step 1   : newNode.next = head          [5] -> [10]
 *      step 2   : head = newNode               head -> [5]
 *      result   : head -> [5] -> [10] -> [20] -> NULL   tail still [20]   size = 3
 *
 *  DRY RUN 2   list: empty,   push_front(7)
 *      head == NULL, so head = tail = newNode.
 *      result   : head, tail -> [7] -> NULL      size = 1
 *
 *  PSEUDOCODE
 *      PUSH_FRONT(val):
 *          newNode <- Node(val)                 // next = NULL
 *          if head == NULL:                     // case 1: empty list
 *              head <- newNode
 *              tail <- newNode                  // tail must be set too
 *          else:                                // case 2: non-empty list
 *              newNode.next <- head             // 1. wire new node forward
 *              head         <- newNode          // 2. move head
 *          size <- size + 1
 *
 *  EDGE CASES HANDLED
 *    - Empty list      : head AND tail both become newNode (forgetting tail makes
 *                        the next push_back crash).
 *    - Single node     : handled by the else branch; tail is unchanged.
 *    - Tail unchanged  : in a non-empty list push_front never moves the tail.
 *    - Allocation fail : "new" runs first. If it throws, nothing has been
 *                        modified and the list stays valid.
 *  COMPLEXITY : Time O(1) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  4.2  push_back(val)  -  insert at the back
 * ----------------------------------------------------------------------------
 *  IDEA
 *    The old tail's next points to the new node, and the new node becomes the
 *    tail. The tail pointer is what makes this O(1).
 *
 *  DRY RUN 1   list: 10 -> 20,   push_back(30)
 *      start    : head -> [10] -> [20] -> NULL         tail -> [20]
 *      newNode  : [30 | NULL]
 *      step 1   : tail.next = newNode          [20] -> [30]
 *      step 2   : tail = newNode               tail -> [30]
 *      result   : head -> [10] -> [20] -> [30] -> NULL   size = 3
 *
 *  DRY RUN 2   list: empty,   push_back(10)
 *      head == NULL, so head = tail = newNode.      result: [10] -> NULL, size = 1
 *
 *  PSEUDOCODE
 *      PUSH_BACK(val):
 *          newNode <- Node(val)
 *          if head == NULL:                     // case 1: empty list
 *              head <- newNode
 *              tail <- newNode
 *          else:                                // case 2: non-empty list
 *              tail.next <- newNode             // 1. old tail points to new node
 *              tail      <- newNode             // 2. move tail
 *          size <- size + 1
 *
 *  EDGE CASES HANDLED
 *    - Empty list  : head == tail == newNode.
 *    - Single node : else branch links the two nodes; head is unchanged.
 *    - Forgetting "tail <- newNode" makes every later append overwrite the same
 *      next slot, so only the last value survives.
 *  COMPLEXITY : Time O(1) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  4.3  pop_front()  -  remove from the front
 * ----------------------------------------------------------------------------
 *  IDEA
 *    Save the head, move head to head.next, free the old head. If the list
 *    became empty, reset tail too.
 *
 *  DRY RUN 1   list: 5 -> 10 -> 20,   pop_front()
 *      temp = head = [5]
 *      head = head.next = [10]
 *      head != NULL, so tail is untouched
 *      delete [5]
 *      result   : head -> [10] -> [20] -> NULL      size = 2
 *
 *  DRY RUN 2   list: 15 (single node),   pop_front()
 *      temp = [15];  head = head.next = NULL
 *      head == NULL, so tail = NULL
 *      delete [15]
 *      result   : empty list (head = tail = NULL), size = 0
 *
 *  PSEUDOCODE
 *      POP_FRONT():
 *          if head == NULL:  throw underflow_error("empty")
 *          temp <- head                         // remember the node to free
 *          head <- head.next                    // move head forward
 *          if head == NULL:                     // the list became empty
 *              tail <- NULL
 *          delete temp
 *          size <- size - 1
 *
 *  EDGE CASES HANDLED
 *    - Empty list  : throws std::underflow_error, nothing changes.
 *    - Single node : head becomes NULL, so tail MUST be reset (invariant S1);
 *                    otherwise tail dangles at freed memory.
 *    - Two or more : only head changes; tail is unchanged.
 *  COMPLEXITY : Time O(1) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  4.4  pop_back()  -  remove from the back
 * ----------------------------------------------------------------------------
 *  IDEA
 *    The new tail is the SECOND-TO-LAST node. Walk from head until
 *    temp.next == tail, free the old tail, make temp the tail, and cut its next.
 *    A single node is special: both head and tail are cleared.
 *
 *  DRY RUN 1   list: 5 -> 10 -> 20,   pop_back()     (tail = [20])
 *      temp = head = [5]
 *      [5].next  = [10] != tail  -> temp = [10]
 *      [10].next = [20] == tail  -> stop
 *      delete tail [20]
 *      tail = temp = [10]
 *      tail.next = NULL
 *      result   : head -> [5] -> [10] -> NULL       tail -> [10]     size = 2
 *
 *  DRY RUN 2   list: 15 (single node),   pop_back()
 *      head == tail, so delete head; head = tail = NULL
 *      result   : empty list, size = 0
 *
 *  PSEUDOCODE
 *      POP_BACK():
 *          if head == NULL:  throw underflow_error("empty")
 *          if head == tail:                     // single node
 *              delete head
 *              head <- NULL
 *              tail <- NULL
 *          else:                                // two or more nodes
 *              temp <- head
 *              while temp.next != tail:         // stop at the second-to-last node
 *                  temp <- temp.next
 *              delete tail
 *              tail      <- temp
 *              tail.next <- NULL                // cut the dangling link
 *          size <- size - 1
 *
 *  EDGE CASES HANDLED
 *    - Empty list      : throws std::underflow_error.
 *    - Single node     : head AND tail cleared; the node is deleted ONCE.
 *    - Two nodes       : temp stays at head (head.next == tail at once); head
 *                        becomes both head and tail.
 *    - tail.next = NULL: without it the new tail still points at freed memory.
 *  COMPLEXITY : Time O(n) (the walk) | Space O(1)
 *    (This is the one end operation a singly list cannot make O(1).)
 *
 * ----------------------------------------------------------------------------
 *  4.5  insert_middle(val, pos)  -  insert at a given index
 * ----------------------------------------------------------------------------
 *  IDEA
 *    Validate 0 <= pos <= size. Then three cases:
 *      1. pos == 0     -> new head
 *      2. pos == size  -> new tail
 *      3. otherwise    -> splice after the node at index pos - 1
 *
 *    A singly node cannot step back, so for the middle case you must stand on
 *    the node BEFORE the target index.
 *
 *  DRY RUN 1 (middle)   list: 5 -> 10 -> 20,   insert_middle(15, 2)
 *      pos = 2: not 0, and not size (3), so the middle case.
 *      prev = head = [5]; walk pos - 1 = 1 step  ->  prev = [10]
 *      newNode.next = prev.next = [20]      [15] -> [20]
 *      prev.next    = newNode               [10] -> [15]
 *      result   : 5 -> 10 -> 15 -> 20 -> NULL       size = 4   (tail still [20])
 *
 *  DRY RUN 2 (front, empty list)   list: empty,   insert_middle(7, 0)
 *      pos == 0: newNode.next = head (NULL); head = newNode;
 *      _size == 0, so tail = newNode too.
 *      result   : [7] -> NULL, head == tail, size = 1
 *
 *  DRY RUN 3 (back)   list: 5 -> 10,   insert_middle(20, 2)      (size = 2)
 *      pos == size: tail.next = newNode; tail = newNode.
 *      result   : 5 -> 10 -> 20 -> NULL       tail -> [20]
 *
 *  PSEUDOCODE
 *      INSERT_MIDDLE(val, pos):
 *          if pos < 0 or pos > size:  throw out_of_range("Invalid position")
 *          newNode <- Node(val)
 *
 *          if pos == 0:                                  // case 1 (checked FIRST)
 *              newNode.next <- head
 *              head         <- newNode
 *              if size == 0:  tail <- newNode            // list was empty
 *              size <- size + 1
 *              return
 *
 *          if pos == size:                               // case 2
 *              tail.next <- newNode
 *              tail      <- newNode
 *              size <- size + 1
 *              return
 *
 *          prev <- head                                  // case 3
 *          repeat (pos - 1) times:  prev <- prev.next    // prev is at index pos-1
 *          newNode.next <- prev.next                     // 1. wire the new node first
 *          prev.next    <- newNode                       // 2. then the predecessor
 *          size <- size + 1
 *
 *  EDGE CASES HANDLED
 *    - pos < 0 or pos > size : throws BEFORE allocating, so a bad index never leaks.
 *    - Empty list, pos == 0  : the only valid position. Case 1 is checked BEFORE
 *                              case 2 because on an empty list pos == size == 0,
 *                              and case 2 would dereference a NULL tail.
 *    - pos == size           : tail moves to the new node (a manual splice would
 *                              forget this).
 *    - Middle position       : 0 < pos < size, so size >= 2 and prev always exists;
 *                              head and tail do not change.
 *    - Signed vs unsigned    : pos is int, size is size_t. The code tests pos < 0
 *                              first, then casts, so a negative pos cannot wrap into
 *                              a huge unsigned number.
 *  COMPLEXITY : Time O(n) general, O(1) when pos is 0 or size | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  4.6  deleteAtIndex(pos)  -  remove the element at an index
 * ----------------------------------------------------------------------------
 *  IDEA
 *    Validate 0 <= pos < size. Then three cases:
 *      1. pos == 0         -> remove head
 *      2. pos == size - 1  -> remove tail (walk to the second-to-last node)
 *      3. otherwise        -> stand on the node BEFORE pos, bypass the target
 *
 *  DRY RUN 1 (middle)   list: 5 -> 10 -> 15 -> 20,   deleteAtIndex(1)
 *      pos = 1: not 0, and not size - 1 (3), so the middle case.
 *      prev = head = [5]; walk pos - 1 = 0 steps (stay)
 *      target = prev.next = [10]
 *      prev.next = target.next = [15]       5 -> 15
 *      delete [10]
 *      result   : 5 -> 15 -> 20 -> NULL       size = 3
 *
 *  DRY RUN 2 (tail)   list: 5 -> 15 -> 20,   deleteAtIndex(2)
 *      pos == size - 1: prev = head = [5]
 *      [5].next  = [15] != tail -> prev = [15]
 *      [15].next = [20] == tail -> stop
 *      delete tail [20]; tail = [15]; tail.next = NULL
 *      result   : 5 -> 15 -> NULL        tail -> [15]      size = 2
 *
 *  DRY RUN 3 (head, single node)   list: 9,   deleteAtIndex(0)
 *      temp = head = [9]; head = head.next = NULL
 *      head == NULL, so tail = NULL; delete [9]
 *      result   : empty list, size = 0
 *
 *  PSEUDOCODE
 *      DELETE_AT_INDEX(pos):
 *          if pos < 0 or pos >= size:  throw out_of_range("Invalid position")
 *
 *          if pos == 0:                                  // case 1
 *              temp <- head
 *              head <- head.next
 *              if head == NULL:  tail <- NULL            // list became empty
 *              delete temp
 *              size <- size - 1
 *              return
 *
 *          if pos == size - 1:                           // case 2
 *              prev <- head
 *              while prev.next != tail:  prev <- prev.next
 *              delete tail
 *              tail      <- prev
 *              tail.next <- NULL
 *              size <- size - 1
 *              return
 *
 *          prev <- head                                  // case 3
 *          repeat (pos - 1) times:  prev <- prev.next
 *          target    <- prev.next
 *          prev.next <- target.next                      // unlink first
 *          delete target                                 // delete last
 *          size <- size - 1
 *
 *  EDGE CASES HANDLED
 *    - Empty list           : pos >= size (0 >= 0) is true, so it throws.
 *    - Single node, pos 0   : case 1 resets head AND tail. Case 1 is checked
 *                             BEFORE case 2, because with size 1 the index 0 equals
 *                             size - 1 and the tail walk would be wrong.
 *    - pos == size - 1      : case 2. Here size >= 2 (pos != 0), so the walk always
 *                             finds a second-to-last node.
 *    - Middle position      : size >= 3, so prev and target are both real nodes.
 *    - Dangling pointers    : prev is re-linked BEFORE the delete.
 *  COMPLEXITY : Time O(n) general, O(1) when pos is 0 | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  4.7  search_ll(key)  -  find the index of a value
 * ----------------------------------------------------------------------------
 *  IDEA
 *    Linear scan from head. Return the index of the FIRST node whose data equals
 *    key, or -1 if no node matches.
 *
 *  DRY RUN   list: 5 -> 15 -> 20
 *      search_ll(15) : idx 0: 5 != 15;  idx 1: 15 == 15  -> returns 1
 *      search_ll(20) : idx 0, idx 1 miss; idx 2: 20 == 20 -> returns 2
 *      search_ll(99) : all three miss, temp becomes NULL   -> returns -1
 *
 *  PSEUDOCODE
 *      SEARCH_LL(key):
 *          temp <- head
 *          idx  <- 0
 *          while temp != NULL:
 *              if temp.data == key:  return idx
 *              temp <- temp.next
 *              idx  <- idx + 1
 *          return -1
 *
 *  EDGE CASES HANDLED
 *    - Empty list      : head is NULL, the loop never runs, returns -1.
 *    - Duplicates      : returns the first (lowest) index.
 *    - Key at the tail : found on the last iteration.
 *    - const method    : it does not modify the list.
 *    - Why -1 is safe  : an INDEX is never negative, so -1 cannot be confused with
 *                        a real result (unlike returning a VALUE).
 *  COMPLEXITY : Time O(n) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  4.8  getElementAtIndex(idx)  -  read the value at an index
 * ----------------------------------------------------------------------------
 *  IDEA
 *    Validate the index, use the tail pointer for the last index, otherwise walk
 *    idx steps from head.
 *
 *  DRY RUN   list: 5 -> 15 -> 20 -> 25
 *      getElementAtIndex(3) : idx == size - 1  -> returns tail.data = 25  (O(1))
 *      getElementAtIndex(1) : temp = [5]; one step -> [15]  -> returns 15
 *      getElementAtIndex(0) : zero steps -> returns head.data = 5
 *      getElementAtIndex(4) : 4 >= size -> throws out_of_range
 *
 *  PSEUDOCODE
 *      GET_ELEMENT_AT_INDEX(idx):
 *          if idx < 0 or idx >= size:  throw out_of_range("Invalid index")
 *          if idx == size - 1:  return tail.data         // O(1) shortcut
 *          temp <- head
 *          repeat idx times:  temp <- temp.next
 *          return temp.data
 *
 *  EDGE CASES HANDLED
 *    - Empty list / idx >= size / idx < 0 : throws std::out_of_range.
 *    - Why throw and not return -1        : -1 may be a legitimate stored value, so
 *                                           the caller could not tell data from error.
 *    - First and last index               : O(1).
 *  COMPLEXITY : Time O(n) general, O(1) at the first or last index | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  4.9  print()
 * ----------------------------------------------------------------------------
 *  DRY RUN   list: 5 -> 15 -> 20            prints:  5 -> 15 -> 20 -> NULL
 *            empty list                     prints:  List is empty.
 *
 *  PSEUDOCODE
 *      PRINT():
 *          if head == NULL:  output "List is empty."; return
 *          temp <- head                         // copy: head must not move
 *          while temp != NULL:
 *              output temp.data, " -> "
 *              temp <- temp.next
 *          output "NULL"
 *
 *  EDGE CASES HANDLED
 *    - Empty list prints a message instead of nothing.
 *    - Walks with a copy, so head is never moved and the list stays reachable.
 *  COMPLEXITY : Time O(n) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  4.10  size()
 * ----------------------------------------------------------------------------
 *      SIZE():  return size            // cached counter, no traversal
 *  COMPLEXITY : Time O(1) | Space O(1)
 *  Every operation that adds or removes a node must update the counter.
 *
 * ----------------------------------------------------------------------------
 *  4.11  Destructor and deleted copy operations
 * ----------------------------------------------------------------------------
 *  DRY RUN   list: 5 -> 15 -> 20 goes out of scope
 *      ~List() calls pop_front() while head != NULL:
 *      pop [5], pop [15], pop [20]  ->  head = tail = NULL, size = 0
 *
 *  PSEUDOCODE
 *      DESTRUCTOR():
 *          while head != NULL:  POP_FRONT()
 *
 *  Every node came from "new", so the list must free them. Reusing pop_front is
 *  safe because it saves the next node, frees the old head, and resets tail when
 *  the list empties. Time O(n), space O(1).
 *
 *  COPY CONSTRUCTOR / COPY ASSIGNMENT  =  delete
 *    The default copy would copy only head, tail and _size, so TWO lists would own
 *    the SAME nodes. When both destructors run, each frees the same nodes: a double
 *    free (crash or corruption). The Rule of Three says: if you write a destructor,
 *    also handle copying. Forbidding copying is the simplest safe choice (the
 *    alternative is a deep copy that allocates new nodes).
 *
 *
 * ============================================================================
 *  5. EDGE CASE MASTER TABLE
 * ============================================================================
 *
 *  Always test an operation on: EMPTY, ONE NODE, TWO NODES, then a normal list.
 *
 *   Operation          Empty           One node          First / last        Middle
 *   -----------------  --------------  ----------------  ------------------  --------
 *   push_front         head = tail =   new -> old head;   -                   -
 *                      newNode         tail unchanged
 *   push_back          head = tail =   old tail -> new;   -                   -
 *                      newNode         tail moves
 *   pop_front          throws          head = tail =     move head           -
 *                                      NULL
 *   pop_back           throws          head = tail =     walk to second-     -
 *                                      NULL              to-last node
 *   insert_middle      only pos 0      pos 0 or 1 are    pos 0 / size use    walk to
 *                      valid; sets     boundary cases    head / tail logic   pos - 1
 *                      head and tail
 *   deleteAtIndex      throws          pos 0: head and   pos 0 / size - 1    bypass
 *                                      tail -> NULL      handled first       target
 *   search_ll          -1              one comparison    first match wins    -
 *   getElementAtIndex  throws          index 0 only      O(1) at the ends    walk idx
 *   print              prints message  one element       -                   -
 *   destructor         no-op           frees one node    -                   -
 *
 *  Invalid index (negative or too large) -> insert / delete / get throw
 *  std::out_of_range. Test pos < 0 BEFORE casting to size_t.
 *
 *
 * ============================================================================
 *  6. COMMON BUGS AND HOW TO AVOID THEM
 * ============================================================================
 *
 *   1. Forgetting tail when the first node is inserted.
 *        Symptom : push_back after push_front crashes.
 *        Fix     : in the empty branch set BOTH head and tail.
 *
 *   2. Not resetting tail when the list becomes empty (pop_front, deleteAtIndex).
 *        Symptom : tail points at freed memory; the next push_back writes to it.
 *        Fix     : after moving head, if head == NULL then tail = NULL.
 *
 *   3. Forgetting "tail = newNode" in push_back.
 *        Symptom : only the last appended value survives.
 *        Fix     : move the tail after linking.
 *
 *   4. Deleting the single node twice in pop_back.
 *        Symptom : crash (double free).
 *        Fix     : handle head == tail first, delete exactly once.
 *
 *   5. Forgetting "tail.next = NULL" after pop_back.
 *        Symptom : the new tail still points at a freed node.
 *        Fix     : always cut the link after moving tail.
 *
 *   6. Overwriting a pointer before saving it.
 *        Example : prev.next = newNode first, then trying to read the old
 *                  prev.next: it is already lost, and the rest of the list with it.
 *        Fix     : newNode.next = prev.next FIRST, then prev.next = newNode.
 *
 *   7. Reading a node after delete.
 *        Symptom : undefined behaviour.
 *        Fix     : save what you need (next) before delete; unlink, then delete.
 *
 *   8. Checking pos == size before pos == 0.
 *        Symptom : NULL dereference when inserting into an empty list.
 *        Fix     : handle pos == 0 first.
 *
 *   9. Forgetting to update size.
 *        Symptom : bounds checks wrong; later operations throw or crash.
 *        Fix     : update size on every path, including early returns.
 *
 *  10. Comparing int with size_t.
 *        Symptom : a negative pos becomes a huge unsigned number.
 *        Fix     : test pos < 0 first, then static_cast<size_t>(pos).
 *
 *  11. Walking with head itself.
 *        Symptom : the list becomes unreachable (leak).
 *        Fix     : traverse with a copy (temp <- head).
 *
 *  12. Returning -1 or silently ignoring errors.
 *        Fix     : throw std::out_of_range or std::underflow_error.
 *
 *
 * ============================================================================
 *  7. COMPLEXITY SUMMARY   (n = number of elements, Space = auxiliary)
 * ============================================================================
 *
 *   Operation           Time                                   Space
 *   ------------------  -------------------------------------  ------
 *   push_front          O(1)                                   O(1)
 *   push_back           O(1)                                   O(1)
 *   pop_front           O(1)                                   O(1)
 *   pop_back            O(n)                                   O(1)
 *   insert_middle       O(n) general; O(1) at pos 0 or size    O(1)
 *   deleteAtIndex       O(n) general; O(1) at pos 0            O(1)
 *   search_ll           O(n)                                   O(1)
 *   getElementAtIndex   O(n) general; O(1) at first/last       O(1)
 *   print               O(n)                                   O(1)
 *   size                O(1)                                   O(1)
 *   destructor          O(n)                                   O(1)
 *
 *   Note: the list stores n nodes (16 bytes each on a typical 64-bit system), so
 *   total memory is O(n); the table above counts only the EXTRA space an
 *   operation needs.
 *
 *
 * ============================================================================
 *  8. FULL DRY RUN   (state after each operation)
 * ============================================================================
 *
 *   #   Operation              List                    Size  head  tail
 *   --  ---------------------  ----------------------  ----  ----  ----
 *   0   (start)                NULL                    0     NULL  NULL
 *   1   push_back(10)          10                      1     10    10
 *   2   push_back(20)          10 -> 20                2     10    20
 *   3   push_front(5)          5 -> 10 -> 20           3     5     20
 *   4   insert_middle(15, 2)   5 -> 10 -> 15 -> 20     4     5     20
 *   5   deleteAtIndex(1)       5 -> 15 -> 20           3     5     20
 *   6   search_ll(15)          returns 1               3     5     20
 *   7   getElementAtIndex(2)   returns 20              3     5     20
 *   8   pop_back()             5 -> 15                 2     5     15
 *   9   pop_front()            15                      1     15    15
 *  10   pop_back()             NULL                    0     NULL  NULL
 *  11   pop_front()            throws underflow_error  0     NULL  NULL
 *
 *   Rows 9 and 10 are the single-node and become-empty transitions, where most
 *   bugs hide.
 *
 *
 * ============================================================================
 *  9. KEY TAKEAWAYS
 * ============================================================================
 *
 *   - A singly node is data + next. Order lives in the next pointers, so nodes
 *     can be anywhere in memory.
 *   - head + tail + size make push_front, push_back, pop_front and size O(1).
 *   - pop_back is O(n): a singly node cannot find its predecessor. That is the
 *     main reason to move to a doubly list.
 *   - Wire the new node first, then fix the neighbour. Unlink, then delete.
 *   - Empty and single-node lists are the edge cases that break most code: always
 *     set or clear BOTH head and tail.
 *   - Check pos == 0 before pos == size (insert) and pos == 0 before
 *     pos == size - 1 (delete).
 *   - Validate indexes (including negatives) before touching any pointer.
 *   - Walk with a copy of head, never head itself.
 *   - Own raw memory? Provide a destructor and forbid or deep-copy on copy.
 *
 *   Related files
 *     Foundations          : Linked_List_Fundamentals.cpp
 *     Full implementation  : 13_Linked_List_Problem_Solving/
 *                            02_Implementation_on_Singly_Linked_List.cpp
 *     Next notes           : 02_Doubly_Linked_List_Node.cpp
 */

// Notes-only file. Empty main() keeps the file buildable as a standalone target.
int main() {
    return 0;
}