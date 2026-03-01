/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — LRU CACHE (LeetCode 146 — Medium)                          ║
║           From Zero to Grandmaster — #1 Design Interview Problem           ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Problem Description
 2. Data Structure Design (DLL + HashMap)
 3. Complete Implementation
 4. Dry Run with Example

LRU CACHE = Least Recently Used Cache
─────────────────────────────────────
  • Fixed capacity cache
  • get(key): O(1) — return value if exists, else -1
  • put(key, value): O(1) — insert/update, evict LRU if full

  WHY DLL + HashMap?
  ──────────────────
  HashMap: O(1) lookup by key → gives pointer to DLL node
  DLL:     O(1) insert/delete → maintains access order

  ┌─────────────────────────────────────────────────────┐
  │  HashMap: key → DLL Node*                           │
  │                                                      │
  │  DLL: HEAD ↔ [MRU] ↔ [...] ↔ [LRU] ↔ TAIL         │
  │        ↑                                 ↑           │
  │   Dummy head                        Dummy tail       │
  │   (sentinel)                        (sentinel)       │
  └─────────────────────────────────────────────────────┘

  Operations:
  • get(key): Move node to front (most recently used)
  • put(key, val):
    - If exists: Update value, move to front
    - If not exists: Insert at front
    - If over capacity: Remove node before tail (LRU)

DRY RUN — Capacity = 2:
───────────────────────
  put(1, 1):  DLL: [1:1]          Map: {1}
  put(2, 2):  DLL: [2:2] ↔ [1:1]  Map: {1, 2}
  get(1):     Move 1 to front
              DLL: [1:1] ↔ [2:2]  Returns 1
  put(3, 3):  Full! Evict LRU (2)
              DLL: [3:3] ↔ [1:1]  Map: {1, 3}
  get(2):     Not found → Returns -1
  put(4, 4):  Full! Evict LRU (1)
              DLL: [4:4] ↔ [3:3]  Map: {3, 4}
  get(1):     Not found → Returns -1
  get(3):     Move 3 to front
              DLL: [3:3] ↔ [4:4]  Returns 3
  get(4):     Move 4 to front
              DLL: [4:4] ↔ [3:3]  Returns 4
*/

#include <iostream>
#include <unordered_map>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// LRU CACHE IMPLEMENTATION — O(1) get, O(1) put
// ═══════════════════════════════════════════════════════════════

class LRUCache {
private:
    struct DLLNode {
        int key, value;
        DLLNode* prev;
        DLLNode* next;
        DLLNode(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    int capacity;
    unordered_map<int, DLLNode*> map;
    DLLNode* head;  // Dummy head (sentinel)
    DLLNode* tail;  // Dummy tail (sentinel)

    // Add node right after head (most recently used position)
    void addToFront(DLLNode* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    // Remove a node from the DLL
    void removeNode(DLLNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    // Move existing node to front (mark as most recently used)
    void moveToFront(DLLNode* node) {
        removeNode(node);
        addToFront(node);
    }

    // Remove the LRU node (the one before tail sentinel)
    DLLNode* removeLRU() {
        DLLNode* lru = tail->prev;
        removeNode(lru);
        return lru;
    }

public:
    LRUCache(int cap) : capacity(cap) {
        head = new DLLNode(0, 0);  // Dummy head
        tail = new DLLNode(0, 0);  // Dummy tail
        head->next = tail;
        tail->prev = head;
    }

    ~LRUCache() {
        DLLNode* curr = head;
        while (curr) {
            DLLNode* next = curr->next;
            delete curr;
            curr = next;
        }
    }

    int get(int key) {
        if (map.find(key) == map.end()) return -1;

        DLLNode* node = map[key];
        moveToFront(node);  // Mark as recently used
        return node->value;
    }

    void put(int key, int value) {
        if (map.find(key) != map.end()) {
            // Update existing
            DLLNode* node = map[key];
            node->value = value;
            moveToFront(node);
        } else {
            // Insert new
            if ((int)map.size() == capacity) {
                // Evict LRU
                DLLNode* lru = removeLRU();
                map.erase(lru->key);
                delete lru;
            }
            DLLNode* newNode = new DLLNode(key, value);
            addToFront(newNode);
            map[key] = newNode;
        }
    }

    void printState() {
        cout << "  DLL (MRU → LRU): ";
        DLLNode* curr = head->next;
        while (curr != tail) {
            cout << "[" << curr->key << ":" << curr->value << "]";
            if (curr->next != tail) cout << " ↔ ";
            curr = curr->next;
        }
        cout << "\n";
    }
};

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  LRU CACHE — THE #1 DESIGN INTERVIEW PROBLEM          ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    LRUCache cache(2);

    cout << "═══ LRU CACHE (Capacity = 2) ═══\n\n";

    cache.put(1, 1);
    cout << "put(1, 1): "; cache.printState();

    cache.put(2, 2);
    cout << "put(2, 2): "; cache.printState();

    cout << "get(1) = " << cache.get(1) << "\n";
    cout << "  After get: "; cache.printState();

    cache.put(3, 3);  // Evicts key 2
    cout << "put(3, 3) [evicts 2]: "; cache.printState();

    cout << "get(2) = " << cache.get(2) << " (evicted!)\n";

    cache.put(4, 4);  // Evicts key 1
    cout << "put(4, 4) [evicts 1]: "; cache.printState();

    cout << "get(1) = " << cache.get(1) << " (evicted!)\n";
    cout << "get(3) = " << cache.get(3) << "\n";
    cout << "  After get: "; cache.printState();
    cout << "get(4) = " << cache.get(4) << "\n";
    cout << "  After get: "; cache.printState();

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "COMPLEXITY:\n";
    cout << "  get():  O(1) time, O(1) space\n";
    cout << "  put():  O(1) time, O(capacity) space\n";
    cout << "\nKEY INSIGHT:\n";
    cout << "  DLL gives O(1) insert/delete at any position\n";
    cout << "  HashMap gives O(1) lookup by key\n";
    cout << "  Together = O(1) for everything!\n";
    cout << "\nPRACTICE: LeetCode 146\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

