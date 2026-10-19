/*
Author: Sarvan Yaduvanshi
Created : 2026-10-19 04:05:18
*/

/*
 * Problem: Reverse Alternate K Nodes in a Linked List (GeeksforGeeks)
 * Difficulty: Medium, Topic: Linked List, Two Pointers
 * Company: Amazon, Microsoft, Google, Facebook, Apple, Adobe, etc. (Very important because 100+ companies asked this question)
 * Given the head of a linked list and an integer k, reverse every alternate group of k nodes, starting with the first group.
 * If the number of nodes left at the end of the list is fewer than k,
 * reverse these remaining nodes or leave them in their original order, depending on the alternation pattern.
 *
 * Example 1:
 * Input: head = 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> NULL, k = 2
 * Output: 2 -> 1 -> 3 -> 4 -> 6 -> 5 -> NULL
 * Explanation: The first group of 2 nodes (1, 2) is reversed to (2, 1). and the second group of 2 nodes (3, 4) is left as is. The third group of 2 nodes (5, 6) is reversed to (6, 5).
 *
 * Example 2:
 * head = 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> NULL, k = 3
 * Output: 3 -> 2 -> 1 -> 4 -> 5 -> 6 -> 8 -> 7 -> NULL
 * Explanation: The first group of 3 nodes (1, 2, 3) is reversed to (3, 2, 1). The second group of 3 nodes (4, 5, 6) is left as is. The third group of 2 nodes
 *
 * Constraints:
 * - The number of nodes in the list is n.
 * - 1 <= n <= 5000
 * - 0 <= Node.val <= 1000
 * - 1 <= k <= n
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
 * PATTERN 5: Reverse Alternate K-Nodes
 * ============================================================================
 * - Core Idea (Pattern 4 + A Simple Skip Loop):
 *   We use the exact same pointers as Pattern 4 (`groupPrev` and `groupHead`):
 *     1. `groupPrev` : Points to the node right BEFORE the current k-group
 *                      (starts at `dummy`).
 *     2. `groupHead` : Points to the FIRST node of the current k-group
 *                      (`groupPrev->next`). After reversal, it becomes the
 *                      LAST node (tail) of the reversed group.
 *
 * - The 4-Phase Loop (Repeated while `groupPrev->next != nullptr`):
 *     Phase 1 [Reverse Up to K Nodes (Pattern 1A)] :
 *       Save `groupHead = groupPrev->next`.
 *       Run the 3-pointer reversal (`prev`, `curr`, `next`) up to `k` times
 *       (stopping early if `curr == nullptr`).
 *       When the loop finishes:
 *         - `prev` is the NEW head of this reversed group.
 *         - `curr` is the first node of the NEXT group.
 *         - `groupHead` is now the NEW tail of this reversed group.
 *
 *     Phase 2 [Reconnect the Reversed Group into the Main List] :
 *       1. `groupPrev->next = prev;` (Connect previous part to new group head)
 *       2. `groupHead->next = curr;` (Connect new group tail to remaining list)
 *
 *     Phase 3 [Move `groupPrev` to the End of Reversed Group] :
 *       `groupPrev = groupHead;`
 *
 *     Phase 4 [Skip the Next K Nodes] :
 *       Move `groupPrev` forward `k` steps (as long as `groupPrev->next != nullptr`).
 *       This leaves the next `k` nodes untouched and parks `groupPrev` right
 *       before the next group that needs to be reversed!
 *
 * - Visual Trace (10 -> 20 -> 30 -> 40 -> 50 -> 60, k = 2):
 *     Start   : [dummy] -> [10] -> [20] -> [30] -> [40] -> [50] -> [60]
 *                  ^        ^
 *              groupPrev groupHead
 *
 *     Iter 1 (Reverse [10, 20], then Skip [30, 40]):
 *       1. Reverse [10, 20] -> `prev` = [20], `curr` = [30]
 *       2. Reconnect : [dummy]->next = [20], [10]->next = [30]
 *       3. Move      : groupPrev = [10]
 *       4. Skip k=2  : groupPrev moves 2 steps forward ([10] -> [30] -> [40])
 *       List State   : [dummy] -> [20] -> [10] -> [30] -> [40] -> [50] -> [60]
 *                                                          ^       ^
 *                                                      groupPrev groupHead
 *
 *     Iter 2 (Reverse [50, 60], then Skip):
 *       1. Reverse [50, 60] -> `prev` = [60], `curr` = nullptr
 *       2. Reconnect : [40]->next = [60], [50]->next = nullptr
 *       3. Move      : groupPrev = [50]
 *       4. Skip k=2  : groupPrev->next is nullptr, so loop ends!
 *       Final List   : [dummy] -> [20] -> [10] -> [30] -> [40] -> [60] -> [50]
 *
 * - Complexity:
 *   Time Complexity  : O(N) — Every node is visited once (either reversed or skipped).
 *   Space Complexity : O(1) — Only a few pointers used in-place.
 * ============================================================================
 */
	static ListNode* reverseAlternateKGroup(ListNode* head, const int k) {
		// Edge case: empty list or k <= 1 (no reversal needed)
		if (head == nullptr || k <= 1)
			return head;

		// Create a dummy node to simplify edge cases (like reversing the first group)
		ListNode dummy(0);
		dummy.next = head;

		// Initialize groupPrev to point to the dummy node
		ListNode* groupPrev = &dummy;

		while (groupPrev->next != nullptr) {
			// Phase 1: Reverse up to k nodes using Pattern 1A
			ListNode* groupHead = groupPrev->next; // Will become tail after reversal
			ListNode* curr = groupHead;
			ListNode* prev = nullptr;

			for (int i = 0; i < k && curr != nullptr; i++) {
				ListNode* next = curr->next;
				curr->next = prev;
				prev = curr;
				curr = next;
			}

			// Phase 2: Reconnect the reversed group back into the main list
			groupPrev->next = prev; // Connect previous part to new group head
			groupHead->next = curr; // Connect new group tail to remaining list

			// Phase 3: Move groupPrev to the end of the reversed group
			groupPrev = groupHead;

			// Phase 4: Skip the next k nodes so they stay in their original order
			for (int i = 0; i < k && groupPrev->next != nullptr; i++) {
				groupPrev = groupPrev->next;
			}
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

	auto newHead = myLinkedList::reverseAlternateKGroup(head, k);
	cout << "Reversed List in alternate groups of " << k << ": ";
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
