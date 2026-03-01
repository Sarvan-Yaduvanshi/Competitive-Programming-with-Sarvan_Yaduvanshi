/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — REORDER LIST, ROTATE LIST, ODD-EVEN LIST                    ║
║           (LeetCode 143, 61, 328) — Structural Modifications              ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Reorder List: L0→Ln→L1→Ln-1→... (LeetCode 143)
 2. Rotate List by K (LeetCode 61)
 3. Odd-Even Linked List (LeetCode 328)
 4. Swap Nodes in Pairs (LeetCode 24)

DRY RUN — Reorder List [1→2→3→4→5]:
────────────────────────────────────
  Step 1: Find middle → slow at 3
          First half:  1 → 2 → 3
          Second half: 4 → 5

  Step 2: Reverse second half
          4 → 5 becomes 5 → 4

  Step 3: Interleave
          Pick 1, pick 5: 1 → 5
          Pick 2, pick 4: 1 → 5 → 2 → 4
          Pick 3:         1 → 5 → 2 → 4 → 3

  Result: 1 → 5 → 2 → 4 → 3 → NULL ✅

DRY RUN — Rotate by K=2 on [1→2→3→4→5]:
────────────────────────────────────────
  Length = 5, effective K = 2 % 5 = 2
  New head is at position (5 - 2) = 3rd node (0-indexed)

  Step 1: Find tail (5), connect to head → circular: 1→2→3→4→5→1→...
  Step 2: Move (5-2) = 3 steps from head → land at node 3
  Step 3: New head = node 3->next = node 4
          Break: node 3->next = NULL

  Result: 4 → 5 → 1 → 2 → 3 → NULL ✅

DRY RUN — Odd-Even on [1→2→3→4→5]:
──────────────────────────────────
  Odd indices:  1 → 3 → 5
  Even indices: 2 → 4
  Connect odd tail to even head:
  Result: 1 → 3 → 5 → 2 → 4 → NULL ✅
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

Node* reverseList(Node* head) {
    Node* prev = nullptr;
    while (head) { Node* n = head->next; head->next = prev; prev = head; head = n; }
    return prev;
}

// ═══════════════════════════════════════════════════════════════
// 1. REORDER LIST — O(n) time, O(1) space
// ═══════════════════════════════════════════════════════════════

void reorderList(Node* head) {
    if (!head || !head->next) return;

    // Find middle
    Node* slow = head;
    Node* fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Reverse second half
    Node* second = reverseList(slow->next);
    slow->next = nullptr;

    // Interleave
    Node* first = head;
    while (second) {
        Node* tmp1 = first->next;
        Node* tmp2 = second->next;
        first->next = second;
        second->next = tmp1;
        first = tmp1;
        second = tmp2;
    }
}

// ═══════════════════════════════════════════════════════════════
// 2. ROTATE LIST — O(n) time, O(1) space
// ═══════════════════════════════════════════════════════════════

Node* rotateRight(Node* head, int k) {
    if (!head || !head->next || k == 0) return head;

    // Find length and tail
    int len = 1;
    Node* tail = head;
    while (tail->next) { len++; tail = tail->next; }

    k = k % len;
    if (k == 0) return head;

    // Make circular
    tail->next = head;

    // Find new tail (len - k - 1 steps from head... or len - k steps)
    int stepsToNewTail = len - k;
    Node* newTail = head;
    for (int i = 1; i < stepsToNewTail; i++) {
        newTail = newTail->next;
    }

    Node* newHead = newTail->next;
    newTail->next = nullptr;

    return newHead;
}

// ═══════════════════════════════════════════════════════════════
// 3. ODD-EVEN LINKED LIST — O(n) time, O(1) space
// ═══════════════════════════════════════════════════════════════

Node* oddEvenList(Node* head) {
    if (!head || !head->next) return head;

    Node* odd = head;
    Node* even = head->next;
    Node* evenHead = even;

    while (even && even->next) {
        odd->next = even->next;
        odd = odd->next;
        even->next = odd->next;
        even = even->next;
    }

    odd->next = evenHead;
    return head;
}

// ═══════════════════════════════════════════════════════════════
// 4. SWAP NODES IN PAIRS — O(n) time, O(1) space
// ═══════════════════════════════════════════════════════════════
/*
  DRY RUN on [1→2→3→4]:
  Swap 1,2: 2→1→3→4
  Swap 3,4: 2→1→4→3
  Result: 2→1→4→3→NULL ✅
*/

Node* swapPairs(Node* head) {
    Node dummy(0);
    dummy.next = head;
    Node* prev = &dummy;

    while (prev->next && prev->next->next) {
        Node* first = prev->next;
        Node* second = prev->next->next;

        first->next = second->next;
        second->next = first;
        prev->next = second;

        prev = first;
    }

    return dummy.next;
}

// ═══════════════════════════════════════════════════════════════
// 5. PARTITION LIST — O(n) time, O(1) space (LeetCode 86)
// ═══════════════════════════════════════════════════════════════

Node* partition(Node* head, int x) {
    Node lessHead(0), greaterHead(0);
    Node* less = &lessHead;
    Node* greater = &greaterHead;

    while (head) {
        if (head->data < x) {
            less->next = head;
            less = less->next;
        } else {
            greater->next = head;
            greater = greater->next;
        }
        head = head->next;
    }

    greater->next = nullptr;
    less->next = greaterHead.next;
    return lessHead.next;
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  STRUCTURAL MODIFICATION PATTERNS                      ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Reorder List
    cout << "═══ REORDER LIST ═══\n";
    int a1[] = {1, 2, 3, 4, 5};
    Node* head = buildList(a1, 5);
    cout << "Before: "; printList(head);
    reorderList(head);
    cout << "After:  "; printList(head);
    freeList(head);

    // Rotate List
    cout << "\n═══ ROTATE LIST (K=2) ═══\n";
    head = buildList(a1, 5);
    cout << "Before: "; printList(head);
    head = rotateRight(head, 2);
    cout << "After:  "; printList(head);
    freeList(head);

    // Odd-Even
    cout << "\n═══ ODD-EVEN LINKED LIST ═══\n";
    head = buildList(a1, 5);
    cout << "Before: "; printList(head);
    head = oddEvenList(head);
    cout << "After:  "; printList(head);
    freeList(head);

    // Swap Pairs
    cout << "\n═══ SWAP NODES IN PAIRS ═══\n";
    int a2[] = {1, 2, 3, 4};
    head = buildList(a2, 4);
    cout << "Before: "; printList(head);
    head = swapPairs(head);
    cout << "After:  "; printList(head);
    freeList(head);

    // Partition
    cout << "\n═══ PARTITION LIST (x=3) ═══\n";
    int a3[] = {1, 4, 3, 2, 5, 2};
    head = buildList(a3, 6);
    cout << "Before: "; printList(head);
    head = partition(head, 3);
    cout << "After:  "; printList(head);
    freeList(head);

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE: LeetCode 143, 61, 328, 24, 86\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

