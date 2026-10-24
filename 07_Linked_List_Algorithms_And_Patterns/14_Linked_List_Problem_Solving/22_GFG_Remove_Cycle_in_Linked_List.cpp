/*
Author: Sarvan Yaduvanshi
Created : 2026-10-24 04:08:02
*/

/*
 * ============================================================================
 *  Remove Cycle in Linked List
 * ============================================================================
 *  Platform   : GeeksforGeeks
 *  Difficulty : Medium
 *  Topics     : Linked List, Two Pointers, Data Structures, Algorithms
 *  Companies  : Amazon, Microsoft, Samsung, Flipkart, Adobe, Snapdeal
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the head of a singly linked list. A cycle exists if the last node
 *  points back to a previous node, forming a loop. Remove the loop from the
 *  linked list if it exists.
 *
 *  Internally, the driver code uses a variable x (1-based indexing) to
 *  represent the position of the node to which the last node is connected.
 *
 *  The driver code will print "true" if the linked list is correctly
 *  modified, otherwise it will print "false".
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      1 -> 3 -> 4
 *           ^____|
 *
 *  Input  : head = [1,3,4], x = 2
 *  Output : true
 *  Explanation: The linked list contains a loop that begins at node x = 2.
 *               After removing the loop, the driver code prints true.
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      1 -> 8 -> 3 -> 4 -> NULL
 *
 *  Input  : head = [1,8,3,4], x = 0
 *  Output : true
 *  Explanation: The linked list does not contain a loop (x = 0).
 *
 * ----------------------------------------------------------------------------
 *  Example 3:
 *
 *      1 -> 2 -> 3 -> 4
 *      ^______________|
 *
 *  Input  : head = [1,2,3,4], x = 1
 *  Output : true
 *  Explanation: The linked list contains a loop that begins at node x = 1.
 *               After removing the loop, the driver code prints true.
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - 1 <= size of linked list <= 10^5
 *      - -10^5 <= node.data <= 10^5
 *      - 0 <= x <= size of linked list
 *
 * ----------------------------------------------------------------------------
 *  Expected Complexities:
 *      Time Complexity   : O(n)
 *      Auxiliary Space   : O(1)
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
 * PATTERN 5B: Remove / Break the Cycle (O(N) Time | O(1) Space)
 * ----------------------------------------------------------------------------
 * - Core Idea:
 *   To remove the cycle, we must find the LAST node of the loop and set its
 *   `next = nullptr`.
 *     Phase 1 : Detect cycle (`slow == fast`). If no cycle, return immediately.
 *     Phase 2 : Reset `slow = head` and move both 1 step until `slow == fast`.
 *               Now `slow` (and `fast`) sit directly on the Cycle Start!
 *     Phase 3 : Keep `slow` locked on Cycle Start, and walk `fast` around the
 *               loop while `fast->next != slow`.
 *               When the loop ends, `fast` is sitting on the LAST node of the
 *               cycle! Set `fast->next = nullptr` to break the loop.
 *
 * - Why Phase 3 (`while (fast->next != slow)`) Is GM-Level:
 *   Many people try to stop 1 node early during Phase 2 (`while (slow->next != fast->next)`),
 *   which FAILS when the cycle starts at `head` (e.g., [1] -> [2] -> [3] -> back to [1])
 *   because `slow` and `fast` are already equal at `head`!
 *   Finding Cycle Start first and then walking `while (fast->next != slow)` works
 *   for 100% of cases (including full circular lists where Cycle Start == `head`).
 * ============================================================================
 */
    static void removeLoop(ListNode* head) {
        // Edge case: If the list is empty or has only one node, no loop can exist
        if (head == nullptr || head->next == nullptr)
            return;

        ListNode* slow = head;
        ListNode* fast = head;

        // Phase 1: Detect cycle using Floyd's Tortoise and Hare algorithm
        while (fast != nullptr && fast->next != nullptr){
            slow = slow->next;
            fast = fast->next->next;

            // If slow and fast meet, a cycle is detected
            if (slow == fast){
                // Phase 2: Find the exact Cycle Start (Pattern 4)
                slow = head;
                while (slow != fast){
                    slow = slow->next;
                    fast = fast->next;
                }

                // Phase 3: `slow` and `fast` are both at Cycle Start.
                // Walk `fast` to the last node of the cycle (whose next is `slow`)
                while (fast->next != slow)
                    fast = fast->next;

                // Break the cycle!
                fast->next = nullptr;
                return;
            }
        }
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

	// Remove the cycle if it exists
    MyLinkedList::removeLoop(head);
    cout << "Linked List after removing cycle: ";
    MyLinkedList::printList(head);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}