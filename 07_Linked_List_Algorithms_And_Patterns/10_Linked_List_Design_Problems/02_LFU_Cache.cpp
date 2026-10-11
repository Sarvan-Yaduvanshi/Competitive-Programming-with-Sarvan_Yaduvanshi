/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — LFU CACHE (LeetCode 460 — Hard)                             ║
║           From Zero to Grandmaster — Advanced Design Problem               ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Problem Description
 2. Data Structure Design (Two HashMaps + Multiple DLLs)
 3. Complete Implementation
 4. Dry Run

LFU CACHE = Least Frequently Used Cache
─────────────────────────────────────────
  Like LRU, but evicts the LEAST FREQUENTLY used item.
  If tie in frequency → evict the LEAST RECENTLY used among them.

  Data Structures:
  ┌──────────────────────────────────────────────────────────┐
  │ keyMap: key → {value, freq, iterator}                    │
  │ freqMap: freq → DLL of keys with that frequency          │
  │ minFreq: tracks the current minimum frequency            │
  │                                                          │
  │ freqMap[1]: [key5] ↔ [key3]    (used 1 time)            │
  │ freqMap[2]: [key1] ↔ [key4]    (used 2 times)           │
  │ freqMap[3]: [key2]             (used 3 times)            │
  │                                                          │
  │ minFreq = 1 (evict from freqMap[1] tail = key3)         │
  └──────────────────────────────────────────────────────────┘

DRY RUN — Capacity = 2:
───────────────────────
  put(1, 1): keyMap:{1→(1,f=1)}, freqMap:{1:[1]}, minFreq=1
  put(2, 2): keyMap:{1→(1,f=1), 2→(2,f=1)}, freqMap:{1:[2,1]}, minFreq=1
  get(1):    freq of 1 becomes 2. freqMap:{1:[2], 2:[1]}, minFreq=1
             Returns 1
  put(3, 3): Full! Evict LFU. minFreq=1, evict tail of freqMap[1] → key 2
             keyMap:{1→(1,f=2), 3→(3,f=1)}, freqMap:{1:[3], 2:[1]}, minFreq=1
  get(2):    Not found → Returns -1
  get(3):    freq of 3 becomes 2. freqMap:{2:[3,1]}, minFreq=2
             Returns 3
  put(4, 4): Full! Evict LFU. minFreq=2, evict tail of freqMap[2] → key 1
             keyMap:{3→(3,f=2), 4→(4,f=1)}, freqMap:{1:[4], 2:[3]}, minFreq=1
*/

#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// LFU CACHE — O(1) get, O(1) put
// ═══════════════════════════════════════════════════════════════

class LFUCache {
private:
    int capacity, minFreq;

    // key → {value, frequency}
    unordered_map<int, pair<int, int>> keyVal;

    // key → iterator in frequency list (for O(1) removal)
    unordered_map<int, list<int>::iterator> keyIter;

    // frequency → list of keys with that frequency (MRU at front)
    unordered_map<int, list<int>> freqList;

    void touch(int key) {
        int freq = keyVal[key].second;

        // Remove from current frequency list
        freqList[freq].erase(keyIter[key]);
        if (freqList[freq].empty()) {
            freqList.erase(freq);
            if (minFreq == freq) minFreq++;
        }

        // Increment frequency and add to new list
        keyVal[key].second++;
        freqList[freq + 1].push_front(key);
        keyIter[key] = freqList[freq + 1].begin();
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

        if ((int)keyVal.size() == capacity) {
            // Evict LFU (and LRU among LFU — back of minFreq list)
            int evictKey = freqList[minFreq].back();
            freqList[minFreq].pop_back();
            if (freqList[minFreq].empty()) freqList.erase(minFreq);
            keyVal.erase(evictKey);
            keyIter.erase(evictKey);
        }

        // Insert new key with frequency 1
        keyVal[key] = {value, 1};
        freqList[1].push_front(key);
        keyIter[key] = freqList[1].begin();
        minFreq = 1;
    }

    void printState() {
        cout << "  Keys: ";
        for (auto& [k, vf] : keyVal) {
            cout << "[" << k << ":" << vf.first << " f=" << vf.second << "] ";
        }
        cout << " minFreq=" << minFreq << "\n";
    }
};

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  LFU CACHE — ADVANCED DESIGN PROBLEM                   ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    LFUCache cache(2);

    cout << "═══ LFU CACHE (Capacity = 2) ═══\n\n";

    cache.put(1, 1);
    cout << "put(1,1): "; cache.printState();

    cache.put(2, 2);
    cout << "put(2,2): "; cache.printState();

    cout << "get(1) = " << cache.get(1) << "\n";
    cout << "  After: "; cache.printState();

    cache.put(3, 3);  // Evicts key 2 (freq=1, LRU among freq=1)
    cout << "put(3,3) [evicts 2]: "; cache.printState();

    cout << "get(2) = " << cache.get(2) << " (evicted!)\n";
    cout << "get(3) = " << cache.get(3) << "\n";
    cout << "  After: "; cache.printState();

    cache.put(4, 4);  // Evicts key 1 is freq=2, key 3 is freq=2, LRU is 1
    cout << "put(4,4) [evicts LFU]: "; cache.printState();

    cout << "get(1) = " << cache.get(1) << " (evicted!)\n";
    cout << "get(3) = " << cache.get(3) << "\n";
    cout << "get(4) = " << cache.get(4) << "\n";

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "LRU vs LFU:\n";
    cout << "  LRU: Evicts least RECENTLY used    → simpler\n";
    cout << "  LFU: Evicts least FREQUENTLY used   → smarter\n";
    cout << "  LFU tie-breaker: evict least recently used among LFU\n";
    cout << "\nPRACTICE: LeetCode 460\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

