/*
 * Author  : Sarvan Yaduvanshi
 * Created : 2026-10-10 10:40:28
 */

/*
 * ============================================================================
 *  PROBLEM : Build a Doubly Linked List from an Array
 * ============================================================================
 *
 *  PROBLEM STATEMENT
 *    Given an array of n integers, build a doubly linked list (DLL) in which
 *    node i stores arr[i], so the list order equals the array order. Every
 *    node must be linked in BOTH directions:
 *
 *        next : points to the following node (NULL for the last node)
 *        prev : points to the preceding node (NULL for the first node)
 *
 *    Return the head of the list. Then:
 *
 *      1. buildList(arr, n)     : create the list and return its head.
 *      2. printForward(head)    : print it from head to tail.
 *      3. printBackward(head)   : print it from tail to head.
 *      4. deleteList(head)      : free every node and reset head to NULL.
 *
 *    An empty array produces an empty list (head = NULL).
 *
 *  INPUT FORMAT                      OUTPUT FORMAT
 *      n                                 Array print    : [a, b, c]
 *      arr[0] arr[1] ... arr[n-1]        Forward print  : a <-> b <-> c <-> NULL
 *                                        Backward print : c <-> b <-> a <-> NULL
 *
 *  CONSTRAINTS
 *      0 <= n <= 10^5
 *      arr[i] is any int (duplicates and negatives are allowed)
 *
 * ----------------------------------------------------------------------------
 *  EXAMPLE 1
 * ----------------------------------------------------------------------------
 *  Input  : arr = [1, 2, 3, 4]
 *  Output : 1 <-> 2 <-> 3 <-> 4 <-> NULL
 *
 *      head                                  tail
 *       |                                     |
 *       v                                     v
 *  NULL <- [1] <-> [2] <-> [3] <-> [4] -> NULL
 *           ^                                ^
 *      prev is NULL                     next is NULL
 *
 *      node   prev    next
 *      [1]    NULL    [2]      <- head: nothing before it
 *      [2]    [1]     [3]
 *      [3]    [2]     [4]
 *      [4]    [3]     NULL     <- tail: nothing after it
 *
 * ----------------------------------------------------------------------------
 *  EXAMPLE 2  (single element)
 * ----------------------------------------------------------------------------
 *  Input  : arr = [10]
 *  Output : 10 <-> NULL
 *
 *           head = tail
 *               |
 *               v
 *      NULL <- [10] -> NULL      prev and next are both NULL;
 *                                head and tail are the SAME node
 *
 * ----------------------------------------------------------------------------
 *  APPROACH : HEAD + TAIL APPEND, WIRING BOTH POINTERS
 * ----------------------------------------------------------------------------
 *    1. If the array is empty, return NULL.
 *    2. Create a node for arr[0]. It is both the head (entry point) and the
 *       tail (last node built so far). Its prev and next stay NULL.
 *    3. For each remaining element, create a node and connect it to the tail
 *       with TWO assignments, then advance the tail:
 *           tail.next    <- newNode        // forward link:  old tail -> new
 *           newNode.prev <- tail           // backward link: new -> old tail
 *           tail         <- newNode        // the new node is the last one now
 *    4. Return head.
 *
 *  WHAT IS DIFFERENT FROM THE SINGLY LIST?
 *    A singly list needs one assignment per append (tail.next). A doubly list
 *    needs two, because every connection exists twice: A.next == B must always
 *    come with B.prev == A. Forgetting the second link produces a list that
 *    prints correctly forwards but is broken backwards, which is why this file
 *    also prints backwards as a check.
 *
 *  WHY KEEP A tail POINTER?
 *    Appending needs the last node. Without tail you would walk from head to
 *    the end for every element: 1 + 2 + ... + n steps = O(n^2). With tail each
 *    append is O(1), so the whole build is O(n).
 *
 *  ALTERNATIVE APPROACHES (same O(n) time)
 *    - Dummy head : start with a throw-away node D, append everything after it
 *                   with the same logic, return D.next. CAUTION: in a doubly
 *                   list you must also set  D.next.prev <- NULL  before
 *                   deleting D, otherwise the real head keeps a prev pointer
 *                   to freed memory.
 *    - Insert at head from the back : loop i = n-1 down to 0; each new node
 *                   gets  node.next <- head,  head.prev <- node (if head
 *                   exists),  head <- node. No tail pointer needed.
 *
 *  ALGORITHM (pseudocode)
 *
 *      BUILD_LIST(arr, n):
 *          if n <= 0:  return NULL
 *          head <- Node(arr[0])                 // prev = NULL, next = NULL
 *          tail <- head
 *          for i from 1 to n - 1:
 *              newNode <- Node(arr[i])
 *              tail.next    <- newNode           // 1. forward link
 *              newNode.prev <- tail              // 2. backward link
 *              tail         <- newNode           // 3. advance tail
 *          return head
 *
 *      PRINT_FORWARD(head):
 *          cur <- head                           // copy, head is not moved
 *          while cur != NULL:
 *              print cur.data, " <-> "
 *              cur <- cur.next
 *          print "NULL"
 *
 *      PRINT_BACKWARD(head):
 *          if head == NULL:  print "NULL"; return
 *          tail <- head
 *          while tail.next != NULL:  tail <- tail.next    // walk to the last node
 *          cur <- tail
 *          while cur != NULL:
 *              print cur.data, " <-> "
 *              cur <- cur.prev                   // uses the prev links
 *          print "NULL"
 *
 *      DELETE_LIST(head):                        // head is a REFERENCE
 *          while head != NULL:
 *              nextNode <- head.next             // SAVE before deleting
 *              delete head
 *              head <- nextNode
 *          // head is now NULL, and so is the caller's pointer
 *
 * ----------------------------------------------------------------------------
 *  DRY RUN : arr = [1, 2, 3, 4]
 * ----------------------------------------------------------------------------
 *
 *  Step 1 : head = tail = new Node(1)
 *      NULL <- [1] -> NULL
 *              head,tail
 *
 *  Step 2 : newNode = Node(2); tail.next = newNode; newNode.prev = tail; tail = newNode
 *      NULL <- [1] <-> [2] -> NULL
 *              head     tail
 *
 *  Step 3 : newNode = Node(3); same three assignments
 *      NULL <- [1] <-> [2] <-> [3] -> NULL
 *              head             tail
 *
 *  Step 4 : newNode = Node(4); same three assignments
 *      NULL <- [1] <-> [2] <-> [3] <-> [4] -> NULL
 *              head                     tail
 *
 *  Return head.
 *  Forward  walk : 1 -> 2 -> 3 -> 4 -> NULL
 *  Backward walk : 4 -> 3 -> 2 -> 1 -> NULL   (proves every prev link is right)
 *
 *  DELETE trace (same list)
 *      head=[1] : save [2], delete [1], head=[2]
 *      head=[2] : save [3], delete [2], head=[3]
 *      head=[3] : save [4], delete [3], head=[4]
 *      head=[4] : save NULL, delete [4], head=NULL  -> loop ends
 *
 * ----------------------------------------------------------------------------
 *  EDGE CASES HANDLED
 * ----------------------------------------------------------------------------
 *    - Empty array (n = 0)  : buildList returns NULL; both prints show "NULL";
 *                             deleteList does nothing.
 *    - One element (n = 1)  : the loop body never runs; head == tail and both
 *                             prev and next are NULL.
 *    - Duplicates/negatives : only values are stored; nothing assumes order or
 *                             uniqueness.
 *    - head.prev and tail.next : stay NULL because the Node constructor sets
 *                             them and nothing overwrites them. This is what
 *                             marks the two ends of a LINEAR doubly list.
 *    - Invalid size         : n < 0 or n > MAX_SIZE would break the fixed-size
 *                             input array, so it is rejected before reading.
 *    - Invalid element      : a non-integer token is reported, not stored.
 *    - Allocation failure   : if "new" throws midway, the partly built list is
 *                             freed and the exception is rethrown (no leak).
 *    - Printing             : walks a copy of head, so the caller's head is not
 *                             moved; an empty list prints "NULL".
 *    - Deleting             : (1) next is saved before each delete (no
 *                             use-after-free); (2) head is passed by REFERENCE
 *                             so the caller's pointer also becomes NULL and
 *                             cannot dangle; (3) it is safe on an empty list.
 *
 *  COMPLEXITY
 *      Operation       Time    Auxiliary space
 *      --------------  ------  ---------------------------------------------
 *      buildList       O(n)    O(1)  (the n nodes are the output itself)
 *      printForward    O(n)    O(1)
 *      printBackward   O(n)    O(1)  (walks to the tail first, then back)
 *      deleteList      O(n)    O(1)
 *
 *  COMMON MISTAKES
 *    - Setting only tail.next and forgetting newNode.prev -> backward walk is
 *      broken (prev stays NULL).
 *    - Forgetting "tail = newNode"                         -> every node is
 *      attached to the same tail, so only the last value survives.
 *    - Walking from head on every append                   -> O(n^2).
 *    - Returning tail instead of head                      -> list is lost.
 *    - delete temp; then reading temp->next                -> use-after-free.
 *    - Passing head by value to deleteList                 -> caller keeps a
 *      dangling pointer to freed memory.
 *    - Dummy-head method without clearing head.prev        -> prev points to a
 *      deleted node.
 */

#include <cstddef>
#include <iostream>

using namespace std;

// A node of the doubly linked list.
struct Node {
    int   data;
    Node* prev;
    Node* next;

    // "explicit" blocks accidental int -> Node conversions. prev and next start
    // as nullptr, so the first node's prev and the last node's next are
    // automatically NULL.
    explicit Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

static void deleteList(Node*& head);  // Defined below; used for error cleanup.

// Builds a doubly linked list holding arr[0..n-1] in order and returns its head
// (nullptr when n <= 0). If an allocation fails midway, the nodes created so
// far are freed and the exception is rethrown, so nothing leaks.
// Time: O(n) | Space: O(1) auxiliary (the n nodes are the result)
static Node* buildList(const int arr[], const int n) {
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
            Node* newNode = new Node(arr[i]);
            tail->next    = newNode;  // 1. forward link:  old tail -> new node
            newNode->prev = tail;     // 2. backward link: new node -> old tail
            tail          = newNode;  // 3. advance the tail
        }
    } catch (...) {
        // If "new" threw, no half-linked node exists: the chain is still valid.
        deleteList(head);
        throw;
    }

    // Callers need the head: it is the only way to reach the list.
    return head;
}

// Prints the list front to back as "a <-> b <-> NULL" ("NULL" for an empty list).
// Time: O(n) | Space: O(1)
static void printForward(const Node* head) {
    // Traverse with a copy so the caller's head is never moved.
    const Node* cur = head;
    while (cur != nullptr) {
        cout << cur->data << " <-> ";
        cur = cur->next;
    }
    cout << "NULL\n";
}

// Prints the list back to front as "b <-> a <-> NULL". It first walks to the
// tail (head is the only entry point), then follows the prev links. Matching
// the mirror image of printForward proves every prev pointer is correct.
// Time: O(n) | Space: O(1)
static void printBackward(const Node* head) {
    if (head == nullptr) {
        cout << "NULL\n";
        return;
    }

    // Walk to the last node.
    const Node* tail = head;
    while (tail->next != nullptr) {
        tail = tail->next;
    }

    // Walk back using prev links.
    const Node* cur = tail;
    while (cur != nullptr) {
        cout << cur->data << " <-> ";
        cur = cur->prev;
    }
    cout << "NULL\n";
}

// Frees every node and sets the caller's head to nullptr. Head is taken by
// reference so the caller's pointer cannot dangle after the call.
// Safe to call on an empty list.
// Time: O(n) | Space: O(1)
static void deleteList(Node*& head) {
    while (head != nullptr) {
        Node* nextNode = head->next;  // Save the next node BEFORE deleting.
        delete head;                  // Free the current node.
        head = nextNode;              // Move on; ends as nullptr.
    }
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

    cout << "Array print    : [";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << (i == n - 1 ? "" : ", ");
    }
    cout << "]\n";

    Node* head = buildList(arr, n);

    cout << "Forward print  : ";
    printForward(head);
    cout << "Backward print : ";
    printBackward(head);

    // Release the nodes; head becomes nullptr.
    deleteList(head);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}