/*
Author: Sarvan Yaduvanshi
Created : 2026-10-19 02:45:37
*/

/*
 * Problem: Reverse Nodes in k-Group (LeetCode 25)
 * Difficulty: Hard, Topic: Linked List, Two Pointers, Recursion
 * Company: Amazon, Microsoft, Google, Facebook, Apple, Adobe, etc. (Very important because 100+ companies asked this question)
 * Given the head of a linked list, reverse the nodes of the list k at a time, and return the modified list.
 * k is a positive integer and is less than or equal to the length of the linked list.
 * If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.
 * You may not alter the values in the list's nodes, only nodes themselves may be changed.
 *
 * Example 1:
 * Input: head = [1,2,3,4,5], k = 2
 * Output: [2,1,4,3,5]
 * Explanation: The list is reversed in groups of 2. The first group (1,2) becomes (2,1), the second group (3,4) becomes (4,3), and the last node (5) remains as it is.
 *              First group: 1->2 becomes 2->1, Second group: 3->4 becomes 4->3, Last node: 5 remains as it is. output: 2->1->4->3->5
 *
 * Example 2:
 * Input: head = [1,2,3,4,5], k = 3
 * Output: [3,2,1,4,5]
 * Explanation: The list is reversed in groups of 3. The first group (1,3) becomes (3,2,1), and the last two nodes (4,5) remain as they are.
 *             First group: 1->2->3 becomes 3->2->1, Last two nodes: 4->5 remain as they are. output: 3->2->1->4->5
 *
 * Constraints:
 *       The number of nodes in the list is n.
 *       1 <= n <= 5000
 *       0 <= Node.val <= 1000
 *       1 <= k <= n
 * Follow up: Can you solve the problem in O(1) extra memory space?
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <random>
#include <chrono>

using namespace std;

class myLinkedList{
private:
	struct ListNode{
		int val;
        ListNode* next;
        explicit ListNode(const int val) : val(val), next(nullptr) {}
	};

	ListNode* head;

public:
	myLinkedList() : head(nullptr) {}

 /*
 * PATTERN 4: Reverse Nodes in K-Group (LeetCode 25 - Hard)
 * ============================================================================
 * - Core Idea (Pattern 3 Repeated in a Loop):
 *   In Pattern 3, we reversed one middle part of a list. Here, we do the
 *   exact same thing repeatedly for every group of `k` nodes:
 *     1. `groupPrev` : Points to the node right BEFORE the current k-group
 *                      (starts at `dummy`).
 *     2. `groupHead` : Points to the FIRST node of the current k-group
 *                      (`groupPrev->next`). After reversal, this node
 *                      becomes the LAST node (tail) of the reversed group!
 *
 * - The 4-Phase Loop (Repeated until fewer than K nodes remain):
 *     Phase 1 [Check if K Nodes Exist] :
 *       Start a pointer `kth` at `groupPrev` and move it `k` steps forward.
 *       If `kth == nullptr` along the way, fewer than `k` nodes are left.
 *       We do not reverse them -> return `dummy.next` immediately!
 *
 *     Phase 2 [Reverse K Nodes (Pattern 1A)] :
 *       Save `groupHead = groupPrev->next`.
 *       Run the standard 3-pointer reversal (`prev`, `curr`, `next`) `k` times.
 *       When the loop finishes:
 *         - `prev` is the NEW first node (head) of this reversed group.
 *         - `curr` is the first node of the NEXT untouched group.
 *         - `groupHead` is now at the END (tail) of this reversed group.
 *
 *     Phase 3 [Reconnect the Reversed Group into the Main List] :
 *       1. `groupPrev->next = prev;` (Connect previous part to new group head)
 *       2. `groupHead->next = curr;` (Connect new group tail to remaining list)
 *
 *     Phase 4 [Move Pointer for the Next Group] :
 *       `groupPrev = groupHead;` (Move `groupPrev` to the end of the current
 *       group so it sits right before the next group).
 *
 * - Visual Trace (10 -> 20 -> 30 -> 40 -> 50, k = 2):
 *     Start   : [dummy] -> [10] -> [20] -> [30] -> [40] -> [50]
 *                  ^        ^
 *              groupPrev groupHead
 *
 *     Group 1 : Reverse [10, 20] -> `prev` = [20], `curr` = [30]
 *               Reconnect : [dummy]->next = [20], [10]->next = [30]
 *               Move      : groupPrev = [10]
 *               List      : [dummy] -> [20] -> [10] -> [30] -> [40] -> [50]
 *                                               ^       ^
 *                                           groupPrev groupHead
 *
 *     Group 2 : Reverse [30, 40] -> `prev` = [40], `curr` = [50]
 *               Reconnect : [10]->next = [40], [30]->next = [50]
 *               Move      : groupPrev = [30]
 *               List      : [dummy] -> [20] -> [10] -> [40] -> [30] -> [50]
 *
 *     Group 3 : Move `kth` from [30] for k=2 steps -> hits nullptr after [50]!
 *               Fewer than 2 nodes remain -> return `dummy.next`!
 *
 * - Complexity:
 *   Time Complexity  : O(N) — Each node is visited at most twice (check + reverse).
 *   Space Complexity : O(1) — Only a few pointers used in-place.
 * ============================================================================
 */
	static ListNode* reverseKGroup(ListNode* head, const int k){
		// Edge case: empty list or k <= 1 (no reversal needed)
		if (head == nullptr || k <= 1)
			return head;

		// Create a dummy node to simplify edge cases (like reversing the first group)
		ListNode dummy(0);
		dummy.next = head;

		// Initialize groupPrev to point to the dummy node
		ListNode* groupPrev = &dummy;

		while (true){
			// Phase 1: Verify that there are at least k nodes remaining in the list
			const ListNode* kth = groupPrev;
			for (int i = 0; i < k; i++){
				kth = kth->next;

				// // Fewer than k nodes remain; leave them untouched and return!
				if (kth == nullptr)
					return dummy.next;
			}

			// Phase 2: Reverse the k nodes using Pattern 1A
			ListNode* groupHead = groupPrev->next; // Will become tail after reversal
			ListNode* curr = groupHead;
			ListNode* prev = nullptr;

			for (int i = 0; i < k; i++){
				ListNode* next = curr->next;
				curr->next = prev;
				prev = curr;
				curr = next;
			}

			// Phase 3: Reconnect the reversed group back into the main list
			groupPrev->next = prev; // Connect previous part to new group head
			groupHead->next = curr; // Connect new group tail to remaining list

			// Phase 4: Move groupPrev to the end of the reversed group for the next iteration
			groupPrev = groupHead;
		}

		return dummy.next; // Return the new head of the modified list
	}

	// Build a linked list from a vector of values
	static ListNode* buildList(const vector<int>& values){
		if (values.empty())
			return nullptr;

		auto* head = new ListNode(values[0]);
		ListNode* curr = head;
		for (size_t i = 1; i < values.size(); ++i){
            curr->next = new ListNode(values[i]);
            curr = curr->next;
        }

		return head;
	}

	// Print the linked list
	static void printList(ListNode* head){
		ListNode* curr = head;
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
	int n, k;
	cout << "Enter the number of nodes in the linked list: ";
	cin >> n;
	cout << "Enter the values of the linked list nodes: ";
	vector<int> values(n);
	for (int& val : values)
		cin >> val;

	cout << "Enter the value of k (group size for reversal): ";
	cin >> k;

	auto head = myLinkedList::buildList(values);
	cout << "Original List: ";
	myLinkedList::printList(head);

	auto newHead = myLinkedList::reverseKGroup(head, k);
	cout << "Reversed List in groups of " << k << ": ";
	myLinkedList::printList(newHead);
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
