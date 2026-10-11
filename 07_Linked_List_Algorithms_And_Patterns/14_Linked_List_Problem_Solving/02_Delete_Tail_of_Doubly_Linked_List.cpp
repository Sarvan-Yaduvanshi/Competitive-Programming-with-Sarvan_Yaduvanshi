/*
Author: Sarvan Yaduvanshi
Created : 2026-10-10 19:15:19
*/

/*
 * Problem: Delete Tail of Doubly Linked List
 * Given the head of a doubly linked list,
 * remove the node at the tail of the linked list and return the head of the modified list.
 * The tail is the last node of the linked list.
 *
 * Example 1:
 * Input: head = [1,2,3]
 * Output: [1,2]
 *
 * Example 2:
 * Input: head = [1]
 * Output: []
 *
 * Constraints:
 *		n == Number of nodes in the linked list
 *		1 <= n <= 100
 *		0 <= ListNode.val <= 100
 */

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class MyLinkedList{
private:
	struct Node{
		int val;
        Node* prev;
        Node* next;
		explicit Node(const int val) : val(val), prev(nullptr), next(nullptr) {}
    };

	Node* head;

public:
	MyLinkedList() : head(nullptr) {}

	// Function to delete the tail of the doubly linked list
	// Time O(n) | Space O(1)
	static Node* deleteTail(Node *&head){
		if (head == nullptr)
			return nullptr;

		// If there's only one node in the list
		if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return nullptr;
        }

		// Traverse to the second last node
		Node* curr = head;
		while (curr->next != nullptr)
			curr = curr->next;

		Node* prev = curr->prev;
		delete curr;
		prev->next = nullptr;

		return head;
	}

	// Build a linked list from an array of values
	static Node* buildList(const int arr[], const int n) {
        if (n <= 0)
        	return nullptr;

        Node* head = new Node(arr[0]);
        Node* curr = head;
        for (int i = 1; i < n; ++i) {
            curr->next = new Node(arr[i]);
            curr->next->prev = curr;
            curr = curr->next;
        }
        return head;
    }

	// Function to print the linked list
	static void printList(Node* head){
		Node* curr = head;
        while (curr != nullptr) {
            cout << curr->val << " -> ";
            curr = curr->next;
        }
        cout << "nullptr" << endl;
	}
};

constexpr int MAX = 100;
static int arr[MAX];
static void solve(){
	int n; cin >> n;
	for (int i = 0; i < n; i++)
        cin >> arr[i];

	auto head = MyLinkedList::buildList(arr, n);
	cout << "Original List: ";
	MyLinkedList::printList(head);

	head = MyLinkedList::deleteTail(head);
	cout << "After Deleting Tail: ";
	MyLinkedList::printList(head);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}
