/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           03 — LRU CACHE (LC 146) & LFU CACHE (LC 460)                      ║
║           From Zero to Grandmaster — Stack & Queue Design Problems          ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

LRU CACHE (Least Recently Used):
────────────────────────────────
  Eviction policy: When full, remove the LEAST RECENTLY USED entry.

  Data Structures: HashMap + Doubly Linked List
    HashMap: key → DLL node pointer (O(1) lookup)
    DLL: most recent at head, least recent at tail

  get(key):  O(1) — look up in map, move node to head
  put(key,val): O(1) — insert at head, evict from tail if full

DRY RUN (capacity=2):
  put(1,1): DLL: [1:1]             map: {1→node}
  put(2,2): DLL: [2:2]↔[1:1]       map: {1,2}
  get(1):   move 1 to head          DLL: [1:1]↔[2:2]  returns 1
  put(3,3): full! evict tail (2)    DLL: [3:3]↔[1:1]  map: {1,3}
  get(2):   not found → returns -1
  put(4,4): full! evict tail (1)    DLL: [4:4]↔[3:3]  map: {3,4}
  get(1):   not found → -1
  get(3):   move 3 to head          DLL: [3:3]↔[4:4]  returns 3

  ┌──────────────────────────────────────────────────────┐
  │  HashMap: key → Node*                                │
  │  DLL: HEAD ↔ [3:3] ↔ [4:4] ↔ TAIL                  │
  │        ↑                        ↑                    │
  │   Most Recent              Least Recent (evict)     │
  └──────────────────────────────────────────────────────┘

LFU CACHE (Least Frequently Used):
──────────────────────────────────
  Eviction: Remove least frequently used. Tie → remove least recently used.
  More complex: needs frequency tracking + order within same frequency.
*/

#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// LRU CACHE (LC 146)
// ═══════════════════════════════════════════════════════════════

class LRUCache {
    int capacity;
    list<pair<int,int>> dll;  // (key, value), front = most recent
    unordered_map<int, list<pair<int,int>>::iterator> cache;

public:
    LRUCache(int cap) : capacity(cap) {}

    int get(int key) {
        if (cache.find(key) == cache.end()) return -1;

        // Move to front (most recently used)
        dll.splice(dll.begin(), dll, cache[key]);
        return cache[key]->second;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            // Update existing
            cache[key]->second = value;
            dll.splice(dll.begin(), dll, cache[key]);
            return;
        }

        if ((int)dll.size() >= capacity) {
            // Evict LRU (tail)
            int evictKey = dll.back().first;
            cache.erase(evictKey);
            dll.pop_back();
        }

        dll.push_front({key, value});
        cache[key] = dll.begin();
    }
};

// ═══════════════════════════════════════════════════════════════
// LFU CACHE (LC 460)
// ═══════════════════════════════════════════════════════════════

class LFUCache {
    int capacity, minFreq;
    unordered_map<int, pair<int,int>> keyVal;       // key → (value, freq)
    unordered_map<int, list<int>> freqList;          // freq → list of keys (LRU order)
    unordered_map<int, list<int>::iterator> keyIter; // key → iterator in freqList

    void touch(int key) {
        int freq = keyVal[key].second;
        keyVal[key].second++;

        // Remove from current frequency list
        freqList[freq].erase(keyIter[key]);
        if (freqList[freq].empty()) {
            freqList.erase(freq);
            if (minFreq == freq) minFreq++;
        }

        // Add to new frequency list (front = most recent)
        int newFreq = freq + 1;
        freqList[newFreq].push_front(key);
        keyIter[key] = freqList[newFreq].begin();
    }

public:
    LFUCache(int cap) : capacity(cap), minFreq(0) {}

    int get(int key) {
        if (keyVal.find(key) == keyVal.end()) return -1;
        touch(key);
        return keyVal[key].first;
    }

    void put(int key, int value) {
        if (capacity <= 0) return;

        if (keyVal.find(key) != keyVal.end()) {
            keyVal[key].first = value;
            touch(key);
            return;
        }

        if ((int)keyVal.size() >= capacity) {
            // Evict LFU (back of minFreq list)
            int evictKey = freqList[minFreq].back();
            freqList[minFreq].pop_back();
            if (freqList[minFreq].empty()) freqList.erase(minFreq);
            keyVal.erase(evictKey);
            keyIter.erase(evictKey);
        }

        keyVal[key] = {value, 1};
        freqList[1].push_front(key);
        keyIter[key] = freqList[1].begin();
        minFreq = 1;
    }
};

// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  LRU CACHE (LC 146) & LFU CACHE (LC 460)                ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // LRU Cache
    cout << "═══ LRU CACHE (capacity=2) ═══\n";
    LRUCache lru(2);
    lru.put(1, 1);
    lru.put(2, 2);
    cout << "  get(1): " << lru.get(1) << "\n";    // 1
    lru.put(3, 3);                                   // evicts key 2
    cout << "  get(2): " << lru.get(2) << "\n";    // -1
    lru.put(4, 4);                                   // evicts key 1
    cout << "  get(1): " << lru.get(1) << "\n";    // -1
    cout << "  get(3): " << lru.get(3) << "\n";    // 3
    cout << "  get(4): " << lru.get(4) << "\n\n";  // 4

    // LFU Cache
    cout << "═══ LFU CACHE (capacity=2) ═══\n";
    LFUCache lfu(2);
    lfu.put(1, 1);
    lfu.put(2, 2);
    cout << "  get(1): " << lfu.get(1) << "\n";    // 1 (freq of 1 is now 2)
    lfu.put(3, 3);                                   // evicts key 2 (freq=1, LFU)
    cout << "  get(2): " << lfu.get(2) << "\n";    // -1
    cout << "  get(3): " << lfu.get(3) << "\n";    // 3
    lfu.put(4, 4);                                   // evicts key 3 (freq=2 vs 1→evict 3 with freq 2? No, 3 has freq 2, 1 has freq 2... evict LRU among freq 2)
    cout << "  get(1): " << lfu.get(1) << "\n";    // 1
    cout << "  get(3): " << lfu.get(3) << "\n";    // -1
    cout << "  get(4): " << lfu.get(4) << "\n";    // 4

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "KEY INSIGHTS:\n";
    cout << "  LRU: HashMap + DLL → O(1) get/put\n";
    cout << "  LFU: HashMap + FreqMap + DLL per freq → O(1) get/put\n";
    cout << "  Both are TOP FAANG interview questions!\n\n";
    cout << "PRACTICE: LC 146 (LRU), LC 460 (LFU)\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

