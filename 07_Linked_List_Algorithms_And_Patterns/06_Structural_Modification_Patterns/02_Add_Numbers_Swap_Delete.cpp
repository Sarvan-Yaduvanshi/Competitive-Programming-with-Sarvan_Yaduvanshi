/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — ADD TWO NUMBERS & FLATTEN MULTILEVEL LIST                   ║
║           (LeetCode 2, 445, 430) — Structural Modifications               ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Add Two Numbers (Reverse Order — LeetCode 2)
 2. Add Two Numbers II (Forward Order — LeetCode 445)
 3. Subtract Two Numbers (Linked List)
 4. Swap Kth from Start and End
 5. Delete Nodes with Greater Value on Right

DRY RUN — Add Two Numbers [2→4→3] + [5→6→4]:
─────────────────────────────────────────────
  Numbers: 342 + 465 = 807

  Step 1: 2 + 5 = 7, carry = 0    → [7]
  Step 2: 4 + 6 = 10, carry = 1   → [7 → 0]
  Step 3: 3 + 4 + 1(carry) = 8    → [7 → 0 → 8]

  Result: 7 → 0 → 8 → NULL (represents 807) ✅

DRY RUN — Delete Greater on Right [12→15→10→11→5→6→2→3]:
────────────────────────────────────────────────────────
  Traverse right to left (reverse first):
  3→2→6→5→11→10→15→12

  Keep max from right:
  3 (max=3), 2<3 skip, 6>3 keep (max=6), 5<6 skip,
  11>6 keep (max=11), 10<11 skip, 15>11 keep (max=15), 12<15 skip

  Result: 15 → 11 → 6 → 3 → NULL ✅
*/

#include <iostream>
#include <stack>
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
// 1. ADD TWO NUMBERS (Reverse Order) — O(max(n,m)) time
// ═══════════════════════════════════════════════════════════════

Node* addTwoNumbers(Node* l1, Node* l2) {
    Node dummy(0);
    Node* curr = &dummy;
    int carry = 0;

    while (l1 || l2 || carry) {
        int sum = carry;
        if (l1) { sum += l1->data; l1 = l1->next; }
        if (l2) { sum += l2->data; l2 = l2->next; }

        carry = sum / 10;
        curr->next = new Node(sum % 10);
        curr = curr->next;
    }

    return dummy.next;
}

// ═══════════════════════════════════════════════════════════════
// 2. ADD TWO NUMBERS II (Forward Order using Stack)
// ═══════════════════════════════════════════════════════════════

Node* addTwoNumbersII(Node* l1, Node* l2) {
    stack<int> s1, s2;
    while (l1) { s1.push(l1->data); l1 = l1->next; }
    while (l2) { s2.push(l2->data); l2 = l2->next; }

    int carry = 0;
    Node* head = nullptr;

    while (!s1.empty() || !s2.empty() || carry) {
        int sum = carry;
        if (!s1.empty()) { sum += s1.top(); s1.pop(); }
        if (!s2.empty()) { sum += s2.top(); s2.pop(); }

        carry = sum / 10;
        Node* newNode = new Node(sum % 10);
        newNode->next = head;
        head = newNode;
    }

    return head;
}

// ═══════════════════════════════════════════════════════════════
// 3. SWAP KTH FROM START AND END — O(n) time, O(1) space
// ═══════════════════════════════════════════════════════════════

Node* swapKthNodes(Node* head, int k) {
    int length = 0;
    Node* temp = head;
    while (temp) { length++; temp = temp->next; }

    if (k > length) return head;

    // Find kth from start
    Node* first = head;
    for (int i = 1; i < k; i++) first = first->next;

    // Find kth from end (= (length - k + 1)th from start)
    Node* second = head;
    for (int i = 1; i < length - k + 1; i++) second = second->next;

    // Swap data
    swap(first->data, second->data);
    return head;
}

// ═══════════════════════════════════════════════════════════════
// 4. DELETE NODES WITH GREATER VALUE ON RIGHT — O(n) time
// ═══════════════════════════════════════════════════════════════

Node* reverseLL(Node* head) {
    Node* prev = nullptr;
    while (head) { Node* n = head->next; head->next = prev; prev = head; head = n; }
    return prev;
}

Node* deleteGreaterOnRight(Node* head) {
    // Reverse → track max → reverse back
    head = reverseLL(head);

    Node* curr = head;
    int maxVal = curr->data;

    while (curr->next) {
        if (curr->next->data < maxVal) {
            Node* temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
        } else {
            maxVal = curr->next->data;
            curr = curr->next;
        }
    }

    return reverseLL(head);
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  ADD NUMBERS, SWAP, DELETE GREATER ON RIGHT            ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Add Two Numbers (reverse order)
    cout << "═══ ADD TWO NUMBERS (Reverse) ═══\n";
    int a1[] = {2, 4, 3};  // 342
    int a2[] = {5, 6, 4};  // 465
    Node* l1 = buildList(a1, 3);
    Node* l2 = buildList(a2, 3);
    cout << "Num1 (342): "; printList(l1);
    cout << "Num2 (465): "; printList(l2);
    Node* sum1 = addTwoNumbers(l1, l2);
    cout << "Sum  (807): "; printList(sum1);
    freeList(l1); freeList(l2); freeList(sum1);

    // Add Two Numbers II (forward order)
    cout << "\n═══ ADD TWO NUMBERS II (Forward) ═══\n";
    int b1[] = {7, 2, 4, 3};  // 7243
    int b2[] = {5, 6, 4};     // 564
    l1 = buildList(b1, 4);
    l2 = buildList(b2, 3);
    cout << "Num1 (7243): "; printList(l1);
    cout << "Num2 (564):  "; printList(l2);
    Node* sum2 = addTwoNumbersII(l1, l2);
    cout << "Sum  (7807): "; printList(sum2);
    freeList(l1); freeList(l2); freeList(sum2);

    // Swap Kth nodes
    cout << "\n═══ SWAP KTH FROM START AND END (K=2) ═══\n";
    int c[] = {1, 2, 3, 4, 5};
    Node* head = buildList(c, 5);
    cout << "Before: "; printList(head);
    head = swapKthNodes(head, 2);
    cout << "After:  "; printList(head);
    freeList(head);

    // Delete greater on right
    cout << "\n═══ DELETE NODES WITH GREATER VALUE ON RIGHT ═══\n";
    int d[] = {12, 15, 10, 11, 5, 6, 2, 3};
    head = buildList(d, 8);
    cout << "Before: "; printList(head);
    head = deleteGreaterOnRight(head);
    cout << "After:  "; printList(head);
    freeList(head);

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE: LeetCode 2, 445, 430\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

