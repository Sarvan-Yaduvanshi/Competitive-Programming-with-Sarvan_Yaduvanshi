/*
 * Author  : Sarvan Yaduvanshi
 * Created : 2026-09-25 04:31:12
 *
 * Doubly Linked List (C++17)
 * --------------------------------------------------------------------------
 * Every node stores its data plus pointers to BOTH its previous and next
 * node, so the list can be traversed in either direction. The list keeps a
 * head pointer, a tail pointer and a size counter, which makes operations at
 * both ends (including pop_back) and all boundary checks run in O(1).
 *
 *           head                      tail
 *            |                          |
 *   NULL <- [5] <-> [10] <-> [15] <-> [20] -> NULL
 *
 * How it compares with a singly linked list:
 *    * Faster pop_back: it is O(1) here, because tail->prev gives the second-to-last node directly. A singly linked list needs O(n) to find it.
 *    * Faster middle access: you can start from whichever end is closer, so reaching an index takes at most about n/2 steps.
 *    * Extra memory: every node stores one more pointer, and every insert or delete must update both prev and next links.
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
 *   9.  print()                       Print the list front to back
 *   10. printReverse()                Print the list back to front
 *   11. size()                        Return the number of elements
 *   12. clear()                       Remove every element
 *
 * Example trace
 *   start               : NULL
 *   push_back(10)       : 10 <-> NULL
 *   push_back(20)       : 10 <-> 20 <-> NULL
 *   push_front(5)       : 5 <-> 10 <-> 20 <-> NULL
 *   insert_middle(15,2) : 5 <-> 10 <-> 15 <-> 20 <-> NULL
 *   deleteAtIndex(1)    : 5 <-> 15 <-> 20 <-> NULL
 *   search_ll(15)       : 1
 *   getElementAtIndex(2): 20
 *   printReverse()      : 20 <-> 15 <-> 5 <-> NULL
 *
 * Error handling
 *   - pop_front / pop_back on an empty list  -> std::underflow_error
 *   - invalid index in insert / delete / get -> std::out_of_range
 *
 * Complexity notation: n = number of elements currently in the list.
 * "Space" refers to auxiliary space beyond the nodes the list itself stores.
 */

#include <cstddef>
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace std;

class DoublyLinkedList {
private:
    // Node type is an implementation detail and is hidden from callers.
    struct Node {
        int   data;
        Node* prev;
        Node* next;
        explicit Node(int val) : data(val), prev(nullptr), next(nullptr) {}
    };

    Node*  head;
    Node*  tail;
    size_t _size;  // Cached size keeps boundary checks O(1).

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
            cur = tail;
            for (size_t i = _size - 1; i > idx; i--) {
                cur = cur->prev;
            }
        }
        return cur;
    }

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), _size(0) {}

    // Owns raw heap memory, so copying would cause a double free.
    DoublyLinkedList(const DoublyLinkedList&)            = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

    // Time: O(n) | Space: O(1)
    ~DoublyLinkedList() { clear(); }

    // Inserts val at the front of the list.
    // Time: O(1) | Space: O(1)
    void push_front(const int val) {
        Node* newNode = new Node(val);

        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        _size++;
    }

    // Inserts val at the back of the list.
    // Time: O(1) | Space: O(1)
    void push_back(const int val) {
        Node* newNode = new Node(val);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        _size++;
    }

    // Removes the front element. Throws std::underflow_error if empty.
    // Time: O(1) | Space: O(1)
    void pop_front() {
        if (head == nullptr) {
            throw underflow_error("Doubly Linked List is empty");
        }
        Node* temp = head;

        if (head == tail) {
            // Single-node list: both ends are cleared.
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }

        delete temp;
        _size--;
    }

    // Removes the back element. Throws std::underflow_error if empty.
    // Time: O(1) (tail->prev gives the new tail directly) | Space: O(1)
    void pop_back() {
        if (head == nullptr) {
            throw underflow_error("Doubly Linked List is empty");
        }
        Node* temp = tail;

        if (head == tail) {
            // Single-node list: both ends are cleared.
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }

        delete temp;
        _size--;
    }

    // Inserts val so that it ends up at index pos (0 <= pos <= size()).
    // Throws std::out_of_range for any other index.
    // Time: O(n) in general, O(1) when pos is 0 or size() | Space: O(1)
    void insert_middle(const int val, const int pos) {
        if (pos < 0 || static_cast<size_t>(pos) > _size) {
            throw out_of_range("Invalid position");
        }

        Node* newNode  = new Node(val);

        // Boundary cases reuse the O(1) operations above.
        if (pos == 0) {
            if (head == nullptr)
                head = tail = newNode;
            else{
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
            _size++;
            return;
        }
        if (static_cast<size_t>(pos) == _size) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
            _size++;
            return;
        }

        // Unlike a singly linked list, we can stop AT pos and step back
        // through prev, so no "node before" tracking is needed.
        Node* nextNode = node_at(pos);
        Node* prevNode = nextNode->prev;

        // Bridge the new node between its neighbours. (prevNode->newNode->nextNode)
        prevNode->next = newNode;
        newNode->next = nextNode;

        // Bridge the new node back to its neighbours. (prevNode<-newNode<-nextNode)
        newNode->prev = prevNode;
        nextNode->prev = newNode;

        _size++;
    }

    // Removes the element at index pos (0 <= pos < size()).
    // Throws std::out_of_range for any other index.
    // Time: O(n) in general, O(1) when pos is 0 or size() - 1 | Space: O(1)
    void deleteAtIndex(const int pos) {
        if (pos < 0 || static_cast<size_t>(pos) >= _size) {
            throw out_of_range("Invalid position");
        }

        // Case 1: delete head.
        if (pos == 0) {
            Node* temp = head;
            head = head->next;

            if (head != nullptr)
                head->prev = nullptr;
            else
                // List is now empty, so update tail as well.
                tail = nullptr;
            
            delete temp;
            _size--;
            return;
        }

        // Case 2: delete tail.
        if (static_cast<size_t>(pos) == _size - 1) {
            Node* prev = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete prev;
            _size--;
            return;
        }

        // Case 3: delete a middle node; bridge its neighbours, then free it.
        Node* target   = node_at(static_cast<size_t>(pos));
        Node* prevNode = target->prev;
        Node* nextNode = target->next;

        prevNode->next = nextNode;
        nextNode->prev = prevNode;

        delete target;
        _size--;
    }

    // Returns the index of the first node equal to key, or -1 if not found.
    // Time: O(n) | Space: O(1)
    int search_ll(const int key) const {
        const Node* temp = head;
        int idx = 0;
        while (temp != nullptr) {
            if (temp->data == key) {
                return idx;
            }
            temp = temp->next;
            idx++;
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

    // Prints the list front to back, e.g. "a <-> b <-> c <-> NULL".
    // Time: O(n) | Space: O(1)
    void print() const {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }
        const Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " <-> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    // Prints the list back to front, e.g. "c <-> b <-> a <-> NULL".
    // Time: O(n) | Space: O(1)
    void printReverse() const {
        if (tail == nullptr) {
            cout << "List is empty.\n";
            return;
        }
        const Node* temp = tail;
        while (temp != nullptr) {
            cout << temp->data << " <-> ";
            temp = temp->prev;
        }
        cout << "NULL\n";
    }

    // Time: O(1) | Space: O(1)
    size_t size() const { return _size; }

    // Removes every element and resets the list to its empty state.
    // Time: O(n) | Space: O(1)
    void clear() {
        Node* temp = head;
        while (temp != nullptr) {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        head = tail = nullptr;
        _size = 0;
    }
};

// Reads one integer from stdin. Returns false on EOF; on malformed input it
// clears the stream, discards the line, and sets ok to false.
static bool read_int(int& out, bool& ok) {
    ok = true;
    if (cin >> out) {
        return true;
    }
    if (cin.eof()) {
        return false;
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    ok = false;
    return true;
}

static void solve() {
    DoublyLinkedList dll;
    int choice = 0, val = 0, pos = 0;
    bool ok = true;

    while (true) {
        cout << "\n--- Doubly Linked List Operations ---\n"
             << "1.  Push Front\n"
             << "2.  Push Back\n"
             << "3.  Pop Front\n"
             << "4.  Pop Back\n"
             << "5.  Insert at Index\n"
             << "6.  Delete at Index\n"
             << "7.  Search\n"
             << "8.  Get Element at Index\n"
             << "9.  Print Forward\n"
             << "10. Print Reverse\n"
             << "11. Size\n"
             << "12. Clear\n"
             << "13. Exit\n"
             << "Enter choice: ";

        if (!read_int(choice, ok)) break;
        if (!ok) {
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        try {
            switch (choice) {
            case 1:
                cout << "Enter value: ";
                if (!read_int(val, ok)) return;
                if (!ok) { cout << "Invalid input!\n"; break; }
                dll.push_front(val);
                break;
            case 2:
                cout << "Enter value: ";
                if (!read_int(val, ok)) return;
                if (!ok) { cout << "Invalid input!\n"; break; }
                dll.push_back(val);
                break;
            case 3:
                dll.pop_front();
                cout << "Popped from front.\n";
                break;
            case 4:
                dll.pop_back();
                cout << "Popped from back.\n";
                break;
            case 5:
                cout << "Enter value and position: ";
                if (!read_int(val, ok)) return;
                if (ok && !read_int(pos, ok)) return;
                if (!ok) { cout << "Invalid input!\n"; break; }
                dll.insert_middle(val, pos);
                cout << "Inserted " << val << " at index " << pos << ".\n";
                break;
            case 6:
                cout << "Enter index to delete: ";
                if (!read_int(pos, ok)) return;
                if (!ok) { cout << "Invalid input!\n"; break; }
                dll.deleteAtIndex(pos);
                cout << "Deleted index " << pos << ".\n";
                break;
            case 7:
                cout << "Enter value to search: ";
                if (!read_int(val, ok)) return;
                if (!ok) { cout << "Invalid input!\n"; break; }
                pos = dll.search_ll(val);
                if (pos != -1)
                    cout << "Found at index: " << pos << "\n";
                else
                    cout << "Not found.\n";
                break;
            case 8:
                cout << "Enter index: ";
                if (!read_int(pos, ok)) return;
                if (!ok) { cout << "Invalid input!\n"; break; }
                cout << "Element at index " << pos << ": "
                     << dll.getElementAtIndex(pos) << "\n";
                break;
            case 9:
                dll.print();
                break;
            case 10:
                dll.printReverse();
                break;
            case 11:
                cout << "Size: " << dll.size() << "\n";
                break;
            case 12:
                dll.clear();
                cout << "List cleared.\n";
                break;
            case 13:
                return;
            default:
                cout << "Invalid choice!\n";
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}