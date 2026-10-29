/*
Author: Sarvan Yaduvanshi
Created : 2026-10-27 04:30:52
*/

/*
 * ============================================================================
 *  23. Merge k Sorted Lists
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 23
 *  Difficulty : Hard
 *  Topics     : Linked List, Divide and Conquer, Heap (Priority Queue),
 *               Merge Sort
 *  Companies  : Amazon, Google, Microsoft, Meta, Apple, Bloomberg, Uber
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  You are given an array of k linked-lists lists, each linked-list is
 *  sorted in ascending order.
 *
 *  Merge all the linked-lists into one sorted linked-list and return it.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      lists[0] :  1 -> 4 -> 5
 *      lists[1] :  1 -> 3 -> 4
 *      lists[2] :  2 -> 6
 *      merged   :  1 -> 1 -> 2 -> 3 -> 4 -> 4 -> 5 -> 6
 *
 *  Input  : lists = [[1,4,5],[1,3,4],[2,6]]
 *  Output : [1,1,2,3,4,4,5,6]
 *  Explanation: The linked-lists are:
 *               [
 *                 1->4->5,
 *                 1->3->4,
 *                 2->6
 *               ]
 *               merging them into one sorted linked list:
 *               1->1->2->3->4->4->5->6
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      lists  :  (empty array, k = 0)
 *      merged :  NULL
 *
 *  Input  : lists = []
 *  Output : []
 *
 * ----------------------------------------------------------------------------
 *  Example 3:
 *
 *      lists[0] :  NULL
 *      merged   :  NULL
 *
 *  Input  : lists = [[]]
 *  Output : []
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - k == lists.length
 *      - 0 <= k <= 10^4
 *      - 0 <= lists[i].length <= 500
 *      - -10^4 <= lists[i][j] <= 10^4
 *      - lists[i] is sorted in ascending order.
 *      - The sum of lists[i].length will not exceed 10^4.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <random>
#include <chrono>
#include <list>
#include <queue>
using namespace std;

class MyLinkedList{
public:
	// Definition for singly-linked list.
	struct ListNode{
		int val;
		ListNode* next;
		explicit ListNode(const int val) : val(val), next(nullptr) {}
	};

private:
	ListNode* head;

public:
	MyLinkedList() : head(nullptr) {}

	/*
	 * Approach 1: Repeatedly Select the Smallest Current Head (Brute Force)
	 *
	 * Every input list is already sorted, so its smallest remaining value is
	 * always at its current head. Scan all non-empty list heads, select the
	 * smallest one, append it to the result, and advance that list's pointer.
	 *
	 * Dry run:
	 *   lists = [1 -> 4, 2 -> 3, 0 -> 5]
	 *
	 *   Selected values: 0, 1, 2, 3, 4, 5
	 *
	 *   After each selection:
	 *     result = 0
	 *     result = 0 -> 1
	 *     result = 0 -> 1 -> 2
	 *     result = 0 -> 1 -> 2 -> 3
	 *     result = 0 -> 1 -> 2 -> 3 -> 4
	 *     result = 0 -> 1 -> 2 -> 3 -> 4 -> 5
	 *
	 * The dummy node simplifies result-list construction. Existing nodes are
	 * reused, and the final node is explicitly terminated with nullptr.
	 *
	 * Complexity:
	 *   Let k be the number of lists and N the total number of nodes.
	 *   - Time: O(N * k), because all k heads are scanned for every node.
	 *   - Space: O(1) auxiliary space, excluding the input lists and output.
	 */
	static ListNode* mergeKLists(vector<ListNode*>& lists){
		// No input lists means there is no merged list.
		if (lists.empty())
            return nullptr;

		// Dummy head simplifies appending nodes to the result.
		ListNode dummy(0);
		ListNode* tail = &dummy;

		// Continue until every input list has been fully consumed.
		while (true){
			int min_index = -1;
			for (int i = 0; i < lists.size(); i++){
				// Ignore lists that have no remaining nodes.
				if (lists[i] == nullptr)
					continue;

				// Track the list whose current head has the smallest value.
				if (min_index == -1 || lists[i]->val < lists[min_index]->val)
					min_index = i;
			}

			// All list heads are null, so merging is complete.
			if (min_index == -1)
				break;

			// Append the smallest node and advance its source list.
			tail->next = lists[min_index];
			tail = tail->next;
			lists[min_index] = lists[min_index]->next;
		}

		// Remove any old link from the final node.
		tail->next = nullptr;
		return dummy.next;
	}

/*
		 * Approach 2: Divide and Conquer(Recursive)
		 *
		 * Instead of comparing the heads of all k lists repeatedly, divide the
		 * range of lists into two halves. Recursively merge the left half and
		 * the right half, then merge those two sorted linked lists.
		 *
		 * The helper function mergeTwoLists performs the standard two-pointer
		 * merge. Because every input list is already sorted, the smaller
		 * current node can safely be attached to the result at each step.
		 *
		 * Example dry run:
		 *   lists = [1 -> 4 -> 5, 1 -> 3 -> 4, 2 -> 6]
		 *
		 *   1. Split the list range:
		 *        [1 -> 4 -> 5]       [1 -> 3 -> 4, 2 -> 6]
		 *
		 *   2. Split the right half again:
		 *        [1 -> 3 -> 4]       [2 -> 6]
		 *
		 *   3. Merge the smaller groups:
		 *        merge(1 -> 3 -> 4, 2 -> 6)
		 *        = 1 -> 2 -> 3 -> 4 -> 6
		 *
		 *   4. Merge the two sorted results:
		 *        merge(1 -> 4 -> 5, 1 -> 2 -> 3 -> 4 -> 6)
		 *        = 1 -> 1 -> 2 -> 3 -> 4 -> 4 -> 5 -> 6
		 *
		 * Let k be the number of lists and N be the total number of nodes.
		 * - Time: O(N log k), because each level processes all N nodes once
		 *          and there are O(log k) levels.
		 * - Space: O(log k) recursion stack space. The nodes are reused, so
		 *           no additional list storage is created.
		 */
	static ListNode* mergeKListsRecursive(const vector<ListNode*>& lists) {
		// empty input means there is no merged list.
		if (lists.empty())
			return nullptr;

		// Helper function merges two sorted linked lists into one sorted list.
		auto mergeTwoLists = [&](ListNode* list1, ListNode* list2) -> ListNode*{
			ListNode dummy(0);
			ListNode* tail = &dummy;

			while (list1 != nullptr && list2 != nullptr){
				// Case 1: list1's current node is smaller or equal, so append it.
				if (list1->val <= list2->val){
					tail->next = list1; // add
					list1 = list1->next; // move forward

				// Case 2: list2's current node is smaller, so append it.
				} else{
					tail->next = list2; // add
					list2 = list2->next; // move forward
				}

				// Advance the tail pointer to the newly added node.
				tail = tail->next;
			}

			// Case 3: One of the lists is exhausted, so append the remaining nodes.
			tail->next = (list1 != nullptr) ? list1 : list2;
			return dummy.next; // return the merged list, skipping the dummy node
		};

		// Recursively merge the inclusive range [start, end].
		auto mergeKSortedListRecursive = [&](auto&& self, const int start, const int end) -> ListNode*{
			// A single list is already sorted and needs no work.
			if (start == end)
				return lists[start];

			// This also protects the helper when an empty range is requested.
			if (start > end)
				return nullptr;

			// midpoint divides the range into two halves for recursive merging.
			const int mid = start + (end - start) / 2;

			ListNode* list1 = self(self, start, mid); // recursively merge the left half
			ListNode* list2 = self(self, mid + 1, end); // recursively merge the right half

			// Both halves are sorted now, so combine them into one sorted list.
			return mergeTwoLists(list1, list2);
		};

		return mergeKSortedListRecursive(mergeKSortedListRecursive, 0, lists.size() - 1);
	}

 /*
  * Approach 3: Bottom-Up Divide & Conquer (Iterative)
 *
 * - Core Idea (Bottom-Up Divide & Conquer Interval Merging):
 *   Instead of merging lists one-by-one sequentially (which takes O(N * K) time)
 *   or using a Min-Heap (which takes O(K) extra space), we pair up lists using
 *   a doubling stride `interval = 1, 2, 4, 8...` directly inside `lists`:
 *     - Pass 1 (interval = 1): Merge lists[0] & lists[1] -> lists[0],
 *                              Merge lists[2] & lists[3] -> lists[2]...
 *     - Pass 2 (interval = 2): Merge lists[0] & lists[2] -> lists[0],
 *                              Merge lists[4] & lists[6] -> lists[4]...
 *     - Pass 3 (interval = 4): Merge lists[0] & lists[4] -> lists[0]...
 *   When `interval >= k`, `lists[0]` holds the complete merged list!
 *
 * - Why Time Complexity is O(N log K):
 *   There are ceil(log2(K)) rounds. In every single round, each of the N total
 *   nodes across all lists is visited at most once during `mergeTwoLists`.
 *   Total work = N * log2(K) = O(N log K) Time with strict O(1) Auxiliary Space!
 *
 * - Quick Dry Run: lists = [ L0: [1->4->5], L1: [1->3->4], L2: [2->6] ] (k = 3)
 *     Round 1 (interval = 1, step i += 2):
 *       - i = 0: lists[0] = mergeTwoLists(lists[0], lists[1])
 *                ==> lists[0] becomes [1 -> 1 -> 3 -> 4 -> 4 -> 5]
 *       - (i = 2 stops because i + interval (2 + 1 = 3) is not < k (3);
 *          lists[2] ([2 -> 6]) waits untouched for the next round!)
 *
 *     Round 2 (interval = 2, step i += 4):
 *       - i = 0: lists[0] = mergeTwoLists(lists[0], lists[2])
 *                ==> lists[0] becomes [1 -> 1 -> 2 -> 3 -> 4 -> 4 -> 5 -> 6]
 *
 *     Loop ends (next interval = 4 >= k). Return `lists[0]`!
 *
 * - Complexity:
 *   Time  : O(N log K) — N = total nodes across all lists, K = number of lists.
 *   Space : O(1)       — In-place pointer rewiring (0 heap / recursion memory).
 * ============================================================================
 */
	static ListNode* mergeKListsOptimal(vector<ListNode*>& lists){
		int k = lists.size();

		// Edge case: If there are no lists, return nullptr.
		if (k == 0)
			return nullptr;

		// Helper function to merge two sorted linked lists into one sorted list.
		auto mergeTwoLists = [&](ListNode* list1, ListNode* list2) -> ListNode*{
			ListNode dummy(0);
			ListNode* tail = &dummy;

			while (list1 != nullptr && list2 != nullptr){
				if (list1->val <= list2->val){
					tail->next = list1;
					list1 = list1->next;

				} else{
					tail->next = list2;
					list2 = list2->next;
				}

				tail = tail->next;
			}

			tail->next = (list1 != nullptr) ? list1 : list2;
			return dummy.next;
		};

		// Double `interval` each round: 1, 2, 4, 8...
		for (int interval = 1; interval < k; interval <<= 1){
			// Jump by `2 * interval` to grab disjoint pairs: (i) and (i + interval)
			for (int i = 0; i + interval < k; i += (interval << 1))
				// Merge lists[i] and lists[i + interval] into lists[i].
				lists[i] = mergeTwoLists(lists[i], lists[i + interval]);
		}

		return lists[0]; // The fully merged list is now at lists[0].
	}

	/*
	 * Approach 4: Min-Heap (priority queue)
	 *
	 * Step 1:
	 *   The first node of every sorted list is the smallest node currently
	 *   available from that list. Put all non-null first nodes into a min-heap.
	 *
	 * Step 2:
	 *   The node at the top of the min-heap is the smallest node among all
	 *   current list nodes. Remove it and attach it to the merged list.
	 *
	 * Step 3:
	 *   After removing a node, its next node becomes the new smallest possible
	 *   node from the same list. Add that next node to the min-heap.
	 *
	 * Step 4:
	 *   Repeat the previous two steps until the min-heap becomes empty.
	 *   At that point, every node has been added to the merged list.
	 *
	 * Dry run:
	 *   lists = [1 -> 4, 1 -> 3, 2 -> 6]
	 *
	 *   Initial heap: [1, 1, 2]
	 *   Remove 1, add its next node 4: result = 1
	 *   Remove 1, add its next node 3: result = 1 -> 1
	 *   Remove 2, add its next node 6: result = 1 -> 1 -> 2
	 *   Remove 3, heap has 4, 6:          result = 1 -> 1 -> 2 -> 3
	 *   Remove 4, heap has 6:             result = 1 -> 1 -> 2 -> 3 -> 4
	 *   Remove 6, heap is empty:          result = 1 -> 1 -> 2 -> 3 -> 4 -> 6
	 *
	 * Let k be the number of lists and N be the total number of nodes.
	 * - Time: O(N log k), because every node enters and leaves the heap once.
	 * - Space: O(k), because the heap stores at most one current node from
	 *           each list.
	 */
	static ListNode* mergeKListsHeap(const vector<ListNode*>& lists){
		// The comparator makes the priority queue behave like a min-heap.
		auto comparator = [](const ListNode* a, const ListNode* b){
			return a->val > b->val;
		};

		// store the current smallest node from each list in a min-heap
		priority_queue<ListNode*, vector<ListNode*>, decltype(comparator)> minHeap(comparator);

		// Add the first node of every non-empty list to the heap.
		for (ListNode* head : lists){
			if (head != nullptr)
				minHeap.push(head);
		}

		// The dummy node makes it easy to build the answer list.
		ListNode dummy(0);
		ListNode* tail = &dummy;

		while (!minHeap.empty()){
			// Get the smallest current node from all lists.
			ListNode* smallest = minHeap.top();
			minHeap.pop();

			// Attach that node to the merged list.
			tail->next = smallest;
			tail = tail->next;

			// Add the next node from the same list, if it exists.
			if (smallest->next != nullptr)
				minHeap.push(smallest->next);
		}

		// All nodes are already in sorted order.
		return dummy.next;
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
	int k;
	cout << "Enter the number of k sorted linked lists: ";
	cin >> k;

	if (k <= 0){
		cout << "No linked lists to merge.\n";
		return;
	}

	/*
	 * Store the input as vectors first. Every approach changes the next
	 * pointers while merging, so each approach must receive fresh lists.
	 */
	vector<vector<int>> input(k);
	for (int i = 0; i < k; i++){
		int n;
		cout << "Enter the number of nodes in list " << i + 1 << ": ";
		cin >> n;

		cout << "Enter the sorted values of list " << i + 1 << ": ";
		input[i].resize(n);
		for (int& value : input[i])
			cin >> value;
	}

	// Build a new copy of every input list for one approach.
	auto createLists = [&](){
		vector<MyLinkedList::ListNode*> lists;
		for (const vector<int>& values : input)
			lists.push_back(MyLinkedList::buildList(values));
		return lists;
	};

	cout << "\nOriginal lists:\n";
	for (int i = 0; i < k; i++){
		cout << "List " << i + 1 << ": ";
		MyLinkedList::printList(MyLinkedList::buildList(input[i]));
	}

	cout << "\nMerged list using Brute Force:\n";
	auto bruteForceLists = createLists();
	MyLinkedList::printList(MyLinkedList::mergeKLists(bruteForceLists));

	cout << "\nMerged list using Recursive Divide and Conquer:\n";
	auto recursiveLists = createLists();
	MyLinkedList::printList(MyLinkedList::mergeKListsRecursive(recursiveLists));

	cout << "\nMerged list using Iterative Divide and Conquer:\n";
	auto iterativeLists = createLists();
	MyLinkedList::printList(MyLinkedList::mergeKListsOptimal(iterativeLists));

	cout << "\nMerged list using Min-Heap:\n";
	auto heapLists = createLists();
	MyLinkedList::printList(MyLinkedList::mergeKListsHeap(heapLists));

}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}
