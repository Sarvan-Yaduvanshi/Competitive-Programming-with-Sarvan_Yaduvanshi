/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           04 — TIME COMPLEXITY BASICS FOR STL                              ║
║           From Zero to Grandmaster — Know Your Costs                       ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Big-O Notation Refresher
 2. Time Complexity of ALL STL Containers
 3. Time Complexity of Common STL Algorithms
 4. How to Estimate TLE
 5. Practical Benchmarking

CORE IDEA:
──────────
  Knowing time complexity lets you PREDICT if your solution will pass.
  Rule of thumb: ~10^8 operations per second in competitive programming.

  N = 10^5 → O(N^2) = 10^10 → TLE!
  N = 10^5 → O(N log N) = ~1.7 × 10^6 → Fast!

GM TIP: Before coding, ALWAYS estimate the complexity first.
        If it's > 10^8, don't even start coding — find a better approach.
*/

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <chrono>
#include <queue>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: BIG-O REFRESHER
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Big-O measures how runtime grows with input size N.

 COMMON COMPLEXITIES (fastest to slowest):
 ┌──────────────┬──────────────┬──────────────┬────────────────────────────┐
 │ Complexity   │ N=10^5       │ N=10^6       │ Examples                   │
 ├──────────────┼──────────────┼──────────────┼────────────────────────────┤
 │ O(1)         │ 1            │ 1            │ Array access, hash lookup  │
 │ O(log N)     │ 17           │ 20           │ Binary search, set.find()  │
 │ O(√N)        │ 316          │ 1000         │ Factorization, sqrt decomp │
 │ O(N)         │ 10^5         │ 10^6         │ Linear scan, accumulate    │
 │ O(N log N)   │ 1.7 × 10^6  │ 2 × 10^7    │ sort(), building BST       │
 │ O(N²)        │ 10^10 ❌     │ 10^12 ❌     │ Nested loops, bubble sort  │
 │ O(N³)        │ 10^15 ❌     │ 10^18 ❌     │ Floyd-Warshall             │
 │ O(2^N)       │ 10^30000 ❌  │ ∞ ❌          │ Subset enumeration         │
 └──────────────┴──────────────┴──────────────┴────────────────────────────┘

 RULE: For 1 second time limit:
   N ≤ 10 → O(N!) ok          N ≤ 20 → O(2^N) ok
   N ≤ 500 → O(N³) ok         N ≤ 5000 → O(N²) ok
   N ≤ 10^6 → O(N log N) ok   N ≤ 10^8 → O(N) ok
*/

// ═══════════════════════════════════════════════════════════════
// SECTION 2: STL CONTAINER COMPLEXITY TABLE
// ═══════════════════════════════════════════════════════════════
/*
 COMPLETE COMPLEXITY REFERENCE:
 ──────────────────────────────

 ┌──────────────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
 │ VECTOR           │ Access   │ PushBack │ Insert   │ Erase    │ Find     │
 │                  │ O(1)     │ O(1)*    │ O(N)     │ O(N)     │ O(N)     │
 ├──────────────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
 │ DEQUE            │ O(1)     │ O(1)*    │ O(N)     │ O(N)     │ O(N)     │
 │                  │          │front too │          │          │          │
 ├──────────────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
 │ LIST             │ O(N)     │ O(1)     │ O(1)**   │ O(1)**   │ O(N)     │
 ├──────────────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
 │ SET / MULTISET   │ -        │ O(logN)  │ O(logN)  │ O(logN)  │ O(logN)  │
 ├──────────────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
 │ MAP / MULTIMAP   │ O(logN)  │ O(logN)  │ O(logN)  │ O(logN)  │ O(logN)  │
 ├──────────────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
 │ UNORDERED_SET    │ -        │ O(1)avg  │ O(1)avg  │ O(1)avg  │ O(1)avg  │
 │                  │          │ O(N)wrst │ O(N)wrst │ O(N)wrst │ O(N)wrst │
 ├──────────────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
 │ UNORDERED_MAP    │ O(1)avg  │ O(1)avg  │ O(1)avg  │ O(1)avg  │ O(1)avg  │
 ├──────────────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
 │ PRIORITY_QUEUE   │ O(1)top  │ O(logN)  │ -        │ O(logN)  │ -        │
 ├──────────────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
 │ STACK / QUEUE    │ O(1)     │ O(1)     │ -        │ O(1)     │ -        │
 └──────────────────┴──────────┴──────────┴──────────┴──────────┴──────────┘

 * = amortized (usually O(1), occasionally O(N) when reallocation happens)
 ** = O(1) if you HAVE the iterator; O(N) to find the position first

 CRITICAL CP INSIGHT:
   unordered_map worst case is O(N) per operation!
   Hackers on Codeforces can ATTACK your hash function.
   Use custom hash or switch to map if you suspect anti-hash tests.
*/

// ═══════════════════════════════════════════════════════════════
// SECTION 3: PRACTICAL BENCHMARKING
// ═══════════════════════════════════════════════════════════════

void benchmarkContainers() {
    cout << "═══ BENCHMARKING STL CONTAINERS ═══\n\n";
    const int N = 1000000;

    // Benchmark vector push_back
    {
        auto start = chrono::steady_clock::now();
        vector<int> v;
        for (int i = 0; i < N; i++) v.push_back(i);
        auto end = chrono::steady_clock::now();
        auto ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        cout << "vector push_back (10^6):       " << ms << " ms\n";
    }

    // Benchmark vector with reserve
    {
        auto start = chrono::steady_clock::now();
        vector<int> v;
        v.reserve(N);  // Pre-allocate!
        for (int i = 0; i < N; i++) v.push_back(i);
        auto end = chrono::steady_clock::now();
        auto ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        cout << "vector push_back+reserve:      " << ms << " ms (FASTER!)\n";
    }

    // Benchmark set insert
    {
        auto start = chrono::steady_clock::now();
        set<int> s;
        for (int i = 0; i < N; i++) s.insert(i);
        auto end = chrono::steady_clock::now();
        auto ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        cout << "set insert (10^6):             " << ms << " ms\n";
    }

    // Benchmark unordered_set insert
    {
        auto start = chrono::steady_clock::now();
        unordered_set<int> s;
        for (int i = 0; i < N; i++) s.insert(i);
        auto end = chrono::steady_clock::now();
        auto ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        cout << "unordered_set insert (10^6):   " << ms << " ms\n";
    }

    // Benchmark map vs unordered_map
    {
        auto start = chrono::steady_clock::now();
        map<int, int> m;
        for (int i = 0; i < N; i++) m[i] = i;
        auto end = chrono::steady_clock::now();
        auto ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        cout << "map insert (10^6):             " << ms << " ms\n";
    }
    {
        auto start = chrono::steady_clock::now();
        unordered_map<int, int> m;
        for (int i = 0; i < N; i++) m[i] = i;
        auto end = chrono::steady_clock::now();
        auto ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        cout << "unordered_map insert (10^6):   " << ms << " ms\n";
    }

    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: ALGORITHM COMPLEXITY
// ═══════════════════════════════════════════════════════════════
/*
 ALGORITHM COMPLEXITIES:
 ───────────────────────
 ┌─────────────────────┬─────────────┬───────────────────────────┐
 │ Algorithm           │ Complexity  │ Notes                     │
 ├─────────────────────┼─────────────┼───────────────────────────┤
 │ sort()              │ O(N log N)  │ IntroSort (hybrid)        │
 │ stable_sort()       │ O(N log N)  │ Merge sort, extra memory  │
 │ partial_sort(k)     │ O(N log K)  │ Only sort first K         │
 │ nth_element()       │ O(N) avg    │ Find k-th, NOT fully sort │
 │ binary_search()     │ O(log N)    │ Requires sorted range     │
 │ lower_bound()       │ O(log N)    │ First >= value            │
 │ upper_bound()       │ O(log N)    │ First > value             │
 │ find()              │ O(N)        │ Linear search             │
 │ count()             │ O(N)        │ Count occurrences         │
 │ accumulate()        │ O(N)        │ Sum/fold                  │
 │ reverse()           │ O(N)        │ In-place                  │
 │ unique()            │ O(N)        │ Requires sorted range     │
 │ next_permutation()  │ O(N)        │ Next lexicographic perm   │
 │ set_union()         │ O(N+M)     │ Both ranges must be sorted│
 └─────────────────────┴─────────────┴───────────────────────────┘

 GM TIP: nth_element is O(N) average — use it instead of sort when you
         only need the k-th smallest element!
*/

void demonstrateComplexity() {
    cout << "═══ ALGORITHM COMPLEXITY DEMO ═══\n\n";
    const int N = 10000000;  // 10^7

    vector<int> v(N);
    for (int i = 0; i < N; i++) v[i] = N - i;

    // sort: O(N log N)
    {
        auto start = chrono::steady_clock::now();
        sort(v.begin(), v.end());
        auto end = chrono::steady_clock::now();
        auto ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        cout << "sort(10^7):          " << ms << " ms\n";
    }

    // binary_search: O(log N) — needs sorted
    {
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < 1000000; i++)
            binary_search(v.begin(), v.end(), i);
        auto end = chrono::steady_clock::now();
        auto ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        cout << "binary_search(10^6): " << ms << " ms\n";
    }

    // find: O(N) linear — much slower for searching
    {
        auto start = chrono::steady_clock::now();
        find(v.begin(), v.end(), N / 2);
        auto end = chrono::steady_clock::now();
        auto ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        cout << "find(mid element):   " << ms << " ms\n";
    }

    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: TLE ESTIMATION GUIDE
// ═══════════════════════════════════════════════════════════════
/*
 HOW TO ESTIMATE IF YOUR SOLUTION WILL TLE:
 ──────────────────────────────────────────

 Step 1: Find N from constraints
 Step 2: Calculate total operations from your approach
 Step 3: Compare with 10^8 (safe limit per second)

 EXAMPLE:
   N = 2 × 10^5
   Your approach: for each element, do a set.lower_bound → O(N log N)
   Operations: 2 × 10^5 × 17 ≈ 3.4 × 10^6 → SAFE ✓

   N = 2 × 10^5
   Your approach: for each pair, check → O(N²)
   Operations: 4 × 10^10 → TLE ✗

 CONSTRAINT-TO-COMPLEXITY CHEAT SHEET:
 ┌──────────────────┬────────────────────┐
 │ N ≤ 10           │ O(N!), O(2^N × N) │
 │ N ≤ 20           │ O(2^N), O(N² × 2^N│
 │ N ≤ 100          │ O(N⁴)             │
 │ N ≤ 500          │ O(N³)             │
 │ N ≤ 5000         │ O(N²)             │
 │ N ≤ 10^5         │ O(N√N), O(N logN) │
 │ N ≤ 10^6         │ O(N log N)        │
 │ N ≤ 10^7         │ O(N)              │
 │ N ≤ 10^8         │ O(N) tight        │
 │ N ≤ 10^18        │ O(log N), O(√N)   │
 └──────────────────┴────────────────────┘
*/

void tleEstimationDemo() {
    cout << "═══ TLE ESTIMATION EXAMPLES ═══\n\n";

    cout << "Problem: N = 200000 elements, find pairs with sum = K\n";
    cout << "  Approach 1: Two nested loops → O(N²) = 4×10^10 → TLE ✗\n";
    cout << "  Approach 2: Sort + Two pointers → O(N log N) = 3.4×10^6 → OK ✓\n";
    cout << "  Approach 3: unordered_set → O(N) avg = 2×10^5 → FAST ✓\n\n";

    cout << "Problem: N = 1000 nodes, all-pairs shortest path\n";
    cout << "  Floyd-Warshall: O(N³) = 10^9 → TIGHT (might TLE)\n";
    cout << "  N × Dijkstra:  O(N² log N) = ~2×10^7 → OK ✓\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    benchmarkContainers();
    demonstrateComplexity();
    tleEstimationDemo();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. Always estimate complexity BEFORE coding\n";
    cout << "2. ~10^8 operations per second = safe limit\n";
    cout << "3. vector + sort + binary_search ≈ O(N log N)\n";
    cout << "4. unordered containers: O(1) average, O(N) worst\n";
    cout << "5. reserve() your vectors — avoids reallocation TLE\n";
    cout << "6. nth_element is O(N) — faster than full sort for k-th element\n";

    return 0;
}

/*
 PRACTICE PROBLEMS:
 ──────────────────
 1. Estimate complexity for each approach before solving:
    [CF 1A Theatre Square]  https://codeforces.com/problemset/problem/1/A
    [CSES Missing Number]   https://cses.fi/problemset/task/1083
    [LC Two Sum]            https://leetcode.com/problems/two-sum/
*/

