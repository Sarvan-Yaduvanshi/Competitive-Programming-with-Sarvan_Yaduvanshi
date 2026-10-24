/*
Author: Sarvan Yaduvanshi
Created : 2026-10-24 04:09:29
*/

/*
 * ============================================================================
 *  Cycle Length in Linked List
 * ============================================================================
 *  Platform   : GeeksforGeeks
 *  Difficulty : Medium
 *  Topics     : Linked List, Two Pointers, Data Structures
 *  Companies  : Amazon, Microsoft, Adobe, Flipkart
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the head of a linked list. A linked list contains a cycle if its
 *  last node is connected to a previous node. If the given list contains a
 *  cycle, return the length of the cycle. Otherwise, return 0.
 *
 *  Note: Internally, the driver code uses an integer x to represent the
 *  position (1-based indexing) of the node to which the last node is
 *  connected. If x = 0, it means last node points to null, which indicates
 *  there is no loop.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      1 -> 2 -> 3 -> 4 -> 5
 *           ^______________|
 *
 *  Input  : head = [1,2,3,4,5], x = 2
 *  Output : 4
 *  Explanation: There exists a loop in the linked list 2 -> 3 -> 4 -> 5,
 *               the length of the loop is 4.
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      19 -> 33 -> 10
 *      ^_____________|
 *
 *  Input  : head = [19,33,10], x = 1
 *  Output : 3
 *  Explanation: There exists a loop in the linked list 19 -> 33 -> 10,
 *               the length of loop is 3.
 *
 * ----------------------------------------------------------------------------
 *  Example 3:
 *
 *      1 -> 2 -> 3 -> NULL
 *
 *  Input  : head = [1,2,3], x = 0
 *  Output : 0
 *  Explanation: There is no loop.
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - 1 <= size of linked list <= 10^5
 *      - 1 <= node.data <= 10^4
 *      - 0 <= x < head.size()
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

    /*
    * ----------------------------------------------------------------------------
    * PATTERN 5A: Find the Length of the Cycle (O(N) Time | O(1) Space)
    * ----------------------------------------------------------------------------
    * - Core Idea:
    *   1. Run Floyd's Cycle Detection (`slow` +1, `fast` +2) until `slow == fast`.
    *   2. Once they meet inside the loop, keep `slow` fixed as an anchor and walk
    *      `slow = slow->next` 1 step at a time, counting steps until slow->next == fast.
    * - Quick Dry Run: [1] -> [2] -> [3] -> [4] -> (back to [2])
    *   1. `slow` and `fast` collide at [4].
    *   2. Start counting the length of the loop:
    *        - check if `slow->next` == `fast` (i.e., [4] == [4]) -> Not equal, move `slow` to [2], length = 1
    *        - check if `slow->next` == `fast` (i.e., [2] == [4]) -> Not equal, move `slow` to [3], length = 2
    *        - check if `slow->next` == `fast` (i.e., [3] == [4]) -> Not equal, move `slow` to [4], length = 3
    *        - check if `slow->next` == `fast` (i.e., [4] == [4]) -> Equal, stop counting, length = 4
    *        - Return the length of the loop.
    */

    static int lengthOfLoop(ListNode *head) {
        // If the list is empty or has only one node, there can't be a cycle
        if (head == nullptr || head->next == nullptr)
            return 0;

        ListNode* slow = head;
        ListNode* fast = head;

        // Phase 1: Detect cycle using Floyd's Tortoise and Hare algorithm
        while (fast != nullptr && fast->next != nullptr){
            slow = slow->next;
            fast = fast->next->next;

            // If slow and fast meet, a cycle is detected
            if (slow == fast){
                // Phase 2: Calculate the length of the cycle
                int cycle = 1;
                // Move slow pointer one step at a time until it meets fast again
                while (slow->next != fast){
                    cycle++;
                    slow = slow->next;
                }

                // Return the length of the cycle
                return cycle;
            }
        }

        //  No cycle exists.
        return 0;
    }
    // Test function to build a linked list from a vector of integers
    static ListNode* buildList(const vector<int>& a, int pos){
        if (a.empty())
            return nullptr;

        auto* head = new ListNode(a[0]);
        ListNode* tail = head;
        vector<ListNode*> nodes;
        nodes.push_back(head);

        for (int i = 1; i < a.size(); i++) {
            tail->next = new ListNode(a[i]);
            tail = tail->next;
            nodes.push_back(tail);
        }

        // Connect the last node to the node at index pos
        if (pos >= 0 && pos < (int)nodes.size()) {
            tail->next = nodes[pos];
        }

        return head;
    }

    // Test function to print the linked list (handles cycles)
    static void printList(ListNode* head) {
        if (head == nullptr) {
            cout << "Empty List\n";
            return;
        }

        unordered_set<ListNode*> visited;
        ListNode* current = head;

        while (current != nullptr) {
            // Detect revisiting a node
            if (visited.count(current)) {
                cout << "(cycle to node with value "
                     << current->val << ")\n";
                return;
            }

            visited.insert(current);
            cout << current->val;

            current = current->next;

            if (current != nullptr)
                cout << " -> ";
        }

        cout << " -> nullptr (no cycle)\n";
    }
};

static void solve(){
    int n;
    cout << "Enter the number of nodes in the linked list: ";
    cin >> n;

    int pos;
    cout << "Enter the position to create a cycle (-1 for no cycle): ";
    cin >> pos;

    cout << "Enter the values of the nodes: ";
    vector<int> a(n);
    for (int& x : a)
        cin >> x;

    auto* head = MyLinkedList::buildList(a, pos);
    cout << "Linked List: ";
    MyLinkedList::printList(head);

	int cycleLength = MyLinkedList::lengthOfLoop(head);

    if (cycleLength > 0) {
        cout << "There exists a loop in the linked list: ";
        MyLinkedList::printList(head);
        cout << "The length of the loop is: " << cycleLength << "\n";
    } else {
        cout << "There is no loop in the linked list.\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}