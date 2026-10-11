/*
Author: Sarvan Yaduvanshi
Created : 2026-10-02 20:22:43
*/

/*
 * Problem : Remove Linked List Elements(Leetcode 203)
 * Problem Statement:
 * Given the head of a linked list and an integer val,
 * remove all the nodes of the linked list that has Node.val == val,
 * and return the new head.
 *
 * Example 1:
 * Input: head = [1,2,6,3,4,5,6], val = 6
 * Output: [1,2,3,4,5]
 *
 * Example 2:
 * Input: head = [], val = 1
 * Output: []
 *
 * Example 3:
 * Input: head = [7,7,7,7], val = 7
 * Output: []
 *
 * Constraints:
 * The number of nodes in the list is in the range [0, 10^4].
 * 1 <= Node.val <= 50
 * 0 <= val <= 50
 */

#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
struct ListNode{
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(nullptr) {}
};

// Approach 1: Recursive Approach
// Time Complexity: O(n) where n is the number of nodes in the linked list
// Space Complexity: O(n) due to recursive call stack
static ListNode* removeElements(ListNode* head, const int val) {
	// Base Case
	if (head == nullptr)
		return nullptr;

	// Case 1: Delete head node
	if (head->val == val){
		ListNode* newHead = head->next;
		delete head;
		return removeElements(newHead, val);
	}

	// Case 2: delete any node
	head->next = removeElements(head->next, val);

	return head;
}

// Approach 2: Iterative Approach
// Time Complexity: O(n) where n is the number of nodes in the linked list
// Space Complexity: O(1) Because we are not using any extra space
ListNode* removeElementsOptimal(ListNode* head, int val){
	// safety check
	if (head == nullptr)
		return nullptr;

	// Case 1: Delete head node(s) multiple times if needed
	while (head != nullptr && head->val == val){
		ListNode* deleteHead = head;
		head = head->next;
		delete deleteHead;
	}

	// if head is nullptr after deleting head node(s)
	if (head == nullptr)
		return nullptr;

	// Case 2: Delete any node(s) in the linked list
	ListNode* temp = head;
	while (temp->next != nullptr){
		// if next node is target node, delete it
		if (temp->next->val == val){
			ListNode* deleteNode = temp->next; // store the node to be deleted
			temp->next = deleteNode->next; // link curr node to deleteNode's next node
			delete deleteNode; // delete the target node
		} else{ // if next node is not target node, move to next node
			temp = temp->next;
		}
	}

	return head;
}

// Build linked list from vector of values
ListNode* buildLinkedList(const vector<int>& values){
	int n = values.size();
	if (n == 0)
		return nullptr;

	ListNode* head = new ListNode(values[0]);
	ListNode* tail = head;
	for (int i = 1; i < n; ++i){
        tail->next = new ListNode(values[i]);
        tail = tail->next;
    }
	return head;
}

// Print linked list
void printLinkedList(ListNode* head){
	if (head == nullptr){
		cout << "Linked list is empty." << endl;
	}

	ListNode* temp = head;
	while (temp != nullptr){
		cout << temp->val << " -> ";
		temp = temp->next;
	}
	cout << "nullptr" << endl;
}

static void solve() {
    int n;
	cout << "Enter the number of nodes in the linked list: ";
	cin >> n;

	vector<int> values(n);
	cout << "Enter " << n << " values for the linked list: ";
	for (int i = 0; i < n; ++i){
		cin >> values[i];
	}

	int val;
	cout << "Enter the value to be removed: ";
	cin >> val;



	ListNode* head = buildLinkedList(values);
	 // removeElements(head, val);
	 removeElementsOptimal(head, val);

	cout << "Original linked list: ";
	printLinkedList(head);


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
