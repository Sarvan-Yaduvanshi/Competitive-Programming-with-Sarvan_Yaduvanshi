/*
Author: Sarvan Yaduvanshi
Created : 2026-10-03 03:16:14
*/

/*
 * Problem: 2095. Delete the Middle Node of a Linked List
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
 * Output: [1,3,4,1,2,6]
 * Explanation:
 * The above figure represents the given linked list. The indices of the nodes are written below.
 * Since n = 7, node 3 with value 7 is the middle node, which is marked in red.
 * We return the new list after removing this node.
 *
 * Example 2:
 * Input: head = [1,2,3,4]
 * Output: [1,2,4]
 * Explanation:
 * The above figure represents the given linked list.
 * For n = 4, node 2 with value 3 is the middle node, which is marked in red.
 *
 * Example 3:
 * Input: head = [2,1]
 * Output: [2]
 * Explanation:
 * The above figure represents the given linked list.
 * For n = 2, node 0 with value 2 is the middle node as well as the only node that is not removed.
 *
 * Constraints:
 *		  The number of nodes in the list is in the range [1, 10^5].
 *		  1 <= Node.val <= 10^5
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

// Approach 2: Using two pointer technique (Fast and Slow pointer)
// To find or delete the middle of a linked list in exactly one pass,
// advanced programmers use the Fast and Slow Pointers technique (often called the Tortoise and Hare algorithm).
//     * The Slow Pointer (Tortoise) moves one step at a time.
//     * The Fast Pointer (Hare) moves two steps at a time.
// Because the fast pointer moves exactly twice as fast, by the time it reaches the end of the list,
// the slow pointer will be sitting exactly in the middle.
// Time Complexity: O(n), Space Complexity: O(1)
static ListNode* deleteMiddleOptimal(ListNode* head){
	// Edge case: empty list or single node
	// If there's only 1 node, delete it and return nullptr
	if (head == nullptr || head->next == nullptr)
		return nullptr;

	ListNode* slow = head; // Slow pointer starts at the head
	// Give fast a 2-step head start so slow stops exactly before the middle
	ListNode* fast = head->next->next;

	// Traverse the list
	while (fast != nullptr && fast->next != nullptr){
		slow = slow->next; // Moves 1 step
		fast = fast->next->next; // Moves 2 steps
	}

	// 'slow' is now pointing to the node right before the middle one
	ListNode* deleteNode = slow->next;
	slow->next = deleteNode->next; // Bypass the middle node
	delete deleteNode; // Safely free the memory

	return head;
}

// Build a linked list from a vector of integers
ListNode* buildLinkedList(const vector<int>& values){
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
	// deleteMiddle(head);
	deleteMiddleOptimal(head);

	cout << "Original linked list: ";
	printLinkedList(head);
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
