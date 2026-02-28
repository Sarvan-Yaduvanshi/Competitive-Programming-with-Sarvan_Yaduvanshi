/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Prefix Sum Hybrid + Contribution Trick with Fixed Window
 *  Level   : Medium → Hard
 * ============================================================================
 *
 *  ▶ KEY TECHNIQUES:
 *  ─────────────────
 *  1. Window Sum via Prefix Array: sum[l..r] = prefix[r+1] - prefix[l]
 *  2. Weighted Window Sum: each element contributes weight * value
 *  3. Contribution Trick: Instead of computing each window's sum,
 *     count how many windows each element belongs to, and its total contribution.
 *     Element at index i belongs to windows starting at max(0, i-k+1) to min(i, n-k).
 *     Count of windows = min(i, k-1, n-k, n-1-i) + 1 (approximately)
 *  4. Prefix XOR Window: XOR of [l..r] = prefixXOR[r+1] ^ prefixXOR[l]
 *
 *  PROBLEMS:
 *  LC 1588 — Sum of All Odd Length Subarrays (contribution trick)
 *            https://leetcode.com/problems/sum-of-all-odd-length-subarrays/
 *  LC 2100 — Find Good Days to Rob the Bank (prefix non-increasing/non-decreasing)
 *            https://leetcode.com/problems/find-good-days-to-rob-the-bank/
 *  LC 1895 — Largest Magic Square (2D prefix + fixed window check)
 *            https://leetcode.com/problems/largest-magic-square/
 *  LC 1423 — Max Points You Can Obtain from Cards (prefix+suffix window)
 *            https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/
 *  CF 1352B — Same Parity Summands (800)
 *            https://codeforces.com/problemset/problem/1352/B
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
using ll = long long;

// ============================================================================
// Window Sum using Prefix Array — O(1) per query after O(N) precomputation
// ============================================================================
/*
 * prefix[0] = 0, prefix[i] = prefix[i-1] + arr[i-1]
 * sum(l..r) = prefix[r+1] - prefix[l]
 * For window of size K starting at i: sum = prefix[i+k] - prefix[i]
 */
vector<ll> windowSumViaPrefix(vector<int>& arr, int k) {
    int n = arr.size();
    vector<ll> prefix(n + 1, 0);
    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + arr[i];

    vector<ll> result;
    for (int i = 0; i + k <= n; i++)
        result.push_back(prefix[i + k] - prefix[i]);
    return result;
}

// ============================================================================
// LC 1588: Sum of All Odd Length Subarrays — CONTRIBUTION TRICK
// ============================================================================
/*
 * Brute force: enumerate all odd-length subarrays, sum → O(N³)
 * Contribution trick: For each element arr[i], count how many odd-length
 * subarrays include it, then total contribution = arr[i] * count.
 *
 * Element i is in subarrays [l..r] where l ≤ i ≤ r.
 * Number of choices for l: (i + 1)  (0, 1, ..., i)
 * Number of choices for r: (n - i)  (i, i+1, ..., n-1)
 * Total subarrays containing i: (i + 1) * (n - i)
 * Of these, odd-length ones: ceil(total / 2) = (total + 1) / 2
 *
 * Time: O(N), Space: O(1)
 */
int sumOddLengthSubarrays(vector<int>& arr) {
    int n = arr.size(), total = 0;
    for (int i = 0; i < n; i++) {
        int subarrays = (i + 1) * (n - i);       // Total subarrays containing i
        int oddCount = (subarrays + 1) / 2;       // Odd-length ones
        total += arr[i] * oddCount;
    }
    return total;
}

// ============================================================================
// CONTRIBUTION TRICK — Total sum of all windows of size K
// ============================================================================
/*
 * Each element arr[i] appears in min(i+1, k, n-i, n-k+1) windows.
 * Instead of summing each window individually, compute:
 *   totalContribution = sum of arr[i] * (number of K-windows containing i)
 *
 * Element i is in K-windows starting from max(0, i-k+1) to min(i, n-k).
 * Count = min(i, n-k) - max(0, i-k+1) + 1
 */
ll totalSumAllKWindows(vector<int>& arr, int k) {
    int n = arr.size();
    ll total = 0;
    for (int i = 0; i < n; i++) {
        int windowsContaining = min(i, n - k) - max(0, i - k + 1) + 1;
        total += (ll)arr[i] * windowsContaining;
    }
    return total;
}

// ============================================================================
// Weighted Window Sum — positional weighting
// ============================================================================
/*
 * Each position in the window has a weight: weight[0], weight[1], ..., weight[k-1].
 * Window sum at position i = sum(arr[i+j] * weight[j]) for j=0..k-1.
 * Sliding: add arr[right]*weight[k-1], subtract arr[left]*weight[0],
 * then shift weights → this is actually convolution, not trivially O(1).
 *
 * For fixed weights: precompute prefix weighted sums or use FFT for large K.
 * For simple weights (like position index): use formula.
 */
vector<ll> weightedWindowSum(vector<int>& arr, vector<int>& weights) {
    int n = arr.size(), k = weights.size();
    vector<ll> result;
    for (int i = 0; i + k <= n; i++) {
        ll sum = 0;
        for (int j = 0; j < k; j++)
            sum += (ll)arr[i + j] * weights[j];
        result.push_back(sum);
    }
    return result; // O(N*K) — for O(N) use FFT
}

// ============================================================================
// LC 1423: Max Points from Cards — Prefix + Suffix Window
// ============================================================================
/*
 * Pick exactly K cards from front and/or back. Maximize sum.
 * Equivalent: Remove a window of (N-K) from the middle. Minimize that.
 * Or: Prefix sum of first i + suffix sum of last (K-i).
 *
 * Time: O(K), Space: O(1)
 */
int maxScore(vector<int>& cardPoints, int k) {
    int n = cardPoints.size();
    // Take first K cards initially
    int currentSum = 0;
    for (int i = 0; i < k; i++) currentSum += cardPoints[i];

    int best = currentSum;
    // Move one card from front to back at a time
    for (int i = k - 1; i >= 0; i--) {
        currentSum -= cardPoints[i];
        currentSum += cardPoints[n - k + i];
        best = max(best, currentSum);
    }
    return best;
}

// ============================================================================
// Prefix XOR Window — XOR of [l..r]
// ============================================================================
vector<int> xorWindowViaPrefix(vector<int>& arr, int k) {
    int n = arr.size();
    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] ^ arr[i];

    vector<int> result;
    for (int i = 0; i + k <= n; i++)
        result.push_back(prefix[i + k] ^ prefix[i]);
    return result;
}

int main() {
    vector<int> arr = {1, 4, 2, 5, 3};

    // Window sum via prefix
    auto ws = windowSumViaPrefix(arr, 3);
    cout << "Window sums (k=3): ";
    for (ll x : ws) cout << x << " ";
    cout << "\n"; // 7 11 10

    // Contribution trick: sum of all odd-length subarrays
    cout << "Sum odd-length subarrays: " << sumOddLengthSubarrays(arr) << "\n"; // 58

    // Total sum of all K=3 windows (contribution)
    cout << "Total sum all K=3 windows: " << totalSumAllKWindows(arr, 3) << "\n"; // 7+11+10=28

    // Max points from cards
    vector<int> cards = {1, 2, 3, 4, 5, 6, 1};
    cout << "Max points (k=3): " << maxScore(cards, 3) << "\n"; // 12

    return 0;
}

