/*
Author: Sarvan Yaduvanshi
Created : 2026-10-02 16:19:34
*/

/*
 * Problem: 237. Delete Node in a Linked List
* There is a singly-linked list head and we want to delete a node node in it.
* You are given the node to be deleted node. You will not be given access to the first node of head.
* All the values of the linked list are unique, and it is guaranteed that the given node node is not the last node in the linked list.
* Delete the given node. Note that by deleting the node, we do not mean removing it from memory. We mean:
*	* The value of the given node should not exist in the linked list.
*	* The number of nodes in the linked list should decrease by one.
*	* All the values before node should be in the same order.
*	* All the values after node should be in the same order.
* Custom testing:
  For the input, you should provide the entire linked list head and the node to be given node.
  node should not be the last node of the list and should be an actual node in the list.
  We will build the linked list and pass the node to your function.
  The output will be the entire list after calling your function.

  Example 1:
			4 -> 5 -> 1 -> 9 ,  Given node: 5
			Output: 4 -> 1 -> 9
  Example 2:
            4 -> 5 -> 1 -> 9 ,  Given node: 1
            Output: 4 -> 5 -> 9

  Constraints:
    The number of the nodes in the given list is in the range [2, 100].
    -100 <= Node.val <= 100
    The value of each node in the list is unique.
    The node to be deleted is in the list and is not a tail node.
*/

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <random>
#include <chrono>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;

    ListNode(int val) {
        this->val = val;
        this->next = nullptr;
    }
};

/*
 * ============================================================================
 * MATH & DELETION PATTERN 4A: 237. Delete Node in a Linked List (O(1) Time & Space)
 * ============================================================================
 *
 * - Core Idea (Clone Next Node's Identity + Delete `node->next`):
 *   To delete `node` normally, we need `prev->next = node->next`, which is
 *   impossible without `head`.
 *   Instead, since we CAN access `node->next`:
 *     1. Copy `node->next->val` into `node->val`.
 *     2. Save `nextNode = node->next`.
 *     3. Bypass `nextNode` (`node->next = nextNode->next`).
 *     4. Free `nextNode` (`delete nextNode`).
 *
 * - Classic Interview Follow-Up ("When does this trick FAIL?"):
 *   1. If `node` is the TAIL node (`node->next == nullptr`), there is no next
 *      node to steal from, and we cannot set `prev->next = nullptr`.
 *   2. If external systems hold raw pointers/references to `node->next` in
 *      memory, deleting `node->next` invalidates their pointers!
 *
 * - Quick Dry Run: [4] -> [5] -> [1] -> [9], node = [5]
 *     Step 1 : `node->val = node->next->val` ==> [4] -> [1] -> [1] -> [9]
 *     Step 2 : `nextNode = node->next`       ==> points to the 2nd [1]
 *     Step 3 : `node->next = nextNode->next` ==> 1st [1]->next points to [9]
 *     Step 4 : `delete nextNode`             ==> frees the 2nd [1]
 *     Result : [4] -> [1] -> [9]
 *
 * - Complexity:
 *   Time  : O(1) — Constant number of pointer/value operations.
 *   Space : O(1) — In-place modification.
 * ============================================================================
 */

static void deleteNode(ListNode* node) {
    // Save the node right after `node` (guaranteed to exist since `node` != tail)
    ListNode* nextNode = node->next;

    // Copy `nextNode`'s value into `node`
    node->val = nextNode->val;

    // Bypass `nextNode` and free its heap memory
    node->next = nextNode->next;
    delete nextNode; // Free the memory of the next node
}

static ListNode* buildList(const vector<int>& arr) {
    if (arr.empty())
        return nullptr;

    ListNode* head = new ListNode(arr[0]);
    ListNode* temp = head;

    for (int i = 1; i < arr.size(); i++) {
        temp->next = new ListNode(arr[i]);
        temp = temp->next;
    }
    return head;
}

static void printList(ListNode* head) {
    ListNode* temp = head;
    while (temp != nullptr) {
        cout << temp->val;
        if (temp->next != nullptr)
            cout << " -> ";
        temp = temp->next;
    }
    cout << '\n';
}

// Find the node with the given value in the linked list
ListNode* findNode(ListNode* head, int value) {
    ListNode* temp = head;
    while (temp != nullptr) {
        if (temp->val == value)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}

static void solve(){
    int n;
    cout << "Enter number of nodes: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter " << n << " values: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    ListNode* head = buildList(arr);
    int deleteValue;
    cout << "Enter value of node to delete: ";
    cin >> deleteValue;
    ListNode* node = findNode(head, deleteValue);
    if (node == nullptr) {
        cout << "Node does not exist.\n";
        return;
    }

    if (node->next == nullptr) {
        cout << "Cannot delete the last node.\n";
        return;
    }
    deleteNode(node);
    cout << "After deletion: ";
    printList(head);
}




int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}
