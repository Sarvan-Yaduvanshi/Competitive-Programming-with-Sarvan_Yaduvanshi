/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — ALL ADVANCED STL TRICKS FOR CP (Combined)                   ║
║           Multiset Sliding Window, PQ Greedy, Map Frequency,               ║
║           Custom Struct Sort, Deque Monotonic Queue                        ║
║           From Zero to Grandmaster                                         ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// TRICK 1: MULTISET SLIDING WINDOW
// ═══════════════════════════════════════════════════════════════
/*
 Maintain sorted window for:
   - k-th smallest in window
   - Window median
   - Window range (max - min)
*/

void multisetSlidingWindow() {
    cout << "═══ MULTISET SLIDING WINDOW ═══\n\n";

    vector<int> arr = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;

    multiset<int> window;
    cout << "Array: "; for (int x : arr) cout << x << " "; cout << "\n";
    cout << "K = " << k << "\n\n";

    for (int i = 0; i < (int)arr.size(); i++) {
        window.insert(arr[i]);
        if (i >= k) window.erase(window.find(arr[i - k]));  // Erase ONE

        if (i >= k - 1) {
            int mn = *window.begin();
            int mx = *prev(window.end());
            auto mid = window.begin();
            advance(mid, k / 2);
            cout << "Window [" << i - k + 1 << ".." << i << "]: "
                 << "min=" << mn << " max=" << mx << " median=" << *mid
                 << " range=" << mx - mn << "\n";
        }
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// TRICK 2: PRIORITY QUEUE GREEDY — HUFFMAN-LIKE
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: Minimize cost of merging N ropes.
   Cost of merging two ropes = sum of their lengths.
   Greedy: always merge the two shortest!
*/

void pqGreedyMerge() {
    cout << "═══ PQ GREEDY: MERGE ROPES ═══\n\n";

    vector<int> ropes = {4, 3, 2, 6};
    priority_queue<int, vector<int>, greater<int>> pq(ropes.begin(), ropes.end());

    cout << "Ropes: "; for (int x : ropes) cout << x << " "; cout << "\n";

    int totalCost = 0;
    while (pq.size() > 1) {
        int a = pq.top(); pq.pop();
        int b = pq.top(); pq.pop();
        int cost = a + b;
        totalCost += cost;
        pq.push(cost);
        cout << "Merge " << a << "+" << b << "=" << cost << " (total: " << totalCost << ")\n";
    }
    cout << "Minimum total cost: " << totalCost << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// TRICK 3: CUSTOM STRUCT SORTING (Multiple keys with tie())
// ═══════════════════════════════════════════════════════════════

void customStructSort() {
    cout << "═══ CUSTOM STRUCT SORTING ═══\n\n";

    struct Event {
        int time, type; // type: 0=start, 1=end
        string name;
    };

    vector<Event> events = {
        {5, 1, "A"}, {3, 0, "B"}, {5, 0, "C"}, {3, 1, "D"}, {7, 0, "E"}
    };

    // Sort by: time ASC, then type ASC (starts before ends), then name
    sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
        return tie(a.time, a.type, a.name) < tie(b.time, b.type, b.name);
    });

    cout << "Events sorted (time, type, name):\n";
    for (auto& e : events) {
        cout << "  t=" << e.time << " " << (e.type == 0 ? "START" : "END  ")
             << " " << e.name << "\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// TRICK 4: MAP FREQUENCY TRICKS
// ═══════════════════════════════════════════════════════════════

void mapFrequencyTricks() {
    cout << "═══ MAP FREQUENCY TRICKS ═══\n\n";

    // Sliding window distinct count
    vector<int> arr = {1, 2, 1, 3, 2, 3, 4, 5, 4, 3};
    int k = 4;
    unordered_map<int, int> freq;
    int distinct = 0;

    cout << "Array: "; for (int x : arr) cout << x << " "; cout << "\n";
    cout << "K = " << k << "\n\n";

    for (int i = 0; i < (int)arr.size(); i++) {
        if (freq[arr[i]]++ == 0) distinct++;
        if (i >= k) {
            if (--freq[arr[i - k]] == 0) distinct--;
        }
        if (i >= k - 1) {
            cout << "Window [" << i - k + 1 << ".." << i << "]: "
                 << distinct << " distinct\n";
        }
    }
    cout << "\n";

    // Top-K frequency using partial_sort
    string text = "the quick brown fox jumps over the lazy dog the fox";
    istringstream iss(text);
    string word;
    map<string, int> wordFreq;
    while (iss >> word) wordFreq[word]++;

    vector<pair<int, string>> freqVec;
    for (auto& [w, c] : wordFreq) freqVec.push_back({-c, w});  // Negate for max
    sort(freqVec.begin(), freqVec.end());

    cout << "Top-3 words:\n";
    for (int i = 0; i < min(3, (int)freqVec.size()); i++) {
        cout << "  " << freqVec[i].second << ": " << -freqVec[i].first << "\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// TRICK 5: DEQUE MONOTONIC QUEUE — JUMP GAME
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: Minimum cost path, at each position can jump to next K positions.
          Cost = max element in window of size K.
          Use monotonic deque to track window minimum efficiently.
*/

void dequeMonotonicTrick() {
    cout << "═══ MONOTONIC DEQUE: SLIDING MIN ═══\n\n";

    vector<int> arr = {5, 3, 4, 2, 8, 1, 7, 6};
    int k = 3;

    deque<int> dq;
    vector<int> mins;

    cout << "Array: "; for (int x : arr) cout << x << " "; cout << "\n";
    cout << "K = " << k << "\n\n";

    for (int i = 0; i < (int)arr.size(); i++) {
        while (!dq.empty() && dq.front() <= i - k) dq.pop_front();
        while (!dq.empty() && arr[dq.back()] >= arr[i]) dq.pop_back();
        dq.push_back(i);

        if (i >= k - 1) {
            mins.push_back(arr[dq.front()]);
            cout << "Window [" << i - k + 1 << ".." << i << "]: min = "
                 << arr[dq.front()] << "\n";
        }
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    multisetSlidingWindow();
    pqGreedyMerge();
    customStructSort();
    mapFrequencyTricks();
    dequeMonotonicTrick();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. Multiset window: erase(find(x)) to remove one, maintain sorted window\n";
    cout << "2. PQ greedy: min heap to always merge smallest (Huffman-like)\n";
    cout << "3. tie() for multi-key comparison in custom sort\n";
    cout << "4. Frequency map + sliding window for distinct count\n";
    cout << "5. Monotonic deque: O(N) for sliding min/max\n";
    cout << "6. These 5 patterns cover 60%+ of medium-hard CP problems!\n";

    return 0;
}

