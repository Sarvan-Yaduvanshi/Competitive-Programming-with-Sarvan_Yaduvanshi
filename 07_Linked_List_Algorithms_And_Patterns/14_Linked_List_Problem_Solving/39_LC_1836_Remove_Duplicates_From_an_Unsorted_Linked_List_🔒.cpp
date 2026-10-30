/*
Author: Sarvan Yaduvanshi
Created : 2026-10-29 20:29:11
*/

/*
 * ============================================================================
 *  Remove Duplicates from Linked List
 * ============================================================================
 *  Platform   : GeeksforGeeks (Leetcode 1836 Premium)
 *  Problem No : N/A (GFG has no number)
 *  Difficulty : Easy
 *  Topics     : Linked List
 *  Companies  : Amazon, Intuit
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given a head of an unsorted linked list. Remove duplicate elements from
 *  this unsorted Linked List. When a value appears in multiple nodes, the
 *  node which appeared first should be kept, all other duplicates are to be
 *  removed.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      Before :  5 -> 2 -> 2 -> 4
 *      After  :  5 -> 2 -> 4
 *
 *  Input  : head = 5 -> 2 -> 2 -> 4
 *  Output : 5 -> 2 -> 4
 *  Explanation: Given linked list elements are 5 -> 2 -> 2 -> 4, in which
 *               2 is repeated only. So, we will delete the extra repeated
 *               elements 2 from the linked list and the resultant linked
 *               list will contain 5 -> 2 -> 4.
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      Before :  2 -> 2 -> 2 -> 2 -> 2
 *      After  :  2
 *
 *  Input  : head = 2 -> 2 -> 2 -> 2 -> 2
 *  Output : 2
 *  Explanation: Given linked list elements are 2 -> 2 -> 2 -> 2 -> 2, in
 *               which 2 is repeated. So, we will delete the extra repeated
 *               elements 2 from the linked list and the resultant linked
 *               list will contain only 2.
 *
 * ----------------------------------------------------------------------------
 *  Approach:
 *      - Traverse the list once using `curr`.
 *      - Store every value kept in an `unordered_set<int> seen`.
 *      - If `curr->val` is already in `seen`, unlink and delete the current
 *        node. Otherwise, insert its value and move `prev` forward.
 *      - The first occurrence is always preserved because a value is added to
 *        `seen` only when it is encountered for the first time.
 *
 *  Dry Run: head = 5 -> 2 -> 2 -> 4
 *      Initial: seen = {}, prev = nullptr, curr = 5
 *
 *      Step 1: 5 is not in `seen`.
 *              Add 5, move `prev` to 5.
 *              List: 5 -> 2 -> 2 -> 4
 *              seen = {5}
 *
 *      Step 2: 2 is not in `seen`.
 *              Add 2, move `prev` to 2.
 *              List: 5 -> 2 -> 2 -> 4
 *              seen = {5, 2}
 *
 *      Step 3: 2 is already in `seen`.
 *              Unlink and delete the current duplicate node.
 *              List: 5 -> 2 -> 4
 *              `prev` stays on the kept 2.
 *
 *      Step 4: 4 is not in `seen`.
 *              Add 4 and move `prev` to 4.
 *              List: 5 -> 2 -> 4
 *              seen = {5, 2, 4}
 *
 *      Final output: 5 -> 2 -> 4
 *
 * ----------------------------------------------------------------------------
 *  Complexity:
 *      Time  : O(n) average, because each node is visited once and hash-set
 *              lookup/insertion takes O(1) average time.
 *      Space : O(n) auxiliary space for the `seen` set.
 *      Note  : With pathological hash collisions, unordered-set operations
 *              can degrade, but O(n) is the expected complexity.
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - 1 <= size of linked list <= 10^6
 *      - 0 <= node.data <= 10^6
 *
 * ----------------------------------------------------------------------------
 *  Expected Complexities:
 *      Time Complexity   : O(n)
 *      Auxiliary Space   : O(n)
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <random>
#include <chrono>
#include <unordered_set>
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

	static ListNode* removeDuplicatesUnsorted(ListNode* head){
		// If the list is empty or has only one node, return the head as is
		if (head == nullptr || head->next == nullptr)
			return head;

		// Use an unordered_set to keep track of seen values
		unordered_set<int> seen;
		ListNode* curr = head; // Pointer to traverse the list
		ListNode* prev = nullptr; // Pointer to keep track of the previous node

		while (curr != nullptr){
			// Case 1: If the current value has already been seen, remove the current node
			if (seen.contains(curr->val)){
				prev->next = curr->next; // unlink the current node from the list
				delete curr; // free the memory of the current node

			} else{ // Case 2: If the current value is new, add it to the seen set and move prev pointer
				seen.insert(curr->val); // add
				prev = curr; // move prev pointer to current node
			}
			// Move to the next node in the list
			curr = prev->next;
		}

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

	ListNode* deleteNodeGivenTar(ListNode* head, const int tar){
		if (head == nullptr)
			return head;

		head->next = deleteNodeGivenTar(head->next, tar);

		if (head->val == tar)
			return head->next;

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

	auto* head = MyLinkedList::buildList(a);
	cout << "Original Linked List: ";
	MyLinkedList::printList(head);

	// Remove duplicates from the unsorted linked list
	head = MyLinkedList::removeDuplicatesUnsorted(head);
	cout << "Linked List after removing duplicates: ";
	MyLinkedList::printList(head);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}