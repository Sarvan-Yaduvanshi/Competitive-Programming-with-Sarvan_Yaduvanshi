/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Greedy Future Simulation — Belady's Algorithm
 *  Level   : Grandmaster
 * ============================================================================
 *
 *  ▶ BELADY'S ALGORITHM (Optimal Page Replacement):
 *  ─────────────────────────────────────────────────
 *  Given a sequence of page requests and a cache of size k:
 *  When cache is full and a new page arrives → EVICT the page that will
 *  be used FARTHEST in the future (or never used again).
 *
 *  This is OPTIMAL (provable by exchange argument) but requires future knowledge!
 *  Used as a benchmark for online page replacement algorithms (LRU, FIFO, etc.)
 *
 *  ▶ IN COMPETITIVE PROGRAMMING:
 *  This pattern appears when you can simulate the optimal strategy because
 *  the full input is known (offline problem).
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <queue>
using namespace std;

// ============================================================================
// Belady's Algorithm — Optimal Page Replacement
// Returns number of page faults
// ============================================================================
int beladyPageFaults(vector<int>& pages, int cacheSize) {
    int n = pages.size();

    // Precompute next occurrence of each page
    // nextUse[i] = next index after i where pages[i] appears
    unordered_map<int, queue<int>> futureUse;
    for (int i = 0; i < n; i++) {
        futureUse[pages[i]].push(i);
    }

    set<pair<int,int>> cache; // {-next_use, page} → max-heap by next_use
    unordered_map<int, int> inCache; // page → next_use (for fast lookup)
    int faults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        futureUse[page].pop(); // Remove current occurrence

        int nextUse = futureUse[page].empty() ? n + 1 : futureUse[page].front();

        if (inCache.count(page)) {
            // Page is in cache, update its next use
            cache.erase({-inCache[page], page});
            cache.insert({-nextUse, page});
            inCache[page] = nextUse;
        } else {
            faults++;
            if ((int)cache.size() >= cacheSize) {
                // Evict page with farthest next use (most negative first in our set)
                auto evict = cache.begin(); // Smallest = most negative = farthest future
                inCache.erase(evict->second);
                cache.erase(evict);
            }
            cache.insert({-nextUse, page});
            inCache[page] = nextUse;
        }
    }
    return faults;
}

int main() {
    vector<int> pages = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int cacheSize = 3;
    cout << "Belady page faults: " << beladyPageFaults(pages, cacheSize) << endl;
    // Optimal: fewer faults than LRU or FIFO

    return 0;
}

