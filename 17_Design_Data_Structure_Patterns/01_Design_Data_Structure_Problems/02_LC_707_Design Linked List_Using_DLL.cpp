/*
Author: Sarvan Yaduvanshi
Created : 2026-11-05 19:22:22
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
#include <string>
#include <iomanip>
#include <random>
#include <chrono>
using namespace std;

// Approach 2: Design Linked List using Doubly Linked List (Optimal)
class MyDoublyLinkedList {
protected:
	// Node structure for the doubly linked list
	struct Node{
		int data;
		Node* prev;
		Node* next;
		explicit Node(const int val) : data(val), prev(nullptr), next(nullptr) {}
	};

	Node* head;
	Node* tail;
	size_t size;

public:
	MyDoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

	// Function 1: Get the value of the node at a specific index
	int get(const int idx){
		// Check for invalid index
		if (idx < 0 || idx >= size)
			return -1;

		// Optimize traversal by starting from head or tail based on index
		Node* temp;
		if (idx < size / 2){
			temp = head;
			for (int i = 0; i < idx; i++)
				temp = temp->next;
		} else{
			temp = tail;
			for (auto i = size - 1; i > idx; i--)
				temp = temp->prev;
		}

		return temp->data;
	}

	// Function 2: Add a node at the head of the linked list
	void addAtHead(int val){
		Node* newNode = new Node(val);

		// If the list is empty, set both head and tail to the new node
		if (head == nullptr){
			head = tail = newNode;
		// If the list is not empty, adjust pointers to insert at head
		} else{
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}
		size++;
	}

	// Function 3: Add a node at the tail of the linked list
	void addAtTail(int val){
		Node* newNode = new Node(val);
		if (head == nullptr){
			head = tail = newNode;
		} else{
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
		size++;
	}

	// Function 4: Add a node at a specific index in the linked list
	void addAtIndex(const int idx, const int val){
		if (idx < 0 || idx > size)
			return;

		if (idx == 0){
			addAtHead(val);
			return;
		}

		if (idx == size){
			addAtTail(val);
			return;
		}

		Node* temp = head;
		for (int i = 0; i < idx; i++)
			temp = temp->next;

		Node* previous = temp->prev;
		Node* newNode = new Node(val);

		newNode->prev = previous;
		newNode->next = temp;

		previous->next = newNode;
		temp->prev = newNode;

		size++;
	}

	// Function 5: Delete a node at a specific index in the linked list
	void deleteAtIndex(const int idx){
		if (idx < 0 || idx >= size)
			return;

		Node* temp = head;
		if (idx == 0){
			head = head->next;
			if (head != nullptr)
				head->prev = nullptr;
			else
				tail = nullptr;

			delete temp;
			size--;
			return;
		}

		for (int i = 0; i < idx; i++)
			temp = temp->next;

		if (temp == tail){
			tail = tail->prev;
			tail->next = nullptr;
			delete temp;
			size--;
			return;
		}

		Node* previous = temp->prev;
		Node* next = temp->next;

		previous->next = next;
		next->prev = previous;
		size--;
	}

	// Function 6: Print the linked list for debugging purposes
	void printLL(){
		const Node* temp = head;
		while (temp != nullptr){
			cout << temp->data << "->";
			temp = temp->next;
		}

		cout << "nullptr\n";
	}
};

static void solve(){
	MyDoublyLinkedList ll;
	ll.addAtHead(1);
	ll.addAtTail(3);
	ll.addAtIndex(1, 2);
	ll.get(1);
	ll.deleteAtIndex(1);
	ll.get(1);


	ll.printLL();
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}
