/*
 * Author  : Sarvan Yaduvanshi
 * Created : 2026-09-23 14:45:14
 *
 * Singly Linked List (C++17)
 * --------------------------------------------------------------------------
 * A generic-free, integer-valued singly linked list that maintains both a
 * head and a tail pointer plus a size counter, so that insertion at the back
 * and all size/boundary checks run in constant time.
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
 *   9.  print()                       Print the list
 *   10. size()                        Return the number of elements
 *
 * Example trace
 *   start               : NULL
 *   push_back(10)       : 10 -> NULL
 *   push_back(20)       : 10 -> 20 -> NULL
 *   push_front(5)       : 5 -> 10 -> 20 -> NULL
 *   insert_middle(15,2) : 5 -> 10 -> 15 -> 20 -> NULL
 *   deleteAtIndex(1)    : 5 -> 15 -> 20 -> NULL
 *   search_ll(15)       : 1
 *   getElementAtIndex(2): 20
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

class List {
private:
    // Node type is an implementation detail and is hidden from callers.
    struct Node {
        int   data;
        Node* next;
        explicit Node(int val) : data(val), next(nullptr) {}
    };

    Node*  head;
    Node*  tail;
    size_t _size;  // Cached size keeps boundary checks O(1).

public:
    List() : head(nullptr), tail(nullptr), _size(0) {}

    // Owns raw heap memory, so copying would cause a double free.
    List(const List&)            = delete;
    List& operator=(const List&) = delete;

    // Time: O(n) | Space: O(1)
    ~List() {
        while (head != nullptr) {
            pop_front();
        }
    }

    // Inserts val at the front of the list.
    // Time: O(1) | Space: O(1)
    void push_front(const int val) {
        // Create a new Node and link curr node
        Node* newNode = new Node(val);

        // Case 1: empty list (both head and tail are newNode)
        if (head == nullptr) {
            head = tail = newNode;
        } else { // Case 2: non-empty list (head is updated to newNode)
            newNode->next = head;
            head = newNode;
        }
        _size++;
    }

    // Inserts val at the back of the list.
    // Time: O(1) | Space: O(1)
    void push_back(const int val) {
        // Create a new Node and link curr node
        Node* newNode = new Node(val);

        // Case 1: empty list (both head and tail are newNode)
        if (head == nullptr) {
            head = tail = newNode;
        } else { // Case 2: non-empty list (tail is updated to newNode)
            tail->next = newNode;
            tail = newNode;
        }
        _size++;
    }

    // Removes the front element. Throws std::underflow_error if empty.
    // Time: O(1) | Space: O(1)
    void pop_front() {
        if (head == nullptr) {
            throw underflow_error("Linked List is empty");
        }
        Node* temp = head;
        head = head->next;

        // The list became empty, so the tail must be reset as well.
        if (head == nullptr) {
            tail = nullptr;
        }

        delete temp;
        _size--;
    }

    // Removes the back element. Throws std::underflow_error if empty.
    // Time: O(n) (must locate the second-to-last node) | Space: O(1)
    void pop_back() {
        if (head == nullptr) {
            throw underflow_error("Linked List is empty");
        }

        // Single-node list: both head and tail are cleared.
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else { // Multi-node list: walk to the second-to-last node.
            Node* temp = head;
            while (temp->next != tail) {
                temp = temp->next;
            }
            delete tail;
            tail = temp;
            tail->next = nullptr;
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

        // Create a new Node and link curr node
        Node* newNode = new Node(val);

        // Case 1: insert at the front or Head (pos == 0)
        if (pos == 0) {
           newNode->next = head;
            head = newNode;
            if (_size == 0) {
                tail = newNode; // if the list is empty than tail update
            }
            _size++;
            return;
        }

        // Case 2: insert at the back or Tail (pos == size())
        if (static_cast<size_t>(pos) == _size) {
            tail->next = newNode;
            tail = newNode;
            _size++;
            return;
        }

        // A singly linked list needs the node BEFORE the target index.
        Node* prev = head;
        for (int i = 0; i < pos - 1; i++)
            prev = prev->next;

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

        // create a temporary pointer to traverse the list
        Node* temp = head;

        // Case 1: delete head.
        if (pos == 0) {
            head = head->next;
            // The list became empty, so the tail must be reset as well.
            if (head == nullptr)
                tail = nullptr;

            delete temp; // delete old head
            _size--;
            return;
        }

        // Case 2: delete tail.
        if (static_cast<size_t>(pos) == _size - 1) {
            Node* prev = head;
            while (prev->next != tail)
                prev = prev->next;

            delete tail;
            tail = prev;
            tail->next = nullptr;
            _size--;
            return;
        }

        // Case 3: delete a middle node; walk to the node BEFORE it.
        Node* prev = head;
        for (int i = 0; i < pos - 1; i++) {
            prev = prev->next;
        }

        Node* deleteNode = prev->next;
        prev->next = deleteNode->next;  // Unlink before freeing.
        delete deleteNode;
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
    // Time: O(n) in general, O(1) for the first and last index | Space: O(1)
    int getElementAtIndex(const int idx) const {
        if (idx < 0 || static_cast<size_t>(idx) >= _size) {
            throw out_of_range("Invalid index");
        }

        // The tail pointer makes the last element reachable directly.
        if (static_cast<size_t>(idx) == _size - 1) {
            return tail->data;
        }

        const Node* temp = head;
        for (int i = 0; i < idx; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

    // Prints the list in the form "a -> b -> c -> NULL".
    // Time: O(n) | Space: O(1)
    void print() const {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }
        const Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    // Time: O(1) | Space: O(1)
    size_t size() const { return _size; }
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
    List ll;
    int choice = 0, val = 0, pos = 0;
    bool ok = true;

    while (true) {
        cout << "\n--- Linked List Operations ---\n"
             << "1.  Push Front\n"
             << "2.  Push Back\n"
             << "3.  Pop Front\n"
             << "4.  Pop Back\n"
             << "5.  Insert at Index\n"
             << "6.  Delete at Index\n"
             << "7.  Search\n"
             << "8.  Print\n"
             << "9.  Get Element at Index\n"
             << "10. Size\n"
             << "11. Exit\n"
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
                ll.push_front(val);
                break;
            case 2:
                cout << "Enter value: ";
                if (!read_int(val, ok)) return;
                if (!ok) { cout << "Invalid input!\n"; break; }
                ll.push_back(val);
                break;
            case 3:
                ll.pop_front();
                cout << "Popped from front.\n";
                break;
            case 4:
                ll.pop_back();
                cout << "Popped from back.\n";
                break;
            case 5:
                cout << "Enter value and position: ";
                if (!read_int(val, ok)) return;
                if (ok && !read_int(pos, ok)) return;
                if (!ok) { cout << "Invalid input!\n"; break; }
                ll.insert_middle(val, pos);
                cout << "Inserted " << val << " at index " << pos << ".\n";
                break;
            case 6:
                cout << "Enter index to delete: ";
                if (!read_int(pos, ok)) return;
                if (!ok) { cout << "Invalid input!\n"; break; }
                ll.deleteAtIndex(pos);
                cout << "Deleted index " << pos << ".\n";
                break;
            case 7:
                cout << "Enter value to search: ";
                if (!read_int(val, ok)) return;
                if (!ok) { cout << "Invalid input!\n"; break; }
                pos = ll.search_ll(val);
                if (pos != -1)
                    cout << "Found at index: " << pos << "\n";
                else
                    cout << "Not found.\n";
                break;
            case 8:
                ll.print();
                break;
            case 9:
                cout << "Enter index: ";
                if (!read_int(pos, ok)) return;
                if (!ok) { cout << "Invalid input!\n"; break; }
                cout << "Element at index " << pos << ": "
                     << ll.getElementAtIndex(pos) << "\n";
                break;
            case 10:
                cout << "Size: " << ll.size() << "\n";
                break;
            case 11:
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