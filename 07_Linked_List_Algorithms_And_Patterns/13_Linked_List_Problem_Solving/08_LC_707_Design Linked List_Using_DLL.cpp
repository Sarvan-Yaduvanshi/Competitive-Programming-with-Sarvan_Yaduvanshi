/*
Author: Sarvan Yaduvanshi
Created : 2026-09-29 15:33:21
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

// Approach 2: Design Linked List using Doubly Linked List (Optimal)
class MyDoublyLinkedList {
protected:
	struct Node{
		int data;
		Node* prev;
		Node* next;
		Node(const int val) : data(val), prev(nullptr), next(nullptr) {}
	};

	Node* head;
	Node* tail;
	size_t size;

public:
	MyDoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

	int get(const int idx){
		if (idx < 0 || idx >= size)
			return -1;

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

	void addAtHead(int val){
		Node* newNode = new Node(val);
		if (head == nullptr){
			head = tail = newNode;
		} else{
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}
		size++;
	}

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

	void printLL(){
		const Node* temp = head;
		while (temp != nullptr){
			cout << temp->data << "->";
			temp = temp->next;
		}

		cout << "nullptr\n";
	}
};
void solve(){
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

	cout << fixed << setprecision(10);

	// Multi-test case support (commented out for this demo)
	// int TC = 1;
	// cin >> TC;
	// while (TC--) solve();

	solve();
	return 0;
}
