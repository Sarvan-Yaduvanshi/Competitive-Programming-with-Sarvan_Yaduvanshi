/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           03 — DESIGN BROWSER HISTORY, TEXT EDITOR, HASHMAP, SKIP LIST     ║
║           From Zero to Grandmaster — Design Problems with Linked Lists     ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Design Browser History (LeetCode 1472)
 2. Design HashMap using Linked List (Chaining)
 3. Implement Deque using DLL
 4. Design Skip List (Concept — LeetCode 1206)

BROWSER HISTORY:
───────────────
  Using DLL: current node tracks where we are.
  visit(url): Add new page after current, discard forward history
  back(steps): Move back min(steps, available) pages
  forward(steps): Move forward min(steps, available) pages

  DRY RUN:
    visit("google")    → [google]  (current = google)
    visit("facebook")  → [google] ↔ [facebook]  (current = facebook)
    visit("youtube")   → [google] ↔ [facebook] ↔ [youtube]
    back(1)            → current = facebook
    back(1)            → current = google
    forward(1)         → current = facebook
    visit("linkedin")  → [google] ↔ [facebook] ↔ [linkedin]
                         (youtube removed — forward history cleared!)
*/

#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// 1. DESIGN BROWSER HISTORY — Using DLL
// ═══════════════════════════════════════════════════════════════

class BrowserHistory {
    struct Page {
        string url;
        Page* prev;
        Page* next;
        Page(string u) : url(u), prev(nullptr), next(nullptr) {}
    };

    Page* current;

    void clearForward(Page* node) {
        while (node) {
            Page* next = node->next;
            delete node;
            node = next;
        }
    }

public:
    BrowserHistory(string homepage) {
        current = new Page(homepage);
    }

    ~BrowserHistory() {
        // Go to beginning
        while (current->prev) current = current->prev;
        clearForward(current);
    }

    void visit(string url) {
        // Clear forward history
        clearForward(current->next);

        Page* newPage = new Page(url);
        current->next = newPage;
        newPage->prev = current;
        current = newPage;
    }

    string back(int steps) {
        while (steps > 0 && current->prev) {
            current = current->prev;
            steps--;
        }
        return current->url;
    }

    string forward(int steps) {
        while (steps > 0 && current->next) {
            current = current->next;
            steps--;
        }
        return current->url;
    }

    string getCurrent() { return current->url; }
};

// ═══════════════════════════════════════════════════════════════
// 2. DESIGN HASHMAP USING LINKED LIST (Chaining)
// ═══════════════════════════════════════════════════════════════
/*
  Hash Table with Separate Chaining:

  Bucket Array:
  ┌────┐
  │ 0  │ → [key=10, val=A] → [key=20, val=B] → NULL
  ├────┤
  │ 1  │ → [key=1, val=C] → NULL
  ├────┤
  │ 2  │ → NULL (empty bucket)
  ├────┤
  │ 3  │ → [key=3, val=D] → [key=13, val=E] → NULL
  └────┘

  Hash function: h(key) = key % tableSize
  Collision resolution: Linked list chaining
*/

class MyHashMap {
    static const int SIZE = 1000;

    struct HNode {
        int key, value;
        HNode* next;
        HNode(int k, int v) : key(k), value(v), next(nullptr) {}
    };

    HNode* buckets[SIZE];

    int hash(int key) { return key % SIZE; }

public:
    MyHashMap() {
        for (int i = 0; i < SIZE; i++) buckets[i] = nullptr;
    }

    ~MyHashMap() {
        for (int i = 0; i < SIZE; i++) {
            HNode* curr = buckets[i];
            while (curr) {
                HNode* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
    }

    void put(int key, int value) {
        int idx = hash(key);
        HNode* curr = buckets[idx];

        // Check if key exists
        while (curr) {
            if (curr->key == key) {
                curr->value = value;
                return;
            }
            curr = curr->next;
        }

        // Insert at head of chain
        HNode* newNode = new HNode(key, value);
        newNode->next = buckets[idx];
        buckets[idx] = newNode;
    }

    int get(int key) {
        int idx = hash(key);
        HNode* curr = buckets[idx];
        while (curr) {
            if (curr->key == key) return curr->value;
            curr = curr->next;
        }
        return -1;
    }

    void remove(int key) {
        int idx = hash(key);
        HNode dummy(0, 0);
        dummy.next = buckets[idx];
        HNode* prev = &dummy;

        while (prev->next) {
            if (prev->next->key == key) {
                HNode* temp = prev->next;
                prev->next = temp->next;
                delete temp;
                buckets[idx] = dummy.next;
                return;
            }
            prev = prev->next;
        }
    }
};

// ═══════════════════════════════════════════════════════════════
// 3. DEQUE USING DOUBLY LINKED LIST
// ═══════════════════════════════════════════════════════════════

class MyDeque {
    struct DNode {
        int data;
        DNode* prev;
        DNode* next;
        DNode(int val) : data(val), prev(nullptr), next(nullptr) {}
    };

    DNode* head;
    DNode* tail;
    int sz;

public:
    MyDeque() : head(nullptr), tail(nullptr), sz(0) {}

    ~MyDeque() {
        while (head) { DNode* t = head; head = head->next; delete t; }
    }

    void pushFront(int val) {
        DNode* node = new DNode(val);
        if (!head) { head = tail = node; }
        else { node->next = head; head->prev = node; head = node; }
        sz++;
    }

    void pushBack(int val) {
        DNode* node = new DNode(val);
        if (!tail) { head = tail = node; }
        else { node->prev = tail; tail->next = node; tail = node; }
        sz++;
    }

    int popFront() {
        if (!head) return -1;
        int val = head->data;
        DNode* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        sz--;
        return val;
    }

    int popBack() {
        if (!tail) return -1;
        int val = tail->data;
        DNode* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        sz--;
        return val;
    }

    int front() { return head ? head->data : -1; }
    int back() { return tail ? tail->data : -1; }
    int size() { return sz; }
    bool empty() { return sz == 0; }

    void print() {
        DNode* curr = head;
        cout << "Deque: [";
        while (curr) {
            cout << curr->data;
            if (curr->next) cout << ", ";
            curr = curr->next;
        }
        cout << "]\n";
    }
};

// ═══════════════════════════════════════════════════════════════
// 4. SKIP LIST CONCEPT
// ═══════════════════════════════════════════════════════════════
/*
  SKIP LIST — Probabilistic data structure for O(log n) search/insert/delete

  Level 3:  HEAD ─────────────────────────── 6 ──────── NIL
  Level 2:  HEAD ───── 3 ──────────────── 6 ───── 9 ── NIL
  Level 1:  HEAD ── 2 ─ 3 ── 5 ── 6 ── 7 ── 9 ── NIL
  Level 0:  HEAD ─ 1 ─ 2 ─ 3 ─ 4 ─ 5 ─ 6 ─ 7 ─ 8 ─ 9 ─ NIL

  Each node has multiple levels (randomly chosen).
  Higher levels act as "express lanes" for faster search.

  Search for 7:
    Start at Level 3: HEAD → 6 (6 < 7, move right) → NIL (overshoot, go down)
    Level 2: 6 → 9 (9 > 7, go down)
    Level 1: 6 → 7 ← FOUND! ✅

  Expected time: O(log n) for all operations
  Space: O(n) expected

  Used in: Redis (sorted sets), LevelDB, MemSQL

  See LeetCode 1206 for full implementation.
*/

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  DESIGN: BROWSER HISTORY, HASHMAP, DEQUE, SKIP LIST    ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Browser History
    cout << "═══ BROWSER HISTORY ═══\n";
    BrowserHistory browser("google.com");
    browser.visit("facebook.com");
    browser.visit("youtube.com");
    cout << "Current: " << browser.getCurrent() << "\n";
    cout << "Back 1: " << browser.back(1) << "\n";
    cout << "Back 1: " << browser.back(1) << "\n";
    cout << "Forward 1: " << browser.forward(1) << "\n";
    browser.visit("linkedin.com");
    cout << "Visit linkedin, Forward 2: " << browser.forward(2) << " (youtube cleared!)\n";
    cout << "Back 2: " << browser.back(2) << "\n";

    // HashMap
    cout << "\n═══ HASHMAP (Chaining) ═══\n";
    MyHashMap hashMap;
    hashMap.put(1, 100);
    hashMap.put(2, 200);
    hashMap.put(1001, 300);  // Same bucket as 1 (1001 % 1000 = 1)
    cout << "get(1) = " << hashMap.get(1) << "\n";
    cout << "get(2) = " << hashMap.get(2) << "\n";
    cout << "get(1001) = " << hashMap.get(1001) << " (collision with key 1!)\n";
    hashMap.remove(1);
    cout << "After remove(1): get(1) = " << hashMap.get(1) << "\n";
    cout << "get(1001) still = " << hashMap.get(1001) << "\n";

    // Deque
    cout << "\n═══ DEQUE USING DLL ═══\n";
    MyDeque dq;
    dq.pushBack(1);
    dq.pushBack(2);
    dq.pushFront(0);
    dq.pushBack(3);
    dq.print();
    cout << "Front: " << dq.front() << ", Back: " << dq.back() << "\n";
    cout << "Pop front: " << dq.popFront() << "\n";
    cout << "Pop back: " << dq.popBack() << "\n";
    dq.print();

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE: LeetCode 1472, 706, 1206\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

