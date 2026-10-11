/*
 * Author  : Sarvan Yaduvanshi
 * Created : 2026-10-10
 *
 * ============================================================================
 *  DOUBLY LINKED LIST  -  NOTES + PSEUDOCODE
 *  Folder : 01_Linked_List_Fundamentals
 *  Level  : Basic -> Expert (definition, comparison, every operation, edge cases)
 * ============================================================================
 *
 *  CONTENTS
 *    1. What is a doubly linked list?
 *    2. Real-world examples
 *    3. Singly vs Doubly linked list (comparison)
 *    4. Design of the implementation (what the class stores and why)
 *    5. Operations, step by step (idea, example, pseudocode, edge cases)
 *         5.1  push_front          5.8   search_ll
 *         5.2  push_back           5.9   getElementAtIndex
 *         5.3  pop_front           5.10  print / printReverse
 *         5.4  pop_back            5.11  size
 *         5.5  node_at (helper)    5.12  clear
 *         5.6  insert_middle       5.13  destructor + deleted copy
 *         5.7  deleteAtIndex
 *    6. Edge case master table
 *    7. Common bugs and how to avoid them
 *    8. Complexity summary
 *    9. Full dry run
 *   10. Key takeaways
 *
 *
 * ============================================================================
 *  1. WHAT IS A DOUBLY LINKED LIST?
 * ============================================================================
 *
 *  DEFINITION
 *    A doubly linked list (DLL) is a linear data structure made of separate
 *    nodes connected by pointers. Every node stores THREE things:
 *
 *        +------+------+------+
 *        | prev | data | next |
 *        +------+------+------+
 *
 *      data : the value stored in the node
 *      prev : pointer to the previous node (NULL for the first node)
 *      next : pointer to the next node     (NULL for the last node)
 *
 *    The list itself keeps a pointer to the first node (head) and, in this
 *    implementation, the last node (tail) and the element count (_size).
 *    Because every node links in both directions, the list can be walked
 *    forwards (head -> tail) and backwards (tail -> head).
 *
 *              head                                tail
 *               |                                   |
 *               v                                   v
 *     NULL <- [ 5 ] <-> [ 10 ] <-> [ 15 ] <-> [ 20 ] -> NULL
 *
 *  Nodes are NOT stored next to each other in memory (unlike an array). They
 *  live at arbitrary heap addresses and are connected only by pointers.
 *
 *  CONCRETE EXAMPLE (addresses are made up)
 *
 *      address 0x100 : [ prev=NULL  | 10 | next=0x200 ]
 *      address 0x200 : [ prev=0x100 | 20 | next=0x300 ]
 *      address 0x300 : [ prev=0x200 | 30 | next=NULL  ]
 *
 *      head = 0x100,  tail = 0x300,  size = 3
 *
 *      Forward  walk : 0x100 -> 0x200 -> 0x300   prints 10, 20, 30
 *      Backward walk : 0x300 -> 0x200 -> 0x100   prints 30, 20, 10
 *
 *  INVARIANTS  (facts that must be true after EVERY operation)
 *    I1. Empty list      : head == NULL, tail == NULL, size == 0.
 *    I2. Non-empty list  : head->prev == NULL  and  tail->next == NULL.
 *    I3. Mutual links    : if A->next == B then B->prev == A.
 *    I4. Size is exact   : size == number of nodes reachable from head.
 *    I5. One node        : head == tail exactly when size == 1.
 *
 *    Almost every linked list bug is one of these invariants being broken.
 *    When you design an operation, ask: "Which invariants can this break,
 *    and which pointers must I fix to restore them?"
 *
 *
 * ============================================================================
 *  2. REAL-WORLD EXAMPLES
 * ============================================================================
 *
 *    - Browser history     : each page node has prev (Back) and next (Forward).
 *    - Music playlist      : "previous song" and "next song" buttons.
 *    - Undo / Redo         : states chained in both directions.
 *    - Image carousel      : move left or right between photos.
 *    - LRU cache           : doubly linked list + hash map. Holding a pointer
 *                            to a node lets you remove it in O(1) and move it
 *                            to the front, which a singly list cannot do.
 *    - Library containers  : std::list is commonly implemented as a doubly
 *                            linked list. Deque-like structures also use it.
 *
 *
 * ============================================================================
 *  3. SINGLY vs DOUBLY LINKED LIST
 * ============================================================================
 *
 *   Feature                       Singly (head + tail)    Doubly (head + tail)
 *   ----------------------------  ----------------------  ----------------------
 *   Node fields                   data, next              data, prev, next
 *   Node size (typical 64-bit)    16 bytes                24 bytes
 *   Traversal direction           forward only            forward and backward
 *   push_front                    O(1)                    O(1)
 *   push_back                     O(1)                    O(1)
 *   pop_front                     O(1)                    O(1)
 *   pop_back                      O(n)                    O(1)
 *   Delete a node given its       O(n)  (must find the    O(1)  (prev gives the
 *     pointer                       predecessor)            predecessor)
 *   Insert before a given node    O(n)                    O(1)
 *   Access by index               up to n steps           up to about n/2 steps
 *   Pointer updates per middle    2                       4
 *     insert
 *   Implementation difficulty     lower                   higher (more links)
 *   Memory overhead               lower                   one extra pointer/node
 *
 *  WHY pop_back IS O(n) IN A SINGLY LIST
 *    To remove the last node you must make the SECOND-TO-LAST node the new
 *    tail. A singly node cannot look backwards, so you walk from head.
 *    In a doubly list, tail->prev IS that node: one step.
 *
 *  WHEN TO CHOOSE WHICH
 *    - Singly : memory is tight, you only move forward (stack, simple queue,
 *               adjacency lists, hash-table chaining).
 *    - Doubly : you need backward movement, O(1) removal of a known node,
 *               or O(1) removal from both ends (LRU cache, deque, editors).
 *
 *
 * ============================================================================
 *  4. DESIGN OF THE IMPLEMENTATION
 * ============================================================================
 *
 *  Members
 *    head   : pointer to the first node (NULL when empty)
 *    tail   : pointer to the last node  (NULL when empty)
 *    _size  : cached element count
 *
 *  Why these choices
 *    - tail pointer  : makes push_back and pop_back O(1).
 *    - _size cache   : bounds checks (pos < 0 || pos > size) cost O(1)
 *                      instead of walking the list to count.
 *    - private Node  : callers never touch raw pointers, so they cannot break
 *                      the invariants from outside.
 *    - explicit Node(int) constructor : prev and next start as NULL, never as
 *                      garbage, and an int cannot silently convert to a Node.
 *    - exceptions    : empty pop -> std::underflow_error,
 *                      bad index -> std::out_of_range. A silent return or a
 *                      magic value such as -1 hides errors (and -1 could be
 *                      real data).
 *
 *  POINTER-ORDER RULE (the single most important habit)
 *    1. Create the new node and wire ITS prev and next first.
 *    2. Only then update the neighbours to point at it.
 *    3. Never overwrite a pointer before you have saved what it pointed to.
 *    4. Unlink a node BEFORE deleting it, and never read it after delete.
 *
 *
 * ============================================================================
 *  5. OPERATIONS
 * ============================================================================
 *
 * ----------------------------------------------------------------------------
 *  5.1  push_front(val)  -  insert at the front
 * ----------------------------------------------------------------------------
 *  IDEA
 *    The new node becomes the head. Its next is the old head, and the old
 *    head's prev is the new node. If the list was empty, the new node is both
 *    head AND tail.
 *
 *  PSEUDOCODE
 *      PUSH_FRONT(val):
 *          newNode <- Node(val)              // prev = NULL, next = NULL
 *          if head == NULL:                  // empty list
 *              head <- newNode
 *              tail <- newNode               // tail must be set too
 *          else:
 *              newNode.next <- head          // 1. wire new node forward
 *              head.prev    <- newNode       // 2. old head points back to it
 *              head         <- newNode       // 3. move head
 *          size <- size + 1
 *
 *  EXAMPLE   list: 10 <-> 20,   push_front(5)
 *      start        : head -> [10] <-> [20] <- tail
 *      newNode      : [NULL | 5 | NULL]
 *      step 1       : newNode.next = [10]          5 -> 10
 *      step 2       : [10].prev    = newNode       5 <-> 10
 *      step 3       : head         = newNode
 *      result       : NULL <- [5] <-> [10] <-> [20] -> NULL      size = 3
 *
 *  EDGE CASES HANDLED
 *    - Empty list      : head == tail == newNode (forgetting tail is the
 *                        classic bug: the next push_back would crash).
 *    - Single node     : handled by the else branch, tail is unchanged.
 *    - Allocation fail : "new" runs first. If it throws, nothing has been
 *                        modified, so the list stays valid.
 *  COMPLEXITY : Time O(1) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  5.2  push_back(val)  -  insert at the back
 * ----------------------------------------------------------------------------
 *  IDEA
 *    Mirror image of push_front. The old tail's next is the new node, the new
 *    node's prev is the old tail, and tail moves to the new node.
 *
 *  PSEUDOCODE
 *      PUSH_BACK(val):
 *          newNode <- Node(val)
 *          if head == NULL:
 *              head <- newNode
 *              tail <- newNode
 *          else:
 *              tail.next    <- newNode       // 1. old tail points forward
 *              newNode.prev <- tail          // 2. new node points back
 *              tail         <- newNode       // 3. move tail
 *          size <- size + 1
 *
 *  EXAMPLE   list: 10 <-> 20,   push_back(30)
 *      step 1 : [20].next = newNode          20 -> 30
 *      step 2 : newNode.prev = [20]          20 <-> 30
 *      step 3 : tail = newNode
 *      result : NULL <- [10] <-> [20] <-> [30] -> NULL      size = 3
 *
 *  EDGE CASES HANDLED
 *    - Empty list : head == tail == newNode.
 *    - Single node: else branch links the two nodes; head is unchanged.
 *  COMPLEXITY : Time O(1) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  5.3  pop_front()  -  remove from the front
 * ----------------------------------------------------------------------------
 *  IDEA
 *    Save the head, move head to head.next, cut the new head's prev link, then
 *    free the old head.
 *
 *  PSEUDOCODE
 *      POP_FRONT():
 *          if head == NULL:
 *              throw underflow_error("empty")
 *          temp <- head
 *          if head == tail:                  // exactly one node
 *              head <- NULL
 *              tail <- NULL
 *          else:
 *              head      <- head.next
 *              head.prev <- NULL             // must not point at freed memory
 *          delete temp
 *          size <- size - 1
 *
 *  EXAMPLE   list: 5 <-> 10 <-> 20,   pop_front()
 *      temp = [5]
 *      head = [10]
 *      [10].prev = NULL
 *      delete [5]
 *      result : NULL <- [10] <-> [20] -> NULL      size = 2
 *
 *  EDGE CASES HANDLED
 *    - Empty list      : throws std::underflow_error, nothing changes.
 *    - Single node     : head AND tail both become NULL (invariant I1).
 *    - Two or more     : head.prev = NULL prevents a dangling pointer to the
 *                        deleted node.
 *  COMPLEXITY : Time O(1) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  5.4  pop_back()  -  remove from the back
 * ----------------------------------------------------------------------------
 *  IDEA
 *    Save the tail, move tail to tail.prev, cut the new tail's next link, then
 *    free the old tail. This is O(1) because tail.prev is the new tail. A
 *    singly list needs O(n) here.
 *
 *  PSEUDOCODE
 *      POP_BACK():
 *          if head == NULL:
 *              throw underflow_error("empty")
 *          temp <- tail
 *          if head == tail:                  // exactly one node
 *              head <- NULL
 *              tail <- NULL
 *          else:
 *              tail      <- tail.prev
 *              tail.next <- NULL
 *          delete temp
 *          size <- size - 1
 *
 *  EXAMPLE   list: 5 <-> 10 <-> 20,   pop_back()
 *      temp = [20]
 *      tail = [10]
 *      [10].next = NULL
 *      delete [20]
 *      result : NULL <- [5] <-> [10] -> NULL      size = 2
 *
 *  EDGE CASES HANDLED
 *    - Empty list  : throws std::underflow_error.
 *    - Single node : head and tail both become NULL; the node is deleted ONCE
 *                    (deleting it twice is undefined behaviour).
 *    - Two or more: tail.prev is guaranteed non-NULL, so tail.next is safe.
 *  COMPLEXITY : Time O(1) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  5.5  node_at(idx)  -  private helper: find the node at an index
 * ----------------------------------------------------------------------------
 *  IDEA
 *    Walk from whichever end is closer. If idx is in the first half, start at
 *    head and go forward idx steps. Otherwise start at tail and go backward
 *    (size - 1 - idx) steps. This halves the worst case compared with always
 *    starting from head.
 *
 *  PRECONDITION : 0 <= idx < size (the caller validates this)
 *
 *  PSEUDOCODE
 *      NODE_AT(idx):
 *          if idx < size / 2:                // integer division
 *              cur <- head
 *              repeat idx times:   cur <- cur.next
 *          else:
 *              cur <- tail
 *              for i from size-1 down to idx+1:   cur <- cur.prev
 *          return cur
 *
 *  EXAMPLE   size = 8
 *      idx = 2  -> 2 < 4  -> start at head, 2 steps forward
 *      idx = 6  -> 6 >= 4 -> start at tail, 7 - 6 = 1 step backward
 *
 *  EDGE CASES HANDLED
 *    - idx == 0        : first branch, 0 steps, returns head.
 *    - idx == size - 1 : second branch, 0 steps, returns tail.
 *    - Odd sizes       : size/2 rounds down; either branch is still correct
 *                        and never exceeds about n/2 steps.
 *  COMPLEXITY : Time O(min(idx, n - idx)), worst case O(n) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  5.6  insert_middle(val, pos)  -  insert at a given index
 * ----------------------------------------------------------------------------
 *  IDEA
 *    Validate 0 <= pos <= size. Then three cases:
 *      A. pos == 0     -> same as push_front
 *      B. pos == size  -> same as push_back
 *      C. otherwise    -> splice between two existing nodes
 *
 *    For case C, find nextNode = the node CURRENTLY at index pos. Its prev is
 *    the left neighbour. The doubly list does not need a "node before pos"
 *    loop: nextNode.prev gives it directly.
 *
 *  PSEUDOCODE
 *      INSERT_MIDDLE(val, pos):
 *          if pos < 0 or pos > size:
 *              throw out_of_range("Invalid position")
 *          newNode <- Node(val)
 *
 *          if pos == 0:                                  // case A (checked FIRST)
 *              if head == NULL:  head <- tail <- newNode
 *              else:             newNode.next <- head
 *                                head.prev    <- newNode
 *                                head         <- newNode
 *              size <- size + 1
 *              return
 *
 *          if pos == size:                               // case B
 *              tail.next    <- newNode
 *              newNode.prev <- tail
 *              tail         <- newNode
 *              size <- size + 1
 *              return
 *
 *          nextNode <- NODE_AT(pos)                      // case C
 *          prevNode <- nextNode.prev
 *          prevNode.next <- newNode                      // forward links
 *          newNode.next  <- nextNode
 *          newNode.prev  <- prevNode                     // backward links
 *          nextNode.prev <- newNode
 *          size <- size + 1
 *
 *  EXAMPLE   list: 5 <-> 10 <-> 20,   insert_middle(15, 2)
 *      pos = 2 is neither 0 nor size (3), so case C.
 *      nextNode = [20]    (node currently at index 2)
 *      prevNode = [10]    (nextNode.prev)
 *
 *      before :  [10] <-> [20]
 *      1. [10].next = [15]       forward  10 -> 15
 *      2. [15].next = [20]       forward  15 -> 20
 *      3. [15].prev = [10]       backward 15 -> 10
 *      4. [20].prev = [15]       backward 20 -> 15
 *      after  :  [10] <-> [15] <-> [20]
 *      list   :  5 <-> 10 <-> 15 <-> 20      size = 4
 *
 *  WHY FOUR POINTER UPDATES
 *    Two neighbours, each with a forward and a backward link to repair.
 *    Missing any one of them breaks invariant I3 (mutual links), and the list
 *    then works forwards but fails backwards (or the reverse).
 *
 *  EDGE CASES HANDLED
 *    - pos < 0 or pos > size : throws std::out_of_range BEFORE allocating, so
 *                              a bad index never leaks memory.
 *    - Empty list, pos == 0  : the only valid position; case A sets head and
 *                              tail. Case A is checked BEFORE case B, because
 *                              on an empty list pos == size == 0 and case B
 *                              would dereference a NULL tail.
 *    - pos == size           : case B, tail moves to the new node.
 *    - Middle position       : 0 < pos < size means size >= 2, so prevNode
 *                              and nextNode are both guaranteed non-NULL.
 *    - Signed vs unsigned    : pos is int, size is size_t. The code checks
 *                              pos < 0 first and then casts to size_t, so a
 *                              negative pos cannot wrap into a huge number.
 *  COMPLEXITY : Time O(n) general, O(1) at pos 0 or size | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  5.7  deleteAtIndex(pos)  -  remove the element at an index
 * ----------------------------------------------------------------------------
 *  IDEA
 *    Validate 0 <= pos < size. Then three cases:
 *      1. pos == 0         -> remove head
 *      2. pos == size - 1  -> remove tail
 *      3. otherwise        -> bridge the two neighbours, then free the node
 *
 *  PSEUDOCODE
 *      DELETE_AT_INDEX(pos):
 *          if pos < 0 or pos >= size:
 *              throw out_of_range("Invalid position")
 *
 *          if pos == 0:                                  // case 1
 *              temp <- head
 *              head <- head.next
 *              if head != NULL:  head.prev <- NULL
 *              else:             tail <- NULL            // list became empty
 *              delete temp
 *              size <- size - 1
 *              return
 *
 *          if pos == size - 1:                           // case 2
 *              temp <- tail
 *              tail <- tail.prev
 *              tail.next <- NULL
 *              delete temp
 *              size <- size - 1
 *              return
 *
 *          target   <- NODE_AT(pos)                      // case 3
 *          prevNode <- target.prev
 *          nextNode <- target.next
 *          prevNode.next <- nextNode                     // bridge forward
 *          nextNode.prev <- prevNode                     // bridge backward
 *          delete target                                 // unlink first, delete last
 *          size <- size - 1
 *
 *  EXAMPLE   list: 5 <-> 10 <-> 15 <-> 20,   deleteAtIndex(1)
 *      target   = [10]     (node_at(1))
 *      prevNode = [5]
 *      nextNode = [15]
 *      [5].next  = [15]    5 -> 15
 *      [15].prev = [5]     5 <- 15
 *      delete [10]
 *      result : 5 <-> 15 <-> 20      size = 3
 *
 *  EDGE CASES HANDLED
 *    - Empty list           : pos >= size (0 >= 0) is true, so it throws.
 *    - Single node, pos 0   : case 1: head becomes NULL, so tail is also set
 *                             to NULL. Case 1 is checked BEFORE case 2,
 *                             because with size 1, pos 0 == size - 1 and the
 *                             tail branch would read tail.prev == NULL.
 *    - pos == size - 1      : case 2. Here size >= 2 (pos != 0), so tail.prev
 *                             is non-NULL and tail.next is safe to write.
 *    - Middle position      : both neighbours exist (size >= 3).
 *    - Dangling pointers    : neighbours are re-linked BEFORE the delete.
 *  COMPLEXITY : Time O(n) general, O(1) at pos 0 or size - 1 | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  5.8  search_ll(key)  -  find the index of a value
 * ----------------------------------------------------------------------------
 *  IDEA
 *    Linear scan from head. Return the index of the FIRST node whose data
 *    equals key, or -1 if no node matches.
 *
 *  PSEUDOCODE
 *      SEARCH(key):
 *          temp <- head
 *          idx  <- 0
 *          while temp != NULL:
 *              if temp.data == key:  return idx
 *              temp <- temp.next
 *              idx  <- idx + 1
 *          return -1
 *
 *  EXAMPLE   list: 5 <-> 15 <-> 20
 *      search(15) -> idx 0: 5 != 15, idx 1: 15 == 15 -> returns 1
 *      search(99) -> reaches NULL -> returns -1
 *
 *  EDGE CASES HANDLED
 *    - Empty list      : head is NULL, the loop never runs, returns -1.
 *    - Duplicates      : returns the first occurrence (lowest index).
 *    - Key at the tail : found on the last iteration.
 *    - const method    : search does not modify the list, so it is const.
 *  NOTE
 *    A -1 return is safe here because an INDEX is never negative. (For a
 *    VALUE lookup such as getElementAtIndex, -1 would be ambiguous.)
 *  COMPLEXITY : Time O(n) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  5.9  getElementAtIndex(idx)  -  read the value at an index
 * ----------------------------------------------------------------------------
 *  PSEUDOCODE
 *      GET_ELEMENT_AT_INDEX(idx):
 *          if idx < 0 or idx >= size:
 *              throw out_of_range("Invalid index")
 *          return NODE_AT(idx).data
 *
 *  EXAMPLE   list: 5 <-> 15 <-> 20,   getElementAtIndex(2) -> 20
 *
 *  EDGE CASES HANDLED
 *    - Empty list / idx >= size / idx < 0 : throws std::out_of_range.
 *    - Why throw and not return -1        : -1 might be a legitimate stored
 *                                           value, so the caller could not
 *                                           tell "error" from "data".
 *    - First and last index               : node_at takes 0 steps (O(1)).
 *  COMPLEXITY : Time O(n) worst case, O(1) at either end | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  5.10  print() and printReverse()
 * ----------------------------------------------------------------------------
 *  PSEUDOCODE
 *      PRINT():                                  // front to back
 *          if head == NULL:  output "List is empty."; return
 *          temp <- head
 *          while temp != NULL:
 *              output temp.data, " <-> "
 *              temp <- temp.next
 *          output "NULL"
 *
 *      PRINT_REVERSE():                          // back to front
 *          if tail == NULL:  output "List is empty."; return
 *          temp <- tail
 *          while temp != NULL:
 *              output temp.data, " <-> "
 *              temp <- temp.prev                 // uses the prev links
 *          output "NULL"
 *
 *  EXAMPLE   list: 5 <-> 15 <-> 20
 *      print()        : 5 <-> 15 <-> 20 <-> NULL
 *      printReverse() : 20 <-> 15 <-> 5 <-> NULL
 *
 *  USE AS A TEST
 *    If print() and printReverse() show exactly mirrored output after an
 *    operation, the next AND prev links are consistent (invariant I3).
 *    If they disagree, a pointer update was missed.
 *
 *  EDGE CASES HANDLED : empty list prints a message instead of nothing.
 *  COMPLEXITY : Time O(n) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  5.11  size()
 * ----------------------------------------------------------------------------
 *      SIZE():  return size            // cached counter, no traversal
 *  COMPLEXITY : Time O(1) | Space O(1)
 *  Every operation that adds or removes a node must update the counter.
 *
 * ----------------------------------------------------------------------------
 *  5.12  clear()  -  remove every element
 * ----------------------------------------------------------------------------
 *  PSEUDOCODE
 *      CLEAR():
 *          temp <- head
 *          while temp != NULL:
 *              nextNode <- temp.next             // SAVE the next node first
 *              delete temp
 *              temp <- nextNode
 *          head <- NULL
 *          tail <- NULL
 *          size <- 0
 *
 *  EXAMPLE   list: 5 <-> 15 <-> 20
 *      iteration 1: save [15], delete [5],  temp = [15]
 *      iteration 2: save [20], delete [15], temp = [20]
 *      iteration 3: save NULL, delete [20], temp = NULL  -> loop ends
 *      head = tail = NULL, size = 0
 *
 *  EDGE CASES HANDLED
 *    - Empty list      : the loop is skipped; calling clear() twice is safe.
 *    - Use after free  : reading temp.next AFTER delete temp is undefined
 *                        behaviour. That is why nextNode is saved first.
 *    - Reset all three : head, tail AND size, otherwise stale pointers remain.
 *  COMPLEXITY : Time O(n) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  5.13  Destructor and deleted copy operations
 * ----------------------------------------------------------------------------
 *  DESTRUCTOR
 *      ~DoublyLinkedList():  clear()
 *    The class owns heap memory (every Node comes from "new"), so it must
 *    free it when the list object dies. Otherwise every list leaks.
 *
 *  COPY CONSTRUCTOR / COPY ASSIGNMENT  =  delete
 *    The default copy would copy only head, tail and _size, so TWO list
 *    objects would point at the SAME nodes. When both destructors run, each
 *    deletes the same nodes: a double free (crash or corruption). The Rule
 *    of Three says: if you write a destructor, also handle copying. Here the
 *    safe and simple choice is to forbid copying.
 *    (Alternative: write a deep copy that allocates new nodes.)
 *
 *
 * ============================================================================
 *  6. EDGE CASE MASTER TABLE
 * ============================================================================
 *
 *  Always test an operation on: EMPTY, ONE NODE, TWO NODES, then a normal list.
 *
 *   Operation          Empty            One node          First / last       Middle
 *   -----------------  ---------------  ----------------  -----------------  -------
 *   push_front         head = tail =    link old head     -                  -
 *                      newNode          (else branch)
 *   push_back          head = tail =    link old tail     -                  -
 *                      newNode          (else branch)
 *   pop_front          throws           head = tail =     move head, cut     -
 *                      underflow_error  NULL              head.prev
 *   pop_back           throws           head = tail =     move tail, cut     -
 *                      underflow_error  NULL              tail.next
 *   insert_middle      only pos 0 is    pos 0 or 1 are    pos 0 / size use   4 pointer
 *                      valid; sets      the boundary      push_front /       updates
 *                      head and tail    cases             push_back logic
 *   deleteAtIndex      throws           pos 0: head AND   pos 0 / size-1     bridge
 *                      out_of_range     tail -> NULL      handled first      both sides
 *   search_ll          returns -1       checks one node   first match wins   -
 *   getElementAtIndex  throws           idx 0 only        O(1) at the ends   node_at
 *   print/printReverse prints message   one element       -                  -
 *   clear              safe no-op       frees one node    -                  -
 *
 *  Invalid index (negative, or too large) -> insert/delete/get throw
 *  std::out_of_range. Check the negative case BEFORE casting to size_t.
 *
 *
 * ============================================================================
 *  7. COMMON BUGS AND HOW TO AVOID THEM
 * ============================================================================
 *
 *   1. Forgetting tail when the first node is inserted.
 *        Symptom : push_back after push_front crashes.
 *        Fix     : in the empty branch set BOTH head and tail.
 *
 *   2. Not clearing the new head's prev (or new tail's next) after a pop.
 *        Symptom : a pointer to freed memory; later traversal reads garbage.
 *        Fix     : head.prev = NULL after pop_front, tail.next = NULL after
 *                  pop_back.
 *
 *   3. Deleting the single node twice in pop_back.
 *        Symptom : crash (double free).
 *        Fix     : delete exactly once, after head and tail are updated.
 *
 *   4. Reading a node after delete.
 *        Symptom : clear() loops forever or crashes.
 *        Fix     : save temp.next in nextNode BEFORE delete temp.
 *
 *   5. Updating only the forward links in insert/delete.
 *        Symptom : print() is right, printReverse() is wrong.
 *        Fix     : always repair BOTH next and prev on BOTH neighbours.
 *
 *   6. Overwriting a pointer before saving it.
 *        Example : prevNode.next = newNode, then trying to read the old
 *                  prevNode.next to link newNode forward: it is already lost.
 *        Fix     : hold nextNode in a variable first (the code does).
 *
 *   7. Checking pos == size before pos == 0.
 *        Symptom : NULL dereference when inserting into an empty list.
 *        Fix     : handle pos == 0 first.
 *
 *   8. Forgetting to update size.
 *        Symptom : bounds checks wrong, later operations throw or crash.
 *        Fix     : update size in every path, including early returns.
 *
 *   9. Comparing int with size_t.
 *        Symptom : a negative pos becomes a huge unsigned number.
 *        Fix     : test pos < 0 first, then static_cast<size_t>(pos).
 *
 *  10. Returning -1 / silently ignoring errors.
 *        Fix     : throw std::out_of_range or std::underflow_error.
 *
 *
 * ============================================================================
 *  8. COMPLEXITY SUMMARY   (n = number of elements, Space = auxiliary)
 * ============================================================================
 *
 *   Operation           Time                                   Space
 *   ------------------  -------------------------------------  ------
 *   push_front          O(1)                                   O(1)
 *   push_back           O(1)                                   O(1)
 *   pop_front           O(1)                                   O(1)
 *   pop_back            O(1)                                   O(1)
 *   insert_middle       O(n) general; O(1) at pos 0 or size    O(1)
 *   deleteAtIndex       O(n) general; O(1) at pos 0 or size-1  O(1)
 *   getElementAtIndex   O(n) worst; O(1) at either end         O(1)
 *   search_ll           O(n)                                   O(1)
 *   print/printReverse  O(n)                                   O(1)
 *   size                O(1)                                   O(1)
 *   clear / destructor  O(n)                                   O(1)
 *
 *   Index operations cost O(min(i, n - i)), which is at most about n/2 steps,
 *   but is still O(n) in Big-O terms.
 *
 *
 * ============================================================================
 *  9. FULL DRY RUN   (state after each operation)
 * ============================================================================
 *
 *   #   Operation              List                            Size  head  tail
 *   --  ---------------------  ------------------------------  ----  ----  ----
 *   0   (start)                NULL                            0     NULL  NULL
 *   1   push_back(10)          10                              1     10    10
 *   2   push_back(20)          10 <-> 20                       2     10    20
 *   3   push_front(5)          5 <-> 10 <-> 20                 3     5     20
 *   4   insert_middle(15, 2)   5 <-> 10 <-> 15 <-> 20          4     5     20
 *   5   deleteAtIndex(1)       5 <-> 15 <-> 20                 3     5     20
 *   6   search_ll(15)          returns 1                       3     5     20
 *   7   getElementAtIndex(2)   returns 20                      3     5     20
 *   8   printReverse()         20 <-> 15 <-> 5 <-> NULL        3     5     20
 *   9   pop_back()             5 <-> 15                        2     5     15
 *  10   pop_front()            15                              1     15    15
 *  11   pop_back()             NULL                            0     NULL  NULL
 *  12   pop_front()            throws underflow_error          0     NULL  NULL
 *
 *   Rows 10 and 11 are the single-node and become-empty transitions, which is
 *   where most bugs hide.
 *
 *
 * ============================================================================
 *  10. KEY TAKEAWAYS
 * ============================================================================
 *
 *   - A DLL node has prev, data, next. Both ends are O(1) with head + tail.
 *   - pop_back is O(1) in a DLL and O(n) in a singly list: the main win.
 *   - Cost: one extra pointer per node and twice the links to maintain.
 *   - Wire the new node first, then fix the neighbours. Unlink, then delete.
 *   - Empty and single-node lists are the edge cases that break most code:
 *     always set/clear BOTH head and tail.
 *   - Validate indexes (including negatives) before touching any pointer.
 *   - Use print() vs printReverse() to verify that next and prev agree.
 *   - Own raw memory? Provide a destructor and deal with copying.
 *
 *   Related files
 *     Full implementation : 14_Linked_List_Problem_Solving/
 *                           03_Implementation_on_Doubly_Linked_List.cpp
 *     Next notes          : 03_Circular_Linked_List.cpp
 */

// Notes-only file. Empty main() keeps the file buildable as a standalone target.
int main() {
    return 0;
}