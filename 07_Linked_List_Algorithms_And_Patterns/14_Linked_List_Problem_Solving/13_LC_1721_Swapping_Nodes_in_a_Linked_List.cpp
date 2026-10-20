/*
Author: Sarvan Yaduvanshi
Created : 2026-10-19 05:36:56
*/

/*
  Problem: Swapping Nodes in a Linked List (Leetcode 1721)
     You are given the head of a linked list, and an integer k.
     Return the head of the linked list after swapping the values of the kth node
     from the beginning and the kth node from the end (the list is 1-indexed).

     Example 1:
        Input: head = [1,2,3,4,5], k = 2
        Output: [1,4,3,2,5]
        Explanation: The 2nd node from the beginning is 2, and the 2nd node from the end is 4. return the list after swapping these nodes.

     Example  2:
        Input: head = [7,9,6,6,7,8,3,0,9,5], k = 5
        Output: [7,9,6,6,8,7,3,0,9,5]
        Explanation: The 5th node from the beginning is 7, and the 5th node from the end is 8. return the list after swapping these nodes.

     Constraints:
        The number of nodes in the list is n.
        1 <= k <= n <= 10^5
        0 <= Node.val <= 100
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

class MyLinkedList{
private:
    struct ListNode{
        int val;
        ListNode* next;
        explicit ListNode(const int val) : val(val), next(nullptr) {}
    };

    ListNode* head;

public:
    MyLinkedList() : head(nullptr) {}

 /*
 * ============================================================================
 * 1721. Swapping Nodes in a Linked List (Optimal 1-Pass O(N) Time | O(1) Space)
 * ============================================================================
 *
 * - Core Idea (Two-Pointer Fixed Gap of Size K):
 *   Instead of counting the total length N in one pass and walking N - k steps
 *   in a second pass, we find both nodes in a SINGLE pass by maintaining a
 *   gap of `k` nodes between `slow` and `fast`:
 *     1. Move `fast` forward `k` steps from `dummy`. Now `fast` sits directly
 *        on the k-th node from the beginning! Save it in `BeforeFirstKthNode`.
 *     2. Move both `slow` (starting at `dummy`) and `fast` one step at a time
 *        until `fast` reaches the last node (`fast->next == nullptr`).
 *     3. Because the gap between `slow` and `fast` is `k` steps, `slow->next`
 *        is now sitting directly on the k-th node from the END!
 *     4. Swap their `val` fields directly with `std::swap`.
 *
 * - Key Pointers:
 *     1. `BeforeFirstKthNode` : Holds the k-th node from the START (`fast` after k steps).
 *     2. `slow->next`         : Lands on the k-th node from the END when `fast` hits tail.
 *
 * - Quick Dry Run: head = [1, 2, 3, 4, 5], k = 2
 *     Start: [dummy] -> [1] -> [2] -> [3] -> [4] -> [5] -> nullptr
 *               ^
 *          slow, fast
 *
 *     Phase 1 (Move `fast` k = 2 steps forward):
 *       - i = 1: fast -> [1]
 *       - i = 2: fast -> [2]
 *       - Save `BeforeFirstKthNode = fast` (Node [2]).
 *       State: [dummy] -> [1] -> [2] -> [3] -> [4] -> [5]
 *                 ^               ^
 *               slow            fast (BeforeFirstKthNode)
 *
 *     Phase 2 (Move `slow` and `fast` together until `fast->next == nullptr`):
 *       - Step 1: slow -> [1], fast -> [3]
 *       - Step 2: slow -> [2], fast -> [4]
 *       - Step 3: slow -> [3], fast -> [5] (`fast->next` is nullptr -> STOP!)
 *       State: [dummy] -> [1] -> [2] -> [3] -> [4] -> [5]
 *                                 ^      ^      ^      ^
 *                     BeforeFirstKth   slow  slow->next fast
 *
 *     Phase 3 (Swap Values):
 *       - Swap `BeforeFirstKthNode->val` ([2]) and `slow->next->val` ([4]).
 *       - Final List: [1] -> [4] -> [3] -> [2] -> [5]
 *
 * - Complexity:
 *   Time  : O(N) — Single pass through the linked list.
 *   Space : O(1) — Only 3 pointers used in-place.
 * ============================================================================
 */

	static ListNode* swapNodes(ListNode* head, const int k){
    	// Edge Case: Empty List or Invalid k
	    if (head == nullptr || k <= 0)
	    	return head;

    	ListNode dummy(0);
    	dummy.next = head;

    	ListNode* slow = &dummy;
    	ListNode* fast = &dummy;

    	// Phase 1: Move `fast` k steps so it lands on the k-th node from the start
    	for (int i = 1; i <= k; i++)
    		fast = fast->next;

    	// Lock in the k-th node from the beginning
    	ListNode* firstKthNode = fast;

    	// Phase 2: Move both pointers until `fast` reaches the last node
    	// Since gap is k, `slow->next` lands on the k-th node from the end
    	while (fast->next != nullptr){
    		slow = slow->next;
    		fast = fast->next;
    	}

    	// Phase 3: Swap values of k-th node from start and k-th node from end
    	swap(firstKthNode->val, slow->next->val);

    	return dummy.next;
    }

	/*
 * ============================================================================
 * 1721 (Follow-Up): Swap Actual Nodes in a Linked List (No Value Modification)
 * ============================================================================
 *
 * - Problem Statement:
 *   Swap the k-th node from the beginning and the k-th node from the end by
 *   rewiring pointers ONLY (modifying `node->val` is strictly forbidden).
 *
 * - Core Idea (Stop 1 Step Before Both Target Nodes + 3-Step Pointer Swap):
 *   To swap two nodes (`firstK` and `secondK`) in a Singly Linked List, we
 *   need their predecessor nodes (`prevFirst` and `prevSecond`):
 *     1. Start `prevFirst`, `prevSecond`, and `fast` at `dummy`.
 *     2. Move `prevFirst` and `fast` forward `k - 1` steps:
 *          - `prevFirst` sits right BEFORE the k-th node from start.
 *          - Move `fast` 1 more step so `fast` sits ON the k-th node from start.
 *     3. Move `prevSecond` and `fast` together until `fast->next == nullptr`:
 *          - `prevSecond` lands right BEFORE the k-th node from the end!
 *     4. Identify targets:
 *          - `firstK  = prevFirst->next`
 *          - `secondK = prevSecond->next`
 *
 * - The Magic 3-Line Pointer Swap (Handles Normal AND Adjacent Nodes!):
 *     If `firstK == secondK` (same middle node), do nothing. Otherwise:
 *       Step 1: `prevFirst->next = secondK;`  (Link 1st predecessor to 2nd node)
 *       Step 2: `prevSecond->next = firstK;`  (Link 2nd predecessor to 1st node)
 *       Step 3: `swap(firstK->next, secondK->next);` (Swap their outgoing links!)
 *
 * - Why This Works Even When Nodes Are Adjacent (e.g., [1] -> [2] -> [3] -> [4], k=2):
 *     Here: prevFirst = [1], firstK = [2], prevSecond = [2], secondK = [3]
 *       - Step 1: [1]->next = [3]
 *       - Step 2: [2]->next = [2] (temporary self-loop on firstK)
 *       - Step 3: swap([2]->next, [3]->next)
 *                 ==> [3]->next becomes [2], and [2]->next becomes [4]!
 *       - Final : [1] -> [3] -> [2] -> [4] (No messy if-else needed!)
 *
 * - Quick Dry Run: head = [1, 2, 3, 4, 5], k = 2
 *     Start : [dummy] -> [1] -> [2] -> [3] -> [4] -> [5]
 *     1. After Phase 1 & 2:
 *          prevFirst  = [1], firstK  = [2]
 *          prevSecond = [3], secondK = [4]
 *     2. Execute 3-Line Pointer Swap:
 *          - prevFirst->next = secondK  ==> [1]->next = [4]
 *          - prevSecond->next = firstK  ==> [3]->next = [2]
 *          - swap([2]->next, [4]->next) ==> [4]->next = [3], [2]->next = [5]
 *     3. Result: [1] -> [4] -> [3] -> [2] -> [5]
 *
 * - Complexity:
 *   Time  : O(N) — Single pass through the list.
 *   Space : O(1) — Pure in-place pointer manipulation.
 * ============================================================================
 */

	static ListNode* swapNodesVersion2(ListNode* head, const int k) {
    	if (head == nullptr || k <= 0)
    		return head;

    	ListNode dummy(0);
    	dummy.next = head;

    	ListNode* prevFirst = &dummy;
    	ListNode* prevSecond = &dummy;
    	ListNode* fast = &dummy;

    	// Phase 1: Move `prevFirst` and `fast` (k - 1) steps to stop BEFORE 1st target
    	for (int i = 1; i < k; i++) {
    		prevFirst = prevFirst->next;
    		fast = fast->next;
    	}

    	// Move `fast` 1 more step so `fast` sits ON the k-th node from the start
    	fast = fast->next;

    	// Phase 2: Move `prevSecond` and `fast` until `fast` hits the last node
    	// Now `prevSecond` sits right BEFORE the k-th node from the end!
    	while (fast->next != nullptr) {
    		prevSecond = prevSecond->next;
    		fast = fast->next;
    	}

    	// Identify the two actual nodes to swap
    	ListNode* firstK = prevFirst->next;
    	ListNode* secondK = prevSecond->next;

    	// Edge case: If both pointers point to the exact same middle node, no swap needed
    	if (firstK == secondK)
    		return dummy.next;

    	// Phase 3: The 3-Line Universal Pointer Swap
    	prevFirst->next = secondK;
    	prevSecond->next = firstK;
    	swap(firstK->next, secondK->next);

    	return dummy.next;
    }

	// Helper function to print the linked list (for testing purposes)
	static void printList(const ListNode* head){
	    if (head == nullptr) {
	        cout << "Empty List\n";
	        return;
	    }

    	const ListNode* current = head;
    	while (current != nullptr){
    		cout << current->val;
	        if (current->next != nullptr)
	            cout << " -> ";
	        current = current->next;
    	}
    	cout << " -> nullptr\n";
    }

	// Helper function to build a linked list from a vector of integers
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
};

static void solve(){
	int n;
	cout << "Enter the number of nodes in the linked list: ";
	cin >> n;

	cout << "Enter the values of the nodes: ";
	vector<int> a(n);
	for (int& x : a)
		cin >> x;

	int k;
	cout << "Enter the value of k (1-indexed): ";
	cin >> k;

	auto* head = MyLinkedList::buildList(a);

	cout << "Original List: ";
	MyLinkedList::printList(head);

	// Swap nodes by value
	head = MyLinkedList::swapNodes(head, k);
	cout << "After Swapping Nodes by Value (k=" << k << "): ";
	MyLinkedList::printList(head);

	// Reset the list to original for the next test
	head = MyLinkedList::buildList(a);

	// Swap actual nodes (no value modification)
	head = MyLinkedList::swapNodesVersion2(head, k);
	cout << "After Swapping Actual Nodes (k=" << k << "): ";
	MyLinkedList::printList(head);

}
int main() {
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

