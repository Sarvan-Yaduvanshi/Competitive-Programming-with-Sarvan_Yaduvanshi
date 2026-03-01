/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — CLONE LINKED LIST WITH RANDOM POINTER (LeetCode 138)        ║
║           From Zero to Grandmaster — Advanced Pointer Manipulation         ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Clone with Random Pointer — HashMap Approach O(n) space
 2. Clone with Random Pointer — Interleaving Approach O(1) space
 3. Deep Copy vs Shallow Copy
 4. XOR Linked List (Concept)

PROBLEM: Clone a linked list where each node has next AND random pointers.

  Original:
  ┌────┬────┬─────┐   ┌────┬────┬─────┐   ┌────┬────┬─────┐
  │ 1  │next│rand─┼──▶│ 2  │next│rand─┼──▶│ 3  │next│rand │
  └────┴──┬─┴─────┘   └────┴──┬─┴─────┘   └────┴──┬─┴──┬──┘
          │                    │                    │    │
          ▼                    ▼                    ▼    ▼
         [3]                  [1]                 NULL  [1]

  Must create a DEEP COPY — completely separate list with same structure.

DRY RUN — Interleaving Approach:
───────────────────────────────
  Step 1: Interleave — Insert clone after each original
          1 → 1' → 2 → 2' → 3 → 3' → NULL

  Step 2: Copy random pointers
          If original->random = X, then clone->random = X->next (which is X')
          1.random = 3 → 1'.random = 3.next = 3'
          2.random = 1 → 2'.random = 1.next = 1'
          3.random = NULL → 3'.random = NULL

  Step 3: Separate the two lists
          Original: 1 → 2 → 3 → NULL
          Clone:    1' → 2' → 3' → NULL ✅

  Time: O(n)  Space: O(1) (excluding output)
*/

#include <iostream>
#include <unordered_map>
using namespace std;

struct RNode {
    int data;
    RNode* next;
    RNode* random;
    RNode(int val) : data(val), next(nullptr), random(nullptr) {}
};

void printRandomList(RNode* head) {
    RNode* curr = head;
    while (curr) {
        cout << "[" << curr->data << ", rand=";
        if (curr->random) cout << curr->random->data;
        else cout << "NULL";
        cout << "]";
        if (curr->next) cout << " -> ";
        curr = curr->next;
    }
    cout << " -> NULL\n";
}

void freeRandomList(RNode* head) {
    while (head) { RNode* t = head; head = head->next; delete t; }
}

// ═══════════════════════════════════════════════════════════════
// 1. HASHMAP APPROACH — O(n) time, O(n) space
// ═══════════════════════════════════════════════════════════════

RNode* cloneWithHashMap(RNode* head) {
    if (!head) return nullptr;

    unordered_map<RNode*, RNode*> map;

    // Pass 1: Create all clone nodes
    RNode* curr = head;
    while (curr) {
        map[curr] = new RNode(curr->data);
        curr = curr->next;
    }

    // Pass 2: Set next and random pointers
    curr = head;
    while (curr) {
        map[curr]->next = map[curr->next];
        map[curr]->random = map[curr->random];
        curr = curr->next;
    }

    return map[head];
}

// ═══════════════════════════════════════════════════════════════
// 2. INTERLEAVING APPROACH — O(n) time, O(1) space ⭐
// ═══════════════════════════════════════════════════════════════

RNode* cloneWithInterleaving(RNode* head) {
    if (!head) return nullptr;

    // Step 1: Insert clone nodes
    //   1 → 2 → 3  becomes  1 → 1' → 2 → 2' → 3 → 3'
    RNode* curr = head;
    while (curr) {
        RNode* clone = new RNode(curr->data);
        clone->next = curr->next;
        curr->next = clone;
        curr = clone->next;
    }

    // Step 2: Copy random pointers
    curr = head;
    while (curr) {
        if (curr->random) {
            curr->next->random = curr->random->next;
        }
        curr = curr->next->next;
    }

    // Step 3: Separate lists
    RNode* cloneHead = head->next;
    curr = head;
    RNode* cloneCurr = cloneHead;

    while (curr) {
        curr->next = cloneCurr->next;
        curr = curr->next;
        if (curr) {
            cloneCurr->next = curr->next;
            cloneCurr = cloneCurr->next;
        } else {
            cloneCurr->next = nullptr;
        }
    }

    return cloneHead;
}

// ═══════════════════════════════════════════════════════════════
// 3. DEEP COPY vs SHALLOW COPY
// ═══════════════════════════════════════════════════════════════
/*
  SHALLOW COPY:
  ─────────────
  Just copies the pointer → both point to SAME memory

  Node* original = new Node(10);
  Node* shallow = original;  // Same object!
  shallow->data = 99;        // Changes original too!

  DEEP COPY:
  ──────────
  Creates a NEW independent copy → separate memory

  Node* original = new Node(10);
  Node* deep = new Node(original->data);  // New object!
  deep->data = 99;  // Original unchanged!

  ┌───────────────────────────────────────────┐
  │  Shallow: ptr1 ──┐                        │
  │                   ├──▶ [data = 10]         │
  │  Shallow: ptr2 ──┘                        │
  │                                            │
  │  Deep:    ptr1 ──▶ [data = 10]  (copy 1)  │
  │           ptr2 ──▶ [data = 10]  (copy 2)  │
  └───────────────────────────────────────────┘
*/

// ═══════════════════════════════════════════════════════════════
// 4. XOR LINKED LIST (Concept — Memory Efficient DLL)
// ═══════════════════════════════════════════════════════════════
/*
  XOR LINKED LIST:
  ───────────────
  A memory-efficient doubly linked list that uses XOR of prev and next
  addresses in a single pointer field!

  Normal DLL: Each node has prev + next → 2 pointers (16 bytes)
  XOR DLL:    Each node has npx (next XOR prev) → 1 pointer (8 bytes)
  Saves 50% pointer memory!

  How it works:
  ┌──────┬──────────────────┐
  │ data │ npx = prev ⊕ next│
  └──────┴──────────────────┘

  To traverse forward:  next = prev ⊕ npx
  To traverse backward: prev = next ⊕ npx

  WHY? Because: A ⊕ (A ⊕ B) = B

  LIMITATION: Cannot use in standard C++ easily (casting pointers to int)
  RARELY USED: Interesting concept, but practical use is limited.
  In CP: Use regular DLL — speed > memory savings

  NOTE: This requires reinterpret_cast and is platform-dependent.
  Shown here as concept only.

  struct XORNode {
      int data;
      XORNode* npx;  // XOR of prev and next
  };

  XORNode* XOR(XORNode* a, XORNode* b) {
      return reinterpret_cast<XORNode*>(
          reinterpret_cast<uintptr_t>(a) ^ reinterpret_cast<uintptr_t>(b)
      );
  }
*/

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  CLONE LIST WITH RANDOM POINTER & XOR LINKED LIST      ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Build test list: 1(→3), 2(→1), 3(→NULL)
    RNode* n1 = new RNode(1);
    RNode* n2 = new RNode(2);
    RNode* n3 = new RNode(3);
    n1->next = n2; n2->next = n3;
    n1->random = n3;
    n2->random = n1;
    n3->random = nullptr;

    cout << "═══ ORIGINAL LIST ═══\n";
    printRandomList(n1);

    // HashMap clone
    cout << "\n═══ CLONE (HashMap) ═══\n";
    RNode* clone1 = cloneWithHashMap(n1);
    printRandomList(clone1);
    cout << "Original addr: " << n1 << ", Clone addr: " << clone1 << " (different!)\n";

    // Interleaving clone
    cout << "\n═══ CLONE (Interleaving — O(1) space) ═══\n";
    RNode* clone2 = cloneWithInterleaving(n1);
    printRandomList(clone2);
    cout << "Original addr: " << n1 << ", Clone addr: " << clone2 << " (different!)\n";

    // Verify deep copy (modify clone, original unchanged)
    cout << "\n═══ DEEP COPY VERIFICATION ═══\n";
    clone1->data = 999;
    cout << "Modified clone1 data to 999\n";
    cout << "Original: "; printRandomList(n1);
    cout << "Clone1:   "; printRandomList(clone1);
    cout << "Original unchanged → DEEP COPY confirmed! ✅\n";

    freeRandomList(n1);
    freeRandomList(clone1);
    freeRandomList(clone2);

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE: LeetCode 138, GFG Clone List with Random Pointer\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

