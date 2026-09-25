/*
Author: Sarvan Yaduvanshi
Created : 2026-09-23 14:45:14
*/

#include <iostream>
#include <stdexcept>
using namespace std;

/*
  <---------- Implementation of Singly Linked List in C++ ---------->

  Built Singly Linked List with the following operations:
    1. push_front(int val)  → Insert at the front
    2. push_back(int val)   → Insert at the back
    3. pop_front()           → Remove from the front
    4. pop_back()            → Remove from the back
    5. insert_at_position(int val, int pos) → Insert at a specific position
    6. search(int key)       → Search for a value
    7. print()                → Print the entire list

    For example, to create a list with values 1 → 2 → 3 → 5 -> 6 → NULL, you can use:
      List ll;
      ll.push_back(1);
      ll.push_back(2);
      ll.push_back(3);
      ll.push_back(5);
      ll.push_back(6);
      ll.print(); // Output: 1->2->3->5->6->NULL
*/

#include <iostream>
#include <stdexcept>

class List {
private:
    // Node is hidden entirely inside the List class
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t _size; // Tracking size makes edge-case checks O(1)

public:
    // Constructor
    List() : head(nullptr), tail(nullptr), _size(0) {}

    // Destructor (Crucial for GM level - prevents memory leaks)
    ~List() {
        while (head != nullptr) {
            pop_front();
        }
    }

    void push_front(int val) {
        Node* newNode = new Node(val);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        _size++;
    }

    void push_back(int val) {
        Node* newNode = new Node(val);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        _size++;
    }

    void pop_front() {
        if (head == nullptr) {
            throw std::underflow_error("Linked List is empty");
        }
        Node* temp = head;
        head = head->next;

        // If the list became empty, tail must also be updated!
        if (head == nullptr) {
            tail = nullptr;
        }

        delete temp;
        _size--;
    }

    void pop_back() {
        if (head == nullptr) {
            throw std::underflow_error("Linked List is empty");
        }

        // Handle single node case safely
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node* temp = head;
            // Iterate safely to the second-to-last node
            while (temp->next != tail) {
                temp = temp->next;
            }
            delete tail;
            tail = temp;
            tail->next = nullptr;
        }
        _size--;
    }

    void insert_middle(int val, int pos) {
        if (pos < 0 || pos > _size) {
            throw std::out_of_range("Invalid position");
        }
        if (pos == 0) {
            push_front(val);
            return;
        }
        if (pos == _size) {
            push_back(val);
            return;
        }

        Node* temp = head;
        for (int i = 0; i < pos - 1; i++) {
            temp = temp->next;
        }

        Node* newNode = new Node(val);
        newNode->next = temp->next;
        temp->next = newNode;
        _size++;
    }

    // Marked as const because it doesn't modify the list
    int search_ll(int key) const {
        Node* temp = head;
        int idx = 0;
        while (temp != nullptr) {
            if (temp->data == key) return idx;
            temp = temp->next;
            idx++;
        }
        return -1; // -1 indicates not found
    }

    // Marked as const
    void print() const {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    size_t size() const { return _size; }
};

static void solve(){
    List ll;
    int choice, val, pos;

    while (true) {
        cout << "\n--- Linked List Operations ---\n";
        cout << "1. Push Front\n2. Push Back\n3. Pop Front\n4. Pop Back\n";
        cout << "5. Insert Middle\n6. Search\n7. Print\n8. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) break;

        try {
            switch (choice) {
            case 1:
                cout << "Enter value: "; cin >> val;
                ll.push_front(val);
                break;
            case 2:
                cout << "Enter value: "; cin >> val;
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
                cout << "Enter value and position: "; cin >> val >> pos;
                ll.insert_middle(val, pos);
                break;
            case 6:
                cout << "Enter value to search: "; cin >> val;
                pos = ll.search_ll(val);
                if (pos != -1) cout << "Found at index: " << pos << "\n";
                else cout << "Not found.\n";
                break;
            case 7:
                ll.print();
                break;
            case 8:
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

