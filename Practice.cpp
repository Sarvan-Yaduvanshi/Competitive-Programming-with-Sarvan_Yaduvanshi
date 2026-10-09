#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class myLinkedList{
protected:
	struct Node{
		int val;
		Node* prev;
		Node* next;
		Node(const int val) : val(val), prev(nullptr), next(nullptr) {}
	};

	Node* head;
	Node* tail;
	size_t size;

public:
	myLinkedList() : head(nullptr), tail(nullptr), size(0) {}

	void push_front(const int val){
		Node* newNode = new Node(val);
		if (head == nullptr)
			head = tail = newNode;
		else{
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}
		size++;
	}

	void push_back(const int val){
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

	void pop_front(){
		if (head == nullptr)
			return;

		Node* temp = head;
		if (head == tail)
			head = tail = nullptr;
		else{
			head = head->next;
			head->prev = nullptr;
		}

		delete temp;
		size--;
	}

	void pop_back(){
		if (head == nullptr)
			return;

		Node* temp = tail;
		if (head == tail){
			delete tail;
			head = tail = nullptr;
		} else{
			tail = tail->prev;
			tail->next = nullptr;
		}
		delete temp;
		size--;
	}

	void addAtPos(const int val, const int idx){
		if (idx < 0 || idx > size)
			return;
		Node* newNode = new Node(val);

		if (idx == 0){
			if (head == nullptr)
				head = tail = newNode;
			else{
				newNode->next = head;
				head->prev = newNode;
				head = newNode;
			}
			size++;
			return;
		}

		if (idx == size){
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
			size++;
			return;
		}

		Node* temp = head;
		for (int i = 0; i < idx; i++)
			temp = temp->next;

		Node* previous = temp->prev;

		newNode->next = temp;
		temp->prev = newNode;

		previous->next = newNode;
		newNode->prev = previous;
		size++;
	}

	void removeAtPos(const int idx){
		if (idx < 0 || idx >= size)
			return;

		Node* temp = head;
		if (idx == 0){
			head = head->next;
			if (head == nullptr)
				tail = nullptr;
			delete temp;
			size--;
			return;
		}

		if (idx == size - 1){
			while (temp->next != tail)
				temp = temp->next;
			delete tail;
			tail = temp;
			tail->next = nullptr;
			size--;
			return;
		}

		for (int i = 0; i < idx - 1; i++)
			temp = temp->next;

		Node* deleteNode = temp->next;
		temp->next = deleteNode->next;
		delete deleteNode;
		size--;
	}

	int searchIdx(const int tar){
		if (head == nullptr)
			return -1;

		if (head->val == tar)
			return 0;

		Node* temp = head;
		int idx = 0;
		while (temp != nullptr){
			if (temp->val == tar)
				return idx;
			idx++;
			temp = temp->next;
		}
		return -1;
	}

	size_t getSize(){
		return size;
	}

	bool empty(){
		return head == nullptr;
	}

	void printLL(){
		Node* temp = head;
		while (temp != nullptr){
			cout << temp->val << "->";
			temp = temp->next;
		}
		cout << "nullptr\n";
	}

	void deleteLL() {
		head = head->next;
		delete head;
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

