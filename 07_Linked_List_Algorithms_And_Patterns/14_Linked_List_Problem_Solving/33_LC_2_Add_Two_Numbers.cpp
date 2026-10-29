/*
Author: Sarvan Yaduvanshi
Created : 2026-10-29 00:07:15
*/

/*
 * ============================================================================
 *  2. Add Two Numbers
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 2
 *  Difficulty : Medium
 *  Topics     : Linked List, Math, Recursion
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  You are given two non-empty linked lists representing two non-negative
 *  integers. The digits are stored in reverse order, and each of their nodes
 *  contains a single digit. Add the two numbers and return the sum as a
 *  linked list.
 *
 *  You may assume the two numbers do not contain any leading zero, except
 *  the number 0 itself.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      l1  :   2 -> 4 -> 3          (number 342)
 *      l2  :   5 -> 6 -> 4          (number 465)
 *      sum :   7 -> 0 -> 8          (number 807)
 *
 *  Input  : l1 = [2,4,3], l2 = [5,6,4]
 *  Output : [7,0,8]
 *  Explanation: 342 + 465 = 807.
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      l1  :   0
 *      l2  :   0
 *      sum :   0
 *
 *  Input  : l1 = [0], l2 = [0]
 *  Output : [0]
 *
 * ----------------------------------------------------------------------------
 *  Example 3:
 *
 *      l1  :   9 -> 9 -> 9 -> 9 -> 9 -> 9 -> 9    (number 9999999)
 *      l2  :   9 -> 9 -> 9 -> 9                   (number 9999)
 *      sum :   8 -> 9 -> 9 -> 9 -> 0 -> 0 -> 0 -> 1
 *                                                 (number 10009998)
 *
 *  Input  : l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
 *  Output : [8,9,9,9,0,0,0,1]
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in each linked list is in the range [1, 100].
 *      - 0 <= Node.val <= 9
 *      - It is guaranteed that the list represents a number that does not
 *        have leading zeros.
 * ============================================================================
 *
 * INTERVIEW CHECKPOINT: INPUT MODIFICATION (Approach 2 Follows) GOLDEN RULE:
 * ============================================================
 * Before solving any problem, ask the interviewer:
 * "Am I allowed to modify the input data structure?"
 *
 * 1. If modification is NOT allowed:
 *    - Preserve the original input.
 *    - Create a separate result structure if needed.
 *
 * 2. If modification IS allowed:
 *    - Consider reusing existing nodes or modifying input in-place.
 *    - Reduce extra space and unnecessary memory allocations.
 *
 * 3. Explain the trade-offs:
 *    - Time complexity
 *    - Auxiliary space complexity
 *    - Extra memory allocations
 *    - Whether the original input is preserved
 *
 * GOLDEN RULE:
 * Never assume input modification is allowed.
 * Clarify constraints first, then choose the best approach.
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
 * MATH & DELETION PATTERN 1: 2. Add Two Numbers (O(max(N,M)) Time | O(1) Aux Space)
 * ============================================================================
 *
 * - Why We NEVER Convert the Linked List to `int` or `long long`:
 *   A linked list can have up to 100 nodes (a 100-digit number!), which
 *   overflows 64-bit `unsigned long long` (max ~20 digits). Digit-by-digit
 *   carry propagation handles numbers of infinite length!
 *
 * - Core Idea (The Unified `l1 || l2 || carry` Loop + Dummy-Tail Builder):
 *   Instead of writing separate loops for uneven list lengths or a leftover
 *   final carry (e.g., 99 + 1 = 100), use ONE master loop condition:
 *     `while (l1 != nullptr || l2 != nullptr || carry != 0)`
 *   In each step:
 *     1. `sum = carry`
 *     2. If `l1` exists: `sum += l1->val`, advance `l1`
 *     3. If `l2` exists: `sum += l2->val`, advance `l2`
 *     4. Update `carry = sum / 10`
 *     5. Append `new ListNode(sum % 10)` to `tail->next` and advance `tail`.
 *
 * - Quick Dry Run: l1 = [9 -> 9], l2 = [1]  (99 + 1 = 100)
 *     Init   : dummy(0), tail = &dummy, carry = 0
 *     Step 1 : sum = 0 + 9 + 1 = 10 -> carry = 1, digit = 0.
 *              List: [0], l1 = [9], l2 = nullptr
 *     Step 2 : sum = 1 + 9 + 0 = 10 -> carry = 1, digit = 0.
 *              List: [0 -> 0], l1 = nullptr, l2 = nullptr
 *     Step 3 : Both l1 & l2 are nullptr, BUT `carry == 1` keeps loop alive!
 *              sum = 1 -> carry = 0, digit = 1.
 *              List: [0 -> 0 -> 1]
 *     End    : l1 == nullptr, l2 == nullptr, carry == 0 -> Loop stops!
 *              Returns `dummy.next` ([0 -> 0 -> 1] == 100).
 *
 * - Complexity:
 *   Time  : O(max(N, M)) — Single pass over the longer list (+1 step if final carry).
 *   Space : O(1) auxiliary space (excluding O(max(N, M)) required for the output list).
 * ============================================================================
 */
	static ListNode* addTwoNumbers(const ListNode* list1, const ListNode* list2){
		// Dummy node to simplify list construction and avoid special cases for the head
		ListNode dummy(0);
		ListNode* tail = &dummy; // build the result list starting from the dummy node
		int carry = 0; // Initialize carry to 0

		// Unified condition handles uneven lengths AND final leftover carry
		while (list1 != nullptr || list2 != nullptr || carry != 0){
			// Start with the carry from the previous step
			int sum = carry;

			// Add the value from list1 if it exists
			if (list1 != nullptr){
				sum += list1->val; // add
				list1 = list1->next; // move forward
			}

			// Add the value from list2 if it exists
			if (list2 != nullptr){
				sum += list2->val; // add
				list2 = list2->next; // move forward
			}

			carry = sum / 10;  // Extract carry for the next position (0 or 1)
			tail->next = new ListNode(sum % 10); // Create node with current digit (0 - 9)
			tail = tail->next; // Move the tail pointer forward
		}

		return dummy.next; // return the new list, skipping the dummy node
	}

	/*
	 * ============================================================================
	 *  Approach 2: Reuse the Input List (In-Place Result)
	 * ============================================================================
	 *
	 *  This approach assumes that modifying either input list is allowed.
	 *  `list1` is used as the result list whenever possible:
	 *
	 *  1. Add the current digits and the carry from the previous position.
	 *  2. Store the result digit directly in the current `list1` node.
	 *  3. Attach that node after `tail`, so no result node is allocated.
	 *  4. When `list1` ends first, continue with the remaining nodes of `list2`.
	 *  5. Allocate only one node if a carry remains after both lists end.
	 *
	 *  Dry run: list1 = [9 -> 9], list2 = [1]  (99 + 1 = 100)
	 *
	 *      Initial: carry = 0, result = []
	 *      Step 1: sum = 9 + 1 + 0 = 10
	 *              Store 0 in list1's first node, carry = 1.
	 *              result = [0], list1 = [9], list2 = nullptr
	 *      Step 2: sum = 9 + 0 + 1 = 10
	 *              Store 0 in list1's second node, carry = 1.
	 *              result = [0 -> 0], both lists are exhausted
	 *      Final:  carry = 1, so append a new node containing 1.
	 *              result = [0 -> 0 -> 1] (100)
	 *
	 *  Complexity:
	 *      Time  : O(max(N, M)), because each input node is visited once.
	 *      Space : O(1) auxiliary space; only one node is allocated for a
	 *              possible final carry. The input nodes are reused as output.
	 *
	 *  Trade-off: The input lists are modified and their original values are
	 *  not preserved. Ask whether input modification is allowed before using
	 *  this approach.
	 * ============================================================================
	 */
	static ListNode* addTwoNumbersReusesList(ListNode* list1, ListNode* list2){
		// Use a dummy node so avoid special cases for the head of the result list
		ListNode dummy(0);
		ListNode* tail = &dummy;
		int carry = 0;

		// Unified loop condition handles uneven lengths and leftover carry
		while (list1 != nullptr || list2 != nullptr){
			// If list1 is exhausted, switch to list2 and continue
			if (list1 == nullptr){
				list1 = list2;
				list2 = nullptr; // list2 is now fully consumed, so set it to nullptr
			}

			// Add the current digits and the carry from the previous position
			int sum = list1->val + carry;

			// Add the value from list2 if it exists
			if (list2 != nullptr){
				sum += list2->val;
				list2 = list2->next;
			}

			// Update carry and store the result digit in the current list1 node
			carry = sum / 10;
			list1->val = sum % 10;

			// Append the modified list1 node to the result list
			tail->next = list1;
			tail = list1; // Move the tail pointer forward
			list1 = list1->next; // Advance list1 to the next node
		}

		// If there's a leftover carry after both lists are exhausted, create a new node
		if (carry != 0)
			tail->next = new ListNode(carry);

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
	int n1, n2;

	cout << "Enter the number of nodes in the first linked list: ";
	cin >> n1;
	cout << "Enter the values of the nodes for the first linked list: ";
	vector<int> a1(n1);
	for (int& x : a1)
		cin >> x;

	cout << "Enter the number of nodes in the second linked list: ";
	cin >> n2;
	cout << "Enter the values of the nodes for the second linked list: ";
	vector<int> a2(n2);
	for (int& x : a2)
		cin >> x;

	auto* head1 = MyLinkedList::buildList(a1);
	auto* head2 = MyLinkedList::buildList(a2);
	cout << "First Linked List: ";
	MyLinkedList::printList(head1);
	cout << "Second Linked List: ";
	MyLinkedList::printList(head2);

	// Add the two numbers represented by the linked lists
	auto* sumHead = MyLinkedList::addTwoNumbers(head1, head2);
	cout << "Sum Linked List: ";
	MyLinkedList::printList(sumHead);

	// Add the two numbers represented by the linked lists using the in-place approach
	auto* sumHeadInPlace = MyLinkedList::addTwoNumbersReusesList(head1, head2);
    cout << "Sum Linked List (In-Place): ";
	MyLinkedList::printList(sumHeadInPlace);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}