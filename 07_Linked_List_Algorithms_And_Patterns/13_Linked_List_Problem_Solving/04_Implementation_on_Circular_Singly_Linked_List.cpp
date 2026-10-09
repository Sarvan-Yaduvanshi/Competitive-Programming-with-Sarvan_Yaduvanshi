/*
 * Author  : Sarvan Yaduvanshi
 * Created : 2026-09-29 14:42:59
 *
 * Circular Singly Linked List (C++17)
 * --------------------------------------------------------------------------
 * A singly linked list whose last node points back to the first node instead
 * of NULL. Only a tail pointer is stored: the head is always tail->next, so
 * insertion at both ends is O(1). Because there is no NULL terminator, every
 * traversal is bounded by the cached size rather than by a NULL check.
 *
 *        head                tail
 *         |                   |
 *        [5] -> [10] -> [15] -> [20] --+
 *         ^                            |
 *         +----------------------------+
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
 *   13. print()                       Print the list
 *   14. size() / isEmpty()            Query the number of elements
 *   15. clear()                       Remove every element
 *
 * Example trace
 *   start               : NULL
 *   push_back(10)       : 10 -> (back to 10)
 *   push_back(20)       : 10 -> 20 -> (back to 10)
 *   push_front(5)       : 5 -> 10 -> 20 -> (back to 5)
 *   insert_middle(15,2) : 5 -> 10 -> 15 -> 20 -> (back to 5)
 *   deleteAtIndex(1)    : 5 -> 15 -> 20 -> (back to 5)
 *   search_ll(15)       : 1
 *   getElementAtIndex(2): 20
 *   rotate(1)           : 15 -> 20 -> 5 -> (back to 15)
 *   reverse()           : 5 -> 20 -> 15 -> (back to 5)
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

using namespace std;

class CircularSinglyLinkedList {
private:
    // Node type is an implementation detail and is hidden from callers.
    struct Node {
        int   data;
        Node* next;
        explicit Node(int val) : data(val), next(nullptr) {}
    };

    Node*  tail;   // head is always tail->next
    size_t _size;  // Cached size bounds every traversal and keeps checks O(1).

public:
    CircularSinglyLinkedList() : tail(nullptr), _size(0) {}

    // Owns raw heap memory, so copying would cause a double free.
    CircularSinglyLinkedList(const CircularSinglyLinkedList&)            = delete;
    CircularSinglyLinkedList& operator=(const CircularSinglyLinkedList&) = delete;

    // Time: O(n) | Space: O(1)
    ~CircularSinglyLinkedList() { clear(); }

    // Time: O(1) | Space: O(1)
    bool isEmpty() const { return tail == nullptr; }

    // Time: O(1) | Space: O(1)
    size_t size() const { return _size; }

    // Returns the first value. Throws std::underflow_error if empty.
    // Time: O(1) | Space: O(1)
    int getFront() const {
        if (isEmpty()) {
            throw underflow_error("Circular Linked List is empty");
        }
        return tail->next->data;
    }

    // Returns the last value. Throws std::underflow_error if empty.
    // Time: O(1) | Space: O(1)
    int getBack() const {
        if (isEmpty()) {
            throw underflow_error("Circular Linked List is empty");
        }
        return tail->data;
    }

    // Inserts val at the front of the list.
    // Time: O(1) | Space: O(1)
    void push_front(const int val) {
        Node* newNode = new Node(val);
        if (tail == nullptr) {
            newNode->next = newNode;  // A lone node points to itself.
            tail = newNode;
        } else {
            newNode->next = tail->next;  // New node points to the old head.
            tail->next = newNode;        // Tail now points to the new head.
        }
        _size++;
    }

    // Inserts val at the back of the list.
    // Time: O(1) | Space: O(1)
    void push_back(const int val) {
        Node* newNode = new Node(val);
        if (tail == nullptr) {
            newNode->next = newNode;  // A lone node points to itself.
        } else {
            newNode->next = tail->next;  // New node points to the head.
            tail->next = newNode;        // Old tail points to the new node.
        }
        tail = newNode;  // The new node is the tail in both cases.
        _size++;
    }

    // Removes the front element. Throws std::underflow_error if empty.
    // Time: O(1) | Space: O(1)
    void pop_front() {
        if (tail == nullptr) {
            throw underflow_error("Circular Linked List is empty");
        }
        Node* head = tail->next;

        if (head == tail) {
            // Single-node list becomes empty.
            tail = nullptr;
        } else {
            tail->next = head->next;  // Skip over the old head.
        }

        delete head;
        _size--;
    }

    // Removes the back element. Throws std::underflow_error if empty.
    // Time: O(n) (must locate the second-to-last node) | Space: O(1)
    void pop_back() {
        if (tail == nullptr) {
            throw underflow_error("Circular Linked List is empty");
        }

        if (tail->next == tail) {
            // Single-node list becomes empty.
            delete tail;
            tail = nullptr;
        } else {
            // Stop at the node whose next is the tail (NOT nullptr: the
            // list is circular, so no node ever points to nullptr).
            Node* prev = tail->next;
            while (prev->next != tail) {
                prev = prev->next;
            }
            prev->next = tail->next;  // Close the circle around the old tail.
            delete tail;
            tail = prev;
        }
        _size--;
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

        // A singly linked list needs the node BEFORE the target index.
        Node* prev = tail->next;
        for (int i = 0; i < pos - 1; i++) {
            prev = prev->next;
        }

        Node* newNode = new Node(val);
        newNode->next = prev->next;
        prev->next = newNode;
        _size++;
    }

    // Removes the element at index pos (0 <= pos < size()).
    // Throws std::out_of_range for any other index.
    // Time: O(n) in general, O(1) when pos is 0 | Space: O(1)
    void deleteAtIndex(const int pos) {
        if (pos < 0 || static_cast<size_t>(pos) >= _size) {
            throw out_of_range("Invalid position");
        }

        // Case 1: delete head.
        if (pos == 0) {
            pop_front();
            return;
        }

        // Case 2: delete tail.
        if (static_cast<size_t>(pos) == _size - 1) {
            pop_back();
            return;
        }

        // Case 3: delete a middle node; walk to the node BEFORE it.
        Node* prev = tail->next;
        for (int i = 0; i < pos - 1; i++) {
            prev = prev->next;
        }

        Node* target = prev->next;
        prev->next = target->next;  // Unlink before freeing.
        delete target;
        _size--;
    }

    // Returns the index of the first node equal to key, or -1 if not found.
    // Time: O(n) | Space: O(1)
    int search_ll(const int key) const {
        if (tail == nullptr) {
            return -1;
        }
        const Node* cur = tail->next;
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
    // Time: O(n) in general, O(1) for the first and last index | Space: O(1)
    int getElementAtIndex(const int idx) const {
        if (idx < 0 || static_cast<size_t>(idx) >= _size) {
            throw out_of_range("Invalid index");
        }

        // The tail pointer makes the last element reachable directly.
        if (static_cast<size_t>(idx) == _size - 1) {
            return tail->data;
        }

        const Node* cur = tail->next;
        for (int i = 0; i < idx; i++) {
            cur = cur->next;
        }
        return cur->data;
    }

    // Removes the first node holding key. Returns true if one was removed.
    // Time: O(n) | Space: O(1)
    bool removeFirstOccurrence(const int key) {
        if (tail == nullptr) {
            return false;
        }

        Node* prev = tail;
        Node* cur  = tail->next;

        for (size_t i = 0; i < _size; i++) {
            if (cur->data == key) {
                if (_size == 1) {
                    tail = nullptr;  // The only node is being removed.
                } else {
                    prev->next = cur->next;  // Bridge over the node.
                    if (cur == tail) {
                        tail = prev;  // Removed the tail: prev takes over.
                    }
                }
                delete cur;
                _size--;
                return true;
            }
            prev = cur;
            cur  = cur->next;
        }
        return false;
    }

    // Reverses the list in place by flipping every next pointer.
    // Time: O(n) | Space: O(1)
    void reverse() {
        if (tail == nullptr || tail->next == tail) {
            return;  // Empty or single-node lists are already reversed.
        }

        Node* oldHead = tail->next;
        Node* prev    = tail;
        Node* cur     = oldHead;

        // Flip each link exactly once; the loop stops when cur wraps to oldHead.
        do {
            Node* nextNode = cur->next;
            cur->next = prev;
            prev = cur;
            cur  = nextNode;
        } while (cur != oldHead);

        // The old head is now the last node.
        tail = oldHead;
    }

    // Rotates the list left by k positions: [1,2,3,4,5] with k = 2 becomes
    // [3,4,5,1,2]. Throws std::invalid_argument if k is negative.
    // Time: O(k mod n) | Space: O(1)
    void rotate(const int k) {
        if (k < 0) {
            throw invalid_argument("Rotation count must be non-negative");
        }
        if (tail == nullptr) {
            return;
        }

        // In a circular list, rotating just means moving the tail pointer.
        const size_t steps = static_cast<size_t>(k) % _size;
        for (size_t i = 0; i < steps; i++) {
            tail = tail->next;
        }
    }

    // Prints the list as "a -> b -> c -> (back to a)".
    // Time: O(n) | Space: O(1)
    void print() const {
        if (tail == nullptr) {
            cout << "List is empty.\n";
            return;
        }
        const Node* head = tail->next;
        const Node* cur  = head;
        for (size_t i = 0; i < _size; i++) {
            cout << cur->data << " -> ";
            cur = cur->next;
        }
        cout << "(back to " << head->data << ")\n";
    }

    // Removes every element and resets the list to its empty state.
    // Time: O(n) | Space: O(1)
    void clear() {
        if (tail == nullptr) {
            return;
        }

        Node* cur = tail->next;
        tail->next = nullptr;  // Break the circle so the loop can terminate.

        while (cur != nullptr) {
            Node* nextNode = cur->next;
            delete cur;
            cur = nextNode;
        }

        tail  = nullptr;
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
    CircularSinglyLinkedList cll;
    int choice = 0, val = 0, pos = 0;

    while (true) {
        cout << "\n--- Circular Singly Linked List Operations ---\n"
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
             << "14. Print\n"
             << "15. Size\n"
             << "16. Clear\n"
             << "17. Exit\n";

        if (!prompt_int("Enter choice: ", choice)) {
            if (cin.eof()) return;
            continue;
        }

        try {
            switch (choice) {
            case 1:
                if (!prompt_int("Enter value: ", val)) break;
                cll.push_front(val);
                break;
            case 2:
                if (!prompt_int("Enter value: ", val)) break;
                cll.push_back(val);
                break;
            case 3:
                cll.pop_front();
                cout << "Popped from front.\n";
                break;
            case 4:
                cll.pop_back();
                cout << "Popped from back.\n";
                break;
            case 5:
                if (!prompt_int("Enter value: ", val)) break;
                if (!prompt_int("Enter position: ", pos)) break;
                cll.insert_middle(val, pos);
                cout << "Inserted " << val << " at index " << pos << ".\n";
                break;
            case 6:
                if (!prompt_int("Enter index to delete: ", pos)) break;
                cll.deleteAtIndex(pos);
                cout << "Deleted index " << pos << ".\n";
                break;
            case 7:
                if (!prompt_int("Enter value to search: ", val)) break;
                pos = cll.search_ll(val);
                if (pos != -1)
                    cout << "Found at index: " << pos << "\n";
                else
                    cout << "Not found.\n";
                break;
            case 8:
                if (!prompt_int("Enter index: ", pos)) break;
                cout << "Element at index " << pos << ": "
                     << cll.getElementAtIndex(pos) << "\n";
                break;
            case 9:
                cout << "Front: " << cll.getFront() << "\n";
                break;
            case 10:
                cout << "Back: " << cll.getBack() << "\n";
                break;
            case 11:
                if (!prompt_int("Enter value to remove: ", val)) break;
                if (cll.removeFirstOccurrence(val))
                    cout << "Removed first occurrence of " << val << ".\n";
                else
                    cout << "Value not found.\n";
                break;
            case 12:
                cll.reverse();
                cout << "List reversed.\n";
                break;
            case 13:
                if (!prompt_int("Enter rotation count: ", pos)) break;
                cll.rotate(pos);
                cout << "Rotated left by " << pos << ".\n";
                break;
            case 14:
                cll.print();
                break;
            case 15:
                cout << "Size: " << cll.size() << "\n";
                break;
            case 16:
                cll.clear();
                cout << "List cleared.\n";
                break;
            case 17:
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