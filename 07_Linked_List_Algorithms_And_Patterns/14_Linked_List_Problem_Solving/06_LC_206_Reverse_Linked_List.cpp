/*
Author: Sarvan Yaduvanshi
Created : 2026-10-18 18:37:22
*/

/*
 * Problem: Reverse Linked List (Leetcode 206)
 * Given the head of a singly linked list, reverse the list, and return the reversed list.
 *
 * Example 1:
 * Input: head = [1,2,3,4,5] => 1 -> 2 -> 3 -> 4 -> 5
 * Output: [5,4,3,2,1] => 5 -> 4 -> 3 -> 2 -> 1
 *
 * Example 2:
 * Input: head = [1,2] => 1 -> 2
 * Output: [2,1] => 2 -> 1
 *
 * Example 3:
 * Input: head = [] => nullptr
 * Output: [] => nullptr
 *
 * Constraints:
 * The number of nodes in the list is the range [0, 5000].
 * -5000 <= Node.val <= 5000
 *
 * Follow up: A linked list can be reversed either iteratively or recursively. Could you implement both?
 */


#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <random>
#include <chrono>
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
 * PATTERN 1A: Iterative Singly Linked List Reversal (The 3-Pointer Technique)
 * - Core Problem (Why 1 or 2 pointers fail):
 *   Imagine a list: [10] -> [20] -> [30] -> NULL
 *   If we stand at [10] and immediately flip its arrow backward (10->next = NULL),
 *   we break the bridge to [20]. Since a Singly Linked List only moves forward,
 *   nodes [20] and [30] are permanently lost in memory (memory leak / lost access).
 *
 * - The Idea (3 Pointers Moving in Lockstep):
 *   To reverse links in-place without extra memory, we use three pointers:
 *     1. prev     : Tracks the node BEHIND us (where curr needs to point).
 *                   Initialized to NULL (since the old head becomes the new tail).
 *     2. curr     : Tracks the node we are CURRENTLY flipping.
 *                   Initialized to head.
 *     3. nextNode : Temporarily saves the node AHEAD of us before breaking the link.
 *                   Initialized to NULL.
 *
 * - The 4-Step Dance (Repeated inside while(curr != NULL)):
 *     Step 1 [Save Future]   : nextNode = curr->next;  // Hold onto the rest of the list
 *     Step 2 [Flip Arrow]    : curr->next = prev;      // Reverse the link backward
 *     Step 3 [Advance prev]  : prev = curr;            // Move prev to current node
 *     Step 4 [Advance curr]  : curr = nextNode;        // Move curr to the saved next node
 *
 * - Visual Dry Run Snapshot:
 *   Initial : NULL    [10] -> [20] -> [30] -> NULL   (prev = NULL, curr = 10)
 *   Pass 1  : NULL <- [10]    [20] -> [30] -> NULL   (prev = 10,   curr = 20)
 *   Pass 2  : NULL <- [10] <- [20]    [30] -> NULL   (prev = 20,   curr = 30)
 *   Pass 3  : NULL <- [10] <- [20] <- [30]    NULL   (prev = 30,   curr = NULL)
 *   Result  : Loop terminates when curr == NULL. Return 'prev' as the new head ([30]).
 *
 * - Complexity Analysis:
 *   Time Complexity  : O(N) — Single pass through all N nodes.
 *   Space Complexity : O(1) — In-place reversal using only 3 pointer variables.
 */

	static Node* reverseList(Node* head){
		// Edge case: empty list or single node
		if (head == nullptr || head->next == nullptr)
			return head;

		Node* curr = head;
		Node* prev = nullptr;

		while (curr != nullptr){
			// Step 1: Save the next node before breaking the link
			Node* nextNode = curr->next;

			// Step 2: Reverse the current node's pointer
			curr->next = prev;

			// Step 3: Move prev one step forward
			prev = curr;

			// Step 4: Move curr one step forward
			curr = nextNode;
		}

		// When curr hits nullptr, prev is sitting on the new head
		return prev;
	}

/*
 * PATTERN 1B: Recursive Reversal (The Call-Stack Backtracking Technique)
 * - Core Idea (The Recursive Leap of Faith):
 *   Instead of using 3 pointers in a while-loop, we dive all the way to the
 *   last node using the recursion call stack. Once we hit the base case (the
 *   last node), we lock it in as `newHead` and flip the pointers backward one
 *   by one as the stack unwinds.
 *
 * - Key Pointer Insight (Why `head->next->next = head` works):
 *   Suppose we are at `head = [10]`, and recursion has already reversed the
 *   rest of the list `[20] <- [30]`.
 *     1. `head` is at [10].
 *     2. `head->next` is STILL pointing forward to [20]!
 *     3. Therefore, `head->next->next` means "[20]'s next pointer".
 *     4. Setting `head->next->next = head` makes [20] point back to [10]!
 *     5. Setting `head->next = NULL` breaks the old forward arrow [10] -> [20]
 *        so we don't create an infinite cycle ([10] <-> [20]).
 *
 * - The 3-Step Unwinding Dance (At every returning stack frame):
 *     Step 1 [Dive Deep]       : Node* newHead = reverseRecursive(head->next);
 *     Step 2 [Flip From Ahead] : head->next->next = head;
 *     Step 3 [Cut Old Link]    : head->next = nullptr;
 *     Step 4 [Bubble Up Head]  : return newHead;
 *
 * - Visual Unwinding Trace (10 -> 20 -> 30 -> NULL):
 *     Base Case (at 30):
 *       30->next is NULL, so return [30] as `newHead`.
 *
 *     Unwind Frame (head = 20):
 *       State before flip : [20] -> [30] -> NULL   (newHead = [30])
 *       20->next->next = 20  ==>  [30]->next = [20]
 *       20->next = NULL      ==>  [20]->next = NULL
 *       State after flip  : NULL <- [20] <- [30]   (returns newHead [30])
 *
 *     Unwind Frame (head = 10):
 *       State before flip : [10] -> [20] <- [30]   (newHead = [30])
 *       10->next->next = 10  ==>  [20]->next = [10]
 *       10->next = NULL      ==>  [10]->next = NULL
 *       State after flip  : NULL <- [10] <- [20] <- [30] (returns newHead [30])
 *
 * - Complexity:
 *   Time Complexity  : O(N) — Visits every node once on the way down/up.
 *   Space Complexity : O(N) — Call stack stores N frames (unlike O(1) iterative).
 */
	static Node* reverseRecursive(Node* head){
		// Base Case: Empty list OR we reached the last node (which becomes newHead)
		if (head == nullptr || head->next == nullptr)
			return head;

		// Step 1: Recursively reach the end of the list
		Node* newHead = reverseRecursive(head->next);

		// Step 2: Make the next node point backward to the current head
		// eg: list: 10->20->nullptr, after recursion, newHead = 20, head = 10, so head->next->next = 20->10
		head->next->next = head;

		// Step 3: Break current head's forward link to avoid a cycle
		// 20->10->nullptr, so we set 10->next = nullptr
		head->next = nullptr;

		// Step 4: Always pass the tail (newHead) up to the caller
		return newHead;
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
	int n; cin >> n;
	vector<int> values(n);
	for (int& val : values)
		cin >> val;

	auto head = ListNode::buildList(values);

	cout << "Original List: ";
	ListNode::printList(head);

	cout << "Reversed List (Iterative): ";
	head = ListNode::reverseList(head);
	ListNode::printList(head);

	// Rebuild the list for recursive reversal
	head = ListNode::buildList(values);

	cout << "Reversed List (Recursive): ";
	head = ListNode::reverseRecursive(head);
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
