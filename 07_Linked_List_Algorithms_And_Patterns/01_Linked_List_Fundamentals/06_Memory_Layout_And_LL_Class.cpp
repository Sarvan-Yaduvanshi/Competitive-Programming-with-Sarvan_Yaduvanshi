/*
 * Author  : Sarvan Yaduvanshi
 * Created : 2026-10-17
 *
 * ============================================================================
 *  MEMORY LAYOUT: ARRAY vs LINKED LIST  -  NOTES + PSEUDOCODE
 *  Folder : 01_Linked_List_Basics
 *  Level  : Basic -> Advanced (how data sits in memory and why it matters)
 * ============================================================================
 *
 *  PSEUDOCODE LEGEND
 *      a <- b      assign b to a            NULL   the null pointer (nullptr)
 *      p.next      next field of the node p points to  (p->next in C++)
 *
 *  CONTENTS
 *    1. Where data lives: stack and heap
 *    2. Layout: array vs linked list
 *    3. Memory cost
 *    4. Cache behaviour
 *    5. Measuring it: benchmark method (pseudocode)
 *    6. When to use an array and when to use a linked list
 *    7. Linked list class: OOP design (pseudocode)
 *    8. Myths and corrections
 *    9. Key takeaways
 *
 *
 * ============================================================================
 *  1. WHERE DATA LIVES: STACK AND HEAP
 * ============================================================================
 *
 *    STACK : local variables, created and destroyed automatically with the
 *            function call. The pointer variable head is a stack variable.
 *    HEAP  : memory you request with new and release with delete. Every linked
 *            list node lives here, so it survives after the function that created
 *            it returns, until you delete it.
 *
 *        stack                          heap
 *        +------+                       +----+-------+      +----+------+
 *        | head | -------------------->  | 10 | o-----+----> | 20 | NULL |
 *        +------+                       +----+-------+      +----+------+
 *        (8-byte pointer)               (each node is a separate allocation)
 *
 *    A pointer stores an ADDRESS. On a typical 64-bit system every pointer is 8
 *    bytes, whatever it points to.
 *
 *
 * ============================================================================
 *  2. LAYOUT: ARRAY vs LINKED LIST
 * ============================================================================
 *
 *  ARRAY : one contiguous block, elements side by side, fixed stride.
 *
 *      address :  0x100   0x104   0x108   0x10C   0x110
 *      value   :  [ 10 ]  [ 20 ]  [ 30 ]  [ 40 ]  [ 50 ]
 *
 *      address(i) = base + i * sizeof(element)        ->  access by index is O(1)
 *
 *  LINKED LIST : separate allocations at unrelated addresses, joined by pointers.
 *
 *      @0x100            @0x2F0            @0x8A4
 *      +----+-------+    +----+-------+    +----+------+
 *      | 10 | 0x2F0 |--->| 20 | 0x8A4 |--->| 30 | NULL |
 *      +----+-------+    +----+-------+    +----+------+
 *
 *      There is no address formula. The only way to find node i is to follow i
 *      links from the head              ->  access by index is O(n)
 *
 *  SIDE BY SIDE
 *
 *   Property                Array / vector            Linked list
 *   ----------------------  ------------------------  ---------------------------
 *   Memory block            one contiguous block      many separate allocations
 *   Order is defined by     position in memory        the next (and prev) pointers
 *   Size                    fixed (or resize + copy)  grows one node at a time
 *   Access by index         O(1)                      O(n)
 *   Insert / delete middle  O(n) (shift elements)     O(1) given the node, else O(n)
 *   Pointers stored         none                      1 per node (2 if doubly)
 *
 *
 * ============================================================================
 *  3. MEMORY COST
 * ============================================================================
 *
 *  NODE SIZE (typical 64-bit platform, data = int)
 *      singly node : int (4) + padding (4) + next pointer (8)                = 16 bytes
 *      doubly node : int (4) + padding (4) + next (8) + prev (8)             = 24 bytes
 *    The padding keeps the 8-byte pointer aligned. The "extra" memory is therefore
 *    more than just one 8-byte pointer: for int data only 4 of 16 bytes (25%) are
 *    payload.
 *
 *  ALLOCATOR OVERHEAD
 *    Each new is a separate allocation. The allocator keeps a small header per
 *    block and rounds sizes up (for example, glibc commonly serves a 16- or 24-byte
 *    request from a 32-byte chunk). Exact numbers depend on the platform, so treat
 *    them as estimates.
 *
 *      Storing 10^6 ints            Payload     Typical total
 *      ---------------------------  ----------  --------------------------
 *      array / vector               4 MB        about 4 MB
 *      singly list (16-byte nodes)  16 MB       16 MB or more (often ~32 MB)
 *      doubly list (24-byte nodes)  24 MB       24 MB or more (often ~32 MB)
 *
 *    Rule of thumb: for small elements, links and allocator bookkeeping cost
 *    several times more memory than the data itself.
 *
 *
 * ============================================================================
 *  4. CACHE BEHAVIOUR
 * ============================================================================
 *
 *  BACKGROUND
 *    The CPU does not read single bytes from main memory. It loads a whole CACHE
 *    LINE (typically 64 bytes) into a fast cache, and a hardware prefetcher guesses
 *    the next lines when it sees sequential access. A cache hit costs about a
 *    nanosecond; a miss that goes to main memory costs on the order of 50-100 ns.
 *
 *  ARRAY TRAVERSAL
 *    Neighbouring elements share a cache line: one line holds 16 ints, so one miss
 *    pays for 16 elements, and the prefetcher streams the next lines ahead of time.
 *    This is excellent spatial locality.
 *
 *  LINKED LIST TRAVERSAL ("POINTER CHASING")
 *    The address of the next node is known only AFTER the current node has been
 *    loaded, so the CPU cannot look ahead. If the nodes are scattered, each hop can
 *    be a cache miss that stalls the CPU until memory answers.
 *
 *      array :  [ 10 20 30 40 50 60 ... 16 ints in one cache line ]   one miss, 16 elements
 *      list  :   node -> (wait) -> node -> (wait) -> node -> (wait)   up to one miss per node
 *
 *  IT DEPENDS ON WHERE THE NODES LANDED
 *    - Best case : nodes allocated one after another from a fresh heap often sit
 *                  close together, so traversal is partly prefetch-friendly. Even
 *                  then a 16-byte node plus allocator overhead fits only about two
 *                  nodes per cache line, versus 16 ints per line in an array.
 *    - Worst case: after many inserts, deletes and a fragmented heap, consecutive
 *                  nodes are far apart and almost every hop misses.
 *
 *  BIG-O vs REALITY
 *    Both traversals are O(n), but the linked list has a much larger constant
 *    factor. The slowdown is typically a few times in the best case and can reach
 *    ten times or more (sometimes much more for large n) in the worst case. It
 *    grows once the data no longer fits in cache. This is why a vector can beat a
 *    linked list even for middle insertion and deletion at ordinary sizes.
 *
 *
 * ============================================================================
 *  5. MEASURING IT: BENCHMARK METHOD
 * ============================================================================
 *
 *  GOAL : compare the time to sum N elements stored in an array and in a list.
 *
 *  PSEUDOCODE
 *      BENCHMARK(N, trials):
 *          arr      <- array holding 0 .. N-1
 *          listSeq  <- linked list holding 0 .. N-1, nodes allocated in order
 *          listMix  <- linked list holding the same values, nodes allocated in a
 *                      random order (simulates a fragmented heap)
 *          for each trial:
 *              t0 <- clock();   sumA <- 0
 *              for i from 0 to N-1:  sumA <- sumA + arr[i]
 *              timeArray <- clock() - t0
 *
 *              t0 <- clock();   sumL <- 0;   cur <- head of the list
 *              while cur != NULL:  sumL <- sumL + cur.data;  cur <- cur.next
 *              timeList <- clock() - t0
 *          assert sumA == sumL
 *          print sumA and sumL                   // so the compiler cannot delete the loops
 *          report the MEDIAN of the trials for each structure
 *          free every node
 *
 *  GOOD BENCHMARK HABITS
 *    - Compile with optimisations (for example -O2). Debug builds give
 *      meaningless comparisons.
 *    - Print or otherwise use the sums: an unused result lets the compiler remove
 *      the whole loop.
 *    - Repeat the run and use the median; discard the first (cold-cache) run.
 *    - Try a small N (fits in cache) and a large N (does not): the gap widens
 *      with N.
 *    - Measure both the in-order and the shuffled list. A single run with nodes
 *      allocated back to back understates the real-world cost.
 *    - Use integer division carefully when printing a ratio (a ratio of 1.9 prints
 *      as 1 with integer division); divide as floating point.
 *
 *
 * ============================================================================
 *  6. WHEN TO USE AN ARRAY AND WHEN TO USE A LINKED LIST
 * ============================================================================
 *
 *   Need                          Array / vector      Linked list
 *   ----------------------------  ------------------  -------------------------------
 *   Random access by index        O(1)                O(n)
 *   Sequential traversal          fast (cache)        slower (pointer chasing)
 *   Insert at the front           O(n)                O(1)
 *   Insert / delete in the middle O(n)                O(1) with a pointer to the node *
 *   Insert / delete at the back   O(1) amortised      O(1) insert with tail; O(n)
 *                                 (vector)            delete in a singly list
 *   Unknown or changing size      vector grows        grows one node at a time
 *   Pointers / iterators stay     no (invalidated on  yes (only the erased node's)
 *     valid after changes         growth or shifts)
 *   Binary search                 O(log n)            O(n) pointer steps (see Sec. 8)
 *   Sorting                       std::sort           merge sort (no random access)
 *   LRU / LFU cache               -                   yes (doubly list + hash map)
 *   Stack / queue                 yes                 yes
 *
 *   * O(1) only if you ALREADY hold a pointer to the position. Finding the
 *     position first costs O(n).
 *
 *  PRACTICAL ADVICE
 *    In competitive programming use arrays or vectors unless you NEED a linked list
 *    property: cheap relinking at known positions, stable references, or splicing
 *    nodes. When a list is needed and speed matters, an array-based list (indices
 *    instead of pointers, nodes in a preallocated array) removes the allocation cost
 *    and the scattering.
 *
 *
 * ============================================================================
 *  7. LINKED LIST CLASS: OOP DESIGN
 * ============================================================================
 *
 *  Encapsulation means the pointers are hidden behind methods. Callers use
 *  push_front, pop_front and so on, and can never break the links by hand. The
 *  full tested versions are in 13_Linked_List_Problem_Solving; this is the design.
 *
 *  PSEUDOCODE (class skeleton)
 *
 *      CLASS LinkedList<T>                       // T = any element type (template)
 *          PRIVATE
 *              STRUCT Node:   data : T,  next : pointer to Node    // hidden type
 *              head : pointer to Node  <- NULL
 *              tail : pointer to Node  <- NULL     // makes push_back O(1)
 *              size : integer          <- 0        // makes size() O(1)
 *          PUBLIC
 *              constructor():    head <- NULL;  tail <- NULL;  size <- 0
 *              destructor():     free every node (save next BEFORE each delete)
 *              copy operations:  forbid, or deep-copy (never shallow-copy)
 *              push_front(v)     push_back(v)
 *              pop_front()       pop_back()
 *              front()           back()           // throw if the list is empty
 *              contains(v)       -> true / false
 *              size()            empty()
 *              print()
 *              begin()           end()            // iterator support
 *
 *  ITERATOR (lets a range-based for loop walk the list)
 *
 *      CLASS Iterator:            holds one pointer p to a Node
 *          dereference   : return p.data
 *          advance (++)  : p <- p.next
 *          not-equal (!=): return p != other.p
 *      begin() : return Iterator(head)
 *      end()   : return Iterator(NULL)            // one past the last node
 *      loop    : for each value in list  ==  for it from begin() while it != end()
 *
 *  DESIGN RULES THAT KEEP THE CLASS CORRECT
 *    - Node is private: invariants cannot be broken from outside.
 *    - Own raw memory -> write a destructor AND handle copying. A default
 *      (shallow) copy makes two lists own the same nodes, and both destructors free
 *      them: a double free (Rule of Three).
 *    - Keep a tail pointer, or push_back must walk the list every time (O(n),
 *      and O(n^2) to build n elements).
 *    - Use an unsigned size type for the counter and report errors with
 *      exceptions (empty pop, invalid index) instead of returning a value that
 *      could be real data.
 *    - Make read-only methods const, and offer a const iterator for const lists.
 *    - Iterators to a node become invalid when that node is erased.
 *    - Generic code copies T on insert: for large T accept it by const reference
 *      or move it into the node.
 *
 *
 * ============================================================================
 *  8. MYTHS AND CORRECTIONS
 * ============================================================================
 *
 *   MYTH                                      REALITY
 *   ----------------------------------------  --------------------------------------
 *   "Every list access is a cache miss."      Often, not always. Nodes allocated back
 *                                             to back can be neighbours. The risk is
 *                                             that nothing guarantees it.
 *   "Arrays are always 5-10x faster."         The gap depends on n, node layout, and
 *                                             hardware: from a few times to much more.
 *                                             Measure, do not memorise a number.
 *   "A node only wastes 8 bytes."             Also padding and allocator overhead; a
 *                                             16-byte node can occupy a 32-byte chunk.
 *   "List insertion is O(1)."                 Only with a pointer to the position;
 *                                             finding it is O(n).
 *   "Binary search on a list is O(n log n)."  It needs only O(log n) comparisons, but
 *                                             reaching each midpoint costs pointer
 *                                             steps: n/2 + n/4 + ... = O(n) in total.
 *                                             Still no better than a linear scan.
 *   "A list is better because it has no       It trades a resize cost for a per-node
 *    resize cost."                            allocation cost and poor locality.
 *
 *
 * ============================================================================
 *  9. KEY TAKEAWAYS
 * ============================================================================
 *
 *   - Array = one contiguous block, order by position, address by formula.
 *     List = scattered heap nodes, order by pointers, no address formula.
 *   - The head pointer lives on the stack; nodes live on the heap and must be
 *     deleted.
 *   - A node costs more than its data: pointer, padding, allocator overhead
 *     (16 bytes for a singly int node, often a 32-byte chunk).
 *   - Traversal is O(n) for both, but arrays win by a constant factor because of
 *     cache lines and prefetching; lists suffer pointer chasing.
 *   - Linked lists win on cheap relinking at known positions, stable pointers
 *     and iterators, and splicing, not on raw speed.
 *   - Benchmark with optimisations, repeat runs, large and small n, in-order and
 *     shuffled nodes.
 *   - A good list class hides Node, keeps head, tail and size, frees nodes in the
 *     destructor, and forbids or deep-copies on copy.
 *
 *   Related files
 *     Previous : 04_Traversal_And_Counting.cpp
 *     Before   : Linked_List_Fundamentals.cpp (definitions and types)
 *     Code     : 13_Linked_List_Problem_Solving/
 */

// Notes-only file. Empty main() keeps the file buildable as a standalone target.
int main() {
    return 0;
}