/*
Author: Sarvan Yaduvanshi
Created : 2026-10-21 06:53:13
*/

/*
 Problem: Reorder List (LC 143)
 You are given the head of a singly linked-list. The list can be represented as:
    L0 → L1 → … → Ln - 1 → Ln
    Reorder the list to be on the following form:
    L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …

 You may not modify the values in the list's nodes. Only nodes themselves may be changed.

 Example 1:
    Input: head = [1,2,3,4], 1 -> 4 -> 2 -> 3
    Output: [1,4,2,3], 1 -> 4 -> 2 -> 3
    Explanation: L0 = 1, L1 = 2, L2 = 3, L3 = 4. Reorder them to L0 → L3 → L1 → L2.

 Example 2:
    Input: head = [1,2,3,4,5], 1 -> 5 -> 2 -> 4 -> 3
    Output: [1,5,2,4,3], 1 -> 5 -> 2 -> 4 -> 3
    Explanation: L0 = 1, L1 = 2, L2 = 3, L3 = 4, L4 = 5. Reorder them to L0 → L4 → L1 → L3 → L2.

 Constraints:
    The number of nodes in the list is in the range [1, 5 * 10^4].
    1 <= Node.val <= 1000
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
 * PATTERN 6B: 143. Reorder List (Optimal O(N) Time | O(1) Space)
 * ============================================================================
 * - Core Idea (Find Middle + Cut + Reverse 2nd Half + Alternating Merge):
 *   Notice that [1 -> 5 -> 2 -> 4 -> 3] is simply the 1st half [1 -> 2 -> 3]
 *   and the reversed 2nd half [5 -> 4] merged one node at a time (like a zipper)!
 *
 * - The 3-Phase Execution:
 *     Phase 1 [Find Middle & Cut List into Two Halves] :
 *       Use `slow` and `fast` pointers (`while (fast->next && fast->next->next)`).
 *       `slow` stops at the end of the 1st half, and `slow->next` starts the 2nd half.
 *       CRITICAL STEP: Set `slow->next = nullptr` to break the link between the
 *       two halves so we don't create a cycle!
 *
 *     Phase 2 [Reverse the Second Half (Pattern 1A)] :
 *       Reverse the 2nd half using `prev`, `curr`, `next`.
 *       After loop, `prev` is the head of the reversed 2nd half.
 *
 *     Phase 3 [Alternating Merge of Both Halves] :
 *       Start `first = head` (1st half) and `second = prev` (reversed 2nd half).
 *       While `second != nullptr`:
 *         1. Save next nodes : `nextFirst = first->next`, `nextSecond = second->next`
 *         2. Link 1st to 2nd : `first->next = second`
 *         3. Link 2nd to 1st : `second->next = nextFirst`
 *         4. Advance both    : `first = nextFirst`, `second = nextSecond`
 *
 * - Visual Trace: head = [1, 2, 3, 4, 5]
 *     Phase 1 (Find Middle & Cut):
 *       `slow` stops at [3]. Save 2nd half start = [4], then cut `[3]->next = nullptr`.
 *       1st Half : [1] -> [2] -> [3] -> nullptr
 *       2nd Half : [4] -> [5] -> nullptr
 *
 *     Phase 2 (Reverse 2nd Half):
 *       1st Half (`first`)  : [1] -> [2] -> [3] -> nullptr
 *       2nd Half (`second`) : [5] -> [4] -> nullptr
 *
 *     Phase 3 (Alternating Merge):
 *       - Step 1 (first = [1], second = [5]):
 *           Save `nextFirst = [2]`, `nextSecond = [4]`
 *           [1]->next = [5], [5]->next = [2]
 *           Advance `first = [2]`, `second = [4]`
 *           List so far: [1] -> [5] -> [2] -> [3] -> nullptr
 *
 *       - Step 2 (first = [2], second = [4]):
 *           Save `nextFirst = [3]`, `nextSecond = nullptr`
 *           [2]->next = [4], [4]->next = [3]
 *           Advance `first = [3]`, `second = nullptr`
 *           Final List : [1] -> [5] -> [2] -> [4] -> [3] -> nullptr
 *
 * - Complexity:
 *   Time  : O(N) — Find middle O(N/2) + Reverse O(N/2) + Merge O(N/2).
 *   Space : O(1) — Pure in-place pointer manipulation.
 * ============================================================================
 */
	static void reorderList(ListNode*& head){
	    if (head == nullptr)
	    	return;

    	// Phase 1: Find the end of the first half using Slow and Fast pointers
    	ListNode* slow = head;
    	ListNode* fast = head;
    	while (fast->next != nullptr && fast->next->next != nullptr){
    		slow = slow->next;
    		fast = fast->next->next;
    	}

    	// Phase 2: Cut the list in half and reverse the second half (Pattern 1A)
    	ListNode* current = slow->next;
    	slow->next = nullptr; // CRITICAL: Cut the link between 1st half and 2nd half!
    	ListNode* previous = nullptr;
    	while (current != nullptr){
    		ListNode* next = current->next;
    		current->next = previous;
    		previous = current;
    		current = next;
    	}

    	// Phase 3: Merge the first half and reversed second half alternately
    	ListNode* first = head; // Head of 1st half
    	ListNode* second = previous; // Head of reversed 2nd half
    	// Note: if list length is even or odd, so second half always <= first half in length,
    	// so we only need to check `second != nullptr` otherwise crash
    	while (second != nullptr){
    		// Step 1: Save the next nodes of both halves before breaking links
    		ListNode* nextFirst = first->next;
    		ListNode* nextSecond = second->next;

    		// Step 2: Place `second` right between `first` and `nextFirst`
    		first->next = second;
    		second->next = nextFirst;

    		// Step 3: Move both pointers forward to their saved next nodes
    		first = nextFirst;
    		second = nextSecond;
    	}
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

	// Helper function to print the linked list
    static void printList(ListNode* head){
    	if (head == nullptr){
            cout << "Empty List" << endl;
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

	cout << "Enter the values of the nodes: ";
	vector<int> a(n);
	for (int& x : a)
		cin >> x;

	auto* head = MyLinkedList::buildList(a);
	cout << "Original List: ";
	MyLinkedList::printList(head);

	MyLinkedList::reorderList(head);
	cout << "Reordered List: ";
	MyLinkedList::printList(head);
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
