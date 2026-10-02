/*
Author: Sarvan Yaduvanshi
Created : 2026-09-29 14:42:59
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>
using namespace std;

/*
 *  <--------------------- CIRCULAR SINGLY LINKED LIST -------------------->
 *
 *  Built Circular Singly Linked List with the following operations:
 *      1. push_front(int val)  → Insert at the front
 *      2. push_back(int val)   → Insert at the back
 *      3. pop_front()           → Remove from the front
 *      4. pop_back()            → Remove from the back
 *      5. insert_at_position(int val, int pos) → Insert at a specific position
 *      6. delete_at_position(int pos) → Delete at a specific position
 *      7. search(int key)       → Search for a value
 *      8. print()                → Print the entire list
 *
 *      For example, the list will look like:
 *           start as empty: NULL
 *           operations:
 *              push_back(10): 10 -> (points back to 10)
 *              push_back(20): 10 -> 20 -> (points back to 10)
 *              push_front(5): 5 -> 10 -> 20 -> (points back to 5)
 *              insert_at_position(15, 2): 5 -> 10 -> 15 -> 20 -> (points back to 5)
 *              delete_at_position(1): 5 -> 15 -> 20 -> (points back to 5)
 *              search(15): returns index 1
 *              print(head): 5 -> 15 -> 20 -> (points back to 5)
*/

class MyCircularSinglyLinkedList{
protected:
	struct Node{
		int data;
		Node* next;
		Node(const int val) : data(val), next(nullptr) {}
	};

	Node* tail;
	size_t size;

public:
	// Constructor: initializes tail to nullptr and size to 0
	MyCircularSinglyLinkedList() : tail(nullptr), size(0) {}

	// Destructor: cleans up all nodes to prevent memory leaks
	~MyCircularSinglyLinkedList(){
		clear();
	}

	// checks if the list is empty
	bool isEmpty() const{
		return tail == nullptr;
	}

	// Returns the size of the list
	size_t getSize() const{
		return size;
	}

	// return front node's value
	int getFront() const{
		if (isEmpty()){
			throw runtime_error("List is empty.");
		}
		return tail->next->data; // front node is tail->next
	}

	// return back node's value
	int getBack() const{
		if (isEmpty()){
			throw runtime_error("List is empty.");
		}
		return tail->data; // back node is tail
	}

	// print the entire list
	void print() const{
		if (isEmpty()){
			cout << "List is empty.\n";
			return;
		}

		Node* head = tail->next;
		Node* temp = head;

		do{
			cout << temp->data << "->";
			temp = temp->next;
		} while (temp != head);
		cout << "nullptr\n";
	}

	// Insert a new node at the head of the list (front)
	void AddAtHead(const int val){
		Node* newNode = new Node(val);

		if (tail == nullptr){
			newNode->next = newNode; // points to itself
			tail = newNode; // update tail to new node
			size++; // increment size
			return;
		} else{
			newNode->next = tail->next; // new node points to head
			tail->next = newNode; // tail points to new node (new head)
		}
		siz++;
	}

	// Insert a new node at the tail of the list (back)
	void AddAtTail(const int val){
		Node* newNode = new Node(val);

		if (tail == nullptr){
			newNode->next = newNode; // points to itself
			tail = newNode; // update tail to new node
			size++;
			return;
		}  else{
			newNode->next = tail->next; // new node points to head
			tail->next = newNode; // old tail points to new node
			tail = newNode; // new node becomes the new tail
		}
		size++;
	}

	// Pop_front: Remove the node at the head of the list
	void pop_front(){
		if (tail == nullptr)
			return;

		Node* head = tail->next;
		// If there's only one node, delete it and set tail to nullptr
		if (head == tail){
			delete head;
			tail = nullptr;
			size = 0;
			return;
		}

		// More than one node: update tali->next becomes head->next, then delete head
		tail->next = head->next;
		delete head;
		size--;
	}

	// Pop_back: Remove the node at the tail of the list
	void pop_back(){
		if (tail == nullptr)
			return;

		// If there's only one node, delete it and set tail to nullptr
		if (tail->next == tail){
			delete tail;
			tail = nullptr;
			size = 0;
			return;
		}

		// More than one node: Find node before tail
		Node* temp = tail->next;
		while (temp->next != nullptr)
			temp = temp->next;

		// Connect previous node to head
		temp->next = tail->next;
		delete tail; // Delete the old tail
		// Previous node becomes new tail
		tail = temp;
		size--;
	}

	// Insert a new node at a specific position (0-based index)
	void insert_at_position(const int val, const int pos){
		if (pos < 0 || pos > size)
			return;

		// single node add at head
		if (pos == 0){
			AddAtHead(val);
			return;
		}

		// single node add at tail
		if (pos == size){
			AddAtTail(val);
			return;
		}

		// before inserting find the node at position pos-1
		Node* temp = tail->next;
		for (int i = 0; i < pos - 1; i++)
			temp = temp->next;

		Node* newNode = new Node(val);
		newNode->next = temp->next; // new node points to the next node
		temp->next = newNode; // previous node points to new node
		size++;
	}

	// Delete a node at a specific position (0-based index)
	void delete_at_position(const int pos){
		if (tail == nullptr || pos < 0 || pos >= size)
			return;

		if (pos == 0){
			pop_front();
			return;
		}

		if (pos == size - 1){
			pop_back();
			return;
		}

		Node* temp = tail->next;
		for (int i = 0; i < pos - 1; i++)
			temp = temp->next;

		Node* deleteNode = temp->next;
		temp->next = deleteNode->next;
		delete deleteNode;
		size--;
	}

	// Search for a value
	bool search(const int key) const{
		if (tail == nullptr)
			return false;

		Node* temp = tail->next;
		do{
			if (temp->data == key)
				return true;
			temp = temp->next;
		} while (temp != tail->next);

		return false;
	}

	// Remove first occurrence of a value
	bool removeFirstOccurrence(const int key){
		if (tail == nullptr)
			return false;

		Node* head = tail->next;
		Node* prev = tail;
		Node* curr = head;

		// Traverse the list to find the key
		do{
			if (curr->data == key){
				// If the node to be deleted is the head
				if (curr == head){
					pop_front();
				} else if (curr == tail){ // If the node to be deleted is the tail
					pop_back();
				} else { // If the node to be deleted is in the middle
					prev->next = curr->next;
					delete curr;
					size--;
				}
				return true; // key found and deleted
			}
			prev = curr;
			curr = curr->next;
		} while (curr != head);

		return false; // not found
	}

	// Reverse the circular singly linked list
	void reverse(){
		if (tail == nullptr || tail->next == tail)
			return; // empty or single node list

		Node* oldHead = tail->next;
		Node* prev = tail;
		Node* curr = oldHead;

		do{
			Node* nextNode = curr->next;
			curr->next = prev; // reverse the link
			prev = curr;
			curr = nextNode;
		} while (curr != oldHead);

		// Update tail to the old head, which is now the new tail
		tail = oldHead;
	}

	// Clear the entire list
	void clear(){
		if (tail == nullptr)
			return;

		Node* head = tail->next;

		// Break circular connection to avoid infinite loop during deletion
		tail->next = nullptr;

		Node* temp = head;
		while (temp != nullptr){
			Node* nextNode = temp->next;
			delete temp;
			temp = nextNode;
		}

		tail = nullptr;
		size = 0;
	}
};
static void solve(){
	
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
