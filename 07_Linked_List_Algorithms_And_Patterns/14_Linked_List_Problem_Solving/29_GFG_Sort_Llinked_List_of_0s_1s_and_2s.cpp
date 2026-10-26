/*
Author: Sarvan Yaduvanshi
Created : 2026-10-26 03:14:50
*/

/*
 * ============================================================================
 *  Sort Linked List of 0s, 1s and 2s
 * ============================================================================
 *  Platform   : GeeksforGeeks
 *  Problem No : N/A (GFG has no number)
 *  Difficulty : Medium
 *  Topics     : Linked List, Sorting, Data Structures
 *  Companies  : Amazon, Microsoft, Adobe, Flipkart, Samsung, Snapdeal
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given a linked list where nodes can contain values 0s, 1s, and 2s only.
 *  Your task is to rearrange the list so that all 0s appear at the
 *  beginning, followed by all 1s, and all 2s are placed at the end.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      Before :  1 -> 2 -> 2 -> 1 -> 2 -> 0 -> 2 -> 2
 *      After  :  0 -> 1 -> 1 -> 2 -> 2 -> 2 -> 2 -> 2
 *                (0s)  (1s)   (2s)
 *
 *  Input  : head = 1 -> 2 -> 2 -> 1 -> 2 -> 0 -> 2 -> 2
 *  Output : 0 -> 1 -> 1 -> 2 -> 2 -> 2 -> 2 -> 2
 *  Explanation: All the 0s are segregated to the left end of the linked
 *               list, 2s to the right end of the list, and 1s in between.
 *               The final list will be:
 *               0 -> 1 -> 1 -> 2 -> 2 -> 2 -> 2 -> 2
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      Before :  2 -> 2 -> 0 -> 1
 *      After  :  0 -> 1 -> 2 -> 2
 *                (0s)  (1s)  (2s)
 *
 *  Input  : head = 2 -> 2 -> 0 -> 1
 *  Output : 0 -> 1 -> 2 -> 2
 *  Explanation: After arranging all the 0s, 1s and 2s in the given format,
 *               the output will be: 0 -> 1 -> 2 -> 2
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - 1 <= size of linked list <= 10^6
 *      - 0 <= node.data <= 2
 * ============================================================================
 */


#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <random>
#include <chrono>
using namespace std;

class MyLinkedList{
private:
	// Definition for singly-linked list.
	struct ListNode{
		int val;
		ListNode* next;
		explicit ListNode(const int val) : val(val), next(nullptr) {}
	};

	ListNode* head;

public:
	MyLinkedList() : head(nullptr) {}

	/*
	 * Approach: Three Stable Partitions
	 *
	 * Maintain separate chains for nodes containing 0, 1, and 2. Traverse the
	 * list once, append each node to its matching chain, then connect the
	 * chains in the order: zeros -> ones -> twos.
	 *
	 * Dry run:
	 *   Input:  1 -> 2 -> 0 -> 2 -> 1 -> 0
	 *
	 *   After traversal:
	 *     zeros: 0 -> 0
	 *     ones : 1 -> 1
	 *     twos : 2 -> 2
	 *
	 *   After connecting:
	 *     0 -> 0 -> 1 -> 1 -> 2 -> 2 -> nullptr
	 *
	 * Dummy nodes simplify the first insertion into each chain. The original
	 * nodes are reused, so no additional list nodes are created.
	 *
	 * Complexity:
	 *   Time: O(n), because every node is visited once.
	 *   Space: O(1) auxiliary space, excluding the three dummy nodes and
	 *          tail pointers.
	 */
	static ListNode* sortList(ListNode* head){
		// Dummy heads simplify construction of the three partitions.
		ListNode zerosDummy(0);
		ListNode onesDummy(0);
		ListNode twosDummy(0);

		// Tail pointers track the last node of each partition.
		ListNode* zerosTail = &zerosDummy;
		ListNode* onesTail = &onesDummy;
		ListNode* twosTail = &twosDummy;

		// Traverse the original list and partition the nodes.
		while (head != nullptr){
			// Save the next node before relinking the current node.
			ListNode* nextNode = head->next;

			// Case 1: Node value is 0, append to zeros chain.
			if (head->val == 0){
				// Append the node to the zero chain.
				zerosTail->next = head;
				zerosTail = zerosTail->next; // update zerosTail to new last node

			// Case 2: Node value is 1, append to ones chain.
			} else if (head->val == 1){
				// Append the node to the one chain.
				onesTail->next = head;
				onesTail = onesTail->next; // update onesTail to new last node

			// Case 3: Node value is 2, append to twos chain.
			} else if (head->val == 2){
				// Append the node to the two chain.
				twosTail->next = head;
				twosTail = twosTail->next; // update twosTail to new last node
			}

			// move to the next node in the original list
			head = nextNode;
		}

		// twosTail->next is already nullptr, but we can explicitly set it for clarity
		twosTail->next = nullptr;

		// Connect the three partitions order matters: first ones, then twos.
		// If onesDummy.next is nullptr, we connect zeros directly to twos.
		onesTail->next = twosDummy.next; // connect ones to twos
		zerosTail->next = onesDummy.next; // connect zeros to ones

		return zerosDummy.next; // return the head of the sorted list
	}

	// Test function to build a linked list from a vector of integers
	static ListNode* buildList(const vector<int>& a){
		if (a.empty())
			return nullptr;

		auto* head = new ListNode(a[0]);
		ListNode* tail = head;
		for (int i = 1; i < a.size(); i++){
			tail->next = new ListNode(a[i]);
			tail = tail->next;
		}

		return head;
	}

	// Test function to print the linked list
	static void printList(ListNode* head){
		if (head == nullptr){
			cout << "Empty List\n";
			return;
		}

		ListNode* current = head;
		while (current != nullptr){
			cout << current->val;
			if (current->next != nullptr)
				cout << " -> ";
			current = current->next;
		}
		cout << " -> nullptr\n";
	}
};


static void solve(){
	int n;
	cout << "Enter the number of nodes in the linked list: ";
	cin >> n;

	cout << "Enter the values of the nodes: ";
	vector<int> a(n);
	for (int& x : a)
		cin >> x;

	auto* head = MyLinkedList::buildList(a);
	cout << "Original Linked List: ";
	MyLinkedList::printList(head);

	// Sort the linked list of 0s, 1s, and 2s
	head = MyLinkedList::sortList(head);
	cout << "Sorted Linked List: ";
	MyLinkedList::printList(head);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}