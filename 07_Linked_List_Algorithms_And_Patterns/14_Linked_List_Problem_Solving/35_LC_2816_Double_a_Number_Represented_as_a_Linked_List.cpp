/*
Author: Sarvan Yaduvanshi
Created : 2026-10-29 17:34:14
*/

/*
 * ============================================================================
 *  2816. Double a Number Represented as a Linked List
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 2816
 *  Difficulty : Medium
 *  Topics     : Linked List, Math, Stack
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  You are given the head of a non-empty linked list representing a
 *  non-negative integer without leading zeroes.
 *
 *  Return the head of the linked list after doubling it.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      Before :  1 -> 8 -> 9          (number 189)
 *      After  :  3 -> 7 -> 8          (number 378)
 *
 *  Input  : head = [1,8,9]
 *  Output : [3,7,8]
 *  Explanation: The figure above corresponds to the given linked list which
 *               represents the number 189. Hence, the returned linked list
 *               represents the number 189 * 2 = 378.
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      Before :       9 -> 9 -> 9     (number 999)
 *      After  :  1 -> 9 -> 9 -> 8     (number 1998)
 *
 *  Input  : head = [9,9,9]
 *  Output : [1,9,9,8]
 *  Explanation: The figure above corresponds to the given linked list which
 *               represents the number 999. Hence, the returned linked list
 *               represents the number 999 * 2 = 1998.
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in the list is in the range [1, 10^4].
 *      - 0 <= Node.val <= 9
 *      - The input is generated such that the list represents a number that
 *        does not have leading zeros, except the number 0 itself.
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
	 * MATH & LINKED-LIST REVERSAL PATTERN: 2816. Double a Number
	 * ============================================================================
	 *
	 * - Why we reverse the list:
	 *   The most significant digit is stored first, but doubling must begin
	 *   from the least significant digit so that carry can move left. Reversing
	 *   the list makes the least significant digit available first.
	 *
	 * - Core Idea (Reverse -> Double -> Reverse):
	 *   1. Reverse the input list.
	 *   2. Traverse the reversed list from right to left.
	 *      For every digit, calculate `sum = (2 * digit) + carry`.
	 *   3. Store `sum % 10` in a new result node and pass `sum / 10` forward.
	 *   4. If a carry remains after the traversal, append it.
	 *   5. Reverse the result list to restore the original digit order.
	 *
	 * - Dry Run: head = [1 -> 8 -> 9]  (189 * 2 = 378)
	 *
	 *      After reversing:
	 *          [9 -> 8 -> 1]
	 *
	 *      Step 1: digit = 9, sum = (2 * 9) + 0 = 18
	 *              digit = 8, carry = 1
	 *              result = [8]
	 *      Step 2: digit = 8, sum = (2 * 8) + 1 = 17
	 *              digit = 7, carry = 1
	 *              result = [8 -> 7]
	 *      Step 3: digit = 1, sum = (2 * 1) + 1 = 3
	 *              digit = 3, carry = 0
	 *              result = [8 -> 7 -> 3]
	 *
	 *      Reverse result:
	 *          [3 -> 7 -> 8] = 378
	 *
	 * - Complexity:
	 *   Time  : O(N), because the input and result lists are each traversed a
	 *           constant number of times.
	 *   Space : O(1) auxiliary space for pointers and carry, excluding
	 *           O(N + 1) space for the newly created output list.
	 *
	 *   Trade-off: The input list is reversed in place, so its original links
	 *   are not preserved. The result uses newly allocated nodes.
	 * ============================================================================
	 */
	static ListNode* doubleItUsingReverse(ListNode* head){
		// Step 1: Reverse the input list to process from least significant digit
	    ListNode* curr = head;
		ListNode* prev = nullptr;
		while (curr != nullptr){
			ListNode* next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}

		// Step 2: Traverse the reversed list and double each digit
		ListNode dummy(0);
		ListNode* tail = &dummy;
		int carry = 0;

		while (prev != nullptr){
			int sum = carry;
			sum += (2 * prev->val); // Double the current digit and add carry
			prev = prev->next; // move forward in the reversed list

			carry = sum / 10; // add carry for next digit

			tail->next = new ListNode(sum % 10); // create new node for current digit
			tail = tail->next; // move tail forward
		}

		// Step 3: If a carry remains, create a new node for it
		if (carry != 0)
			tail->next = new ListNode(carry);

		// Step 4: Reverse the result list to restore original order
		curr = dummy.next;
		prev = nullptr;
		while (curr != nullptr){
			ListNode* next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}

		// Return the head of the newly created doubled list
		return prev;
	}

	/*
 * ============================================================================
 * MATH & DELETION PATTERN 2B: 2816. Double a Number (1-Pass O(N) Time | O(1) Space)
 * ============================================================================
 *
 * - GM Mathematical Insight (1-Step Lookahead Carry Prediction):
 *   When doubling a number, the maximum carry from any position is ALWAYS 1
 *   (since 9 * 2 + 1 = 19).
 *   Furthermore, a digit `x` produces a carry to its left IF AND ONLY IF `x >= 5`
 *   (because 4 * 2 + 1 = 9 < 10, while 5 * 2 = 10 >= 10)!
 *   Therefore, we don't need to reverse the list! Walking left-to-right at `curr`:
 *     1. `curr->val = (curr->val * 2) % 10;`
 *     2. If `curr->next != nullptr && curr->next->val >= 5`, increment `curr->val++`!
 *
 * - Handling Carry Out of `head`:
 *   If `head->val >= 5` initially, we simply prepend a leading `[0]` node
 *   (`head = new ListNode(0, head)`), and the loop naturally increments that `[0]`
 *   to `[1]` when it checks `curr->next->val >= 5`!
 *
 * - Quick Dry Run: head = [9 -> 9 -> 9]
 *     Pre-check : `head->val` is 9 (>= 5) -> prepend [0]:
 *                 List becomes [0 -> 9 -> 9 -> 9]
 *     Step 1 (curr = [0]):
 *       - `0 * 2 % 10 = 0`. Since `curr->next` is 9 (>= 5), `curr->val++` ==> [1]
 *     Step 2 (curr = 1st [9]):
 *       - `9 * 2 % 10 = 8`. Since `curr->next` is 9 (>= 5), `curr->val++` ==> [9]
 *     Step 3 (curr = 2nd [9]):
 *       - `9 * 2 % 10 = 8`. Since `curr->next` is 9 (>= 5), `curr->val++` ==> [9]
 *     Step 4 (curr = 3rd [9]):
 *       - `9 * 2 % 10 = 8`. `curr->next` is nullptr ==> [8]
 *     Final Result: [1 -> 9 -> 9 -> 8] (1998) in 1 single left-to-right pass!
 *
 * - Complexity:
 *   Time  : O(N) — Single left-to-right pass!
 *   Space : O(1) — Pure in-place modification (0 stack, 0 reversal).
 * ============================================================================
 */
	static ListNode* doubleIt(ListNode* head){
		// If the most significant digit is >= 5, doubling will produce a new leading 1
		if (head->val >= 5){
			ListNode* newNode = new ListNode(0); // create a new leading node to handle carry
			newNode->next = head; // link the new node to the original head
			head = newNode; // update head to point to the new leading node
		}

		// Single pass left-to-right with 1-node lookahead for carry
		ListNode* curr = head;
		while (curr != nullptr){
			// Double current digit and keep the ones place
			curr->val = (2 * curr->val) % 10;

			// Lookahead: Will the NEXT digit generate a carry when doubled?
			if (curr->next != nullptr && curr->next->val >= 5)
				curr->val += 1;

			curr = curr->next; // move to the next node
		}

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

	// Method 1: Double the number represented by the linked list using reverse
	auto* doubledHead = MyLinkedList::doubleItUsingReverse(head);
	cout << "Doubled Linked List: ";
	MyLinkedList::printList(doubledHead);

	// Reset the original list for the next method
	head = MyLinkedList::buildList(a);

	// Method 2: Double the number represented by the linked list using 1-pass O(N) time and O(1) space
	auto* doubledHeadInPlace = MyLinkedList::doubleIt(head);
	cout << "Doubled Linked List (In-Place): ";
	MyLinkedList::printList(doubledHeadInPlace);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}