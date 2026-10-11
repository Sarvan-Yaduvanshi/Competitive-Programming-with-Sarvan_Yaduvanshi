/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — PALINDROME, NTH FROM END, INTERSECTION, HAPPY NUMBER        ║
║           From Zero to Grandmaster — Fast/Slow Pointer Applications        ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Remove Nth from End (LeetCode 19)
 2. Palindrome Linked List (LeetCode 234)
 3. Intersection of Two Lists (LeetCode 160)
 4. Happy Number (LeetCode 202)

DRY RUN — Remove Nth from End (N=2) on [1→2→3→4→5]:
────────────────────────────────────────────────────
  Two pointers with gap of N:

  Step 1: Move fast N=2 steps ahead
          slow=1, fast=3        (gap = 2)
          1 → 2 → 3 → 4 → 5 → NULL
          ↑       ↑
         slow    fast

  Step 2: Move both until fast reaches end
          slow=2, fast=4
          slow=3, fast=5
          slow=3, fast=NULL → STOP (fast->next == NULL, one step earlier)

  Actually, move until fast->next == NULL:
          slow at node BEFORE the target → slow=3
  Step 3: slow->next = slow->next->next  →  3→5, delete 4

  Result: 1 → 2 → 3 → 5 → NULL ✅

DRY RUN — Palindrome Check on [1→2→2→1]:
────────────────────────────────────────
  Step 1: Find middle using slow/fast → middle at second 2
  Step 2: Reverse second half: 1→2  and  1→2
  Step 3: Compare: 1==1 ✅, 2==2 ✅ → PALINDROME!

DRY RUN — Intersection on:
  A: 1 → 2 ─┐
             └──▶ 8 → 4 → 5 → NULL
  B: 3 ─────┘

  lenA = 5, lenB = 3, diff = 2
  Advance A by 2: ptrA = 8
  Now move both: ptrA=8, ptrB=8 → MEET! Intersection at 8 ✅
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
// 1. REMOVE NTH FROM END — O(n) time, O(1) space
// ═══════════════════════════════════════════════════════════════

Node* removeNthFromEnd(Node* head, int n) {
    Node dummy(0);
    dummy.next = head;
    Node* fast = &dummy;
    Node* slow = &dummy;

    // Move fast N+1 steps ahead
    for (int i = 0; i <= n; i++) {
        fast = fast->next;
    }

    // Move both until fast reaches NULL
    while (fast != nullptr) {
        slow = slow->next;
        fast = fast->next;
    }

    // slow->next is the node to remove
    Node* toDelete = slow->next;
    slow->next = slow->next->next;
    delete toDelete;

    return dummy.next;
}

// ═══════════════════════════════════════════════════════════════
// 2. PALINDROME CHECK — O(n) time, O(1) space
// ═══════════════════════════════════════════════════════════════

Node* reverseList(Node* head) {
    Node* prev = nullptr;
    while (head) {
        Node* next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

bool isPalindrome(Node* head) {
    if (!head || !head->next) return true;

    // Find middle
    Node* slow = head;
    Node* fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Reverse second half
    Node* secondHalf = reverseList(slow->next);
    slow->next = nullptr;

    // Compare
    Node* p1 = head;
    Node* p2 = secondHalf;
    bool result = true;
    while (p1 && p2) {
        if (p1->data != p2->data) {
            result = false;
            break;
        }
        p1 = p1->next;
        p2 = p2->next;
    }

    // Restore list (optional but good practice)
    slow->next = reverseList(secondHalf);

    return result;
}

// ═══════════════════════════════════════════════════════════════
// 3. INTERSECTION OF TWO LISTS — O(n+m) time, O(1) space
// ═══════════════════════════════════════════════════════════════

Node* getIntersection(Node* headA, Node* headB) {
    if (!headA || !headB) return nullptr;

    Node* ptrA = headA;
    Node* ptrB = headB;

    // When one pointer reaches end, redirect to other list's head
    // They will meet at intersection or both become NULL
    while (ptrA != ptrB) {
        ptrA = (ptrA == nullptr) ? headB : ptrA->next;
        ptrB = (ptrB == nullptr) ? headA : ptrB->next;
    }

    return ptrA;  // Intersection node or NULL
}

// ═══════════════════════════════════════════════════════════════
// 4. HAPPY NUMBER — O(log n) time, O(1) space
// ═══════════════════════════════════════════════════════════════
/*
  A number is happy if repeatedly summing squares of digits leads to 1.
  Uses Floyd's cycle detection on the number sequence!

  DRY RUN — Is 19 happy?
  19 → 1² + 9² = 82
  82 → 8² + 2² = 68
  68 → 6² + 8² = 100
  100 → 1² + 0² + 0² = 1  → HAPPY! ✅

  DRY RUN — Is 2 happy?
  2 → 4 → 16 → 37 → 58 → 89 → 145 → 42 → 20 → 4 → CYCLE! NOT HAPPY ❌
*/

int sumOfSquares(int n) {
    int sum = 0;
    while (n > 0) {
        int digit = n % 10;
        sum += digit * digit;
        n /= 10;
    }
    return sum;
}

bool isHappy(int n) {
    int slow = n;
    int fast = n;

    do {
        slow = sumOfSquares(slow);
        fast = sumOfSquares(sumOfSquares(fast));
    } while (slow != fast);

    return slow == 1;
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  FAST/SLOW POINTER APPLICATIONS                        ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Remove Nth from End
    cout << "═══ REMOVE NTH FROM END ═══\n";
    int arr1[] = {1, 2, 3, 4, 5};
    Node* head = buildList(arr1, 5);
    cout << "Before (remove 2nd from end): "; printList(head);
    head = removeNthFromEnd(head, 2);
    cout << "After:  "; printList(head);
    freeList(head);

    // Palindrome Check
    cout << "\n═══ PALINDROME CHECK ═══\n";
    int p1[] = {1, 2, 3, 2, 1};
    head = buildList(p1, 5);
    cout << "List: "; printList(head);
    cout << "Palindrome? " << (isPalindrome(head) ? "YES" : "NO") << "\n";
    freeList(head);

    int p2[] = {1, 2, 3, 4, 5};
    head = buildList(p2, 5);
    cout << "List: "; printList(head);
    cout << "Palindrome? " << (isPalindrome(head) ? "YES" : "NO") << "\n";
    freeList(head);

    // Intersection
    cout << "\n═══ INTERSECTION OF TWO LISTS ═══\n";
    Node* common = new Node(8);
    common->next = new Node(4);
    common->next->next = new Node(5);

    Node* headA = new Node(1);
    headA->next = new Node(2);
    headA->next->next = common;

    Node* headB = new Node(3);
    headB->next = common;

    cout << "A: 1 -> 2 -> 8 -> 4 -> 5\n";
    cout << "B: 3 -> 8 -> 4 -> 5\n";
    Node* inter = getIntersection(headA, headB);
    cout << "Intersection at: " << (inter ? to_string(inter->data) : "NULL") << "\n";

    // Cleanup (careful: shared nodes)
    delete headA->next; delete headA;
    delete headB;
    delete common->next->next; delete common->next; delete common;

    // Happy Number
    cout << "\n═══ HAPPY NUMBER ═══\n";
    for (int n : {19, 2, 7, 4, 100, 1}) {
        cout << n << " is " << (isHappy(n) ? "HAPPY 😊" : "NOT HAPPY 😢") << "\n";
    }

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE: LeetCode 19, 234, 160, 202, 876\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

