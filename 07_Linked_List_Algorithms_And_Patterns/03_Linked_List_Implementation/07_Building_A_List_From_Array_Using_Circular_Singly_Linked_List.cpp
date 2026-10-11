/*
 * Author  : Sarvan Yaduvanshi
 * Created : 2026-10-10 10:50:28
 */

/*
 * ============================================================================
 *  PROBLEM : Create a Circular Singly Linked List from an Array   (GFG)
 * ============================================================================
 *
 *  PROBLEM STATEMENT
 *    Given an array of n integers, build a circular singly linked list in which
 *    node i stores arr[i], so the list order equals the array order. The last
 *    node's next pointer must point back to the HEAD instead of NULL, so the
 *    nodes form a ring. Return the head of the new list. Then:
 *
 *      1. buildCircularSLL(arr, n)  : create the list and return its head.
 *      2. printCircularSLL(head)    : print it once around the ring.
 *      3. deleteCircularSLL(head)   : free every node and reset head to NULL.
 *
 *    An empty array produces an empty list (head = NULL).
 *
 *  INPUT FORMAT                      OUTPUT FORMAT
 *      n                                 Array print : [a, b, c]
 *      arr[0] arr[1] ... arr[n-1]        Circular SLL print :
 *                                          a -> b -> c -> (back to a)
 *
 *  CONSTRAINTS
 *      0 <= n <= 10^5
 *      arr[i] is any int (duplicates and negatives are allowed)
 *
 * ----------------------------------------------------------------------------
 *  EXAMPLE 1
 * ----------------------------------------------------------------------------
 *  Input  : arr = [10, 20, 30, 40, 50]
 *  Output : 10 -> 20 -> 30 -> 40 -> 50 -> (back to 10)
 *
 *           +----------------- next ------------------+
 *           |                                         |
 *           v                                         |
 *  head -> [10] -> [20] -> [30] -> [40] -> [50] ------+
 *                                           tail
 *
 *  The last node (50) points back to the head (10); no node has a NULL next.
 *
 * ----------------------------------------------------------------------------
 *  EXAMPLE 2
 * ----------------------------------------------------------------------------
 *  Input  : arr = [1, 2, 3, 4]
 *  Output : 1 -> 2 -> 3 -> 4 -> (back to 1)
 *
 *           +----------- next ------------+
 *           |                             |
 *           v                             |
 *  head -> [1] -> [2] -> [3] -> [4] ------+
 *                               tail
 *
 * ----------------------------------------------------------------------------
 *  APPROACH : BUILD A NORMAL CHAIN, THEN CLOSE THE RING ONCE
 * ----------------------------------------------------------------------------
 *    1. If the array is empty, return NULL.
 *    2. Create a node for arr[0]. It is both the head (entry point) and the
 *       tail (last node built so far).
 *    3. For each remaining element, append a node after the tail and advance
 *       the tail:
 *           tail.next <- Node(arr[i])
 *           tail      <- tail.next
 *    4. Close the ring with ONE assignment:   tail.next <- head
 *    5. Return head.
 *
 *  WHY CLOSE THE RING AT THE END?
 *    While the loop runs, the list is an ordinary singly list, so the loop body
 *    is the familiar "append at tail" code with no wrap-around special cases.
 *    A single closing assignment afterwards also handles n = 1 correctly:
 *    head == tail, so  tail.next <- head  makes the lone node point to itself
 *    (a self-loop), exactly what a one-node circular list must be.
 *
 *  ALTERNATIVE : KEEP THE RING CLOSED AT EVERY STEP
 *    Make the first node a self-loop (head.next <- head), then for each new
 *    node set  tail.next <- newNode  and  newNode.next <- head  inside the loop.
 *    This is also correct and the list is a valid ring after every iteration,
 *    but it repeats the "point back to head" assignment n times, and a cleanup
 *    after a failed allocation must then deal with a closed ring.
 *
 *  WHY RETURN head?
 *    The problem asks for the head. (A circular list is often stored by its
 *    TAIL instead: head = tail.next gives the front in O(1) and tail gives the
 *    back in O(1). Here a local tail is used only while building.)
 *
 *  ALGORITHM (pseudocode)
 *
 *      BUILD_CIRCULAR_SLL(arr, n):
 *          if n <= 0:  return NULL
 *          head <- Node(arr[0])
 *          tail <- head
 *          for i from 1 to n - 1:
 *              tail.next <- Node(arr[i])         // link the new node
 *              tail      <- tail.next            // advance the tail
 *          tail.next <- head                     // close the ring (one time)
 *          return head
 *
 *      PRINT_CIRCULAR_SLL(head):
 *          if head == NULL:  print "List is empty"; return
 *          cur <- head
 *          do:
 *              print cur.data, " -> "
 *              cur <- cur.next
 *          while cur != head                     // one full turn
 *          print "(back to ", head.data, ")"
 *
 *      DELETE_CIRCULAR_SLL(head):                // head is a REFERENCE
 *          if head == NULL:  return 0
 *          cur   <- head.next
 *          count <- 0
 *          while cur != head:                    // head is the stop marker
 *              nextNode <- cur.next              // SAVE before deleting
 *              delete cur
 *              cur <- nextNode
 *              count <- count + 1
 *          delete head                           // head goes LAST
 *          head  <- NULL
 *          return count + 1
 *
 * ----------------------------------------------------------------------------
 *  DRY RUN : arr = [1, 2, 3, 4]
 * ----------------------------------------------------------------------------
 *
 *  Step 1 : head = tail = new Node(1)           (ring not closed yet)
 *      head --> [1 | NULL]
 *                  ^ tail
 *
 *  Step 2 : tail.next = new Node(2);  tail = tail.next
 *      head --> [1 | o]--> [2 | NULL]
 *                              ^ tail
 *
 *  Step 3 : tail.next = new Node(3);  tail = tail.next
 *      head --> [1 | o]--> [2 | o]--> [3 | NULL]
 *                                          ^ tail
 *
 *  Step 4 : tail.next = new Node(4);  tail = tail.next
 *      head --> [1 | o]--> [2 | o]--> [3 | o]--> [4 | NULL]
 *                                                    ^ tail
 *
 *  Step 5 : close the ring:  tail.next = head
 *           +---------------------------------------+
 *           |                                       |
 *           v                                       |
 *  head -> [1] -> [2] -> [3] -> [4] ----------------+
 *
 *  Return head.  Print walks 1 -> 2 -> 3 -> 4 and stops when it is back at 1.
 *
 *  DELETE trace (same list)
 *      cur = head.next = [2]
 *      cur=[2] : save [3], delete [2], cur=[3]
 *      cur=[3] : save [4], delete [3], cur=[4]
 *      cur=[4] : save [1], delete [4], cur=[1]  -> cur == head, loop ends
 *      delete [1] (the head, last), head = NULL, 4 nodes freed
 *
 * ----------------------------------------------------------------------------
 *  EDGE CASES HANDLED
 * ----------------------------------------------------------------------------
 *    - Empty array (n = 0)  : buildList returns NULL; print reports an empty
 *                             list; delete returns 0 and does nothing.
 *    - One element (n = 1)  : the loop never runs; tail.next <- head makes the
 *                             node point to itself:   head -> [7] -+
 *                                                           ^      |
 *                                                           +------+
 *    - Two elements         : head.next = tail and tail.next = head.
 *    - Duplicates/negatives : only values are stored; nothing assumes order or
 *                             uniqueness.
 *    - Invalid size         : n < 0 or n > MAX_SIZE would break the fixed-size
 *                             input array, so it is rejected before reading.
 *    - Invalid element      : a non-integer token is reported, not stored.
 *    - Allocation failure   : if "new" throws midway, the partly built chain is
 *                             freed and the exception is rethrown (no leak).
 *                             The ring is not closed yet at that point, so a
 *                             plain walk to NULL is enough.
 *    - Printing             : uses do-while. A plain "while (cur != head)" runs
 *                             ZERO times because cur starts equal to head. A
 *                             "while (cur != NULL)" never stops, since no node
 *                             has a NULL next.
 *    - Deleting             : (1) head is the stop marker, so it is deleted
 *                             LAST; deleting it first would leave the loop
 *                             comparing against a freed pointer.
 *                             (2) next is saved before each delete (no
 *                             use-after-free).
 *                             (3) head is passed by REFERENCE and set to NULL,
 *                             so the caller's pointer cannot dangle.
 *                             (4) a single node is handled: head.next == head
 *                             so the loop is skipped and only head is deleted.
 *
 *  COMPLEXITY
 *      Operation           Time    Auxiliary space
 *      ------------------  ------  ---------------------------------------------
 *      buildCircularSLL    O(n)    O(1)  (the n nodes are the output itself)
 *      printCircularSLL    O(n)    O(1)
 *      deleteCircularSLL   O(n)    O(1)
 *
 *  COMMON MISTAKES
 *    - Forgetting tail.next <- head             -> the list is linear; the
 *      do-while print then dereferences NULL and crashes.
 *    - A single node whose next is NULL         -> must point to itself.
 *    - Printing with while (cur != head)        -> prints nothing.
 *    - Printing with while (cur != NULL)        -> infinite loop.
 *    - Deleting head before the other nodes     -> the loop can no longer tell
 *      when it is back at the start.
 *    - Passing head by value to delete          -> caller keeps a dangling
 *      pointer to freed memory.
 *    - Forgetting "tail = tail.next"            -> every node is attached to
 *      the same tail, so only the last value survives in the ring.
 */

#include <cstddef>
#include <iostream>

using namespace std;

// A node of the circular singly linked list.
struct Node {
    int   data;
    Node* next;

    // "explicit" blocks accidental int -> Node conversions. next starts as
    // nullptr; buildCircularSLL points the last node back to the head.
    explicit Node(int val) : data(val), next(nullptr) {}
};

// Builds a circular singly linked list holding arr[0..n-1] in order and returns
// its head (nullptr when n <= 0). If an allocation fails midway, the nodes
// created so far are freed and the exception is rethrown, so nothing leaks.
// Time: O(n) | Space: O(1) auxiliary (the n nodes are the result)
static Node* buildCircularSLL(const int arr[], const int n) {
    // Edge case: nothing to build.
    if (n <= 0) {
        return nullptr;
    }

    // The first node is both the head (entry point) and the tail (last node).
    Node* head = new Node(arr[0]);
    Node* tail = head;

    try {
        // Append each remaining element after the tail in O(1).
        for (int i = 1; i < n; i++) {
            tail->next = new Node(arr[i]);  // 1. link the new node
            tail = tail->next;              // 2. advance the tail
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

    // Close the ring once. For n == 1 (head == tail) this makes a self-loop.
    tail->next = head;
    return head;
}

// Prints the ring once as "a -> b -> c -> (back to a)".
// Time: O(n) | Space: O(1)
static void printCircularSLL(const Node* head) {
    if (head == nullptr) {
        cout << "List is empty (head = NULL).\n";
        return;
    }

    const Node* cur = head;
    do {
        cout << cur->data << " -> ";
        cur = cur->next;
    } while (cur != head);  // do-while: cur starts equal to head

    cout << "(back to " << head->data << ")\n";
}

// Frees every node, sets the caller's head to nullptr, and returns the number
// of nodes deleted. Head is the stop marker, so it is deleted last.
// Safe to call on an empty list.
// Time: O(n) | Space: O(1)
static size_t deleteCircularSLL(Node*& head) {
    if (head == nullptr) {
        return 0;
    }

    size_t count = 0;
    Node* cur = head->next;
    while (cur != head) {
        Node* nextNode = cur->next;  // Save the next node BEFORE deleting.
        delete cur;
        cur = nextNode;
        count++;
    }

    delete head;     // The stop marker goes last.
    head = nullptr;  // The caller's pointer must not dangle.
    return count + 1;
}

constexpr int MAX_SIZE = 100000;  // Maximum number of array elements (10^5).
static int arr[MAX_SIZE];         // Input values (static: zero-initialised, off the stack).

static void solve() {
    int n = 0;
    if (!(cin >> n) || n < 0 || n > MAX_SIZE) {
        cout << "Invalid array size.\n";
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!(cin >> arr[i])) {
            cout << "Invalid array element.\n";
            return;
        }
    }

    cout << "Array print        : [";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << (i == n - 1 ? "" : ", ");
    }
    cout << "]\n";

    Node* head = buildCircularSLL(arr, n);

    cout << "Circular SLL print : ";
    printCircularSLL(head);

    const size_t freed = deleteCircularSLL(head);
    cout << "Deleted " << freed << " node(s). head = "
         << (head == nullptr ? "NULL" : "NOT NULL") << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}