/*
Author: Sarvan Yaduvanshi
Created : 2026-10-25 10:22:45
*/

/*
 * ============================================================================
 *  86. Partition List
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 86
 *  Difficulty : Medium
 *  Topics     : Linked List, Two Pointers
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the head of a linked list and a value x, partition it such that all
 *  nodes less than x come before nodes greater than or equal to x.
 *
 *  You should preserve the original relative order of the nodes in each of
 *  the two partitions.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      Before :  1 -> 4 -> 3 -> 2 -> 5 -> 2
 *      x = 3
 *      After  :  1 -> 2 -> 2 -> 4 -> 3 -> 5
 *                (< 3)          (>= 3)
 *
 *  Input  : head = [1,4,3,2,5,2], x = 3
 *  Output : [1,2,2,4,3,5]
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      Before :  2 -> 1
 *      x = 2
 *      After  :  1 -> 2
 *                (< 2)  (>= 2)
 *
 *  Input  : head = [2,1], x = 2
 *  Output : [1,2]
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in the list is in the range [0, 200].
 *      - -100 <= Node.val <= 100
 *      - -200 <= x <= 200
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
	 * Approach: Stable Partition Using One Linked-List Chain and a Vector
	 *
	 * The required partition has two groups:
	 *   1. Nodes with values less than x.
	 *   2. Nodes with values greater than or equal to x.
	 *
	 * The relative order inside both groups must remain unchanged. To preserve
	 * that order, traverse the original list from left to right:
	 *   - Append every node with value < x immediately to the result chain.
	 *   - Store every node with value >= x in a vector.
	 *
	 * After the traversal, append the stored nodes to the end of the result
	 * chain in the same order in which they were encountered.
	 *
	 * The dummy node makes the first insertion into the result list simple:
	 * `dummy.next` will become the new head of the partitioned list.
	 *
	 * It is important to save `head->next` before changing links. This allows
	 * the traversal to continue safely even though nodes are being relinked.
	 *
	 * Dry run:
	 *
	 *   Input list: 1 -> 4 -> 3 -> 2 -> 5 -> 2 -> nullptr
	 *   x = 3
	 *
	 *   Start:
	 *     less-than-x list = empty
	 *     stored list      = empty
	 *
	 *   Process each node:
	 *     1 < 3  -> append to result: 1
	 *     4 >= 3 -> store:            [4]
	 *     3 >= 3 -> store:            [4, 3]
	 *     2 < 3  -> append to result: 1 -> 2
	 *     5 >= 3 -> store:            [4, 3, 5]
	 *     2 < 3  -> append to result: 1 -> 2 -> 2
	 *
	 *   Append stored nodes:
	 *     1 -> 2 -> 2 -> 4 -> 3 -> 5 -> nullptr
	 *
	 *   Notice that:
	 *     - All values < 3 come before values >= 3.
	 *     - The order 1, 2, 2 is preserved.
	 *     - The order 4, 3, 5 is preserved.
	 *
	 * Complexity:
	 *   Let n be the number of nodes in the linked list.
	 *   - Time: O(n). The list is traversed once and the vector is traversed
	 *           once to append the second partition.
	 *   - Space: O(n) in the worst case because the vector can store all nodes
	 *            when every node has a value >= x.
	 */
	static ListNode* partitionUseVector(ListNode* head, const int x){
		// Lists with zero or one node are already partitioned.
		if (head == nullptr || head->next == nullptr)
			return head;

		// Dummy node simplifies construction of the result list.
		ListNode dummy(0);
		ListNode* tail = &dummy;

		// Store the nodes belonging to the second partition.
		vector<ListNode*> greater_than_node_val_x;

		while (head != nullptr){
			// Save the next node before relinking the current node.
			ListNode* nextNode = head->next;
			if (head->val < x){
				// Append nodes smaller than x immediately.
				tail->next = head;
				tail = tail->next;
			} else{
				// Keep >= x nodes in their original order for later.
				greater_than_node_val_x.emplace_back(head);
			}

			head = nextNode;
		}

		// Append the >= x partition after all nodes smaller than x.
		for (ListNode* node : greater_than_node_val_x){
			tail->next = node;
			tail = tail->next;
		}

		// Terminate the list to remove any old links from the original list.
		tail->next = nullptr;
		return dummy.next;
	}

	/*
 * ============================================================================
 * MERGE & SORT PATTERN 2A: 86. Partition List (Optimal O(N) Time | O(1) Space)
 * ============================================================================
 *
 * - Core Idea (The 2-Bucket Dummy-Tail Engine):
 *   Instead of swapping nodes in-place (which is messy and breaks relative order),
 *   create TWO separate `dummy + tail` builders on the stack:
 *     1. `lessDummy`    & `lessTail`    : Collects all nodes with `val < x`.
 *     2. `greaterDummy` & `greaterTail` : Collects all nodes with `val >= x`.
 *
 * - The 3-Phase Execution:
 *     Phase 1 [Route Each Node Into Its Bucket] :
 *       Walk `head` through the list:
 *         - If `head->val < x` : attach to `lessTail->next`, advance `lessTail`.
 *         - Else               : attach to `greaterTail->next`, advance `greaterTail`.
 *         - Advance `head = head->next`.
 *
 *     Phase 2 [CRITICAL: Cut Old Forward Link on `greaterTail`] :
 *       Set `greaterTail->next = nullptr;`!
 *       Why? The last node placed in the `greater` bucket might still have its
 *       original `next` pointer pointing to a smaller node that came after it
 *       (e.g., [5]->next pointing to [2]), which would create an infinite cycle!
 *
 *     Phase 3 [Connect Bucket 1 to Bucket 2] :
 *       Point `lessTail->next = greaterDummy.next` and return `lessDummy.next`.
 *
 * - Quick Dry Run: head = [1 -> 4 -> 3 -> 2 -> 5 -> 2], x = 3
 *     After Phase 1 (Routing):
 *       lessDummy    -> [1] -> [2] -> [2]  (lessTail sits at 2nd [2])
 *       greaterDummy -> [4] -> [3] -> [5]  (greaterTail sits at [5], whose `next`
 *                                           is STILL pointing to the 2nd [2]!)
 *     Phase 2 (Cut Cycle):
 *       `greaterTail->next = nullptr;`     ([5]->next becomes nullptr)
 *     Phase 3 (Connect):
 *       `lessTail->next = greaterDummy.next;` (2nd [2]->next connects to [4])
 *       Final: [1] -> [2] -> [2] -> [4] -> [3] -> [5] -> nullptr
 *
 * - Complexity:
 *   Time  : O(N) — Single pass through all N nodes.
 *   Space : O(1) — Rewires existing nodes in-place using 2 stack dummy nodes.
 * ============================================================================
 */
	static ListNode* partition(ListNode* head, const int x){
		// Create two separate Dummy-Tail builders on the stack
		ListNode lessDummy(0);
		ListNode greaterDummy(0);

		ListNode* lessTail = &lessDummy;
		ListNode* greaterTail = &greaterDummy;

		// Phase 1: Traverse the original list until all nodes are processed
		while (head != nullptr){
			// Save the next node before relinking the current node.
			ListNode* nextNode = head->next;

			// Case 1: Node value is less than x, append to the `< x` list
			if (head->val < x){
				lessTail->next = head;
				lessTail = lessTail->next;

			// Case 2: Node value is greater than or equal to x, append to the `>= x` list
			} else{
				greaterTail->next = head;
				greaterTail = greaterTail->next;
			}

			// Assign the saved next node to continue traversal
			head = nextNode;
		}

		// Phase 2: CRITICAL — Terminate the `greater` list to prevent a cycle!
		greaterTail->next = nullptr;

		// Phase 3: Connect the tail of `< x` list to the head of `>= x` list
		lessTail->next = greaterDummy.next;

		return lessDummy.next;  // Return the head of the new partitioned list
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

	int x;
	cout << "Enter the partition value x: ";
	cin >> x;

	cout << "Enter the values of the nodes: ";
	vector<int> a(n);
	for (int& x : a)
		cin >> x;

	auto* head = MyLinkedList::buildList(a);
	cout << "Original Linked List: ";
	MyLinkedList::printList(head);

	// Partition the list using the optimal O(N) time and O(1) space approach
	head = MyLinkedList::partition(head, x);
	cout << "Partitioned Linked List (x = " << x << "): ";
	MyLinkedList::printList(head);

	// Partition the list using the vector-based approach
	head = MyLinkedList::buildList(a);  // Rebuild the original list
	head = MyLinkedList::partitionUseVector(head, x);
	cout << "Partitioned Linked List using Vector (x = " << x << "): ";
	MyLinkedList::printList(head);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}