/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           05 — RESERVE OPTIMIZATION — THE COMPLETE GUIDE                   ║
║           From Zero to Grandmaster — Stop Wasting Time on Reallocation     ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. vector::reserve — How Capacity Doubling Works
 2. unordered_map::reserve — Pre-allocate Buckets
 3. string::reserve — Avoid String Reallocation
 4. shrink_to_fit — Reclaim Wasted Memory
 5. Benchmark: With vs Without Reserve

═══════════════════════════════════════════════════════════════════════════════
 HOW VECTOR CAPACITY WORKS
═══════════════════════════════════════════════════════════════════════════════

 vector maintains TWO sizes:
   size()     = number of elements currently stored
   capacity() = total memory allocated (how many CAN be stored)

 When size == capacity and you push_back:
   1. Allocate NEW block of 2× capacity
   2. COPY/MOVE all elements to new block → O(n)!
   3. Deallocate old block
   4. Insert new element

 DRY RUN:
   push 1:  size=1, cap=1                            (alloc 1)
   push 2:  cap FULL → alloc 2, copy 1 element       (copy 1)
   push 3:  cap FULL → alloc 4, copy 2 elements      (copy 2)
   push 4:  size=4, cap=4                            (no realloc)
   push 5:  cap FULL → alloc 8, copy 4 elements      (copy 4)
   push 6:  size=6, cap=8                            (no realloc)
   push 7:  size=7, cap=8                            (no realloc)
   push 8:  size=8, cap=8                            (no realloc)
   push 9:  cap FULL → alloc 16, copy 8 elements     (copy 8)

   Total copies: 0 + 1 + 2 + 0 + 4 + 0 + 0 + 0 + 8 = 15 for 9 pushes

   WITH reserve(9): ZERO copies! Allocate 9 (or more) upfront.
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: VECTOR RESERVE — VISUALIZE REALLOCATIONS
// ═══════════════════════════════════════════════════════════════

void vectorReserveDemo() {
    cout << "═══ VECTOR CAPACITY GROWTH (Without Reserve) ═══\n\n";

    vector<int> v;
    int reallocCount = 0;
    int totalCopies = 0;
    int prevCap = 0;

    for (int i = 0; i < 33; i++) {
        v.push_back(i);
        if ((int)v.capacity() != prevCap) {
            if (prevCap > 0) {
                reallocCount++;
                totalCopies += prevCap;
                cout << "  REALLOC #" << reallocCount
                     << ": cap " << prevCap << " → " << v.capacity()
                     << " (copied " << prevCap << " elements)\n";
            } else {
                cout << "  Initial alloc: cap = " << v.capacity() << "\n";
            }
            prevCap = v.capacity();
        }
    }
    cout << "\n  Total reallocations: " << reallocCount << "\n";
    cout << "  Total elements copied: " << totalCopies << "\n";
    cout << "  Final: size=" << v.size() << ", cap=" << v.capacity() << "\n\n";

    // With reserve
    cout << "═══ WITH reserve(33) ═══\n\n";
    vector<int> v2;
    v2.reserve(33);
    cout << "  After reserve(33): size=" << v2.size() << ", cap=" << v2.capacity() << "\n";
    for (int i = 0; i < 33; i++) v2.push_back(i);
    cout << "  After 33 pushes:   size=" << v2.size() << ", cap=" << v2.capacity() << "\n";
    cout << "  Reallocations: 0! ✓\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: VECTOR RESERVE — BENCHMARK
// ═══════════════════════════════════════════════════════════════

void vectorReserveBenchmark() {
    cout << "═══ VECTOR RESERVE BENCHMARK ═══\n\n";

    for (int N : {100000, 1000000, 5000000, 10000000}) {
        // Without reserve
        auto start = chrono::steady_clock::now();
        vector<int> v1;
        for (int i = 0; i < N; i++) v1.push_back(i);
        auto t1 = chrono::duration_cast<chrono::microseconds>(
            chrono::steady_clock::now() - start).count();

        // With reserve
        start = chrono::steady_clock::now();
        vector<int> v2;
        v2.reserve(N);
        for (int i = 0; i < N; i++) v2.push_back(i);
        auto t2 = chrono::duration_cast<chrono::microseconds>(
            chrono::steady_clock::now() - start).count();

        double speedup = t1 > 0 ? (double)t1 / max(t2, 1L) : 0;
        cout << "  N=" << setw(8) << N
             << ": no-reserve=" << setw(6) << t1 << " μs"
             << ",  reserve=" << setw(6) << t2 << " μs"
             << ",  speedup=" << fixed << setprecision(1) << speedup << "x\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: UNORDERED_MAP RESERVE
// ═══════════════════════════════════════════════════════════════

void unorderedMapReserve() {
    cout << "═══ UNORDERED_MAP RESERVE ═══\n\n";

    const int N = 500000;

    // Without reserve — many rehashes
    {
        unordered_map<int, int> m;
        cout << "Without reserve:\n";
        cout << "  Initial buckets: " << m.bucket_count() << "\n";
        for (int i = 0; i < N; i++) m[i] = i;
        cout << "  Final buckets:   " << m.bucket_count() << "\n";
        cout << "  Load factor:     " << fixed << setprecision(3) << m.load_factor() << "\n";
    }

    // With reserve — no rehashes
    {
        unordered_map<int, int> m;
        m.reserve(N);
        cout << "\nWith reserve(" << N << "):\n";
        cout << "  Initial buckets: " << m.bucket_count() << "\n";
        for (int i = 0; i < N; i++) m[i] = i;
        cout << "  Final buckets:   " << m.bucket_count() << "\n";
        cout << "  Load factor:     " << fixed << setprecision(3) << m.load_factor() << "\n\n";
    }

    // Benchmark
    {
        auto start = chrono::steady_clock::now();
        unordered_map<int, int> m1;
        for (int i = 0; i < N; i++) m1[i] = i;
        auto t1 = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();

        start = chrono::steady_clock::now();
        unordered_map<int, int> m2;
        m2.reserve(N);
        for (int i = 0; i < N; i++) m2[i] = i;
        auto t2 = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();

        cout << "  Benchmark (5×10^5): no-reserve=" << t1 << "ms, reserve=" << t2 << "ms\n\n";
    }
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: STRING RESERVE
// ═══════════════════════════════════════════════════════════════

void stringReserve() {
    cout << "═══ STRING RESERVE ═══\n\n";

    const int N = 1000000;

    // Without reserve — O(n²) from reallocations!
    {
        string s;
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < N; i++) s += 'x';
        auto ms = chrono::duration_cast<chrono::microseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "String concat (10^6) no reserve:   " << ms << " μs\n";
    }

    // With reserve — O(n)
    {
        string s;
        s.reserve(N);
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < N; i++) s += 'x';
        auto ms = chrono::duration_cast<chrono::microseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "String concat (10^6) with reserve: " << ms << " μs\n\n";
    }
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: SHRINK_TO_FIT — RECLAIM WASTED MEMORY
// ═══════════════════════════════════════════════════════════════

void shrinkToFitDemo() {
    cout << "═══ SHRINK_TO_FIT ═══\n\n";

    /*
     After erasing elements, vector keeps its capacity.
     shrink_to_fit() requests the container to reduce capacity to size.
     (Note: it's a non-binding request — compiler MAY ignore it)
    */

    vector<int> v(1000000);
    cout << "After creating 10^6 elements: size=" << v.size()
         << ", cap=" << v.capacity() << "\n";

    v.resize(100);
    cout << "After resize(100):           size=" << v.size()
         << ", cap=" << v.capacity() << " (capacity unchanged!)\n";

    v.shrink_to_fit();
    cout << "After shrink_to_fit():       size=" << v.size()
         << ", cap=" << v.capacity() << " ✓\n\n";

    // Alternative: swap trick (guaranteed)
    vector<int> v2(1000000);
    v2.resize(100);
    cout << "Swap trick: cap before=" << v2.capacity();
    vector<int>(v2).swap(v2);  // Create temp copy, swap with original
    cout << ", cap after=" << v2.capacity() << " ✓\n\n";

    cout << "GM TIP: In CP, you rarely need shrink_to_fit.\n";
    cout << "        Memory limit is usually generous.\n";
    cout << "        Focus on reserve() to PREVENT reallocs, not reclaim.\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 6: WHEN TO RESERVE — PATTERNS
// ═══════════════════════════════════════════════════════════════

void reservePatterns() {
    cout << "═══ RESERVE PATTERNS ═══\n\n";

    // Pattern 1: Known size from input
    cout << "Pattern 1: Known size from input\n";
    cout << "  int n; cin >> n;\n";
    cout << "  vector<int> a(n);   // Direct construction with size\n";
    cout << "  // or:\n";
    cout << "  vector<int> a; a.reserve(n);\n\n";

    // Pattern 2: Building result vector
    cout << "Pattern 2: Building result\n";
    cout << "  vector<int> result;\n";
    cout << "  result.reserve(n);  // Know max possible size\n";
    cout << "  for (...) result.push_back(...);\n\n";

    // Pattern 3: Adjacency list
    cout << "Pattern 3: Adjacency list (graph)\n";
    cout << "  vector<vector<int>> adj(n);  // n vectors created\n";
    cout << "  // Can't easily reserve inner vectors\n";
    cout << "  // Alternative: use flat edge list + sort\n\n";

    // Pattern 4: unordered_map frequency
    cout << "Pattern 4: Frequency map\n";
    cout << "  unordered_map<int,int,custom_hash> freq;\n";
    cout << "  freq.reserve(n);  // At most n distinct elements\n";
    cout << "  for (int x : arr) freq[x]++;\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vectorReserveDemo();
    vectorReserveBenchmark();
    unorderedMapReserve();
    stringReserve();
    shrinkToFitDemo();
    reservePatterns();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. reserve() eliminates ALL reallocation overhead\n";
    cout << "2. vector without reserve: O(log n) reallocations, O(n) total copies\n";
    cout << "3. unordered_map.reserve(n): prevents O(n) rehash operations\n";
    cout << "4. string.reserve(n): avoids O(n²) from repeated concatenation\n";
    cout << "5. shrink_to_fit(): rarely needed in CP, use for memory-tight problems\n";
    cout << "6. RULE: If you know the size, ALWAYS reserve!\n";

    return 0;
}

