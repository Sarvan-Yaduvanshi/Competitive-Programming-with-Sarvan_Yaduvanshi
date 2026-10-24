/*
Author: Sarvan Yaduvanshi
Created : 2026-10-24 01:02:03
*/

/*
 * ============================================================================
 *  142. Linked List Cycle II
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 142
 *  Difficulty : Medium
 *  Topics     : Hash Table, Linked List, Two Pointers
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the head of a linked list, return the node where the cycle begins.
 *  If there is no cycle, return null.
 *
 *  There is a cycle in a linked list if there is some node in the list that
 *  can be reached again by continuously following the next pointer.
 *  Internally, pos is used to denote the index of the node that tail's next
 *  pointer is connected to (0-indexed). It is -1 if there is no cycle. Note
 *  that pos is not passed as a parameter.
 *
 *  Do not modify the linked list.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      3 -> 2 -> 0 -> -4
 *           ^___________|
 *
 *  Input  : head = [3,2,0,-4], pos = 1
 *  Output : tail connects to node index 1
 *  Explanation: There is a cycle in the linked list, where tail connects to
 *               the second node.
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      1 -> 2
 *      ^____|
 *
 *  Input  : head = [1,2], pos = 0
 *  Output : tail connects to node index 0
 *  Explanation: There is a cycle in the linked list, where tail connects to
 *               the first node.
 *
 * ----------------------------------------------------------------------------
 *  Example 3:
 *
 *      1 -> NULL
 *
 *  Input  : head = [1], pos = -1
 *  Output : no cycle
 *  Explanation: There is no cycle in the linked list.
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of the nodes in the list is in the range [0, 10^4].
 *      - -10^5 <= Node.val <= 10^5
 *      - pos is -1 or a valid index in the linked-list.
 *
 * ----------------------------------------------------------------------------
 *  Follow up: Can you solve it using O(1) (i.e. constant) memory?
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
 * ============================================================================
 *  SLOW & FAST PATTERN 4: 142. Linked List Cycle II
 *  Time: O(N)  |  Space: O(1)
 * ============================================================================
 *
 *  Core Idea (Floyd's Cycle Entry Algorithm, 2 Phases):
 *
 *    Phase 1 [Detect Cycle + Find Meeting Point]
 *      slow moves 1 step, fast moves 2 steps, until slow == fast.
 *      If fast hits nullptr -> no cycle -> return nullptr.
 *
 *    Phase 2 [Find Cycle Entrance using L1 = L2]
 *      Reset slow = head. Keep fast at meeting point.
 *      Move BOTH 1 step at a time. Where they collide = cycle start.
 *
 * ----------------------------------------------------------------------------
 *  PICTURE:
 *
 *    head                 Cycle Start
 *     |<----- L1 = 3 ----->|
 *    [1]--->[2]--->[3]--->[15]--->[4]--->[13]
 *                           ^              v
 *                           |             [6]
 *                           |              v
 *                          [9]<---[8]<---[7] <== MEET (slow & fast)
 *                          |<-- L2 = 3 ---|
 *
 *    L1 = head -> cycle start            = 3  (1 -> 2 -> 3 -> 15)
 *    d  = cycle start -> meeting point   = 4  (15 -> 4 -> 13 -> 6 -> 7)
 *    L2 = meeting point -> cycle start   = 3  (7 -> 8 -> 9 -> 15)
 *    C  = cycle length = d + L2          = 7
 *
 * ----------------------------------------------------------------------------
 *  WHY 1: Why will slow and fast ALWAYS meet inside the cycle?
 *
 *    Once both are inside the cycle, look at the gap "fast -> slow"
 *    (steps fast must walk forward to reach slow).
 *
 *      fast moves 2, slow moves 1  ==>  gap shrinks by exactly 1 per step.
 *
 *    Gap can never jump over 0 (it drops by 1 only), so it MUST hit 0.
 *
 *      Example (slow at 15, fast at 6, gap = 4):
 *
 *        Step   slow   fast   gap(fast -> slow)
 *        ----   ----   ----   -----------------
 *         0      15      6          4
 *         1       4      8          3
 *         2      13     15          2
 *         3       6     13          1
 *         4       7      7          0   <== COLLISION
 *
 * ----------------------------------------------------------------------------
 *  WHY 2: Why does the meeting point lead us to the cycle start?
 *
 *    At collision (fast did 1 extra lap of length C = d + L2):
 *
 *      Slow distance = L1 + d
 *      Fast distance = L1 + d + (d + L2) = L1 + 2d + L2
 *      Fast = 2 x Slow:
 *
 *          2(L1 + d) = L1 + 2d + L2
 *          2L1 + 2d  = L1 + 2d + L2
 *                L1  = L2          (PROVEN!)
 *
 *    Check with picture: L1 = 3, L2 = 3.
 *
 *      Slow steps = L1 + d = 3 + 4 = 7  -> lands on node 7
 *      Fast steps = 2 x 7  = 14         -> 3 + 11 steps, 11 mod 7 = 4 -> node 7
 *
 *    Because L1 == L2, one pointer from head and one from meeting point,
 *    both walking 1 step, reach cycle start at the SAME time.
 *
 *    Note: if fast did k laps, L1 = (k-1)*C + L2. Extra laps just return to
 *    the same node, so the result is still the cycle start.
 *
 * ----------------------------------------------------------------------------
 *  Quick Dry Run: [1] -> [2] -> [3] -> [4] -> (back to [2])
 *    Cycle start = [2], L1 = 1, d = 2, L2 = 1, C = 3
 *
 *    Phase 1 (Find Meeting Point):
 *      Init   : slow = [1], fast = [1]
 *      Step 1 : slow = [2], fast = [3]
 *      Step 2 : slow = [3], fast = [2]
 *      Step 3 : slow = [4], fast = [4]   ==> Collision at [4]
 *
 *    Phase 2 (Reset slow = head, move both 1 step):
 *      Reset  : slow = [1], fast = [4]
 *      Step 1 : slow = [2], fast = [2]   ==> slow == fast
 *      Return [2]
 *
 * ----------------------------------------------------------------------------
 *  Complexity:
 *    Time  : O(N) - Phase 1 takes O(N), Phase 2 takes L1 <= N steps.
 *    Space : O(1) - Only 2 pointers, in-place.
 * ============================================================================
 */
    static ListNode* detectCycle(ListNode *head){
		// Handle edge cases: empty list or single node with no cycle
	    if (head == nullptr || head->next == nullptr)
	        return nullptr;

	    ListNode* slow = head;
	    ListNode* fast = head;

		// Phase 1: Detect if a cycle exists and find the collision point
	    while (fast != nullptr && fast->next != nullptr){
	        slow = slow->next;
	        fast = fast->next->next;

	    	// If `slow` and `fast` meet, a cycle exists
	        if (slow == fast){
	        	// Phase 2: Cycle found! Reset `slow` to `head` and walk both 1 step
	            slow = head;
	            while (slow != fast){
	                slow = slow->next;
	            	fast = fast->next; // Both move at 1x speed now!
	            }

	        	// Both pointers now sit on the exact start of the cycle
	        	return slow;
	        }
	    }

		// No cycle exists
		return nullptr;
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

	// Check for cycle and print the starting node of the cycle (if any)
	auto* cycleStart = MyLinkedList::detectCycle(head);
	cout << "Cycle starts at node with value: ";
	if (cycleStart != nullptr)
		cout << cycleStart->val << "\n";
	else
		cout << "No cycle detected.\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}
