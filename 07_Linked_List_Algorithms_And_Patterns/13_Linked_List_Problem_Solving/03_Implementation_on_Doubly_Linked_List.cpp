/*
Author: Sarvan Yaduvanshi
Created : 2026-09-25 04:31:12
*/

#include <iostream>
#include <stdexcept>
using namespace std;

/*
 *  <---------- Implementation of Doubly Linked List in C++ ---------->
 *
 *  Built Doubly Linked List with the following operations:
 *		1. push_front(int val)  → Insert at the front
 *		2. push_back(int val)   → Insert at the back
 *		3. pop_front()           → Remove from the front
 *		4. pop_back()            → Remove from the back
 *		5. insert_at_position(int val, int pos) → Insert at a specific
 *		6. delete_at_position(int pos) → Delete at a specific position
 *		7. search(int key)       → Search for a value
 *		8. print()                → Print the entire list
 *
 *	For example, the list will look like:
 *		start as empty: NULL
 *		operations:
 *			push_back(10): 10 -> NULL
 *			push_back(20): 10 -> 20 -> NULL
 *			push_front(5): 5 -> 10 -> 20 -> NULL
 *			insert_at_position(15, 2): 5 -> 10 -> 15
 *			delete_at_position(1): 5 -> 15 -> 20 -> NULL
 *			search(15): returns index 1
 *			print(head): 5 -> 15 -> 20 -> NULL
*/
class doublyLinkedList{
protected:
	struct Node{
		int data;
		Node* prev;
		Node* next;
		// Constructor: initialize the values without initialize all node as garbage value
		Node(const int val) : data(val), prev(nullptr), next(nullptr) {}
	};

	Node* head;
	Node* tail;
	size_t size;

public:
	doublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

	// Operation 1) push_front() -> insert node as front
	void push_frontOrAddAtHead(const int val){
		Node* newNode = new Node(val);

		if (head == nullptr)
			head = tail = nullptr;
		else{
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}
		size++;
	}

	// Operation 2) push_back() -> insert node as last
	void push_backOrAddAtTail(const int val){
		Node* newNode = new Node(val);

		if (head == nullptr)
			head = tail = newNode;
		else{
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
		size++;
	}

	// Operation 3) pop_front() → Remove from the front
	void pop_frontOrRemoveAtHead(){
		if (head == nullptr)
			return;

		const Node* temp = head;

		if (head == tail)
			head = tail = nullptr;
		else{
			head = head->next;
			head->prev = nullptr;
		}

		delete temp;
		size--;
	}

	// Operation 4) pop_back() → Remove from the last
	void pop_backOrRemoveAtTail(){
		if (head != nullptr)
			return;

		const Node* temp = tail;

		if (head == tail){
			delete tail;
			head = tail = nullptr;
		}else{
			tail = tail->prev;
			tail->next = nullptr;
		}

		delete temp;
		size--;
	}

	// Operation 5) insert_at_position() → Insert at a specific position
	void insertAtIndex(const int val, const int pos){
		if (pos < 0 || pos > size)
			return;

		if (pos == 0){
			push_frontOrAddAtHead(val);
			return;
		}

		if (pos == size){
			push_backOrAddAtTail(val);
			return;
		}

		// SLL: I need the node BEFORE pos → pos - 1
		// DLL: I can reach pos and go BACK using prev → pos
		Node* temp = head;
		for (int i = 0; i < pos; i++)
			temp = temp->next;

		// Node before temp
		Node* previous = temp->prev;
		// Create new node
		Node* newNode = new Node(val);

		// Connect new node
		newNode->prev = previous; // connect new node to previous node
		newNode->next = temp; // connect new node to next node

		// Connect surrounding nodes
		previous->next = newNode; // connect previous node to new node
		temp->prev = newNode; // connect next node to new node

		size++;
	}
	// Operation 6) delete_at_position() → Delete at a specific position
	void deleteAtIndex(const int pos){
		if (pos < 0 || pos >= size)
			return;

		// delete head
		if (pos == 0){
			pop_frontOrRemoveAtHead();
			return;
		}

		// delete tail
		if (pos == size - 1){
			pop_backOrRemoveAtTail();
			return;
		}

		// delete middle node
		const Node* temp = head;
		for (int i = 0; i < pos; i++)
			temp = temp->next;

		// create two pointers to connect the previous and next nodes
		Node* previous = temp->prev; // get the previous node
		Node* next = temp->next; // get the next node

		previous->next = next; // connect previous node to next node n1->n2
		next->prev = previous; // connect next node to previous node n1<-n2

		delete temp; // delete the node at position pos than n1<-n2
		size--;
	}
	// Operation 7) search() → Search for a value
	// Basic implementation of search function in doubly linked list
	int getElementAtIndex(const int pos){
		if (pos < 0 | pos >= size)
			return -1;

		const Node* temp = head;
		for (int i = 0; i < pos; i++)
			temp = temp->next;

		return temp->data;
	}

	// Operation 7) Get Element at Index
	// DLL Can Search From Both Directions
	int getElementAtIndexBothDirection(const int pos){
		if (pos < 0 || pos >= size)
			return -1;

		Node* temp;
		if (pos < size / 2){
			temp = head;
			for (int i = 0; i < pos; i++)
				temp = temp->next;
		} else{
			temp = tail;
			for (auto i = size - 1; i > pos; i--)
				temp = temp->prev;
		}

		return temp->data;
	}

	// Operation 8) search() → Search target value in the list and return index
	int serach(const int key){
		Node* temp = head;
		int idx = 0;
		while (temp != nullptr){
			if (temp->data == key)
				return idx;

			temp = temp->next;
			idx++;
		}
		return -1; // not found
	}

	// Operation 9) print() → Print the entire list
	// Forwards Traversal of Doubly Linked List
	void printForwards(){
		if (head == nullptr)
			return;

		Node* temp = head;
		while (temp != nullptr){
			cout << temp->data << " <-> ";
			temp = temp->next;
		}
		cout << "NULL\n";
	}

	// Operation 9) print() → Print the entire list
	// Backwards Traversal of Doubly Linked List
	void printReverse(){
		if (tail == nullptr)
			return;

		Node* temp = tail;
		while (temp != nullptr){
			cout << temp->data << " <-> ";
			temp = temp->prev;
		}
		cout << "NULL\n";
	}

	// Get Size of the List
	size_t getSize() {
		return size;
	}

	// Delete the entire linked list
	void clear(){
		Node* temp = head;
		while (temp != nullptr){
			Node* nextNode = temp->next;
			delete temp;
			temp = nextNode;
		}
		head = tail = nullptr;
		size = 0;
	}

	// Deconstructor to free memory when the list is destroyed
	~doublyLinkedList(){
		clear();
	}

};
void solve(){
	doublyLinkedList dll;

	int choice, val, pos;

	while (true){
		cout << "\n--- Doubly Linked List Operations ---\n";
		cout << "1. Push Front\n";
		cout << "2. Push Back\n";
		cout << "3. Pop Front\n";
		cout << "4. Pop Back\n";
		cout << "5. Insert at Index\n";
		cout << "6. Delete at Index\n";
		cout << "7. Get Element at Index\n";
		cout << "8. Search\n";
		cout << "9. Print Forward\n";
		cout << "10. Print Reverse\n";
		cout << "11. Get Size of the List\n";
		cout << "12. Clear the List\n";
		cout << "11. Exit\n";
		cout << "Enter choice: ";

		if (!(cin >> choice))
			break;

		switch (choice){
			case 1:
				cout << "Enter value: ";
				cin >> val;
				dll.push_frontOrAddAtHead(val);
				break;
			case 2:
				cout << "Enter value: ";
				cin >> val;
				dll.push_backOrAddAtTail(val);
				break;
			case 3:
				dll.pop_frontOrRemoveAtHead();
				break;
			case 4:
				dll.pop_backOrRemoveAtTail();
				break;
			case 5:
				cout << "Enter value and index: ";
				cin >> val >> pos;
				dll.insertAtIndex(val, pos);
				break;
			case 6:
				cout << "Enter index to delete: ";
				cin >> pos;
				dll.deleteAtIndex(pos);
				break;
			case 7:
				cout << "Enter index to get element: ";
				cin >> val;
				pos = dll.getElementAtIndexBothDirection(val);
				if (pos != -1)
					cout << "Value found at index: " << pos << "\n";
				else
					cout << "Value not found.\n";
				break;
			case 8:
				cout << "Enter value to search: ";
				cin >> val;
				pos = dll.serach(val);
				if (pos != -1)
					cout << "Value found at index: " << pos << "\n";
				else
					cout << "Value not found.\n";
				break;
			case 9:
				dll.printForwards();
				break;
			case 10:
				dll.printReverse();
				break;
			case 11:
				cout << "Size of the list: " << dll.getSize() << "\n";
				break;
			case 12:
				dll.clear();
				cout << "List cleared.\n";
				break;
			case 13:
				return; // Exit the program
			default:
				cout << "Invalid choice! Please try again.\n";
		}
	}
}


int main(){
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
