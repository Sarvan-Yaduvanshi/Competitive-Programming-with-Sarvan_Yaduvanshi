/*
Author: Sarvan Yaduvanshi
Created : 2026-10-03 03:16:14
*/

/*
 * Problem: Delete the Middle Node of a Linked List (LEETCODE 2095)
 * Difficulty: Medium
 * Company: Google, Amazon, Microsoft, Apple, Facebook etc.
 * Problem statement:
 * You are given the head of a linked list. Delete the middle node, and return the head of the modified linked list.
 * The middle node of a linked list of size n is the ⌊n / 2⌋th node from the start using 0-based indexing,
 * where ⌊x⌋ denotes the largest integer less than or equal to x.
 * For example, if n = 1, 2, 3, 4, or 5, then the middle node index is 0, 1, 1, 2, or 2, respectively.
 *
 * Example 1:
 * Input: head = [1,3,4,7,1,2,6] == 1->3->4->7->1->2->6
 * Output: [1,3,4,1,2,6]         == 1->3->4->1->2->6
 * Explanation: middle node with value 7 is removed.
 *
 * Example 2:
 * Input: head = [1,2,3,4], == 1->2->3->4
 * Output: [1,2,4]          == 1->2->4
 * Explanation: middle node with value 3 is removed.
 *
 * Example 3:
 * Input: head = [2,1]
 * Output: [2]
 * Explanation: The middle node with value 1 is removed.
 *
 * Constraints:
 *		  The number of nodes in the list is in the range [1, 10^5].
 *		  1 <= Node.val <= 10^5
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <random>
#include <chrono>
using namespace std;

struct ListNode{
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(nullptr) {}
};

// Function to delete the middle node of a linked list(Leetcode gives-us)
// Approach 1: Simple Approach to first cal length of linked list and then delete the middle node
// Time Complexity: O(n) + O(n/2) = O(n), Space Complexity: O(1)
static ListNode* deleteMiddle(ListNode* head){
	// Edge case: empty list or single node
	if (head == nullptr)
		return nullptr;

	// Calculate the size of the linked list
	int size = 0;
	ListNode* temp = head;
	while (temp->next != nullptr){
		size++;
		temp = temp->next;
	}

	// Handle head node deletion case separately
	if (size == 0){
		head = head->next;
		delete head;
		return nullptr;
	}

	// Find first half of the linked list and delete the middle node
	ListNode* curr = head;
	for (int i = 0; i < ((size + 1) / 2) - 1; i++)
		curr = curr->next;

	ListNode* deleteNode = curr->next;
	curr->next = deleteNode->next;
	delete deleteNode;

	return head;
}

/*
 * ============================================================================
 * SLOW & FAST PATTERN 2: 2095. Delete the Middle Node (O(N) Time | O(1) Space)
 * ============================================================================
 *
 * - GM Trick (Give `fast` a 2-Step Head Start Instead of Using a `prev` Pointer):
 *   In Pattern 1 (LC 876), starting `slow = head` and `fast = head` makes `slow`
 *   land ON the middle node.
 *   To delete the middle node, we need `slow` to stop 1 node BEFORE the middle!
 *   Instead of maintaining a 3rd pointer (`prev`), we give `fast` a 1-turn head
 *   start (`fast = head->next->next`) while keeping `slow = head`.
 *   Now `fast` finishes 1 iteration earlier, so `slow` stops 1 step before `middle`!
 *
 * - 3-Phase Execution:
 *     Phase 1 [Edge Case (0 or 1 Node)] :
 *       If `head == nullptr || head->next == nullptr`, deleting the only node
 *       leaves an empty list -> return `nullptr` (also ensures `head->next->next`
 *       is 100% safe to access!).
 *
 *     Phase 2 [Walk with `fast` Head-Start] :
 *       Start `slow = head` and `fast = head->next->next`.
 *       Loop while `fast != nullptr && fast->next != nullptr`.
 *       When loop ends, `slow` sits right BEFORE the middle node (`slow->next`).
 *
 *     Phase 3 [Unlink & Free Memory] :
 *       Save `middle = slow->next`, bypass it (`slow->next = middle->next`),
 *       and free heap memory (`delete middle`).
 *
 * - Quick Dry Run: head = [1, 2, 3, 4, 5]
 *     Init   : slow = [1], fast = [3]  (head->next->next)
 *     Step 1 : slow = [2], fast = [5]
 *     End    : `fast->next` is nullptr -> Loop stops!
 *              `slow` is at [2] (right before middle [3]).
 *     Delete : `middle` = [3], `[2]->next = [4]`, `delete [3]`.
 *     Output : [1] -> [2] -> [4] -> [5]
 *
 * - Complexity:
 *   Time  : O(N) — Single pass of N/2 steps.
 *   Space : O(1) — Only 2 pointers used in-place (no extra `prev` pointer needed).
 * ============================================================================
 */
static ListNode* deleteMiddleOptimal(ListNode* head){
	// Edge case: 0 or 1 node -> deleting middle leaves an empty list
	if (head == nullptr || head->next == nullptr)
		return nullptr;

	// GM Trick: Start `fast` 2 steps ahead so `slow` stops 1 node BEFORE middle
	ListNode* slow = head;
	ListNode* fast = head->next->next;

	// Traverse the list
	while (fast != nullptr && fast->next != nullptr){
		slow = slow->next; // Moves 1 step
		fast = fast->next->next; // Moves 2 steps
	}

	// `slow->next` is the exact middle node; unlink and free it
	ListNode* middle = slow->next;
	slow->next = middle->next; // Bypass the middle node

	delete middle; // Clean up removed node from heap memory

	return head;
}

// Build a linked list from a vector of integers
static ListNode* buildLinkedList(const vector<int>& values){
	int n = values.size();
	if (n == 0) return nullptr;

	ListNode* head = new ListNode(values[0]);
	ListNode* tail = head;
	for (int i = 1; i < n; ++i){
        tail->next = new ListNode(values[i]);
        tail = tail->next;
    }
	return head;
}

// Function to print the linked list
void printLinkedList(ListNode* head){
	while (head != nullptr){
		cout << head->val << "->";
		head = head->next;
	}
	cout << "nullptr" << endl;
}
static void solve(){
	int n;
	cout << "Enter the number of nodes in the linked list: ";
	cin >> n;

	vector<int> values(n);
	cout << "Enter " << n << " values for the linked list: ";
	for (int i = 0; i < n; ++i){
		cin >> values[i];
	}

	ListNode* head = buildLinkedList(values);
	cout << "Original Linked List: ";
	printLinkedList(head);

	head = deleteMiddleOptimal(head);
	cout << "Linked List after deleting the middle node: ";
	printLinkedList(head);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}
