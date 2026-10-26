/*
Author: Sarvan Yaduvanshi
Created : 2026-10-25 15:31:07
*/

/*
 * ============================================================================
 *  328. Odd Even Linked List
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 328
 *  Difficulty : Medium
 *  Topics     : Linked List
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the head of a singly linked list, group all the nodes with odd
 *  indices together followed by the nodes with even indices, and return the
 *  reordered list.
 *
 *  The first node is considered odd, and the second node is even, and so on.
 *
 *  Note that the relative order inside both the even and odd groups should
 *  remain as it was in the input.
 *
 *  You must solve the problem in O(1) extra space complexity and O(n) time
 *  complexity.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      Before :  1 -> 2 -> 3 -> 4 -> 5
 *      index  : (1)  (2)  (3)  (4)  (5)
 *      After  :  1 -> 3 -> 5 -> 2 -> 4
 *                (odd group)   (even group)
 *
 *  Input  : head = [1,2,3,4,5]
 *  Output : [1,3,5,2,4]
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      Before :  2 -> 1 -> 3 -> 5 -> 6 -> 4 -> 7
 *      index  : (1)  (2)  (3)  (4)  (5)  (6)  (7)
 *      After  :  2 -> 3 -> 6 -> 7 -> 1 -> 5 -> 4
 *                (odd group)        (even group)
 *
 *  Input  : head = [2,1,3,5,6,4,7]
 *  Output : [2,3,6,7,1,5,4]
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in the linked list is in the range [0, 10^4].
 *      - -10^6 <= Node.val <= 10^6
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
 * ============================================================================
 * MERGE & SORT PATTERN 2B: 328. Odd Even Linked List (O(N) Time | O(1) Space)
 * ============================================================================
 *
 * - Core Idea (Leapfrog 2-Bucket Stitching):
 *   Since the 1st node is always Odd (`odd = head`) and the 2nd node is always
 *   Even (`even = head->next`), we save `evenHead = even` and leapfrog both
 *   pointers over each other in lockstep:
 *     1. `odd->next = even->next;`  (Connect current odd to next odd)
 *     2. `odd = odd->next;`         (Advance `odd` tail)
 *     3. `even->next = odd->next;`  (Connect current even to next even)
 *     4. `even = even->next;`       (Advance `even` tail)
 *   Finally, attach `odd->next = evenHead`!
 *
 * - Quick Dry Run: [1] -> [2] -> [3] -> [4] -> [5] -> nullptr
 *     Init   : odd = [1], even = [2], evenHead = [2]
 *     Step 1 :
 *       - odd->next = even->next ([3]), odd moves to [3]   (Odds  : [1] -> [3])
 *       - even->next = odd->next ([4]), even moves to [4]  (Evens : [2] -> [4])
 *     Step 2 :
 *       - odd->next = even->next ([5]), odd moves to [5]   (Odds  : [1] -> [3] -> [5])
 *       - even->next = odd->next (nullptr), even = nullptr (Evens : [2] -> [4] -> nullptr)
 *     End    : `even == nullptr` -> Loop stops!
 *     Stitch : `odd->next = evenHead` ([5]->next = [2]).
 *     Result : [1] -> [3] -> [5] -> [2] -> [4] -> nullptr
 *
 * - Complexity:
 *   Time  : O(N) — Single pass through the list.
 *   Space : O(1) — Only 3 pointers (`odd`, `even`, `evenHead`) used in-place.
 * ============================================================================
 */
	static ListNode* oddEvenList(ListNode* head){
		// Handle edge cases: empty list or single node list
		if (head == nullptr || head->next == nullptr)
			return head;

		ListNode* odd = head;          // Tail of Odd-indexed bucket
		ListNode* even = head->next;   // Tail of Odd-indexed bucket
		ListNode* evenHead = even;     // Save start of Even bucket to attach at end

		// Since `even` is always ahead of `odd`, check `even` and `even->next`
		while (even != nullptr && even->next != nullptr){
			odd->next = even->next; // Link current Odd to next Odd
			odd = odd->next;        // Move `odd` forward

			even->next = odd->next;  // Link current Even to next Even
			even = even->next;       // Move `even` forward
		}

		// Connect the tail of the Odd list to the head of the Even list
		odd->next = evenHead;
		return head;
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

	cout << "Enter the values of the nodes: ";
	vector<int> a(n);
	for (int& x : a)
		cin >> x;

	auto* head = MyLinkedList::buildList(a);
	cout << "Original Linked List: ";
	MyLinkedList::printList(head);

	// Reorder the linked list using the oddEvenList function
	head = MyLinkedList::oddEvenList(head);
	cout << "Reordered Linked List (Odd-Even): ";
	MyLinkedList::printList(head);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}
