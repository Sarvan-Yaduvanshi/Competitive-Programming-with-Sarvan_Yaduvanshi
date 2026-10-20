/*
Author: Sarvan Yaduvanshi
Created : 2026-10-19 05:35:39
*/

/*
Problem: Swap Nodes in Pairs (Leetcode 24)
    Given a linked list, swap every two adjacent nodes and return its head.
    You must solve the problem without modifying the values in the list's nodes
    (i.e., only nodes themselves may be changed.)

    Example 1:
    Input: head = [1,2,3,4], 1 -> 2 -> 3 -> 4
    Output: [2,1,4,3], 2 -> 1 -> 4 -> 3
    Explanation: The pairs (1, 2) and (3, 4) are reverse pointer each other.

    Example 2:
    Input: head = [],  nullptr
    Output: [], nullptr

    Constraints:
    The number of nodes in the list is in the range [0, 100].
    0 <= Node.val <= 100
*/
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <random>
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

 /*
 * ============================================================================
 * 24. Swap Nodes in Pairs (Optimal O(N) Time | O(1) Space)
 * ============================================================================
 *
 * - Core Idea (K-Group Reversal Simplified for K = 2):
 *   Swapping adjacent pairs is just "Reverse Nodes in K-Group" where K = 2.
 *   Because a pair only has 2 nodes (`first` and `second`), we don't need an
 *   inner reversal loop. We simply stand at `previous` (the node right BEFORE
 *   the pair) and rewire 3 arrows in-place!
 *
 * - Key Pointers:
 *     1. `previous` : Node right BEFORE the current pair (starts at `dummy`).
 *     2. `first`    : 1st node of the pair (`previous->next`). Becomes 2nd after swap.
 *     3. `second`   : 2nd node of the pair (`first->next`). Becomes 1st after swap.
 *
 * - Loop Condition (`while (previous->next && previous->next->next)`):
 *   Ensures at least 2 nodes exist ahead of `previous` to form a full pair.
 *   If only 1 node (or 0 nodes) remains, the loop stops and leaves it untouched.
 *
 * - The 4-Step Pointer Swap (Order Matters!):
 *     Before : [previous] -> [first] -> [second] -> [nextPair...]
 *
 *     Step 1 [Link 1st to Rest] : `first->next = second->next;`
 *            ([first] now points past [second] to [nextPair...])
 *     Step 2 [Flip 2nd to 1st]  : `second->next = first;`
 *            ([second] now points backward to [first])
 *     Step 3 [Link Prev to 2nd] : `previous->next = second;`
 *            ([previous] now connects to [second] as the new pair head)
 *     Step 4 [Advance Anchor]   : `previous = first;`
 *            (Since `first` is now at the END of the swapped pair, move
 *             `previous` to `first` so it sits right before the next pair!)
 *
 *     After  : [previous] -> [second] -> [first] -> [nextPair...]
 *                                           ^
 *                                    new `previous`
 *
 * - Quick Dry Run: head = [1, 2, 3, 4]
 *     Start  : [dummy] -> [1] -> [2] -> [3] -> [4] -> nullptr
 *                 ^
 *             previous
 *
 *     Pair 1 (first = [1], second = [2]):
 *       1. [1]->next = [3]         (first->next = second->next)
 *       2. [2]->next = [1]         (second->next = first)
 *       3. [dummy]->next = [2]     (previous->next = second)
 *       4. previous = [1]          (move anchor to end of swapped pair)
 *       List : [dummy] -> [2] -> [1] -> [3] -> [4] -> nullptr
 *                                 ^
 *                             previous
 *
 *     Pair 2 (first = [3], second = [4]):
 *       1. [3]->next = nullptr     (first->next = second->next)
 *       2. [4]->next = [3]         (second->next = first)
 *       3. [1]->next = [4]         (previous->next = second)
 *       4. previous = [3]          (move anchor to end of swapped pair)
 *       List : [dummy] -> [2] -> [1] -> [4] -> [3] -> nullptr
 *                                               ^
 *                                           previous
 *
 *     End    : `previous->next` is nullptr -> Loop terminates! Return [2].
 *
 * - Complexity:
 *   Time  : O(N) — Visits each pair once in a single pass.
 *   Space : O(1) — Pure in-place pointer manipulation.
 * ============================================================================
 */
    static ListNode* swapNodesPairs(ListNode* head){
        // Edge Case: If the list is empty or has only one node, return it as-is.
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode dummy(0);
        dummy.next = head;

        // `previous` always sits right before the pair we are about to swap
        ListNode* previous = &dummy;

        // Only swap if a full pair (first AND second) exists ahead
        while (previous ->next != nullptr && previous ->next->next != nullptr){
            ListNode* first = previous ->next; // 1st node of the pair
            ListNode* second = first->next; // 2nd node of the pair

            // Step 1-3: Rewire the 3 pointers to swap `first` and `second`
            first->next = second->next; // Connect `first` to the node after the pair
            second->next = first; // Flip `second` to point back to `first`
            previous ->next = second; // Connect previous part to `second` (new pair head)

            // Step 4: Move `previous` to `first` (now at the end of the swapped pair)
            previous  = first;
        }

        return dummy.next;
    }

    static ListNode* buildList(const vector<int>& values){
        if (values.empty())
            return nullptr;

        ListNode* head = new ListNode(values[0]);
        ListNode* tail = head;
        for (int i = 1; i < values.size(); i++){
            tail->next = new ListNode(values[i]);
            tail = tail->next;
        }

        return head;
    }

    static void printList(const ListNode* head){
        if (head == nullptr){
            cout << "List is empty\n";
            return;
        }

        const ListNode* temp = head;
        while (temp != nullptr){
            cout << temp->val << " -> ";
            temp = temp->next;
        }

        cout << "nullptr\n";
    }
};

static void solve() {
    int n;
    cout << "Enter the number of nodes in the linked list: ";
    cin >> n;
    cout << "Enter the values of the linked list nodes: ";
    vector<int> values(n);
    for (int& val : values)
        cin >> val;

    auto head = MyLinkedList::buildList(values);
    cout << "Original List: ";
    MyLinkedList::printList(head);

    auto newHead = MyLinkedList::swapNodesPairs(head);
    cout << "List after swapping nodes in pairs: ";
    MyLinkedList::printList(newHead);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    solve();
    return 0;
}

