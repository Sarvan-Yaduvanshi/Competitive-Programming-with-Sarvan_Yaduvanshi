/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           03 — MERGE SORT & INSERTION SORT ON LINKED LIST                  ║
║           (LeetCode 148, 147) — Sort Patterns                             ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Merge Sort on Linked List (LeetCode 148) — O(n log n)
 2. Insertion Sort on Linked List (LeetCode 147) — O(n²)
 3. Partition List (Dutch National Flag on LL)
 4. Remove Duplicates (Sorted & Unsorted)

DRY RUN — Merge Sort on [4 → 2 → 1 → 3]:
─────────────────────────────────────────
  Split: [4 → 2] and [1 → 3]

  Left:  Split [4 → 2] into [4] and [2]
         Merge [4] and [2] → [2 → 4]

  Right: Split [1 → 3] into [1] and [3]
         Merge [1] and [3] → [1 → 3]

  Merge [2 → 4] and [1 → 3]:
    Compare 2 vs 1 → pick 1
    Compare 2 vs 3 → pick 2
    Compare 4 vs 3 → pick 3
    Append 4

  Result: 1 → 2 → 3 → 4 → NULL ✅

  WHY MERGE SORT FOR LINKED LIST?
  ─────────────────────────────────
  • No random access needed (unlike quicksort)
  • Finding middle: O(n) with fast/slow pointer
  • Merge: O(n) with O(1) space (re-link nodes)
  • Total: O(n log n) time, O(log n) space (recursion stack)
*/

#include <iostream>
#include <unordered_set>
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
// 1. MERGE SORT ON LINKED LIST — O(n log n) time, O(log n) space
// ═══════════════════════════════════════════════════════════════

Node* mergeTwoLists(Node* l1, Node* l2) {
    Node dummy(0);
    Node* tail = &dummy;
    while (l1 && l2) {
        if (l1->data <= l2->data) { tail->next = l1; l1 = l1->next; }
        else { tail->next = l2; l2 = l2->next; }
        tail = tail->next;
    }
    tail->next = l1 ? l1 : l2;
    return dummy.next;
}

Node* getMiddle(Node* head) {
    Node* slow = head;
    Node* fast = head->next;  // Important: use head->next for even split
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

Node* mergeSort(Node* head) {
    // Base case
    if (!head || !head->next) return head;

    // Split into two halves
    Node* mid = getMiddle(head);
    Node* rightHalf = mid->next;
    mid->next = nullptr;

    // Recursively sort both halves
    Node* left = mergeSort(head);
    Node* right = mergeSort(rightHalf);

    // Merge sorted halves
    return mergeTwoLists(left, right);
}

// ═══════════════════════════════════════════════════════════════
// 2. INSERTION SORT ON LINKED LIST — O(n²) time, O(1) space
// ═══════════════════════════════════════════════════════════════
/*
  DRY RUN on [4 → 2 → 1 → 3]:

  sorted: (empty), curr = 4
  Insert 4: sorted = [4]

  curr = 2: 2 < 4 → insert before 4
  sorted = [2 → 4]

  curr = 1: 1 < 2 → insert at head
  sorted = [1 → 2 → 4]

  curr = 3: 3 > 2, 3 < 4 → insert between 2 and 4
  sorted = [1 → 2 → 3 → 4] ✅
*/

Node* insertionSort(Node* head) {
    Node dummy(0);  // Sorted list starts empty
    Node* curr = head;

    while (curr) {
        Node* next = curr->next;

        // Find insertion point in sorted list
        Node* prev = &dummy;
        while (prev->next && prev->next->data < curr->data) {
            prev = prev->next;
        }

        // Insert curr after prev
        curr->next = prev->next;
        prev->next = curr;

        curr = next;
    }

    return dummy.next;
}

// ═══════════════════════════════════════════════════════════════
// 3. SORT LIST 0-1-2 (Dutch National Flag) — O(n) time
// ═══════════════════════════════════════════════════════════════

Node* sortList012(Node* head) {
    Node zero(0), one(0), two(0);
    Node* z = &zero, *o = &one, *t = &two;

    Node* curr = head;
    while (curr) {
        if (curr->data == 0) { z->next = curr; z = z->next; }
        else if (curr->data == 1) { o->next = curr; o = o->next; }
        else { t->next = curr; t = t->next; }
        curr = curr->next;
    }

    // Connect: zeros → ones → twos
    z->next = one.next ? one.next : two.next;
    o->next = two.next;
    t->next = nullptr;

    return zero.next;
}

// ═══════════════════════════════════════════════════════════════
// 4. REMOVE DUPLICATES (Sorted List) — O(n) time, O(1) space
// ═══════════════════════════════════════════════════════════════

Node* removeDupsSorted(Node* head) {
    Node* curr = head;
    while (curr && curr->next) {
        if (curr->data == curr->next->data) {
            Node* temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
        } else {
            curr = curr->next;
        }
    }
    return head;
}

// ═══════════════════════════════════════════════════════════════
// 5. REMOVE DUPLICATES (Unsorted List) — O(n) time, O(n) space
// ═══════════════════════════════════════════════════════════════

Node* removeDupsUnsorted(Node* head) {
    unordered_set<int> seen;
    Node dummy(0);
    dummy.next = head;
    Node* prev = &dummy;
    Node* curr = head;

    while (curr) {
        if (seen.count(curr->data)) {
            prev->next = curr->next;
            delete curr;
            curr = prev->next;
        } else {
            seen.insert(curr->data);
            prev = curr;
            curr = curr->next;
        }
    }
    return dummy.next;
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  MERGE SORT, INSERTION SORT & REMOVE DUPLICATES        ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Merge Sort
    cout << "═══ MERGE SORT ═══\n";
    int arr1[] = {4, 2, 1, 3, 5};
    Node* head = buildList(arr1, 5);
    cout << "Before: "; printList(head);
    head = mergeSort(head);
    cout << "After:  "; printList(head);
    freeList(head);

    // Insertion Sort
    cout << "\n═══ INSERTION SORT ═══\n";
    int arr2[] = {4, 2, 1, 3};
    head = buildList(arr2, 4);
    cout << "Before: "; printList(head);
    head = insertionSort(head);
    cout << "After:  "; printList(head);
    freeList(head);

    // Sort 0-1-2
    cout << "\n═══ SORT 0-1-2 ═══\n";
    int arr3[] = {1, 2, 0, 1, 2, 0, 1, 0};
    head = buildList(arr3, 8);
    cout << "Before: "; printList(head);
    head = sortList012(head);
    cout << "After:  "; printList(head);
    freeList(head);

    // Remove duplicates (sorted)
    cout << "\n═══ REMOVE DUPLICATES (SORTED) ═══\n";
    int arr4[] = {1, 1, 2, 3, 3, 3, 4, 5, 5};
    head = buildList(arr4, 9);
    cout << "Before: "; printList(head);
    head = removeDupsSorted(head);
    cout << "After:  "; printList(head);
    freeList(head);

    // Remove duplicates (unsorted)
    cout << "\n═══ REMOVE DUPLICATES (UNSORTED) ═══\n";
    int arr5[] = {3, 1, 2, 3, 4, 1, 5, 2};
    head = buildList(arr5, 8);
    cout << "Before: "; printList(head);
    head = removeDupsUnsorted(head);
    cout << "After:  "; printList(head);
    freeList(head);

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE: LeetCode 148, 147, 83, 82\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

