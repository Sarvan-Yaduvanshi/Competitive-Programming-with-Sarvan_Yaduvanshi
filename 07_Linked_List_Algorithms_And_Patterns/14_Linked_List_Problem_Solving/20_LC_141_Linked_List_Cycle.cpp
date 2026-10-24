/*
Author: Sarvan Yaduvanshi
Created : 2026-10-23 23:53:18
*/

/*
 * ============================================================================
 *  141. Linked List Cycle
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 141
 *  Difficulty : Easy
 *  Topics     : Hash Table, Linked List, Two Pointers
 *  Companies  : Amazon, Microsoft, Google, Apple, Meta, Bloomberg, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given head, the head of a linked list, determine if the linked list has a
 *  cycle in it.
 *
 *  There is a cycle in a linked list if there is some node in the list that
 *  can be reached again by continuously following the next pointer.
 *  Internally, pos is used to denote the index of the node that tail's next
 *  pointer is connected to. Note that pos is not passed as a parameter.
 *
 *  Return true if there is a cycle in the linked list. Otherwise, return
 *  false.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      3 -> 2 -> 0 -> -4
 *           ^___________|
 *
 *  Input  : head = [3,2,0,-4], pos = 1
 *  Output : true
 *  Explanation: There is a cycle in the linked list, where the tail connects
 *               to the 1st node (0-indexed).
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      1 -> 2
 *      ^____|
 *
 *  Input  : head = [1,2], pos = 0
 *  Output : true
 *  Explanation: There is a cycle in the linked list, where the tail connects
 *               to the 0th node.
 *
 * ----------------------------------------------------------------------------
 *  Example 3:
 *
 *      1 -> NULL
 *
 *  Input  : head = [1], pos = -1
 *  Output : false
 *  Explanation: There is no cycle in the linked list.
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of the nodes in the list is in the range [0, 10^4].
 *      - -10^5 <= Node.val <= 10^5
 *      - pos is -1 or a valid index in the linked-list.
 *
 * ----------------------------------------------------------------------------
 *  Follow up: Can you solve it using O(1) (i.e. constant) memory?
 * ============================================================================
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
#include <unordered_set>
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
 * SLOW & FAST PATTERN 3: 141. Linked List Cycle (Optimal O(N) Time | O(1) Space)
 * ============================================================================
 *
 * - Core Idea (Floyd's Tortoise and Hare Algorithm) or (Floyd's Cycle Finding Algorithm):
 *   Start both `slow` and `fast` at `head`.
 *     - `slow` moves 1 step  (`slow = slow->next`)
 *     - `fast` moves 2 steps (`fast = fast->next->next`)
 *   - If there is NO cycle: `fast` hits `nullptr` (or `fast->next == nullptr`)
 *     and we return `false`.
 *   - If there IS a cycle: `fast` enters the loop first and eventually laps
 *     `slow` from behind (`slow == fast`), so we return `true`!
 *
 * - Mathematical Proof (Why `fast` NEVER Skips Over `slow`):
 *   Once both pointers are inside the cycle, suppose `fast` is `G` steps
 *   behind `slow`.
 *   In each turn, `slow` moves +1 and `fast` moves +2.
 *   Relative change in gap = G + 1 - 2 = G - 1.
 *   Since the gap decreases by EXACTLY 1 step every iteration
 *   (G -> G-1 -> ... -> 2 -> 1 -> 0), `fast` can NEVER jump over `slow`!
 *   They are guaranteed to collide before `slow` even completes 1 full lap.
 *
 * - Quick Dry Run: [1] -> [2] -> [3] -> [4] -> (points back to [2])
 *     Init   : slow = [1], fast = [1]
 *     Step 1 : slow = [2], fast = [3]  (Gap from fast[3] behind slow[2] in loop = 2 steps)
 *     Step 2 : slow = [3], fast = [2]  (Gap from fast[2] behind slow[3] in loop = 1 step)
 *     Step 3 : slow = [4], fast = [4]  (Gap = 0 -> `slow == fast`! Return `true`!)
 *
 * - Complexity:
 *   Time  : O(N) — At most N steps to enter cycle + at most CycleLength steps to meet.
 *   Space : O(1) — Only 2 pointers used in-place (vs. O(N) for Hash Set).
 * ============================================================================
 */

	static bool hasCycle(ListNode *head){
		// Edge case: empty list or single node with no cycle
		if (head == nullptr || head->next == nullptr)
			return false;

		ListNode* slow = head;
		ListNode* fast = head;

		// Move `slow` by 1 and `fast` by 2
		while (fast != nullptr && fast->next != nullptr){
			slow = slow->next;
			fast = fast->next->next;

			// If `slow` and `fast` meet, a cycle exists
			if (slow == fast)
				return true;
		}

		// `fast` reached the end of the list -> No cycle exists
		return false;
	}
	// Test function to build a linked list from a vector of integers
	static ListNode* buildList(const vector<int>& a, const int pos) {
		if (a.empty())
			return nullptr;

		ListNode* head = new ListNode(a[0]);
		ListNode* tail = head;

		// Build the normal linked list
		vector<ListNode*> nodes;
		nodes.push_back(head);

		for (int i = 1; i < a.size(); i++) {
			tail->next = new ListNode(a[i]);
			tail = tail->next;
			nodes.push_back(tail);
		}

		// Connect the last node to the node at index pos
		if (pos >= 0 && pos < (int)nodes.size()) {
			tail->next = nodes[pos];
		}

		return head;
	}

	// Test function to print the linked list (handles cycles)
	static void printList(ListNode* head) {
		if (head == nullptr) {
			cout << "Empty List\n";
			return;
		}

		unordered_set<ListNode*> visited;
		ListNode* current = head;

		while (current != nullptr) {
			// Detect revisiting a node
			if (visited.count(current)) {
				cout << "(cycle to node with value "
					 << current->val << ")\n";
				return;
			}

			visited.insert(current);
			cout << current->val;

			current = current->next;

			if (current != nullptr)
				cout << " -> ";
		}

		cout << " -> nullptr\n";
	}
};

static void solve(){
	int n;
	cout << "Enter the number of nodes in the linked list: ";
	cin >> n;

	int pos;
	cout << "Enter the position to create a cycle (-1 for no cycle): ";
	cin >> pos;

	cout << "Enter the values of the nodes: ";
	vector<int> a(n);
	for (int& x : a)
		cin >> x;

	auto* head = MyLinkedList::buildList(a, pos);
	cout << "Linked List: ";
	MyLinkedList::printList(head);

	// Check for cycle
	bool has_cycle = MyLinkedList::hasCycle(head);
	if (has_cycle)
		cout << "The linked list has a cycle.\n";
    else
        cout << "The linked list does not have a cycle.\n";

}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}
