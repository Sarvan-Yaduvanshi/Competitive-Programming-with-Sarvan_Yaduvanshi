/*
Author: Sarvan Yaduvanshi
Created : 2026-10-27 19:27:04
*/

/*
 * ============================================================================
 *  147. Insertion Sort List
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 147
 *  Difficulty : Medium
 *  Topics     : Linked List, Sorting
 *  Companies  : Amazon, Microsoft, Google, Apple, Meta, Bloomberg, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the head of a singly linked list, sort the list using insertion
 *  sort, and return the sorted list's head.
 *
 *  The steps of the insertion sort algorithm:
 *
 *      1. Insertion sort iterates, consuming one input element each
 *         repetition and growing a sorted output list.
 *      2. At each iteration, insertion sort removes one element from the
 *         input data, finds the location it belongs within the sorted list
 *         and inserts it there.
 *      3. It repeats until no input elements remain.
 *
 *  The following is a graphical example of the insertion sort algorithm.
 *  The partially sorted list (black) initially contains only the first
 *  element in the list. One element (red) is removed from the input data
 *  and inserted in-place into the sorted list with each iteration.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      Start   :  [4] | 2 -> 1 -> 3        (sorted part | unsorted part)
 *      Step 1  :  [2 -> 4] | 1 -> 3        insert 2
 *      Step 2  :  [1 -> 2 -> 4] | 3        insert 1
 *      Step 3  :  [1 -> 2 -> 3 -> 4]       insert 3
 *
 *  Input  : head = [4,2,1,3]
 *  Output : [1,2,3,4]
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      Start   :  [-1] | 5 -> 3 -> 4 -> 0
 *      Step 1  :  [-1 -> 5] | 3 -> 4 -> 0        insert 5
 *      Step 2  :  [-1 -> 3 -> 5] | 4 -> 0        insert 3
 *      Step 3  :  [-1 -> 3 -> 4 -> 5] | 0        insert 4
 *      Step 4  :  [-1 -> 0 -> 3 -> 4 -> 5]       insert 0
 *
 *  Input  : head = [-1,5,3,4,0]
 *  Output : [-1,0,3,4,5]
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in the list is in the range [1, 5000].
 *      - -5000 <= Node.val <= 5000
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
 * MERGE & SORT PATTERN 5: 147. Insertion Sort List (O(N^2) Worst | O(N) Best)
 * ============================================================================
 *
 * - Core Idea (Separate `dummy` Sorted Builder + Cached `prev` Search Pointer):
 *   Start with an empty sorted list anchored at `ListNode dummy(INT_MIN)`
 *   (`dummy.next = nullptr`).
 *   Walk `curr` through the original list one node at a time:
 *     1. Save `nextCurr = curr->next` before modifying `curr->next`.
 *     2. Find the insertion spot `prev` inside the sorted `dummy` list such
 *        that `prev->val <= curr->val` and `prev->next->val > curr->val`.
 *     3. Splice `curr` right after `prev`:
 *          `curr->next = prev->next;`
 *          `prev->next = curr;`
 *     4. Advance `curr = nextCurr`.
 *
 * - GM Optimization (Why We Don't Reset `prev = &dummy` Every Time):
 *   If we reset `prev = &dummy` on every iteration, an already-sorted list
 *   [1 -> 2 -> 3 -> 4] still takes O(N^2) time!
 *   Instead, we only reset `prev = &dummy` IF `prev->val > curr->val`!
 *   If `curr->val >= prev->val`, `prev` stays where it was and walks forward,
 *   giving O(N) best-case time on sorted/nearly-sorted inputs!
 *
 * - Quick Dry Run: head = [4 -> 2 -> 1 -> 3]
 *     Init   : dummy(INT_MIN) -> nullptr, prev = &dummy, curr = [4]
 *
 *     Step 1 (Insert [4]):
 *       - Save `nextCurr = [2]`.
 *       - `prev->next` is nullptr -> splice [4] after `dummy`:
 *         dummy -> [4] -> nullptr  (prev sits at dummy)
 *
 *     Step 2 (Insert [2]):
 *       - Save `nextCurr = [1]`.
 *       - `prev->next` is [4] (> 2) -> loop doesn't advance `prev`.
 *       - Splice [2] between `dummy` and [4]:
 *         dummy -> [2] -> [4] -> nullptr
 *
 *     Step 3 (Insert [1]):
 *       - Save `nextCurr = [3]`.
 *       - Splice [1] between `dummy` and [2]:
 *         dummy -> [1] -> [2] -> [4] -> nullptr
 *
 *     Step 4 (Insert [3]):
 *       - Save `nextCurr = nullptr`.
 *       - `prev` walks past [1] and [2], stops at [2] (since [2]->next is [4] > 3).
 *       - Splice [3] between [2] and [4]:
 *         dummy -> [1] -> [2] -> [3] -> [4] -> nullptr
 *
 * - Complexity:
 *   Time  : O(N^2) Worst Case (reverse sorted) | O(N) Best Case (already sorted).
 *   Space : O(1) — Rewires existing nodes in-place into `dummy`.
 * ============================================================================
 */
	static ListNode* insertionSortList(ListNode* head) {
		// Edge Case: If the list is empty or has only one node, it's already sorted.
        if (head == nullptr || head->next == nullptr)
        	return head;

		// `dummy` anchors the new sorted list (initialized with INT_MIN for safe comparison)
		ListNode dummy(INT_MIN);
		ListNode* prev = &dummy; // Caches last insertion point for O(N) best-case speed
		ListNode* curr = head;   // Walks through the original unsorted list

		while (curr != nullptr){
			// Step 1: Save the next unsorted node BEFORE overwriting `curr->next`
			ListNode* nextNode = curr->next;

			// Step 2: GM Optimization — Only reset `prev` to `&dummy` if `curr` belongs BEFORE `prev`
			if (prev->val > curr->val)
				prev = &dummy;

			// Walk `prev` forward until `prev->next` is greater than `curr->val` (or nullptr)
			while (prev->next != nullptr && prev->next->val <= curr->val)
				prev = prev->next;

			// Step 3: Splice `curr` right between `prev` and `prev->next`
			curr->next = prev->next;
			prev->next = curr;

			// Step 4: Advance `curr` to the next unsorted node
			curr = nextNode;
		}

		// Return the head of the newly sorted list, which is `dummy.next`
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

	cout << "Enter the values of the nodes: ";
	vector<int> a(n);
	for (int& x : a)
		cin >> x;

	auto* head = MyLinkedList::buildList(a);
	cout << "Original Linked List: ";
	MyLinkedList::printList(head);

	head = MyLinkedList::insertionSortList(head);
	cout << "Sorted Linked List: ";
	MyLinkedList::printList(head);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}
