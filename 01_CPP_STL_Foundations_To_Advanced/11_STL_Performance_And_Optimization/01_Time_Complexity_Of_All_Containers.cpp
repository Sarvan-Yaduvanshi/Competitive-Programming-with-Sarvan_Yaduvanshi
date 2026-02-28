/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — TIME COMPLEXITY OF ALL STL CONTAINERS                       ║
║           From Zero to Grandmaster — The Complete Reference                ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. MASTER COMPLEXITY TABLE (Every container, every operation)
 2. Amortized vs Worst-Case — What CP Judges Actually Measure
 3. Hidden Constants — Why O(1) Can Be Slower Than O(log n)
 4. Live Benchmarks — Proof with Numbers
 5. How to Estimate If Your Solution Will TLE

═══════════════════════════════════════════════════════════════════════════════
 MASTER COMPLEXITY TABLE
═══════════════════════════════════════════════════════════════════════════════

 SEQUENCE CONTAINERS:
 ┌──────────────┬──────────┬───────────┬───────────┬───────────┬───────────┐
 │ Container    │ Access   │ push_back │ push_front│ Insert mid│ Erase mid │
 ├──────────────┼──────────┼───────────┼───────────┼───────────┼───────────┤
 │ vector       │ O(1)     │ O(1) *    │ O(n) ✗    │ O(n)      │ O(n)      │
 │ deque        │ O(1)     │ O(1) *    │ O(1) *    │ O(n)      │ O(n)      │
 │ list         │ O(n)     │ O(1)      │ O(1)      │ O(1) **   │ O(1) **   │
 │ forward_list │ O(n)     │ N/A       │ O(1)      │ O(1) **   │ O(1) **   │
 │ array        │ O(1)     │ N/A       │ N/A       │ N/A       │ N/A       │
 └──────────────┴──────────┴───────────┴───────────┴───────────┴───────────┘
  * = amortized (occasional reallocation costs O(n), but averaged → O(1))
  ** = O(1) ONLY if you already have an iterator to the position!
       Finding the position is O(n) since list has no random access.

 ASSOCIATIVE CONTAINERS:
 ┌──────────────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
 │ Container        │ Insert   │ Erase    │ Find     │ lower_b  │ Count    │
 ├──────────────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
 │ set              │ O(log n) │ O(log n) │ O(log n) │ O(log n) │ O(log n) │
 │ multiset         │ O(log n) │ O(log n) │ O(log n) │ O(log n) │O(log n+k)│
 │ map              │ O(log n) │ O(log n) │ O(log n) │ O(log n) │ O(log n) │
 │ multimap         │ O(log n) │ O(log n) │ O(log n) │ O(log n) │O(log n+k)│
 │ unordered_set    │ O(1)/O(n)│ O(1)/O(n)│ O(1)/O(n)│ N/A      │O(1)/O(n) │
 │ unordered_map    │ O(1)/O(n)│ O(1)/O(n)│ O(1)/O(n)│ N/A      │O(1)/O(n) │
 └──────────────────┴──────────┴──────────┴──────────┴──────────┴──────────┘
  unordered: O(1) average, O(n) worst case (hash collisions!)

 CONTAINER ADAPTORS:
 ┌──────────────────┬──────────┬──────────┬──────────┬──────────┐
 │ Container        │ Top/Front│ Push     │ Pop      │ Size     │
 ├──────────────────┼──────────┼──────────┼──────────┼──────────┤
 │ stack            │ O(1)     │ O(1)     │ O(1)     │ O(1)     │
 │ queue            │ O(1)     │ O(1)     │ O(1)     │ O(1)     │
 │ priority_queue   │ O(1)     │ O(log n) │ O(log n) │ O(1)     │
 └──────────────────┴──────────┴──────────┴──────────┴──────────┘

 PBDS:
 ┌──────────────────┬──────────┬──────────┬──────────┬──────────────────────┐
 │ Container        │ Insert   │ Erase    │ Find     │ Special              │
 ├──────────────────┼──────────┼──────────┼──────────┼──────────────────────┤
 │ ordered_set      │ O(log n) │ O(log n) │ O(log n) │ find_by_order O(logn)│
 │ (PBDS tree)      │          │          │          │ order_of_key O(logn) │
 └──────────────────┴──────────┴──────────┴──────────┴──────────────────────┘

 SPECIAL:
 ┌──────────────────┬──────────┬──────────┬──────────────────────────────────┐
 │ Container        │ Access   │ Set/Reset│ Special                          │
 ├──────────────────┼──────────┼──────────┼──────────────────────────────────┤
 │ bitset<N>        │ O(1)     │ O(1)     │ AND/OR/XOR/SHIFT: O(N/64)       │
 │ string           │ O(1)     │ O(1)     │ substr O(k), find O(n*m)        │
 └──────────────────┴──────────┴──────────┴──────────────────────────────────┘
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: AMORTIZED vs WORST-CASE
// ═══════════════════════════════════════════════════════════════
/*
 AMORTIZED O(1):
 ───────────────
 vector::push_back is "amortized O(1)".
 Most calls are O(1), but when capacity is full, it REALLOCATES:
   • Allocates 2× memory
   • Copies ALL elements → O(n)
   • Then inserts → O(1)

 Over N push_back calls, total work = N + N/2 + N/4 + ... ≈ 2N → O(1) each!

 DRY RUN (capacity doubling):
   push 1 → cap=1, no realloc                     cost: 1
   push 2 → cap=1 FULL → realloc to 2, copy 1     cost: 1+1 = 2
   push 3 → cap=2 FULL → realloc to 4, copy 2     cost: 1+2 = 3
   push 4 → cap=4, no realloc                      cost: 1
   push 5 → cap=4 FULL → realloc to 8, copy 4     cost: 1+4 = 5
   push 6 → cap=8, no realloc                      cost: 1
   push 7 → cap=8, no realloc                      cost: 1
   push 8 → cap=8, no realloc                      cost: 1
   ─────
   Total for 8 pushes: 1+2+3+1+5+1+1+1 = 15
   Amortized per push: 15/8 ≈ 1.875 → O(1)

   BUT: That single realloc at push 5 was O(n)!
   If you have a HARD real-time constraint, use reserve().
*/

void demonstrateAmortized() {
    cout << "═══ AMORTIZED vs WORST-CASE ═══\n\n";

    vector<int> v;
    cout << "push_back capacity growth:\n";
    int prevCap = 0;
    for (int i = 0; i < 20; i++) {
        v.push_back(i);
        if ((int)v.capacity() != prevCap) {
            cout << "  push " << i << ": size=" << v.size()
                 << ", capacity=" << v.capacity();
            if (prevCap > 0)
                cout << " ← REALLOC (copied " << prevCap << " elements!)";
            cout << "\n";
            prevCap = v.capacity();
        }
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: HIDDEN CONSTANTS — WHY O(1) CAN LOSE TO O(log n)
// ═══════════════════════════════════════════════════════════════
/*
 BIG-O HIDES CONSTANTS!

 unordered_map find: O(1) average
   But: hash computation + modulo + bucket traversal + cache miss
   Hidden constant: ~5-10x more than a simple array access

 map find: O(log n)
   But: tree traversal is cache-unfriendly (pointer chasing)
   For n=10^5, log n ≈ 17 → 17 cache misses

 REAL-WORLD COMPARISON (10^6 ops):
   array[i]:           ~5 ms    (O(1), cache-friendly)
   vector[i]:          ~5 ms    (O(1), cache-friendly)
   unordered_map[i]:   ~80 ms   (O(1) but high constant!)
   map[i]:             ~300 ms  (O(log n), cache-unfriendly)
   set.find(x):        ~350 ms  (O(log n), cache-unfriendly)

 TAKEAWAY: For pure indexed access, NOTHING beats vector/array.
           unordered_map is 15x slower than vector even though both are "O(1)".
*/

void demonstrateHiddenConstants() {
    cout << "═══ HIDDEN CONSTANTS BENCHMARK ═══\n\n";

    const int N = 1000000;

    // Array access
    {
        vector<int> arr(N);
        iota(arr.begin(), arr.end(), 0);
        auto start = chrono::steady_clock::now();
        long long sum = 0;
        for (int i = 0; i < N; i++) sum += arr[i];
        auto ms = chrono::duration_cast<chrono::microseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "vector[i] (10^6):       " << ms << " μs\n";
    }

    // unordered_map access
    {
        unordered_map<int, int> um;
        um.reserve(N);
        for (int i = 0; i < N; i++) um[i] = i;
        auto start = chrono::steady_clock::now();
        long long sum = 0;
        for (int i = 0; i < N; i++) sum += um[i];
        auto ms = chrono::duration_cast<chrono::microseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "unordered_map[i] (10^6):" << ms << " μs\n";
    }

    // map access
    {
        map<int, int> m;
        for (int i = 0; i < N; i++) m[i] = i;
        auto start = chrono::steady_clock::now();
        long long sum = 0;
        for (int i = 0; i < N; i++) sum += m[i];
        auto ms = chrono::duration_cast<chrono::microseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "map[i] (10^6):          " << ms << " μs\n";
    }

    // set find
    {
        set<int> s;
        for (int i = 0; i < N; i++) s.insert(i);
        auto start = chrono::steady_clock::now();
        long long sum = 0;
        for (int i = 0; i < N; i++) {
            auto it = s.find(i);
            sum += *it;
        }
        auto ms = chrono::duration_cast<chrono::microseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "set.find (10^6):        " << ms << " μs\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: HOW TO ESTIMATE TLE
// ═══════════════════════════════════════════════════════════════
/*
 RULE OF THUMB:
 ──────────────
 Online judges allow ~10^8 simple operations per second.
 (Add, compare, array access = "simple")

 COMPLEXITY → MAX N for 1 second:
 ┌──────────────┬────────────────┬──────────────────────────────────┐
 │ Complexity   │ Max N (1 sec)  │ Example                          │
 ├──────────────┼────────────────┼──────────────────────────────────┤
 │ O(1)         │ Any            │ Math formula                     │
 │ O(log n)     │ ~10^18         │ Binary search, power             │
 │ O(√n)        │ ~10^16         │ Trial division                   │
 │ O(n)         │ ~10^8          │ Linear scan                      │
 │ O(n log n)   │ ~5×10^6        │ sort, set operations             │
 │ O(n√n)       │ ~10^5          │ Mo's algorithm                   │
 │ O(n²)        │ ~10^4          │ Nested loops, DP 2D              │
 │ O(n² log n)  │ ~3×10^3        │ Sort inside nested loop          │
 │ O(n³)        │ ~500           │ Floyd-Warshall, matrix mult      │
 │ O(2^n)       │ ~25            │ Brute-force subsets               │
 │ O(n!)        │ ~12            │ Permutation brute-force           │
 │ O(n × 2^n)   │ ~20            │ Bitmask DP                       │
 └──────────────┴────────────────┴──────────────────────────────────┘

 ADJUSTMENT FOR STL:
   set/map operations have ~5-10x higher constant than array
   → Treat O(n log n) with set as if it were O(5n log n)
   → Max N ≈ 10^6 for set-heavy solutions (not 5×10^6)

 FORMULA:
   operations = complexity(N)
   If operations > 3×10^8 → likely TLE
   If operations > 10^8 with heavy STL → likely TLE
*/

void demonstrateTLEEstimation() {
    cout << "═══ TLE ESTIMATION ═══\n\n";

    // Example: Is O(n²) feasible for n=10^4?
    int n = 10000;
    long long ops = (long long)n * n;
    cout << "O(n²) with n=10^4: " << ops << " ops → "
         << (ops < 300000000 ? "✓ PASS" : "✗ TLE") << "\n";

    // Example: Is O(n²) feasible for n=10^5?
    n = 100000;
    ops = (long long)n * n;
    cout << "O(n²) with n=10^5: " << ops << " ops → "
         << (ops < 300000000 ? "✓ PASS" : "✗ TLE") << "\n";

    // Example: Is O(n log n) with map feasible for n=5×10^5?
    n = 500000;
    ops = (long long)n * 20 * 10;  // log₂(5e5)≈19, ×10 for map constant
    cout << "O(n log n) map n=5×10^5: " << ops << " ops → "
         << (ops < 300000000 ? "✓ PASS" : "✗ TLE (borderline!)") << "\n\n";

    cout << "GM TIP: When in doubt, benchmark locally with chrono!\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: COMMON TLE TRAPS WITH COMPLEXITY
// ═══════════════════════════════════════════════════════════════

void demonstrateTLETraps() {
    cout << "═══ COMMON TLE TRAPS ═══\n\n";

    cout << "TRAP 1: std::lower_bound on set → O(n)!\n";
    cout << "  BAD:  lower_bound(s.begin(), s.end(), x)  → O(n)\n";
    cout << "  GOOD: s.lower_bound(x)                     → O(log n)\n\n";

    cout << "TRAP 2: std::find on map → O(n)!\n";
    cout << "  BAD:  find(m.begin(), m.end(), make_pair(k,v)) → O(n)\n";
    cout << "  GOOD: m.find(k)                                 → O(log n)\n\n";

    cout << "TRAP 3: Checking key in map with [] → creates entry!\n";
    cout << "  BAD:  if (m[key] != 0)   → creates m[key]=0 if missing!\n";
    cout << "  GOOD: if (m.count(key))  → no side effect\n\n";

    cout << "TRAP 4: size() on list → O(1) since C++11 (was O(n))!\n";
    cout << "  But: distance(it1, it2) on list is O(n)\n\n";

    cout << "TRAP 5: erase in middle of vector inside loop → O(n²) total!\n";
    cout << "  GOOD: erase-remove idiom → O(n) total\n\n";

    cout << "TRAP 6: String concatenation in loop → O(n²)!\n";
    cout << "  BAD:  for (...) result += s;  (each += copies entire result)\n";
    cout << "  GOOD: stringstream or reserve() first\n\n";

    // Live demo of trap 6
    {
        const int N = 50000;
        // BAD: O(n²) string concat
        auto start = chrono::steady_clock::now();
        string bad;
        for (int i = 0; i < N; i++) bad += "x";
        auto t1 = chrono::duration_cast<chrono::microseconds>(
            chrono::steady_clock::now() - start).count();

        // GOOD: reserve first
        start = chrono::steady_clock::now();
        string good;
        good.reserve(N);
        for (int i = 0; i < N; i++) good += "x";
        auto t2 = chrono::duration_cast<chrono::microseconds>(
            chrono::steady_clock::now() - start).count();

        cout << "String concat (5×10^4):\n";
        cout << "  Without reserve: " << t1 << " μs\n";
        cout << "  With reserve:    " << t2 << " μs\n\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demonstrateAmortized();
    demonstrateHiddenConstants();
    demonstrateTLEEstimation();
    demonstrateTLETraps();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. Amortized O(1) = O(1) on average, but occasional O(n) spikes\n";
    cout << "2. Hidden constants: unordered_map O(1) is ~15x slower than vector O(1)\n";
    cout << "3. Rule: ~10^8 simple ops/sec, ~10^7 for STL-heavy ops\n";
    cout << "4. ALWAYS use member .find()/.lower_bound() on set/map\n";
    cout << "5. Estimate ops BEFORE coding — avoid wasting time on TLE solutions\n";
    cout << "6. When borderline: benchmark locally with chrono\n";

    return 0;
}

/*
 PRACTICE:
 ─────────
 Try these to internalize complexity:
 1. Estimate complexity of your last 5 solved problems
 2. For each, predict max N that would pass in 1 second
 3. Verify by benchmarking on your machine
*/

