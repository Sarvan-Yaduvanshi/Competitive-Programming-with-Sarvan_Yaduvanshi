/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           03 — SEARCH, LENGTH, PRINT & REVERSE PRINT                       ║
║           From Zero to Grandmaster — Complete Foundation                    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Search Element (Iterative & Recursive)
 2. Length of Linked List (Iterative & Recursive)
 3. Print List (Forward)
 4. Reverse Print (Using Recursion)
 5. Print with Index
 6. Find Middle Element
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

void freeList(Node* head) {
    while (head) { Node* t = head; head = head->next; delete t; }
}

// ═══════════════════════════════════════════════════════════════
// 1. SEARCH — Iterative O(n), Recursive O(n)
// ═══════════════════════════════════════════════════════════════

int searchIterative(Node* head, int target) {
    int index = 0;
    Node* curr = head;
    while (curr) {
        if (curr->data == target) return index;
        curr = curr->next;
        index++;
    }
    return -1;
}

bool searchRecursive(Node* head, int target) {
    if (!head) return false;
    if (head->data == target) return true;
    return searchRecursive(head->next, target);
}

// ═══════════════════════════════════════════════════════════════
// 2. LENGTH — Iterative O(n), Recursive O(n)
// ═══════════════════════════════════════════════════════════════

int lengthIterative(Node* head) {
    int count = 0;
    while (head) { count++; head = head->next; }
    return count;
}

int lengthRecursive(Node* head) {
    if (!head) return 0;
    return 1 + lengthRecursive(head->next);
}

// ═══════════════════════════════════════════════════════════════
// 3. PRINT LIST — Various formats
// ═══════════════════════════════════════════════════════════════

void printList(Node* head) {
    while (head) {
        cout << head->data;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << " -> NULL\n";
}

void printWithIndex(Node* head) {
    int i = 0;
    while (head) {
        cout << "[" << i << "]=" << head->data << " ";
        head = head->next;
        i++;
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// 4. REVERSE PRINT (Recursion) — O(n) time, O(n) stack
// ═══════════════════════════════════════════════════════════════
/*
  DRY RUN — Reverse print [1, 2, 3]:

  reversePrint(1):
    → reversePrint(2):
      → reversePrint(3):
        → reversePrint(NULL): return
        print 3
      print 2
    print 1

  Output: 3 2 1
*/

void reversePrint(Node* head) {
    if (!head) return;
    reversePrint(head->next);
    cout << head->data << " ";
}

// ═══════════════════════════════════════════════════════════════
// 5. FIND MIDDLE ELEMENT (Two techniques)
// ═══════════════════════════════════════════════════════════════

int findMiddle(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow ? slow->data : -1;
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  SEARCH, LENGTH, PRINT & REVERSE PRINT                 ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    int arr[] = {10, 20, 30, 40, 50};
    Node* head = buildList(arr, 5);

    cout << "═══ PRINT ═══\n";
    cout << "Forward:    "; printList(head);
    cout << "With Index: "; printWithIndex(head);
    cout << "Reverse:    "; reversePrint(head); cout << "\n";

    cout << "\n═══ LENGTH ═══\n";
    cout << "Length (iter): " << lengthIterative(head) << "\n";
    cout << "Length (recur): " << lengthRecursive(head) << "\n";

    cout << "\n═══ SEARCH ═══\n";
    cout << "Search 30 (iter): index = " << searchIterative(head, 30) << "\n";
    cout << "Search 99 (iter): index = " << searchIterative(head, 99) << "\n";
    cout << "Search 50 (recur): " << (searchRecursive(head, 50) ? "FOUND" : "NOT FOUND") << "\n";

    cout << "\n═══ MIDDLE ELEMENT ═══\n";
    cout << "Middle: " << findMiddle(head) << "\n";

    freeList(head);

    // Edge cases
    cout << "\n═══ EDGE CASES ═══\n";
    Node* empty = nullptr;
    cout << "Empty list length: " << lengthIterative(empty) << "\n";
    cout << "Search in empty: " << searchIterative(empty, 1) << "\n";

    Node* single = new Node(42);
    cout << "Single node middle: " << findMiddle(single) << "\n";
    delete single;

    return 0;
}

