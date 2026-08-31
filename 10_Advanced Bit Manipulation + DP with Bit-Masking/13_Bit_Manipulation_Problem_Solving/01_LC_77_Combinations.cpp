/*
Author: Sarvan.DP.GrandMaster
Created : 2026-08-31 16:40:18
*/


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;

static vector<vector<int>> combination_bitwise(const int n, const int k) {
    if (k < 0 || k > n) return {};
    if (k == 0) return {{}};

    // 1. Calculate nCr mathematically to pre-allocate 'ans'
    long long combinations_count = 1;
    for (int i = 1; i <= k; ++i) {
        combinations_count = combinations_count * (n - i + 1) / i;
    }

    vector<vector<int>> ans;
    ans.reserve(combinations_count);

    // 2. Initialize the first combination mask (k ones on the right)
    // E.g., if k = 3, mask = (1 << 3) - 1 = 7 (binary 00111)
    int mask = (1 << k) - 1;

    // The largest valid mask will have the k ones on the far left of the n bits
    // E.g., if n=5, k=3, max_mask = 7 << (5-3) = 7 << 2 = 28 (binary 11100)
    int limit = mask << (n - k);

    vector<int> current;
    current.reserve(k);

    while (mask <= limit) {
        current.clear();

        // 3. Decode the mask into actual numbers (1-indexed)
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                current.emplace_back(i + 1);
            }
        }
        ans.emplace_back(current);

        // 4. Gosper's Hack: Generate the next lexicographical bitmask
        int c0 = mask & -mask;
        int r = mask + c0;
        mask = r | (((r ^ mask) >> 2) / c0);
    }

    return ans;
}
void solve() {
    
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << fixed << setprecision(10);
    
    // Multi-test case support (commented out for this demo)
    // int TC = 1;
    // cin >> TC;
    // while (TC--) solve();
    
    solve();
    return 0;
}

