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
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
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
};

void solve(){
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cout << fixed << setprecision(10);

	// Multi-test case support (commented out for this demo)
	// int TC = 1;
	// cin >> TC;
	// while (TC--) solve();

	solve();
	return 0;
}
