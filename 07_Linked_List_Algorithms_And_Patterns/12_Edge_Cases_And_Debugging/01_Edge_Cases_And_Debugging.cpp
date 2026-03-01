/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — EDGE CASES & DEBUGGING IN LINKED LISTS                      ║
║           From Zero to Grandmaster — Master All Edge Cases                 ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Common Edge Cases & How to Handle Them
 2. Memory Leak Detection & Prevention
 3. Dangling Pointer Pitfalls
 4. Debugging Techniques (Print, Assert, Visualize)
 5. Interview Patterns & Top Tips
 6. The Dummy Node Master Pattern

EDGE CASES THAT BREAK YOUR CODE:
────────────────────────────────
  ┌──────────────────────────────────────────────────────────────┐
  │  Case                    │  What can go wrong                │
  ├──────────────────────────┼──────────────────────────────────-┤
  │  Empty list (NULL head)  │  Dereference NULL → CRASH         │
  │  Single node             │  head->next is NULL               │
  │  Two nodes               │  Boundary in many algorithms      │
  │  Even vs Odd length      │  Middle node differs              │
  │  All same values         │  Remove duplicates edge case      │
  │  Insert at position 0    │  Need to update head              │
  │  Delete head node        │  Need to return new head          │
  │  Delete tail node        │  SLL needs O(n) to find prev      │
  │  Cycle exists            │  Infinite loop in traversal!      │
  │  Very long list          │  Stack overflow in recursion      │
  └──────────────────────────┴──────────────────────────────────-┘

THE DUMMY NODE PATTERN:
──────────────────────
  THE most important trick for linked list problems!
  Eliminates ALL head-related edge cases.

  WITHOUT dummy:
  ─────────────
  Node* insertSorted(Node* head, int val) {
      if (!head || val <= head->data) {   // Special case for head!
          Node* n = new Node(val);
          n->next = head;
          return n;
      }
      Node* curr = head;
      while (curr->next && curr->next->data < val) curr = curr->next;
      Node* n = new Node(val);
      n->next = curr->next;
      curr->next = n;
      return head;
  }

  WITH dummy:
  ──────────
  Node* insertSorted(Node* head, int val) {
      Node dummy(0);
      dummy.next = head;
      Node* curr = &dummy;
      while (curr->next && curr->next->data < val) curr = curr->next;
      Node* n = new Node(val);
      n->next = curr->next;
      curr->next = n;
      return dummy.next;  // No special cases needed!
  }

  DUMMY NODE ON STACK (not heap) — no need to delete!
*/

#include <iostream>
#include <cassert>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

void printList(Node* head) {
    while (head) { cout << head->data; if (head->next) cout << " -> "; head = head->next; }
    cout << " -> NULL\n";
}

void freeList(Node* head) { while (head) { Node* t = head; head = head->next; delete t; } }

int length(Node* head) { int c = 0; while (head) { c++; head = head->next; } return c; }

// ═══════════════════════════════════════════════════════════════
// 1. EDGE CASE TESTING FRAMEWORK
// ═══════════════════════════════════════════════════════════════

// Reverse function to test
Node* reverse(Node* head) {
    Node* prev = nullptr;
    while (head) { Node* n = head->next; head->next = prev; prev = head; head = n; }
    return prev;
}

void testReverse() {
    cout << "  Testing reverse...\n";

    // Empty list
    Node* h = nullptr;
    h = reverse(h);
    assert(h == nullptr);
    cout << "    ✅ Empty list\n";

    // Single node
    h = new Node(1);
    h = reverse(h);
    assert(h->data == 1 && h->next == nullptr);
    cout << "    ✅ Single node\n";
    delete h;

    // Two nodes
    h = new Node(1); h->next = new Node(2);
    h = reverse(h);
    assert(h->data == 2 && h->next->data == 1);
    cout << "    ✅ Two nodes\n";
    freeList(h);

    // Odd length
    h = new Node(1); h->next = new Node(2); h->next->next = new Node(3);
    h = reverse(h);
    assert(h->data == 3 && h->next->data == 2 && h->next->next->data == 1);
    cout << "    ✅ Odd length (3)\n";
    freeList(h);

    // Even length
    h = new Node(1); h->next = new Node(2);
    h->next->next = new Node(3); h->next->next->next = new Node(4);
    h = reverse(h);
    assert(h->data == 4);
    cout << "    ✅ Even length (4)\n";
    freeList(h);

    // All same values
    h = new Node(5); h->next = new Node(5); h->next->next = new Node(5);
    h = reverse(h);
    assert(h->data == 5 && length(h) == 3);
    cout << "    ✅ All same values\n";
    freeList(h);
}

// ═══════════════════════════════════════════════════════════════
// 2. MEMORY LEAK DETECTION & PREVENTION
// ═══════════════════════════════════════════════════════════════
/*
  MEMORY LEAK: Allocated memory that is never freed.

  ❌ COMMON MISTAKES:
  ──────────────────
  1. Forgetting to delete removed nodes:
     curr->next = curr->next->next;  // LEAK! Skipped node not freed

  2. Reassigning head without freeing:
     head = head->next;  // LEAK! Old head not freed

  3. Returning early without cleanup:
     if (error) return;  // LEAK! List not freed

  4. Losing the only pointer to a node:
     Node* temp = head;
     head = new Node(5);  // If temp not saved, old head is LEAKED

  ✅ CORRECT PATTERN:
  ───────────────────
  1. Always save pointer before reassigning:
     Node* temp = curr->next;
     curr->next = temp->next;
     delete temp;  ✅

  2. Delete entire list in destructor / cleanup function:
     void freeList(Node* head) {
         while (head) {
             Node* temp = head;
             head = head->next;
             delete temp;
         }
     }
*/

void demonstrateMemoryPitfalls() {
    cout << "\n═══ MEMORY PITFALL EXAMPLES ═══\n\n";

    // ❌ Wrong: Memory leak
    cout << "  ❌ BAD: curr->next = curr->next->next (leaks skipped node)\n";

    // ✅ Correct: Save and delete
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);

    cout << "  ✅ GOOD: Save pointer, relink, then delete\n";
    Node* toDelete = head->next;  // Save [2]
    head->next = head->next->next; // [1] → [3]
    delete toDelete;                // Free [2]
    cout << "  After correct deletion: "; printList(head);
    freeList(head);
}

// ═══════════════════════════════════════════════════════════════
// 3. DANGLING POINTER PREVENTION
// ═══════════════════════════════════════════════════════════════
/*
  DANGLING POINTER: Pointer that points to freed/deallocated memory.

  ❌ DANGEROUS:
  Node* node = new Node(10);
  delete node;
  cout << node->data;  // UNDEFINED BEHAVIOR! node is dangling

  ✅ SAFE:
  Node* node = new Node(10);
  delete node;
  node = nullptr;      // Set to NULL after delete
  if (node) cout << node->data;  // Safe — won't execute
*/

void demonstrateDanglingPointer() {
    cout << "\n═══ DANGLING POINTER PREVENTION ═══\n\n";

    Node* node = new Node(42);
    cout << "  Before delete: node->data = " << node->data << "\n";

    delete node;
    node = nullptr;  // ✅ Set to NULL after delete!

    if (node) {
        cout << "  After delete: " << node->data << "\n";
    } else {
        cout << "  After delete: node is NULL (safe!) ✅\n";
    }
}

// ═══════════════════════════════════════════════════════════════
// 4. DEBUGGING UTILITIES
// ═══════════════════════════════════════════════════════════════

// Verbose print with addresses (for debugging pointer issues)
void debugPrint(Node* head) {
    cout << "  DEBUG: ";
    int idx = 0;
    while (head) {
        cout << "[" << idx << ": val=" << head->data
             << " @" << head << " →" << head->next << "] ";
        head = head->next;
        idx++;
    }
    cout << "\n";
}

// Detect cycle (returns true and prints info)
bool debugDetectCycle(Node* head) {
    Node* slow = head;
    Node* fast = head;
    int steps = 0;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        steps++;
        if (slow == fast) {
            cout << "  ⚠️  CYCLE DETECTED after " << steps << " steps!\n";
            cout << "  Meeting point: val=" << slow->data << " @" << slow << "\n";
            return true;
        }
    }
    cout << "  ✅ No cycle detected (list is proper)\n";
    return false;
}

// Validate list structure
void validateList(Node* head, int expectedLength) {
    int actual = length(head);
    if (actual == expectedLength) {
        cout << "  ✅ Length check passed: " << actual << "\n";
    } else {
        cout << "  ❌ Length mismatch! Expected " << expectedLength
             << ", got " << actual << "\n";
    }
}

// ═══════════════════════════════════════════════════════════════
// 5. INTERVIEW MASTER PATTERNS CHECKLIST
// ═══════════════════════════════════════════════════════════════
/*
  TOP 20 INTERVIEW PATTERNS:
  ─────────────────────────
  ┌────┬────────────────────────────┬──────────────────────────┐
  │ #  │ Pattern                    │ Used In                  │
  ├────┼────────────────────────────┼──────────────────────────┤
  │  1 │ Dummy Node                 │ Almost every LL problem  │
  │  2 │ Two Pointer (same speed)   │ Intersection, merge      │
  │  3 │ Fast/Slow Pointer          │ Middle, cycle, palindrome│
  │  4 │ Three-Pointer Reversal     │ Reverse, K-group, sublist│
  │  5 │ Recursive Reversal         │ Elegant reversal         │
  │  6 │ Split + Reverse + Merge    │ Reorder, palindrome, sort│
  │  7 │ Carry Propagation          │ Add numbers              │
  │  8 │ In-place Modification      │ Most LL problems         │
  │  9 │ DLL + HashMap              │ LRU, LFU, O(1) cache    │
  │ 10 │ Sentinel Nodes             │ DLL operations           │
  │ 11 │ Counting First             │ K-group, nth from end    │
  │ 12 │ Interleaving               │ Clone random, merge      │
  │ 13 │ Stack-based Approach       │ Add numbers II, reverse  │
  │ 14 │ Recursion with Backtrack   │ Reverse print, deep copy │
  │ 15 │ Circular Logic             │ Josephus, rotate         │
  │ 16 │ Multiple Dummy Lists       │ Partition, odd-even      │
  │ 17 │ Hash Set for Visited       │ Remove unsorted dups     │
  │ 18 │ Right-to-Left Processing   │ Delete greater on right  │
  │ 19 │ Level-by-Level Processing  │ Flatten multilevel       │
  │ 20 │ Iterator Pattern           │ Design Linked List class │
  └────┴────────────────────────────┴──────────────────────────┘

  BEFORE CODING ANY LL PROBLEM:
  ────────────────────────────
  1. Draw the linked list
  2. Identify which pattern to use
  3. Think about edge cases: empty, 1 node, 2 nodes
  4. Use dummy node if head might change
  5. Walk through your algorithm on paper FIRST
  6. Code it
  7. Test with edge cases
*/

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  EDGE CASES & DEBUGGING IN LINKED LISTS                ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Edge case testing
    cout << "═══ EDGE CASE TESTING ═══\n";
    testReverse();

    // Memory pitfalls
    demonstrateMemoryPitfalls();

    // Dangling pointers
    demonstrateDanglingPointer();

    // Debug utilities
    cout << "\n═══ DEBUGGING UTILITIES ═══\n\n";
    Node* head = new Node(10);
    head->next = new Node(20);
    head->next->next = new Node(30);

    debugPrint(head);
    debugDetectCycle(head);
    validateList(head, 3);

    freeList(head);

    // Cycle detection debug
    cout << "\n  Creating list with cycle for testing...\n";
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    n1->next = n2; n2->next = n3; n3->next = n2; // cycle at 2
    debugDetectCycle(n1);
    // Break cycle for cleanup
    n3->next = nullptr;
    freeList(n1);

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "INTERVIEW CHECKLIST:\n";
    cout << "  □ Always handle empty list (head == NULL)\n";
    cout << "  □ Always handle single node (head->next == NULL)\n";
    cout << "  □ Use dummy node when head might change\n";
    cout << "  □ Draw the pointer diagram before coding\n";
    cout << "  □ Test with even AND odd length lists\n";
    cout << "  □ Free memory / explain cleanup in interview\n";
    cout << "  □ Consider cycle — does your algo handle it?\n";
    cout << "  □ Mention time & space complexity\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

