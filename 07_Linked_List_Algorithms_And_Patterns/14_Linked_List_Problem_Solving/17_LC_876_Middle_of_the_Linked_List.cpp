/*
Author: Sarvan Yaduvanshi
Created : 2026-10-03 21:13:52
*/

/*
  Problem: Middle of the Linked List (Leetcode 876)
    Given the head of a singly linked list, return the middle node of the linked list.
    If there are two middle nodes, return the second middle node.

    Example 1:
    Input: head = [1,2,3,4,5],  1 -> 2 -> 3 -> 4 -> 5
    Output: [3,4,5],  3 -> 4 -> 5
    Explanation: The middle node of the list is node 3.

    Example 2:
    Input: head = [1,2,3,4,5,6], 1 -> 2 -> 3 -> 4 -> 5 -> 6
    Output: [4,5,6],  4 -> 5 -> 6
    Explanation: Since the list has two middle nodes with values 3 and 4, we return the second one.

    Constraints:
       The number of nodes in the list is in the range [1, 100].
       1 <= Node.val <= 100
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
	MyLinkedList() : head(nullptr) {}

 /*
 * ============================================================================
 * SLOW & FAST PATTERN 1: 876. Middle of the Linked List (O(N) Time | O(1) Space)
 * ============================================================================
 *
 * - Core Idea (2x Speed Ratio):
 *   Start both `slow` and `fast` at `head`.
 *     - `slow` moves 1 step  (`slow = slow->next`)
 *     - `fast` moves 2 steps (`fast = fast->next->next`)
 *   When `fast` reaches the end, `slow` is at the exact halfway mark!
 *
 * - PRO CP RULE: Controlling 1st Middle vs. 2nd Middle in Even Lists:
 *   Suppose the list is Even: [10] -> [20] -> [30] -> [40] -> nullptr
 *
 *     Case A: Need the 2ND Middle ([30] - Required by LeetCode 876):
 *       Condition: `while (fast != nullptr && fast->next != nullptr)`
 *       `fast` jumps all the way to `nullptr`, pushing `slow` 1 step further to [30].
 *
 *     Case B: Need the 1ST Middle ([20] - Required for Splitting/MergeSort/Reorder):
 *       Condition: `while (fast->next != nullptr && fast->next->next != nullptr)`
 *       `fast` stops early on the 2nd-to-last node, keeping `slow` at [20].
 *
 * - Why Order Inside `while (fast != nullptr && fast->next != nullptr)` Matters:
 *   We MUST check `fast != nullptr` FIRST! If `fast` is already `nullptr`,
 *   checking `fast->next` first will cause a Segmentation Fault (Null Pointer Crash).
 *
 * - Visual Dry Run:
 *     1. Odd List: [1] -> [2] -> [3] -> [4] -> [5] -> nullptr
 *        Start : slow = [1], fast = [1]
 *        Step 1: slow = [2], fast = [3]
 *        Step 2: slow = [3], fast = [5]
 *        End   : `fast->next` is nullptr -> Loop stops! Returns `slow` ([3]).
 *
 *     2. Even List: [1] -> [2] -> [3] -> [4] -> nullptr
 *        Start : slow = [1], fast = [1]
 *        Step 1: slow = [2], fast = [3]
 *        Step 2: slow = [3], fast = nullptr
 *        End   : `fast` is nullptr -> Loop stops! Returns `slow` ([3] - 2nd Middle).
 *
 *   Note: A super common question in interviews is: "Why do we need BOTH fast != nullptr AND fast->next != nullptr in the while condition?"
 *        Answer: fast != nullptr catches Even lists, and
 *                fast->next != nullptr catches Odd lists?
 *                Together, those two checks guarantee fast->next->next is always 100% safe from crashing!
 *
 * - Complexity:
 *   Time  : O(N) — `fast` traverses N nodes in N/2 iterations.
 *   Space : O(1) — Only 2 pointers used in-place.
 * ============================================================================
 */
	static ListNode* middleNode(ListNode* head){
		ListNode* slow = head;
		ListNode* fast = head;
		// Move `slow` by 1 step and `fast` by 2 steps until `fast` hits the end
		while (fast != nullptr && fast->next != nullptr){
			slow = slow->next; // slow moves 1 step
			fast = fast->next->next; // fast moves 2 steps
		}

		return slow; // `slow` is now sitting on the middle node (or 2nd middle if even length)
	}

	// Function to build a linked list from a vector of integers
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

	// Function to print the linked list
	static void printList(ListNode* head){
		if (!head){
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
	cout << "Original List: ";
	MyLinkedList::printList(head);

	auto* middle = MyLinkedList::middleNode(head);
	cout << "Middle Node Value: " << middle->val << "\n";
	cout << "Middle List: ";
	MyLinkedList::printList(middle);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	solve();
	return 0;
}
