/*
╔══════════════════════════════════════════════════════════════════════════════╗
║       04 — MIN COST TO CONNECT ROPES + REORGANIZE STRING                     ║
║           From Zero to Grandmaster — Priority Queue Patterns                ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Min Cost to Connect Ropes (Huffman Coding Pattern)
 2. Reorganize String (LC 767)
 3. Min Cost to Hire K Workers (LC 857)

MIN COST TO CONNECT ROPES:
─────────────────────────
  Given array of rope lengths. Connect two ropes at a time.
  Cost of connecting = sum of their lengths.
  Find minimum total cost.

  GREEDY INSIGHT: Always connect the two SHORTEST ropes first.
  Use MIN HEAP to always get the two smallest.

  DRY RUN: ropes = [4, 3, 2, 6]

  Heap: [2, 3, 4, 6]
  Step 1: connect 2+3=5,  cost=5     Heap: [4, 5, 6]
  Step 2: connect 4+5=9,  cost=5+9=14 Heap: [6, 9]
  Step 3: connect 6+9=15, cost=14+15=29 Heap: [15]

  Total cost = 29 ✅

  This is essentially HUFFMAN CODING!
  ┌───────────────────────────────────────┐
  │        [15]                           │
  │       /    \                          │
  │     [9]    [6]     cost = 5+9+15=29  │
  │    /   \                              │
  │  [4]   [5]                            │
  │        / \                            │
  │      [2] [3]                          │
  └───────────────────────────────────────┘

TIME: O(n log n)  SPACE: O(n)

REORGANIZE STRING (LC 767):
──────────────────────────
  Given string, rearrange so no two adjacent characters are same.
  Return "" if impossible.

  GREEDY + MAX HEAP: Always place the most frequent character first.
  After placing one character, temporarily hold it and place next most frequent.

  DRY RUN: "aab" → "aba" ✅
  freq: a=2, b=1
  Heap: [(2,'a'), (1,'b')]
  Pick 'a'(2), prev='a'(1→hold). Pick 'b'(1), push prev back
  Result: "ab" + 'a' → "aba"

  When is it impossible?
  If maxFreq > (n+1)/2 → impossible!
  e.g., "aaab" → a=3, len=4, (4+1)/2=2, 3>2 → impossible
*/

#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// MIN COST TO CONNECT ROPES
// ═══════════════════════════════════════════════════════════════

long long minCostConnectRopes(vector<int>& ropes) {
    priority_queue<long long, vector<long long>, greater<long long>> minH;
    for (int r : ropes) minH.push(r);

    long long totalCost = 0;
    while (minH.size() > 1) {
        long long a = minH.top(); minH.pop();
        long long b = minH.top(); minH.pop();
        long long cost = a + b;
        totalCost += cost;
        minH.push(cost);
    }
    return totalCost;
}

// ═══════════════════════════════════════════════════════════════
// REORGANIZE STRING (LC 767)
// ═══════════════════════════════════════════════════════════════

string reorganizeString(string s) {
    vector<int> freq(26, 0);
    for (char c : s) freq[c - 'a']++;

    // Check impossibility
    int maxFreq = *max_element(freq.begin(), freq.end());
    if (maxFreq > ((int)s.size() + 1) / 2) return "";

    // Max heap of (frequency, character)
    priority_queue<pair<int, char>> maxH;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) maxH.push({freq[i], 'a' + i});
    }

    string result;
    while (!maxH.empty()) {
        auto [cnt1, ch1] = maxH.top(); maxH.pop();

        // If last char is same, use second most frequent
        if (!result.empty() && result.back() == ch1) {
            if (maxH.empty()) return "";  // Can't place
            auto [cnt2, ch2] = maxH.top(); maxH.pop();
            result += ch2;
            if (cnt2 - 1 > 0) maxH.push({cnt2 - 1, ch2});
            maxH.push({cnt1, ch1});  // Put first back
        } else {
            result += ch1;
            if (cnt1 - 1 > 0) maxH.push({cnt1 - 1, ch1});
        }
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// MIN COST TO HIRE K WORKERS (LC 857) — Advanced
// ═══════════════════════════════════════════════════════════════
/*
  n workers with quality[i] and wage[i].
  Hire exactly k workers. Must pay proportionally by quality.
  Each worker paid at least their minimum wage.

  Key insight: Sort by wage/quality ratio.
  For each worker as the "captain" (highest ratio), total cost =
    ratio × sum of k smallest qualities.
  Use MAX HEAP of size k to maintain k smallest qualities.

  TIME: O(n log n)
*/

double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
    int n = quality.size();
    // Create (ratio, quality) pairs
    vector<pair<double, int>> workers;
    for (int i = 0; i < n; i++) {
        workers.push_back({(double)wage[i] / quality[i], quality[i]});
    }
    // Sort by ratio
    sort(workers.begin(), workers.end());

    priority_queue<int> maxH;  // Max heap of qualities (to remove largest)
    int qualitySum = 0;
    double minCost = 1e18;

    for (auto& [ratio, q] : workers) {
        maxH.push(q);
        qualitySum += q;

        if ((int)maxH.size() > k) {
            qualitySum -= maxH.top();
            maxH.pop();
        }

        if ((int)maxH.size() == k) {
            minCost = min(minCost, ratio * qualitySum);
        }
    }
    return minCost;
}

// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  CONNECT ROPES + REORGANIZE STRING + HIRE K WORKERS      ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Connect Ropes
    cout << "═══ MIN COST TO CONNECT ROPES ═══\n";
    vector<int> ropes = {4, 3, 2, 6};
    cout << "  Ropes: [4,3,2,6] → cost = " << minCostConnectRopes(ropes) << "\n";
    vector<int> ropes2 = {1, 2, 3, 4, 5};
    cout << "  Ropes: [1,2,3,4,5] → cost = " << minCostConnectRopes(ropes2) << "\n\n";

    // Reorganize String
    cout << "═══ REORGANIZE STRING (LC 767) ═══\n";
    cout << "  \"aab\" → \"" << reorganizeString("aab") << "\"\n";
    cout << "  \"aaab\" → \"" << reorganizeString("aaab") << "\" (impossible)\n";
    cout << "  \"vvvlo\" → \"" << reorganizeString("vvvlo") << "\"\n\n";

    // Hire K Workers
    cout << "═══ MIN COST TO HIRE K WORKERS (LC 857) ═══\n";
    vector<int> q1 = {10, 20, 5}, w1 = {70, 50, 30};
    cout << "  quality=[10,20,5], wage=[70,50,30], k=2 → ";
    cout << mincostToHireWorkers(q1, w1, 2) << "\n";

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE:\n";
    cout << "  LC 767  — Reorganize String\n";
    cout << "  LC 857  — Minimum Cost to Hire K Workers\n";
    cout << "  LC 1167 — Minimum Cost to Connect Sticks\n";
    cout << "  LC 502  — IPO (Greedy + Heap)\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

