/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — BITSET COMPLETE GUIDE                                       ║
║           From Zero to Grandmaster — 64x Speedup for DP                    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Bitset Basics & Operations
 2. Bitset Arithmetic (AND, OR, XOR, SHIFT)
 3. Counting and Querying
 4. DP Optimization with Bitset (Knapsack 64x Speedup!)
 5. Reachability in Graph with Bitset

WHAT IS BITSET?
───────────────
  bitset<N> = fixed-size array of N bits, operated in 64-bit chunks.
  Bitwise operations are 64x faster than operating bit-by-bit!

  bitset<8> b("10110011") → stores 8 bits
  Internal: processed in 64-bit words → if N=1000, only 16 words!

  All bitwise ops (AND, OR, XOR, SHIFT): O(N/64) instead of O(N)
  This is called "bitset optimization" and is a GM-level trick.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ═══ SECTION 1: BASICS ═══
    cout << "═══ BITSET BASICS ═══\n\n";

    bitset<8> b1;           // All zeros: 00000000
    bitset<8> b2(42);       // From int: 00101010
    bitset<8> b3("11001100"); // From string

    cout << "b1 (zeros):  " << b1 << "\n";
    cout << "b2 (42):     " << b2 << "\n";
    cout << "b3 (string): " << b3 << "\n\n";

    // Set, reset, flip
    b1.set(3);      // Set bit 3 → 00001000
    b1.set(5);      // Set bit 5 → 00101000
    cout << "After set(3,5): " << b1 << "\n";

    b1.reset(3);    // Clear bit 3 → 00100000
    cout << "After reset(3): " << b1 << "\n";

    b1.flip();      // Flip all bits → 11011111
    cout << "After flip():   " << b1 << "\n";

    b1.flip(0);     // Flip bit 0
    cout << "After flip(0):  " << b1 << "\n\n";

    // Access individual bits
    cout << "b2 = " << b2 << "\n";
    cout << "b2[0] = " << b2[0] << ", b2[1] = " << b2[1]
         << ", b2[5] = " << b2[5] << "\n";
    cout << "b2.test(3) = " << b2.test(3) << " (with bounds check)\n\n";

    // ═══ SECTION 2: BITWISE OPERATIONS ═══
    cout << "═══ BITWISE OPERATIONS ═══\n\n";

    bitset<8> a("11001100");
    bitset<8> b("10101010");

    cout << "a =     " << a << "\n";
    cout << "b =     " << b << "\n";
    cout << "a & b = " << (a & b) << " (AND)\n";
    cout << "a | b = " << (a | b) << " (OR)\n";
    cout << "a ^ b = " << (a ^ b) << " (XOR)\n";
    cout << "~a =    " << (~a) << " (NOT)\n";
    cout << "a << 2 = " << (a << 2) << " (left shift)\n";
    cout << "a >> 2 = " << (a >> 2) << " (right shift)\n\n";

    // ═══ SECTION 3: COUNTING ═══
    cout << "═══ COUNTING ═══\n\n";

    bitset<8> c("10110011");
    cout << "c = " << c << "\n";
    cout << "count() = " << c.count() << " (number of 1s)\n";
    cout << "size() = " << c.size() << " (total bits)\n";
    cout << "any() = " << c.any() << " (at least one 1?)\n";
    cout << "none() = " << c.none() << " (all zeros?)\n";
    cout << "all() = " << c.all() << " (all ones?)\n\n";

    // Convert
    cout << "to_ulong() = " << c.to_ulong() << "\n";
    cout << "to_string() = " << c.to_string() << "\n\n";

    // ═══ SECTION 4: KNAPSACK DP WITH BITSET (THE GM TRICK!) ═══
    cout << "═══ KNAPSACK WITH BITSET (64x SPEEDUP) ═══\n\n";
    /*
     PROBLEM: Given weights, can we achieve sum S? (Subset Sum)

     STANDARD DP: O(N × S) with boolean dp[S+1]
     BITSET DP:   O(N × S / 64) — 64x faster!

     IDEA:
       dp = bitset where dp[i] = 1 if sum i is achievable
       For each weight w: dp |= (dp << w)

       This shifts ALL achievable sums by w and unions them!

     DRY RUN: weights = [3, 5, 7], target = 8
       dp = 000000001  (only sum 0)
       w=3: dp |= dp<<3 → 000001001  (sums 0, 3)
       w=5: dp |= dp<<5 → 000101001  → 100101001  (sums 0, 3, 5, 8)
       w=7: dp |= dp<<7 → ...
       dp[8] = 1 → YES, sum 8 is achievable (3+5)!
    */

    vector<int> weights = {3, 5, 7, 1, 4};
    const int MAXSUM = 100;
    bitset<101> dp;  // dp[i] = can we make sum i?
    dp[0] = 1;       // Sum 0 is always achievable

    cout << "Weights: ";
    for (int w : weights) cout << w << " ";
    cout << "\n\n";

    for (int w : weights) {
        dp |= (dp << w);  // This single line replaces O(S) inner loop!
    }

    cout << "Achievable sums: ";
    for (int i = 0; i <= 20; i++) {
        if (dp[i]) cout << i << " ";
    }
    cout << "\n";

    int target = 8;
    cout << "Can make " << target << "? " << (dp[target] ? "YES" : "NO") << "\n";
    target = 6;
    cout << "Can make " << target << "? " << (dp[target] ? "YES" : "NO") << "\n\n";

    // ═══ SECTION 5: GRAPH REACHABILITY WITH BITSET ═══
    cout << "═══ GRAPH REACHABILITY ═══\n\n";
    /*
     PROBLEM: For each node, which nodes can it reach?

     STANDARD: BFS/DFS per node → O(V × (V + E))
     BITSET:   Process in topological order → O(V² / 64)

     reach[u] |= reach[v] for each edge u→v (in reverse topo order)
    */

    int n = 5;
    // DAG: 0→1, 0→2, 1→3, 2→3, 3→4
    vector<vector<int>> adj(n);
    adj[0] = {1, 2}; adj[1] = {3}; adj[2] = {3}; adj[3] = {4};

    // Process in reverse topological order: 4, 3, 2, 1, 0
    vector<bitset<5>> reach(n);
    vector<int> order = {4, 3, 2, 1, 0};

    for (int u : order) {
        reach[u][u] = 1;  // Can reach itself
        for (int v : adj[u]) {
            reach[u] |= reach[v];  // O(N/64) per edge!
        }
    }

    cout << "Reachability:\n";
    for (int i = 0; i < n; i++) {
        cout << "  Node " << i << " can reach: ";
        for (int j = 0; j < n; j++) {
            if (reach[i][j]) cout << j << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. bitset<N> operations: O(N/64) instead of O(N)\n";
    cout << "2. Knapsack/Subset Sum: dp |= (dp << w) — 64x speedup\n";
    cout << "3. Graph reachability: reach[u] |= reach[v] — O(V²/64)\n";
    cout << "4. count() for popcount, test(i) for safe access\n";
    cout << "5. Size must be compile-time constant\n";
    cout << "6. This is a GRANDMASTER-level optimization technique!\n";

    return 0;
}

/*
 PRACTICE PROBLEMS:
 ──────────────────
 1. [AtCoder DP Contest — Knapsack 2] Use bitset for subset sum
 2. [CSES Reachability Queries]        Bitset + topo sort
 3. [CF Subset Sum DP]                 Bitset optimization
*/

