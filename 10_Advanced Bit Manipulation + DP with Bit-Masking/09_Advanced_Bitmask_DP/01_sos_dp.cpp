/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 09.01 — SOS DP (Sum Over Subsets)                        ║
║           Bit Manipulation — Advanced Bitmask DP                           ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: For each mask, compute f(mask) = Σ a[sub] for all sub ⊆ mask.
    Naive: O(3ⁿ) using submask iteration.
    SOS DP: O(n × 2ⁿ) — MUCH faster!

RECURRENCE (SOS DP):
════════════════════
    dp[mask][i] = sum of a[sub] for all sub that agree with mask on bits > i,
                  and sub's bits 0..i can be anything that's a subset of mask's bits 0..i.

    dp[mask][-1] = a[mask]  (base: only mask itself)
    dp[mask][i]  = dp[mask][i-1]                    if bit i of mask is 0
                 = dp[mask][i-1] + dp[mask^(1<<i)][i-1]  if bit i of mask is 1

    Final: f(mask) = dp[mask][n-1]

OPTIMIZED (in-place, just like DP dimensions collapse):
    for (int i = 0; i < n; i++)
        for (int mask = 0; mask < (1 << n); mask++)
            if (mask & (1 << i))
                dp[mask] += dp[mask ^ (1 << i)];

DRY RUN — n=2, a = [a₀₀=1, a₀₁=2, a₁₀=3, a₁₁=4]:
    After bit 0: dp[00]=1, dp[01]=1+2=3, dp[10]=3, dp[11]=3+4=7
    After bit 1: dp[00]=1, dp[01]=3, dp[10]=1+3=4, dp[11]=3+7=10
    Verify f(11) = a[00]+a[01]+a[10]+a[11] = 1+2+3+4 = 10 ✓
    Verify f(10) = a[00]+a[10] = 1+3 = 4 ✓
    Verify f(01) = a[00]+a[01] = 1+2 = 3 ✓

TIME: O(n × 2ⁿ), SPACE: O(2ⁿ)

PRACTICE PROBLEMS:
══════════════════
    Codeforces: 165E, 449D, 383E
    AtCoder: ARC100-E
*/
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   SOS DP (Sum Over Subsets)                     ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    int n = 3;
    vector<long long> a = {1, 2, 3, 4, 5, 6, 7, 8}; // a[0..7]
    vector<long long> dp = a; // copy

    // SOS DP
    for (int i = 0; i < n; i++)
        for (int mask = 0; mask < (1 << n); mask++)
            if (mask & (1 << i))
                dp[mask] += dp[mask ^ (1 << i)];

    // Verify with brute force
    cout << "\n--- SOS DP Results (n=3) ---" << endl;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long brute = 0;
        for (int sub = mask; ; sub = (sub - 1) & mask) {
            brute += a[sub];
            if (sub == 0) break;
        }
        cout << "  f(" << bitset<3>(mask) << ") = " << dp[mask]
             << " (brute: " << brute << ")" << (dp[mask] == brute ? " ✓" : " ✗") << endl;
        assert(dp[mask] == brute);
    }

    // Application: for each number, count how many array elements are its submasks
    cout << "\n--- Application: Count submask occurrences ---" << endl;
    vector<int> arr = {3, 5, 6, 7}; // binary: 011, 101, 110, 111
    int N = 3;
    vector<long long> freq(1 << N, 0);
    for (int x : arr) freq[x]++;

    // SOS DP on freq
    for (int i = 0; i < N; i++)
        for (int mask = 0; mask < (1 << N); mask++)
            if (mask & (1 << i))
                freq[mask] += freq[mask ^ (1 << i)];

    cout << "  Array: {3(011), 5(101), 6(110), 7(111)}" << endl;
    for (int mask = 0; mask < (1 << N); mask++) {
        cout << "  Submasks of " << bitset<3>(mask) << " in array: " << freq[mask] << endl;
    }

    cout << "\n✅ SOS DP verified!" << endl;
    return 0;
}

