/*
Author: Sarvan Yaduvanshi
Created : 2026-10-29 20:25:59
*/

/*
 * ============================================================================
 *  82. Remove Duplicates from Sorted List II
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 82
 *  Difficulty : Medium
 *  Topics     : Linked List, Two Pointers
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  You are given the head of a sorted linked list.
 *
 *  Delete all nodes that have duplicate numbers, leaving only distinct
 *  numbers from the original list.
 *
 *  Return the linked list sorted as well.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      Before :  1 -> 2 -> 3 -> 3 -> 4 -> 4 -> 5
 *      After  :  1 -> 2 -> 5
 *                          (3s and 4s removed completely)
 *
 *  Input  : head = [1,2,3,3,4,4,5]
 *  Output : [1,2,5]
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      Before :  1 -> 1 -> 1 -> 2 -> 3
 *      After  :  2 -> 3
 *                (all 1s removed, head changes)
 *
 *  Input  : head = [1,1,1,2,3]
 *  Output : [2,3]
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
 * MATH & DELETION PATTERN 3B: 82. Remove Duplicates from Sorted List II
 * ============================================================================
 *
 * - Core Idea (`dummy` + Last-Unique Anchor `prev` + Inner Wipeout Loop):
 *   Since `head` itself can be a duplicate (Example 2), we MUST use `dummy`.
 *   Maintain `prev = &dummy` (the last node known to be 100% unique) and
 *   `curr = head` (the scout pointer inspecting the current value):
 *     - If `curr->next != nullptr && curr->val == curr->next->val`:
 *         Save `dupVal = curr->val`.
 *         Loop while `curr != nullptr && curr->val == dupVal`, deleting every
 *         copy of `dupVal` and advancing `curr`.
 *         Connect `prev->next = curr`! (Keep `prev` stationary until the new
 *         `curr` is verified to be unique on the next iteration!).
 *     - Else:
 *         `curr` is unique! Advance `prev = curr` and `curr = curr->next`.
 *
 * - Why `prev` Stays Stationary After Bridging Back-to-Back Duplicates:
 *   Consider [1 -> 3 -> 3 -> 4 -> 4 -> 5] with `prev = [1]`, `curr = 1st [3]`:
 *     - Inner loop wipes out both [3]s; `curr` lands on 1st [4].
 *     - We set `prev->next = curr` ([1]->next = 1st [4]).
 *     - If we moved `prev` to [4] right now, we'd keep [4] even though [4] is
 *       ALSO a duplicate! By keeping `prev` on [1], the next iteration checks
 *       [4] == [4], wipes out both [4]s, and links [1]->next = [5]!
 *
 * - Quick Dry Run: head = [1 -> 1 -> 2 -> 3 -> 3]
 *     Init   : dummy -> [1 -> 1 -> 2 -> 3 -> 3], prev = &dummy, curr = 1st [1]
 *     Step 1 : curr (1) == curr->next (1) -> `dupVal = 1`.
 *              Inner loop deletes both [1]s, `curr` lands on [2].
 *              `prev->next = [2]` (`dummy -> [2 -> 3 -> 3]`, `prev` stays at `dummy`).
 *     Step 2 : curr (2) != curr->next (3) -> [2] is unique!
 *              Advance `prev = [2]`, `curr = 1st [3]`.
 *     Step 3 : curr (3) == curr->next (3) -> `dupVal = 3`.
 *              Inner loop deletes both [3]s, `curr` lands on `nullptr`.
 *              `prev->next = nullptr` (`[2]->next = nullptr`).
 *     End    : `curr == nullptr` -> Loop stops! Returns `dummy.next` ([2]).
 *
 * - Complexity:
 *   Time  : O(N) — Each node is visited and/or deleted exactly once.
 *   Space : O(1) — Pure in-place pointer manipulation using 1 stack `dummy`.
 * ============================================================================
 */
	static  ListNode* deleteDuplicates(ListNode* head){
		// Handle edge cases: empty list or single node list
		if (head == nullptr || head->next == nullptr)
			return head;

		// Create a dummy node to handle edge cases where the head itself is a duplicate
		ListNode dummy(0);
		dummy.next = head;

		ListNode* prev = &dummy; // Always points to the last confirmed unique node
		ListNode* curr = head;  // Scout pointer inspecting the next group

		while (curr != nullptr){
			// Case 1: `curr` is the start of a duplicate block
			if (curr->next != nullptr && curr->val == curr->next->val){
				// Save the duplicate value to skip all its occurrences
				int duplicate = curr->val;

				// Skip all nodes with the duplicate value
				while (curr != nullptr && curr->val == duplicate){
					ListNode* temp = curr; // before deleting, store the current node
					curr = curr->next; // move to the next node
					delete temp; // free memory of the duplicate node
				}

				// Link the last unique node to the next unique node (or nullptr)
				prev->next = curr;
				// Note: `prev` does NOT move forward here because `curr` may still be a duplicate in the next iteration

			} else{ // Case 2: curr is confirmed unique -> move both pointers forward
				prev = curr;
				curr = curr->next;
			}
		}

		return dummy.next; // Return the new head, skipping the dummy node
	}

	static ListNode* deleteDuplicatesRecursive(ListNode* head){
		// Base case: if the list is empty or has only one node, return it as is
		if (head == nullptr || head->next == nullptr)
			return head;

		// Recursive case: if the current node is a duplicate, skip all duplicates
		auto skipAllDup = [&](auto&& self, ListNode* node, const int val) -> ListNode*{
			// Case 1: if curr node is nullptr or its value is not equal to the duplicate value, return it
			if (node == nullptr || node->val != val)
				return node;

			// Case 2: if curr node is a duplicate, skip it and continue recursively
			return self(self, node->next, val);
		};

		// If the current node is a duplicate, skip all duplicates and continue recursively
		if (head->val == head->next->val){
			int duplicate = head->val;
			return deleteDuplicatesRecursive(skipAllDup(skipAllDup, head, duplicate));
		}

		// If the current node is unique, keep it and continue recursively
		head->next = deleteDuplicatesRecursive(head->next);
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

	cout << "Enter the values of the nodes: ";
	vector<int> a(n);
	for (int& x : a)
		cin >> x;

	auto* head = MyLinkedList::buildList(a);
	cout << "Original Linked List: ";
	MyLinkedList::printList(head);

	// Call the iterative version of deleteDuplicates
	head = MyLinkedList::deleteDuplicates(head);
	cout << "Linked List after removing duplicates (Iterative): ";
	MyLinkedList::printList(head);

	// rebuild the list to avoid memory issues after deletion
	head = MyLinkedList::buildList(a);

	// Call the recursive version of deleteDuplicates
	head = MyLinkedList::deleteDuplicatesRecursive(head);
	cout << "Linked List after removing duplicates (Recursive): ";
	MyLinkedList::printList(head);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}