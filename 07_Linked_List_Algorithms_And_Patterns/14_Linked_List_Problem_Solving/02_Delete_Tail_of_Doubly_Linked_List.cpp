/*
Author: Sarvan Yaduvanshi
Created : 2026-10-10 19:15:19
*/

/*
 * Problem: Delete Kth Element of Doubly Linked List
 * Given the head of a doubly linked list and an integer k,
 * remove the node at the kth position of the linked list and return the head of the modified list.
 *
 * Example 1:
 * Input: head = [2,5,7,9], k = 2
 * Output: head = [2,7,9]
 * Explanation: The node with value 5 was removed.
 *
 * Example 2:
 * Input: head = [2,5,7], k = 1
 * Output: head = [5,7]
 * Explanation: The node with value 2 was removed.
 *
 * Constraints:
 *		n == Number of nodes in the linked list
 *		1 <= n <= 100
 *		0 <= ListNode.val <= 100
 *		1 <= k <= n
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
	static Node* deleteTail(Node *&head, const int k){
		if (head == nullptr || k < 0)
			return nullptr;

		// Case 1: If the list has only one node
		if (k == 1){
			const Node* temp = head;
			head = head->next;
			if (head != nullptr)
				head->prev = nullptr;
			delete temp;
			return head;
		}

		// Case 2: If the list has more than one node
		const Node* curr = head;
		for (int i = 1; i < k; i++)
			curr = curr->next;

		// if the kth node is nullptr, return head (k is out of bounds)
		if (curr == nullptr)
			return head;

		Node* nextNode = curr->next;
		Node* prevNode = curr->prev;

		if (prevNode != nullptr)
			prevNode->next = nextNode;
		if (nextNode != nullptr)
			nextNode->prev = prevNode;

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
	int n, k; cin >> n >> k;
	for (int i = 0; i < n; i++)
        cin >> arr[i];

	auto head = MyLinkedList::buildList(arr, n);
	cout << "Original List: ";
	MyLinkedList::printList(head);

	head = MyLinkedList::deleteTail(head, k);
	cout << "After Deleting kth position tail: ";
	MyLinkedList::printList(head);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}
