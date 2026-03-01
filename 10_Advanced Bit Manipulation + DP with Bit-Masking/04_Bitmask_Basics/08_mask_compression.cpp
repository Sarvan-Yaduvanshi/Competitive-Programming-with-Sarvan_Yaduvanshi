/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 04.08 — MASK COMPRESSION                                 ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

CONCEPT: When the actual element values are large but count is small (≤20),
    map them to indices 0..k-1 and use bitmask over these indices.

EXAMPLE:
    Elements: {100, 500, 200, 300} → Compress to indices: 100→0, 200→1, 300→2, 500→3
    Now use 4-bit bitmask.

TECHNIQUE: Coordinate compression + bitmask.
    1. Collect unique values, sort them
    2. Map each value to its sorted index
    3. Use bitmask over indices

APPLICATIONS:
═════════════
    • Bitmask DP with large element values but small count
    • Encode states in DP where states are from a small set
    • Reduce memory from large value space to small index space

TIME: O(n log n) for compression, then O(1) per mask operation
*/
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <bitset>
using namespace std;

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   MASK COMPRESSION                              ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // Example: large values, small count
    vector<int> values = {1000, 5000, 2000, 3000, 1000, 5000};

    // Step 1: Get unique sorted values
    vector<int> sorted_unique = values;
    sort(sorted_unique.begin(), sorted_unique.end());
    sorted_unique.erase(unique(sorted_unique.begin(), sorted_unique.end()), sorted_unique.end());

    // Step 2: Create mapping
    map<int, int> compress;
    for (int i = 0; i < (int)sorted_unique.size(); i++) {
        compress[sorted_unique[i]] = i;
    }

    cout << "\n--- Compression Mapping ---" << endl;
    for (auto& [val, idx] : compress) {
        cout << "  " << val << " → index " << idx << endl;
    }

    // Step 3: Build bitmask for a subset
    int n = sorted_unique.size(); // n = 4, fits in bitmask
    vector<int> subset = {1000, 3000, 5000};
    int mask = 0;
    for (int v : subset) mask |= (1 << compress[v]);

    cout << "\n--- Subset {1000, 3000, 5000} as bitmask ---" << endl;
    cout << "  mask = " << bitset<4>(mask) << " (" << mask << ")" << endl;
    cout << "  Size = " << __builtin_popcount(mask) << endl;

    // Check membership
    cout << "\n--- Membership Checks ---" << endl;
    for (int v : {1000, 2000, 3000, 5000}) {
        int idx = compress[v];
        bool present = (mask >> idx) & 1;
        cout << "  " << v << " (index " << idx << "): " << (present ? "IN SET" : "not in set") << endl;
    }

    // Can now do bitmask DP over these 4 elements
    cout << "\n  Total possible subsets: 2^" << n << " = " << (1 << n) << " (very manageable!)" << endl;

    cout << "\n✅ Mask compression demonstrated!" << endl;
    return 0;
}

