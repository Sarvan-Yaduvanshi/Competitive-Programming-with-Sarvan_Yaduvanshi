/*
Author: Sarvan Yaduvanshi
Created : 2026-10-18 21:24:39
*/

/*
 * Problem: Reverse Linked List II (LeetCode 92)
 * Difficulty: Medium, Topic: Linked List, Two Pointers
 * Company: Amazon, Microsoft, Google, Facebook, Apple, Adobe, etc. (Very important because 100+ companies asked this question)
 * Given the head of a singly linked list and two integers left and right where left <= right,
 * reverse the nodes of the list from position left to position right, and return the reversed list.
 *
 * Example 1:
 * Input: head = [1,2,3,4,5], left = 2, right = 4
 * Output: [1,4,3,2,5]
 * Explanation: Before the reversal, the list is 1->2->3->4->5. After reversing from position 2 to 4, the list becomes 1->4->3->2->5.
 *
 * Example 2:
 * Input: head = [5], left = 1, right = 1
 * Output: [5]
 * Explanation: The list has only one node, so reversing it does not change the list.
 *
 * Constraints:
 * The number of nodes in the list is n.
 * 1 <= n <= 500
 * -500 <= Node.val <= 500
 * 1 <= left <= right <= n
 * Follow up: Could you do it in one pass?
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

class ListNode{
private:
	struct Node{
        int val;
        Node* next;
        explicit Node(const int val) : val(val), next(nullptr) {}
    };

	Node* head;

public:
	ListNode() : head(nullptr) {}

 /*
 * PATTERN 3: Reverse a Sublist Between `left` and right (LeetCode 92)
 * - Problem Statement:
 *   Given a Singly Linked List and two 1-based positions left and right,
 *   reverse only the nodes from position left to right in one pass O(N)
 *   and in-place O(1) space.
 *   Example: 10 -> 20 -> 30 -> 40 -> 50, left = 2, right = 4
 *   Output : 10 -> 40 -> 30 -> 20 -> 50
 *
 * - Why We Need a dummy Node:
 *   If left == 1, the original head of the list is part of the reversal,
 *   meaning the overall head will change and there is no node before left.
 *   Creating dummy -> head guarantees there is ALWAYS a node before left
 *   (beforeLeft), eliminating messy if (left == 1) edge-case branches.
 *
 * - The 4-Phase Surgical Plan:
 *     Phase 1 [Walk to Anchor] :
 *       Start `beforeLeft` at `dummy` and move it `left - 1` steps forward.
 *       Now `beforeLeft` sits right before the sublist (`[10]`), and
 *       `beforeLeft->next` is the start of our sublist (`[20]`).
 *
 *     Phase 2 [Save Sublist Tail] :
 *       `sublistTail = beforeLeft->next;` (Node [20]).
 *       Since [20] is the FIRST node of the sublist now, it will become the
 *       LAST node (tail) of the sublist after reversal!
 *
 *     Phase 3 [Standard 3-Pointer Reversal for (right - left + 1) nodes] :
 *       Run our exact Pattern 1A 4-step dance right - left + 1 times.
 *       When this loop finishes:
 *         - `prev` sits on the NEW head of the reversed sublist ([40]).
 *         - `curr` sits on the first node AFTER the sublist ([50]).
 *
 *     Phase 4 [Re-Stitch the 2 Broken Ends] :
 *       1. Connect left anchor to new sublist head : beforeLeft->next = prev;
 *          ([10]->next = [40])
 *       2. Connect new sublist tail to right rest  : `sublistTail->next = curr;
 *          ([20]->next = [50])
 *
 * - Visual Stitch Trace:
 *     Original   : [dummy] -> [10] -> [20] -> [30] -> [40] -> [50] -> NULL
 *                             ^       ^
 *                         beforeLeft sublistTail
 *
 *     After Loop : [10]    NULL <- [20] <- [30] <- [40]    [50] -> NULL
 *                   ^              ^               ^       ^
 *               beforeLeft    sublistTail         prev    curr
 *
 *     Re-Stitch  : [10]->next = prev ([40])
 *                  [20]->next = curr ([50])
 *     Result     : [dummy] -> [10] -> [40] -> [30] -> [20] -> [50] -> NULL
 *
 * - Complexity:
 *   Time Complexity  : O(N) — Single pass up to position right.
 *   Space Complexity : O(1) — In-place pointer manipulation.
 */
	static Node* reverseBetween(Node* head, const int left, const int right){
		// Edge case: empty list, single node, or no reversal needed
		if (head == nullptr || left == right)
			return head;

		// Create a dummy node on the stack to handle left == 1 smoothly
		Node dummy(0);
		dummy.next = head;

		// Phase 1: Move `beforeLeft` to the node just before position `left`
		Node* before_left = &dummy;
		for (int i = 1; i < left; i++)
			before_left = before_left->next;

		// Phase 2: Lock in `sublistTail` (the node at `left`, which becomes tail after reversal)
		Node* sublist_tail = before_left->next;

		// Phase 3: Reverse exactly (right - left + 1) nodes using Pattern 1A
		Node* prev = nullptr;
		Node* curr = sublist_tail;
		int total_node_to_rev = right - left + 1;
		for (int i = 0; i < total_node_to_rev; i++){
			Node* next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}

		// Phase 4: Stitch the reversed sublist back into the main list
		before_left->next = prev; // Connect node before `left` to new sublist head
		sublist_tail->next = curr; // Connect reversed sublist's tail to node after `right`

		return dummy.next;
	}
	// Build a linked list from a array of values
	static Node* buildList(const vector<int>& values){
		if (values.empty())
			return nullptr;

		Node* head = new Node(values[0]);
		Node* curr = head;

		for (size_t i = 1; i < values.size(); ++i){
			curr->next = new Node(values[i]);
			curr = curr->next;
		}

		return head;
	}

	// Print the linked list
	static void printList(Node* head){
		Node* curr = head;
		while (curr != nullptr){
			cout << curr->val;
			if (curr->next != nullptr)
				cout << " -> ";
			curr = curr->next;
		}
		cout << " -> nullptr" << endl;
	}
};
static void solve(){
	int n, left, right;
	cout << "Enter the number of nodes in the linked list: ";
	cin >> n;
	cout << "Enter the left and right positions for reversal (1-based index): ";
	cin >> left >> right;

	vector<int> values(n);
	cout << "Enter the values of the linked list nodes: ";
	for (int& val : values)
		cin >> val;

	auto head = ListNode::buildList(values);

	cout << "Original List: ";
	ListNode::printList(head);

	head = ListNode::reverseBetween(head, left, right);
	cout << "Reversed List (from position " << left << " to " << right << "): ";
    ListNode::printList(head);
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
