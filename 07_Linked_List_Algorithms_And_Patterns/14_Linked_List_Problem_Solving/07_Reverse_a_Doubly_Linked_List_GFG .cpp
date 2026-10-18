/*
Author: Sarvan Yaduvanshi
Created : 2026-10-18 20:31:30
*/

/*
 * Problem: Reverse a Doubly Linked List (GeeksforGeeks)
 * Given the head of a doubly linked list, reverse the list and return the head of the reversed doubly linked list.
 *
 * Example 1:
 * Input: head = [1,2,3,4,5] => nullptr <- 1 <-> 2 <-> 3 <-> 4 <-> 5 -> nullptr
 * Output: [5,4,3,2,1] => nullptr <- 5 <-> 4 <-> 3 <-> 2 <-> 1 -> nullptr
 *
 * Example 2:
 * Input: head = [1,2] => nullptr <- 1 <-> 2 -> nullptr
 * Output: [2,1] => nullptr <- 2 <-> 1 -> nullptr
 *
 * Constraints:
 * The number of nodes in the list is the range [0, 5000].
 * -5000 <= Node.val <= 5000
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

class DoublyListNode{
private:
	struct Node{
		int val;
        Node* prev;
        Node* next;
        explicit Node(const int val) : val(val), prev(nullptr), next(nullptr) {}
	};

	Node* head;
public:
	DoublyListNode() : head(nullptr) {}

 /*
 * PATTERN 2: Reverse a Doubly Linked List (The In-Place Pointer Swap)
 * - Core Idea (Swapping `prev` and `next` at Every Node):
 *   Unlike a Singly Linked List (which needs 3 pointers), each node in a
 *   Doubly Linked List already stores both `prev` and `next`. Reversing the
 *   list simply means visiting every node and swapping its `prev` and `next`
 *   links using a single temporary pointer (`temp`).
 *
 * - Two Critical Interview Traps to Watch Out For:
 *     1. Moving to the Next Node (`curr = curr->prev`):
 *        Because we just swapped `curr->prev` and `curr->next`, the pointer
 *        that leads to the next unvisited node is now sitting inside `curr->prev`!
 *        So we advance using `curr = curr->prev` (NOT `curr->next`).
 *     2. Returning the New Head (`temp->prev`):
 *        Inside the loop, `temp` saves `curr->prev` BEFORE the swap. When `curr`
 *        reaches the last node (say [30]), `temp` holds [20]. After [30]'s links
 *        are swapped, [20]'s `prev` pointer (`temp->prev`) points directly to [30].
 *        So `temp->prev` is our new head!
 *
 * - The 4-Step Dance (Repeated inside while(curr != NULL)):
 *     Step 1 [Save Old prev]   : temp = curr->prev;
 *     Step 2 [Update prev]     : curr->prev = curr->next;
 *     Step 3 [Update next]     : curr->next = temp;
 *     Step 4 [Advance curr]    : curr = curr->prev;  // Old next is now in prev!
 *
 * - Visual Trace (NULL <- [10] <-> [20] <-> [30] -> NULL):
 *     Node [10]:
 *       Before : prev = NULL, next = [20]
 *       Swap   : prev = [20], next = NULL
 *       Move   : curr = curr->prev (moves to [20])
 *
 *     Node [20]:
 *       Before : prev = [10], next = [30]
 *       Swap   : prev = [30], next = [10]
 *       Move   : curr = curr->prev (moves to [30])
 *
 *     Node [30]:
 *       Before : prev = [20], next = NULL   (temp saves [20])
 *       Swap   : prev = NULL, next = [20]
 *       Move   : curr = curr->prev (moves to NULL, loop ends)
 *
 *     Final New Head:
 *       Since `temp` is at [20], and [20]'s new `prev` is [30],
 *       `temp->prev` gives us [30] (the new head)!
 *
 * - Complexity:
 *   Time Complexity  : O(N) — Single traversal through N nodes.
 *   Space Complexity : O(1) — Only 2 pointer variables (`curr`, `temp`).
 */
	static Node* reverseDLL(Node* head){
		// Edge case: Empty list or single node list
		if (head == nullptr || head->next == nullptr)
			return head;

		// Node* currNode = head;
		// Node* newHead = nullptr;
		// // Used to swap the prev and next pointers of each node
		// while (currNode != nullptr){
		// 	// Swap the prev and next pointers
		// 	swap(currNode->prev, currNode->next);
		//
		// 	// Before moving to the next node, update newHead to the current node
		// 	newHead = currNode;
		//     // Update currNode to the next node in the original list (which is now prev due to the swap)
		// 	currNode = currNode->prev;
		// }
		// return newHead;

		// Optimized version without using swap function
		Node* currNode = head;
		Node* temp = nullptr;

		while (currNode != nullptr){
			// Step 1: Save curr->prev in temp
			temp = currNode->prev;

			// Step 2: Swap curr->prev and curr->next
			currNode->prev = currNode->next;
			currNode->next = temp;

			// Step 3: Move to the next node in original list (now stored in curr->prev!)
			currNode = currNode->prev;
		}

		// Before updating head, check that temp isn't nullptr (handled by edge case,
		// but good defensive coding practice)
		if (temp != nullptr)
			head = temp->prev;

		return head;
	}

	// Approach 2: Using Recursion (Less Optimal)
	// Time Complexity  : O(N) — Each node is visited once.
	// Space Complexity : O(N) — Recursion stack can go as deep as N nodes
	static Node* reverseDLLRecursive(Node* head){
		// Base case: if the list is empty or we reach the end of the list
		if (head == nullptr)
			return head;

		// Step 1: Swap the prev and next pointers of the current node
		swap(head->prev, head->next);

		// Step 2: If the new prev (originally next) is nullptr, we've reached the new head
		if (head->prev == nullptr)
            return head;

		// Step 3: Recursion on the next node (which is now in head->prev after the swap)
		return reverseDLLRecursive(head->prev);
	}

	// Helper function to print the list (for testing)
	static void printList(Node* head){
		Node* curr = head;
		while (curr != nullptr){
			cout << curr->val << " <-> ";
			curr = curr->next;
		}
		cout << "nullptr\n";
	}

	// Helper function to create a doubly linked list from a vector (for testing)
	static Node* createList(const vector<int>& vals){
		if (vals.empty())
			return nullptr;

		Node* head = new Node(vals[0]);
		Node* curr = head;
		for (size_t i = 1; i < vals.size(); ++i){
			Node* newNode = new Node(vals[i]);
			curr->next = newNode;
			newNode->prev = curr;
			curr = newNode;
		}
		return head;
	}
};

static void solve() {
    int n; cin >> n;
	vector<int> vals(n);
	for (int i = 0; i < n; ++i)
		cin >> vals[i];

    auto head = DoublyListNode::createList(vals);

    cout << "Original List: ";
    DoublyListNode::printList(head);

    head = DoublyListNode::reverseDLL(head);
    cout << "Reversed List (Iterative): ";
    DoublyListNode::printList(head);

    // To test the recursive version, recreate the list
    head = DoublyListNode::createList(vals);
    head = DoublyListNode::reverseDLLRecursive(head);
    cout << "Reversed List (Recursive): ";
    DoublyListNode::printList(head);
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

