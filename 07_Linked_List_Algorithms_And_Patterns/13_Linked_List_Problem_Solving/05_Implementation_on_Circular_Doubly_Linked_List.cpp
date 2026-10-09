/*
 * Author  : Sarvan Yaduvanshi
 * Created : 2026-10-10
 *
 * Circular Doubly Linked List (C++17)
 * --------------------------------------------------------------------------
 * Every node stores its data plus pointers to its previous and next node,
 * and the list wraps around in BOTH directions: the last node's next is the
 * head, and the head's prev is the last node. Only a head pointer is stored,
 * because the tail is always head->prev. This gives O(1) access to both ends
 * (including pop_back). With no NULL terminator, every traversal is bounded by
 * the cached size instead of a NULL check.
 *
 *          +----------------------------------------+
 *          v                                        |
 *        head                                      tail
 *         [5] <-> [10] <-> [15] <-> [20]
 *          |                                        ^
 *          +----------------------------------------+
 *
 * Supported operations
 *   1.  push_front(val)               Insert a value at the front
 *   2.  push_back(val)                Insert a value at the back
 *   3.  pop_front()                   Remove the front element
 *   4.  pop_back()                    Remove the back element
 *   5.  insert_middle(val, pos)       Insert a value at a given index
 *   6.  deleteAtIndex(pos)            Remove the element at a given index
 *   7.  search_ll(key)                Return the index of a value, or -1
 *   8.  getElementAtIndex(idx)        Return the value stored at a given index
 *   9.  getFront() / getBack()        Peek at the first / last value
 *   10. removeFirstOccurrence(key)    Remove the first node holding key
 *   11. reverse()                     Reverse the list in place
 *   12. rotate(k)                     Rotate the list left by k positions
 *   13. print() / printReverse()      Print the list front-to-back / back-to-front
 *   14. size() / isEmpty()            Query the number of elements
 *   15. clear()                       Remove every element
 *
 * Example trace
 *   start               : NULL
 *   push_back(10)       : 10 <-> (back to 10)
 *   push_back(20)       : 10 <-> 20 <-> (back to 10)
 *   push_front(5)       : 5 <-> 10 <-> 20 <-> (back to 5)
 *   insert_middle(15,2) : 5 <-> 10 <-> 15 <-> 20 <-> (back to 5)
 *   deleteAtIndex(1)    : 5 <-> 15 <-> 20 <-> (back to 5)
 *   search_ll(15)       : 1
 *   getElementAtIndex(2): 20
 *   printReverse()      : 20 <-> 15 <-> 5 <-> (back to 20)
 *   rotate(1)           : 15 <-> 20 <-> 5 <-> (back to 15)
 *   reverse()           : 5 <-> 20 <-> 15 <-> (back to 5)
 *
 * Error handling
 *   - pop / getFront / getBack on an empty list -> std::underflow_error
 *   - invalid index in insert / delete / get    -> std::out_of_range
 *   - negative rotation count                   -> std::invalid_argument
 *
 * Complexity notation: n = number of elements currently in the list.
 * "Space" refers to auxiliary space beyond the nodes the list itself stores.
 */

#include <cstddef>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>

using namespace std;

class CircularDoublyLinkedList {
private:
    // Node type is an implementation detail and is hidden from callers.
    struct Node {
        int   data;
        Node* prev;
        Node* next;
        explicit Node(int val) : data(val), prev(nullptr), next(nullptr) {}
    };

    Node*  head;   // The tail is always head->prev.
    size_t _size;  // Cached size bounds every traversal and keeps checks O(1).

    // Creates a node holding val and links it immediately BEFORE `where`.
    // If `where` is nullptr (empty list) the node becomes a self-loop.
    // Returns the new node; the caller decides whether it becomes the head.
    // Time: O(1) | Space: O(1)
    Node* insert_before(Node* where, const int val) {
        Node* newNode = new Node(val);
        if (where == nullptr) {
            newNode->prev = newNode->next = newNode;
        } else {
            newNode->next = where;
            newNode->prev = where->prev;
            where->prev->next = newNode;
            where->prev = newNode;
        }
        _size++;
        return newNode;
    }

    // Detaches `node` from the list and frees it, fixing head if needed.
    // Time: O(1) | Space: O(1)
    void unlink(Node* node) {
        if (_size == 1) {
            head = nullptr;  // The only node is being removed.
        } else {
            node->prev->next = node->next;  // Bridge over the node.
            node->next->prev = node->prev;
            if (node == head) {
                head = node->next;
            }
        }
        delete node;
        _size--;
    }

    // Returns the node at index idx. Precondition: idx < _size.
    // Starts from whichever end is closer to idx.
    // Time: O(min(idx, n - idx)), i.e. O(n) worst case | Space: O(1)
    Node* node_at(const size_t idx) const {
        Node* cur;
        if (idx < _size / 2) {
            cur = head;
            for (size_t i = 0; i < idx; i++) {
                cur = cur->next;
            }
        } else {
            cur = head->prev;  // The tail.
            for (size_t i = _size - 1; i > idx; i--) {
                cur = cur->prev;
            }
        }
        return cur;
    }

public:
    CircularDoublyLinkedList() : head(nullptr), _size(0) {}

    // Owns raw heap memory, so copying would cause a double free.
    CircularDoublyLinkedList(const CircularDoublyLinkedList&)            = delete;
    CircularDoublyLinkedList& operator=(const CircularDoublyLinkedList&) = delete;

    // Time: O(n) | Space: O(1)
    ~CircularDoublyLinkedList() { clear(); }

    // Time: O(1) | Space: O(1)
    bool isEmpty() const { return head == nullptr; }

    // Time: O(1) | Space: O(1)
    size_t size() const { return _size; }

    // Returns the first value. Throws std::underflow_error if empty.
    // Time: O(1) | Space: O(1)
    int getFront() const {
        if (isEmpty()) {
            throw underflow_error("Circular Doubly Linked List is empty");
        }
        return head->data;
    }

    // Returns the last value. Throws std::underflow_error if empty.
    // Time: O(1) | Space: O(1)
    int getBack() const {
        if (isEmpty()) {
            throw underflow_error("Circular Doubly Linked List is empty");
        }
        return head->prev->data;
    }

    // Inserts val at the front of the list.
    // Time: O(1) | Space: O(1)
    void push_front(const int val) {
        // Inserting before the head places the node at the tail position;
        // moving head onto it makes it the new front.
        head = insert_before(head, val);
    }

    // Inserts val at the back of the list.
    // Time: O(1) | Space: O(1)
    void push_back(const int val) {
        Node* newNode = insert_before(head, val);
        if (head == nullptr) {
            head = newNode;  // First element: it is both head and tail.
        }
    }

    // Removes the front element. Throws std::underflow_error if empty.
    // Time: O(1) | Space: O(1)
    void pop_front() {
        if (head == nullptr) {
            throw underflow_error("Circular Doubly Linked List is empty");
        }
        unlink(head);
    }

    // Removes the back element. Throws std::underflow_error if empty.
    // Time: O(1) (the tail is head->prev) | Space: O(1)
    void pop_back() {
        if (head == nullptr) {
            throw underflow_error("Circular Doubly Linked List is empty");
        }
        unlink(head->prev);
    }

    // Inserts val so that it ends up at index pos (0 <= pos <= size()).
    // Throws std::out_of_range for any other index.
    // Time: O(n) in general, O(1) when pos is 0 or size() | Space: O(1)
    void insert_middle(const int val, const int pos) {
        if (pos < 0 || static_cast<size_t>(pos) > _size) {
            throw out_of_range("Invalid position");
        }

        // Boundary cases reuse the O(1) operations above.
        if (pos == 0) {
            push_front(val);
            return;
        }
        if (static_cast<size_t>(pos) == _size) {
            push_back(val);
            return;
        }

        // Stop AT pos and insert before it; prev gives the left neighbour.
        insert_before(node_at(static_cast<size_t>(pos)), val);
    }

    // Removes the element at index pos (0 <= pos < size()).
    // Throws std::out_of_range for any other index.
    // Time: O(n) in general, O(1) when pos is 0 or size() - 1 | Space: O(1)
    void deleteAtIndex(const int pos) {
        if (pos < 0 || static_cast<size_t>(pos) >= _size) {
            throw out_of_range("Invalid position");
        }
        unlink(node_at(static_cast<size_t>(pos)));
    }

    // Returns the index of the first node equal to key, or -1 if not found.
    // Time: O(n) | Space: O(1)
    int search_ll(const int key) const {
        if (head == nullptr) {
            return -1;
        }
        const Node* cur = head;
        for (size_t i = 0; i < _size; i++) {
            if (cur->data == key) {
                return static_cast<int>(i);
            }
            cur = cur->next;
        }
        return -1;
    }

    // Returns the value stored at index idx (0 <= idx < size()).
    // Throws std::out_of_range for any other index.
    // Time: O(n) worst case, O(1) at either end | Space: O(1)
    int getElementAtIndex(const int idx) const {
        if (idx < 0 || static_cast<size_t>(idx) >= _size) {
            throw out_of_range("Invalid index");
        }
        return node_at(static_cast<size_t>(idx))->data;
    }

    // Removes the first node holding key. Returns true if one was removed.
    // Time: O(n) | Space: O(1)
    bool removeFirstOccurrence(const int key) {
        if (head == nullptr) {
            return false;
        }
        Node* cur = head;
        for (size_t i = 0; i < _size; i++) {
            if (cur->data == key) {
                unlink(cur);
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    // Reverses the list in place by swapping every node's prev and next.
    // Time: O(n) | Space: O(1)
    void reverse() {
        if (head == nullptr || _size == 1) {
            return;  // Empty or single-node lists are already reversed.
        }

        Node* cur = head;
        for (size_t i = 0; i < _size; i++) {
            swap(cur->prev, cur->next);
            cur = cur->prev;  // After the swap, prev holds the OLD next.
        }

        // The old tail is now reachable as head->next (it was head->prev).
        head = head->next;
    }

    // Rotates the list left by k positions: [1,2,3,4,5] with k = 2 becomes
    // [3,4,5,1,2]. Throws std::invalid_argument if k is negative.
    // Time: O(min(k mod n, n - k mod n)) | Space: O(1)
    void rotate(const int k) {
        if (k < 0) {
            throw invalid_argument("Rotation count must be non-negative");
        }
        if (head == nullptr) {
            return;
        }

        // Rotating a circular list only moves the head pointer. Walk the
        // shorter way around: forward for a left rotation, backward if the
        // equivalent right rotation is cheaper.
        const size_t steps = static_cast<size_t>(k) % _size;
        if (steps <= _size - steps) {
            for (size_t i = 0; i < steps; i++) {
                head = head->next;
            }
        } else {
            for (size_t i = 0; i < _size - steps; i++) {
                head = head->prev;
            }
        }
    }

    // Prints the list front to back: "a <-> b <-> c <-> (back to a)".
    // Time: O(n) | Space: O(1)
    void print() const {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }
        const Node* cur = head;
        for (size_t i = 0; i < _size; i++) {
            cout << cur->data << " <-> ";
            cur = cur->next;
        }
        cout << "(back to " << head->data << ")\n";
    }

    // Prints the list back to front: "c <-> b <-> a <-> (back to c)".
    // Time: O(n) | Space: O(1)
    void printReverse() const {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }
        const Node* tail = head->prev;
        const Node* cur  = tail;
        for (size_t i = 0; i < _size; i++) {
            cout << cur->data << " <-> ";
            cur = cur->prev;
        }
        cout << "(back to " << tail->data << ")\n";
    }

    // Removes every element and resets the list to its empty state.
    // Time: O(n) | Space: O(1)
    void clear() {
        Node* cur = head;
        for (size_t i = 0; i < _size; i++) {
            Node* nextNode = cur->next;
            delete cur;
            cur = nextNode;
        }
        head  = nullptr;
        _size = 0;
    }
};

// Prints msg and reads one integer. Returns false on failure. On malformed
// input it clears the stream, discards the line, and reports the problem;
// on EOF it stays silent so the caller can exit via cin.eof().
static bool prompt_int(const char* msg, int& out) {
    cout << msg;
    if (cin >> out) {
        return true;
    }
    if (!cin.eof()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input!\n";
    }
    return false;
}

static void solve() {
    CircularDoublyLinkedList cdll;
    int choice = 0, val = 0, pos = 0;

    while (true) {
        cout << "\n--- Circular Doubly Linked List Operations ---\n"
             << "1.  Push Front\n"
             << "2.  Push Back\n"
             << "3.  Pop Front\n"
             << "4.  Pop Back\n"
             << "5.  Insert at Index\n"
             << "6.  Delete at Index\n"
             << "7.  Search\n"
             << "8.  Get Element at Index\n"
             << "9.  Get Front\n"
             << "10. Get Back\n"
             << "11. Remove First Occurrence\n"
             << "12. Reverse\n"
             << "13. Rotate Left\n"
             << "14. Print Forward\n"
             << "15. Print Reverse\n"
             << "16. Size\n"
             << "17. Clear\n"
             << "18. Exit\n";

        if (!prompt_int("Enter choice: ", choice)) {
            if (cin.eof()) return;
            continue;
        }

        try {
            switch (choice) {
            case 1:
                if (!prompt_int("Enter value: ", val)) break;
                cdll.push_front(val);
                break;
            case 2:
                if (!prompt_int("Enter value: ", val)) break;
                cdll.push_back(val);
                break;
            case 3:
                cdll.pop_front();
                cout << "Popped from front.\n";
                break;
            case 4:
                cdll.pop_back();
                cout << "Popped from back.\n";
                break;
            case 5:
                if (!prompt_int("Enter value: ", val)) break;
                if (!prompt_int("Enter position: ", pos)) break;
                cdll.insert_middle(val, pos);
                cout << "Inserted " << val << " at index " << pos << ".\n";
                break;
            case 6:
                if (!prompt_int("Enter index to delete: ", pos)) break;
                cdll.deleteAtIndex(pos);
                cout << "Deleted index " << pos << ".\n";
                break;
            case 7:
                if (!prompt_int("Enter value to search: ", val)) break;
                pos = cdll.search_ll(val);
                if (pos != -1)
                    cout << "Found at index: " << pos << "\n";
                else
                    cout << "Not found.\n";
                break;
            case 8:
                if (!prompt_int("Enter index: ", pos)) break;
                cout << "Element at index " << pos << ": "
                     << cdll.getElementAtIndex(pos) << "\n";
                break;
            case 9:
                cout << "Front: " << cdll.getFront() << "\n";
                break;
            case 10:
                cout << "Back: " << cdll.getBack() << "\n";
                break;
            case 11:
                if (!prompt_int("Enter value to remove: ", val)) break;
                if (cdll.removeFirstOccurrence(val))
                    cout << "Removed first occurrence of " << val << ".\n";
                else
                    cout << "Value not found.\n";
                break;
            case 12:
                cdll.reverse();
                cout << "List reversed.\n";
                break;
            case 13:
                if (!prompt_int("Enter rotation count: ", pos)) break;
                cdll.rotate(pos);
                cout << "Rotated left by " << pos << ".\n";
                break;
            case 14:
                cdll.print();
                break;
            case 15:
                cdll.printReverse();
                break;
            case 16:
                cout << "Size: " << cdll.size() << "\n";
                break;
            case 17:
                cdll.clear();
                cout << "List cleared.\n";
                break;
            case 18:
                return;
            default:
                cout << "Invalid choice!\n";
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
        }

        if (cin.eof()) return;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}
