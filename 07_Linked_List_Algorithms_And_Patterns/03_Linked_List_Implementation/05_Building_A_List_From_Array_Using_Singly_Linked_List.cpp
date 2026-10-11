/*
 * Author  : Sarvan Yaduvanshi
 * Created : 2026-09-23 23:38:00
 */

/*
 * ============================================================================
 *  PROBLEM : Build a Singly Linked List from an Array
 * ============================================================================
 *
 *  PROBLEM STATEMENT
 *    Given an array of n integers, build a singly linked list in which node i
 *    stores arr[i], so the list order equals the array order. Then:
 *
 *      1. buildList(arr, n)  : create the list and return its head.
 *      2. printList(head)    : print it in the form  a->b->c->NULL.
 *      3. deleteList(head)   : free every node and reset head to NULL.
 *
 *    An empty array produces an empty list (head = NULL).
 *
 *  INPUT FORMAT                      OUTPUT FORMAT
 *      n                                 Array print       : [a, b, c]
 *      arr[0] arr[1] ... arr[n-1]        Linked List print : a->b->c->NULL
 *
 *  CONSTRAINTS
 *      0 <= n <= 10^5
 *      arr[i] is any int (duplicates and negatives are allowed)
 *
 * ----------------------------------------------------------------------------
 *  EXAMPLE 1
 * ----------------------------------------------------------------------------
 *  Input  : arr = [5, 10, 15, 20]
 *  Output : 5->10->15->20->NULL
 *
 *      head
 *       |
 *       v
 *     +----+---+     +----+---+     +----+---+     +----+------+
 *     |  5 | o-+---->| 10 | o-+---->| 15 | o-+---->| 20 | NULL |
 *     +----+---+     +----+---+     +----+---+     +----+------+
 *                                                      ^
 *                                                     tail
 *     (each node = [ data | next pointer ], o--> means "points to")
 *
 * ----------------------------------------------------------------------------
 *  EXAMPLE 2  (single element)
 * ----------------------------------------------------------------------------
 *  Input  : arr = [42]
 *  Output : 42->NULL
 *
 *      head
 *       |
 *       v
 *     +----+------+
 *     | 42 | NULL |      head and tail are the SAME node
 *     +----+------+
 *       ^
 *      tail
 *
 * ----------------------------------------------------------------------------
 *  APPROACH : HEAD + TAIL APPEND
 * ----------------------------------------------------------------------------
 *    1. If the array is empty, return NULL (an empty list has no head).
 *    2. Create a node for arr[0]. It is both the head (entry point of the list)
 *       and the tail (last node built so far).
 *    3. For each remaining element, append a node AFTER the tail and move the
 *       tail forward:
 *           tail.next <- Node(arr[i])      // link the new node
 *           tail      <- tail.next         // the new node is the last one now
 *    4. Return head. Nothing else is needed: the last node's next is already
 *       NULL because the Node constructor initialises it.
 *
 *  WHY KEEP A tail POINTER?
 *    Appending needs the last node. Without tail you would walk from head to
 *    the end for every element: 1 + 2 + ... + n steps = O(n^2). With tail each
 *    append is O(1), so the whole build is O(n).
 *
 *  WHY RETURN head, NOT tail?
 *    The head is the only way to reach the list. Losing it loses every node
 *    (a memory leak). tail is a local helper that is discarded.
 *
 *  ALTERNATIVE APPROACHES (same O(n) time)
 *    - Dummy head : start with a throw-away node D, append everything after it
 *                   with the same tail logic, return D.next. This removes the
 *                   "first element is special" branch. Common in LeetCode
 *                   solutions that build or merge lists.
 *    - Insert at head from the back : loop i = n-1 down to 0 and push each
 *                   value at the front. No tail pointer needed.
 *    - Recursion  : build(i) = Node(arr[i]) with next = build(i + 1). Clean but
 *                   uses O(n) call stack, which can overflow for n = 10^5.
 *
 *  ALGORITHM (pseudocode)
 *
 *      BUILD_LIST(arr, n):
 *          if n <= 0:  return NULL
 *          head <- Node(arr[0])
 *          tail <- head
 *          for i from 1 to n - 1:
 *              tail.next <- Node(arr[i])
 *              tail      <- tail.next
 *          return head
 *
 *      PRINT_LIST(head):
 *          cur <- head                      // copy, so head itself is not moved
 *          while cur != NULL:
 *              print cur.data, "->"
 *              cur <- cur.next
 *          print "NULL"
 *
 *      DELETE_LIST(head):                   // head is a REFERENCE
 *          while head != NULL:
 *              nextNode <- head.next        // SAVE before deleting
 *              delete head
 *              head <- nextNode
 *          // head is now NULL, and so is the caller's pointer
 *
 * ----------------------------------------------------------------------------
 *  DRY RUN : arr = [5, 10, 15, 20]
 * ----------------------------------------------------------------------------
 *
 *  Step 1 : head = tail = new Node(5)
 *      head --> [5 | NULL]
 *                  ^ tail
 *
 *  Step 2 : tail.next = new Node(10);  tail = tail.next
 *      head --> [5 | o]--> [10 | NULL]
 *                              ^ tail
 *
 *  Step 3 : tail.next = new Node(15);  tail = tail.next
 *      head --> [5 | o]--> [10 | o]--> [15 | NULL]
 *                                          ^ tail
 *
 *  Step 4 : tail.next = new Node(20);  tail = tail.next
 *      head --> [5 | o]--> [10 | o]--> [15 | o]--> [20 | NULL]
 *                                                      ^ tail
 *
 *  Return head.  Printing walks 5 -> 10 -> 15 -> 20 -> NULL.
 *
 *  DELETE trace (same list)
 *      head=[5]  : save [10], delete [5],  head=[10]
 *      head=[10] : save [15], delete [10], head=[15]
 *      head=[15] : save [20], delete [15], head=[20]
 *      head=[20] : save NULL, delete [20], head=NULL  -> loop ends
 *
 * ----------------------------------------------------------------------------
 *  EDGE CASES HANDLED
 * ----------------------------------------------------------------------------
 *    - Empty array (n = 0)  : buildList returns NULL; printList prints "NULL";
 *                             deleteList does nothing.
 *    - One element (n = 1)  : the loop body never runs; head == tail.
 *    - Duplicates/negatives : only values are stored; nothing assumes order or
 *                             uniqueness.
 *    - Invalid size         : n < 0 or n > MAX_SIZE would break the fixed-size
 *                             input array, so it is rejected before reading.
 *    - Invalid element      : a non-integer token is reported, not stored.
 *    - Allocation failure   : if "new" throws midway, the partly built list is
 *                             freed and the exception is rethrown (no leak).
 *    - Printing             : walks a copy of head, so the caller's head is not
 *                             moved; an empty list prints "NULL", not "->NULL".
 *    - Deleting             : (1) next is saved before each delete (no
 *                             use-after-free); (2) head is passed by REFERENCE
 *                             so the caller's pointer also becomes NULL and
 *                             cannot dangle; (3) it is safe on an empty list.
 *
 *  COMPLEXITY
 *      Operation     Time    Auxiliary space
 *      ------------  ------  ---------------------------------------------
 *      buildList     O(n)    O(1)  (the n nodes are the output itself)
 *      printList     O(n)    O(1)
 *      deleteList    O(n)    O(1)
 *
 *  COMMON MISTAKES
 *    - Walking from head on every append                 -> O(n^2).
 *    - Forgetting "tail = tail->next"                    -> every node is
 *      attached to the same tail, so only the last value survives in the list.
 *    - Returning tail instead of head                    -> list is lost.
 *    - delete head; then reading head->next              -> use-after-free.
 *    - Passing head by value to deleteList               -> caller keeps a
 *      dangling pointer to freed memory.
 *    - Moving head while printing                        -> the list is
 *      unreachable afterwards (leak).
 */

#include <cstddef>
#include <iostream>

using namespace std;

// A node of the singly linked list.
struct Node {
    int   data;
    Node* next;

    // "explicit" blocks accidental int -> Node conversions; next starts as
    // nullptr, so the last node built is automatically NULL-terminated.
    explicit Node(int val) : data(val), next(nullptr) {}
};

static void deleteList(Node*& head);  // Defined below; used for error cleanup.

// Builds a singly linked list holding arr[0..n-1] in order and returns its head
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
            tail->next = new Node(arr[i]);  // 1. link the new node
            tail = tail->next;              // 2. advance the tail
        }
    } catch (...) {
        // tail->next is still nullptr if "new" threw, so the chain is valid.
        deleteList(head);
        throw;
    }

    // Callers need the head: it is the only way to reach the list.
    return head;
}

// Prints the list as "a->b->c->NULL" ("NULL" alone for an empty list).
// Time: O(n) | Space: O(1)
static void printList(const Node* head) {
    // Traverse with a copy so the caller's head is never moved.
    const Node* cur = head;
    while (cur != nullptr) {
        cout << cur->data << "->";
        cur = cur->next;
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

    cout << "Array print : [";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << (i == n - 1 ? "" : ", ");
    }
    cout << "]\n";

    Node* head = buildList(arr, n);
    cout << "Linked List print : ";
    printList(head);

    // Release the nodes; head becomes nullptr.
    deleteList(head);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}