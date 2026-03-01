/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           05 — REVERSE EVEN LENGTH GROUPS (LeetCode 2074)                  ║
║           From Zero to Grandmaster — Reversal Patterns                     ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Reverse Even Length Groups (LeetCode 2074)
 2. Reverse Between Positions (LeetCode 92) — Revisited with Dry Run
 3. Swap Kth Node from Start and End (LeetCode 1721)

REVERSE EVEN LENGTH GROUPS:
──────────────────────────
  The first group has 1 node, second has 2, third has 3, ...
  Reverse ONLY groups with EVEN length.
  Last group may have fewer nodes than expected.

  DRY RUN on [5→4→2→1→7→6→8→3→9]:
  ──────────────────────────────────
  Group 1: [5] (length=1, ODD)          → Keep:    5
  Group 2: [4, 2] (length=2, EVEN)      → Reverse: 2, 4
  Group 3: [1, 7, 6] (length=3, ODD)    → Keep:    1, 7, 6
  Group 4: [8, 3, 9] (length=3 < 4, ODD)→ Keep:    8, 3, 9

  Wait! Group 4 should have 4 elements but only has 3 → length 3 is ODD

  Result: 5 → 2 → 4 → 1 → 7 → 6 → 8 → 3 → 9

  Algorithm:
  1. For each group, count actual nodes available
  2. If count is even, reverse that segment
  3. Move to next group
*/

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

Node* buildList(int arr[], int n) {
    if (n == 0) return nullptr;
    Node* head = new Node(arr[0]);
    Node* tail = head;
    for (int i = 1; i < n; i++) { tail->next = new Node(arr[i]); tail = tail->next; }
    return head;
}

void printList(Node* head) {
    while (head) { cout << head->data; if (head->next) cout << " -> "; head = head->next; }
    cout << " -> NULL\n";
}

void freeList(Node* head) { while (head) { Node* t = head; head = head->next; delete t; } }

// ═══════════════════════════════════════════════════════════════
// 1. REVERSE EVEN LENGTH GROUPS — O(n) time, O(1) space
// ═══════════════════════════════════════════════════════════════

Node* reverseEvenLengthGroups(Node* head) {
    if (!head) return nullptr;

    Node* prev = head;  // Previous group's last node
    int groupSize = 2;  // Start from group 2 (group 1 has 1 node = odd, skip)

    while (prev->next) {
        // Count nodes in current group
        Node* curr = prev->next;
        int count = 0;
        for (int i = 0; i < groupSize && curr; i++) {
            count++;
            curr = curr->next;
        }

        if (count % 2 == 0) {
            // Reverse 'count' nodes after prev
            Node* revPrev = nullptr;
            Node* revCurr = prev->next;
            Node* tail = revCurr;  // First node becomes tail after reversal

            for (int i = 0; i < count; i++) {
                Node* next = revCurr->next;
                revCurr->next = revPrev;
                revPrev = revCurr;
                revCurr = next;
            }

            prev->next = revPrev;    // Connect to reversed head
            tail->next = revCurr;    // Connect tail to remaining
            prev = tail;
        } else {
            // Skip this group (odd length)
            for (int i = 0; i < count; i++) {
                prev = prev->next;
            }
        }

        groupSize++;
    }

    return head;
}

// ═══════════════════════════════════════════════════════════════
// 2. REVERSE BETWEEN (LeetCode 92) — Clean Version
// ═══════════════════════════════════════════════════════════════
/*
  DRY RUN — Reverse between L=2, R=4 on [1→2→3→4→5]:

  Step 0: Use dummy node
          dummy → 1 → 2 → 3 → 4 → 5 → NULL
          pre = dummy, move to pos L-1 = pos 1
          pre = node(1)

  Now repeatedly "pull" next node to front of sublist:

  Step 1: curr=2, pull 3 to front
          dummy → 1 → 3 → 2 → 4 → 5 → NULL

  Step 2: curr=2, pull 4 to front
          dummy → 1 → 4 → 3 → 2 → 5 → NULL

  Done (R - L = 2 iterations)
  Result: 1 → 4 → 3 → 2 → 5 → NULL ✅
*/

Node* reverseBetween(Node* head, int left, int right) {
    if (!head || left == right) return head;

    Node dummy(0);
    dummy.next = head;
    Node* pre = &dummy;

    for (int i = 1; i < left; i++) pre = pre->next;

    Node* curr = pre->next;
    for (int i = 0; i < right - left; i++) {
        Node* next = curr->next;
        curr->next = next->next;
        next->next = pre->next;
        pre->next = next;
    }

    return dummy.next;
}

// ═══════════════════════════════════════════════════════════════
// 3. SWAP KTH FROM START AND END (LeetCode 1721)
// ═══════════════════════════════════════════════════════════════
/*
  DRY RUN — K=2 on [1→2→3→4→5]:
  Kth from start = node(2)
  Kth from end = node(4)  (5 - 2 + 1 = 4th from start)
  Swap values: 2 ↔ 4
  Result: 1 → 4 → 3 → 2 → 5 → NULL ✅
*/

Node* swapNodes(Node* head, int k) {
    // Find kth from start
    Node* first = head;
    for (int i = 1; i < k; i++) first = first->next;

    // Find kth from end using two pointer
    Node* slow = head;
    Node* fast = first->next;
    while (fast) {
        slow = slow->next;
        fast = fast->next;
    }
    // slow = kth from end

    // Swap values
    swap(first->data, slow->data);
    return head;
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  REVERSE EVEN LENGTH GROUPS & MORE REVERSAL PATTERNS   ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Reverse Even Length Groups
    cout << "═══ REVERSE EVEN LENGTH GROUPS (LC 2074) ═══\n";
    int a1[] = {5, 4, 2, 1, 7, 6, 8, 3, 9};
    Node* head = buildList(a1, 9);
    cout << "Before: "; printList(head);
    cout << "Groups: [5] [4,2] [1,7,6] [8,3,9]\n";
    cout << "Even groups reversed: [5] [2,4] [1,7,6] [8,3,9]\n";
    head = reverseEvenLengthGroups(head);
    cout << "After:  "; printList(head);
    freeList(head);

    // Reverse Between
    cout << "\n═══ REVERSE BETWEEN L=2, R=4 (LC 92) ═══\n";
    int a2[] = {1, 2, 3, 4, 5};
    head = buildList(a2, 5);
    cout << "Before: "; printList(head);
    head = reverseBetween(head, 2, 4);
    cout << "After:  "; printList(head);
    freeList(head);

    // Swap Kth Nodes
    cout << "\n═══ SWAP KTH FROM START AND END (K=2, LC 1721) ═══\n";
    head = buildList(a2, 5);
    cout << "Before: "; printList(head);
    head = swapNodes(head, 2);
    cout << "After:  "; printList(head);
    freeList(head);

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE: LeetCode 2074, 92, 1721\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

