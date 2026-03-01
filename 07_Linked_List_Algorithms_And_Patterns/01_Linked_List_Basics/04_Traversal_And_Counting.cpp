/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           04 — LINKED LIST TRAVERSAL & COUNTING                            ║
║           From Zero to Grandmaster — Complete Foundation                    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Iterative Traversal
 2. Recursive Traversal
 3. Length (Iterative & Recursive)
 4. Count Occurrences
 5. Sum of Elements
 6. Search Element
 7. Find Nth Node
 8. Reverse Print (Recursive)

DRY RUN — Iterative Traversal on [10, 20, 30, 40]:

  head ──▶ [10] ──▶ [20] ──▶ [30] ──▶ [40] ──▶ NULL

  Step 1: curr = head = [10]     → Print 10
  Step 2: curr = curr->next = [20] → Print 20
  Step 3: curr = curr->next = [30] → Print 30
  Step 4: curr = curr->next = [40] → Print 40
  Step 5: curr = curr->next = NULL → STOP

DRY RUN — Recursive Traversal on [10, 20, 30]:

  printRecursive(10)
    → print 10, call printRecursive(20)
      → print 20, call printRecursive(30)
        → print 30, call printRecursive(NULL)
          → BASE CASE: return
        ← return
      ← return
    ← return

  Output: 10 20 30

DRY RUN — Reverse Print (Recursive) on [10, 20, 30]:

  reversePrint(10)
    → call reversePrint(20)
      → call reversePrint(30)
        → call reversePrint(NULL)
          → BASE CASE: return
        → print 30  ← AFTER recursive call!
      → print 20
    → print 10

  Output: 30 20 10
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
    for (int i = 1; i < n; i++) {
        tail->next = new Node(arr[i]);
        tail = tail->next;
    }
    return head;
}

void deleteList(Node* head) {
    while (head) { Node* t = head; head = head->next; delete t; }
}

// ═══════════════════════════════════════════════════════════════
// 1. ITERATIVE TRAVERSAL — O(n) time, O(1) space
// ═══════════════════════════════════════════════════════════════

void printIterative(Node* head) {
    Node* curr = head;
    while (curr != nullptr) {
        cout << curr->data;
        if (curr->next) cout << " -> ";
        curr = curr->next;
    }
    cout << " -> NULL\n";
}

// ═══════════════════════════════════════════════════════════════
// 2. RECURSIVE TRAVERSAL — O(n) time, O(n) stack space
// ═══════════════════════════════════════════════════════════════

void printRecursive(Node* head) {
    if (head == nullptr) {
        cout << "NULL\n";
        return;
    }
    cout << head->data << " -> ";
    printRecursive(head->next);
}

// ═══════════════════════════════════════════════════════════════
// 3. REVERSE PRINT (Recursive) — O(n) time, O(n) stack space
// ═══════════════════════════════════════════════════════════════

void reversePrint(Node* head) {
    if (head == nullptr) return;
    reversePrint(head->next);      // Go to end first
    cout << head->data << " ";     // Print on backtrack
}

// ═══════════════════════════════════════════════════════════════
// 4. LENGTH — Iterative & Recursive
// ═══════════════════════════════════════════════════════════════

int lengthIterative(Node* head) {
    int count = 0;
    Node* curr = head;
    while (curr != nullptr) {
        count++;
        curr = curr->next;
    }
    return count;
}

int lengthRecursive(Node* head) {
    if (head == nullptr) return 0;
    return 1 + lengthRecursive(head->next);
}

// ═══════════════════════════════════════════════════════════════
// 5. COUNT OCCURRENCES
// ═══════════════════════════════════════════════════════════════

int countOccurrences(Node* head, int target) {
    int count = 0;
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->data == target) count++;
        curr = curr->next;
    }
    return count;
}

// ═══════════════════════════════════════════════════════════════
// 6. SUM OF ALL ELEMENTS
// ═══════════════════════════════════════════════════════════════

int sumOfList(Node* head) {
    int sum = 0;
    Node* curr = head;
    while (curr != nullptr) {
        sum += curr->data;
        curr = curr->next;
    }
    return sum;
}

// ═══════════════════════════════════════════════════════════════
// 7. SEARCH ELEMENT
// ═══════════════════════════════════════════════════════════════

bool searchIterative(Node* head, int target) {
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->data == target) return true;
        curr = curr->next;
    }
    return false;
}

bool searchRecursive(Node* head, int target) {
    if (head == nullptr) return false;
    if (head->data == target) return true;
    return searchRecursive(head->next, target);
}

// ═══════════════════════════════════════════════════════════════
// 8. FIND NTH NODE (0-indexed and 1-indexed)
// ═══════════════════════════════════════════════════════════════

int getNth(Node* head, int index) {  // 0-indexed
    Node* curr = head;
    int count = 0;
    while (curr != nullptr) {
        if (count == index) return curr->data;
        count++;
        curr = curr->next;
    }
    return -1;  // Index out of range
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  LINKED LIST TRAVERSAL & COUNTING                      ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    int arr[] = {10, 20, 30, 20, 40, 20, 50};
    Node* head = buildList(arr, 7);

    cout << "═══ ITERATIVE TRAVERSAL ═══\n";
    cout << "List: "; printIterative(head);

    cout << "\n═══ RECURSIVE TRAVERSAL ═══\n";
    cout << "List: "; printRecursive(head);

    cout << "\n═══ REVERSE PRINT ═══\n";
    cout << "Reverse: "; reversePrint(head); cout << "\n";

    cout << "\n═══ LENGTH ═══\n";
    cout << "Length (iterative): " << lengthIterative(head) << "\n";
    cout << "Length (recursive): " << lengthRecursive(head) << "\n";

    cout << "\n═══ COUNT OCCURRENCES ═══\n";
    cout << "Count of 20: " << countOccurrences(head, 20) << "\n";
    cout << "Count of 99: " << countOccurrences(head, 99) << "\n";

    cout << "\n═══ SUM ═══\n";
    cout << "Sum: " << sumOfList(head) << "\n";

    cout << "\n═══ SEARCH ═══\n";
    cout << "Search 30 (iterative): " << (searchIterative(head, 30) ? "FOUND" : "NOT FOUND") << "\n";
    cout << "Search 99 (recursive): " << (searchRecursive(head, 99) ? "FOUND" : "NOT FOUND") << "\n";

    cout << "\n═══ GET NTH NODE ═══\n";
    for (int i = 0; i < 7; i++) {
        cout << "Index " << i << ": " << getNth(head, i) << "\n";
    }

    deleteList(head);

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "COMPLEXITY SUMMARY:\n";
    cout << "───────────────────\n";
    cout << "Traversal (iter):   O(n) time, O(1) space\n";
    cout << "Traversal (recur):  O(n) time, O(n) space (call stack)\n";
    cout << "Reverse Print:      O(n) time, O(n) space\n";
    cout << "Length:             O(n) time\n";
    cout << "Search:             O(n) time\n";
    cout << "Get Nth:            O(n) time\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

