#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class myLinkedList{
private:
	struct Node{
		int data;
		Node* next;
		explicit Node(const int val) : data(val), next(nullptr) {}
	};

	Node* head;
	Node* tail;
	size_t sz;

public:
	myLinkedList() : head(nullptr), tail(nullptr), sz(0) {}

	void push_front(const int val){
		Node* newNode = new Node(val);

		if (head == nullptr)
			head = tail = newNode;
		else{
			newNode->next = head;
			head = newNode;
		}
		sz++;
	}

	void push_back(const int val){
		Node* newNode = new Node(val);

		if (head == nullptr)
			head = tail = nullptr;
		else{
			tail->next = newNode;
			tail = newNode;
		}
		sz++;
	}

	void addAtPos(const int val, const int pos){
		if (pos < 0 || pos > sz)
			return;

		Node* newNode = new Node(val);
		// Case 1: insert node at head
		if (pos == 0){
			newNode->next = head;
			head = newNode;
			sz++;
			return;
		}

		// Case 2: insert node at tail
		if (pos == sz){
			tail->next = newNode;
			tail = newNode;
			sz++;
			return;
		}

		// case 3: insert node at middle
		Node* curr = head;
		for (int i = 0; i < pos - 1; i++)
			curr = curr->next;

		curr->next = newNode; // after
		newNode->next = curr->next; // connect first

		sz++;
	}

	void pop_front(){
		if (head == nullptr)
			return;

		Node* temp = head;
		head = head->next;
		if (head == nullptr)
			tail = nullptr;
		delete temp;
		sz--;
	}

	void pop_back(){
		if (head == nullptr)
			return;

		// Case 1: only single node
		if (head->next == nullptr || head == tail){
			delete tail;
			head = tail = nullptr;
			sz--;
			return;
		} else{ // Case 2: if delete tail
			Node* prev = head;
			while (prev->next != tail)
				prev = prev->next;

			delete tail;
			tail = prev;
			tail->next = nullptr;
			sz--;
			return;
		}
	}

	void popAtPos(const int pos){
		if (head == nullptr || pos < 0 || pos > sz - 1)
			return;

		// Case 1: only single node remove head
		if (pos == 0){
			Node* prev = head;
			head = head->next;
			if (head == nullptr)
				tail = nullptr;
			delete prev;
			sz--;
			return;
		}

		// Case 2: remove node any pos include tail node
		// not handle pos == sz - 1 as separate because this loop automatically handle
		Node* prev = head;
		for (int i = 0; i < pos - 1; i++)
			prev = prev->next;

		Node* deleteNode = prev->next;
		prev->next = deleteNode->next;

		delete deleteNode;
		sz--;
	}

	bool isEmpty(){
		return head == nullptr;
	}

	size_t getSize(){
		return sz;
	}

	void deleteNode(){
		Node* prev = head;
		head = head->next;
		delete prev;
	}

	int getIdx(const int val){
		if (head->data == val)
			return 0;

		Node* curr = head->next;
		int idx = 1;
		while (curr != nullptr){
			if (curr->data == val)
				return idx;
			idx++;
			curr = curr->next;
		}

		return -1;
	}

	int getNodeVal(const int pos){
		if (pos < 0)
			return -1;

		if (pos == 0)
			return head->data;

		Node* curr = head;
		for (int i = 0; i < pos - 1; i++)
			curr = curr->next;

		return curr->next->data;
	}

	Node* sortedOrder(const int val){
		Node* newNode = new Node(val);
		if (head == nullptr){
			newNode->next = head;
			head = newNode;
			return head;
		}
		if (val <= head->data){
			newNode->next = head;
			head = newNode;
			return head;
		} else{
			Node* curr = head->next;
			while (curr->next != nullptr && curr->next->data <= val){
				curr = curr->next;
			}

			newNode->next = curr->next;
			curr->next = newNode;
		}

		return head;

	}
};


static void solve(){
	myLinkedList ll;

	ll.push_front(2);
	ll.push_back(3);
	ll.push_back(4);
	ll.push_back(5);
	ll.push_back(6);
	ll.push_front(1);
	ll.printLL();

	ll.pop_front();
	ll.pop_back();
	ll.printLL();

	ll.addAtPos(8, 2);
	ll.printLL();

	ll.removeAtPos(2);
	ll.printLL();

	ll.removeAtPos(0);
	ll.removeAtPos(2);
	ll.printLL();

	ll.deleteLL();
	ll.printLL();
}
int main(){
	solve();
}

