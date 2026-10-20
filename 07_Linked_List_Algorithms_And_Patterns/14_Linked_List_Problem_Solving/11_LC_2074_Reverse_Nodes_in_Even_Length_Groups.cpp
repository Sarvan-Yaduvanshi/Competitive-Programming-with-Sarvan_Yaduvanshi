/*
Author: Sarvan Yaduvanshi
Created : 2026-10-19 05:27:10
*/

/*
 * Problem: Reverse Nodes in Even Length Groups (Leetcode 2074)
 * You are given the head of a linked list.
 * The nodes in the linked list are sequentially assigned to non-empty groups
 * whose lengths form the sequence of the natural numbers (1, 2, 3, 4, ...).
 * The length of a group is the number of nodes assigned to it. In other words,
 *      The 1st node is assigned to the first group.
 *      The 2nd and the 3rd nodes are assigned to the second group.
 *      The 4th, 5th, and 6th nodes are assigned to the third group, and so on.
 * Note that the length of the last group may be less than or equal to 1 + the length of the second to last group.
 * Reverse the nodes in each group with an even length, and return the head of the modified linked list.
 *
 * Example 1: 1st group: 1 node (1) -> 2nd group: 2 nodes (2,3) -> 3rd group: 3 nodes (4,5,6) -> 4th group: 4 nodes (7,8,9,10)
 * Input: head = [5,2,6,3,9,1,7,3,8,4],  5-> 2->6->3->9->1->7->3->8->4
 * Output: [5,6,2,3,9,1,4,8,3,7],  5->6->2->3->9->1->4->8->3->7
* Explanation:
- The length of the first group is 1, which is odd, hence no reversal occurs.
- The length of the second group is 2, which is even, hence the nodes are reversed.
- The length of the third group is 3, which is odd, hence no reversal occurs.
- The length of the last group is 4, which is even, hence the nodes are reversed.
 *
 * Example 2:  1st group: 1 node (1) -> 2nd group: 2 nodes (1,0) -> 3rd group: 3 nodes (6)
 * Input: head = [1,1,0,6],  1->1->0->6
 * Output: [1,0,1,6],  1->0->1->6
* Explanation:
- The length of the first group is 1. No reversal occurs.
- The length of the second group is 2. The nodes are reversed.
- The length of the last group is 1. No reversal occurs.
 *
 * Example 3:  1st group: 1 node (2) -> 2nd group: 2 nodes (1,3) -> 3rd group: 3 nodes (5,6,7) -> 4th group: 4 nodes (9,10,11,12)
 * Input: head = [2,1,3,5,6,7,9,10,11,12],  2->1->3->5->6->7->9->10->11->12
 * Output: [2,3,1,5,6,7,12,11,10,9],  2->3->1->5->6->7->12->11->10->9
 * Explanation:
- The length of the first group is 1. No reversal occurs.
- The length of the second group is 2. The nodes are reversed.
- The length of the third group is 3. No reversal occurs.
- The length of the last group is 4. The nodes are reversed.
 *
 * Constraints:
 * The number of nodes in the list is in the range [1, 10^5].
 * 0 <= Node.val <= 10^5
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
 * ============================================================================
 * 2074. Reverse Nodes in Even Length Groups (Optimal O(N) Time | O(1) Space)
 * ============================================================================
 *
 * - Core Idea (Count Actual Length First, Then Reverse If Even):
 *   Nodes are grouped in natural sizes (groupSize = 1, 2, 3, 4...).
 *   HOWEVER, the last group might run out of nodes early (e.g., expected 3,
 *   but only 2 nodes left). Since 2 is EVEN, we still must reverse it!
 *   Therefore, we CANNOT just check `if (groupSize % 2 == 0)`. We must walk
 *   the group first to count its `actualLength`, and check `actualLength % 2 == 0`.
 *
 * - Key Pointers & CP Trick Used in This Code:
 *     1. `prevGroup`      : Node right BEFORE the current group.
 *     2. `startGroup`     : FIRST node of current group (becomes tail if reversed).
 *     3. `groupEnd`       : LAST node of current group (becomes head if reversed).
 *     4. `nextGroupStart` : FIRST node of the NEXT group (`groupEnd->next`).
 *     * CP Trick: Initializing `previous = nextGroupStart` before the reversal
 *       loop automatically connects `startGroup->next` (the new tail) to
 *       `nextGroupStart` on the very first flip!
 *
 * - 3-Phase Loop (While `prevGroup->next != nullptr`):
 *     Phase 1 [Measure Actual Group]:
 *       Start at `startGroup` and walk up to `groupSize` steps to find `groupEnd`
 *       and count `actualLength`.
 *
 *     Phase 2 [Even vs. Odd Decision]:
 *       - If `actualLength` is EVEN:
 *           Reverse from `startGroup` up to `nextGroupStart`.
 *           Reconnect `prevGroup->next = groupEnd` (new head of this group).
 *           Move `prevGroup = startGroup` (new tail of this group).
 *       - If `actualLength` is ODD:
 *           No reversal needed! Simply jump `prevGroup = groupEnd`.
 *
 *     Phase 3 [Next Natural Number]:
 *       Increment `groupSize++` for the next group.
 *
 * - Quick Dry Run: head = [1, 1, 0, 6, 5]
 *     Start: [dummy] -> [1] -> [1] -> [0] -> [6] -> [5]
 *               ^
 *           prevGroup
 *
 *     1. groupSize = 1:
 *        Group = [1], actualLength = 1 (ODD).
 *        Skip reversal -> prevGroup jumps to `groupEnd` ([1]).
 *
 *     2. groupSize = 2:
 *        Group = [1 -> 0], actualLength = 2 (EVEN), nextGroupStart = [6].
 *        Reverse [1, 0] with `previous = [6]` ==> [0] -> [1] -> [6].
 *        Reconnect `prevGroup->next = groupEnd` ([0]).
 *        Move `prevGroup = startGroup` ([1]).
 *        List: [dummy] -> [1] -> [0] -> [1] -> [6] -> [5]
 *                                        ^
 *                                    prevGroup
 *
 *     3. groupSize = 3 (Last Group Edge Case!):
 *        We try to take 3 nodes, but hit nullptr after [6 -> 5].
 *        actualLength = 2 (EVEN!), nextGroupStart = nullptr.
 *        Reverse [6, 5] with `previous = nullptr` ==> [5] -> [6] -> nullptr.
 *        Reconnect `prevGroup->next = groupEnd` ([5]).
 *        Move `prevGroup = startGroup` ([6]).
 *        Final List: [1] -> [0] -> [1] -> [5] -> [6]
 *
 * - Complexity:
 *   Time  : O(N) — Each node is visited at most twice (1x count, 1x reverse).
 *   Space : O(1) — Pure in-place pointer manipulation.
 * ============================================================================
 */

	static ListNode* reverseEvenLengthGroups(ListNode* head){
		// Create a dummy node to point to first node, which simplifies edge cases
		ListNode dummy(0);
		dummy.next = head;

		// Initialize prevGroup to dummy
		ListNode* prevGroup = &dummy;
		int groupSize = 1; // Expected size: 1, 2, 3, 4...

		// Process each group until we reach the end of the list
		while (prevGroup->next != nullptr){
			// Initialize pointers to the start and end of the current group
			ListNode* startGroup = prevGroup->next;
			ListNode* groupEnd = startGroup;
			int actualLength = 1; // Count actual length of the group

			// Phase 1: Walk to the end of current group & count actual nodes
			while (actualLength < groupSize && groupEnd->next != nullptr){
				groupEnd = groupEnd->next; // move groupEnd until we reach the expected group size or end of list
				actualLength++; // Increment actual length of the group
			}

			// Initialize nextGroupStart to the node after groupEnd
			ListNode* nextGroupStart = groupEnd->next;

			// Phase 2: Reverse only if the ACTUAL number of nodes is even
			if (actualLength % 2 == 0){
				ListNode* current = startGroup;
				// CP Trick: Start `previous` at `nextGroupStart` so `startGroup`
				// (the new tail) automatically links to the next group on step 1!
				ListNode* previous = nextGroupStart;

				// Reverse the current group in-place
				while (current != nextGroupStart){
					ListNode* next = current->next;
					current->next = previous;
					previous = current;
					current = next;
				}
				// Reconnect previous group to new head (`groupEnd`), and move anchor to new tail (`startGroup`)
				prevGroup->next = groupEnd;
				prevGroup = startGroup;

			} else{
				// Odd length: keep group as-is and jump anchor to the end of this group
				prevGroup = groupEnd;
			}

			// Phase 3: Expand target size for next group
			groupSize++;
		}

		return dummy.next;
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
	int n;
	cout << "Enter the number of nodes in the linked list: ";
	cin >> n;
	cout << "Enter the values of the linked list nodes: ";
	vector<int> values(n);
	for (int& val : values)
		cin >> val;

	auto head = myLinkedList::buildList(values);
	cout << "Original List: ";
	myLinkedList::printList(head);

	auto newHead = myLinkedList::reverseEvenLengthGroups(head);
	cout << "Modified List after reversing even length groups: ";
	myLinkedList::printList(newHead);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}
