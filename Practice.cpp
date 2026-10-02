#include <iostream>
using namespace std;

class myLinkedList{
protected:
	struct Node{
		int data;
		Node* next;
		Node(const int val) : data(val), next(nullptr) {}
	};

	Node* head;
	Node* tail;
	size_t size;

public:
	myLinkedList() : head(nullptr), tail(nullptr), size(0) {}

	// Oper 1) push_front
	void push_front(const int val){
		Node* newNode = new Node(val);
		if (head == nullptr)
			head = tail = newNode;
		else{
			newNode->next = head;
			head = newNode;
		}

		size++;
	}

	// Oper 2) push_back
	void push_back(const int val){
		Node* newNode = new Node(val);
		if (head == nullptr)
			head = tail = newNode;
		else{
			tail->next = newNode;
			tail = newNode;
		}

		size++;
	}

	// Oper 3) pop_front()
	void pop_front(){
		if (head == nullptr)
			return;

		Node* temp = head;
		head = head->next;

		if (head == nullptr)
			tail = nullptr;

		delete temp;
		size--;
	}

	// Oper 4) pop_back()
	void pop_back(){
		if (head == nullptr)
			return;

		/
	}
};


static void solve(){


}

int main(){
	solve();
}