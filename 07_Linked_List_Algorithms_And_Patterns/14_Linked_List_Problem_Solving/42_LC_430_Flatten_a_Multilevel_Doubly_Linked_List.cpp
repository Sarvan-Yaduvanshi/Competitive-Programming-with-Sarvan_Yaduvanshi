/*
Author: Sarvan Yaduvanshi
Created : 2026-11-01 02:25:58
*/

/*
 * ============================================================================
 *  430. Flatten a Multilevel Doubly Linked List
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 430
 *  Difficulty : Medium
 *  Topics     : Linked List, Depth-First Search, Doubly-Linked List
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Uber
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  You are given a doubly linked list, which contains nodes that have a next
 *  pointer, a previous pointer, and an additional child pointer. This child
 *  pointer may or may not point to a separate doubly linked list, also
 *  containing these special nodes. These child lists may have one or more
 *  children of their own, and so on, to produce a multilevel data structure
 *  as shown in the example below.
 *
 *  Given the head of the first level of the list, flatten the list so that
 *  all the nodes appear in a single-level, doubly linked list. Let curr be
 *  a node with a child list. The nodes in the child list should appear
 *  after curr and before curr.next in the flattened list.
 *
 *  Return the head of the flattened list. The nodes in the list must have
 *  all of their child pointers set to null.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      Level 0 :  1 --- 2 --- 3 --- 4 --- 5 --- 6 --- NULL
 *                              |
 *      Level 1 :               7 --- 8 --- 9 --- 10 --- NULL
 *                                    |
 *      Level 2 :                     11 --- 12 --- NULL
 *
 *      After flatten:
 *      1 <-> 2 <-> 3 <-> 7 <-> 8 <-> 11 <-> 12 <-> 9 <-> 10 <-> 4 <-> 5 <-> 6
 *
 *  Input  : head = [1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
 *  Output : [1,2,3,7,8,11,12,9,10,4,5,6]
 *  Explanation: The multilevel linked list in the input is shown above.
 *               After flattening the multilevel linked list it becomes the
 *               single-level list shown above.
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      Level 0 :  1 --- 2 --- NULL
 *                 |
 *      Level 1 :  3 --- NULL
 *
 *      After flatten:
 *      1 <-> 3 <-> 2
 *
 *  Input  : head = [1,2,null,3]
 *  Output : [1,3,2]
 *  Explanation: The multilevel linked list in the input is shown above.
 *               After flattening the multilevel linked list it becomes
 *               1 <-> 3 <-> 2.
 *
 * ----------------------------------------------------------------------------
 *  Example 3:
 *
 *      NULL
 *
 *  Input  : head = []
 *  Output : []
 *  Explanation: There could be empty list in the input.
 *
 * ----------------------------------------------------------------------------
 *  How the multilevel linked list is represented in test cases:
 *  We use the multilevel linked list from Example 1 above:
 *
 *      1---2---3---4---5---6--NULL
 *              |
 *              7---8---9---10--NULL
 *                  |
 *                  11--12--NULL
 *
 *  The serialization of each level is as follows:
 *
 *      [1,2,3,4,5,6,null]
 *      [7,8,9,10,null]
 *      [11,12,null]
 *
 *  To serialize all levels together, we will add nulls in each level to
 *  signify no node connects to the upper node of the previous level. The
 *  serialization becomes:
 *
 *      [1,    2,    3, 4, 5, 6, null]
 *                   |
 *      [null, null, 7,    8, 9, 10, null]
 *                         |
 *      [            null, 11, 12, null]
 *
 *  Merging the serialization of each level and removing trailing nulls we
 *  obtain:
 *
 *      [1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of Nodes will not exceed 1000.
 *      - 1 <= Node.val <= 10^5
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

using namespace std;

class multilevelDoublyLinkedList{
private:
	struct Node{
        int val;
        Node* prev;
        Node* next;
        Node* child;

        explicit Node(const int v) : val(v), prev(nullptr), next(nullptr), child(nullptr) {}
    };

public:
	multilevelDoublyLinkedList() = default;

	using Level = vector<int>;

	/*
 * ============================================================================
 * DESIGN & FLATTEN PATTERN 2A: 430. Flatten a Multilevel Doubly Linked List
 * (Optimal O(N) Time | Strict O(1) Auxiliary Space — No Stack / No Recursion!)
 * ============================================================================
 *
 * - Core Idea (Iterative Morris-Style Tail Splicing in O(1) Space):
 *   Walk `curr` from `head`. Whenever `curr->child != nullptr`:
 *     1. Find the tail of the `curr->child` level:
 *        Walk `childTail = curr->child` while `childTail->next != nullptr`.
 *     2. Connect `childTail` to `curr->next`:
 *        `childTail->next = curr->next;`
 *        `if (curr->next != nullptr) curr->next->prev = childTail;`
 *     3. Connect `curr` to `curr->child` and clear `curr->child`:
 *        `curr->next = curr->child;`
 *        `curr->child->prev = curr;`
 *        `curr->child = nullptr;`
 *     4. Advance `curr = curr->next` (which now steps directly into the spliced
 *        child list, flattening any nested sub-children on future iterations!).
 *
 * - Visual Dry Run:
 *     1 <---> 2 <---> 3 <---> 4
 *             |
 *             7 <---> 8
 *                     |
 *                     11 <---> 12
 *
 *     - At `curr = 1`: No child -> advance `curr = 2`.
 *     - At `curr = 2`: Has child [7 <-> 8]!
 *         * `childTail` starts at [7], walks to [8].
 *         * Connect [8] <---> [3] (old `curr->next`).
 *         * Connect [2] <---> [7], set `2->child = nullptr`.
 *         * Main track is now: 1 <-> 2 <-> 7 <-> 8 <-> 3 <-> 4 (with 8->child = 11).
 *         * Advance `curr = 7`.
 *     - At `curr = 7`: No child -> advance `curr = 8`.
 *     - At `curr = 8`: Has child [11 <-> 12]!
 *         * `childTail` walks from [11] to [12].
 *         * Connect [12] <---> [3] (old `8->next`).
 *         * Connect [8] <---> [11], set `8->child = nullptr`.
 *         * Final Main Track: 1 <-> 2 <-> 7 <-> 8 <-> 11 <-> 12 <-> 3 <-> 4!
 *
 * - Complexity:
 *   Time  : O(N) — Each node is visited a constant number of times.
 *   Space : O(1) — Zero recursion call stack and zero explicit stack used!
 * ============================================================================
 */
	static Node* flatten(Node* head){
		// handle edge case of empty list
		if (head == nullptr)
			return nullptr;

		// `curr` will traverse the entire list, flattening child lists in-place
		Node* curr = head;

		// Iterate through the list until we reach the end
		while (curr != nullptr){
			// Case 1: // If `curr` has a child level, splice it between `curr` and `curr->next`
			if (curr->child != nullptr){
				// Find the tail of the child list
				Node* childTail = curr->child;

				// 1. Walk to the tail of the immediate child list
				while (childTail->next != nullptr)
					childTail = childTail->next;

				// 2. Wire `childTail` forward to `curr->next` (and backward if not null)
				childTail->next = curr->next;
				if (curr->next != nullptr)
					curr->next->prev = childTail;

				// 3. Wire `curr` forward to `curr->child` and nullify `curr->child`
				curr->next = curr->child; // Wire `curr` to the child list
				curr->child->prev = curr; // Wire child back to curr
				curr->child = nullptr; // Clear the child pointer since it's now flattened
			}

			// Case 2: Move `curr` forward to the next node (which may be a child or original next)
			curr = curr->next;
		}

		// Return the head of the flattened list
		return head;
	}

	static Node* buildFromLevels(const vector<Level>& levels){
		if (levels.empty())
			return nullptr;

		vector<vector<Node*>> nodesByLevel;
		nodesByLevel.reserve(levels.size());

		for (const Level& level : levels){
			vector<Node*> nodes;
			for (int value : level){
				if (value != -1)
					nodes.push_back(new Node(value));
			}

			for (size_t i = 1; i < nodes.size(); ++i){
				nodes[i - 1]->next = nodes[i];
				nodes[i]->prev = nodes[i - 1];
			}
			nodesByLevel.push_back(nodes);
		}

		for (size_t level = 1; level < levels.size(); ++level){
			size_t leadingNulls = 0;
			while (leadingNulls < levels[level].size() &&
				   levels[level][leadingNulls] == -1)
				++leadingNulls;

			if (leadingNulls < nodesByLevel[level - 1].size() &&
				!nodesByLevel[level].empty())
				nodesByLevel[level - 1][leadingNulls]->child =
					nodesByLevel[level].front();
		}

		return nodesByLevel.front().empty() ? nullptr : nodesByLevel.front().front();
	}

	static void printOriginal(const vector<Level>& levels){
		cout << "Original multilevel list:\n";
		for (size_t level = 0; level < levels.size(); ++level){
			cout << "  Level " << level << ": [";
			for (size_t i = 0; i < levels[level].size(); ++i){
				if (i > 0)
					cout << ",";
				if (levels[level][i] == -1)
					cout << "null";
				else
					cout << levels[level][i];
			}
			cout << "]\n";
		}
	}

	static void printFlattened(const Node* head){
		cout << "After flatten: [";
		bool first = true;
		for (const Node* curr = head; curr != nullptr; curr = curr->next){
			if (!first)
				cout << ",";
			cout << curr->val;
			first = false;
		}
		cout << "]\n";
	}

	static void deleteList(Node* head){
		while (head != nullptr){
			Node* next = head->next;
			delete head;
			head = next;
		}
	}
};

void solve(){
	/*
	 * Input format follows the LeetCode level serialization, using -1 for null:
	 *
	 *   number_of_levels
	 *   count level_0_values  level_0_values...
	 *   count level_1_values  level_1_values...
	 *   ...
	 *
	 * Leading nulls on a child level identify its parent index in the
	 * preceding level. Example level 1 starts with two nulls, so it is the
	 * child of level 0 node at index 2.
	 */
	int numberOfLevels;
	if (!(cin >> numberOfLevels) || numberOfLevels <= 0)
		return;

	vector<multilevelDoublyLinkedList::Level> levels;
	levels.reserve(numberOfLevels);

	for (int level = 0; level < numberOfLevels; ++level){
		int count;
		cin >> count;
		if (count < 0)
			return;

		multilevelDoublyLinkedList::Level values(count);
		for (int& value : values)
			cin >> value;
		levels.push_back(values);
	}

	multilevelDoublyLinkedList::printOriginal(levels);
	auto* head = multilevelDoublyLinkedList::buildFromLevels(levels);
	head = multilevelDoublyLinkedList::flatten(head);
	multilevelDoublyLinkedList::printFlattened(head);
	multilevelDoublyLinkedList::deleteList(head);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}
