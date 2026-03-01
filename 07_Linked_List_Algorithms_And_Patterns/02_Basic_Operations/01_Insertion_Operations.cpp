/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — INSERTION OPERATIONS IN LINKED LIST                           ║
║           From Zero to Grandmaster — Complete Foundation                     ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Insert at Head
 2. Insert at Tail
 3. Insert at Position
 4. Insert in Sorted Order

DRY RUN — Insert at Head:
─────────────────────────
  Before:  head ──▶ [20] ──▶ [30] ──▶ NULL
  Insert 10 at head:

  Step 1: newNode = new Node(10)
          [10 | NULL]

  Step 2: newNode->next = head
          [10 | ──]──▶ [20] ──▶ [30] ──▶ NULL

  Step 3: head = newNode
          head ──▶ [10] ──▶ [20] ──▶ [30] ──▶ NULL  ✅

  Time: O(1)  Space: O(1)

DRY RUN — Insert at Tail:
─────────────────────────
  Before:  head ──▶ [10] ──▶ [20] ──▶ NULL
  Insert 30 at tail:

  Step 1: newNode = new Node(30)
  Step 2: Traverse to last node (20)
  Step 3: last->next = newNode
          head ──▶ [10] ──▶ [20] ──▶ [30] ──▶ NULL  ✅

  Time: O(n)  Space: O(1)

DRY RUN — Insert at Position 2 (0-indexed):
────────────────────────────────────────────
  Before:  head ──▶ [10] ──▶ [20] ──▶ [40] ──▶ NULL
  Insert 30 at position 2:

  Step 1: newNode = new Node(30)
  Step 2: Traverse to position 1 (node 20)
          curr at [20]
  Step 3: newNode->next = curr->next  →  [30]──▶[40]
  Step 4: curr->next = newNode        →  [20]──▶[30]

  After:   head ──▶ [10] ──▶ [20] ──▶ [30] ──▶ [40] ──▶ NULL  ✅

  Time: O(n)  Space: O(1)
*/

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

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
// 1. INSERT AT HEAD — O(1) time, O(1) space
// ═══════════════════════════════════════════════════════════════

Node* insertAtHead(Node* head, int val) {
    Node* newNode = new Node(val);
    newNode->next = head;
    return newNode;  // New head
}

// ═══════════════════════════════════════════════════════════════
// 2. INSERT AT TAIL — O(n) time, O(1) space
// ═══════════════════════════════════════════════════════════════

Node* insertAtTail(Node* head, int val) {
    Node* newNode = new Node(val);

    if (head == nullptr) return newNode;  // Empty list

    Node* curr = head;
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    curr->next = newNode;
    return head;
}

// ═══════════════════════════════════════════════════════════════
// 3. INSERT AT POSITION — O(n) time, O(1) space
// ═══════════════════════════════════════════════════════════════
/*
  Position is 0-indexed.
  pos=0 → insert at head
  pos=length → insert at tail
*/

Node* insertAtPosition(Node* head, int val, int pos) {
    if (pos == 0) return insertAtHead(head, val);

    Node* newNode = new Node(val);
    Node* curr = head;

    for (int i = 0; i < pos - 1 && curr != nullptr; i++) {
        curr = curr->next;
    }

    if (curr == nullptr) {
        cout << "Position out of range!\n";
        delete newNode;
        return head;
    }

    newNode->next = curr->next;
    curr->next = newNode;
    return head;
}

// ═══════════════════════════════════════════════════════════════
// 4. INSERT IN SORTED ORDER — O(n) time, O(1) space
// ═══════════════════════════════════════════════════════════════
/*
  DRY RUN — Insert 25 into sorted list [10, 20, 30, 40]:

  Step 1: Compare 25 with 10 → 25 > 10, move forward
  Step 2: Compare 25 with 20 → 25 > 20, move forward
  Step 3: Compare 25 with 30 → 25 < 30, insert before 30!

  Result: [10] ──▶ [20] ──▶ [25] ──▶ [30] ──▶ [40] ──▶ NULL
*/

Node* insertSorted(Node* head, int val) {
    Node* newNode = new Node(val);

    // Insert at head if list is empty or val is smallest
    if (head == nullptr || val <= head->data) {
        newNode->next = head;
        return newNode;
    }

    Node* curr = head;
    while (curr->next != nullptr && curr->next->data < val) {
        curr = curr->next;
    }

    newNode->next = curr->next;
    curr->next = newNode;
    return head;
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  INSERTION OPERATIONS IN LINKED LIST                   ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Insert at Head
    cout << "═══ INSERT AT HEAD ═══\n";
    Node* head = nullptr;
    head = insertAtHead(head, 30);
    head = insertAtHead(head, 20);
    head = insertAtHead(head, 10);
    cout << "After inserting 30, 20, 10 at head: "; printList(head);
    deleteList(head);

    // Insert at Tail
    cout << "\n═══ INSERT AT TAIL ═══\n";
    head = nullptr;
    head = insertAtTail(head, 10);
    head = insertAtTail(head, 20);
    head = insertAtTail(head, 30);
    cout << "After inserting 10, 20, 30 at tail: "; printList(head);
    deleteList(head);

    // Insert at Position
    cout << "\n═══ INSERT AT POSITION ═══\n";
    head = nullptr;
    head = insertAtTail(head, 10);
    head = insertAtTail(head, 20);
    head = insertAtTail(head, 40);
    cout << "Before: "; printList(head);
    head = insertAtPosition(head, 30, 2);
    cout << "After insert 30 at pos 2: "; printList(head);
    head = insertAtPosition(head, 5, 0);
    cout << "After insert 5 at pos 0:  "; printList(head);
    deleteList(head);

    // Insert in Sorted Order
    cout << "\n═══ INSERT IN SORTED ORDER ═══\n";
    head = nullptr;
    int values[] = {30, 10, 20, 40, 25, 5, 35};
    for (int v : values) {
        head = insertSorted(head, v);
        cout << "Insert " << v << ": "; printList(head);
    }
    deleteList(head);

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "COMPLEXITY SUMMARY:\n";
    cout << "───────────────────\n";
    cout << "Insert at Head:     O(1) time, O(1) space\n";
    cout << "Insert at Tail:     O(n) time, O(1) space\n";
    cout << "Insert at Position: O(n) time, O(1) space\n";
    cout << "Insert Sorted:      O(n) time, O(1) space\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

