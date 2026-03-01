/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — FLOYD'S CYCLE DETECTION (Tortoise & Hare)                   ║
║           From Zero to Grandmaster — Core Pattern                          ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Detect Cycle (LeetCode 141)
 2. Find Cycle Start (LeetCode 142)
 3. Find Cycle Length
 4. Mathematical Proof

FLOYD'S CYCLE DETECTION ALGORITHM:
──────────────────────────────────
  Two pointers: slow (1 step), fast (2 steps)
  If cycle exists → they WILL meet inside the cycle
  If no cycle → fast reaches NULL

  WHY IT WORKS (Mathematical Proof):
  ─────────────────────────────────
  Let:
    L = distance from head to cycle start
    C = cycle length
    K = distance from cycle start to meeting point

  When slow enters cycle: slow has traveled L steps
  Fast has traveled 2L steps → fast is (2L - L) = L steps ahead in cycle
  → fast is L mod C steps ahead of slow in the cycle

  They meet when fast catches slow:
  → fast gains 1 step per iteration
  → they meet after (C - L%C) more steps

DRY RUN — Detect Cycle:
───────────────────────
  List: 1 → 2 → 3 → 4 → 5 → 3 (cycle at node 3)

          ┌────────────────────┐
          ▼                    │
     1 → 2 → 3 → 4 → 5 ──────┘

  Step 0: slow=1, fast=1
  Step 1: slow=2, fast=3     (slow+1, fast+2)
  Step 2: slow=3, fast=5
  Step 3: slow=4, fast=4     ← MEET! Cycle detected! ✅

DRY RUN — Find Cycle Start:
───────────────────────────
  After detection, reset slow to head, keep fast at meeting point.
  Both move 1 step. They meet at cycle start.

  Step 0: slow=1, fast=4
  Step 1: slow=2, fast=5
  Step 2: slow=3, fast=3     ← MEET at cycle start = 3 ✅

DRY RUN — Cycle Length:
──────────────────────
  From meeting point, move one pointer until it returns.
  Count: 3 → 4 → 5 → 3  →  Length = 3 ✅
*/

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// ═══════════════════════════════════════════════════════════════
// 1. DETECT CYCLE — O(n) time, O(1) space
// ═══════════════════════════════════════════════════════════════

bool hasCycle(Node* head) {
    Node* slow = head;
    Node* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;           // 1 step
        fast = fast->next->next;     // 2 steps

        if (slow == fast) return true;  // Cycle detected
    }
    return false;  // fast reached NULL → no cycle
}

// ═══════════════════════════════════════════════════════════════
// 2. FIND CYCLE START — O(n) time, O(1) space
// ═══════════════════════════════════════════════════════════════

Node* detectCycleStart(Node* head) {
    Node* slow = head;
    Node* fast = head;

    // Phase 1: Detect cycle
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }

    if (!fast || !fast->next) return nullptr;  // No cycle

    // Phase 2: Find start
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }

    return slow;  // Cycle start node
}

// ═══════════════════════════════════════════════════════════════
// 3. FIND CYCLE LENGTH — O(n) time, O(1) space
// ═══════════════════════════════════════════════════════════════

int cycleLength(Node* head) {
    Node* slow = head;
    Node* fast = head;

    // Find meeting point
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            // Count cycle length
            int length = 1;
            Node* temp = slow->next;
            while (temp != slow) {
                length++;
                temp = temp->next;
            }
            return length;
        }
    }
    return 0;  // No cycle
}

// ═══════════════════════════════════════════════════════════════
// FIND MIDDLE NODE — O(n) time, O(1) space
// ═══════════════════════════════════════════════════════════════
/*
  DRY RUN — Find Middle of [1, 2, 3, 4, 5]:
  Step 0: slow=1, fast=1
  Step 1: slow=2, fast=3
  Step 2: slow=3, fast=5
  fast->next = NULL → STOP
  Middle = slow = 3 ✅

  For even length [1, 2, 3, 4]:
  Step 0: slow=1, fast=1
  Step 1: slow=2, fast=3
  Step 2: slow=3, fast=NULL (fast->next is NULL)
  Middle = slow = 3 (second middle)
*/

Node* findMiddle(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  FLOYD'S CYCLE DETECTION — FAST & SLOW POINTER        ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Create list with cycle: 1 → 2 → 3 → 4 → 5 → 3
    cout << "═══ CYCLE DETECTION ═══\n";
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    Node* n4 = new Node(4);
    Node* n5 = new Node(5);
    n1->next = n2; n2->next = n3; n3->next = n4; n4->next = n5;
    n5->next = n3;  // Create cycle at node 3

    cout << "List: 1 → 2 → 3 → 4 → 5 → (cycle back to 3)\n";
    cout << "Has cycle: " << (hasCycle(n1) ? "YES" : "NO") << "\n";

    Node* cycleStart = detectCycleStart(n1);
    cout << "Cycle starts at: " << (cycleStart ? to_string(cycleStart->data) : "N/A") << "\n";
    cout << "Cycle length: " << cycleLength(n1) << "\n";

    // Break cycle for cleanup
    n5->next = nullptr;
    // Cleanup
    delete n1; delete n2; delete n3; delete n4; delete n5;

    // No cycle case
    cout << "\n═══ NO CYCLE ═══\n";
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    cout << "List: 1 → 2 → 3 → NULL\n";
    cout << "Has cycle: " << (hasCycle(head) ? "YES" : "NO") << "\n";

    // Find middle
    cout << "\n═══ FIND MIDDLE ═══\n";
    Node* mid = findMiddle(head);
    cout << "Middle of [1, 2, 3]: " << mid->data << "\n";

    // Cleanup
    Node* curr = head;
    while (curr) { Node* t = curr; curr = curr->next; delete t; }

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE: LeetCode 141, 142, 876, 202\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

