/*
Author: Sarvan Yaduvanshi
Created : 2026-09-25 00:55:41
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include <chrono>
#include <stdexcept>

using namespace std;

/*

Problem: Design a Linked List (LeetCode 707)
Difficulty: Medium, Topic: Linked List, Design

Design your implementation of the linked list. You can choose to use a singly or doubly linked list.
A node in a singly linked list should have two attributes:
    val and next. val is the value of the current node, and next is a pointer/reference to the next node.
If you want to use the doubly linked list, you will need one more attribute prev to indicate the previous node in the linked list. Assume all nodes in the linked list are 0-indexed.

Implement the MyLinkedList class:
    - MyLinkedList() Initializes the MyLinkedList object.
    - int get(int index) Get the value of the indexth node in the linked list. If the index is invalid, return -1.
    - void addAtHead(int val) Add a node of value val before the first element of the linked list.
        After the insertion, the new node will be the first node of the linked list.
    - void addAtTail(int val) Append a node of value val as the last element of the linked list.
    - void addAtIndex(int index, int val) Add a node of value val before the indexth node in the linked list.
        If index equals the length of the linked list, the node will be appended to the end of the linked list.
        If index is greater than the length, the node will not be inserted.
    - void deleteAtIndex(int index) Delete the indexth node in the linked list, if the index is valid.

Example 1:
Input
["MyLinkedList", "addAtHead", "addAtTail", "addAtIndex", "get", "deleteAtIndex", "get"]
[[], [1], [3], [1, 2], [1], [1], [1]]
Output
[null, null, null, null, 2, null, 3]

Explanation
MyLinkedList myLinkedList = new MyLinkedList();
myLinkedList.addAtHead(1);
myLinkedList.addAtTail(3);
myLinkedList.addAtIndex(1, 2);    // linked list becomes 1->2->3
myLinkedList.get(1);              // return 2
myLinkedList.deleteAtIndex(1);    // now the linked list is 1->3
myLinkedList.get(1);              // return 3


Constraints:
    0 <= index, val <= 1000
    Please do not use the built-in LinkedList library.
    At most 2000 calls will be made to get, addAtHead, addAtTail, addAtIndex and deleteAtIndex.
*/

class MyLinkedList {
protected:
    // Node is hidden entirely inside the List class
    struct Node{
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t _size; // Tracking size makes edge-case checks O(1)
public:
    // Constructor
    MyLinkedList() : head(nullptr), tail(nullptr), _size(0) {}

    int get(int index) {
        if (index < 0 || index >= _size)
            return -1;

        Node* temp = head;
        for (int i = 0; i < index; i++){
            temp = temp->next;
        }

        return temp->data;
    }

    void addAtHead(int val) {
        Node* newNode = new Node(val);
        if (head == nullptr)
            head = tail = newNode;
        else{
            newNode->next = head;
            head = newNode;
        }

        _size++;
    }

    void addAtTail(int val) {
        Node* newNode = new Node(val);
        if (head == nullptr)
            head = tail = nullptr;
        else{
            tail->next = newNode;
            tail = newNode;
        }

        _size++;
    }

    void addAtIndex(int index, int val) {
        if (index < 0 || index > _size)
            return;

        if (index == 0){
            addAtHead(val);
            return;
        }

        if (index == _size){
            addAtTail(val);
            return;
        }

        Node* temp = head;
        for (int i = 0; i < index - 1; i++){
            temp = temp->next;
        }

        Node* newNode = new Node(val);
        newNode->next = temp->next;
        temp->next = newNode;
        _size++;
    }

    void deleteAtIndex(int index) {
        if (index < 0 || index >= _size)
            return;

        if (index == 0){
            Node* temp = head;
            head = head->next;
            delete temp;

            _size--;
            if (_size == 0)
                tail = nullptr;
            return;;
        }

        Node* temp = head;
        for (int i = 0; i < index - 1; i++){
            temp = temp->next;
        }

        Node* deleteNode = temp->next;
        temp->next = deleteNode->next;

        if (deleteNode == tail)
            tail = temp;

        delete deleteNode;
        _size--;
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
};

void solve() {
    MyLinkedList ll;
    int choice, val, index;

    while (true){
        cout << "\n--- MyLinkedList Operations ---\n";
        cout << "1. Get Node (get)\n";
        cout << "2. Add at Head (addAtHead)\n";
        cout << "3. Add at Tail (addAtTail)\n";
        cout << "4. Add at Index (addAtIndex)\n";
        cout << "5. Delete at Index (deleteAtIndex)\n";
        cout << "6. Print\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) break;

        switch (choice) {
            case 1:
                cout << "Enter index: ";
                cin >> index;
                cout << "Value at index " << index << ": " << ll.get(index) << "\n";
                break;
            case 2:
                cout << "Enter value: ";
                cin >> val;
                ll.addAtHead(val);
                cout << "Added " << val << " at head.\n";
                break;
            case 3:
                cout << "Enter value: ";
                cin >> val;
                ll.addAtTail(val);
                cout << "Added " << val << " at tail.\n";
                break;
            case 4:
                cout << "Enter index and value (e.g., 2 10): ";
                cin >> index >> val;
                ll.addAtIndex(index, val);
                cout << "Attempted to add " << val << " at index " << index << ".\n";
                break;
            case 5:
                cout << "Enter index: ";
                cin >> index;
                ll.deleteAtIndex(index);
                cout << "Attempted to delete node at index " << index << ".\n";
                break;
            case 6:
                ll.print();
                break;
            case 7:
                cout << "Exiting...\n";
                return;
            default:
                cout << "Invalid choice! Please select 1-6.\n";
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << fixed << setprecision(10);
    
    // Multi-test case support (commented out for this demo)
    // int TC = 1;
    // cin >> TC;
    // while (TC--) solve();
    
    solve();
    return 0;
}

