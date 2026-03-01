/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 11.01 — BITSET USAGE AND BITSET DP                       ║
║           Bit Manipulation — Bitset & Optimization Tricks                  ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

C++ BITSET:
═══════════
    bitset<N> — fixed-size array of N bits, with O(N/64) time for bitwise operations.

    Operations: &, |, ^, ~, <<, >>, .count(), .any(), .none(), .flip(), .test(i), .set(i)

KEY ADVANTAGE: 64× speedup over manual bit checking.
    Regular loop over N bits: O(N)
    Bitset operation: O(N/64) — 64 bits processed per CPU instruction!

BITSET DP — SUBSET SUM:
════════════════════════
    Problem: Given array of n integers, determine all achievable subset sums.

    Regular DP: dp[s] = true/false, for each element: dp[s] |= dp[s - a[i]]  → O(n × S)

    Bitset DP: dp is a bitset<S+1>. For each element: dp |= (dp << a[i])  → O(n × S/64)

    This is 64× faster!

DRY RUN — arr=[3,5,7], what sums are possible?
    dp = 000...001 (only sum 0)
    After 3: dp |= dp<<3 → 000...001001 (sums: 0, 3)
    After 5: dp |= dp<<5 → 000...101001001 (sums: 0, 3, 5, 8)
    After 7: sums: {0, 3, 5, 7, 8, 10, 12, 15}

PRACTICE PROBLEMS:
══════════════════
    Codeforces: 1554C (bitset subset sum)
    CSES: Money Sums (with bitset optimization)
*/
#include <iostream>
#include <vector>
#include <bitset>
#include <cassert>
using namespace std;

const int MAXSUM = 100001;

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   BITSET USAGE AND BITSET DP                    ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // Basic bitset operations
    cout << "\n--- Basic Bitset Operations ---" << endl;
    bitset<8> a("10110011");
    bitset<8> b("01101010");
    cout << "  a = " << a << endl;
    cout << "  b = " << b << endl;
    cout << "  a&b = " << (a & b) << endl;
    cout << "  a|b = " << (a | b) << endl;
    cout << "  a^b = " << (a ^ b) << endl;
    cout << "  ~a  = " << (~a) << endl;
    cout << "  a<<2 = " << (a << 2) << endl;
    cout << "  a.count() = " << a.count() << " set bits" << endl;

    // Subset Sum with Bitset
    cout << "\n--- Bitset DP: Subset Sum ---" << endl;
    vector<int> arr = {3, 5, 7, 12, 20};
    bitset<MAXSUM> dp;
    dp[0] = 1; // sum 0 is achievable

    for (int x : arr) dp |= (dp << x);

    cout << "  Array: {3, 5, 7, 12, 20}" << endl;
    cout << "  Achievable sums: ";
    for (int s = 0; s <= 50; s++) {
        if (dp[s]) cout << s << " ";
    }
    cout << endl;
    cout << "  Total achievable sums (≤50): ";
    int count = 0;
    for (int s = 0; s <= 50; s++) if (dp[s]) count++;
    cout << count << endl;

    assert(dp[0] == 1);
    assert(dp[3] == 1);
    assert(dp[15] == 1); // 3+5+7
    assert(dp[47] == 1); // 3+5+7+12+20

    // Bitset for reachability in graph
    cout << "\n--- Bitset for Graph Reachability (Transitive Closure) ---" << endl;
    int V = 5;
    vector<bitset<100>> reach(V);
    // Edges: 0→1, 1→2, 2→3, 3→4, 0→3
    reach[0][1] = reach[0][3] = 1;
    reach[1][2] = 1;
    reach[2][3] = 1;
    reach[3][4] = 1;
    // Self-reachable
    for (int i = 0; i < V; i++) reach[i][i] = 1;
    // Floyd-Warshall with bitset: O(V³/64)
    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            if (reach[i][k]) reach[i] |= reach[k];

    cout << "  Can reach from 0: ";
    for (int j = 0; j < V; j++) if (reach[0][j]) cout << j << " ";
    cout << endl; // all reachable

    cout << "\n✅ Bitset usage and DP verified!" << endl;
    return 0;
}

