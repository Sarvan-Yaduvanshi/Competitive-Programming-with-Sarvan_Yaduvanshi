/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           10 — MEMORY LAYOUT & CACHE OPTIMIZATION                          ║
║           From Zero to Grandmaster — The Hardware Advantage                 ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. How CPU Cache Works (L1/L2/L3)
 2. Cache Lines — Why 64 Bytes Matters
 3. Contiguous vs Node-Based Memory Layout
 4. Array of Structs (AoS) vs Struct of Arrays (SoA)
 5. Cache-Friendly vs Cache-Hostile Patterns
 6. False Sharing (brief)
 7. Practical Tips for CP

═══════════════════════════════════════════════════════════════════════════════
 HOW CPU CACHE WORKS
═══════════════════════════════════════════════════════════════════════════════

 CPU → L1 Cache (32KB, ~1ns) → L2 Cache (256KB, ~4ns)
     → L3 Cache (8MB, ~12ns) → RAM (16GB, ~100ns)

 When CPU needs data at address X:
   1. Check L1 → HIT? Use it. (~1ns)
   2. Check L2 → HIT? Load into L1. (~4ns)
   3. Check L3 → HIT? Load into L1+L2. (~12ns)
   4. RAM → Load 64-byte CACHE LINE into all levels. (~100ns)

 KEY INSIGHT: CPU loads 64 BYTES at a time, not 4!
 So if you access arr[0], arr[1], arr[2], arr[3] are FREE (same cache line)!

 CONSEQUENCE:
   Sequential access (vector):  Almost always L1 hit → ~1ns per element
   Random access (linked list): Almost always L1 miss → ~100ns per element
   That's 100x difference just from memory layout!

 ┌──────────────────────────────────────────────────────────────────────┐
 │ Access Pattern          │ Cache Behavior           │ Speed          │
 ├──────────────────────────┼──────────────────────────┼────────────────┤
 │ vector sequential scan  │ Every access is cache hit│ ★★★★★ FASTEST │
 │ array[i] indexed        │ Predictable, prefetched  │ ★★★★★ FASTEST │
 │ deque sequential        │ Mostly cache-friendly    │ ★★★★            │
 │ unordered_map lookup    │ Hash + bucket access     │ ★★★              │
 │ map/set traversal       │ Pointer chasing, random  │ ★★               │
 │ list traversal          │ Every node = cache miss  │ ★ SLOWEST       │
 └──────────────────────────┴──────────────────────────┴────────────────┘
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: CACHE LINE VISUALIZATION
// ═══════════════════════════════════════════════════════════════

void cacheLineDemo() {
    cout << "═══ CACHE LINE (64 BYTES) ═══\n\n";

    cout << "One cache line = 64 bytes:\n";
    cout << "  = 16 ints (4 bytes each)\n";
    cout << "  = 8 doubles (8 bytes each)\n";
    cout << "  = 8 pointers on 64-bit (8 bytes each)\n\n";

    cout << "When you access arr[0], CPU loads arr[0..15] into cache!\n\n";

    cout << "VECTOR: [10][20][30][40][50][60][70][80] ... contiguous\n";
    cout << "         ├──── cache line 1 ────────────┤\n";
    cout << "  Access arr[0] → arr[1..15] are FREE (prefetched)!\n\n";

    cout << "LIST:   [node1] → [node2] → [node3] → ...\n";
    cout << "        addr:0x1000  0xF000   0x3000\n";
    cout << "  Access node1 → node2 is at different cache line → MISS!\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: SEQUENTIAL vs RANDOM ACCESS BENCHMARK
// ═══════════════════════════════════════════════════════════════

void sequentialVsRandom() {
    cout << "═══ SEQUENTIAL vs RANDOM ACCESS ═══\n\n";

    const int N = 5000000;
    vector<int> v(N);
    iota(v.begin(), v.end(), 0);

    // Sequential access — cache-friendly
    {
        auto start = chrono::steady_clock::now();
        long long sum = 0;
        for (int i = 0; i < N; i++) sum += v[i];
        auto us = chrono::duration_cast<chrono::microseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "Sequential (5×10^6):   " << us << " μs\n";
    }

    // Random access — cache-hostile
    {
        vector<int> indices(N);
        iota(indices.begin(), indices.end(), 0);
        mt19937 rng(42);
        shuffle(indices.begin(), indices.end(), rng);

        auto start = chrono::steady_clock::now();
        long long sum = 0;
        for (int i = 0; i < N; i++) sum += v[indices[i]];
        auto us = chrono::duration_cast<chrono::microseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "Random shuffle (5×10^6):" << us << " μs\n";
    }

    // Stride access — partially cache-hostile
    {
        auto start = chrono::steady_clock::now();
        long long sum = 0;
        for (int i = 0; i < N; i += 16) sum += v[i];  // Skip 16 = 1 cache line
        auto us = chrono::duration_cast<chrono::microseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "Stride-16 (N/16 ops):  " << us << " μs\n\n";
    }

    cout << "Random access is MUCH slower due to cache misses!\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: AoS vs SoA (Array of Structs vs Struct of Arrays)
// ═══════════════════════════════════════════════════════════════
/*
 Array of Structs (AoS):
   struct Point { int x, y, z; };
   vector<Point> points;
   Memory: [x0,y0,z0][x1,y1,z1][x2,y2,z2]...

   ✓ Good when you access all fields of each element
   ✗ Bad when you only access one field (wastes cache loading unused fields)

 Struct of Arrays (SoA):
   struct Points { vector<int> x, y, z; };
   Memory: [x0,x1,x2,...][y0,y1,y2,...][z0,z1,z2,...]

   ✓ Good when you process one field at a time (sum all x values)
   ✗ Bad when you need all fields of each element
*/

void aosSoaBenchmark() {
    cout << "═══ AoS vs SoA BENCHMARK ═══\n\n";

    const int N = 5000000;

    // AoS — Access only x field
    struct PointAoS { int x, y, z; };
    vector<PointAoS> aos(N);
    for (int i = 0; i < N; i++) aos[i] = {i, i * 2, i * 3};

    {
        auto start = chrono::steady_clock::now();
        long long sum = 0;
        for (int i = 0; i < N; i++) sum += aos[i].x;  // Loads y,z too (wasted!)
        auto us = chrono::duration_cast<chrono::microseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "AoS (access only .x): " << us << " μs\n";
    }

    // SoA — Access only x array
    vector<int> sx(N), sy(N), sz(N);
    for (int i = 0; i < N; i++) { sx[i] = i; sy[i] = i * 2; sz[i] = i * 3; }

    {
        auto start = chrono::steady_clock::now();
        long long sum = 0;
        for (int i = 0; i < N; i++) sum += sx[i];  // Only loads x values!
        auto us = chrono::duration_cast<chrono::microseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "SoA (access only x[]): " << us << " μs\n\n";
    }

    cout << "SoA wins when accessing single field: 3x better cache usage!\n";
    cout << "(Each cache line has 16 x-values instead of 5 x-values + waste)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: CONTAINER MEMORY LAYOUT COMPARISON
// ═══════════════════════════════════════════════════════════════

void containerMemoryLayouts() {
    cout << "═══ CONTAINER MEMORY LAYOUTS ═══\n\n";

    cout << "VECTOR / ARRAY / STRING:\n";
    cout << "  [elem0][elem1][elem2][elem3][elem4]...  (contiguous)\n";
    cout << "  ★★★★★ Cache-friendly: sequential prefetch works perfectly\n\n";

    cout << "DEQUE:\n";
    cout << "  [block0: e0,e1,...,e511] [block1: e512,...,e1023] ...\n";
    cout << "  ★★★★ Mostly contiguous within blocks (512 bytes each)\n\n";

    cout << "SET / MAP (Red-Black Tree):\n";
    cout << "  [node100] ← ptr → [node50] ← ptr → [node25]\n";
    cout << "                   ↘ [node75]\n";
    cout << "  ★★ Every traversal step = pointer chase = likely cache miss\n\n";

    cout << "UNORDERED_MAP (Hash Table):\n";
    cout << "  Bucket array: [ptr0][ptr1][ptr2]...  (contiguous)\n";
    cout << "  Chains: ptr0 → [node] → [node]       (scattered nodes)\n";
    cout << "  ★★★ Bucket lookup OK, chain traversal = cache miss\n\n";

    cout << "LIST:\n";
    cout << "  [node] ←→ [node] ←→ [node] ←→ [node]\n";
    cout << "  Each node allocated separately → scattered in memory\n";
    cout << "  ★ Worst cache performance of all containers\n\n";

    // Memory overhead per int element
    cout << "MEMORY OVERHEAD PER int ELEMENT:\n";
    cout << "  vector:        4 bytes  (just the int)\n";
    cout << "  deque:         4 bytes  (approximately)\n";
    cout << "  set:          ~40 bytes (int + 3 ptrs + color + alignment)\n";
    cout << "  map:          ~48 bytes (key + value + 3 ptrs + color)\n";
    cout << "  unordered_map: ~56 bytes (key + value + hash + ptr + bucket ptr)\n";
    cout << "  list:         ~24 bytes (int + 2 ptrs)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: 2D ARRAY — ROW-MAJOR vs COLUMN-MAJOR
// ═══════════════════════════════════════════════════════════════

void rowVsColumnMajor() {
    cout << "═══ ROW-MAJOR vs COLUMN-MAJOR ACCESS ═══\n\n";

    /*
     C++ arrays are ROW-MAJOR:
       int a[3][4]:
       Memory: [a[0][0] a[0][1] a[0][2] a[0][3]] [a[1][0] a[1][1] ...] [a[2][0] ...]

       Row-major access (i then j): sequential → cache-friendly ✓
       Column-major (j then i): stride access → cache-hostile ✗
    */

    const int R = 2000, C = 2000;
    vector<vector<int>> mat(R, vector<int>(C, 1));

    // Row-major (cache-friendly)
    {
        auto start = chrono::steady_clock::now();
        long long sum = 0;
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                sum += mat[i][j];
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "Row-major (for i, for j):    " << ms << " ms  ← FAST\n";
    }

    // Column-major (cache-hostile)
    {
        auto start = chrono::steady_clock::now();
        long long sum = 0;
        for (int j = 0; j < C; j++)
            for (int i = 0; i < R; i++)
                sum += mat[i][j];
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "Column-major (for j, for i): " << ms << " ms  ← SLOW\n\n";
    }

    cout << "RULE: Always iterate row-first (outer=i, inner=j) in C++!\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 6: PRACTICAL TIPS FOR CP
// ═══════════════════════════════════════════════════════════════

void practicalTips() {
    cout << "═══ PRACTICAL CACHE TIPS FOR CP ═══\n\n";

    cout << "TIP 1: vector > everything for sequential processing\n";
    cout << "  Don't use list/set when vector+sort works.\n\n";

    cout << "TIP 2: Sort then binary_search > maintaining sorted set\n";
    cout << "  If queries come after all insertions:\n";
    cout << "  vector + sort + lower_bound > set.insert + set.find\n\n";

    cout << "TIP 3: 1D array over 2D for better cache\n";
    cout << "  int a[N*M] instead of int a[N][M]\n";
    cout << "  Access a[i*M + j] instead of a[i][j]\n";
    cout << "  Especially for DP tables!\n\n";

    cout << "TIP 4: Flat adjacency list > vector<vector<int>>\n";
    cout << "  For graphs: store edges in flat array + offsets\n";
    cout << "  CSR format: better cache than nested vectors\n\n";

    cout << "TIP 5: Process data in chunks that fit in L1/L2\n";
    cout << "  L1 = 32KB ≈ 8000 ints\n";
    cout << "  If your DP table row < 8000, each row fits in L1!\n\n";

    cout << "TIP 6: Avoid pointer-heavy structures in hot paths\n";
    cout << "  map, set, list = pointer chasing = cache misses\n";
    cout << "  vector, array, deque = contiguous = cache hits\n\n";

    cout << "TIP 7: Use #pragma GCC optimize for borderline TLE\n";
    cout << "  #pragma GCC optimize(\"O2,unroll-loops\")\n";
    cout << "  #pragma GCC target(\"avx2,bmi,bmi2,popcnt\")\n";
    cout << "  Can give 2-3x speedup on some problems!\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cacheLineDemo();
    sequentialVsRandom();
    aosSoaBenchmark();
    containerMemoryLayouts();
    rowVsColumnMajor();
    practicalTips();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. CPU cache loads 64 bytes at a time (cache line)\n";
    cout << "2. Sequential (vector) ≈ 100x faster than random (list)\n";
    cout << "3. vector > deque > unordered_map > map > list (cache order)\n";
    cout << "4. Row-major access for 2D arrays (outer=row, inner=col)\n";
    cout << "5. SoA beats AoS when processing single fields\n";
    cout << "6. set/map: ~40-48 bytes per element vs vector's 4 bytes\n";
    cout << "7. When borderline TLE: think about cache, not just Big-O\n";

    return 0;
}

