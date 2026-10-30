/*
Author: Sarvan Yaduvanshi
Created : 2026-10-29 20:04:03
*/

/*
 * ============================================================================
 *  83. Remove Duplicates from Sorted List
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 83
 *  Difficulty : Easy
 *  Topics     : Linked List
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the head of a sorted linked list, delete all duplicates such that
 *  each element appears only once. Return the linked list sorted as well.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      Before :  1 -> 1 -> 2
 *      After  :  1 -> 2
 *
 *  Input  : head = [1,1,2]
 *  Output : [1,2]
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      Before :  1 -> 1 -> 2 -> 3 -> 3
 *      After  :  1 -> 2 -> 3
 *
 *  Input  : head = [1,1,2,3,3]
 *  Output : [1,2,3]
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in the list is in the range [0, 300].
 *      - -100 <= Node.val <= 100
 *      - The list is guaranteed to be sorted in ascending order.
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
 * ============================================================================
 * MATH & DELETION PATTERN 3A: 83. Remove Duplicates from Sorted List I
 * ============================================================================
 *
 * - Core Idea (Single Pointer Lookahead — No `dummy` Needed):
 *   Since we always keep the FIRST occurrence of every number, `head` never
 *   gets deleted. Walk `curr` from `head`:
 *     - If `curr->val == curr->next->val`:
 *         Unlink and `delete` `curr->next`.
 *         DO NOT advance `curr` yet (in case of 3+ duplicates like [1->1->1])!
 *     - Else:
 *         Advance `curr = curr->next`.
 *
 * - Quick Dry Run: head = [1 -> 1 -> 1 -> 2]
 *     Init   : curr = 1st [1]
 *     Step 1 : curr->val (1) == curr->next->val (1) -> delete 2nd [1].
 *              List: [1 -> 1 -> 2] (`curr` stays on 1st [1]!)
 *     Step 2 : curr->val (1) == curr->next->val (1) -> delete 3rd [1].
 *              List: [1 -> 2]      (`curr` stays on 1st [1]!)
 *     Step 3 : curr->val (1) != curr->next->val (2) -> advance `curr` to [2].
 *     End    : `curr->next == nullptr` -> Loop stops! Returns `[1 -> 2]`.
 *
 * - Complexity:
 *   Time  : O(N) — Every node is visited or deleted at most once.
 *   Space : O(1) — Pure in-place pointer manipulation.
 * ============================================================================
 */
	static  ListNode* deleteDuplicates(ListNode* head){
		// Edge Case: Empty List or Single Node List
		if (head == nullptr || head->next == nullptr)
			return head;

		// Initialize `curr` to the head of the list
		ListNode* curr = head;

		// Traverse the list until the end
		while (curr != nullptr && curr->next != nullptr){
			// Case 1: Duplicate found, remove the next node
			if (curr->val == curr->next->val){
				ListNode* duplicate = curr->next; // before deleting, store the duplicate node
				curr->next = duplicate->next; // unlink the duplicate node
				delete duplicate; // safely delete the duplicate node to free memory

			} else{ // Case 2: No duplicate, move to the next node
				curr = curr->next;
			}
		}

		return head;
	}

	/*
	 * ============================================================================
	 * RECURSION PATTERN: 83. Remove Duplicates from Sorted List
	 * ============================================================================
	 *
	 * - Core Idea (Solve the Suffix, Then Decide the Current Node):
	 *   Because the list is sorted, duplicates are adjacent. First recursively
	 *   remove duplicates from `head->next`. The recursive call returns the
	 *   cleaned suffix, which is attached back to `head->next`.
	 *
	 *   After the recursive call returns:
	 *   1. If `head->val == head->next->val`, the current node is a duplicate
	 *      of the first node in the cleaned suffix, so return `head->next`.
	 *      This skips the current node.
	 *   2. Otherwise, return `head` and keep the current node.
	 *
	 * - Dry Run: head = [1 -> 1 -> 2 -> 3 -> 3]
	 *   Expected result: [1 -> 2 -> 3]
	 *
	 *   Bind phase (calls go deeper):
	 *      D1(head=1a) -> D2(head=1b) -> D3(head=2)
	 *          -> D4(head=3a) -> D5(head=3b)
	 *      D5 reaches the base case (`head->next == nullptr`) and returns 3b.
	 *
	 *   Unbind phase (calls return):
	 *      1. D4 (3a):
	 *           `head->next` becomes 3b.
	 *           3a == 3b, so duplicate found.
	 *           Return 3b; 3a is skipped.
	 *           Cleaned suffix: [3b]
	 *
	 *      2. D3 (2):
	 *           `head->next` becomes 3b.
	 *           2 != 3, so return 2.
	 *           Cleaned suffix: [2 -> 3b]
	 *
	 *      3. D2 (1b):
	 *           `head->next` becomes 2.
	 *           1 == 2 is false, so return 1b.
	 *           Cleaned suffix: [1b -> 2 -> 3b]
	 *
	 *      4. D1 (1a):
	 *           `head->next` becomes 1b.
	 *           1 == 1 is true, so return 1b.
	 *           1a is skipped.
	 *           Final result: [1b -> 2 -> 3b] = [1 -> 2 -> 3]
	 *
	 *   The recursion does not explicitly delete duplicate nodes; it bypasses
	 *   them by returning the next node. The skipped nodes become unreachable.
	 *
	 * - Complexity:
	 *   Time  : O(N), because each node creates exactly one recursive call and
	 *           performs constant work while the call stack unwinds.
	 *   Space : O(N) auxiliary space for the recursion call stack.
	 *           No extra linked-list nodes are created.
	 * ============================================================================
	 */
	static ListNode* deleteDuplicatesUsingRecursive(ListNode* head){
		// Base Case: empty list or single node should be no duplicates
		if (head == nullptr || head->next == nullptr)
			return head;

		// Step 1: Recursively process the rest of the list
		head->next = deleteDuplicatesUsingRecursive(head->next);

		// Step 2: If the current node is a duplicate, skip it
		if (head->val == head->next->val)
			return head->next;

		// Step 3: Otherwise, keep the current node
		return head;
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

	cout << "Enter the sorted values of the nodes: ";
	vector<int> a(n);
	for (int& x : a)
		cin >> x;

	auto* head = MyLinkedList::buildList(a);
	cout << "Original Linked List: ";
	MyLinkedList::printList(head);

	// Remove duplicates
	head = MyLinkedList::deleteDuplicates(head);
	cout << "Linked List after removing duplicates: ";
	MyLinkedList::printList(head);

	// rebuild the list for recursive test
	head = MyLinkedList::buildList(a);

	// Approach 2: Using Recursion
	head = MyLinkedList::deleteDuplicatesUsingRecursive(head);
	cout << "Linked List after removing duplicates (Recursive): ";
	MyLinkedList::printList(head);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}