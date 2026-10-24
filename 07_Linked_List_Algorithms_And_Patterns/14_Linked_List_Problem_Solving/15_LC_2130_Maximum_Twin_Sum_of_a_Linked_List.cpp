/*
Author: Sarvan Yaduvanshi
Created : 2026-10-21 05:39:56
*/

/*
  Problem: Maximum Twin Sum of a Linked List (LeetCode 2130)
   In a linked list of size n, where n is even, the ith node (0-indexed) of
   the linked list is known as the twin of the (n-1-i)th node, if 0 <= i <= (n / 2) - 1.

     For example, if n = 4, then node 0 is the twin of node 3, and node 1 is the twin of node 2. These are the only nodes with twins for n = 4.

  The twin sum is defined as the sum of a node and its twin.
  Given the head of a linked list with even length, return the maximum twin sum of the linked list.

  Example 1:               idx: 0    1    3    4
    Input: head = [5,4,2,1],    5 -> 4 -> 2 -> 1
    Output: 6
    Explanation:
     - The nodes with twins present in this linked list are:
       - Node 0 is the twin of node 3 having a twin sum of 5 + 1 = 6.
       - Node 1 is the twin of node 2 having a twin sum of 4 + 2 = 6.

  Example 2:               idx: 0    1    3    4
    Input: head = [4,2,2,3],    4 -> 2 -> 2 -> 3
    Output: 7
    Explanation:
     - The nodes with twins present in this linked list are:
       - Node 0 is the twin of node 3 having a twin sum of 4 + 3 = 7.
       - Node 1 is the twin of node 2 having a twin sum of 2 + 2 = 4.

   Example 3:               idx: 0      1
     Input: head = [1,100000],   1 -> 100000
     Output: 100001
     Explanation:
      - There is only one node with a twin in this linked list having a twin sum of 1 + 100000 = 100001.

   Constraints:
     - The number of nodes in the list is an even integer in the range [2, 10^5].
     - Each node's value is an integer in the range [1, 10^5].
*/


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <chrono>

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

	// Approach 1: Iterative Approach (Two Pointers + Reverse Second Half)
	// Time Complexity: O(n), Space Complexity: O(1)
	// Consider: Can you solve this using O(1) space without modifying the original linked list structure?
	// Answer -> No, we cannot solve this problem using O(1) space without modifying the original linked list structure.
	//          But we can solve O(1) Space and without modifying the original linked list Used Doubly Linked List.
	//          Because in Doubly Linked List we can traverse the list in both directions, so we can find the twin nodes without modifying the original linked list structure.
	static int pairSum(ListNode* head){
		ListNode* slow = head;
		ListNode* fast = head;

		while (fast->next != nullptr && fast->next->next != nullptr){
			slow = slow->next;
			fast = fast->next->next;
		}

		ListNode* current = slow->next;
		ListNode* previous = nullptr;
		while (current != nullptr){
			ListNode* next = current->next;
			current->next = previous;
			previous = current;
			current = next;
		}

		int maximum_twin_sum = 0;
		ListNode* firstHalf = head;
		ListNode* secondHalf = previous;
		while (secondHalf != nullptr){
			maximum_twin_sum = max(maximum_twin_sum, firstHalf->val + secondHalf->val);
			firstHalf = firstHalf->next;
			secondHalf = secondHalf->next;
		}

		return maximum_twin_sum;
	}

	// Approach 2: Recursive Approach (Recursion + Two Pointers)
	// Time Complexity: O(n), Space Complexity: O(n)
	static int pairSumRecursive(ListNode* head){
		int maximum_twin_sum = 0;
        const ListNode* left = head;

		auto pairSumHelper = [&](auto&& self, ListNode* right) -> int {
			// Base case: If the right pointer reaches the end of the list, return 0.
			if (right == nullptr)
				return 0;

			// Recursive call to move the right pointer to the end of the list.
			self(self, right->next);

			// calculate the twin sum for the current pair of nodes (left and right) and update the maximum twin sum.
			maximum_twin_sum = max(maximum_twin_sum, left->val + right->val);

			// Move the left pointer to the next node for the next pair of twins.
			left = left->next;
            return maximum_twin_sum;
        };

        return pairSumHelper(pairSumHelper, head);
    }

	// Builds a linked list from a vector of integers and returns the head of the list.
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

	// Prints the linked list starting from the given head node.
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
	cout << "Enter the number of elements in the linked list: ";
	cin >> n;

	vector<int> a(n);
	cout << "Enter the elements of the linked list: ";
	for (int& x : a)
		cin >> x;

	cout << "Input Linked List: ";
	auto* head = MyLinkedList::buildList(a);
	MyLinkedList::printList(head);

	const int maximum_twin_sum = MyLinkedList::pairSum(head);
	cout << "Maximum Twin Sum of the Linked List: " << maximum_twin_sum << endl;

	// build the linked list again for the recursive approach since the original list was modified
	head = MyLinkedList::buildList(a);

	// Method 2: Recursive Approach
	const int maximum_twin_sum_recursive = MyLinkedList::pairSumRecursive(head);
	cout << "Maximum Twin Sum of the Linked List (Recursive Approach): " << maximum_twin_sum_recursive << endl;
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
