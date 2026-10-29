/*
Author: Sarvan Yaduvanshi
Created : 2026-10-29 14:16:15
*/

/*
 * ============================================================================
 *  445. Add Two Numbers II
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 445
 *  Difficulty : Medium
 *  Topics     : Linked List, Math, Stack
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  You are given two non-empty linked lists representing two non-negative
 *  integers. The most significant digit comes first and each of their nodes
 *  contains a single digit. Add the two numbers and return the sum as a
 *  linked list.
 *
 *  You may assume the two numbers do not contain any leading zero, except
 *  the number 0 itself.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      l1  :   7 -> 2 -> 4 -> 3        (number 7243)
 *      l2  :        5 -> 6 -> 4        (number 564)
 *      sum :   7 -> 8 -> 0 -> 7        (number 7807)
 *
 *  Input  : l1 = [7,2,4,3], l2 = [5,6,4]
 *  Output : [7,8,0,7]
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      l1  :   2 -> 4 -> 3             (number 243)
 *      l2  :   5 -> 6 -> 4             (number 564)
 *      sum :   8 -> 0 -> 7             (number 807)
 *
 *  Input  : l1 = [2,4,3], l2 = [5,6,4]
 *  Output : [8,0,7]
 *
 * ----------------------------------------------------------------------------
 *  Example 3:
 *
 *      l1  :   0
 *      l2  :   0
 *      sum :   0
 *
 *  Input  : l1 = [0], l2 = [0]
 *  Output : [0]
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in each linked list is in the range [1, 100].
 *      - 0 <= Node.val <= 9
 *      - It is guaranteed that the list represents a number that does not
 *        have leading zeros.
 *
 * ----------------------------------------------------------------------------
 *  Follow up: Could you solve it without reversing the input lists?
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
	 * MATH & LINKED-LIST REVERSAL PATTERN: 445. Add Two Numbers II
	 * ============================================================================
	 *
	 * - Why we reverse the lists:
	 *   Digits are stored from most significant to least significant, but
	 *   addition must start from the least significant digit. Reversing both
	 *   lists allows us to add from right to left without using stacks.
	 *
	 * - Core Idea (Reverse -> Add -> Reverse):
	 *   1. Reverse `list1` and `list2`.
	 *   2. Add corresponding digits, starting with `sum = carry`.
	 *   3. Store each calculated digit in a newly created result node.
	 *   4. Reverse the result to restore most-significant-digit-first order.
	 *
	 * - Dry Run: list1 = [7 -> 2 -> 4 -> 3], list2 = [5 -> 6 -> 4]
	 *   (7243 + 564 = 7807)
	 *
	 *      After reversing:
	 *          list1 = [3 -> 4 -> 2 -> 7]
	 *          list2 = [4 -> 6 -> 5]
	 *
	 *      Step 1: sum = 3 + 4 + 0 = 7  -> digit = 7, carry = 0
	 *              result = [7]
	 *      Step 2: sum = 4 + 6 + 0 = 10 -> digit = 0, carry = 1
	 *              result = [7 -> 0]
	 *      Step 3: sum = 2 + 5 + 1 = 8  -> digit = 8, carry = 0
	 *              result = [7 -> 0 -> 8]
	 *      Step 4: sum = 7 + 0 + 0 = 7  -> digit = 7, carry = 0
	 *              result = [7 -> 0 -> 8 -> 7]
	 *
	 *      Reverse result:
	 *          [7 -> 8 -> 0 -> 7] = 7807
	 *
	 * - Complexity:
	 *   Time  : O(N + M), because each list and the result are traversed a
	 *           constant number of times.
	 *   Space : O(1) auxiliary space for pointers and carry, excluding
	 *           O(max(N, M) + 1) space for the output list.
	 *
	 *   Trade-off: The input lists are reversed in place, so their original
	 *   links are not preserved.
	 * ============================================================================
	 */
	static ListNode* addTwoNumbers(ListNode* list1, ListNode* list2){
		// Step 1: Reverse first list
		ListNode* curr = list1;
		ListNode* prev = nullptr;
		while (curr != nullptr){
			ListNode* next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}

		// Step 2: Reverse second list
		ListNode* curr2 = list2;
		ListNode* prev2 = nullptr;
		while (curr2 != nullptr){
			ListNode* next = curr2->next;
			curr2->next = prev2;
			prev2 = curr2;
			curr2 = next;
		}

		// Step 3: Add the two reversed lists
		ListNode dummy(0);
		ListNode* tail = &dummy;
		int carry = 0;
		while (prev != nullptr || prev2 != nullptr || carry != 0){
			int sum = carry;

			if (prev != nullptr){
				sum += prev->val;
				prev = prev->next;
			}

			if (prev2 != nullptr){
				sum += prev2->val;
				prev2 = prev2->next;
			}

			carry = sum / 10;
			tail->next = new ListNode(sum % 10);
			tail = tail->next;
		}

		// Step 4: Reverse the result list to restore original order
		curr = dummy.next;
		prev = nullptr;
		while (curr != nullptr){
			ListNode* next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}

		// Return the head of the final result list
		return prev;
	}

	/*
 * ============================================================================
 * MATH & DELETION PATTERN 2A: 445. Add Two Numbers II (No Input Modification)
 * ============================================================================
 *
 * - Core Idea (Two Stacks + Front/Head-Insertion Builder):
 *   1. Push all values of `l1` into `s1` and `l2` into `s2` so the 1s digits
 *      sit on top of the stacks.
 *   2. Run our unified carry loop: `while (!s1.empty() || !s2.empty() || carry != 0)`.
 *   3. GM Builder Trick (Head-Insertion instead of Tail-Append):
 *      Since we generate digits from least-significant (1s) to most-significant,
 *      we prepend each `newNode` directly in front of `head`:
 *        `ListNode* newNode = new ListNode(sum % 10);`
 *        `newNode->next = head;`
 *        `head = newNode;`
 *      This builds the final list in forward order automatically without needing
 *      a final reversal pass!
 *
 * - Note (When Modifying Input Lists IS Allowed - O(1) Aux Space):
 *   1. `l1 = reverseList(l1); l2 = reverseList(l2);`  (Reversal Pattern 1A)
 *   2. `res = addTwoNumbers(l1, l2);`                 (Math Pattern 1 - LC 2)
 *   3. `return reverseList(res);`
 *
 * - Quick Dry Run: l1 = [7 -> 2 -> 4 -> 3], l2 = [5 -> 6 -> 4]
 *     Stacks : s1 = [7, 2, 4, 3] (top = 3), s2 = [5, 6, 4] (top = 4), head = nullptr
 *     Step 1 : 3 + 4 + 0 = 7  (carry = 0) -> prepend [7]:
 *              head = [7] -> nullptr
 *     Step 2 : 4 + 6 + 0 = 10 (carry = 1) -> prepend [0]:
 *              head = [0] -> [7] -> nullptr
 *     Step 3 : 2 + 5 + 1 = 8  (carry = 0) -> prepend [8]:
 *              head = [8] -> [0] -> [7] -> nullptr
 *     Step 4 : 7 + 0 + 0 = 7  (carry = 0) -> prepend [7]:
 *              head = [7] -> [8] -> [0] -> [7] -> nullptr
 *
 * - Complexity:
 *   Time  : O(N + M) — Push all nodes once, pop all nodes once.
 *   Space : O(N + M) stack space to preserve original lists unmodified.
 * ============================================================================
 */
	static ListNode* addTwoNumbersWithoutReverse(const ListNode* l1, const ListNode* l2){
		// Step 1: Push all values of l1 into stack st1 so the 1s digit is on top
		stack<int> st1;
		while (l1 != nullptr){
			st1.push(l1->val);
			l1 = l1->next;
		}

		// Step 2: Push all values of l2 into stack st2 so the 1s digit is on top
		stack<int> st2;
		while (l2 != nullptr){
			st2.push(l2->val);
			l2 = l2->next;
		}

		// Step 3: Add the two numbers using the stacks and build the result list
		ListNode* head = nullptr; // Anchors the front of our growing result list
		int carry = 0;

		// Unified carry loop: continue until both stacks are empty and no carry remains
		while (!st1.empty() || !st2.empty() || carry != 0){
			// Calculate the sum of the top digits and the carry
			int sum =  carry;

			// Add the top value from st1 if available
			if (!st1.empty()){
				sum += st1.top();
				st1.pop();
			}

			// Add the top value from st2 if available
			if (!st2.empty()){
				sum += st2.top();
				st2.pop();
			}

			// Compute the new carry and create a new node for the current digit
			carry = sum / 10;

			// Head-Insertion: Prepend `newNode` directly in front of `head`
			ListNode* newNode = new ListNode(sum % 10);
			newNode->next = head;
			head = newNode;
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

	// Approach 2: do not reverse the input lists, use stacks to add the numbers
	auto* sumHeadWithoutReverse = MyLinkedList::addTwoNumbersWithoutReverse(head1, head2);
	cout << "Sum Linked List (Without Reversing Input Lists): ";
	MyLinkedList::printList(sumHeadWithoutReverse);

	// Approach 1: reverse the input lists, add the numbers, and reverse the result
	auto* sumHead = MyLinkedList::addTwoNumbers(head1, head2);
	cout << "Sum Linked List: ";
	MyLinkedList::printList(sumHead);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}