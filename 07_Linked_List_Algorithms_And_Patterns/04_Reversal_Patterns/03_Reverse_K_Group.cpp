/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           03 — REVERSE K-GROUP (LeetCode 25 — Hard)                        ║
║           From Zero to Grandmaster — Core Pattern                          ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Reverse in K-Group (Iterative)
 2. Reverse in K-Group (Recursive)
 3. Reverse Alternate K Nodes

DRY RUN — Reverse K-Group (K=3) on [1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → NULL]:
───────────────────────────────────────────────────────────────────────────────

  Step 1: Count first K=3 nodes → [1, 2, 3] exists → Reverse them
          Before: 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8
          After:  3 → 2 → 1 → 4 → 5 → 6 → 7 → 8
                              ↑
                        1 is now the tail of this group

  Step 2: Count next K=3 nodes → [4, 5, 6] exists → Reverse them
          3 → 2 → 1 → 6 → 5 → 4 → 7 → 8
                              ↑
                        4 is now the tail of this group

  Step 3: Count next K=3 nodes → [7, 8] only 2 < 3 → Keep as is
          3 → 2 → 1 → 6 → 5 → 4 → 7 → 8 → NULL

  Result: 3 → 2 → 1 → 6 → 5 → 4 → 7 → 8 → NULL ✅

  Pointer Management Visualization:
  ┌───┐   ┌───┐   ┌───┐   ┌───┐   ┌───┐   ┌───┐   ┌───┐   ┌───┐
  │ 3 │──▶│ 2 │──▶│ 1 │──▶│ 6 │──▶│ 5 │──▶│ 4 │──▶│ 7 │──▶│ 8 │──▶NULL
  └───┘   └───┘   └───┘   └───┘   └───┘   └───┘   └───┘   └───┘
  \________↑________/      \________↑________/      \______↑_____/
    Reversed Group 1        Reversed Group 2        Kept (< K)

  Time: O(n)   Space: O(1) iterative / O(n/k) recursive
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
// 1. REVERSE K-GROUP (Recursive) — O(n) time, O(n/k) space
// ═══════════════════════════════════════════════════════════════

Node* reverseKGroup(Node* head, int k) {
    // Step 1: Check if k nodes exist
    Node* check = head;
    for (int i = 0; i < k; i++) {
        if (check == nullptr) return head;  // Less than k nodes — don't reverse
        check = check->next;
    }

    // Step 2: Reverse k nodes
    Node* prev = nullptr;
    Node* curr = head;
    Node* next = nullptr;
    for (int i = 0; i < k; i++) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    // Step 3: head is now the TAIL of reversed group
    // Connect it to the result of reversing the rest
    head->next = reverseKGroup(curr, k);

    return prev;  // prev is the new head of reversed group
}

// ═══════════════════════════════════════════════════════════════
// 2. REVERSE K-GROUP (Iterative) — O(n) time, O(1) space
// ═══════════════════════════════════════════════════════════════

Node* reverseKGroupIterative(Node* head, int k) {
    if (!head || k <= 1) return head;

    // Count total nodes
    int count = 0;
    Node* temp = head;
    while (temp) { count++; temp = temp->next; }

    Node dummy(0);
    dummy.next = head;
    Node* prevGroupEnd = &dummy;

    while (count >= k) {
        Node* groupStart = prevGroupEnd->next;
        Node* prev = nullptr;
        Node* curr = groupStart;

        for (int i = 0; i < k; i++) {
            Node* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        prevGroupEnd->next = prev;      // Connect prev group to reversed head
        groupStart->next = curr;         // Connect reversed tail to next group
        prevGroupEnd = groupStart;       // Move to end of reversed group
        count -= k;
    }

    return dummy.next;
}

// ═══════════════════════════════════════════════════════════════
// 3. REVERSE ALTERNATE K NODES — O(n) time, O(n/k) space
// ═══════════════════════════════════════════════════════════════
/*
  DRY RUN — Reverse Alternate K=2 on [1 → 2 → 3 → 4 → 5 → 6 → 7 → 8]:

  Group 1: [1, 2] → REVERSE → [2, 1]
  Group 2: [3, 4] → SKIP (keep order)
  Group 3: [5, 6] → REVERSE → [6, 5]
  Group 4: [7, 8] → SKIP

  Result: 2 → 1 → 3 → 4 → 6 → 5 → 7 → 8 → NULL
*/

Node* reverseAlternateKNodes(Node* head, int k) {
    Node* check = head;
    for (int i = 0; i < k; i++) {
        if (!check) return head;
        check = check->next;
    }

    // Reverse k nodes
    Node* prev = nullptr;
    Node* curr = head;
    for (int i = 0; i < k; i++) {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    // Skip k nodes (don't reverse)
    head->next = curr;
    Node* skipTail = curr;
    for (int i = 1; i < k && skipTail != nullptr; i++) {
        skipTail = skipTail->next;
    }

    // Recurse on the remaining list
    if (skipTail != nullptr) {
        skipTail->next = reverseAlternateKNodes(skipTail->next, k);
    }

    return prev;
}

// ═══════════════════════════════════════════════════════════════
// 4. REVERSE SUBLIST [L, R] (LeetCode 92)
// ═══════════════════════════════════════════════════════════════
/*
  DRY RUN — Reverse between positions 2 and 4 on [1 → 2 → 3 → 4 → 5]:

  Before: 1 → 2 → 3 → 4 → 5 → NULL
              L         R

  Step 1: Navigate to position L-1 (node 1)
  Step 2: Reverse from L to R: [2, 3, 4] → [4, 3, 2]
  Step 3: Connect: 1 → 4 → 3 → 2 → 5

  Result: 1 → 4 → 3 → 2 → 5 → NULL ✅
*/

Node* reverseSublist(Node* head, int left, int right) {
    if (!head || left == right) return head;

    Node dummy(0);
    dummy.next = head;
    Node* pre = &dummy;

    // Move to node before left position
    for (int i = 1; i < left; i++) {
        pre = pre->next;
    }

    Node* curr = pre->next;
    // Reverse (right - left) times
    for (int i = 0; i < right - left; i++) {
        Node* next = curr->next;
        curr->next = next->next;
        next->next = pre->next;
        pre->next = next;
    }

    return dummy.next;
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  REVERSE K-GROUP & SUBLIST PATTERNS                    ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Reverse K-Group (Recursive)
    cout << "═══ REVERSE K-GROUP (Recursive, K=3) ═══\n";
    int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    Node* head = buildList(arr1, 8);
    cout << "Before: "; printList(head);
    head = reverseKGroup(head, 3);
    cout << "After:  "; printList(head);
    freeList(head);

    // Reverse K-Group (Iterative)
    cout << "\n═══ REVERSE K-GROUP (Iterative, K=3) ═══\n";
    head = buildList(arr1, 8);
    cout << "Before: "; printList(head);
    head = reverseKGroupIterative(head, 3);
    cout << "After:  "; printList(head);
    freeList(head);

    // Reverse Alternate K Nodes
    cout << "\n═══ REVERSE ALTERNATE K NODES (K=2) ═══\n";
    head = buildList(arr1, 8);
    cout << "Before: "; printList(head);
    head = reverseAlternateKNodes(head, 2);
    cout << "After:  "; printList(head);
    freeList(head);

    // Reverse Sublist [L, R]
    cout << "\n═══ REVERSE SUBLIST [2, 4] ═══\n";
    int arr2[] = {1, 2, 3, 4, 5};
    head = buildList(arr2, 5);
    cout << "Before: "; printList(head);
    head = reverseSublist(head, 2, 4);
    cout << "After:  "; printList(head);
    freeList(head);

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE: LeetCode 25, 92, 24\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

