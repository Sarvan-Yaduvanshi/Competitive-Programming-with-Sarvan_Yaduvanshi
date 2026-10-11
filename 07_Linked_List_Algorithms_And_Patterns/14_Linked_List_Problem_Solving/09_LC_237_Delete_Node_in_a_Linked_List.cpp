/*
Author: Sarvan Yaduvanshi
Created : 2026-10-02 16:19:34
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
struct ListNode {
    int val;
    ListNode* next;

    ListNode(int val) {
        this->val = val;
        this->next = nullptr;
    }
};
ListNode* buildList(const vector<int>& arr) {
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
void printList(ListNode* head) {
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
/*
    IMPORTANT:
    We DON'T have head.
    We only have the node that needs to be deleted.
    Example:  4 -> 5 -> 1 -> 9
                   ^
                  node
    We cannot directly remove 5 because we don't know 4.
    Instead:
        1. Copy next node's value into current node.
        2. Skip the next node.
    Before:
        4 -> [5] -> [1] -> 9
              node
    Copy:
        4 -> [1] -> [1] -> 9
    Then skip old 1:
        4 -> 1 -> 9
*/
void deleteNode(ListNode* node) {
    // Safety check
    if (node == nullptr || node->next == nullptr)
        return;

    // Save next node
    ListNode* nextNode = node->next;

    // Copy next node's value
    node->val = nextNode->val;

    // Skip next node
    node->next = nextNode->next;

    // Free the skipped node
    delete nextNode;
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
