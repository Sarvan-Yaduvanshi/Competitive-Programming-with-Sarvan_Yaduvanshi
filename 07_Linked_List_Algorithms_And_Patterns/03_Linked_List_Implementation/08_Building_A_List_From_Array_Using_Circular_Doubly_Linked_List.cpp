/*
 * Author  : Sarvan Yaduvanshi
 * Created : 2026-10-10 17:23:03
 */

/*
 * ============================================================================
 *  PROBLEM : Circular Doubly Linked List from an Array
 * ============================================================================
 *
 *  PROBLEM STATEMENT
 *    Given an array of n integers, build a circular doubly linked list (CDLL)
 *    whose nodes hold the array elements in the same order. Then:
 *
 *      1. buildCircularDLL(arr)  : create the list and return its head.
 *      2. printForward(head)     : print the list from the head to the last node.
 *      3. printBackward(head)    : print the list from the last node to the head.
 *      4. deleteCircularDLL(head): free every node and reset head to NULL.
 *
 *    In the resulting list:
 *      - node i stores arr[i], and the list order equals the array order;
 *      - every node's next points to the following node and prev points to the
 *        preceding node;
 *      - the last node's next points to the HEAD, and the head's prev points to
 *        the LAST node, so the list forms a ring in both directions;
 *      - an empty array produces an empty list (head = NULL).
 *
 *  INPUT FORMAT (for this program)
 *      n
 *      arr[0] arr[1] ... arr[n-1]
 *
 *  OUTPUT FORMAT
 *      Forward  : the list read from head to last, then "(back to [head])"
 *      Backward : the list read from last to head, then "(back to [last])"
 *      A line confirming how many nodes were deleted.
 *
 *  CONSTRAINTS
 *      0 <= n <= 10^5
 *      -10^9 <= arr[i] <= 10^9      (duplicates and negatives are allowed)
 *
 * ----------------------------------------------------------------------------
 *  EXAMPLE 1
 * ----------------------------------------------------------------------------
 *  Input  : arr = [1, 2, 3, 4]
 *  Output :
 *      Forward  : [1] <-> [2] <-> [3] <-> [4] <-> (back to [1])
 *      Backward : [4] <-> [3] <-> [2] <-> [1] <-> (back to [4])
 *
 *  Figure (next pointers go right and wrap from 4 to 1; prev pointers go left
 *  and wrap from 1 to 4):
 *
 *             +----------------- next ------------------+
 *             |                                         |
 *             v                                         |
 *           +---+     +---+     +---+     +---+         |
 *  head ->  | 1 | <-> | 2 | <-> | 3 | <-> | 4 |---------+
 *           +---+     +---+     +---+     +---+
 *             |                             ^
 *             +----------- prev ------------+
 *                                         tail
 *
 *  Pointer table:
 *      node   prev   next
 *      [1]    [4]    [2]       <- head.prev is the last node
 *      [2]    [1]    [3]
 *      [3]    [2]    [4]
 *      [4]    [3]    [1]       <- last.next is the head
 *
 * ----------------------------------------------------------------------------
 *  EXAMPLE 2  (single element)
 * ----------------------------------------------------------------------------
 *  Input  : arr = [7]
 *  Output :
 *      Forward  : [7] <-> (back to [7])
 *      Backward : [7] <-> (back to [7])
 *
 *  Figure (the only node is its own neighbour in both directions):
 *
 *                +--- next ---+
 *                |            |
 *                v            |
 *      head -> +---+          |
 *              | 7 |----------+
 *              +---+
 *                ^ |
 *                | |
 *                +-+ prev
 *
 *      head.next == head   and   head.prev == head
 *
 * ----------------------------------------------------------------------------
 *  APPROACH
 * ----------------------------------------------------------------------------
 *    Build the nodes as an ordinary doubly linked chain (head ... tail) while
 *    walking the array once, then CLOSE THE RING a single time at the end:
 *
 *        tail.next <- head
 *        head.prev <- tail
 *
 *    Keeping the ring open during the loop means the loop body is exactly the
 *    usual "append to a doubly list" code, with no wrap-around special cases.
 *    Closing it once afterwards also works for n = 1 (head == tail gives the
 *    two self-loops).
 *
 *  ALGORITHM (pseudocode)
 *
 *      BUILD_CIRCULAR_DLL(arr):
 *          if arr is empty:  return NULL
 *          head <- NULL
 *          tail <- NULL
 *          for each value in arr:
 *              node <- Node(value)               // prev = NULL, next = NULL
 *              if head == NULL:
 *                  head <- node
 *                  tail <- node
 *              else:
 *                  tail.next <- node             // 1. old tail points forward
 *                  node.prev <- tail             // 2. new node points back
 *                  tail      <- node             // 3. move tail
 *          tail.next <- head                     // close the ring (forward)
 *          head.prev <- tail                     // close the ring (backward)
 *          return head
 *
 *      PRINT_FORWARD(head):
 *          if head == NULL:  print "List is empty"; return
 *          cur <- head
 *          do:
 *              print "[", cur.data, "] <-> "
 *              cur <- cur.next
 *          while cur != head                     // do-while, see edge cases
 *          print "(back to [", head.data, "])"
 *
 *      PRINT_BACKWARD(head):
 *          if head == NULL:  print "List is empty"; return
 *          tail <- head.prev                     // the last node
 *          cur  <- tail
 *          do:
 *              print "[", cur.data, "] <-> "
 *              cur <- cur.prev
 *          while cur != tail
 *          print "(back to [", tail.data, "])"
 *
 *      DELETE_CIRCULAR_DLL(head):
 *          if head == NULL:  return 0
 *          tail <- head.prev
 *          tail.next <- NULL                     // break the ring: now linear
 *          count <- 0
 *          while head != NULL:
 *              nextNode <- head.next             // SAVE before delete
 *              delete head
 *              head <- nextNode
 *              count <- count + 1
 *          return count                          // head is now NULL
 *
 *  BUILD TRACE for arr = [1, 2, 3, 4]
 *
 *      step  value  head  tail  chain (ring still open)
 *      ----  -----  ----  ----  ---------------------------------
 *      1     1      1     1     [1]
 *      2     2      1     2     [1] <-> [2]
 *      3     3      1     3     [1] <-> [2] <-> [3]
 *      4     4      1     4     [1] <-> [2] <-> [3] <-> [4]
 *      close tail.next = [1], head.prev = [4]  ->  ring complete
 *
 *  DELETE TRACE for the same list
 *      tail = head.prev = [4];  tail.next = NULL      (ring becomes a chain)
 *      delete [1], delete [2], delete [3], delete [4]  (next saved each time)
 *      head = NULL, count = 4
 *
 * ----------------------------------------------------------------------------
 *  EDGE CASES HANDLED
 * ----------------------------------------------------------------------------
 *    - Empty array (n = 0)  : build returns NULL; both prints report an empty
 *                             list; delete returns 0 and does nothing.
 *    - One element (n = 1)  : head == tail, so closing the ring creates the two
 *                             self-loops (next and prev both point to the node).
 *    - Two elements         : head.next = tail, head.prev = tail,
 *                             tail.next = head, tail.prev = head.
 *    - Duplicates/negatives : only values are stored; nothing assumes uniqueness.
 *    - Printing             : uses do-while. A plain "while (cur != head)" would
 *                             run zero times because cur starts equal to head.
 *                             A "while (cur != NULL)" would never stop.
 *    - Deleting             : (1) the ring is broken first, otherwise the loop
 *                             walks forever and frees nodes twice;
 *                             (2) the next node is saved before each delete
 *                             (no use-after-free);
 *                             (3) head is reset to NULL (no dangling pointer);
 *                             (4) calling delete on an empty list is safe.
 *    - Allocation failure   : if "new" throws midway, the partly built chain is
 *                             freed and the exception is rethrown, so nothing
 *                             leaks. The ring is not closed yet at that point,
 *                             so a plain walk to NULL is enough.
 *    - Invalid input        : a bad n or a non-integer element is reported
 *                             instead of building a half-filled list.
 *
 *  COMPLEXITY
 *      Operation            Time    Auxiliary space
 *      -------------------  ------  ---------------
 *      buildCircularDLL     O(n)    O(1)   (the n nodes are the output itself)
 *      printForward         O(n)    O(1)
 *      printBackward        O(n)    O(1)
 *      deleteCircularDLL    O(n)    O(1)
 *
 *  VERIFYING THE LINKS
 *      If printForward and printBackward show mirrored output, every next and
 *      prev pointer is consistent (A.next == B implies B.prev == A) and the ring
 *      is closed in both directions.
 */

#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

// A node of the circular doubly linked list.
struct Node {
    int   data;
    Node* prev;
    Node* next;
    explicit Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

// Builds a circular doubly linked list holding arr in order and returns the
// head (nullptr for an empty array). On allocation failure it frees whatever
// it built and rethrows, so nothing leaks.
// Time: O(n) | Space: O(1) auxiliary (the n nodes are the result)
static Node* buildCircularDLL(const vector<int>& arr) {
    if (arr.empty()) {
        return nullptr;
    }

    Node* head = nullptr;
    Node* tail = nullptr;

    try {
        for (const int value : arr) {
            Node* node = new Node(value);
            if (head == nullptr) {
                head = tail = node;
            } else {
                tail->next = node;  // 1. old tail points forward to the new node
                node->prev = tail;  // 2. new node points back to the old tail
                tail = node;        // 3. move tail
            }
        }
    } catch (...) {
        // The ring is still open (tail->next == nullptr), so this walk ends.
        while (head != nullptr) {
            Node* nextNode = head->next;
            delete head;
            head = nextNode;
        }
        throw;
    }

    // Close the ring in both directions. For n == 1 this makes two self-loops.
    tail->next = head;
    head->prev = tail;
    return head;
}

// Prints the list front to back: "[a] <-> [b] <-> (back to [a])".
// Time: O(n) | Space: O(1)
static void printForward(const Node* head) {
    if (head == nullptr) {
        cout << "List is empty (head = NULL).\n";
        return;
    }

    const Node* cur = head;
    do {
        cout << "[" << cur->data << "] <-> ";
        cur = cur->next;
    } while (cur != head);  // do-while: cur starts equal to head

    cout << "(back to [" << head->data << "])\n";
}

// Prints the list back to front: "[c] <-> [b] <-> (back to [c])".
// Time: O(n) | Space: O(1)
static void printBackward(const Node* head) {
    if (head == nullptr) {
        cout << "List is empty (head = NULL).\n";
        return;
    }

    const Node* tail = head->prev;  // The last node.
    const Node* cur  = tail;
    do {
        cout << "[" << cur->data << "] <-> ";
        cur = cur->prev;
    } while (cur != tail);

    cout << "(back to [" << tail->data << "])\n";
}

// Frees every node, sets head to nullptr, and returns the number of nodes
// deleted. Safe to call on an empty list.
// Time: O(n) | Space: O(1)
static size_t deleteCircularDLL(Node*& head) {
    if (head == nullptr) {
        return 0;
    }

    Node* tail = head->prev;
    tail->next = nullptr;  // Break the ring so the walk below has an end.

    size_t count = 0;
    while (head != nullptr) {
        Node* nextNode = head->next;  // Save before deleting.
        delete head;
        head = nextNode;
        count++;
    }
    return count;  // head is now nullptr
}

static void solve() {
    int n = 0;
    if (!(cin >> n) || n < 0) {
        cout << "Invalid array size.\n";
        return;
    }

    vector<int> arr(static_cast<size_t>(n));
    for (int& x : arr) {
        if (!(cin >> x)) {
            cout << "Invalid array element.\n";
            return;
        }
    }

    Node* head = buildCircularDLL(arr);

    cout << "Forward  : ";
    printForward(head);
    cout << "Backward : ";
    printBackward(head);

    const size_t freed = deleteCircularDLL(head);
    cout << "Deleted " << freed << " node(s). head = "
         << (head == nullptr ? "NULL" : "NOT NULL") << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}