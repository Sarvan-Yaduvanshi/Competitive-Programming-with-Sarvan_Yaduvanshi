#include <iostream>
using namespace std;

struct Node {
	int data;
	Node* next;

	// constructor initialize
	Node(const int val) : data(val), next(nullptr) {}
};

static void solve(){
	// Step 1: Create a new node
	Node* a = new Node(10);
	Node* b = new Node(20);
	Node* c = new Node(30);

	// Step 2: linked node each other
	a->next = b;
	b->next = c;

	// point head = a
	Node* head = a;
	Node* temp = head;
	while (temp != nullptr){
		cout << temp->data << "->";
		temp = temp->next;
	}
	cout << "NULL\n";

	temp = head;
	while (temp != nullptr){
		cout << "Node(" << temp->data << ") at address: " << temp
		<< ", next points to: " << temp->next << "\n";

		temp = temp->next;
	}

	delete a;
	delete b;
	delete c;
}
int main(){
	solve();

	return 0;
}