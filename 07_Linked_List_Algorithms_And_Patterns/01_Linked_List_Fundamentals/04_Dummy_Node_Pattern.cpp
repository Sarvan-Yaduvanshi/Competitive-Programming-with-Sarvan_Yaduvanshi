/*
 * Author  : Sarvan Yaduvanshi
 * Created : 2026-10-17
 *
 * ============================================================================
 *  DUMMY NODE (SENTINEL NODE) PATTERN IN LINKED LISTS  -  NOTES + PSEUDOCODE
 *  Folder : 07_Linked_List_Algorithms_And_Patterns
 *  Level  : Zero -> Advanced (concept, templates, dry runs, edge cases, problems)
 * ============================================================================
 *
 *  PSEUDOCODE LEGEND
 *      a <- b      assign b to a            NULL   the null pointer (nullptr)
 *      p.next      next field of the node p points to  (p->next in C++)
 *      p.data      value stored in the node (val in LeetCode's ListNode)
 *
 *  CONTENTS
 *    1. The problem: the head is a special case
 *    2. What is a dummy node?
 *    3. Why it works
 *    4. C++ setup and memory rules
 *    5. The templates
 *    6. Pattern walkthroughs (each: idea, dry run, pseudocode, edge cases)
 *         6.1  Remove all elements with a value     (LeetCode 203)
 *         6.2  Remove the Nth node from the end     (LeetCode 19)
 *         6.3  Merge two sorted lists               (LeetCode 21)
 *         6.4  Partition a list around x            (LeetCode 86)
 *         6.5  Insert into a sorted list
 *         6.6  Add two numbers                      (LeetCode 2)
 *         6.7  Remove duplicates, keep none         (LeetCode 82)
 *         6.8  Swap nodes in pairs                  (LeetCode 24)
 *    7. Advanced ideas
 *    8. When you do NOT need a dummy node
 *    9. Edge case checklist
 *   10. Common mistakes
 *   11. Complexity
 *   12. Recognising the pattern + practice roadmap
 *   13. Quick revision Q&A and key takeaways
 *
 *
 * ============================================================================
 *  1. THE PROBLEM: THE HEAD IS A SPECIAL CASE
 * ============================================================================
 *
 *  Almost every linked-list modification has the same shape: find the node
 *  BEFORE the one you want to change, then rewrite that node's next pointer.
 *
 *      delete X :   prev.next <- X.next
 *      insert N :   N.next <- prev.next;  prev.next <- N
 *
 *  This works for every node except the FIRST one. The first node has no
 *  predecessor: the only thing pointing at it is the variable head, which is a
 *  different kind of thing from a next field. So the head needs its own code path.
 *
 *  EXAMPLE : delete every node equal to 10 from   10 -> 10 -> 20 -> 10 -> 30
 *
 *      WITHOUT A DUMMY NODE (two code paths)
 *
 *          // path 1: the head itself may need deleting, repeatedly
 *          while head != NULL and head.data == 10:
 *              head <- head.next                      // changes the head VARIABLE
 *          // path 2: every other node is deleted through its predecessor
 *          prev <- head
 *          while prev != NULL and prev.next != NULL:
 *              if prev.next.data == 10:  prev.next <- prev.next.next
 *              else:                     prev <- prev.next
 *          return head
 *
 *      Two loops, one extra emptiness check (head may become NULL), and the
 *      function must return the possibly changed head. Every head-modifying
 *      problem repeats this, and forgetting the head case is a classic bug.
 *
 *
 * ============================================================================
 *  2. WHAT IS A DUMMY NODE?
 * ============================================================================
 *
 *  DEFINITION
 *    A dummy node (also called a sentinel node or header node) is an extra node
 *    placed BEFORE the real head. It holds no meaningful data. Its only job is to
 *    be a stable predecessor for the first real node, so the head stops being a
 *    special case.
 *
 *      WITHOUT :   head -> [10] -> [20] -> [30] -> NULL
 *
 *      WITH    :   dummy -> [10] -> [20] -> [30] -> NULL
 *                    ^
 *                    +-- not part of the answer; dummy.next is the real head
 *
 *  THE THREE RULES
 *    1. Create the dummy and point it at the head:     dummy.next <- head
 *    2. Do all the work through pointers that start at the dummy.
 *    3. Return dummy.next (the CURRENT first real node), never the old head.
 *
 *  NAMES YOU WILL SEE
 *      dummy / sentinel / header node : the same idea.
 *      Temporary dummy  : created inside one function, discarded at the end
 *                         (this file's main topic).
 *      Permanent sentinel : a dummy kept inside a list class for its whole life
 *                         (see Section 7 and the Sentinel Doubly Linked List).
 *
 *
 * ============================================================================
 *  3. WHY IT WORKS
 * ============================================================================
 *
 *    - With the dummy in front, the first real node has a predecessor, like every
 *      other node. The head becomes an ordinary interior node.
 *    - One uniform rule then covers every position:
 *          "stand on the predecessor, change predecessor.next"
 *    - The only pointer that ever changes the list's start is  dummy.next. That
 *      is a FIELD, updated by the same statements as any other link, instead of
 *      a separate head variable.
 *    - dummy.next is always up to date. The original variable head may point to a
 *      node that was deleted or is no longer first, which is why you return
 *      dummy.next.
 *    - When the list is empty, dummy.next is NULL and the code still works.
 *
 *  FIGURE : deleting the first node
 *
 *      before :  dummy -> [10] -> [20] -> [30] -> NULL      prev = dummy
 *      prev.next <- prev.next.next          (same statement as any other delete)
 *      after  :  dummy -------> [20] -> [30] -> NULL        [10] is bypassed
 *      return dummy.next   ->   [20]
 *
 *
 * ============================================================================
 *  4. C++ SETUP AND MEMORY RULES
 * ============================================================================
 *
 *  SETUP (pseudocode)
 *      dummy      <- Node(0)            // a real node object; the 0 is a placeholder
 *      dummy.next <- head
 *      prev       <- address of dummy   // the walker starts at the dummy
 *
 *  In C++ with LeetCode's ListNode this is:  a local ListNode dummy(0),
 *  dummy.next = head, ListNode* prev = &dummy.
 *
 *  MEMORY RULES
 *    1. STACK DUMMY (usual in contests). The dummy is a local object. It is
 *       destroyed when the function returns, so there is nothing to free.
 *    2. Returning dummy.next is SAFE: it points to a real list node on the heap.
 *       Returning the ADDRESS OF dummy is a bug: it points to a destroyed local.
 *       Make sure no real node's next ever points to the dummy either.
 *    3. HEAP DUMMY (new). If you allocate it with new, you must delete it before
 *       returning, after saving dummy.next:
 *           result <- dummy.next;  delete dummy;  return result
 *    4. Nodes you REMOVE from the list are still your responsibility. In contest
 *       code they are usually left alone; in production code delete them after
 *       unlinking (prev.next <- victim.next, then delete victim).
 *    5. The dummy's data value is irrelevant for most problems. Never READ it as
 *       if it were real data (for example when comparing with the previous node's
 *       value, Section 6.7).
 *
 *
 * ============================================================================
 *  5. THE TEMPLATES
 * ============================================================================
 *
 *  TEMPLATE A : MODIFY THE LIST IN PLACE (the head may change)
 *
 *      dummy.next <- head
 *      prev       <- dummy
 *      while prev.next != NULL:
 *          if prev.next must be changed:   rewire through prev     (prev may stay)
 *          else:                           prev <- prev.next
 *      return dummy.next
 *    Used by: remove elements, delete nodes, insert into a sorted list, remove
 *    duplicates, swap pairs, reverse a segment.
 *
 *  TEMPLATE B : BUILD A NEW LIST (append at a tail)
 *
 *      tail <- dummy                        // dummy.next is still NULL
 *      for each item to output:
 *          tail.next <- (existing or new node)
 *          tail      <- tail.next
 *      tail.next <- NULL (or the remaining nodes)
 *      return dummy.next
 *    The first output node needs no special case: it is just dummy.next.
 *    Used by: merge sorted lists, add two numbers, copy / filter a list.
 *
 *  TEMPLATE C : SPLIT INTO SEVERAL LISTS (one dummy and tail per list)
 *
 *      dummyA, tailA ;  dummyB, tailB
 *      for each node cur in the input:
 *          append cur to tailA or tailB according to a rule
 *      tailA.next <- dummyB.next            // join the lists
 *      tailB.next <- NULL                   // CUT the end (avoids a cycle)
 *      return dummyA.next
 *    Used by: partition list, odd-even list.
 *
 *  TEMPLATE D : OPERATE ON A SEGMENT (the dummy anchors "the node before it")
 *
 *      dummy.next <- head
 *      before <- dummy                      // advance to the node before the segment
 *      ... reverse / move / delete the segment, reconnect through before ...
 *      return dummy.next
 *    Used by: reverse between positions, reverse in k-groups, delete a range.
 *
 *
 * ============================================================================
 *  6. PATTERN WALKTHROUGHS
 * ============================================================================
 *
 * ----------------------------------------------------------------------------
 *  6.1  REMOVE ALL ELEMENTS WITH A VALUE            (LeetCode 203)
 * ----------------------------------------------------------------------------
 *  PROBLEM  Given the head of a list and a value val, remove every node whose
 *           data equals val and return the new head.
 *  IDEA     Template A. prev stays put after a deletion, because the next node
 *           may also match.
 *
 *  DRY RUN   list: 10 -> 10 -> 20 -> 10 -> 30,   val = 10
 *      start  : dummy -> [10a] -> [10b] -> [20] -> [10c] -> [30] -> NULL      prev = dummy
 *
 *      step 1 : prev.next = 10a, matches    -> prev.next = 10b          prev stays dummy
 *               dummy -> [10b] -> [20] -> [10c] -> [30]
 *      step 2 : prev.next = 10b, matches    -> prev.next = 20           prev stays dummy
 *               dummy -> [20] -> [10c] -> [30]
 *      step 3 : prev.next = 20, no match    -> prev = 20
 *      step 4 : prev.next = 10c, matches    -> prev.next = 30           prev stays at 20
 *               dummy -> [20] -> [30]
 *      step 5 : prev.next = 30, no match    -> prev = 30
 *      step 6 : prev.next = NULL            -> loop ends
 *      return dummy.next = [20]       result : 20 -> 30 -> NULL
 *
 *  PSEUDOCODE
 *      REMOVE_ELEMENTS(head, val):
 *          dummy.next <- head
 *          prev <- dummy
 *          while prev.next != NULL:
 *              if prev.next.data == val:
 *                  prev.next <- prev.next.next        // bypass; prev does NOT move
 *              else:
 *                  prev <- prev.next                  // advance only on a keep
 *          return dummy.next
 *
 *  EDGE CASES
 *    - Empty list           : dummy.next = NULL, the loop never runs, returns NULL.
 *    - Head matches         : handled by the same statement (prev = dummy).
 *    - Several heads match  : prev stays on dummy, so every leading match is removed.
 *    - All nodes match      : every node is bypassed; returns NULL.
 *    - Last node matches    : prev.next <- NULL.
 *    - No node matches      : the list is returned unchanged.
 *  COMPLEXITY : Time O(n) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  6.2  REMOVE THE Nth NODE FROM THE END            (LeetCode 19)
 * ----------------------------------------------------------------------------
 *  PROBLEM  Remove the n-th node counted from the end (1 = the last node) in ONE
 *           pass and return the head.
 *  IDEA     Two pointers, slow and fast, both start at the dummy. Move fast n steps
 *           ahead. Then move both together until fast is on the LAST node. The gap
 *           of n nodes puts slow on the node BEFORE the target. The dummy matters
 *           when the target is the head: slow then stands on the dummy.
 *
 *  DRY RUN   list: 1 -> 2 -> 3 -> 4 -> 5,   n = 2   (remove 4)
 *      start   : dummy -> 1 -> 2 -> 3 -> 4 -> 5 -> NULL      slow = fast = dummy
 *      phase 1 : move fast n = 2 steps         fast = 1, then fast = 2
 *      phase 2 : while fast.next != NULL, advance both
 *                fast = 3, slow = 1
 *                fast = 4, slow = 2
 *                fast = 5, slow = 3        fast.next == NULL -> stop
 *      slow = 3, so the target is slow.next = 4
 *      slow.next <- slow.next.next            3 -> 5
 *      return dummy.next      result : 1 -> 2 -> 3 -> 5 -> NULL
 *
 *  DRY RUN (target is the head)   list: 1 -> 2,   n = 2
 *      phase 1 : fast moves 2 steps -> fast = 2; fast.next == NULL at once
 *      phase 2 : the loop does not run, so slow stays on the dummy
 *      slow.next = 1 is the target: dummy.next <- 2            result : 2 -> NULL
 *      (Without a dummy you would have to detect "n equals the length" separately.)
 *
 *  PSEUDOCODE
 *      REMOVE_NTH_FROM_END(head, n):
 *          dummy.next <- head
 *          slow <- dummy
 *          fast <- dummy
 *          repeat n times:  fast <- fast.next         // create the gap of n nodes
 *          while fast.next != NULL:
 *              slow <- slow.next
 *              fast <- fast.next
 *          slow.next <- slow.next.next                // slow is the predecessor
 *          return dummy.next
 *
 *  EDGE CASES
 *    - n == length          : the head is removed; slow stays on the dummy.
 *    - Single node, n = 1   : returns NULL.
 *    - n == 1               : the last node is removed; slow stops on the
 *                             second-to-last node.
 *    - n > length           : if the input is not guaranteed valid, stop when fast
 *                             becomes NULL while moving it, and return unchanged.
 *  COMPLEXITY : Time O(L) single pass (L = length) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  6.3  MERGE TWO SORTED LISTS                      (LeetCode 21)
 * ----------------------------------------------------------------------------
 *  PROBLEM  Merge two sorted lists into one sorted list by splicing the existing
 *           nodes together.
 *  IDEA     Template B. The dummy is a fixed starting point and tail builds the
 *           result, so the first output node needs no special case.
 *
 *  DRY RUN   list1: 1 -> 3 -> 5      list2: 2 -> 4
 *      start  : dummy -> NULL, tail = dummy
 *      step 1 : 1 <= 2, take list1      dummy -> 1                  list1 = 3
 *      step 2 : 3 <= 2? no, take list2  dummy -> 1 -> 2             list2 = 4
 *      step 3 : 3 <= 4, take list1      dummy -> 1 -> 2 -> 3        list1 = 5
 *      step 4 : 5 <= 4? no, take list2  dummy -> 1 -> 2 -> 3 -> 4   list2 = NULL
 *      loop ends (list2 is empty): attach the REMAINDER  tail.next <- list1  (5)
 *      return dummy.next      result : 1 -> 2 -> 3 -> 4 -> 5 -> NULL
 *
 *  PSEUDOCODE
 *      MERGE_SORTED(list1, list2):
 *          tail <- dummy
 *          while list1 != NULL and list2 != NULL:
 *              if list1.data <= list2.data:
 *                  tail.next <- list1;  list1 <- list1.next
 *              else:
 *                  tail.next <- list2;  list2 <- list2.next
 *              tail <- tail.next
 *          if list1 != NULL:  tail.next <- list1       // attach what is left
 *          else:              tail.next <- list2
 *          return dummy.next
 *
 *  EDGE CASES
 *    - One list empty       : the loop is skipped; the other list is attached whole.
 *    - Both empty           : dummy.next stays NULL; returns NULL.
 *    - Equal values         : "<=" takes list1 first, so the merge is stable.
 *    - Remainder            : one list always runs out first; attach the other in
 *                             ONE assignment (do not copy it node by node).
 *    - No allocation        : existing nodes are relinked, so extra space is O(1).
 *  COMPLEXITY : Time O(m + n) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  6.4  PARTITION A LIST AROUND x                   (LeetCode 86)
 * ----------------------------------------------------------------------------
 *  PROBLEM  Rearrange the list so every node with data < x comes before every node
 *           with data >= x, keeping the original relative order inside each group.
 *  IDEA     Template C. Two dummies, two tails: build a "small" list and a "large"
 *           list in one pass, then join them.
 *
 *  DRY RUN   list: 1 -> 4 -> 3 -> 2 -> 5 -> 2,   x = 3
 *      node 1 : 1 < 3   small :  1
 *      node 4 : 4 >= 3  large :  4
 *      node 3 : 3 >= 3  large :  4 -> 3
 *      node 2 : 2 < 3   small :  1 -> 2
 *      node 5 : 5 >= 3  large :  4 -> 3 -> 5
 *      node 2 : 2 < 3   small :  1 -> 2 -> 2
 *      join   : smallTail.next <- largeDummy.next          1 -> 2 -> 2 -> 4 -> 3 -> 5
 *      cut    : largeTail.next <- NULL
 *      return smallDummy.next    result : 1 -> 2 -> 2 -> 4 -> 3 -> 5 -> NULL
 *
 *  WHY THE CUT IS ESSENTIAL
 *    The last large node (5) still points at its ORIGINAL next, the last 2, which is
 *    now in the small list. Without largeTail.next <- NULL the lists form a loop
 *    (... 5 -> 2 -> 4 -> 3 -> 5 ...) and any later traversal never ends.
 *
 *  PSEUDOCODE
 *      PARTITION(head, x):
 *          smallTail <- smallDummy;  largeTail <- largeDummy
 *          cur <- head
 *          while cur != NULL:
 *              nextNode <- cur.next                    // save before relinking
 *              if cur.data < x:  smallTail.next <- cur;  smallTail <- cur
 *              else:             largeTail.next <- cur;  largeTail <- cur
 *              cur <- nextNode
 *          largeTail.next <- NULL                      // cut the old tail link
 *          smallTail.next <- largeDummy.next           // join small + large
 *          return smallDummy.next
 *
 *  EDGE CASES
 *    - Empty list             : both dummies stay empty; returns NULL.
 *    - All nodes < x          : the large list is empty; smallTail.next becomes
 *                               largeDummy.next = NULL (still correct).
 *    - All nodes >= x         : smallDummy.next is NULL, so the join yields the
 *                               large list: smallTail is smallDummy and its next
 *                               becomes the large head. Returns that head.
 *    - Stability              : nodes are appended in input order, so relative
 *                               order is kept in both groups.
 *  COMPLEXITY : Time O(n) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  6.5  INSERT INTO A SORTED LIST
 * ----------------------------------------------------------------------------
 *  PROBLEM  Insert a value into an ascending list so it stays sorted; return the
 *           head (the new node may become the head).
 *  IDEA     Template A. Stop on the node whose NEXT is the first one that is not
 *           smaller than the value. That node is the predecessor, even when it is
 *           the dummy.
 *
 *  DRY RUN   list: 10 -> 20 -> 30 -> 40
 *      insert 25 : prev = dummy; 10 < 25 -> prev = 10; 20 < 25 -> prev = 20;
 *                  30 < 25? no -> stop.   newNode.next = 30;  20.next = newNode
 *                  result : 10 -> 20 -> 25 -> 30 -> 40
 *      insert 5  : prev = dummy; prev.next = 10, 10 < 5? no -> stop at once.
 *                  newNode.next = 10;  dummy.next = newNode    (the head CHANGED)
 *                  result : 5 -> 10 -> 20 -> 30 -> 40
 *      insert 50 : prev advances to 40; prev.next = NULL -> stop.
 *                  newNode.next = NULL;  40.next = newNode
 *                  result : 10 -> 20 -> 30 -> 40 -> 50
 *      empty list, insert 7 : prev = dummy; prev.next = NULL -> stop.
 *                  newNode.next = NULL;  dummy.next = newNode   result : 7
 *
 *  PSEUDOCODE
 *      INSERT_SORTED(head, value):
 *          dummy.next <- head
 *          prev <- dummy
 *          while prev.next != NULL and prev.next.data < value:
 *              prev <- prev.next
 *          newNode <- Node(value)
 *          newNode.next <- prev.next                  // wire the new node first
 *          prev.next    <- newNode                    // then the predecessor
 *          return dummy.next
 *
 *  EDGE CASES : front, middle, back and empty list all use the same four lines.
 *  Equal values: "<" inserts BEFORE existing equals; use "<=" to insert after them.
 *  COMPLEXITY : Time O(n) | Space O(1) (plus the new node)
 *
 * ----------------------------------------------------------------------------
 *  6.6  ADD TWO NUMBERS                             (LeetCode 2)
 * ----------------------------------------------------------------------------
 *  PROBLEM  Two non-negative numbers are stored as lists of digits in REVERSE
 *           order (least significant digit first). Return their sum as a list in
 *           the same format.
 *  IDEA     Template B with NEW nodes. Add digit by digit with a carry; the dummy
 *           means the first digit needs no special case.
 *
 *  DRY RUN   l1: 2 -> 4 -> 3 (342)     l2: 5 -> 6 -> 4 (465)      expected 807
 *      step  l1  l2  carry-in  sum   digit  carry-out   result so far
 *      ----  --  --  --------  ----  -----  ----------  ---------------
 *      1     2   5   0         7     7      0           7
 *      2     4   6   0         10    0      1           7 -> 0
 *      3     3   4   1         8     8      0           7 -> 0 -> 8
 *      all digits used and carry = 0 -> stop.   return dummy.next
 *      result : 7 -> 0 -> 8 -> NULL
 *
 *  DRY RUN (final carry)   l1: 9 -> 9      l2: 1
 *      step 1 : 9 + 1 + 0 = 10 -> digit 0, carry 1
 *      step 2 : 9 + 0 + 1 = 10 -> digit 0, carry 1
 *      step 3 : both lists are empty but carry = 1 -> digit 1, carry 0
 *      result : 0 -> 0 -> 1 -> NULL      (100)
 *
 *  PSEUDOCODE
 *      ADD_TWO_NUMBERS(l1, l2):
 *          tail <- dummy;  carry <- 0
 *          while l1 != NULL or l2 != NULL or carry != 0:
 *              sum <- carry
 *              if l1 != NULL:  sum <- sum + l1.data;  l1 <- l1.next
 *              if l2 != NULL:  sum <- sum + l2.data;  l2 <- l2.next
 *              tail.next <- Node(sum mod 10)
 *              tail      <- tail.next
 *              carry     <- sum div 10
 *          return dummy.next
 *
 *  EDGE CASES
 *    - Different lengths    : a finished list contributes 0.
 *    - Final carry          : the "or carry != 0" condition appends the extra digit.
 *    - One list empty       : the other is copied digit by digit.
 *    - Both numbers zero    : 0 + 0 -> a single node 0.
 *  COMPLEXITY : Time O(max(m, n)) | Space O(max(m, n)) for the result list
 *
 * ----------------------------------------------------------------------------
 *  6.7  REMOVE DUPLICATES, KEEP NONE                (LeetCode 82)
 * ----------------------------------------------------------------------------
 *  PROBLEM  In a SORTED list, delete every value that appears more than once
 *           (remove all copies, not just the extras). Return the head.
 *  IDEA     Template A. The head itself may be part of a duplicate run, so the
 *           dummy is required. Skip whole runs through prev.
 *
 *  DRY RUN   list: 1 -> 2 -> 3 -> 3 -> 4 -> 4 -> 5
 *      start  : dummy -> 1 -> 2 -> 3a -> 3b -> 4a -> 4b -> 5     prev = dummy, cur = 1
 *      cur=1  : cur.next = 2, different  -> keep: prev = 1, cur = 2
 *      cur=2  : cur.next = 3, different  -> keep: prev = 2, cur = 3a
 *      cur=3a : cur.next = 3b, equal     -> duplicate run of 3
 *               skip while cur.data == 3: cur = 3a, 3b, then 4a (stop)
 *               prev.next <- cur   (2.next = 4a)       prev stays at 2
 *      cur=4a : cur.next = 4b, equal     -> skip the run: cur = 4a, 4b, then 5
 *               prev.next <- cur   (2.next = 5)        prev stays at 2
 *      cur=5  : cur.next = NULL          -> keep: prev = 5, cur = NULL
 *      result : 1 -> 2 -> 5 -> NULL
 *
 *  DRY RUN (duplicate at the head)   list: 1 -> 1 -> 2
 *      prev = dummy, cur = 1a: equal to next -> skip run: cur = 2
 *      prev.next <- 2   (dummy.next = 2)         result : 2 -> NULL
 *
 *  PSEUDOCODE
 *      REMOVE_DUPLICATES_ALL(head):
 *          dummy.next <- head
 *          prev <- dummy;  cur <- head
 *          while cur != NULL:
 *              if cur.next != NULL and cur.next.data == cur.data:
 *                  dupValue <- cur.data
 *                  while cur != NULL and cur.data == dupValue:
 *                      cur <- cur.next                 // skip the whole run
 *                  prev.next <- cur                    // bridge over the run
 *              else:
 *                  prev <- cur                         // unique node: keep it
 *                  cur  <- cur.next
 *          return dummy.next
 *
 *  EDGE CASES
 *    - Empty / single node  : returned unchanged.
 *    - All values equal     : every node is skipped; returns NULL.
 *    - Run at the head      : handled because prev starts on the dummy.
 *    - Run at the tail      : prev.next becomes NULL.
 *    - dummy.data           : never read. The code compares cur with cur.next
 *                             only, so a dummy value that equals a real value is
 *                             harmless. (A version comparing with prev.data would
 *                             read the dummy: avoid it, or pick an out-of-range
 *                             sentinel value.)
 *  COMPLEXITY : Time O(n) | Space O(1)
 *
 * ----------------------------------------------------------------------------
 *  6.8  SWAP NODES IN PAIRS                         (LeetCode 24)
 * ----------------------------------------------------------------------------
 *  PROBLEM  Swap every two adjacent nodes by relinking (not by swapping the
 *           values) and return the head.
 *  IDEA     Template A. The first pair changes the head, so the dummy is the
 *           predecessor of every pair, including the first. prev always names the
 *           node before the current pair.
 *
 *  DRY RUN   list: 1 -> 2 -> 3 -> 4
 *      start  : dummy -> 1 -> 2 -> 3 -> 4 -> NULL      prev = dummy
 *      pair 1 : a = 1, b = 2
 *               a.next <- b.next     1 -> 3
 *               b.next <- a          2 -> 1
 *               prev.next <- b       dummy -> 2
 *               prev <- a            prev = 1
 *               dummy -> 2 -> 1 -> 3 -> 4
 *      pair 2 : a = 3, b = 4
 *               a.next <- b.next     3 -> NULL
 *               b.next <- a          4 -> 3
 *               prev.next <- b       1 -> 4
 *               prev <- a            prev = 3
 *               dummy -> 2 -> 1 -> 4 -> 3
 *      prev.next = NULL -> stop.   return dummy.next   result : 2 -> 1 -> 4 -> 3 -> NULL
 *
 *  PSEUDOCODE
 *      SWAP_PAIRS(head):
 *          dummy.next <- head
 *          prev <- dummy
 *          while prev.next != NULL and prev.next.next != NULL:
 *              a <- prev.next
 *              b <- a.next
 *              a.next    <- b.next          // 1. a skips b
 *              b.next    <- a               // 2. b points back to a
 *              prev.next <- b               // 3. predecessor points to the new first
 *              prev      <- a               // 4. a is now the end of the swapped pair
 *          return dummy.next
 *
 *  ORDER MATTERS : step 1 must save b.next into a.next BEFORE step 2 overwrites
 *  b.next, or the rest of the list is lost.
 *
 *  EDGE CASES
 *    - Empty / single node  : the loop condition fails at once.
 *    - Odd length (1,2,3)   : result 2 -> 1 -> 3; the last node is left alone.
 *    - Two nodes            : one swap; the dummy makes the new head natural.
 *  COMPLEXITY : Time O(n) | Space O(1)
 *
 *
 * ============================================================================
 *  7. ADVANCED IDEAS
 * ============================================================================
 *
 *  7.1  PERMANENT SENTINEL INSIDE A LIST CLASS
 *    Instead of creating a dummy per function, a list class can keep a head
 *    sentinel (and often a tail sentinel) for its whole life:
 *        empty :  HEAD <-> TAIL
 *        full  :  HEAD <-> [a] <-> [b] <-> TAIL
 *    Every real node always has a real prev and next, so insert and unlink need no
 *    empty, first or last special cases. The implementation Sentinel Doubly Linked
 *    List in your problem-solving folder does exactly this. Many standard
 *    libraries use a sentinel in their list containers for the same reason.
 *
 *  7.2  TWO (OR MORE) DUMMIES
 *    When the output has several parts, give each part its own dummy and tail
 *    (partition, odd-even list, splitting by a rule). Join the parts at the end
 *    and CUT the final tail (Section 6.4).
 *
 *  7.3  DUMMY IN A DOUBLY LINKED LIST
 *    The same trick works, but the real head also has a prev pointer. When you
 *    return dummy.next as the head, clear its prev (it may point at the dummy):
 *        head <- dummy.next
 *        if head != NULL:  head.prev <- NULL
 *    Every relink must also fix the prev pointers (four updates per middle insert).
 *
 *  7.4  DUMMY AS THE ANCHOR OF A SEGMENT
 *    Reversing nodes between positions L and R, or in groups of k, needs "the node
 *    before the segment". With a dummy that node always exists, even when the
 *    segment starts at the first node (LeetCode 92 and 25).
 *
 *  7.5  DUMMY IN A CIRCULAR LIST
 *    A header node in a circular list makes the empty list a one-node ring that
 *    points to itself. Traversals stop when they return to the header, and insertion
 *    never has to special-case an empty list.
 *
 *  7.6  THE SENTINEL TRICK IN SEARCHING
 *    A sentinel can also remove a loop condition. To search for key in an array or
 *    list, append the key itself as a sentinel at the end. The scan then needs no
 *    "have I run past the end?" check; afterwards test whether the match was the
 *    sentinel. The same word, a different use of the idea: guarantee that the loop
 *    always stops.
 *
 *  7.7  MERGE K SORTED LISTS (LeetCode 23)
 *    Repeatedly pick the smallest head among k lists (with a min-heap) and append
 *    it to the tail of one result list started from a dummy. Same Template B, the
 *    only change is how the next node is chosen.
 *
 *
 * ============================================================================
 *  8. WHEN YOU DO NOT NEED A DUMMY NODE
 * ============================================================================
 *
 *    A dummy node only helps when the FIRST node can change. Skip it when:
 *
 *    - The head never changes: pure traversal, counting, searching, printing,
 *      finding the middle, detecting a cycle.
 *    - You only delete a node you hold a pointer to and never the first one.
 *    - Iterative REVERSAL of the whole list: the new head is the old tail, and the
 *      two-pointer reversal already handles the first node cleanly.
 *    - Remove Duplicates from a Sorted List (keep one copy, LeetCode 83): the first
 *      node always survives, so the head never changes.
 *
 *  TRADE-OFFS OF USING ONE
 *    + Less code, fewer branches, fewer places for head bugs.
 *    + The same logic works for empty, one-node and many-node lists.
 *    - One extra node (constant memory, negligible time).
 *    - A new way to go wrong: returning head instead of dummy.next, reading the
 *      dummy's data, or letting a pointer to the dummy escape (Section 10).
 *
 *
 * ============================================================================
 *  9. EDGE CASE CHECKLIST (dummy-node solutions)
 * ============================================================================
 *
 *    [ ] Empty list                       (dummy.next = NULL; should return NULL)
 *    [ ] Single node                      (kept, and removed)
 *    [ ] Two nodes                        (smallest case with a distinct head and tail)
 *    [ ] The head is affected             (deleted, replaced, swapped, a duplicate)
 *    [ ] Several consecutive heads are affected
 *    [ ] The last node is affected        (next becomes NULL)
 *    [ ] Every node matches / is removed  (result NULL)
 *    [ ] No node matches                  (list unchanged)
 *    [ ] Consecutive matches in the middle (prev must NOT advance after a delete)
 *    [ ] n equals the length              (remove Nth from end -> removes the head)
 *    [ ] One input list empty             (merge)
 *    [ ] Final carry                      (add two numbers)
 *    [ ] The split lists are cut at the end (partition: no cycle)
 *    [ ] Return value is dummy.next, not head
 *
 *
 * ============================================================================
 *  10. COMMON MISTAKES
 * ============================================================================
 *
 *   1. Returning head instead of dummy.next.
 *        Symptom : wrong or dangling result when the head changed or was deleted.
 *        Fix     : always return dummy.next.
 *
 *   2. Advancing prev after a deletion.
 *        Symptom : consecutive matches survive (10, 10 -> one 10 remains).
 *        Fix     : advance prev only when the next node is KEPT.
 *
 *   3. Forgetting to set dummy.next <- head.
 *        Symptom : the whole list is ignored; the result is empty.
 *        Fix     : make it the second line of every dummy solution.
 *
 *   4. Not cutting the tail after splitting or relinking.
 *        Symptom : a cycle; later traversal or printing never ends.
 *        Fix     : tail.next <- NULL when the last node moved (partition, merge of
 *                  rearranged nodes).
 *
 *   5. Returning or storing the ADDRESS of a stack dummy.
 *        Symptom : undefined behaviour after the function returns.
 *        Fix     : return dummy.next (a real heap node); never point a real node
 *                  at the dummy.
 *
 *   6. Heap-allocating the dummy and never deleting it.
 *        Symptom : a one-node memory leak per call.
 *        Fix     : prefer a stack dummy; otherwise delete it after saving
 *                  dummy.next.
 *
 *   7. Reading the dummy's data as if it were real.
 *        Symptom : a wrong comparison when a real value equals the placeholder.
 *        Fix     : compare only real nodes, or use an impossible sentinel value.
 *
 *   8. Dereferencing prev.next.next without checking prev.next.
 *        Symptom : crash on the last node.
 *        Fix     : test prev.next != NULL first (and prev.next.next for pairs).
 *
 *   9. Overwriting a pointer before saving it (swap pairs, partition).
 *        Symptom : the rest of the list is lost.
 *        Fix     : save the next pointer first, or order the assignments so the
 *                  old value is read before it is replaced.
 *
 *  10. Forgetting to attach the remainder in a merge.
 *        Symptom : nodes silently disappear.
 *        Fix     : tail.next <- whichever list is not yet empty.
 *
 *  11. Doubly lists: updating next but not prev, or leaving the head's prev
 *      pointing at the dummy.
 *        Fix     : fix both directions; clear head.prev when returning.
 *
 *
 * ============================================================================
 *  11. COMPLEXITY
 * ============================================================================
 *
 *   The dummy node adds O(1) extra space and does not change the time of any
 *   solution. It removes branches, not work.
 *
 *   Problem                       Time            Extra space
 *   ----------------------------  --------------  ----------------------------
 *   Remove elements               O(n)            O(1)
 *   Remove Nth from end           O(L), one pass  O(1)
 *   Merge two sorted lists        O(m + n)        O(1) (nodes are reused)
 *   Partition list                O(n)            O(1)
 *   Insert into a sorted list     O(n)            O(1)
 *   Add two numbers               O(max(m, n))    O(max(m, n)) result list
 *   Remove duplicates (keep none) O(n)            O(1)
 *   Swap nodes in pairs           O(n)            O(1)
 *   Merge k sorted lists (heap)   O(N log k)      O(k) for the heap
 *
 *
 * ============================================================================
 *  12. RECOGNISING THE PATTERN + PRACTICE ROADMAP
 * ============================================================================
 *
 *  DECISION GUIDE
 *      Could the first node be deleted, replaced, or moved?     -> use a dummy
 *      Am I building a NEW list one node at a time?             -> dummy + tail
 *      Am I splitting the list into two or more parts?          -> one dummy per part
 *      Do I need "the node before" a segment that may start
 *      at the head?                                             -> dummy as the anchor
 *      Am I only reading the list or reversing all of it?       -> probably no dummy
 *
 *  PRACTICE ROADMAP (easy to hard)
 *
 *   Step  Problem                                  LeetCode  Template
 *   ----  ---------------------------------------  --------  --------
 *   1     Remove Linked List Elements              203       A
 *   2     Merge Two Sorted Lists                   21        B
 *   3     Delete the Middle Node of a Linked List  2095      A (two pointers)
 *   4     Remove Nth Node From End of List         19        A (two pointers)
 *   5     Add Two Numbers                          2         B
 *   6     Partition List                           86        C
 *   7     Odd Even Linked List                     328       C
 *   8     Swap Nodes in Pairs                      24        A
 *   9     Remove Duplicates from Sorted List II    82        A
 *   10    Insertion Sort List                      147       A
 *   11    Sort List (merge step)                   148       B
 *   12    Reverse Linked List II                   92        D
 *   13    Reverse Nodes in k-Group                 25        D
 *   14    Merge k Sorted Lists                     23        B + heap
 *   15    Design Linked List (sentinel head)       707       permanent sentinel
 *
 *   Contrast problems that do NOT need one: Reverse Linked List (206), Remove
 *   Duplicates from Sorted List (83), Linked List Cycle (141).
 *
 *   Suggested order: deletion first, then merging, then partitioning, then the
 *   segment problems. Those patterns cover a large share of linked-list problems.
 *
 *
 * ============================================================================
 *  13. QUICK REVISION Q&A AND KEY TAKEAWAYS
 * ============================================================================
 *
 *  Q1  What is a dummy node?
 *      An extra node placed before the real head. It holds no real data and makes
 *      the head an ordinary node with a predecessor.
 *  Q2  Why return dummy.next and not head?
 *      The head may have been deleted or may no longer be first. dummy.next always
 *      names the current first real node.
 *  Q3  The input list is empty and you run: dummy.next <- head; return dummy.next.
 *      What is returned?
 *      NULL. dummy.next was assigned head, which is NULL. It is not the dummy's
 *      address and not a new node.
 *  Q4  Is it safe to return dummy.next when dummy is a local variable?
 *      Yes. It points to a real list node. Returning the dummy's own address would
 *      be a bug.
 *  Q5  Why does prev not advance after a deletion?
 *      The node that moved up may also need deleting. prev advances only on a keep.
 *  Q6  Why do partition-style solutions need tail.next <- NULL?
 *      The last moved node still points at its old successor, which now sits in the
 *      other list. Without the cut the lists form a cycle.
 *  Q7  Which pattern builds a new list from nothing?
 *      Template B: dummy + tail. The first node is dummy.next, no special case.
 *  Q8  Does a dummy node change the time complexity?
 *      No. It adds one node (O(1) space) and removes branches.
 *  Q9  When is a dummy node unnecessary?
 *      When the head cannot change: traversal, search, whole-list reversal, keeping
 *      one copy of sorted duplicates.
 *  Q10 Dummy node vs permanent sentinel?
 *      A dummy is temporary inside one function; a sentinel lives inside the list
 *      class and removes special cases from every operation.
 *
 *  KEY TAKEAWAYS
 *    - The head has no predecessor, so it needs special code. A dummy node gives it
 *      one: the head becomes an ordinary node.
 *    - Three rules: dummy.next <- head; work through pointers that start at the
 *      dummy; return dummy.next.
 *    - Four templates: modify in place, build with a tail, split into several lists,
 *      anchor a segment.
 *    - After a deletion keep prev in place; after a keep move it forward.
 *    - Split or rearranged lists need their last tail cut to avoid a cycle.
 *    - Stack dummy: nothing to free, but never return its address. Heap dummy:
 *      delete it.
 *    - Never read the dummy's data as real data.
 *    - It does not change complexity: O(1) extra space, simpler and safer code.
 *    - Skip it when the head cannot change.
 *
 *  Related files
 *      Foundations      : Linked_List_Fundamentals.cpp
 *      Permanent sentinel : 13_Linked_List_Problem_Solving/ (Sentinel Doubly Linked List)
 *      Related patterns : 03_Reversal_Patterns, 04_Fast_Slow_Pointer_Techniques,
 *                         05_Merge_And_Sort_Patterns
 */

// Notes-only file. Empty main() keeps the file buildable as a standalone target.
int main() {
    return 0;
}