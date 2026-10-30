/*
Author: Sarvan Yaduvanshi
Created : 2026-10-30 12:24:29
*/

/*
 * ============================================================================
 *  138. Copy List with Random Pointer
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 138
 *  Difficulty : Medium
 *  Topics     : Hash Table, Linked List
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  A linked list of length n is given such that each node contains an
 *  additional random pointer, which could point to any node in the list, or
 *  null.
 *
 *  Construct a deep copy of the list. The deep copy should consist of
 *  exactly n brand new nodes, where each new node has its value set to the
 *  value of its corresponding original node. Both the next and random
 *  pointer of the new nodes should point to new nodes in the copied list
 *  such that the pointers in the original list and copied list represent
 *  the same list state. None of the pointers in the new list should point
 *  to nodes in the original list.
 *
 *  For example, if there are two nodes X and Y in the original list, where
 *  X.random --> Y, then for the corresponding two nodes x and y in the
 *  copied list, x.random --> y.
 *
 *  Return the head of the copied linked list.
 *
 *  The linked list is represented in the input/output as a list of n nodes.
 *  Each node is represented as a pair of [val, random_index] where:
 *
 *      - val          : an integer representing Node.val
 *      - random_index : the index of the node (range from 0 to n-1) that
 *                       the random pointer points to, or null if it does
 *                       not point to any node.
 *
 *  Your code will only be given the head of the original linked list.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      index :    0       1        2        3        4
 *      node  :  [7] --> [13] --> [11] --> [10] --> [1] --> NULL
 *      random:  null     0        4        2        0
 *
 *      random arrows:
 *          [13] ----> [7]
 *          [11] ----> [1]
 *          [10] ----> [11]
 *          [1]  ----> [7]
 *
 *  Input  : head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
 *  Output : [[7,null],[13,0],[11,4],[10,2],[1,0]]
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      index :    0       1
 *      node  :  [1] --> [2] --> NULL
 *      random:   1       1
 *
 *      random arrows:
 *          [1] ----> [2]
 *          [2] ----> [2]   (points to itself)
 *
 *  Input  : head = [[1,1],[2,1]]
 *  Output : [[1,1],[2,1]]
 *
 * ----------------------------------------------------------------------------
 *  Example 3:
 *
 *      index :    0       1       2
 *      node  :  [3] --> [3] --> [3] --> NULL
 *      random:  null     0      null
 *
 *      random arrows:
 *          [3 at index 1] ----> [3 at index 0]
 *
 *  Input  : head = [[3,null],[3,0],[3,null]]
 *  Output : [[3,null],[3,0],[3,null]]
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - 0 <= n <= 1000
 *      - -10^4 <= Node.val <= 10^4
 *      - Node.random is null or is pointing to some node in the linked
 *        list.
 * ============================================================================
 */


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_map>
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
public:
	struct ListNode{
		int val;
		ListNode* next;
		ListNode* random;

		explicit ListNode(const int val) : val(val), next(nullptr), random(nullptr) {}
	};

	ListNode* head;
public:
	myLinkedList() : head(nullptr) {}

	// Input format: values[0..n-1] and random indices[0..n-1].
	// A random index of -1 represents a null random pointer.
	static ListNode* buildLL(const vector<int>& values, const vector<int>& randomIndices){
		if (values.empty())
			return nullptr;

		vector<ListNode*> nodes;
		nodes.reserve(values.size());
		for (int value : values)
			nodes.push_back(new ListNode(value));

		for (size_t i = 0; i + 1 < nodes.size(); i++)
			nodes[i]->next = nodes[i + 1];

		for (size_t i = 0; i < nodes.size(); i++){
			const int randomIndex = randomIndices[i];
			if (randomIndex >= 0)
				nodes[i]->random = nodes[randomIndex];
		}

		return nodes.front();
	}

	static void printAll(const ListNode* head){
		vector<const ListNode*> nodes;
		unordered_map<const ListNode*, int> index;
		for (const ListNode* curr = head; curr != nullptr; curr = curr->next){
			index[curr] = static_cast<int>(nodes.size());
			nodes.push_back(curr);
		}

		cout << "[";
		for (size_t i = 0; i < nodes.size(); i++){
			if (i > 0)
				cout << ",";

			cout << "[" << nodes[i]->val << ",";
			if (nodes[i]->random == nullptr)
				cout << "null";
			else
				cout << index[nodes[i]->random];
			cout << "]";
		}
		cout << "]\n";
	}

	static void deleteList(ListNode*& head){
		while (head != nullptr){
			ListNode* next = head->next;
			delete head;
			head = next;
		}
	}

	/*
 * ============================================================================
 * MATH & DELETION PATTERN 5: 138. Copy List with Random Pointer (O(1) Aux Space)
 * ============================================================================
 *
 * - Core Idea (The 3-Pass Interweaving Clone Engine — No Hash Map!):
 *   Instead of using an O(N) `unordered_map<Node*, Node*>` to map each original
 *   node to its clone, we temporarily store each clone at `original->next`!
 *
 *     Pass 1 [Interweave Clones Into Original List] :
 *       For each original node `curr`, create `clone = new Node(curr->val)` and
 *       insert it right after `curr`:
 *         `clone->next = curr->next;`
 *         `curr->next  = clone;`
 *       List becomes: Orig1 -> Clone1 -> Orig2 -> Clone2 -> Orig3 -> Clone3
 *
 *     Pass 2 [Assign `random` Pointers Using the Interwoven Lookup] :
 *       Since every original node `X` has its clone sitting at `X->next`, the
 *       clone of `curr->random` is sitting right at `curr->random->next`!
 *       So for each original node `curr`:
 *         `if (curr->random != nullptr)`
 *             `curr->next->random = curr->random->next;`
 *
 *     Pass 3 [Unweave / Separate Original and Cloned Lists] :
 *       Use a `dummy` + `cloneTail` builder to extract all `Clone` nodes while
 *       restoring `curr->next` back to its original next node:
 *         `Node* clone = curr->next;`
 *         `curr->next = clone->next;`       // Restore Original list!
 *         `cloneTail->next = clone;`        // Append to Cloned list!
 *
 * - CRITICAL TRAP (Why Pass 2 and Pass 3 CANNOT Be Merged Into One Loop):
 *   Suppose `Orig3->random` points backward to `Orig1`. If you unweave `Orig1`
 *   and `Clone1` while processing `Orig1`, then by the time you reach `Orig3`,
 *   `Orig1->next` is `Orig2` (NO LONGER `Clone1`!), breaking `curr->random->next`!
 *   Therefore, ALL `random` links must be wired in Pass 2 before unweaving in Pass 3.
 *
 * - Quick Dry Run: [7 (rand: null)] -> [13 (rand: 7)]
 *     Pass 1 (Interweave):
 *       [7] -> [7'] -> [13] -> [13'] -> nullptr
 *     Pass 2 (Wire `random`):
 *       - At [7]  : `7->random` is nullptr -> `7'->random` stays nullptr.
 *       - At [13] : `13->random` is [7]    -> `13'->random = 7->next` ([7'])!
 *     Pass 3 (Unweave):
 *       - Original restored : [7] -> [13] -> nullptr
 *       - Clone extracted   : [7' (rand: null)] -> [13' (rand: 7')] -> nullptr
 *
 * - Complexity:
 *   Time  : O(N) — 3 linear passes (2N steps each) = O(N) total time.
 *   Space : O(1) — Zero auxiliary memory (no `unordered_map` allocated!).
 * ============================================================================
 */
	static ListNode* copyRandomList(ListNode* head){
		// handle edge case of empty list
		if (head == nullptr)
			return nullptr;

		// Pass 1: Create cloned nodes and weave them right after each original node
		// eg: Original: A -> B -> C should become: A -> A' -> B -> B' -> C -> C'
		ListNode* curr = head;
		while (curr != nullptr){
			// Create a clone of the current node
			ListNode* clone = new ListNode(curr->val);

			clone->next = curr->next; // clone now points to the next original node (eg: A' -> B)
			curr->next = clone; // curr now points to its clone eg: A -> A'

			// Jump 2 steps to the next original node (eg: B)
			curr = clone->next;
		}

		// Pass 2: Connect `random` pointers for all cloned nodes
		curr = head;
		while (curr != nullptr){
			// check if the original node has a random pointer
			if (curr->random != nullptr)
				// `curr->next` is `curr`'s clone; `curr->random->next` is `random`'s clone!
				// eg: if A.random = C, then A'.random = C'
				curr->next->random = curr->random->next;

			curr = curr->next->next; // Jump 2 steps to the next original node
		}

		// Pass 3: Unweave the lists (restore original list & extract cloned list)
		ListNode dummy(0);
		ListNode* cloneTail = &dummy;
		curr = head;

		while (curr != nullptr){
			// 1. Extract the clone node (eg: A -> A' -> B becomes A' for the cloned list)
			ListNode* clone = curr->next;

			// 2. Restore the original node's `next` pointer (eg: A -> A' -> B becomes A -> B)
			curr->next = clone->next;

			// 3. Attach `clone` to our extracted clone list (eg: dummy -> A' -> B')
			cloneTail->next = clone;
			cloneTail = clone; // Move the tail pointer forward to the newly added clone

			// 4. Move `curr` to the next original node (eg: A -> B)
			curr = curr->next;
		}

		// Return the head of the cloned list (skipping the dummy node)
		return dummy.next;
	}
};


static void solve(){
	int n;
	if (!(cin >> n) || n < 0 || n > 1000)
		return;

	vector<int> values(n);
	vector<int> randomIndices(n);

	for (int i = 0; i < n; i++)
		cin >> values[i];

	for (int i = 0; i < n; i++){
		cin >> randomIndices[i];
		if (randomIndices[i] < -1 || randomIndices[i] >= n)
			return;
	}

	myLinkedList::ListNode* head = myLinkedList::buildLL(values, randomIndices);
	myLinkedList::ListNode* copiedHead = myLinkedList::copyRandomList(head);
	myLinkedList::printAll(copiedHead);

	myLinkedList::deleteList(head);
	myLinkedList::deleteList(copiedHead);

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
