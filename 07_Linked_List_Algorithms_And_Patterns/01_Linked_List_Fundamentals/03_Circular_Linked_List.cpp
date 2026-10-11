/*
 * Author  : Sarvan Yaduvanshi
 * Created : 2026-10-10
 *
 * ============================================================================
 *  CIRCULAR LINKED LIST (SINGLY + DOUBLY)  -  NOTES + PSEUDOCODE
 *  Folder : 01_Linked_List_Fundamentals
 *  Level  : Basic -> Expert (definition, comparison, every operation, edge cases)
 * ============================================================================
 *
 *  CONTENTS
 *    0. What is a circular linked list?  (definition, examples, linear vs circular)
 *    1. Circular Singly Linked List
 *         1.1  Structure and design        1.10 getElementAtIndex
 *         1.2  Invariants                  1.11 getFront / getBack
 *         1.3  push_front                  1.12 removeFirstOccurrence
 *         1.4  push_back                   1.13 reverse
 *         1.5  pop_front                   1.14 rotate
 *         1.6  pop_back                    1.15 print
 *         1.7  insert_middle               1.16 size / isEmpty
 *         1.8  deleteAtIndex               1.17 clear
 *         1.9  search_ll                   1.18 destructor + deleted copy
 *                                          1.19 dry run
 *    2. Circular Doubly Linked List
 *         2.1  Structure and design        2.10 insert_middle
 *         2.2  Invariants                  2.11 deleteAtIndex
 *         2.3  insert_before (helper)      2.12 search_ll / getElementAtIndex
 *         2.4  unlink (helper)             2.13 removeFirstOccurrence
 *         2.5  node_at (helper)            2.14 reverse
 *         2.6  push_front                  2.15 rotate
 *         2.7  push_back                   2.16 print / printReverse
 *         2.8  pop_front                   2.17 clear
 *         2.9  pop_back                    2.18 dry run
 *         2.19 Circular singly vs circular doubly (comparison)
 *    3. Traversal Patterns
 *    4. Detecting a Circular List  (and finding / removing the cycle)
 *    5. Use Cases
 *    6. Edge case master table
 *    7. Common bugs and how to avoid them
 *    8. Complexity summary (all four list types)
 *    9. Key takeaways
 *
 *
 * ============================================================================
 *  0. WHAT IS A CIRCULAR LINKED LIST?
 * ============================================================================
 *
 *  DEFINITION
 *    A circular linked list is a linked list in which the last node points
 *    back to the first node instead of NULL. The chain of nodes forms a ring:
 *    starting at any node and following next pointers eventually returns to
 *    that same node. In a non-empty circular list NO node has a NULL link.
 *
 *    There are two common variants:
 *      - Circular SINGLY linked list : each node has next; tail.next == head.
 *      - Circular DOUBLY linked list : each node has prev and next;
 *                                      tail.next == head AND head.prev == tail.
 *
 *    Circular singly (stores only tail):
 *
 *            head                tail
 *             |                   |
 *            [5] -> [10] -> [15] -> [20] --+
 *             ^                            |
 *             +----------------------------+
 *
 *    Circular doubly (stores only head, tail is head.prev):
 *
 *               +----------------------------------------+
 *               v                                        |
 *             head                                      tail
 *              [5] <-> [10] <-> [15] <-> [20]
 *               |                                        ^
 *               +----------------------------------------+
 *
 *  CONCRETE EXAMPLE (circular singly, addresses are made up)
 *
 *      address 0x100 : [ 10 | next=0x200 ]
 *      address 0x200 : [ 20 | next=0x300 ]
 *      address 0x300 : [ 30 | next=0x100 ]     <- points BACK to the first node
 *
 *      tail = 0x300,  head = tail.next = 0x100,  size = 3
 *      Walk from head: 0x100 -> 0x200 -> 0x300 -> 0x100 -> 0x200 ...  (never ends)
 *
 *      A one-node circular list points to itself:  [ 7 | next=self ]
 *
 *  KEY CONSEQUENCE : THERE IS NO NULL TO STOP AT
 *    In a linear list you loop "while (cur != NULL)". In a circular list that
 *    loop never ends. Every traversal must stop by (a) a counter, (b) coming
 *    back to a start node, or (c) reaching the tail. See Section 3.
 *
 *  LINEAR vs CIRCULAR
 *
 *   Feature                     Linear list                Circular list
 *   --------------------------  -------------------------  -------------------------
 *   Last node link              NULL                       head (back to the start)
 *   Traversal end condition     cur == NULL                counter, or cur == start
 *   Reach head from tail        O(n) (singly) or via prev  O(1): tail.next
 *   Singly: push_back with      needs a tail pointer       needs a tail pointer; with
 *     ONE stored pointer        (head alone gives O(n))    ONLY tail you get BOTH ends
 *   Rotate the list             relink both ends           move one pointer
 *   Concatenate two lists       O(1) with tail pointers    O(1), swap two next links
 *   Risk                        NULL dereference           infinite loop
 *   Natural fit                 ordinary sequences         repeating / cyclic processes
 *
 *  REAL-WORLD EXAMPLES
 *    - Round-robin CPU scheduling : processes take turns, then the first runs again.
 *    - Multiplayer turn order     : after the last player, play returns to the first.
 *    - Music "repeat all"         : the playlist wraps from the last song to the first.
 *    - Josephus problem           : people in a circle, every k-th one is removed.
 *    - Token ring networks        : a token circulates among stations.
 *    - OS / kernel structures     : the Linux kernel list_head is a circular doubly
 *                                   linked list; Fibonacci heaps keep their root list
 *                                   as a circular doubly linked list.
 *    More detail in Section 5.
 *
 *
 * ============================================================================
 *  1. CIRCULAR SINGLY LINKED LIST
 * ============================================================================
 *
 * ----------------------------------------------------------------------------
 *  1.1  STRUCTURE AND DESIGN
 * ----------------------------------------------------------------------------
 *    Node    : data, next
 *    Members : tail   (pointer to the LAST node; NULL when empty)
 *              _size  (cached element count)
 *    The head is never stored. It is always  head = tail.next.
 *
 *  WHY STORE ONLY THE TAIL (not the head)?
 *    With a tail pointer you reach BOTH ends in O(1):
 *        last element  = tail
 *        first element = tail.next
 *    Therefore push_front, push_back, pop_front, getFront and getBack are all
 *    O(1). If you stored only the head, push_back would need O(n) to find the
 *    last node. Storing both head and tail also works but is redundant: one
 *    pointer already encodes both, and there are fewer pointers to keep in sync.
 *
 *  WHY CACHE _size?
 *    Traversal loops are bounded by "repeat size times" instead of a NULL check
 *    (there is no NULL). The cached size also makes index validation O(1).
 *
 *  OTHER DESIGN CHOICES
 *    - Node is private so callers cannot break the circle from outside.
 *    - Errors are exceptions (underflow_error, out_of_range, invalid_argument),
 *      never silent returns or a magic -1 for values.
 *    - Copy constructor and copy assignment are deleted (see 1.18).
 *
 * ----------------------------------------------------------------------------
 *  1.2  INVARIANTS  (must hold after EVERY operation)
 * ----------------------------------------------------------------------------
 *    C1. Empty list        : tail == NULL and size == 0.
 *    C2. Non-empty list    : tail.next is the head. No node has next == NULL.
 *    C3. Single node       : tail.next == tail (the node points to itself).
 *    C4. Closed ring       : starting at the head and following next exactly
 *                            size times returns to the head.
 *    C5. Size is exact     : size equals the number of nodes in the ring.
 *
 *    Every edge case below is "which invariant could this break, and what do I
 *    fix to restore it?"
 *
 * ----------------------------------------------------------------------------
 *  1.3  push_front(val)  -  insert at the front
 * ----------------------------------------------------------------------------
 *  IDEA
 *    The new node must come right after the tail (that is what "head" means).
 *    Insert it between tail and the old head. The TAIL DOES NOT CHANGE: the
 *    last node is still the same node, only its next pointer now points to a
 *    different first node.
 *
 *  PSEUDOCODE
 *      PUSH_FRONT(val):
 *          newNode <- Node(val)
 *          if tail == NULL:                   // empty list
 *              newNode.next <- newNode        // a lone node points to itself
 *              tail <- newNode
 *          else:
 *              newNode.next <- tail.next      // 1. new node points to old head
 *              tail.next    <- newNode        // 2. tail points to new head
 *          size <- size + 1
 *
 *  EXAMPLE   list: 10 -> 20 (tail = 20),   push_front(5)
 *      before : tail=[20],  head=tail.next=[10]
 *      step 1 : [5].next  = [10]          5 -> 10
 *      step 2 : [20].next = [5]           20 -> 5   (tail now points to new head)
 *      result : 5 -> 10 -> 20 -> (back to 5)       tail still [20]     size = 3
 *
 *  EDGE CASES HANDLED
 *    - Empty list     : newNode.next = newNode creates the self-loop (C3).
 *                       Forgetting it leaves next == NULL and crashes later.
 *    - Single node    : else branch gives  new -> old -> (back to new);
 *                       tail stays the old node.
 *    - Tail unchanged : do not move tail in push_front.
 *  COMPLEXITY : Time O(1) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  1.4  push_back(val)  -  insert at the back
 * ----------------------------------------------------------------------------
 *  IDEA
 *    Identical pointer surgery to push_front, but the new node also becomes
 *    the tail. In other words: push_back = push_front + move tail.
 *
 *  PSEUDOCODE
 *      PUSH_BACK(val):
 *          newNode <- Node(val)
 *          if tail == NULL:
 *              newNode.next <- newNode        // self-loop
 *          else:
 *              newNode.next <- tail.next      // 1. new node points to the head
 *              tail.next    <- newNode        // 2. old tail points to new node
 *          tail <- newNode                    // 3. new node is the tail (both cases)
 *          size <- size + 1
 *
 *  EXAMPLE   list: 10 -> 20 (tail = 20),   push_back(30)
 *      step 1 : [30].next = [10]          30 -> head
 *      step 2 : [20].next = [30]          20 -> 30
 *      step 3 : tail = [30]
 *      result : 10 -> 20 -> 30 -> (back to 10)     size = 3
 *
 *  EDGE CASES HANDLED
 *    - Empty list  : self-loop, then tail = newNode (head == tail).
 *    - Single node : new node links to the old node as head; old node links to new.
 *  COMPLEXITY : Time O(1) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  1.5  pop_front()  -  remove from the front
 * ----------------------------------------------------------------------------
 *  IDEA
 *    The head is tail.next. Make the tail skip over it: tail.next = head.next.
 *    Then delete the old head.
 *
 *  PSEUDOCODE
 *      POP_FRONT():
 *          if tail == NULL:  throw underflow_error("empty")
 *          head <- tail.next
 *          if head == tail:                   // exactly one node
 *              tail <- NULL
 *          else:
 *              tail.next <- head.next         // skip the old head
 *          delete head
 *          size <- size - 1
 *
 *  EXAMPLE   list: 5 -> 10 -> 20 (tail = 20),   pop_front()
 *      head = [5]
 *      [20].next = [10]
 *      delete [5]
 *      result : 10 -> 20 -> (back to 10)           size = 2
 *
 *  EDGE CASES HANDLED
 *    - Empty list  : throws std::underflow_error.
 *    - Single node : head == tail, so tail becomes NULL (C1). Do not write
 *                    tail.next, the node is about to be deleted.
 *    - Two or more : only tail.next changes; tail pointer is unchanged.
 *  COMPLEXITY : Time O(1) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  1.6  pop_back()  -  remove from the back
 * ----------------------------------------------------------------------------
 *  IDEA
 *    The new tail must be the SECOND-TO-LAST node. A singly node cannot look
 *    backwards, so walk from the head until  prev.next == tail.  Then close
 *    the circle around the old tail and delete it.
 *
 *  PSEUDOCODE
 *      POP_BACK():
 *          if tail == NULL:  throw underflow_error("empty")
 *          if tail.next == tail:              // exactly one node
 *              delete tail
 *              tail <- NULL
 *          else:
 *              prev <- tail.next              // start at the head
 *              while prev.next != tail:       // stop BEFORE the tail
 *                  prev <- prev.next
 *              prev.next <- tail.next         // prev now points to the head
 *              delete tail
 *              tail <- prev
 *          size <- size - 1
 *
 *  EXAMPLE   list: 5 -> 10 -> 20 (tail = 20),   pop_back()
 *      prev = [5]  : 5.next  = 10 != 20 -> prev = [10]
 *      prev = [10] : 10.next == 20 -> stop
 *      [10].next = tail.next = [5]        closes the circle
 *      delete [20];  tail = [10]
 *      result : 5 -> 10 -> (back to 5)             size = 2
 *
 *  EDGE CASES HANDLED
 *    - Empty list     : throws std::underflow_error.
 *    - Single node    : delete once, tail = NULL.
 *    - Two nodes      : prev is the head; prev.next == tail immediately; then
 *                       prev.next = head makes the survivor a self-loop (C3).
 *    - THE CLASSIC BUG: writing  while (prev.next != NULL)  here. In a circular
 *                       list no node ever has next == NULL, so the loop never
 *                       stops (or walks forever around the ring).
 *  COMPLEXITY : Time O(n) | Space O(1)
 *    (This is the one end operation a circular SINGLY list cannot make O(1).
 *     The circular doubly list can, see 2.9.)
 *
 * ----------------------------------------------------------------------------
 *  1.7  insert_middle(val, pos)  -  insert at a given index
 * ----------------------------------------------------------------------------
 *  IDEA
 *    Validate 0 <= pos <= size. Boundary positions reuse existing operations;
 *    otherwise find the node BEFORE index pos and splice after it.
 *
 *  PSEUDOCODE
 *      INSERT_MIDDLE(val, pos):
 *          if pos < 0 or pos > size:  throw out_of_range("Invalid position")
 *          if pos == 0:     PUSH_FRONT(val); return
 *          if pos == size:  PUSH_BACK(val);  return
 *          prev <- tail.next                  // head, which is index 0
 *          repeat (pos - 1) times:
 *              prev <- prev.next              // now prev is at index pos-1
 *          newNode <- Node(val)
 *          newNode.next <- prev.next          // 1. wire the new node first
 *          prev.next    <- newNode            // 2. then the predecessor
 *          size <- size + 1
 *
 *  EXAMPLE   list: 5 -> 10 -> 20,   insert_middle(15, 2)
 *      prev starts at [5], walks pos-1 = 1 step -> [10]
 *      [15].next = [20]
 *      [10].next = [15]
 *      result : 5 -> 10 -> 15 -> 20 -> (back to 5)  size = 4
 *
 *  EDGE CASES HANDLED
 *    - pos < 0 or pos > size : throws before allocating (no leak).
 *    - Empty list            : only pos 0 is valid, handled by push_front.
 *    - pos == size           : push_back updates the TAIL; a manual splice would
 *                              forget to move it.
 *    - Middle positions      : 0 < pos < size, so tail does not change.
 *    - Signed vs unsigned    : test pos < 0 first, then cast to size_t.
 *  COMPLEXITY : Time O(n) general, O(1) at pos 0 or size | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  1.8  deleteAtIndex(pos)  -  remove the element at an index
 * ----------------------------------------------------------------------------
 *  PSEUDOCODE
 *      DELETE_AT_INDEX(pos):
 *          if pos < 0 or pos >= size:  throw out_of_range("Invalid position")
 *          if pos == 0:         POP_FRONT(); return
 *          if pos == size - 1:  POP_BACK();  return
 *          prev <- tail.next
 *          repeat (pos - 1) times:  prev <- prev.next
 *          target <- prev.next
 *          prev.next <- target.next           // unlink first
 *          delete target                      // delete last
 *          size <- size - 1
 *
 *  EXAMPLE   list: 5 -> 10 -> 15 -> 20,   deleteAtIndex(1)
 *      prev = [5], target = [10]
 *      [5].next = [15]
 *      delete [10]
 *      result : 5 -> 15 -> 20 -> (back to 5)       size = 3
 *
 *  EDGE CASES HANDLED
 *    - Empty list            : pos >= size is true, throws.
 *    - Single node, pos 0    : pop_front sets tail = NULL. pos == 0 is checked
 *                              BEFORE pos == size-1 (they are equal when size = 1).
 *    - Head / tail positions : delegated to pop_front / pop_back, which keep tail
 *                              and the closed ring correct.
 *    - Middle position       : size >= 3, so prev and target are real nodes.
 *  COMPLEXITY : Time O(n) general, O(1) at pos 0 | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  1.9  search_ll(key)  -  find the index of a value
 * ----------------------------------------------------------------------------
 *  PSEUDOCODE
 *      SEARCH(key):
 *          if tail == NULL:  return -1
 *          cur <- tail.next
 *          for i from 0 to size - 1:          // bounded by size, NOT by NULL
 *              if cur.data == key:  return i
 *              cur <- cur.next
 *          return -1
 *
 *  EXAMPLE   list: 5 -> 15 -> 20
 *      search(15) -> returns 1
 *      search(99) -> after 3 nodes, loop ends -> returns -1 (no infinite loop)
 *
 *  EDGE CASES HANDLED
 *    - Empty list : returns -1 immediately; tail.next would dereference NULL.
 *    - Duplicates : returns the first (lowest) index.
 *    - Not found  : the size bound stops the loop. A "while (cur != NULL)" loop
 *                   would run forever here.
 *  COMPLEXITY : Time O(n) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  1.10  getElementAtIndex(idx)
 * ----------------------------------------------------------------------------
 *  PSEUDOCODE
 *      GET_ELEMENT_AT_INDEX(idx):
 *          if idx < 0 or idx >= size:  throw out_of_range("Invalid index")
 *          if idx == size - 1:  return tail.data     // O(1) shortcut
 *          cur <- tail.next
 *          repeat idx times:  cur <- cur.next
 *          return cur.data
 *
 *  EDGE CASES HANDLED
 *    - Invalid index throws (a return of -1 could be real data).
 *    - Last index uses the tail pointer directly.
 *    - Index 0 takes zero steps from the head.
 *  COMPLEXITY : Time O(n) general, O(1) at first/last index | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  1.11  getFront() / getBack()
 * ----------------------------------------------------------------------------
 *      GET_FRONT():  if tail == NULL throw underflow_error;  return tail.next.data
 *      GET_BACK():   if tail == NULL throw underflow_error;  return tail.data
 *
 *  EDGE CASES : empty list throws; single node gives the same value for both.
 *  COMPLEXITY : Time O(1) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  1.12  removeFirstOccurrence(key)
 * ----------------------------------------------------------------------------
 *  IDEA
 *    Scan with two pointers: cur and its predecessor prev. A circular list has
 *    a free trick: the predecessor of the HEAD is the TAIL. So start with
 *    prev = tail, cur = head, and the head needs no special case.
 *
 *  PSEUDOCODE
 *      REMOVE_FIRST_OCCURRENCE(key):
 *          if tail == NULL:  return false
 *          prev <- tail
 *          cur  <- tail.next
 *          repeat size times:
 *              if cur.data == key:
 *                  if size == 1:
 *                      tail <- NULL                 // the only node
 *                  else:
 *                      prev.next <- cur.next        // bridge over cur
 *                      if cur == tail:
 *                          tail <- prev             // removed the tail
 *                  delete cur
 *                  size <- size - 1
 *                  return true
 *              prev <- cur
 *              cur  <- cur.next
 *          return false
 *
 *  EXAMPLE   list: 5 -> 10 -> 20 (tail = 20)
 *      remove 5  (head)  : prev=[20], cur=[5]  -> [20].next=[10]. Head is now 10.
 *      remove 20 (tail)  : prev=[10], cur=[20] -> [10].next=[5];  cur == tail so
 *                          tail = [10].
 *      remove 99         : whole ring scanned, returns false.
 *
 *  EDGE CASES HANDLED
 *    - Empty list         : returns false.
 *    - Single node match  : tail = NULL, then delete.
 *    - Head match         : prev = tail makes it identical to a middle removal.
 *    - Tail match         : tail must move to prev (otherwise tail dangles).
 *    - No match / duplicates : bounded loop, first occurrence only.
 *  COMPLEXITY : Time O(n) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  1.13  reverse()  -  reverse the list in place
 * ----------------------------------------------------------------------------
 *  IDEA
 *    Flip every next pointer so it points to the previous node. The first
 *    node's new "previous" is the old tail (it is the node before the head in
 *    the ring), so start with prev = tail. When every link is flipped the old
 *    head is the new tail.
 *
 *  PSEUDOCODE
 *      REVERSE():
 *          if tail == NULL or tail.next == tail:  return   // 0 or 1 node
 *          oldHead <- tail.next
 *          prev <- tail
 *          cur  <- oldHead
 *          do:
 *              nextNode <- cur.next        // save before overwriting
 *              cur.next <- prev            // flip the link
 *              prev     <- cur
 *              cur      <- nextNode
 *          while cur != oldHead            // stop after one full turn
 *          tail <- oldHead                 // old head is now the last node
 *
 *  EXAMPLE   list: 5 -> 10 -> 20 (tail = 20)
 *      oldHead=[5], prev=[20], cur=[5]
 *      pass 1 : next=[10]; 5.next=20;  prev=[5];  cur=[10]
 *      pass 2 : next=[20]; 10.next=5;  prev=[10]; cur=[20]
 *      pass 3 : next=[5];  20.next=10; prev=[20]; cur=[5]  -> stop
 *      tail = [5]
 *      result : head = tail.next = [20]:  20 -> 10 -> 5 -> (back to 20)
 *
 *  WHY do-while?  cur starts EQUAL to oldHead, so a plain "while (cur != oldHead)"
 *                 would run zero times.
 *  EDGE CASES HANDLED
 *    - Empty or single node : returns early (already reversed).
 *    - Two nodes            : works; both links flip.
 *    - tail update          : forgetting "tail <- oldHead" leaves a wrong tail.
 *  COMPLEXITY : Time O(n) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  1.14  rotate(k)  -  rotate left by k positions
 * ----------------------------------------------------------------------------
 *  IDEA
 *    A circular list has no real "first" node, only a pointer that says where
 *    the ring starts. Rotating left means: move that starting point forward.
 *    Since head = tail.next, moving the TAIL forward by one moves the head
 *    forward by one. No node is created, deleted, or relinked.
 *
 *  PSEUDOCODE
 *      ROTATE(k):
 *          if k < 0:  throw invalid_argument("negative")
 *          if tail == NULL:  return            // BEFORE the modulo (see below)
 *          steps <- k mod size                 // full turns change nothing
 *          repeat steps times:
 *              tail <- tail.next
 *
 *  EXAMPLE   list: 5 -> 10 -> 15 -> 20 (tail = 20),   rotate(1)
 *      tail moves 20 -> 5. New head = tail.next = [10].
 *      result : 10 -> 15 -> 20 -> 5 -> (back to 10)
 *      rotate(4) or rotate(8) on this list : steps = 0, nothing changes.
 *
 *  EDGE CASES HANDLED
 *    - k < 0                : throws std::invalid_argument.
 *    - Empty list           : return before "k mod size" (modulo by zero).
 *    - k == 0, k multiple of size : steps = 0, no work.
 *    - k > size             : reduced by the modulo.
 *  COMPLEXITY : Time O(k mod n) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  1.15  print()
 * ----------------------------------------------------------------------------
 *  PSEUDOCODE
 *      PRINT():
 *          if tail == NULL:  output "List is empty."; return
 *          head <- tail.next
 *          cur  <- head
 *          repeat size times:
 *              output cur.data, " -> "
 *              cur <- cur.next
 *          output "(back to ", head.data, ")"
 *
 *  EXAMPLE   5 -> 15 -> 20 -> (back to 5)
 *  EDGE CASES : empty message; the size bound prevents infinite output.
 *  COMPLEXITY : Time O(n) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  1.16  size() / isEmpty()
 * ----------------------------------------------------------------------------
 *      SIZE():     return size          // cached counter
 *      IS_EMPTY(): return tail == NULL
 *  COMPLEXITY : Time O(1) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  1.17  clear()
 * ----------------------------------------------------------------------------
 *  IDEA
 *    Free every node. First BREAK THE CIRCLE (tail.next = NULL) so the walk has
 *    an end; otherwise the loop would revisit deleted nodes forever.
 *
 *  PSEUDOCODE
 *      CLEAR():
 *          if tail == NULL:  return
 *          cur <- tail.next                // the head
 *          tail.next <- NULL               // break the ring: now it is linear
 *          while cur != NULL:
 *              nextNode <- cur.next        // SAVE before delete
 *              delete cur
 *              cur <- nextNode
 *          tail <- NULL
 *          size <- 0
 *
 *  EXAMPLE   list: 5 -> 15 -> 20 (tail = 20)
 *      cur = [5]; [20].next = NULL      (now 5 -> 15 -> 20 -> NULL)
 *      delete 5, delete 15, delete 20, cur = NULL -> stop.  tail = NULL, size = 0
 *
 *  EDGE CASES HANDLED
 *    - Empty list           : returns immediately (idempotent).
 *    - Single node          : tail.next = NULL breaks the self-loop; one delete.
 *    - Use after free       : nextNode is saved before the delete.
 *    - Forgetting the break : infinite loop / double free.
 *  COMPLEXITY : Time O(n) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  1.18  Destructor and deleted copy operations
 * ----------------------------------------------------------------------------
 *    ~CircularSinglyLinkedList() calls clear(): every node came from "new", so
 *    the list must free them. Copy constructor and copy assignment are deleted:
 *    a shallow copy would make two lists share the same ring, and both
 *    destructors would free the same nodes (double free).
 *
 * ----------------------------------------------------------------------------
 *  1.19  DRY RUN   (list shown from head; tail value in its own column)
 * ----------------------------------------------------------------------------
 *   #   Operation              List (head first)     Size  tail
 *   --  ---------------------  --------------------  ----  ----
 *   0   (start)                NULL                  0     NULL
 *   1   push_back(10)          10                    1     10
 *   2   push_back(20)          10 20                 2     20
 *   3   push_front(5)          5 10 20               3     20
 *   4   insert_middle(15, 2)   5 10 15 20            4     20
 *   5   deleteAtIndex(1)       5 15 20               3     20
 *   6   search_ll(15)          returns 1             3     20
 *   7   getElementAtIndex(2)   returns 20            3     20
 *   8   rotate(1)              15 20 5               3     5
 *   9   reverse()              5 20 15               3     15
 *  10   pop_back()             5 20                  2     20
 *  11   pop_front()            20                    1     20
 *  12   pop_back()             NULL                  0     NULL
 *  13   pop_front()            throws underflow      0     NULL
 *
 *   Rows 11 and 12 are the single-node and become-empty transitions, where
 *   most circular-list bugs appear.
 *
 *
 * ============================================================================
 *  2. CIRCULAR DOUBLY LINKED LIST
 * ============================================================================
 *
 * ----------------------------------------------------------------------------
 *  2.1  STRUCTURE AND DESIGN
 * ----------------------------------------------------------------------------
 *    Node    : data, prev, next
 *    Members : head   (pointer to the FIRST node; NULL when empty)
 *              _size  (cached element count)
 *    The tail is never stored: it is always  tail = head.prev.
 *
 *  WHY ONLY A HEAD POINTER?
 *    Because the ring is closed in both directions, head.prev IS the last
 *    node. One pointer reaches both ends in O(1), and pop_back is O(1) too,
 *    which the circular SINGLY list cannot do.
 *
 *  THREE PRIVATE HELPERS DO ALL THE POINTER WORK
 *    insert_before(where, val) : link a new node just before a given node
 *    unlink(node)              : detach and delete any node
 *    node_at(idx)              : find a node by index from the nearer end
 *  Every public operation is a thin wrapper around these, so the tricky
 *  edge cases (empty, single node, head/tail changes) live in exactly two
 *  small functions instead of being repeated in every operation.
 *
 * ----------------------------------------------------------------------------
 *  2.2  INVARIANTS
 * ----------------------------------------------------------------------------
 *    D1. Empty list      : head == NULL and size == 0.
 *    D2. Non-empty list  : tail.next == head and head.prev == tail, where
 *                          tail = head.prev. No node has a NULL link.
 *    D3. Mutual links    : if A.next == B then B.prev == A.
 *    D4. Single node     : head.next == head and head.prev == head.
 *    D5. Size is exact   : size equals the number of nodes in the ring.
 *
 * ----------------------------------------------------------------------------
 *  2.3  insert_before(where, val)  -  private helper
 * ----------------------------------------------------------------------------
 *  IDEA
 *    Create a node and splice it in immediately BEFORE the node `where`. The
 *    left neighbour is where.prev. If `where` is NULL (empty list) the new node
 *    becomes a self-loop. Returns the new node; the CALLER decides whether it
 *    becomes the head.
 *
 *  PSEUDOCODE
 *      INSERT_BEFORE(where, val):
 *          newNode <- Node(val)
 *          if where == NULL:                       // empty list
 *              newNode.prev <- newNode
 *              newNode.next <- newNode             // self-loop
 *          else:
 *              newNode.next <- where               // 1. new node's links first
 *              newNode.prev <- where.prev
 *              where.prev.next <- newNode          // 2. left neighbour -> new
 *              where.prev      <- newNode          // 3. where -> new (LAST)
 *          size <- size + 1
 *          return newNode
 *
 *  EXAMPLE   ring: 5 <-> 10 <-> 20,   insert_before(20, 15)
 *      newNode.next = [20]
 *      newNode.prev = [20].prev = [10]
 *      [10].next    = [15]
 *      [20].prev    = [15]
 *      result : 5 <-> 10 <-> 15 <-> 20 (ring closed)
 *
 *  ORDER MATTERS
 *    newNode.prev must read where.prev BEFORE step 3 overwrites it. Doing step 3
 *    first loses the left neighbour.
 *
 *  EDGE CASES HANDLED
 *    - Empty list     : self-loop (D4).
 *    - Single node    : where.prev == where, so the formulas still work:
 *                       new.next = where, new.prev = where,
 *                       where.next = new, where.prev = new  ->  two-node ring.
 *    - Allocation fail: "new" runs first, so a throw changes nothing.
 *  COMPLEXITY : Time O(1) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  2.4  unlink(node)  -  private helper
 * ----------------------------------------------------------------------------
 *  IDEA
 *    Detach a node by joining its two neighbours, move head if the removed node
 *    was the head, then delete it.
 *
 *  PSEUDOCODE
 *      UNLINK(node):
 *          if size == 1:
 *              head <- NULL                        // the ring becomes empty
 *          else:
 *              node.prev.next <- node.next         // bridge over the node
 *              node.next.prev <- node.prev
 *              if node == head:
 *                  head <- node.next               // head moves forward
 *          delete node
 *          size <- size - 1
 *
 *  EXAMPLE   ring: 5 <-> 10 <-> 20,   unlink(20) (the tail)
 *      [10].next = [5]
 *      [5].prev  = [10]                 (head.prev now names the new tail)
 *      delete [20]
 *      result : 5 <-> 10 (ring closed)
 *
 *  EDGE CASES HANDLED
 *    - Single node : node.prev and node.next are the node ITSELF. Without the
 *                    size == 1 branch the bridge writes into a node that is
 *                    about to be deleted and head would dangle.
 *    - Head removed: head must move to node.next, or it points at freed memory.
 *    - Tail removed: nothing extra: the tail is head.prev, which the bridge has
 *                    already updated.
 *  COMPLEXITY : Time O(1) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  2.5  node_at(idx)  -  private helper (walk from the nearer end)
 * ----------------------------------------------------------------------------
 *  PRECONDITION : 0 <= idx < size
 *
 *  PSEUDOCODE
 *      NODE_AT(idx):
 *          if idx < size / 2:
 *              cur <- head
 *              repeat idx times:  cur <- cur.next
 *          else:
 *              cur <- head.prev                    // the tail
 *              for i from size-1 down to idx+1:  cur <- cur.prev
 *          return cur
 *
 *  EXAMPLE   size = 8:  idx 2 -> 2 steps from head;  idx 6 -> 1 step from tail.
 *  EDGE CASES : idx 0 and idx size-1 take zero steps; size 1 returns head.
 *  COMPLEXITY : Time O(min(idx, n - idx)), worst case O(n) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  2.6  push_front(val)
 * ----------------------------------------------------------------------------
 *  PSEUDOCODE
 *      PUSH_FRONT(val):
 *          head <- INSERT_BEFORE(head, val)
 *
 *  WHY IT WORKS
 *    In a ring, "just before the head" is the tail position. Inserting there and
 *    then moving head onto the new node makes it the first element, with no
 *    other pointer changes. On an empty list INSERT_BEFORE(NULL, val) returns a
 *    self-loop node and head takes it.
 *
 *  EXAMPLE   ring: 10 <-> 20,   push_front(5)
 *      insert 5 before head [10]: ring 10 <-> 20 <-> 5, then head = [5]
 *      result : 5 <-> 10 <-> 20 (head = 5, tail = head.prev = 20)
 *  EDGE CASES : empty list and single-node list handled by the helper.
 *  COMPLEXITY : Time O(1) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  2.7  push_back(val)
 * ----------------------------------------------------------------------------
 *  PSEUDOCODE
 *      PUSH_BACK(val):
 *          newNode <- INSERT_BEFORE(head, val)     // lands in the tail position
 *          if head == NULL:                        // list was empty
 *              head <- newNode
 *
 *  WHY IT WORKS : the position before the head IS the back of the ring, so head
 *  stays where it is. Only an empty list needs head assigned.
 *
 *  EXAMPLE   ring: 5 <-> 10,   push_back(20)  ->  5 <-> 10 <-> 20 (head = 5)
 *  EDGE CASES : empty list (head must be set), single node (two-node ring).
 *  COMPLEXITY : Time O(1) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  2.8  pop_front()
 * ----------------------------------------------------------------------------
 *  PSEUDOCODE
 *      POP_FRONT():
 *          if head == NULL:  throw underflow_error("empty")
 *          UNLINK(head)
 *
 *  EDGE CASES : empty throws; single node leaves an empty list; otherwise head
 *  moves to the next node (done inside UNLINK).
 *  COMPLEXITY : Time O(1) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  2.9  pop_back()
 * ----------------------------------------------------------------------------
 *  PSEUDOCODE
 *      POP_BACK():
 *          if head == NULL:  throw underflow_error("empty")
 *          UNLINK(head.prev)                       // head.prev is the tail
 *
 *  O(1) BECAUSE head.prev IS the tail and its predecessor is reached by prev
 *  links. A circular SINGLY list needs an O(n) walk for the same operation.
 *
 *  EXAMPLE   ring: 5 <-> 10 <-> 20,   pop_back()  ->  5 <-> 10
 *  EDGE CASES : empty throws; single node -> empty list; head never moves
 *               (unless the single node is both head and tail).
 *  COMPLEXITY : Time O(1) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  2.10  insert_middle(val, pos)
 * ----------------------------------------------------------------------------
 *  PSEUDOCODE
 *      INSERT_MIDDLE(val, pos):
 *          if pos < 0 or pos > size:  throw out_of_range("Invalid position")
 *          if pos == 0:     PUSH_FRONT(val); return
 *          if pos == size:  PUSH_BACK(val);  return
 *          INSERT_BEFORE(NODE_AT(pos), val)        // before the node now at pos
 *
 *  EXAMPLE   ring: 5 <-> 10 <-> 20,   insert_middle(15, 2)
 *      NODE_AT(2) = [20];  insert 15 before it.
 *      result : 5 <-> 10 <-> 15 <-> 20
 *
 *  EDGE CASES HANDLED
 *    - pos < 0 or pos > size : throws before allocating.
 *    - Empty list, pos 0     : push_front (self-loop, head set).
 *    - pos == size           : push_back (checked after pos == 0, because on an
 *                              empty list both are 0).
 *    - Middle position       : the helper does all four pointer updates; no
 *                              "node before" loop is needed.
 *  COMPLEXITY : Time O(n) general, O(1) at pos 0 or size | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  2.11  deleteAtIndex(pos)
 * ----------------------------------------------------------------------------
 *  PSEUDOCODE
 *      DELETE_AT_INDEX(pos):
 *          if pos < 0 or pos >= size:  throw out_of_range("Invalid position")
 *          UNLINK(NODE_AT(pos))
 *
 *  No head / tail / single-node branches here: UNLINK handles all of them.
 *
 *  EXAMPLE   ring: 5 <-> 10 <-> 15 <-> 20,   deleteAtIndex(1)
 *      NODE_AT(1) = [10]  ->  UNLINK  ->  5 <-> 15 <-> 20
 *  EDGE CASES : empty list throws; pos 0 moves head; pos size-1 removes the tail;
 *               single node empties the list.
 *  COMPLEXITY : Time O(n) general, O(1) at pos 0 or size - 1 | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  2.12  search_ll(key) and getElementAtIndex(idx)
 * ----------------------------------------------------------------------------
 *  PSEUDOCODE
 *      SEARCH(key):
 *          if head == NULL:  return -1
 *          cur <- head
 *          for i from 0 to size - 1:
 *              if cur.data == key:  return i
 *              cur <- cur.next
 *          return -1
 *
 *      GET_ELEMENT_AT_INDEX(idx):
 *          if idx < 0 or idx >= size:  throw out_of_range("Invalid index")
 *          return NODE_AT(idx).data
 *
 *  EDGE CASES : empty list (-1 / throws); not found stops by the size bound;
 *               get at either end is O(1).
 *  COMPLEXITY : search O(n); get O(n) worst case, O(1) at the ends | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  2.13  removeFirstOccurrence(key)
 * ----------------------------------------------------------------------------
 *  PSEUDOCODE
 *      REMOVE_FIRST_OCCURRENCE(key):
 *          if head == NULL:  return false
 *          cur <- head
 *          repeat size times:
 *              if cur.data == key:
 *                  UNLINK(cur)
 *                  return true
 *              cur <- cur.next
 *          return false
 *
 *  Because every node knows its predecessor (prev), no second pointer is needed
 *  and UNLINK handles head / tail / single-node cases.
 *  COMPLEXITY : Time O(n) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  2.14  reverse()
 * ----------------------------------------------------------------------------
 *  IDEA
 *    Reversing a doubly list means every node's prev and next trade places.
 *    Afterwards the old tail must become the head.
 *
 *  PSEUDOCODE
 *      REVERSE():
 *          if head == NULL or size == 1:  return
 *          cur <- head
 *          repeat size times:
 *              swap(cur.prev, cur.next)
 *              cur <- cur.prev                 // after the swap, prev = OLD next
 *          head <- head.next                   // after the swap, next = OLD prev,
 *                                              // i.e. the old tail
 *
 *  EXAMPLE   ring A <-> B <-> C,  head = A
 *      A : swap -> A.prev=B, A.next=C;  cur = A.prev = B
 *      B : swap -> B.prev=C, B.next=A;  cur = B.prev = C
 *      C : swap -> C.prev=A, C.next=B;  cur = C.prev = A  (3 passes done)
 *      head = A.next = C
 *      result : C <-> B <-> A (ring closed), no node allocated or freed
 *
 *  EDGE CASES HANDLED
 *    - Empty / single node : returns early.
 *    - Moving cur          : uses prev AFTER the swap (the old next). Using
 *                            cur.next would walk backwards and never finish.
 *    - Head update         : forgetting it leaves head pointing at the new tail.
 *  COMPLEXITY : Time O(n) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  2.15  rotate(k)  -  rotate left by k positions
 * ----------------------------------------------------------------------------
 *  IDEA
 *    Only the head pointer moves. Because the ring is doubly linked, the head
 *    can move the SHORTER way: forward for a small left rotation, backward
 *    (using prev) if the equivalent right rotation is cheaper.
 *
 *  PSEUDOCODE
 *      ROTATE(k):
 *          if k < 0:  throw invalid_argument("negative")
 *          if head == NULL:  return
 *          steps <- k mod size
 *          if steps <= size - steps:
 *              repeat steps times:         head <- head.next
 *          else:
 *              repeat (size - steps) times: head <- head.prev
 *
 *  EXAMPLE   ring [5,10,15,20], rotate(3):  steps = 3 > size - steps = 1
 *      move head BACKWARD once: head = 20  ->  20 5 10 15
 *      which equals rotating left by 3.
 *
 *  EDGE CASES : k < 0 throws; empty list returns before the modulo; steps == 0
 *               does nothing; k >= size is reduced by the modulo.
 *  COMPLEXITY : Time O(min(k mod n, n - k mod n)) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  2.16  print() and printReverse()
 * ----------------------------------------------------------------------------
 *  PSEUDOCODE
 *      PRINT():
 *          if head == NULL:  output "List is empty."; return
 *          cur <- head
 *          repeat size times:  output cur.data, " <-> ";  cur <- cur.next
 *          output "(back to ", head.data, ")"
 *
 *      PRINT_REVERSE():
 *          if head == NULL:  output "List is empty."; return
 *          tail <- head.prev
 *          cur  <- tail
 *          repeat size times:  output cur.data, " <-> ";  cur <- cur.prev
 *          output "(back to ", tail.data, ")"
 *
 *  USE AS A TEST : if print() and printReverse() show mirrored output after an
 *  operation, the next and prev links are consistent (D3).
 *  COMPLEXITY : Time O(n) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  2.17  clear()
 * ----------------------------------------------------------------------------
 *  PSEUDOCODE
 *      CLEAR():
 *          cur <- head
 *          repeat size times:
 *              nextNode <- cur.next            // SAVE before delete
 *              delete cur
 *              cur <- nextNode
 *          head <- NULL
 *          size <- 0
 *
 *  Here the loop is bounded by size, so the circle does not need to be broken.
 *  (Both styles are valid: break the ring, or count.)
 *  EDGE CASES : empty list performs zero iterations and never dereferences head;
 *               nextNode saved first avoids use-after-free.
 *  COMPLEXITY : Time O(n) | Space O(1)
 *  The destructor calls clear(); copy operations are deleted (double free).
 *
 * ----------------------------------------------------------------------------
 *  2.18  DRY RUN   (list shown from head)
 * ----------------------------------------------------------------------------
 *   #   Operation              List (head first)     Size  head  tail
 *   --  ---------------------  --------------------  ----  ----  ----
 *   0   (start)                NULL                  0     NULL  NULL
 *   1   push_back(10)          10                    1     10    10
 *   2   push_back(20)          10 20                 2     10    20
 *   3   push_front(5)          5 10 20               3     5     20
 *   4   insert_middle(15, 2)   5 10 15 20            4     5     20
 *   5   deleteAtIndex(1)       5 15 20               3     5     20
 *   6   search_ll(15)          returns 1             3     5     20
 *   7   getElementAtIndex(2)   returns 20            3     5     20
 *   8   printReverse()         20 15 5               3     5     20
 *   9   rotate(1)              15 20 5               3     15    5
 *  10   reverse()              5 20 15               3     5     15
 *  11   pop_back()             5 20                  2     5     20
 *  12   pop_front()            20                    1     20    20
 *  13   pop_back()             NULL                  0     NULL  NULL
 *  14   pop_front()            throws underflow      0     NULL  NULL
 *
 *   (tail = head.prev; it is shown only to help you check the ring.)
 *
 * ----------------------------------------------------------------------------
 *  2.19  CIRCULAR SINGLY vs CIRCULAR DOUBLY
 * ----------------------------------------------------------------------------
 *
 *   Feature                      Circular singly         Circular doubly
 *   ---------------------------  ----------------------  -----------------------
 *   Node fields                  data, next              data, prev, next
 *   Node size (typical 64-bit)   16 bytes                24 bytes
 *   Pointer stored by the list   tail                    head
 *   Other end reached by         head = tail.next        tail = head.prev
 *   push_front / push_back       O(1) / O(1)             O(1) / O(1)
 *   pop_front                    O(1)                    O(1)
 *   pop_back                     O(n)                    O(1)
 *   Remove a node given its      O(n) (find the          O(1) (prev gives the
 *     pointer                      predecessor)            predecessor)
 *   Insert before a given node   O(n)                    O(1)
 *   Index access                 up to n steps           up to about n/2 steps
 *   Backward traversal           not possible            natural (prev links)
 *   Rotate by k                  O(k mod n)              O(min(k mod n, n - k mod n))
 *   Reverse                      flip next, track prev   swap prev/next, move head
 *   Pointers updated per insert  2 (middle)              4 (middle)
 *   Memory overhead              lower                   one extra pointer per node
 *   Code complexity / bug risk   lower                   higher (use helpers)
 *
 *   CHOOSE circular singly : memory matters and you only move forward
 *                            (round-robin, queue with one pointer, Josephus).
 *   CHOOSE circular doubly : you need O(1) removal from the back or of a known
 *                            node, or backward movement (kernel lists, heaps).
 *
 *
 * ============================================================================
 *  3. TRAVERSAL PATTERNS
 * ============================================================================
 *
 *  Without a NULL terminator you must decide HOW to stop. Choose the pattern
 *  that matches what you know.
 *
 *  PATTERN 1 : COUNT-BOUNDED LOOP   (used by the implementations above)
 *      cur <- head
 *      repeat size times:
 *          visit(cur)
 *          cur <- cur.next
 *    + Safest. Works while nodes are not added or removed during the walk.
 *    - Needs a trustworthy size.
 *
 *  PATTERN 2 : DO-WHILE UNTIL BACK AT THE START
 *      if list is empty: return
 *      start <- head
 *      cur   <- start
 *      do:
 *          visit(cur)
 *          cur <- cur.next
 *      while cur != start
 *    + No size needed.
 *    ! Must be do-while. A plain  while (cur != start)  runs ZERO times because
 *      cur starts equal to start.
 *    ! Empty-list check is mandatory, otherwise cur is NULL.
 *
 *  PATTERN 3 : STOP AT THE TAIL   (circular singly)
 *      if tail == NULL: return
 *      cur <- tail.next                  // head
 *      loop:
 *          visit(cur)
 *          if cur == tail: break
 *          cur <- cur.next
 *    + Natural when you hold the tail pointer.
 *
 *  PATTERN 4 : BACKWARD TRAVERSAL   (circular doubly)
 *      cur <- head.prev                  // tail
 *      repeat size times:
 *          visit(cur)
 *          cur <- cur.prev
 *
 *  PATTERN 5 : START FROM ANY NODE
 *    A ring has no real beginning, so you can start at any node `p` and visit
 *    everything exactly once:  visit(p), p.next, ..., until you return to p.
 *    This is the basis of round-robin and "current player" logic: keep a
 *    pointer to the current node and just advance it.
 *
 *  PATTERN 6 : CYCLIC STEPPING (k steps around the ring)
 *      repeat (k mod size) times:  cur <- cur.next
 *    The modulo removes full laps. Use it for rotate, "skip k people", etc.
 *
 *  PATTERN 7 : TRAVERSE WITH A TRAILING POINTER (circular singly)
 *    To delete or insert after a node you need its predecessor. Use
 *    prev <- tail, cur <- head: the head's predecessor is the tail, so the head
 *    needs no special case (see 1.12 and the Josephus code in Section 5).
 *
 *  PATTERN 8 : TWO-POINTER (slow / fast)
 *    Move one pointer 1 step and another 2 steps per iteration. Used to detect
 *    a cycle and to find the middle (Section 4). In a circular list the fast
 *    pointer stops when it returns to the head, not at NULL.
 *
 *  PATTERN 9 : NEARER-END SEARCH (circular doubly)
 *    If idx < size/2 walk forward from head, otherwise walk backward from
 *    head.prev. At most about n/2 steps.
 *
 *  PATTERN 10 : DELETE WHILE TRAVERSING
 *      cur <- head
 *      repeat size times:                 // size is copied BEFORE the loop
 *          nextNode <- cur.next           // save first
 *          if shouldRemove(cur):  remove cur
 *          cur <- nextNode
 *    ! Fix the loop bound before you start (use a copy of size), because size
 *      shrinks as you delete.
 *    ! If you use "return to the start node" as the stop test, do not delete
 *      that start node, or the loop can never see it again.
 *
 *  TRAVERSAL MISTAKES
 *    - while (cur != NULL)         infinite loop (no node is NULL).
 *    - while (cur != head)         zero iterations on the first check.
 *    - Traversing an empty list    NULL dereference.
 *    - Forgetting the size bound   infinite output when printing.
 *    - Modifying the list while using a node as the stop marker.
 *
 *
 * ============================================================================
 *  4. DETECTING A CIRCULAR LIST
 * ============================================================================
 *
 *  THE PROBLEM
 *    Given a node pointer to a singly linked list, decide whether following
 *    next pointers ever loops back. Two different questions exist:
 *
 *      Q1. "Is it a PURE circular list?"  (last node points to the head)
 *      Q2. "Does it contain ANY cycle?"   (last node may point to a MIDDLE node,
 *                                          a "rho" or "6" shape)
 *
 *      Pure circular :  A -> B -> C -> A
 *      Rho shape     :  A -> B -> C -> D -> B   (cycle B, C, D; A is a tail)
 *
 *    A circular list is the special case where the cycle starts at the head.
 *
 *  METHOD 1 : HASH SET OF VISITED NODES
 *      HAS_CYCLE(head):
 *          visited <- empty set
 *          cur <- head
 *          while cur != NULL:
 *              if cur in visited:  return true
 *              insert cur into visited
 *              cur <- cur.next
 *          return false
 *    Time O(n) | Space O(n). Simple and obviously correct. Store node ADDRESSES,
 *    not values (values can repeat).
 *
 *  METHOD 2 : FLOYD'S TORTOISE AND HARE   (best: O(1) extra space)
 *      HAS_CYCLE(head):
 *          slow <- head
 *          fast <- head
 *          while fast != NULL and fast.next != NULL:
 *              slow <- slow.next             // 1 step
 *              fast <- fast.next.next        // 2 steps
 *              if slow == fast:  return true
 *          return false
 *    Time O(n) | Space O(1).
 *
 *    Why it works : once both pointers are inside a cycle of length L, each
 *    iteration the gap between them changes by 1 (fast gains one step), so the
 *    gap reaches 0 within L iterations. With no cycle, fast reaches NULL.
 *
 *    EXAMPLE   pure circle A -> B -> C -> (A)
 *      start    : slow=A, fast=A
 *      iter 1   : slow=B, fast=C
 *      iter 2   : slow=C, fast=B        (C.next=A, A.next=B)
 *      iter 3   : slow=A, fast=A        slow == fast -> cycle found
 *
 *  METHOD 3 : WALK UNTIL NULL OR BACK TO THE HEAD   (pure circular only)
 *      IS_PURE_CIRCULAR(head):
 *          if head == NULL:  return false
 *          cur <- head.next
 *          while cur != NULL and cur != head:
 *              cur <- cur.next
 *          return cur == head
 *    Time O(n) | Space O(1). It answers Q1 only. DANGER: on a rho-shaped list
 *    it loops forever (it never meets NULL or the head). Use Floyd when you do
 *    not know the shape.
 *
 *  FIND THE CYCLE LENGTH
 *      After slow == fast (inside the cycle):
 *          count <- 1
 *          cur <- slow.next
 *          while cur != slow:  cur <- cur.next;  count <- count + 1
 *          return count
 *
 *  FIND WHERE THE CYCLE STARTS   (Floyd phase 2)
 *      After the meeting point:
 *          p <- head
 *          q <- meeting node
 *          while p != q:  p <- p.next;  q <- q.next
 *          return p                         // first node of the cycle
 *    Proof sketch : let a = steps from head to the cycle start, b = steps from
 *    the cycle start to the meeting node, L = cycle length. slow walked a + b,
 *    fast walked 2(a + b) = a + b + k*L for some whole k, so a + b = k*L,
 *    hence a = k*L - b. Walking a steps from the meeting node lands exactly on
 *    the cycle start, and so does walking a steps from the head.
 *
 *  BREAK THE CYCLE / CONVERT BETWEEN CIRCULAR AND LINEAR
 *      Pure circular -> linear :  tail.next <- NULL          (tail = node whose next is head)
 *      Linear -> circular      :  tail.next <- head
 *      Rho -> linear           :  find the cycle start S, walk to the node X whose
 *                                 next == S (stay inside the cycle), set X.next <- NULL.
 *
 *  FOR THE IMPLEMENTATIONS IN THIS FOLDER
 *    You do not need detection: the class guarantees invariants C2/D2 by
 *    construction, and traversals are size-bounded. Detection matters when you
 *    receive a raw node pointer from unknown code (interview problems, bug
 *    hunting a corrupted list).
 *
 *  EDGE CASES TO TEST
 *    - Empty list (head == NULL)          : no cycle.
 *    - Single node, next == NULL          : no cycle.
 *    - Single node, next == itself        : cycle (self-loop). Floyd: slow=fast
 *                                            after one iteration.
 *    - Two nodes pointing at each other   : cycle.
 *    - Cycle starts at the head           : pure circular list.
 *    - Cycle starts in the middle         : rho shape; Method 3 would hang.
 *    - Even and odd cycle lengths         : Floyd handles both.
 *
 *  RELATED PRACTICE PROBLEMS
 *    - Linked List Cycle            (LeetCode 141)  Floyd
 *    - Linked List Cycle II         (LeetCode 142)  cycle start
 *    - Rotate List                  (LeetCode 61)   make circular, cut at the new tail
 *    - Find the Winner of the Circular Game (LeetCode 1823)  Josephus
 *    - Insert into a Sorted Circular Linked List (LeetCode 708)
 *
 *
 * ============================================================================
 *  5. USE CASES
 * ============================================================================
 *
 *  WHY CIRCULAR?
 *    Use a circular list when the process repeats in a cycle and "after the
 *    last comes the first" is a natural rule: there is no special wrap-around
 *    code, you just advance the pointer.
 *
 *   Use case                 List type          Operation that benefits
 *   -----------------------  -----------------  ---------------------------------
 *   Round-robin scheduler    circular singly    advance current = current.next, O(1)
 *   Turn-based game order    circular singly    next player is always next
 *   Queue with ONE pointer   circular singly    enqueue = push_back, dequeue =
 *                                               pop_front, both O(1) with only tail
 *   Playlist repeat-all      circular doubly    next AND previous song wrap around
 *   Josephus problem         circular singly    delete every k-th node in the ring
 *   Concatenate two lists    circular singly    O(1): swap two next pointers
 *   Fibonacci heap roots     circular doubly    O(1) splice of two root lists
 *   Linux kernel list_head   circular doubly    O(1) insert / remove of known nodes
 *   Token ring / carousel    either             repeating visit order
 *
 *  5.1  ROUND-ROBIN SCHEDULING
 *      Keep a pointer `current` to the process whose turn it is.
 *      loop:
 *          run current for one time quantum
 *          if current finished:  remove it from the ring
 *          else:                 current <- current.next
 *    No wrap-around check is needed; the ring does it automatically.
 *
 *  5.2  QUEUE USING ONE POINTER
 *    Store only tail. enqueue(x) = push_back(x). dequeue() = pop_front().
 *    peek() = tail.next.data. All O(1) and only one pointer is stored.
 *
 *  5.3  O(1) CONCATENATION  (two circular singly lists A and B)
 *      CONCAT(A, B):                       // a = A.tail, b = B.tail
 *          if A is empty:  return B
 *          if B is empty:  return A
 *          temp   <- a.next                // head of A
 *          a.next <- b.next                // A's last node now points to B's head
 *          b.next <- temp                  // B's last node now points to A's head
 *          return list with tail = b       // sequence: A..., B..., then back to A
 *    EXAMPLE  A = 1 2 (tail 2), B = 3 4 (tail 4)  ->  1 2 3 4 (tail 4)
 *    Time O(1). A linear singly list also concatenates in O(1) with a tail
 *    pointer, but the circular version keeps the ring closed with the same two
 *    pointer swaps.
 *
 *  5.4  JOSEPHUS PROBLEM
 *    n people stand in a circle numbered 1..n. Starting at person 1, count k
 *    people and remove the k-th; counting resumes after the removed person.
 *    The last survivor is the answer.
 *
 *      JOSEPHUS(n, k):
 *          build a circular singly list holding 1..n
 *          prev <- tail                    // predecessor of the head
 *          cur  <- head
 *          while size > 1:
 *              repeat (k - 1) times:
 *                  prev <- cur
 *                  cur  <- cur.next
 *              prev.next <- cur.next       // remove cur
 *              delete cur
 *              cur <- prev.next
 *              size <- size - 1
 *          return cur.data
 *
 *    EXAMPLE  n = 5, k = 2  ->  removal order 2, 4, 1, 5, survivor 3
 *      ring 1 2 3 4 5:  remove 2 (cur moves to 3), remove 4 (cur 5),
 *      remove 1 (cur 3), remove 5 -> only 3 remains.
 *    Time O(n * k) by simulation (a recurrence gives O(n)). Space O(n) for the
 *    list. This is a textbook use of PATTERN 7 (trailing pointer).
 *
 *  5.5  KERNEL AND HEAP STRUCTURES
 *    A circular doubly list lets code insert or remove a node it already holds
 *    a pointer to in O(1), with no NULL special cases at the ends. That is why
 *    the Linux kernel's list_head and the Fibonacci heap's root list use it.
 *
 *  WHEN NOT TO USE A CIRCULAR LIST
 *    - You need random access by index in O(1)   -> use an array / vector.
 *    - Data is naturally linear with a clear end -> a plain list is simpler and
 *      avoids infinite-loop risk.
 *    - Memory per node is critical                -> prefer singly over doubly.
 *    - The team is not comfortable with the stop-condition pitfalls (Section 3).
 *
 *
 * ============================================================================
 *  6. EDGE CASE MASTER TABLE
 * ============================================================================
 *
 *  Always test an operation on: EMPTY, ONE NODE, TWO NODES, then a larger list.
 *
 *   Operation (both lists)  Empty               One node                    Ends / middle
 *   ----------------------  ------------------  --------------------------  ------------------
 *   push_front              self-loop; set      node links to the old one,  tail unchanged
 *                           tail / head         ring stays closed           (singly)
 *   push_back               self-loop; set      same                        singly: move tail
 *                           tail / head                                     doubly: head fixed
 *   pop_front               throws              tail / head -> NULL         skip old head
 *   pop_back                throws              tail / head -> NULL         singly: O(n) walk,
 *                                                                           stop at prev.next
 *                                                                           == tail
 *                                                                           doubly: unlink tail
 *   insert_middle           only pos 0 valid    pos 0 or 1 are boundary     pos 0, size use
 *                                               cases                       push_*; middle
 *   deleteAtIndex           throws              pos 0 empties the list;     ends use pop_*;
 *                                               check pos 0 BEFORE size-1   middle unlinks
 *   search_ll               -1                  one comparison              bounded by size
 *   getElementAtIndex       throws              index 0 only                O(1) at ends
 *   removeFirstOccurrence   false               empties the list on match   head / tail moves
 *   reverse                 no-op               no-op                       relink all nodes,
 *                                                                           update tail / head
 *   rotate(k)               no-op (no modulo    no-op (k mod 1 = 0)         k mod size steps
 *                           by zero)
 *   print / printReverse    prints message      one element                 size-bounded loop
 *   clear                   no-op               frees one node              break ring or count
 *
 *  Invalid index (negative or too large) -> insert / delete / get throw
 *  std::out_of_range. Test pos < 0 BEFORE casting to size_t.
 *
 *
 * ============================================================================
 *  7. COMMON BUGS AND HOW TO AVOID THEM
 * ============================================================================
 *
 *   1. Using NULL as the loop terminator.
 *        Symptom : infinite loop, or a crash after walking forever.
 *        Fix     : stop by counter, by returning to the start, or at the tail.
 *
 *   2. First node does not point to itself.
 *        Symptom : next == NULL, later traversal crashes.
 *        Fix     : on an empty list set  newNode.next <- newNode  (and prev too).
 *
 *   3. Forgetting to move tail in push_back (singly).
 *        Symptom : the new node is skipped by "last element" reads.
 *        Fix     : tail <- newNode in both branches. push_front must NOT move it.
 *
 *   4. pop_back loop condition.
 *        Symptom : while (prev.next != NULL) never ends.
 *        Fix     : while (prev.next != tail).
 *
 *   5. Not closing the circle after a removal.
 *        Symptom : last node still points at a freed node.
 *        Fix     : prev.next <- head (singly) / bridge both prev and next (doubly).
 *
 *   6. clear() without breaking or bounding the ring.
 *        Symptom : infinite loop, use-after-free, double free.
 *        Fix     : set tail.next = NULL first, or loop exactly size times; always
 *                  save the next node before deleting.
 *
 *   7. while (cur != head) in a traversal.
 *        Symptom : the loop body never runs.
 *        Fix     : use do-while, or a count-bounded loop.
 *
 *   8. Modulo by zero in rotate on an empty list.
 *        Fix     : return before computing  k mod size.
 *
 *   9. Deleting the node that serves as the stop marker.
 *        Symptom : the traversal never sees its start node again.
 *        Fix     : pick a different marker, or use a size-bounded loop.
 *
 *  10. Doubly: overwriting where.prev before reading it (insert_before).
 *        Fix     : read where.prev into newNode.prev first.
 *
 *  11. Doubly: unlinking a single node by bridging.
 *        Symptom : head dangles. The node's neighbours are the node itself.
 *        Fix     : special-case size == 1 (set head = NULL).
 *
 *  12. reverse: forgetting to update tail (singly) or head (doubly).
 *        Fix     : singly: tail <- oldHead.  doubly: head <- head.next.
 *
 *  13. Forgetting to update size.
 *        Symptom : bounded loops go wrong, bounds checks wrong.
 *        Fix     : update size on every path, including early returns.
 *
 *  14. Comparing int with size_t.
 *        Symptom : a negative pos becomes a huge unsigned value.
 *        Fix     : test pos < 0 first, then static_cast<size_t>(pos).
 *
 *
 * ============================================================================
 *  8. COMPLEXITY SUMMARY   (n = number of elements, Space = auxiliary)
 * ============================================================================
 *
 *   Operation              Linear    Linear    Circular    Circular
 *                          singly*   doubly    singly      doubly
 *   ---------------------  --------  --------  ----------  ---------
 *   push_front             O(1)      O(1)      O(1)        O(1)
 *   push_back              O(1)      O(1)      O(1)        O(1)
 *   pop_front              O(1)      O(1)      O(1)        O(1)
 *   pop_back               O(n)      O(1)      O(n)        O(1)
 *   delete a known node    O(n)      O(1)      O(n)        O(1)
 *   insert before a node   O(n)      O(1)      O(n)        O(1)
 *   index access           O(n)      O(n)      O(n)        O(n)
 *   search by value        O(n)      O(n)      O(n)        O(n)
 *   reverse                O(n)      O(n)      O(n)        O(n)
 *   rotate by k            O(n)      O(n)      O(k mod n)  O(min(k mod n,
 *                                                                n - k mod n))
 *   Space (auxiliary)      O(1) for every operation above
 *
 *   * linear singly with both head and tail pointers.
 *   Circular singly stores ONE pointer (tail) and still gets O(1) at both ends.
 *   Index operations cost O(min(i, n - i)) in the doubly versions (at most about
 *   n/2 steps) but remain O(n) in Big-O terms.
 *
 *
 * ============================================================================
 *  9. KEY TAKEAWAYS
 * ============================================================================
 *
 *   - Circular = last node links back to the first. There is no NULL, so every
 *     loop needs an explicit stop: counter, return-to-start, or tail.
 *   - Circular singly stores only tail: head = tail.next, so BOTH ends are O(1)
 *     for insertion. pop_back is still O(n).
 *   - Circular doubly stores only head: tail = head.prev, so ALL end operations
 *     are O(1), including pop_back.
 *   - push_front never moves the singly tail; push_back always does.
 *   - Empty and single-node lists are where bugs live: the lone node must point
 *     to itself, and removing it must reset the pointer to NULL.
 *   - In the doubly version, route everything through insert_before and unlink.
 *     Edge cases then live in two small functions.
 *   - rotate is just moving a pointer: O(k mod n), no relinking.
 *   - Detect cycles with Floyd (O(1) space). A "walk until NULL or head" check
 *     only works on pure circular lists and hangs on a rho shape.
 *   - Use circular lists for repeating processes: schedulers, turn order,
 *     Josephus, one-pointer queues, kernel/heap structures.
 *
 *   Related files
 *     Full implementations : 14_Linked_List_Problem_Solving/
 *                            04_Implementation_on_Circular_Singly_Linked_List.cpp
 *                            05_Implementation_on_Circular_Doubly_Linked_List.cpp
 *     Previous notes       : 02_Doubly_Linked_List_Node.cpp
 *     Next notes           : 04_Traversal_And_Counting.cpp
 */

// Notes-only file. Empty main() keeps the file buildable as a standalone target.
int main() {
    return 0;
}
/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           03 — CIRCULAR LINKED LIST: STRUCTURE & TRAVERSAL                 ║
║           From Zero to Grandmaster — Complete Foundation                    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Circular Singly Linked List
 2. Circular Doubly Linked List
 3. Traversal Patterns
 4. Detecting Circular List
 5. Use Cases

CIRCULAR SINGLY LINKED LIST:
────────────────────────────
  Last node's next points BACK to the first node (no NULL!)

        ┌───────────────────────────────┐
        │                               │
        ▼                               │
   ┌───┬───┐   ┌───┬───┐   ┌───┬───┐  │
   │ 1 │ ──┼──▶│ 2 │ ──┼──▶│ 3 │ ──┼──┘
   └───┴───┘   └───┴───┘   └───┴───┘
    ↑ head

  head->next != NULL  (NEVER null in circular list!)
  Traversal: start at head, stop when we come back to head

CIRCULAR DOUBLY LINKED LIST:
────────────────────────────
        ┌──────────────────────────────────────────┐
        │                                          │
        ▼                                          │
   ┌──┬───┬──┐   ┌──┬───┬──┐   ┌──┬───┬──┐       │
   │◀─│ 1 │──┼──▶│◀─│ 2 │──┼──▶│◀─│ 3 │──┼───────┘
   └──┴───┴──┘   └──┴───┴──┘   └──┴───┴──┘
    ↑           ↑                        │
    └────────────────────────────────────┘
     head->prev = last, last->next = head
*/

#include <iostream>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: CIRCULAR SINGLY LINKED LIST
// ═══════════════════════════════════════════════════════════════

struct CNode {
    int data;
    CNode* next;
    CNode(int val) : data(val), next(nullptr) {}
};

/*
  DRY RUN — Building Circular SLL from [1, 2, 3, 4]:

  Step 1: head = new CNode(1), head->next = head  (self-loop)
          ┌────┐
          │    ▼
          [1]──┘

  Step 2: Insert 2 after head
          head ──▶ [1] ──▶ [2] ──┐
                    ↑             │
                    └─────────────┘

  Step 3: Insert 3 after 2
          head ──▶ [1] ──▶ [2] ──▶ [3] ──┐
                    ↑                      │
                    └──────────────────────┘

  Step 4: Insert 4 after 3
          head ──▶ [1] ──▶ [2] ──▶ [3] ──▶ [4] ──┐
                    ↑                               │
                    └───────────────────────────────┘
*/

CNode* buildCircularSLL(int arr[], int n) {
    if (n == 0) return nullptr;

    CNode* head = new CNode(arr[0]);
    head->next = head;  // Self-loop for single node

    CNode* tail = head;
    for (int i = 1; i < n; i++) {
        CNode* newNode = new CNode(arr[i]);
        newNode->next = head;    // New node points to head
        tail->next = newNode;    // Old tail points to new node
        tail = newNode;          // Update tail
    }
    return head;
}

void printCircularSLL(CNode* head) {
    if (head == nullptr) { cout << "(empty)\n"; return; }

    cout << "Circular SLL: ";
    CNode* curr = head;
    do {
        cout << curr->data;
        curr = curr->next;
        if (curr != head) cout << " -> ";
    } while (curr != head);
    cout << " -> (back to " << head->data << ")\n";
}

bool isCircular(CNode* head) {
    if (head == nullptr) return true;  // Empty is trivially circular

    CNode* curr = head->next;
    while (curr != nullptr && curr != head) {
        curr = curr->next;
    }
    return curr == head;
}

int lengthCircular(CNode* head) {
    if (head == nullptr) return 0;

    int count = 1;
    CNode* curr = head->next;
    while (curr != head) {
        count++;
        curr = curr->next;
    }
    return count;
}

void deleteCircularSLL(CNode* head) {
    if (head == nullptr) return;
    CNode* curr = head->next;
    while (curr != head) {
        CNode* temp = curr;
        curr = curr->next;
        delete temp;
    }
    delete head;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: CIRCULAR DOUBLY LINKED LIST
// ═══════════════════════════════════════════════════════════════

struct CDNode {
    int data;
    CDNode* prev;
    CDNode* next;
    CDNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};

CDNode* buildCircularDLL(int arr[], int n) {
    if (n == 0) return nullptr;

    CDNode* head = new CDNode(arr[0]);
    head->prev = head;
    head->next = head;

    CDNode* tail = head;
    for (int i = 1; i < n; i++) {
        CDNode* newNode = new CDNode(arr[i]);
        newNode->next = head;
        newNode->prev = tail;
        tail->next = newNode;
        head->prev = newNode;
        tail = newNode;
    }
    return head;
}

void printCircularDLL(CDNode* head) {
    if (head == nullptr) { cout << "(empty)\n"; return; }

    cout << "Circular DLL: ";
    CDNode* curr = head;
    do {
        cout << curr->data;
        curr = curr->next;
        if (curr != head) cout << " <-> ";
    } while (curr != head);
    cout << " <-> (back to " << head->data << ")\n";
}

void deleteCircularDLL(CDNode* head) {
    if (head == nullptr) return;
    CDNode* curr = head->next;
    while (curr != head) {
        CDNode* temp = curr;
        curr = curr->next;
        delete temp;
    }
    delete head;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: USE CASES
// ═══════════════════════════════════════════════════════════════
/*
  USE CASES FOR CIRCULAR LINKED LIST:
  ───────────────────────────────────
  1. Round-Robin Scheduling (OS process scheduling)
  2. Josephus Problem (elimination game)
  3. Circular Buffer (streaming data)
  4. Music Playlist (repeat mode)
  5. Board Games (players taking turns)
  6. Token Ring Network

  KEY DIFFERENCE FROM LINEAR LL:
  • No NULL termination → No "end" of list
  • Must use head comparison to detect full traversal
  • Infinite loop risk if traversal condition is wrong!
*/

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  CIRCULAR LINKED LIST: STRUCTURE & TRAVERSAL           ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Circular Singly Linked List
    cout << "═══ CIRCULAR SINGLY LINKED LIST ═══\n\n";
    int arr1[] = {1, 2, 3, 4, 5};
    CNode* csll = buildCircularSLL(arr1, 5);
    printCircularSLL(csll);
    cout << "Is Circular: " << (isCircular(csll) ? "YES" : "NO") << "\n";
    cout << "Length: " << lengthCircular(csll) << "\n";
    deleteCircularSLL(csll);

    // Circular Doubly Linked List
    cout << "\n═══ CIRCULAR DOUBLY LINKED LIST ═══\n\n";
    int arr2[] = {10, 20, 30, 40};
    CDNode* cdll = buildCircularDLL(arr2, 4);
    printCircularDLL(cdll);

    // Show connections
    cout << "\nNode connections:\n";
    CDNode* curr = cdll;
    do {
        cout << "  Node(" << curr->data << "): prev=" << curr->prev->data
             << ", next=" << curr->next->data << "\n";
        curr = curr->next;
    } while (curr != cdll);

    deleteCircularDLL(cdll);

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE PROBLEMS:\n";
    cout << "───────────────────\n";
    cout << "1. Insert at any position in circular SLL\n";
    cout << "2. Delete a node from circular SLL\n";
    cout << "3. Split circular list into two halves\n";
    cout << "4. Check if a given SLL is circular or linear\n";
    cout << "5. Convert linear SLL to circular and vice versa\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

