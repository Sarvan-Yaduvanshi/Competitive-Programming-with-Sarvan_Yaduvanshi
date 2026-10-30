/*
Author: Sarvan Yaduvanshi
Created : 2026-10-29 18:07:15
*/

/*
 * ============================================================================
 *  369. Plus One Linked List  (LeetCode Premium) (Available in GeeksforGeeks)
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 369
 *  Difficulty : Medium
 *  Topics     : Linked List, Math
 *  Companies  : Google, Amazon, Microsoft, Meta, Apple, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given a non-negative integer represented as a linked list of digits,
 *  plus one to the integer.
 *
 *  The digits are stored such that the most significant digit is at the
 *  head of the list.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      Before :  1 -> 2 -> 3          (number 123)
 *      After  :  1 -> 2 -> 4          (number 124)
 *
 *  Input  : head = [1,2,3]
 *  Output : [1,2,4]
 *  Explanation: 123 + 1 = 124. Only the last digit changes. No carry.
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      Before :  0                    (number 0)
 *      After  :  1                    (number 1)
 *
 *  Input  : head = [0]
 *  Output : [1]
 *  Explanation: 0 + 1 = 1.
 *
 * ----------------------------------------------------------------------------
 *  Example 3: (extra example, carry in the middle)
 *
 *      Before :  1 -> 2 -> 9          (number 129)
 *      After  :  1 -> 3 -> 0          (number 130)
 *
 *  Input  : head = [1,2,9]
 *  Output : [1,3,0]
 *  Explanation: 129 + 1 = 130. Last digit 9 becomes 0 and gives carry 1.
 *               Carry moves left: 2 + 1 = 3. The carry stops there, so the
 *               first digit 1 stays the same.
 *
 * ----------------------------------------------------------------------------
 *  Example 4: (extra example, carry makes a new head node)
 *
 *      Before :       9 -> 9 -> 9     (number 999)
 *      After  :  1 -> 0 -> 0 -> 0     (number 1000)
 *
 *  Input  : head = [9,9,9]
 *  Output : [1,0,0,0]
 *  Explanation: 999 + 1 = 1000. Every 9 becomes 0 and passes carry left.
 *               Carry reaches the front, so a new head node 1 is created.
 *               The list becomes 1 longer.
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in the linked list is in the range [1, 100].
 *      - 0 <= Node.val <= 9
 *      - The number represented by the linked list does not contain leading
 *        zeros except for the zero itself.
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
	 * MATH & LINKED-LIST CARRY PATTERN: 369. Plus One Linked List
	 * ============================================================================
	 *
	 * - Core Idea (Find the Last Non-Nine Digit):
	 *   Adding one only changes the suffix of consecutive 9s. Therefore, scan
	 *   the list once and remember the last node whose value is not 9.
	 *
	 *   1. Use a dummy node before `head` so the number 999 can create a new
	 *      leading digit without a special-case traversal.
	 *   2. Find `lastNotNine`, the last node with a value other than 9.
	 *   3. Increment `lastNotNine->val`.
	 *   4. Set every node after it to 0 because those nodes were 9 and become
	 *      0 after the carry passes through them.
	 *   5. If the dummy was incremented, return a new node containing 1.
	 *
	 * - Dry Run: head = [1 -> 2 -> 9 -> 9]  (1299 + 1 = 1300)
	 *
	 *      Initial:
	 *          dummy -> 1 -> 2 -> 9 -> 9
	 *          lastNotNine = dummy
	 *
	 *      Scan:
	 *          1 is not 9 -> lastNotNine = node(1)
	 *          2 is not 9 -> lastNotNine = node(2)
	 *          9, 9       -> lastNotNine remains node(2)
	 *
	 *      Increment lastNotNine:
	 *          2 becomes 3
	 *          List: 1 -> 3 -> 9 -> 9
	 *
	 *      Reset the suffix after lastNotNine:
	 *          9 -> 0, 9 -> 0
	 *          Result: 1 -> 3 -> 0 -> 0 = 1300
	 *
	 * - Special Case: head = [9 -> 9 -> 9]
	 *      No non-nine node is found, so the dummy value becomes 1 and the
	 *      original nodes become 0. Return [1 -> 0 -> 0 -> 0].
	 *
	 * - Complexity:
	 *   Time  : O(N), because the list is scanned once and the affected suffix
	 *           is reset once.
	 *   Space : O(1) auxiliary space. Only one new node is allocated when all
	 *           digits are 9; otherwise, the list is modified in place.
	 *
	 *   Trade-off: The input list is modified directly, but no reversal or
	 *   recursion is required.
	 * ============================================================================
	 */
	static ListNode* plusOne(ListNode* head){
		// Dummy node simplifies carry propagation when all digits are 9
		ListNode dummy(0);
		dummy.next = head;

		// Track the last node that is not 9, because only this node will be incremented
		ListNode* lastNotNine = &dummy;

		// Loop through the list to find the last non-nine node
		for (ListNode* curr = head; curr != nullptr; curr = curr->next){
			if (curr->val != 9)
				lastNotNine = curr; // Update lastNotNine to the current node if it's not 9
		}

		// Update the last non-nine node by incrementing its value
		lastNotNine->val++;

		// Set all nodes after lastNotNine to 0, as they were 9 and now become 0
		for (ListNode* curr = lastNotNine->next; curr != nullptr; curr = curr->next)
			curr->val = 0;

		// Special case: if all nodes were 9, the dummy node's value is now 1, and we return a new head
		if (lastNotNine == &dummy){
			ListNode* newNode = new ListNode(1); // Create a new node with value 1
			newNode->next = head; // Link the new node to the original head
			return newNode; // Return the new head of the list
		}

		return dummy.next;
	}

	// Approach 2: Reverse the list, add one, and reverse back
	static ListNode* plusOneReverse(ListNode* head){
		// Step 1: Reverse the linked list
		ListNode* prev = nullptr;
		ListNode* curr = head;
		while (curr != nullptr){
			ListNode* nextTemp = curr->next;
			curr->next = prev;
			prev = curr;
			curr = nextTemp;
		}
		head = prev; // New head after reversal

		// Step 2: Add one to the reversed list
		curr = head;
		int carry = 1; // Start with a carry of 1 for the plus one operation
		while (curr != nullptr && carry > 0){
			int sum = curr->val + carry;
			curr->val = sum % 10; // Update the current node's value
			carry = sum / 10; // Calculate new carry
			if (curr->next == nullptr && carry > 0){
				curr->next = new ListNode(carry); // If at the end and there's still a carry, add a new node
				carry = 0; // Reset carry as it's handled
			}
			curr = curr->next; // Move to the next node
		}

		// Step 3: Reverse the list back to original order
		prev = nullptr;
		curr = head;
		while (curr != nullptr){
			ListNode* nextTemp = curr->next;
			curr->next = prev;
			prev = curr;
			curr = nextTemp;
		}
		return prev; // Return the new head of the list
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

	// Approach 1: Use the plusOne function to add one to the linked list
	auto* newHead = MyLinkedList::plusOne(head);
	cout << "Linked List after adding one: ";
	MyLinkedList::printList(newHead);


	// Reset the list to original for the second approach
	head = MyLinkedList::buildList(a);

	// Approach 2: Use the plusOneReverse function to add one to the linked list
	auto* newHeadReverse = MyLinkedList::plusOneReverse(head);
	cout << "Linked List after adding one (using reverse method): ";
	MyLinkedList::printList(newHeadReverse);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}