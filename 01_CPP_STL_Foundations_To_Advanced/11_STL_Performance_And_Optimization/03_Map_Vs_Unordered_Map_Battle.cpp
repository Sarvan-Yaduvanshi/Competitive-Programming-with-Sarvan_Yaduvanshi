/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           03 — MAP vs UNORDERED_MAP — THE DEFINITIVE BATTLE                ║
║           From Zero to Grandmaster — When Each One Wins                    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Internal Structure Comparison (BST vs Hash Table)
 2. Benchmark: Integer Keys
 3. Benchmark: String Keys
 4. When map Wins (order, safety, lower_bound)
 5. When unordered_map Wins (speed)
 6. The Decision Matrix

═══════════════════════════════════════════════════════════════════════════════
 INTERNAL STRUCTURE
═══════════════════════════════════════════════════════════════════════════════

 MAP (Red-Black Tree):
 ─────────────────────
         (30)                Keys are SORTED
        /    \               Insert/Find = O(log n) — always
      (10)   (40)            Memory: node = key + value + 3 pointers + color
      / \      \             Cache: BAD (pointer chasing through tree)
    (5) (20)  (50)

 UNORDERED_MAP (Hash Table):
 ──────────────────────────
   Bucket 0: → [key1, val1] → [key2, val2]    (chaining)
   Bucket 1: → [key3, val3]
   Bucket 2: (empty)
   Bucket 3: → [key4, val4] → [key5, val5] → [key6, val6]  (chain!)

   Find = O(1) average, O(n) worst (all in one bucket!)
   Memory: hash table + buckets + chains
   Cache: MODERATE (hash computation + bucket access)
*/

#include <bits/stdc++.h>
using namespace std;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

// ═══════════════════════════════════════════════════════════════
// SECTION 1: INTEGER KEY BENCHMARKS
// ═══════════════════════════════════════════════════════════════

void benchmarkIntKeys() {
    cout << "═══ INTEGER KEY BENCHMARK ═══\n\n";

    const int N = 1000000;

    // map
    {
        map<int, int> m;
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < N; i++) m[i] = i;
        auto t_ins = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();

        start = chrono::steady_clock::now();
        long long sum = 0;
        for (int i = 0; i < N; i++) sum += m[i];
        auto t_find = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();

        cout << "map<int,int> (10^6):\n";
        cout << "  Insert: " << t_ins << " ms,  Find: " << t_find << " ms\n";
    }

    // unordered_map (default hash, no reserve)
    {
        unordered_map<int, int> m;
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < N; i++) m[i] = i;
        auto t_ins = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();

        start = chrono::steady_clock::now();
        long long sum = 0;
        for (int i = 0; i < N; i++) sum += m[i];
        auto t_find = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();

        cout << "unordered_map (no reserve, default hash):\n";
        cout << "  Insert: " << t_ins << " ms,  Find: " << t_find << " ms\n";
    }

    // unordered_map (reserve + custom hash) — THE GM WAY
    {
        unordered_map<int, int, custom_hash> m;
        m.reserve(N);
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < N; i++) m[i] = i;
        auto t_ins = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();

        start = chrono::steady_clock::now();
        long long sum = 0;
        for (int i = 0; i < N; i++) sum += m[i];
        auto t_find = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();

        cout << "unordered_map (reserve + custom hash):\n";
        cout << "  Insert: " << t_ins << " ms,  Find: " << t_find << " ms\n\n";
    }
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: STRING KEY BENCHMARKS
// ═══════════════════════════════════════════════════════════════
/*
 String keys are ESPECIALLY interesting:
   map<string>:     comparison = O(|s|), tree traversal = O(log n)
                     Total per op = O(|s| × log n)
   unordered_map:   hash = O(|s|), then O(1) lookup
                     Total per op = O(|s|)

   For long strings, unordered_map wins BIG.
*/

void benchmarkStringKeys() {
    cout << "═══ STRING KEY BENCHMARK ═══\n\n";

    const int N = 200000;
    vector<string> keys(N);
    for (int i = 0; i < N; i++) keys[i] = "key_" + to_string(i) + "_value";

    // map
    {
        map<string, int> m;
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < N; i++) m[keys[i]] = i;
        auto t_ins = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();

        start = chrono::steady_clock::now();
        long long sum = 0;
        for (int i = 0; i < N; i++) sum += m[keys[i]];
        auto t_find = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();

        cout << "map<string,int> (2×10^5):\n";
        cout << "  Insert: " << t_ins << " ms,  Find: " << t_find << " ms\n";
    }

    // unordered_map
    {
        unordered_map<string, int> m;
        m.reserve(N);
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < N; i++) m[keys[i]] = i;
        auto t_ins = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();

        start = chrono::steady_clock::now();
        long long sum = 0;
        for (int i = 0; i < N; i++) sum += m[keys[i]];
        auto t_find = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();

        cout << "unordered_map<string,int> (2×10^5, reserve):\n";
        cout << "  Insert: " << t_ins << " ms,  Find: " << t_find << " ms\n\n";
    }

    cout << "String keys: unordered_map saves the O(log n) comparisons!\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: WHEN MAP WINS
// ═══════════════════════════════════════════════════════════════

void whenMapWins() {
    cout << "═══ WHEN map WINS ═══\n\n";

    // Case 1: You need sorted iteration
    cout << "CASE 1: Sorted output needed\n";
    map<string, int> freq;
    for (auto& w : vector<string>{"banana", "apple", "cherry", "apple", "banana", "apple"})
        freq[w]++;
    cout << "  Frequency (auto-sorted by key):\n";
    for (auto& [word, cnt] : freq)
        cout << "    " << word << ": " << cnt << "\n";
    cout << "\n";

    // Case 2: lower_bound / upper_bound
    cout << "CASE 2: Range queries with lower_bound\n";
    map<int, string> scores = {{90, "A"}, {80, "B"}, {70, "C"}, {60, "D"}};
    int query = 75;
    auto it = scores.lower_bound(query);
    if (it != scores.end())
        cout << "  Score >= " << query << ": " << it->first << " (" << it->second << ")\n";
    cout << "  (unordered_map has NO lower_bound!)\n\n";

    // Case 3: Anti-hack safety
    cout << "CASE 3: CF contest safety\n";
    cout << "  map is ALWAYS O(log n) — nobody can hack it\n";
    cout << "  unordered_map is O(n) worst case — hackers WILL exploit it\n";
    cout << "  If you forget custom hash → potential TLE from hacks!\n\n";

    // Case 4: Small N
    cout << "CASE 4: N ≤ 10^3 — doesn't matter which you use\n";
    cout << "  For small N, the constant factor difference is negligible.\n";
    cout << "  Use map for cleaner sorted output.\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: DECISION MATRIX
// ═══════════════════════════════════════════════════════════════

void printDecisionMatrix() {
    cout << "═══ THE DECISION MATRIX ═══\n\n";

    cout << "┌──────────────────────────┬──────────────────┬──────────────────────┐\n";
    cout << "│ Situation                │ Use              │ Reason               │\n";
    cout << "├──────────────────────────┼──────────────────┼──────────────────────┤\n";
    cout << "│ Need sorted keys         │ map              │ Auto-sorted BST      │\n";
    cout << "│ Need lower_bound         │ map              │ unordered has none    │\n";
    cout << "│ Need predecessor/succ    │ map              │ BST traversal        │\n";
    cout << "│ N ≤ 10^3                 │ Either           │ No perf difference   │\n";
    cout << "│ N ≈ 10^5-10^6, pure find │ unordered_map    │ O(1) avg vs O(logn)  │\n";
    cout << "│ String keys              │ unordered_map    │ Saves O(logn) comps  │\n";
    cout << "│ CF contest, worried hack │ map              │ 100%% safe O(logn)   │\n";
    cout << "│ CF + fast                │ unordered+custom │ O(1) + unhackable    │\n";
    cout << "│ Need ordered iteration   │ map              │ Keys auto-sorted     │\n";
    cout << "│ Frequency counting       │ unordered_map    │ Fastest for pure cnt │\n";
    cout << "│ Two-sum / subarray sum   │ unordered_map    │ O(1) lookup critical │\n";
    cout << "│ Coordinate compression   │ map (or sort)    │ Need sorted mapping  │\n";
    cout << "└──────────────────────────┴──────────────────┴──────────────────────┘\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: LIVE DEMO — SAME PROBLEM, BOTH WAYS
// ═══════════════════════════════════════════════════════════════

void sameProbleBothWays() {
    cout << "═══ SAME PROBLEM, BOTH WAYS ═══\n\n";

    // Problem: Count distinct elements in subarrays of size K
    vector<int> arr = {1, 2, 1, 3, 2, 3, 4, 5, 4, 3, 2, 1};
    int K = 4;

    cout << "Array: "; for (int x : arr) cout << x << " "; cout << "\n";
    cout << "K = " << K << "\n\n";

    // With map (sorted, but slower)
    {
        map<int, int> freq;
        cout << "Using map:\n";
        for (int i = 0; i < (int)arr.size(); i++) {
            freq[arr[i]]++;
            if (i >= K) { if (--freq[arr[i - K]] == 0) freq.erase(arr[i - K]); }
            if (i >= K - 1)
                cout << "  Window [" << i-K+1 << ".." << i << "]: " << freq.size() << " distinct\n";
        }
    }
    cout << "\n";

    // With unordered_map (faster, unordered)
    {
        unordered_map<int, int> freq;
        cout << "Using unordered_map:\n";
        for (int i = 0; i < (int)arr.size(); i++) {
            freq[arr[i]]++;
            if (i >= K) { if (--freq[arr[i - K]] == 0) freq.erase(arr[i - K]); }
            if (i >= K - 1)
                cout << "  Window [" << i-K+1 << ".." << i << "]: " << freq.size() << " distinct\n";
        }
    }
    cout << "\n";
    cout << "Same result! unordered is faster, map is safer.\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    benchmarkIntKeys();
    benchmarkStringKeys();
    whenMapWins();
    printDecisionMatrix();
    sameProbleBothWays();

    cout << "═══ GM VERDICT ═══\n";
    cout << "1. Default choice: unordered_map + custom_hash + reserve()\n";
    cout << "2. Need order/lower_bound → map, no exception\n";
    cout << "3. CF contest, no custom hash memorized → just use map\n";
    cout << "4. String keys → unordered wins big (saves O(logn) comparisons)\n";
    cout << "5. N ≤ 10^3 → use whatever is cleaner\n";
    cout << "6. NEVER use default unordered_map on CF without custom hash\n";

    return 0;
}

