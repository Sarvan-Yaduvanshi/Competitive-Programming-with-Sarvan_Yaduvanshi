#include <iostream>
using namespace std;

// Build Singly linked list

class MyLinkedList{
protected:
	struct Node{
		int data;
		Node* next;
		Node(int val) : data(val), next(nullptr) {}
	};

	Node* head;
	Node* tail;
	size_t size;

public:
	MyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

	// Operation 1) push_front() -> insert node as front
	void push_frontOrAddAtHead(int val){
		Node* newNode = new Node(val);

		if (head == nullptr)
			head = tail = newNode;
		else{
			newNode->next = head;
			head = newNode;
		}

		size++;
	}

	// Operation 2) push_back() -> insert node as back
	void push_backOrAddAtTail(int val){
		Node* newNode = new Node(val);

		if (head == nullptr)
			head = tail = newNode;
		else{
			tail->next = newNode;
			tail = newNode;
		}

		size++;
	}

	// Operation 3) pop_front() or remove node as head
	void pop_frontOrRemoveAtHead(){
		if (head == nullptr)
			return;

		Node* temp = head;
		head = head->next;

		if (head == nullptr)
			tail = nullptr;

		delete temp;
		size--;
	}

	// Operation 4) pop_back() or remove node as tail
	void pop_backOrRemoveAtTail(){
		if (head == nullptr)
			return;

		if (head == tail){
			delete tail;
			head = tail = nullptr;
		} else{
			Node* temp = head;
			while (temp->next != nullptr)
				temp = temp->next;

			delete tail;
			tail = temp;
			tail->next = nullptr;
		}
	}

	void inertAtPosition(const int val, const int pos){
		if (pos < 0 || pos > size)
			return;

		if (pos == 1){
			push_frontOrAddAtHead(val);
			return;
		}

		if (pos == size){
			push_backOrAddAtTail(val);
			return;
		}

		Node* temp = head;
		for (int i = 0; i < pos - 1; i++){
			temp = temp->next;
		}

		Node* newNode = new Node(val);
		newNode->next = temp->next;
		temp->next = newNode;
		size++;
	}

	int search(int val, int pos){
		if (head == nullptr){
			return -1;
		}

		if
	}
};


static void solve(){


}

int main(){
	solve();
}