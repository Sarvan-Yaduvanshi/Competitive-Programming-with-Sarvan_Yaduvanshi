/*
Author: Sarvan Yaduvanshi
Created : 2026-10-03 05:31:41
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
 * Problem : Identical Linked Lists (GFG)
 * Problem Statement:
 * Given two singly linked lists, head1 and head2, the task is to determine whether the two linked lists are identical.
 * Two linked lists are considered identical if they have the same number of nodes and
 * each corresponding node contains the same data in the same order.
 *
 * Example 1:
 * Input: head1: 1->2->3->4->5->6, head2: 99->59->42->20
 * Output: false
 * Explanation: The two linked lists have different lengths and different data in corresponding nodes, so they are not identical.
 *
 * Example 2:
 * Input: head1: 1->2->3->4->5, head2 : 1->2->3->4->5
 * Output: true
 * Explanation: The two linked lists have the same length and the same data in corresponding nodes, so they are identical.
 *
 * Constraints:
 * The number of nodes in both linked lists is in the range [0, 10^4].
 * 1 <= Node.val <= 10^5
 * Expected Complexities: Time Complexity: O(n), Space Complexity: O(1)
*/

struct ListNode{
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Function to check if two linked lists are identical
// Time Complexity: O(n), Space Complexity: O(1)
bool areIdentical(ListNode* head1, ListNode* head2){
    while (head1 != nullptr && head2 != nullptr){
        if (head1->val != head2->val)
            return false;
        head1 = head1->next;
        head2 = head2->next;
    }

    return head1 == nullptr && head2 == nullptr;
}

// Build linked list from vector of values
ListNode* buildLinkedList(const vector<int>& values){
    int n = values.size();
    if (n == 0)
        return nullptr;

    ListNode* head = new ListNode(values[0]);
    ListNode* tail = head;
    for (int i = 1; i < n; ++i){
        tail->next = new ListNode(values[i]);
        tail = tail->next;
    }
    return head;
}
void solve() {
    int n1, n2;
    cout << "Enter the number of nodes in the first linked list: ";
    cin >> n1;
    cout << "Enter the number of nodes in the second linked list: ";
    cin >> n2;

    vector<int> values1(n1), values2(n2);
    cout << "Enter " << n1 << " values for the first linked list: ";
    for (int i = 0; i < n1; ++i){
        cin >> values1[i];
    }

    cout << "Enter " << n2 << " values for the second linked list: ";
    for (int i = 0; i < n2; ++i){
        cin >> values2[i];
    }

    ListNode* head1 = buildLinkedList(values1);
    ListNode* head2 = buildLinkedList(values2);

    if (areIdentical(head1, head2)){
        cout << "The two linked lists are identical." << endl;
    } else {
        cout << "The two linked lists are not identical." << endl;
    }
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

