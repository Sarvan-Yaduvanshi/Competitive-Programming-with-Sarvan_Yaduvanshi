/*
Author: Sarvan Yaduvanshi
Created : 2026-10-20 19:57:57
*/

/*
  Problem: Palindrome Linked List (LeetCode 234)
  Given the head of a singly linked list, return true if it is a palindrome or false otherwise.

    Example 1:
    Input: head = [1,2,2,1]
    Output: true
    Explanation: The linked list is 1->2->1, which is a palindrome. because it reads the same forwards and backwards.

    Example 2:
    Input: head = [1,2]
    Output: false
    Explanation: The linked list is 1->2, which is not a palindrome. because it does not read the same forwards and backwards.

    Constraints:
		The number of nodes in the list is in the range [1, 10^5].
		0 <= Node.val <= 9
		Follow up: Could you do it in O(n) time and O(1) space?
*/

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;

class MyLinkedList{
private:
	struct ListNode{
		int val;
        ListNode* next;
        explicit ListNode(const int val) : val(val), next(nullptr) {}
	};

	ListNode* head;

public:
	MyLinkedList() : head(nullptr) {};

 /*
 * ============================================================================
 * PATTERN 6A: 234. Palindrome Linked List (Approach 1: Iterative (3-Phase Middle + Reverse + Two-Pointer Comparison))
 * ============================================================================
 * - Core Idea (The 3-Phase Half-Reversal Blueprint):
 *   Since we cannot move backward from the tail of a Singly Linked List, we
 *   reverse the SECOND half of the list in-place and compare it with the
 *   FIRST half!
 *
 * - The 3-Phase Execution:
 *     Phase 1 [Find the End of the First Half (Slow & Fast Pointers)] :
 *       Start `slow = head` and `fast = head`.
 *       Loop while `fast->next != nullptr && fast->next->next != nullptr`.
 *       When the loop ends, `slow` sits at the end of the 1st half, and
 *       `slow->next` is the first node of the 2nd half!
 *
 *     Phase 2 [Reverse the Second Half (Pattern 1A)] :
 *       Run our standard 3-pointer reversal (`prev`, `curr`, `next`) starting
 *       at `curr = slow->next`.
 *       When finished, `prev` points to the head of the reversed 2nd half.
 *
 *     Phase 3 [Compare Both Halves] :
 *       Set `firstHalf = head` and `secondHalf = prev`.
 *       Walk both forward while `secondHalf != nullptr`.
 *       If `firstHalf->val != secondHalf->val`, return `false`!
 *
 * - Visual Trace (head = [1, 2, 3, 2, 1] - Odd Length):
 *     Phase 1 (Find Middle):
 *       [1] -> [2] -> [3] -> [2] -> [1] -> nullptr
 *                      ^             ^
 *                    slow          fast
 *       (`slow->next` is the second [2], where the 2nd half starts!)
 *
 *     Phase 2 (Reverse 2nd Half starting from `slow->next`):
 *       1st Half : [1] -> [2] -> [3]
 *       2nd Half : [1] -> [2] -> nullptr   (`prev` sits on [1])
 *
 *     Phase 3 (Compare `firstHalf` and `secondHalf`):
 *       - Step 1: firstHalf ([1]) == secondHalf ([1]) (Match!)
 *       - Step 2: firstHalf ([2]) == secondHalf ([2]) (Match!)
 *       - Step 3: `secondHalf` hits nullptr -> Loop ends! Return `true`!
 *       (Notice the middle node [3] in an odd-length list doesn't even need
 *        to be checked because `secondHalf` hits nullptr right before it!)
 *
 * - Complexity:
 *   Time  : O(N) — Find middle O(N/2) + Reverse O(N/2) + Compare O(N/2).
 *   Space : O(1) — Pure in-place pointer manipulation (no stack/vector used).
 * ============================================================================
 */
	static bool isPalindrome(ListNode* head){
		// Handle edge cases: empty list or single node list is always a palindrome
		if (head == nullptr || head->next == nullptr)
			return true;

		// Phase 1: Find the end of the first half using Slow and Fast pointers
		ListNode* slow = head;
		ListNode* fast = head;

		while (fast->next != nullptr && fast->next->next != nullptr){
			slow = slow->next;
			fast = fast->next->next;
		}

		// Phase 2: Reverse the second half starting at `slow->next` (Pattern 1A)
		ListNode* current = slow->next;
		ListNode* previous = nullptr;
		while (current != nullptr){
			ListNode* nextNode = current->next;
            current->next = previous;
            previous = current;
            current = nextNode;
		}

		// Phase 3: Compare the first half and the reversed second half
		ListNode* firstHalf = head;
		ListNode* secondHalf = previous; // `prev` is the head of the reversed 2nd half
		while (secondHalf != nullptr){
			if (firstHalf->val != secondHalf->val)
				return false;
			firstHalf = firstHalf->next;
			secondHalf = secondHalf->next;
		}

		return true;
	}

	// Follow-up: Restore the original list structure after checking for palindrome
	// Time Complexity: O(N), Space Complexity: O(1)
	static bool isPalindromeLinkedList(ListNode* head){
		// Handle edge cases: empty or single node
		if (head == nullptr || head->next == nullptr)
			return true;

		ListNode* slow = head;
		ListNode* fast = head;

		// Phase 1: Find the end of the first half using Slow and Fast pointers
		while (fast->next != nullptr && fast->next->next != nullptr){
			slow = slow->next;
			fast = fast->next->next;
		}

		// Phase 2: Reverse the second half starting at `slow->next`
		ListNode* current = slow->next;
		ListNode* previous = nullptr;
		while (current != nullptr){
			ListNode* next = current->next;
			current->next = previous;
			previous = current;
			current = next;
		}

		// Phase 3: Compare the first half and the reversed second half
		ListNode* firstHalf = head;
		ListNode* secondHalf = previous;
		bool isPalindrome = true; // Assume the list is a palindrome until proven otherwise
		while (secondHalf != nullptr){
			if (firstHalf->val != secondHalf->val){
				isPalindrome = false; // Not a palindrome
				break; // Exit the loop early since we found a mismatch
			}
			firstHalf = firstHalf->next;
			secondHalf = secondHalf->next;
		}

		// Phase 4: Restore the original list structure by reversing the second half back
		current = previous; // Start from the head of the reversed second half
		previous = nullptr;
		while (current != nullptr){
			ListNode* next = current->next;
			current->next = previous;
			previous = current;
			current = next;
		}

		// Reconnect the first half with the restored second half
		slow->next = previous; // `previous` is now the head of the restored second half

		return isPalindrome; // Return whether the list is a palindrome or not
	}

	// Additional utility function to print the linked list (for debugging purposes)
	static void printList(ListNode* head){
		if (head == nullptr){
			cout << "Empty List" << endl;
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

	// Build a linked list from a vector of integers (for testing purposes)
	static ListNode* buildList(const vector<int>& a){
		if (a.empty())
			return nullptr;

		ListNode* head = new ListNode(a[0]);
		ListNode* tail = head;
		for (int i = 1; i < a.size(); i++){
			tail->next = new ListNode(a[i]);
			tail = tail->next;
		}

		return head;
	}
};

static void solve(){
	int n;
	cout << "Enter the number of nodes in the linked list: ";
	cin >> n;

	vector<int> a(n);
	cout << "Enter the values of the nodes: ";
	for (int& x : a)
		cin >> x;

	auto* head = MyLinkedList::buildList(a);
	cout << "Original Linked List: ";
	MyLinkedList::printList(head);

	// Method 1: Check if the linked list is a palindrome without restoring the original structure
	bool isPalin = MyLinkedList::isPalindrome(head);
	cout << "Is the linked list a palindrome? " << (isPalin ? "Yes" : "No") << endl;
	cout << "Linked List after checking: (may be modified or incomplete) ";
	MyLinkedList::printList(head);

	// rebuild the list again for the second method since the first method modifies it
	head = MyLinkedList::buildList(a);

	// Method 2: Check if the linked list is a palindrome and restore the original structure
	bool isPalinRestored = MyLinkedList::isPalindromeLinkedList(head);
	cout << "Is the linked list a palindrome (with restoration)? " << (isPalinRestored ? "Yes" : "No") << endl;
	cout << "Linked List after restoration (if modified): ";
	MyLinkedList::printList(head);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}
