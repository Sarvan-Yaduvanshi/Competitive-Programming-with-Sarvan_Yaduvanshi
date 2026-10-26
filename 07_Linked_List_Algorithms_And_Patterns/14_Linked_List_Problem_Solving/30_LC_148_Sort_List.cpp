/*
Author: Sarvan Yaduvanshi
Created : 2026-10-26 04:37:19
*/

/*
 * ============================================================================
 *  148. Sort List
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 148
 *  Difficulty : Medium
 *  Topics     : Linked List, Two Pointers, Divide and Conquer, Sorting,
 *               Merge Sort
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the head of a linked list, return the list after sorting it in
 *  ascending order.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      Before :  4 -> 2 -> 1 -> 3
 *      After  :  1 -> 2 -> 3 -> 4
 *
 *  Input  : head = [4,2,1,3]
 *  Output : [1,2,3,4]
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      Before :  -1 -> 5 -> 3 -> 4 -> 0
 *      After  :  -1 -> 0 -> 3 -> 4 -> 5
 *
 *  Input  : head = [-1,5,3,4,0]
 *  Output : [-1,0,3,4,5]
 *
 * ----------------------------------------------------------------------------
 *  Example 3:
 *
 *      Before :  NULL
 *      After  :  NULL
 *
 *  Input  : head = []
 *  Output : []
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in the list is in the range [0, 5 * 10^4].
 *      - -10^5 <= Node.val <= 10^5
 *
 * ----------------------------------------------------------------------------
 *  Follow up: Can you sort the linked list in O(n log n) time and O(1)
 *  memory (i.e. constant space)?
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <random>
#include <chrono>
#include <list>
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
	 * Approach: Sort Node Pointers
	 *
	 * Store every node pointer in a vector, sort the pointers by node value,
	 * then reconnect the nodes in sorted order. The nodes themselves are reused;
	 * only their links are changed.
	 *
	 * Dry run:
	 *   Input:  4 -> 2 -> 1 -> 3 -> nullptr
	 *
	 *   Collected values: [4, 2, 1, 3]
	 *   Sorted pointers : [1, 2, 3, 4]
	 *   Reconnected list: 1 -> 2 -> 3 -> 4 -> nullptr
	 *
	 * The final node is explicitly connected to nullptr to remove its old link.
	 *
	 * Complexity:
	 *   Time: O(n log n), due to sorting n node pointers.
	 *   Space: O(n), for storing the node pointers in the vector.
	 */
	static ListNode* sortListUsingVector(ListNode* head){
		// Empty and single-node lists are already sorted.
		if (head == nullptr || head->next == nullptr)
			return head;

		// Collect pointers so they can be sorted without creating new nodes.
		vector<ListNode*> list;
		while (head != nullptr){
			list.emplace_back(head);
			head = head->next;
		}

		// Sort the pointers according to the values stored in their nodes.
		ranges::sort(list, [](ListNode* a, ListNode* b){
			return a->val < b->val;
		});

		// Reconnect nodes in sorted order using a dummy head.
		ListNode dummy(0);
		ListNode* tail = &dummy;
		for (ListNode* node : list){
			tail->next = node;
			tail = tail->next;
		}

		// The last node should point to nullptr to terminate the list.
		tail->next = nullptr;
		return dummy.next; // return the new head of the sorted list
	}

	/*
 * ============================================================================
 * MERGE & SORT PATTERN 3: 148. Sort List (O(N log N) Time | No Extra Array)
 * ============================================================================
 *
 * - Core Idea (Combine Slow/Fast 1st Middle + Pattern 1 Merge Two Lists):
 *   Merge Sort on a Linked List is simply 3 steps repeated recursively:
 *     Phase 1 [Split in Half (1st Middle)] :
 *       Use `slow = head` and `fast = head` with condition:
 *         `while (fast->next != nullptr && fast->next->next != nullptr)`
 *       Save `rightHead = slow->next`, then CUT `slow->next = nullptr`!
 *
 *     Phase 2 [Recursively Sort Both Halves] :
 *       `left  = sortList(head);`
 *       `right = sortList(rightHead);`
 *
 *     Phase 3 [Merge Both Sorted Halves (Pattern 1 - LC 21)] :
 *       Use the `dummy + tail` zipper engine to merge `left` and `right` in-place!
 *
 * - CRITICAL TRAP (Why 1st Middle is Mandatory for Merge Sort):
 *   Consider a 2-node list: [4] -> [2] -> nullptr.
 *   If we used `while (fast && fast->next)`, `slow` would move to [2], leaving
 *   the left half as [4 -> 2] (size 2) and right half as `nullptr` (size 0),
 *   causing Infinite Recursion (Stack Overflow)!
 *   Using `while (fast->next && fast->next->next)` keeps `slow` at [4], cleanly
 *   splitting into [4] (size 1) and [2] (size 1).
 *
 * - Quick Dry Run: head = [4 -> 2 -> 1 -> 3]
 *     1. Split [4 -> 2 -> 1 -> 3]:
 *        `slow` stops at [2]. Cut `[2]->next = nullptr`.
 *        Left  : [4 -> 2]
 *        Right : [1 -> 3]
 *
 *     2. Split Left [4 -> 2] & Right [1 -> 3]:
 *        - [4 -> 2] splits into [4] and [2] -> `mergeTwoLists([4], [2])` ==> [2 -> 4]
 *        - [1 -> 3] splits into [1] and [3] -> `mergeTwoLists([1], [3])` ==> [1 -> 3]
 *
 *     3. Final Merge:
 *        `mergeTwoLists([2 -> 4], [1 -> 3])` ==> [1 -> 2 -> 3 -> 4]
 *
 * - Complexity:
 *   Time  : O(N log N) — log(N) split levels, doing O(N) merge work per level.
 *   Space : O(log N) recursion call stack (0 heap allocations, no vector used!).
 *           (Note: Bottom-Up Iterative Merge Sort achieves strict O(1) stack space).
 * ============================================================================
 */
	static ListNode* sortListRecursive(ListNode* head){
		// Local lambda function to merge two sorted linked lists in-place.
		auto mergeTwoLists = [&](ListNode* list1, ListNode* list2) -> ListNode*{
			// Create a dummy node to simplify the merge process.
			ListNode dummy(0);
			ListNode* tail = &dummy; // build the merged list starting from dummy

			// Merge nodes from both lists in sorted order.
			while (list1 != nullptr && list2 != nullptr){
				// Case 1: list1's value is less than or equal to list2's value.
				if (list1->val <= list2->val){
					tail->next = list1; // assign list1 value to tail-next
					list1 = list1->next; // move list1 pointer forward

				// Case 2: list2's value is less than list1's value.
				} else{
					tail->next = list2; // assign list2 value to tail-next
					list2 = list2->next; // move list2 pointer forward
				}

				// Move the tail pointer forward to the newly added node.
				tail = tail->next;
			}

			// If one of the lists is exhausted, append the remaining nodes of the other list.
			tail->next = (list1 != nullptr) ? list1 : list2;
			return dummy.next; // return the head of the merged list (skipping the dummy node)
		};

		// Base Case: 0 or 1 node is already sorted
		if (head == nullptr || head->next == nullptr)
			return head;

		// Phase 1: Find 1st Middle using Slow & Fast pointers
		ListNode* slow = head;
		ListNode* fast = head;
		while (fast->next != nullptr && fast->next->next != nullptr){
			slow = slow->next;
			fast = fast->next->next;
		}

		// Cut the list into two independent halves
		ListNode* rightHead = slow->next;
		slow->next = nullptr; // CRITICAL: Disconnect left half from right half!

		// Phase 2: Recursively sort the left half and right half
		ListNode* leftSorted = sortList(head);
		ListNode* rightSorted = sortList(rightHead);

		// Phase 3: Merge the two sorted halves using Pattern 1
		return mergeTwoLists(leftSorted, rightSorted);
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

	/*
 * ============================================================================
 * MERGE & SORT PATTERN 3B: 148. Sort List - Bottom-Up Iterative (Strict O(1) Space)
 * ============================================================================
 *
 * - Core Idea (Bottom-Up Block Doubling: step = 1, 2, 4, 8...):
 *   Instead of splitting top-down via recursion, iterate over block sizes
 *   `step = 1, 2, 4, 8...` while `step < length`.
 *   In each pass, repeatedly:
 *     1. Grab `left = curr`.
 *     2. Cut `left` after `step` nodes -> returns `right = split(left, step)`.
 *     3. Cut `right` after `step` nodes -> returns `curr = split(right, step)`
 *        (which is the start of the NEXT pair!).
 *     4. Merge `left` and `right` directly onto `tail->next`, and advance `tail`
 *        to the end of the merged sublist!
 *
 * - The Two GM Helper Functions:
 *     1. `split(head, step)` :
 *        Walks `step - 1` steps from `head`, cuts `head->next = nullptr`, and
 *        returns the pointer to the next chunk (`nextChunk`).
 *     2. `merge(list1, list2, tail)` :
 *        Attaches merged `list1` and `list2` starting at `tail->next`, then
 *        walks `tail` to the last node of the merged list and returns the new `tail`.
 *
 * - Visual Dry Run: head = [4 -> 2 -> 1 -> 3] (length = 4)
 *     Pass 1 (step = 1):
 *       - Pair 1: split gives left=[4], right=[2], curr=[1 -> 3]
 *                 merge([4], [2])   ==> tail builds [2 -> 4]
 *       - Pair 2: split gives left=[1], right=[3], curr=nullptr
 *                 merge([1], [3])   ==> tail builds [2 -> 4 -> 1 -> 3]
 *
 *     Pass 2 (step = 2):
 *       - Pair 1: split gives left=[2 -> 4], right=[1 -> 3], curr=nullptr
 *                 merge([2->4], [1->3]) ==> tail builds [1 -> 2 -> 3 -> 4]
 *
 *     Loop ends since next `step = 4` is not `< length (4)`.
 *
 * - Complexity:
 *   Time  : O(N log N) — ceil(log2(N)) passes, each scanning N nodes once.
 *   Space : O(1)       — Strictly O(1) auxiliary space (no recursion stack!).
 * ============================================================================
 */
	static ListNode* sortList(ListNode* head){
		// Base Case: 0 or 1 node is already sorted
		if (head == nullptr || head->next == nullptr)
			return head;

		// Phase 1: Count total nodes in the linked list
		const ListNode* temp = head;
		int length = 0;
		while (temp != nullptr){
			length++;
			temp = temp->next;
		}

		// Helper 1: Split the list into two parts, returning the head of the second part
		auto split = [&](ListNode* node, const int step) -> ListNode*{
			// if the node is nullptr, there's nothing to split; return nullptr.
			if (node == nullptr)
				return nullptr;

			// Walk (step - 1) steps to reach the tail of the current chunk
			for (int i = 1; i < step && node->next != nullptr; i++)
				node = node->next;

			// Save the next node to return, and cut the current chunk
			ListNode* nextNode = node->next;
			node->next = nullptr; // Disconnect the current chunk from the rest of the list

			return nextNode; // Return the head of the next chunk
		};

		// Helper 2: Merge `list1` and `list2` onto `tail`, and return the NEW `tail`
		auto mergeTwoLists = [&](ListNode* list1, ListNode* list2, ListNode* tail) -> ListNode*{
			// Merge nodes from both lists in sorted order, starting from `tail`
			while (list1 != nullptr && list2 != nullptr){
				// Case 1: list1's value is less than or equal to list2's value.
				if (list1->val <= list2->val){
					tail->next = list1; // assign list1 value to tail-next
					list1 = list1->next; // move list1 pointer forward

				// Case 2: list2's value is less than list1's value.
				} else{
					tail->next = list2; // assign list2 value to tail-next
					list2 = list2->next; // move list2 pointer forward
				}

				// Move the tail pointer forward to the newly added node.
				tail = tail->next;
			}

			// If one of the lists is exhausted, append the remaining nodes of the other list.
			tail->next = (list1 != nullptr) ? list1 : list2;

			// Walk `tail` to the very end of the newly merged chunk
			while (tail->next != nullptr)
				tail = tail->next;

			return tail; // Return the end of this merged pair to anchor the next pair
		};

		// Create a dummy node to simplify the merge process and handle edge cases.
		ListNode dummy(0);
		dummy.next = head;

		// Phase 2: Double the chunk size `step` on each pass (1, 2, 4, 8...)
		for (int step = 1; step < length; step <<= 1){
			ListNode* prevTail = &dummy; // Anchors the end of the sorted prefix
			ListNode* curr = dummy.next; // Start of the current pass

			// For each pair of chunks, split and merge them
			while (curr != nullptr){
				// 1. Carve out `left` chunk of size `step`
				ListNode* left = curr;

				// 2. Carve out `right` chunk of size `step`
				ListNode* right = split(left, step);

				// 3. Save `curr` as the start of the NEXT pair after `right`
				curr = split(right, step);

				// 4. Merge `left` and `right` onto `prevTail`, and advance `prevTail`
				prevTail = mergeTwoLists(left, right, prevTail);
			}
		}

		// Return the head of the sorted list, which is `dummy.next`
		return dummy.next;
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

	// Method 1: Sort using vector of pointers
	auto* sortedHead1 = MyLinkedList::sortListUsingVector(head);
	cout << "Sorted Linked List (Using Vector): ";
	MyLinkedList::printList(sortedHead1);

	// Rebuild the original list for the next method
	head = MyLinkedList::buildList(a);

	// Method 2: Sort using merge sort (in-place)
	auto* sortedHead2 = MyLinkedList::sortListRecursive(head);
	cout << "Sorted Linked List (In-Place Merge Sort): ";
	MyLinkedList::printList(sortedHead2);

	// Rebuild the original list for the next method
	head = MyLinkedList::buildList(a);

	// Method 3: Sort using bottom-up iterative merge sort (strict O(1) space)
	auto* sortedHead3 = MyLinkedList::sortList(head);
	cout << "Sorted Linked List (Bottom-Up Iterative Merge Sort): ";
	MyLinkedList::printList(sortedHead3);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}
