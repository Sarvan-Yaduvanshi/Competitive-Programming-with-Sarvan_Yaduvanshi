/*
Author: Sarvan Yaduvanshi
Created : 2026-10-23 07:58:20
*/

/*
 * ============================================================================
 *  19. Remove Nth Node From End of List
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 19
 *  Difficulty : Medium
 *  Topics     : Linked List, Two Pointers
 *  Companies  : Amazon, Meta, Microsoft, Google, Apple, Bloomberg
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the head of a linked list, remove the nth node from the end of the
 *  list and return its head.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      1 -> 2 -> 3 -> 4 -> 5          1 -> 2 -> 3 -> 5
 *                     ^ remove
 *
 *  Input  : head = [1,2,3,4,5], n = 2
 *  Output : [1,2,3,5]
 *  Explanation: The 2nd node from the end is 4. After removing it, the list
 *               becomes [1,2,3,5].
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *  Input  : head = [1], n = 1
 *  Output : []
 *  Explanation: The only node is the 1st from the end. Removing it leaves an
 *               empty list.
 *
 * ----------------------------------------------------------------------------
 *  Example 3:
 *
 *  Input  : head = [1,2], n = 1
 *  Output : [1]
 *  Explanation: The 1st node from the end is 2. After removing it, the list
 *               becomes [1].
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in the list is sz.
 *      - 1 <= sz <= 30
 *      - 0 <= Node.val <= 100
 *      - 1 <= n <= sz
 *
 * ----------------------------------------------------------------------------
 *  Follow up: Could you do this in one pass?
 * ============================================================================
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
	 * Approach 1: One-pass algorithm
	 * Idea: Use two pointers, slow and fast. Move the fast pointer n steps ahead,
	 *       then move both pointers until the fast pointer reaches the end.
	 *       The slow pointer will be at the (n+1)th node from the end, allowing us
	 *       to remove the nth node from the end.
	 * Time Complexity: O(N) where N is the number of nodes in the linked list.
	 * Space Complexity: O(1)
	 */
	static ListNode* removeNthFromEnd(ListNode* head, const int n) {
		// Handle edge cases where the list is empty or n is non-positive
		if (head == nullptr || n <= 0)
			return head;

		ListNode dummy(0);
		dummy.next = head;

		// Both slow and fast pointers start at the dummy node
		ListNode* slow = &dummy;
		ListNode* fast = &dummy;

		// Step 1: Move the fast pointer n steps ahead
		for (int i = 1; i <= n; i++)
			fast = fast->next;

		// Step 2: Move both pointers until fast reaches the end
		while (fast != nullptr && fast->next != nullptr){
			slow = slow->next;
			fast = fast->next;
		}

		// Step 3: Remove the nth node from the end
		ListNode* nth_node_delete = slow->next;

		// if nth_node_delete is nullptr, it means n is greater than the length of the list
		if (nth_node_delete == nullptr)
			return dummy.next;

		// Update the next pointer of the slow node to skip the nth node
		slow->next = nth_node_delete->next;
		delete nth_node_delete;

		// return the new head
		return dummy.next;
	}

	// Approach 2: Two-pass algorithm
	// Idea: Step 1: Calculate the length of the linked list.
	//       Step 2: Find the (length - n)th node and remove the next node.
	// Time Complexity: O(N) where N is the number of nodes in the linked list.
	// Space Complexity: O(1)
	static ListNode* removeNthFromEndTwoPass(ListNode* head, const int n){
		// Handle edge cases where the list is empty or n is non-positive
		if (head == nullptr || n <= 0)
			return head;

		// Step 1: Calculate the length of the linked list
		int length = 0;
		ListNode* current = head;
		while (current != nullptr){
			length++;
			current = current->next;
		}

		// Step 2: Find the (length - n)th node and remove the next node
		int target = length - n;
		if (target < 0) // n is greater than the length of the list
			return head;

		ListNode dummy(0);
		dummy.next = head;

		// Step 3: Move to the (length - n)th node
		ListNode* prev = &dummy;
		for (int i = 0; i < target; i++)
			prev = prev->next;

		// Step 4: Remove the nth node from the end
		ListNode* nth_node_delete = prev->next;
		if (nth_node_delete != nullptr)
			prev->next = nth_node_delete->next;

		delete nth_node_delete;  // Free the memory of the removed node

		// Step 5: Return the new head
		return dummy.next;
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

	int remove_n;
	cout << "Enter the position of the node to remove from the end (n): ";
	cin >> remove_n;

	cout << "Enter the values of the nodes: ";
	vector<int> a(n);
	for (int& x : a)
		cin >> x;

	auto* head = MyLinkedList::buildList(a);
	cout << "Original Linked List: ";
	MyLinkedList::printList(head);

	// Method 1: One-pass algorithm
	auto* new_head_one_pass = MyLinkedList::removeNthFromEnd(head, remove_n);
	cout << "Linked List after removing the " << remove_n << "th node from the end (One-pass): ";
	MyLinkedList::printList(new_head_one_pass);

	// Reset the list for the second method
	head = MyLinkedList::buildList(a);

	// Method 2: Two-pass algorithm
	auto* new_head_two_pass = MyLinkedList::removeNthFromEndTwoPass(head, remove_n);
	cout << "Linked List after removing the " << remove_n << "th node from the end (Two-pass): ";
	MyLinkedList::printList(new_head_two_pass);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}