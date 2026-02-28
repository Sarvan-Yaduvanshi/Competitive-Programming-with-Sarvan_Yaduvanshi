/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Floyd's Cycle Detection — Linked List Cycle I & II
 *  Level   : Easy → Medium
 * ============================================================================
 *
 *  LC 141 — Linked List Cycle (detect)
 *           https://leetcode.com/problems/linked-list-cycle/
 *  LC 142 — Linked List Cycle II (find start)
 *           https://leetcode.com/problems/linked-list-cycle-ii/
 *  LC 457 — Circular Array Loop
 *           https://leetcode.com/problems/circular-array-loop/
 *  GFG    — https://practice.geeksforgeeks.org/problems/detect-loop-in-linked-list/
 *
 *  FLOYD'S ALGORITHM:
 *  ──────────────────
 *  Phase 1 — Detect: slow=1 step, fast=2 steps. If they meet → cycle exists.
 *  Phase 2 — Find start: Reset slow to head. Both move 1 step. Meet at cycle start.
 *
 *  PROOF WHY PHASE 2 WORKS:
 *  Let a = distance from head to cycle start
 *  Let b = distance from cycle start to meeting point
 *  Let c = cycle length
 *  At meeting: slow traveled (a + b), fast traveled (a + b + k*c) for some k
 *  fast = 2 * slow → a + b + k*c = 2(a + b) → k*c = a + b → a = k*c - b
 *  So from meeting point, traveling (a) more steps = traveling (k*c - b) = reaching cycle start!
 *
 * ============================================================================
 */
#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// LC 141: Detect cycle — O(N) time, O(1) space
bool hasCycle(ListNode *head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

// LC 142: Find cycle start — O(N) time, O(1) space
ListNode* detectCycle(ListNode *head) {
    ListNode *slow = head, *fast = head;

    // Phase 1: Detect meeting point
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            // Phase 2: Find cycle start
            slow = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow; // Cycle start
        }
    }
    return nullptr; // No cycle
}

int main() {
    // Create: 3 → 2 → 0 → -4 → (back to 2)
    ListNode* head = new ListNode(3);
    head->next = new ListNode(2);
    head->next->next = new ListNode(0);
    head->next->next->next = new ListNode(-4);
    head->next->next->next->next = head->next; // cycle to node 2

    cout << "Has cycle: " << hasCycle(head) << "\n"; // 1
    ListNode* start = detectCycle(head);
    if (start) cout << "Cycle starts at: " << start->val << "\n"; // 2

    return 0;
}

