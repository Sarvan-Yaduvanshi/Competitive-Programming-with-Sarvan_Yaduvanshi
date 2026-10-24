/*
Author: Sarvan Yaduvanshi
Created : 2026-10-24 19:25:54
*/

/*
 * ============================================================================
 *  160. Intersection of Two Linked Lists
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 160
 *  Difficulty : Easy
 *  Topics     : Hash Table, Linked List, Two Pointers
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Adobe, Uber
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the heads of two singly linked-lists headA and headB, return the
 *  node at which the two lists intersect. If the two linked lists have no
 *  intersection at all, return null.
 *
 *  For example, the following two linked lists begin to intersect at
 *  node c1:
 *
 *      A:      a1 -> a2 ---.
 *                           \
 *                            c1 -> c2 -> c3
 *                           /
 *      B:  b1 -> b2 -> b3 -'
 *
 *  The test cases are generated such that there are no cycles anywhere in
 *  the entire linked structure.
 *
 *  Note that the linked lists must retain their original structure after
 *  the function returns.
 *
 * ----------------------------------------------------------------------------
 *  Custom Judge:
 *  The inputs to the judge are given as follows (your program is NOT given
 *  these inputs):
 *
 *      - intersectVal : The value of the node where the intersection occurs.
 *                       This is 0 if there is no intersected node.
 *      - listA        : The first linked list.
 *      - listB        : The second linked list.
 *      - skipA        : The number of nodes to skip ahead in listA (starting
 *                       from the head) to get to the intersected node.
 *      - skipB        : The number of nodes to skip ahead in listB (starting
 *                       from the head) to get to the intersected node.
 *
 *  The judge will then create the linked structure based on these inputs and
 *  pass the two heads, headA and headB, to your program. If you correctly
 *  return the intersected node, then your solution will be accepted.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      A:       4 -> 1 --.
 *                         \
 *                          8 -> 4 -> 5
 *                         /
 *      B:  5 -> 6 -> 1 --'
 *
 *  Input  : intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5],
 *           skipA = 2, skipB = 3
 *  Output : Intersected at '8'
 *  Explanation: The intersected node's value is 8 (note that this must not
 *               be 0 if the two lists intersect).
 *               From the head of A, it reads as [4,1,8,4,5]. From the head
 *               of B, it reads as [5,6,1,8,4,5]. There are 2 nodes before
 *               the intersected node in A; There are 3 nodes before the
 *               intersected node in B.
 *
 *               - Note that the intersected node's value is not 1 because
 *                 the nodes with value 1 in A and B (2nd node in A and 3rd
 *                 node in B) are different node references. In other words,
 *                 they point to two different locations in memory, while
 *                 the nodes with value 8 in A and B (3rd node in A and 4th
 *                 node in B) point to the same location in memory.
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      A:  1 -> 9 -> 1 -> 2 -> 4
 *                         ^
 *                         |
 *      B:            3 ---'
 *
 *      (B = 3 -> 2 -> 4, joins A at node 2)
 *
 *  Input  : intersectVal = 2, listA = [1,9,1,2,4], listB = [3,2,4],
 *           skipA = 3, skipB = 1
 *  Output : Intersected at '2'
 *  Explanation: The intersected node's value is 2 (note that this must not
 *               be 0 if the two lists intersect).
 *               From the head of A, it reads as [1,9,1,2,4]. From the head
 *               of B, it reads as [3,2,4]. There are 3 nodes before the
 *               intersected node in A; There is 1 node before the
 *               intersected node in B.
 *
 * ----------------------------------------------------------------------------
 *  Example 3:
 *
 *      A:  2 -> 6 -> 4 -> NULL
 *      B:  1 -> 5 -> NULL
 *
 *  Input  : intersectVal = 0, listA = [2,6,4], listB = [1,5],
 *           skipA = 3, skipB = 2
 *  Output : No intersection
 *  Explanation: From the head of A, it reads as [2,6,4]. From the head of B,
 *               it reads as [1,5]. Since the two lists do not intersect,
 *               intersectVal must be 0, while skipA and skipB can be
 *               arbitrary values. The two lists do not intersect, so
 *               return null.
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes of listA is m.
 *      - The number of nodes of listB is n.
 *      - 1 <= m, n <= 3 * 10^4
 *      - 1 <= Node.val <= 10^5
 *      - 0 <= skipA <= m
 *      - 0 <= skipB <= n
 *      - intersectVal is 0 if listA and listB do not intersect.
 *      - intersectVal == listA[skipA] == listB[skipB] if listA and listB
 *        intersect.
 *
 * ----------------------------------------------------------------------------
 *  Follow up: Could you write a solution that runs in O(m + n) time and use
 *  only O(1) memory?
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <unordered_set>
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
 * Approach 1: Hash Set of Node Addresses
 *
 * Important:
 * Two nodes having the same value are not necessarily the same node.
 * The lists intersect only when both pointers refer to the exact same
 * object in memory. Therefore, store ListNode* addresses rather than values.
 *
 * Steps:
 *   1. If either list is empty, intersection is impossible, so return null.
 *   2. Traverse list A and insert the address of every node into an
 *      unordered_set.
 *   3. Traverse list B. For each node, check whether its address already
 *      exists in the set.
 *   4. The first matching address is the intersection node. Return it.
 *   5. If the traversal of list B finishes without a match, return null.
 *
 * Dry run 1: Lists intersect
 *
 *       A: 4 -> 1 -> 8 -> 4 -> 5
 *                    ^
 *       B: 5 -> 6 -> 1 -'
 *
 *   Suppose the node with value 8 is physically shared by both lists.
 *
 *   After traversing A:
 *       set = {address(4), address(1), address(8),
 *              address(4), address(5)}
 *
 *   Traverse B:
 *       - B's 5: address not found
 *       - B's 6: address not found
 *       - B's 1: address not found
 *       - B's 8: address found
 *
 *   Return the shared node with value 8. Notice that the two nodes with
 *   value 1 are different addresses, so equal values do not cause a match.
 *
 * Dry run 2: Lists do not intersect
 *
 *       A: 2 -> 6 -> 4
 *       B: 1 -> 5
 *
 *   After traversing A:
 *       set = {address(A2), address(A6), address(A4)}
 *
 *   Traverse B:
 *       - address(B1) is not found
 *       - address(B5) is not found
 *
 *   No address matches, so return nullptr.
 *
 * Complexity:
 *   Let m be the number of nodes in list A and n be the number of nodes
 *   in list B.
 *   - Time: O(m + n), because each list is traversed at most once.
 *   - Space: O(m), because the set stores every node address from list A.
 */
	static ListNode* getIntersectionNodeUsingSet(ListNode *headA, ListNode *headB){
		// An empty list cannot share a node with the other list.
		if (headA == nullptr || headB == nullptr)
			return nullptr;

		// Store node addresses from list A, not node values.
		unordered_set<ListNode*> list1;
		ListNode* temp = headA;
		while (temp != nullptr){
			list1.insert(temp);
			temp = temp->next;
		}

		// The first address from list B found in the set is the intersection.
		temp = headB;
		while (temp != nullptr){
			if (list1.contains(temp))
				return temp;
			temp = temp->next;
		}

		// No node address was shared by the two lists.
		return nullptr;
	}

	/*
 * ============================================================================
 * SLOW & FAST PATTERN 6: 160. Intersection of Two Linked Lists (O(N+M) Time | O(1) Space)
 * ============================================================================
 * Approach 2: Two Pointers (Optimal)
 * - Core Idea (The Track-Switching Synchronization Trick):
 *   Since List A and List B can have different lengths, we synchronize them by
 *   having each pointer switch to the other list's head once it hits `nullptr`.
 *
 * - The Math Proof (Why Distances Always Match):
 *   Let:
 *     - A = Non-intersecting nodes in List A
 *     - B = Non-intersecting nodes in List B
 *     - C = Shared intersecting tail nodes
 *
 *   - Pointer `pA` path : List A (A + C) + switched to B's head (B) = A + C + B
 *   - Pointer `pB` path : List B (B + C) + switched to A's head (A) = B + C + A
 *
 *   Since `A + C + B == B + C + A`, both pointers cover the exact same total
 *   distance and collide at the intersection node on the second lap!
 *   If there is no intersection ($C = 0$), both pointers reach `nullptr` at the
 *   exact same time ($A + B = B + A$), terminating the loop safely.
 *
 * - Quick Dry Run:
 *   List A : [4] -> [1] -> [8] -> [4] -> [5]  (A = 2, C = 3)
 *   List B : [5] -> [6] -> [1] -> [8] -> [4] -> [5]  (B = 3, C = 3)
 *
 *   - pA starts at [4], pB starts at [5]
 *   - pA travels [4, 1] then switches to List B's head ([5, 6, 1...])
 *   - pB travels [5, 6, 1] then switches to List A's head ([4, 1...])
 *   - Both pointers line up perfectly at node [8] on the second lap!
 *
 * - Complexity:
 *   Time  : O(N + M) — At most 2 passes over the combined length of both lists.
 *   Space : O(1)     — Only 2 pointers used in-place.
 * ============================================================================
 */
	static ListNode *getIntersectionNode(ListNode *headA, ListNode *headB){
		// If either list is empty, there can be no intersection.
		if (headA == nullptr || headB == nullptr)
			return nullptr;

		// Both pointers traverse both lists, switching to the other list's head
		ListNode* pA = headA;
		ListNode* pB = headB;

		// Loop until both pointers meet at the intersection node (or both hit nullptr)
		while (pA != pB){
			// If pA reaches the end of List A, switch to headB; otherwise move forward 1 step
			pA = (pA == nullptr) ? headB : pA->next;

			// If pB reaches the end of List B, switch to headA; otherwise move forward 1 step
			pB = (pB == nullptr) ? headA : pB->next;
		}

		// Returns either the intersection node or nullptr (if no intersection)
		return pA;
	}

	// Test function to build a linked list from a vector of integers
	static ListNode* buildList(const vector<int>& a){
		if (a.empty())
			return nullptr;

		auto* head = new ListNode(a[0]);
		ListNode* tail = head;
		for (size_t i = 1; i < a.size(); i++){
			tail->next = new ListNode(a[i]);
			tail = tail->next;
		}

		return head;
	}

	/*
	 * Build two lists with a physically shared suffix.
	 *
	 * listA and listB contain the values to display. When an intersection is
	 * requested, list B gets new nodes only before intersectionIndexB; its
	 * remaining nodes point to the existing suffix of list A.
	 */
	static pair<ListNode*, ListNode*> buildIntersectingLists(
		const vector<int>& listA,
		const vector<int>& listB,
		const int intersectionIndexA,
		const int intersectionIndexB
	){
		ListNode* headA = buildList(listA);

		if (intersectionIndexA == -1 || intersectionIndexB == -1)
			return {headA, buildList(listB)};

		ListNode* intersection = headA;
		for (int i = 0; i < intersectionIndexA; i++)
			intersection = intersection->next;

		ListNode* headB = nullptr;
		ListNode* tailB = nullptr;
		for (int i = 0; i < intersectionIndexB; i++){
			auto* node = new ListNode(listB[i]);
			if (headB == nullptr)
				headB = node;
			else
				tailB->next = node;
			tailB = node;
		}

		if (tailB == nullptr)
			headB = intersection;
		else
			tailB->next = intersection;

		return {headA, headB};
	}

	// Print the values of a linked list from head to nullptr.
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
	int n, m;

	cout << "Enter the number of nodes in List A: ";
	cin >> n;
	vector<int> listA(n);
	cout << "Enter the values for List A: ";
	for (int i = 0; i < n; i++)
		cin >> listA[i];

	cout << "Enter the number of nodes in List B: ";
	cin >> m;
	vector<int> listB(m);
	cout << "Enter the values for List B: ";
	for (int i = 0; i < m; i++)
		cin >> listB[i];

	cout << "Enter the index in List A where the intersection starts (0-based, -1 for no intersection): ";
	int intersectionIndexA;
	cin >> intersectionIndexA;

	cout << "Enter the index in List B where the intersection starts (0-based, -1 for no intersection): ";
	int intersectionIndexB;
	cin >> intersectionIndexB;

	const bool noIntersection =
		intersectionIndexA == -1 && intersectionIndexB == -1;
	const bool validIntersectionIndices =
		intersectionIndexA >= 0 &&
		intersectionIndexA < n &&
		intersectionIndexB >= 0 &&
		intersectionIndexB < m;

	if (!noIntersection && !validIntersectionIndices){
		cout << "Invalid intersection indices.\n";
		return;
	}

	if (!noIntersection){
		const int sharedLength = n - intersectionIndexA;
		if (m - intersectionIndexB != sharedLength){
			cout << "Invalid input: shared suffix lengths must be equal.\n";
			return;
		}

		for (int i = 0; i < sharedLength; i++){
			if (listA[intersectionIndexA + i] != listB[intersectionIndexB + i]){
				cout << "Invalid input: shared suffix values must be equal.\n";
				return;
			}
		}
	}

	// The shared suffix is connected to the same ListNode objects.
	auto [headA, headB] = MyLinkedList::buildIntersectingLists(
		listA, listB, intersectionIndexA, intersectionIndexB
	);

	cout << "\nList A: ";
	MyLinkedList::printList(headA);
	cout << "List B: ";
	MyLinkedList::printList(headB);

	auto* intersection =
		MyLinkedList::getIntersectionNodeUsingSet(headA, headB);

	if (intersection == nullptr){
		cout << "No intersection.\n";
		return;
	}

	int indexA = 0;
	for (auto* current = headA; current != intersection; current = current->next)
		indexA++;

	int indexB = 0;
	for (auto* current = headB; current != intersection; current = current->next)
		indexB++;

	cout << "Intersected at node with value " << intersection->val
		 << " at index " << indexA << " in List A and index "
		 << indexB << " in List B.\n";
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}