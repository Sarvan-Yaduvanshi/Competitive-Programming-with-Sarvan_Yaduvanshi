/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — SKIP LIST IMPLEMENTATION & UNROLLED LINKED LIST             ║
║           From Zero to Grandmaster — Advanced LL Data Structures           ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Skip List — Complete Implementation (LeetCode 1206)
 2. Unrolled Linked List (Concept)
 3. Self-Organizing List (Move-to-Front)

SKIP LIST:
─────────
  A probabilistic data structure that allows O(log n) average
  search, insert, and delete in a sorted linked list.

  Structure (multiple levels of linked lists):

  Level 3:  HEAD ─────────────────────── 6 ────────── NIL
  Level 2:  HEAD ───── 3 ────────────── 6 ──── 9 ─── NIL
  Level 1:  HEAD ── 2 ─ 3 ── 5 ── 6 ── 7 ─── 9 ─── NIL
  Level 0:  HEAD ─ 1 ─ 2 ─ 3 ─ 4 ─ 5 ─ 6 ─ 7 ─ 8 ─ 9 ─ NIL

  Each element appears at level 0 (bottom).
  With probability p (usually 0.5), it also appears at the next level.

  Search for 7:
    Start Level 3: HEAD → 6 → NIL (6 < 7, but next is NIL, go down)
    Level 2: 6 → 9 (9 > 7, go down)
    Level 1: 6 → 7  FOUND! ✅

  Expected complexity: O(log n) for search, insert, delete
  Space: O(n) expected

  Used in: Redis, LevelDB, MemSQL, Java ConcurrentSkipListMap
*/

#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
#include <ctime>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// 1. SKIP LIST IMPLEMENTATION (LeetCode 1206)
// ═══════════════════════════════════════════════════════════════

class Skiplist {
    static const int MAX_LEVEL = 16;
    static constexpr double P = 0.5;

    struct SkipNode {
        int val;
        vector<SkipNode*> forward;  // forward[i] = next node at level i
        SkipNode(int v, int level) : val(v), forward(level + 1, nullptr) {}
    };

    SkipNode* head;
    int currentLevel;

    int randomLevel() {
        int lvl = 0;
        while ((double)rand() / RAND_MAX < P && lvl < MAX_LEVEL - 1) {
            lvl++;
        }
        return lvl;
    }

public:
    Skiplist() {
        srand(time(nullptr));
        head = new SkipNode(INT_MIN, MAX_LEVEL);
        currentLevel = 0;
    }

    ~Skiplist() {
        SkipNode* curr = head;
        while (curr) {
            SkipNode* next = curr->forward[0];
            delete curr;
            curr = next;
        }
    }

    bool search(int target) {
        SkipNode* curr = head;
        for (int i = currentLevel; i >= 0; i--) {
            while (curr->forward[i] && curr->forward[i]->val < target) {
                curr = curr->forward[i];
            }
        }
        curr = curr->forward[0];
        return curr && curr->val == target;
    }

    void add(int num) {
        vector<SkipNode*> update(MAX_LEVEL, head);
        SkipNode* curr = head;

        // Find position at each level
        for (int i = currentLevel; i >= 0; i--) {
            while (curr->forward[i] && curr->forward[i]->val < num) {
                curr = curr->forward[i];
            }
            update[i] = curr;
        }

        int newLevel = randomLevel();
        if (newLevel > currentLevel) {
            currentLevel = newLevel;
        }

        SkipNode* newNode = new SkipNode(num, newLevel);

        // Insert at each level
        for (int i = 0; i <= newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }

    bool erase(int num) {
        vector<SkipNode*> update(MAX_LEVEL, head);
        SkipNode* curr = head;

        for (int i = currentLevel; i >= 0; i--) {
            while (curr->forward[i] && curr->forward[i]->val < num) {
                curr = curr->forward[i];
            }
            update[i] = curr;
        }

        curr = curr->forward[0];
        if (!curr || curr->val != num) return false;

        for (int i = 0; i <= currentLevel; i++) {
            if (update[i]->forward[i] != curr) break;
            update[i]->forward[i] = curr->forward[i];
        }

        delete curr;

        while (currentLevel > 0 && !head->forward[currentLevel]) {
            currentLevel--;
        }
        return true;
    }

    void print() {
        for (int i = currentLevel; i >= 0; i--) {
            cout << "  Level " << i << ": HEAD";
            SkipNode* curr = head->forward[i];
            while (curr) {
                cout << " → " << curr->val;
                curr = curr->forward[i];
            }
            cout << " → NIL\n";
        }
    }
};

// ═══════════════════════════════════════════════════════════════
// 2. SELF-ORGANIZING LIST (Move-to-Front Heuristic)
// ═══════════════════════════════════════════════════════════════
/*
  When an element is accessed, move it to the front of the list.
  Frequently accessed elements naturally migrate to the front.
  Amortized O(1) for frequently accessed elements!

  Used in: LRU caches, compiler symbol tables, self-adjusting DS

  DRY RUN:
    List: A → B → C → D
    Access C: Move C to front → C → A → B → D
    Access C: Already near front → C → A → B → D (no change)
    Access D: Move D to front → D → C → A → B
*/

class SelfOrganizingList {
    struct Node {
        int data;
        int accessCount;
        Node* next;
        Node(int val) : data(val), accessCount(0), next(nullptr) {}
    };

    Node* head;

public:
    SelfOrganizingList() : head(nullptr) {}

    ~SelfOrganizingList() {
        while (head) { Node* t = head; head = head->next; delete t; }
    }

    void insert(int val) {
        Node* node = new Node(val);
        node->next = head;
        head = node;
    }

    // Move-to-Front: O(n) search, O(1) move
    bool searchMTF(int val) {
        if (!head) return false;
        if (head->data == val) {
            head->accessCount++;
            return true;
        }

        Node* prev = head;
        Node* curr = head->next;
        while (curr) {
            if (curr->data == val) {
                curr->accessCount++;
                // Move to front
                prev->next = curr->next;
                curr->next = head;
                head = curr;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false;
    }

    void print() {
        Node* curr = head;
        while (curr) {
            cout << curr->data << "(cnt=" << curr->accessCount << ")";
            if (curr->next) cout << " → ";
            curr = curr->next;
        }
        cout << " → NULL\n";
    }
};

// ═══════════════════════════════════════════════════════════════
// 3. UNROLLED LINKED LIST (Concept)
// ═══════════════════════════════════════════════════════════════
/*
  UNROLLED LINKED LIST:
  ────────────────────
  Each node stores an ARRAY of elements instead of one element.
  Combines cache-friendliness of arrays with flexibility of LL.

  Normal LL:
  [1] → [2] → [3] → [4] → [5] → [6] → [7] → [8]
  (8 nodes, 8 pointers, poor cache)

  Unrolled LL (block size = 4):
  [1,2,3,4] → [5,6,7,8]
  (2 nodes, 2 pointers, great cache!)

  ┌─────────────────┬──────┐   ┌─────────────────┬──────┐
  │ [1, 2, 3, 4]    │ next─┼──▶│ [5, 6, 7, 8]    │ NULL │
  │ count = 4       │      │   │ count = 4       │      │
  └─────────────────┴──────┘   └─────────────────┴──────┘

  Advantages:
  • Better cache performance (sequential access within blocks)
  • Less memory overhead (fewer pointers)
  • Good for text editors (rope variant)

  Complexity:
  • Search: O(n) worst case, but faster in practice
  • Insert: O(√n) amortized (split blocks when full)
  • Space: O(n) but with less overhead
*/

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  SKIP LIST & SELF-ORGANIZING LIST                      ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Skip List
    cout << "═══ SKIP LIST ═══\n";
    Skiplist sl;
    for (int x : {3, 6, 7, 9, 12, 17, 19, 21, 25}) {
        sl.add(x);
    }
    cout << "After inserting [3,6,7,9,12,17,19,21,25]:\n";
    sl.print();

    cout << "\nSearch 7: " << (sl.search(7) ? "FOUND" : "NOT FOUND") << "\n";
    cout << "Search 10: " << (sl.search(10) ? "FOUND" : "NOT FOUND") << "\n";

    sl.erase(7);
    cout << "\nAfter erasing 7:\n";
    sl.print();
    cout << "Search 7: " << (sl.search(7) ? "FOUND" : "NOT FOUND") << "\n";

    // Self-Organizing List
    cout << "\n═══ SELF-ORGANIZING LIST (Move-to-Front) ═══\n";
    SelfOrganizingList sol;
    for (int x : {5, 4, 3, 2, 1}) sol.insert(x);
    cout << "Initial: "; sol.print();

    sol.searchMTF(3);
    cout << "After accessing 3: "; sol.print();

    sol.searchMTF(5);
    cout << "After accessing 5: "; sol.print();

    sol.searchMTF(3);
    cout << "After accessing 3 again: "; sol.print();

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "SKIP LIST vs BALANCED BST:\n";
    cout << "  Both: O(log n) search/insert/delete\n";
    cout << "  Skip List: Simpler to implement, probabilistic\n";
    cout << "  BST: Deterministic, but complex (AVL/Red-Black)\n";
    cout << "  Skip List: Better for concurrent access (lock-free)\n";
    cout << "\nPRACTICE: LeetCode 1206 (Design Skiplist)\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

