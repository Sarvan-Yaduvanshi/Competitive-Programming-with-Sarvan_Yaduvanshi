/*
Author: Sarvan Yaduvanshi
Created : 2026-11-05 19:20:15
*/

/*
 * ============================================================================
 *  707. Design Linked List
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 707
 *  Difficulty : Medium
 *  Topics     : Linked List, Design
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Design your implementation of the linked list. You can choose to use a
 *  singly or doubly linked list.
 *
 *  A node in a singly linked list should have two attributes: val and next.
 *  val is the value of the current node, and next is a pointer/reference to
 *  the next node.
 *
 *  If you want to use the doubly linked list, you will need one more
 *  attribute prev to indicate the previous node in the linked list. Assume
 *  all nodes in the linked list are 0-indexed.
 *
 *  Implement the MyLinkedList class:
 *
 *      - MyLinkedList()
 *            Initializes the MyLinkedList object.
 *
 *      - int get(int index)
 *            Get the value of the indexth node in the linked list. If the
 *            index is invalid, return -1.
 *
 *      - void addAtHead(int val)
 *            Add a node of value val before the first element of the linked
 *            list. After the insertion, the new node will be the first node
 *            of the linked list.
 *
 *      - void addAtTail(int val)
 *            Append a node of value val as the last element of the linked
 *            list.
 *
 *      - void addAtIndex(int index, int val)
 *            Add a node of value val before the indexth node in the linked
 *            list. If index equals the length of the linked list, the node
 *            will be appended to the end of the linked list. If index is
 *            greater than the length, the node will not be inserted.
 *
 *      - void deleteAtIndex(int index)
 *            Delete the indexth node in the linked list, if the index is
 *            valid.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      Input
 *      ["MyLinkedList", "addAtHead", "addAtTail", "addAtIndex", "get",
 *       "deleteAtIndex", "get"]
 *      [[], [1], [3], [1, 2], [1], [1], [1]]
 *
 *      Output
 *      [null, null, null, null, 2, null, 3]
 *
 *  Explanation:
 *      MyLinkedList myLinkedList = new MyLinkedList();
 *      myLinkedList.addAtHead(1);
 *      myLinkedList.addAtTail(3);
 *      myLinkedList.addAtIndex(1, 2);    // linked list becomes 1->2->3
 *      myLinkedList.get(1);              // return 2
 *      myLinkedList.deleteAtIndex(1);    // now the linked list is 1->3
 *      myLinkedList.get(1);              // return 3
 *
 * ----------------------------------------------------------------------------
 *  Picture (list after each call):
 *
 *      new               :  (empty)
 *      addAtHead(1)      :  1
 *      addAtTail(3)      :  1 -> 3
 *      addAtIndex(1, 2)  :  1 -> 2 -> 3
 *      get(1)            :  1 -> 2 -> 3        returns 2
 *      deleteAtIndex(1)  :  1 -> 3
 *      get(1)            :  1 -> 3             returns 3
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - 0 <= index, val <= 1000
 *      - Please do not use the built-in LinkedList library.
 *      - At most 2000 calls will be made to get, addAtHead, addAtTail,
 *        addAtIndex and deleteAtIndex.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class MyLinkedList {
private:
    // Node structure
    struct Node {
        int val;
        Node* next;

        explicit Node(const int v) : val(v), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t _size;

public:
    // Function 1: Initialize the my linked list object
    MyLinkedList() : head(nullptr), tail(nullptr), _size(0) {}

    // Function 2: Get the value of the indexth node in the linked list
    int get(int index) {
        // Check for invalid index
        if (index < 0 || index >= _size)
            return -1;

        Node* temp = head;
        for (int i = 0; i < index; i++)
            temp = temp->next;

        return temp->val;
    }

    // Function 3: Add a node of value val before the first element of the linked list
    void addAtHead(int val) {
        // Step 1: Create a new node with the given value
        Node* newNode = new Node(val);

        // Step 2: If the list is empty, set both head and tail to the new node
        if (head == nullptr)
            head = tail = newNode;
       // Step 3: If the list is not empty, insert the new node at the head
        else {
            newNode->next = head;
            head = newNode;
        }

        _size++;
    }

    // Function 4: Add a node of value val as the last element of the linked list
    void addAtTail(int val) {
        // Step 1: Create a new node with the given value
        Node* newNode = new Node(val);

        // Step 2: If the list is empty, set both head and tail to the new node
        if (head == nullptr)
            head = tail = newNode;
        // Step 3: If the list is not empty, insert the new node at the tail
        else {
            tail->next = newNode;
            tail = newNode;
        }

        _size++;
    }

    // Function 5: Add a node of value val before the indexth node in the linked list
    void addAtIndex(int index, int val) {
        // Check for invalid index
        if (index < 0 || index > _size)
            return;

        // Case 1: If index is 0, add at head
        if (index == 0) {
            addAtHead(val);
            return;
        }

        // Case 2: If index is equal to the size, add at tail
        if (index == _size) {
            addAtTail(val);
            return;
        }

        // Case 3: Insert in the middle of the list
        Node* temp = head;
        for (int i = 0; i < index - 1; i++)
            temp = temp->next;

        // Create a new node and insert it after temp
        Node* nextNode = temp->next;

        Node* newNode = new Node(val);
        newNode->next = nextNode;
        temp->next = newNode;

        _size++;
    }

    // Function 6: Delete the indexth node in the linked list, if the index is valid
    void deleteAtIndex(int index) {
        // Check for invalid index
        if (index < 0 || index >= _size)
            return;

        // Case 1: If index is 0, delete the head node
        if (index == 0) {
            Node* temp = head;
            head = head->next;

            // If the list becomes empty after deletion, set tail to nullptr
            if (head == nullptr)
                tail = nullptr;

            delete temp;
            _size--;
            return;
        }

        // Case 2: Delete a node in the middle or at the tail
        Node* temp = head;
        for (int i = 0; i < index - 1; i++)
            temp = temp->next;

        // save the node to be deleted
        Node* deleteNode = temp->next;

        // If the node to be deleted is the tail, update the tail pointer
        if (deleteNode == tail)
            tail = temp;

        // link the previous node to the next node, effectively removing the deleteNode from the list
        temp->next = deleteNode->next;
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
            cout << temp->val << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
};

static void solve() {
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

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();

	return 0;
}