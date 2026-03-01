/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — DELETION OPERATIONS IN LINKED LIST                          ║
║           From Zero to Grandmaster — Complete Foundation                    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Delete Head
 2. Delete Tail
 3. Delete by Value
 4. Delete by Position
 5. Delete Entire List

DRY RUN — Delete Head:
──────────────────────
  Before:  head ──▶ [10] ──▶ [20] ──▶ [30] ──▶ NULL

  Step 1: temp = head   →  temp points to [10]
  Step 2: head = head->next  →  head now points to [20]
  Step 3: delete temp   →  free [10]

  After:   head ──▶ [20] ──▶ [30] ──▶ NULL  ✅
  Time: O(1)

DRY RUN — Delete Tail:
──────────────────────
  Before:  head ──▶ [10] ──▶ [20] ──▶ [30] ──▶ NULL

  Step 1: Traverse to second-to-last (curr = [20])
          curr ──▶ [20]  →  curr->next = [30]
  Step 2: delete curr->next  →  free [30]
  Step 3: curr->next = NULL

  After:   head ──▶ [10] ──▶ [20] ──▶ NULL  ✅
  Time: O(n)

DRY RUN — Delete by Value (delete 20):
──────────────────────────────────────
  Before:  head ──▶ [10] ──▶ [20] ──▶ [30] ──▶ NULL

  Step 1: prev = NULL, curr = head = [10]
          10 ≠ 20 → move forward
  Step 2: prev = [10], curr = [20]
          20 == 20 → FOUND!
  Step 3: prev->next = curr->next  →  [10]──▶[30]
  Step 4: delete curr  →  free [20]

  After:   head ──▶ [10] ──▶ [30] ──▶ NULL  ✅
  Time: O(n)
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

void printList(Node* head) {
    Node* curr = head;
    while (curr) {
        cout << curr->data;
        if (curr->next) cout << " -> ";
        curr = curr->next;
    }
    cout << " -> NULL\n";
}

void deleteList(Node* head) {
    while (head) { Node* t = head; head = head->next; delete t; }
}

// ═══════════════════════════════════════════════════════════════
// 1. DELETE HEAD — O(1) time, O(1) space
// ═══════════════════════════════════════════════════════════════

Node* deleteHead(Node* head) {
    if (head == nullptr) return nullptr;

    Node* temp = head;
    head = head->next;
    delete temp;
    return head;
}

// ═══════════════════════════════════════════════════════════════
// 2. DELETE TAIL — O(n) time, O(1) space
// ═══════════════════════════════════════════════════════════════

Node* deleteTail(Node* head) {
    if (head == nullptr) return nullptr;
    if (head->next == nullptr) {  // Single node
        delete head;
        return nullptr;
    }

    Node* curr = head;
    while (curr->next->next != nullptr) {
        curr = curr->next;
    }
    delete curr->next;
    curr->next = nullptr;
    return head;
}

// ═══════════════════════════════════════════════════════════════
// 3. DELETE BY VALUE — O(n) time, O(1) space
// ═══════════════════════════════════════════════════════════════

Node* deleteByValue(Node* head, int val) {
    if (head == nullptr) return nullptr;

    // If head is the target
    if (head->data == val) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return head;
    }

    Node* curr = head;
    while (curr->next != nullptr && curr->next->data != val) {
        curr = curr->next;
    }

    if (curr->next != nullptr) {
        Node* temp = curr->next;
        curr->next = curr->next->next;
        delete temp;
    } else {
        cout << "Value " << val << " not found!\n";
    }
    return head;
}

// ═══════════════════════════════════════════════════════════════
// 4. DELETE BY POSITION — O(n) time, O(1) space
// ═══════════════════════════════════════════════════════════════

Node* deleteByPosition(Node* head, int pos) {
    if (head == nullptr) return nullptr;

    if (pos == 0) return deleteHead(head);

    Node* curr = head;
    for (int i = 0; i < pos - 1 && curr->next != nullptr; i++) {
        curr = curr->next;
    }

    if (curr->next == nullptr) {
        cout << "Position " << pos << " out of range!\n";
        return head;
    }

    Node* temp = curr->next;
    curr->next = curr->next->next;
    delete temp;
    return head;
}

// ═══════════════════════════════════════════════════════════════
// 5. DELETE ALL OCCURRENCES — O(n) time, O(1) space
// ═══════════════════════════════════════════════════════════════
/*
  DRY RUN — Delete all 20s from [20, 10, 20, 30, 20]:

  Step 1: head->data == 20 → delete head, head = [10]
  Step 2: curr = [10], curr->next = [20] → delete, link [10]→[30]
  Step 3: curr = [30], curr->next = [20] → delete, link [30]→NULL

  Result: [10] ──▶ [30] ──▶ NULL
*/

Node* deleteAllOccurrences(Node* head, int val) {
    // Handle leading nodes with target value
    while (head != nullptr && head->data == val) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    if (head == nullptr) return nullptr;

    Node* curr = head;
    while (curr->next != nullptr) {
        if (curr->next->data == val) {
            Node* temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
        } else {
            curr = curr->next;
        }
    }
    return head;
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  DELETION OPERATIONS IN LINKED LIST                    ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Delete Head
    cout << "═══ DELETE HEAD ═══\n";
    int arr1[] = {10, 20, 30, 40, 50};
    Node* head = buildList(arr1, 5);
    cout << "Before: "; printList(head);
    head = deleteHead(head);
    cout << "After:  "; printList(head);
    deleteList(head);

    // Delete Tail
    cout << "\n═══ DELETE TAIL ═══\n";
    head = buildList(arr1, 5);
    cout << "Before: "; printList(head);
    head = deleteTail(head);
    cout << "After:  "; printList(head);
    deleteList(head);

    // Delete by Value
    cout << "\n═══ DELETE BY VALUE ═══\n";
    head = buildList(arr1, 5);
    cout << "Before: "; printList(head);
    head = deleteByValue(head, 30);
    cout << "Delete 30: "; printList(head);
    head = deleteByValue(head, 10);
    cout << "Delete 10: "; printList(head);
    deleteList(head);

    // Delete by Position
    cout << "\n═══ DELETE BY POSITION ═══\n";
    head = buildList(arr1, 5);
    cout << "Before: "; printList(head);
    head = deleteByPosition(head, 2);
    cout << "Delete pos 2: "; printList(head);
    head = deleteByPosition(head, 0);
    cout << "Delete pos 0: "; printList(head);
    deleteList(head);

    // Delete all occurrences
    cout << "\n═══ DELETE ALL OCCURRENCES ═══\n";
    int arr2[] = {20, 10, 20, 30, 20, 40, 20};
    head = buildList(arr2, 7);
    cout << "Before:      "; printList(head);
    head = deleteAllOccurrences(head, 20);
    cout << "Delete all 20s: "; printList(head);
    deleteList(head);

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "COMPLEXITY SUMMARY:\n";
    cout << "───────────────────\n";
    cout << "Delete Head:            O(1)\n";
    cout << "Delete Tail:            O(n)\n";
    cout << "Delete by Value:        O(n)\n";
    cout << "Delete by Position:     O(n)\n";
    cout << "Delete All Occurrences: O(n)\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

