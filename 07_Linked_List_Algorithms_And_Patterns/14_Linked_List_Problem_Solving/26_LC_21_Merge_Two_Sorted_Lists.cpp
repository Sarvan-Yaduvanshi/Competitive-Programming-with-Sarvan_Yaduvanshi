/*
Author: Sarvan Yaduvanshi
Created : 2026-10-25 00:33:32
*/

/*
 * ============================================================================
 *  21. Merge Two Sorted Lists
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 21
 *  Difficulty : Easy
 *  Topics     : Linked List, Recursion
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Adobe, Uber
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  You are given the heads of two sorted linked lists list1 and list2.
 *
 *  Merge the two lists into one sorted list. The list should be made by
 *  splicing together the nodes of the first two lists.
 *
 *  Return the head of the merged linked list.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      list1 :  1 -> 2 -> 4
 *      list2 :  1 -> 3 -> 4
 *      merged:  1 -> 1 -> 2 -> 3 -> 4 -> 4
 *
 *  Input  : list1 = [1,2,4], list2 = [1,3,4]
 *  Output : [1,1,2,3,4,4]
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      list1 :  NULL
 *      list2 :  NULL
 *      merged:  NULL
 *
 *  Input  : list1 = [], list2 = []
 *  Output : []
 *
 * ----------------------------------------------------------------------------
 *  Example 3:
 *
 *      list1 :  NULL
 *      list2 :  0 -> NULL
 *      merged:  0 -> NULL
 *
 *  Input  : list1 = [], list2 = [0]
 *  Output : [0]
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in both lists is in the range [0, 50].
 *      - -100 <= Node.val <= 100
 *      - Both list1 and list2 are sorted in non-decreasing order.
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
 * MERGE & SORT PATTERN 1: 21. Merge Two Sorted Lists (O(N+M) Time | O(1) Space)
 * ============================================================================
 *
 * - Core Idea (The Dummy-Tail Builder Engine):
 *   Use a stack-allocated `dummy` node to anchor the start of the result, and a
 *   moving `tail` pointer (`tail = &dummy`) that always sits at the end of the
 *   merged list being built.
 *
 * - The 3-Phase Execution:
 *     Phase 1 [Compare & Attach Smaller Node] :
 *       While BOTH `list1 != nullptr` and `list2 != nullptr`:
 *         - If `list1->val <= list2->val`: attach `tail->next = list1`, advance `list1`.
 *         - Else                         : attach `tail->next = list2`, advance `list2`.
 *         - Always advance `tail = tail->next` to stay at the end of the built list.
 *
 *     Phase 2 [O(1) Leftover Chain Attach] :
 *       When one list hits `nullptr`, the other list still has sorted nodes left.
 *       Instead of looping (like in arrays), attach the entire remaining chain
 *       in 1 step: `tail->next = (list1 != nullptr) ? list1 : list2;`
 *
 *     Phase 3 [Return Real Head] :
 *       Return `dummy.next`.
 *
 * - Quick Dry Run: list1 = [1 -> 3 -> 5], list2 = [2 -> 4]
 *     Init   : [dummy], tail = &dummy
 *     Step 1 : Compare 1 vs 2 -> attach [1], list1 = [3], tail = [1]
 *              Merged: [dummy] -> [1]
 *     Step 2 : Compare 3 vs 2 -> attach [2], list2 = [4], tail = [2]
 *              Merged: [dummy] -> [1] -> [2]
 *     Step 3 : Compare 3 vs 4 -> attach [3], list1 = [5], tail = [3]
 *              Merged: [dummy] -> [1] -> [2] -> [3]
 *     Step 4 : Compare 5 vs 4 -> attach [4], list2 = nullptr, tail = [4]
 *              Merged: [dummy] -> [1] -> [2] -> [3] -> [4]
 *     End    : `list2` is nullptr -> Loop stops!
 *              Leftover attach: `tail->next = list1` (attaches [5 -> nullptr]).
 *              Final: [1] -> [2] -> [3] -> [4] -> [5] -> nullptr
 *
 * - Complexity:
 *   Time  : O(N + M) — Visits nodes until one list ends.
 *   Space : O(1)     — Rewires existing nodes in-place without `new`.
 * ============================================================================
 */
	static ListNode* mergeTwoLists(ListNode* list1, ListNode* list2){
		// Create a dummy node on the stack to anchor the merged list
		ListNode dummy(0);
		ListNode* tail = &dummy;

		// Phase 1: Compare heads of both lists and attach the smaller node to `tail`
		while (list1 != nullptr && list2 != nullptr){
			// list1's value is smaller or equal, attach it to the merged list and move list1 forward
			if (list1->val <= list2->val){
				tail->next = list1;
				list1 = list1->next;

			// list2's value is smaller, attach it to the merged list and move list2 forward
			} else{
				tail->next = list2;
				list2 = list2->next;
			}

			// Move the tail pointer to the end of the merged list
			tail = tail->next;
		}

		// Phase 2: Attach the remaining nodes from the non-empty list (if any)
		tail->next = (list1 != nullptr) ? list1 : list2;

		// Phase 3: Return the real head sitting right after `dummy`
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
	int n, m;

	cout << "Enter the number of nodes in the first linked list: ";
	cin >> n;
	cout << "Enter the values of the nodes in the first linked list: ";
	vector<int> a(n);
	for (int& x : a)
		cin >> x;

	cout << "Enter the number of nodes in the second linked list: ";
	cin >> m;
	cout << "Enter the values of the nodes in the second linked list: ";
	vector<int> b(m);
	for (int& x : b)
		cin >> x;

	// Build the two linked lists
	auto* list1 = MyLinkedList::buildList(a);
	auto* list2 = MyLinkedList::buildList(b);

	// print the original linked lists
	cout << "Original Linked List 1: ";
	MyLinkedList::printList(list1);

	// print the original linked lists
	cout << "Original Linked List 2: ";
	MyLinkedList::printList(list2);

	// Merge the two sorted linked lists
	auto* mergedList = MyLinkedList::mergeTwoLists(list1, list2);
	cout << "Merged Sorted Linked List: ";
	MyLinkedList::printList(mergedList);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}
