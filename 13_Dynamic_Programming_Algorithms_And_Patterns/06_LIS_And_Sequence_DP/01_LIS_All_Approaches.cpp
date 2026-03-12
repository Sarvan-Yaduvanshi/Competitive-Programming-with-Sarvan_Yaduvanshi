/*
 * ============================================================================
 *        LONGEST INCREASING SUBSEQUENCE (LIS) — ALL APPROACHES
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Sequence DP — LIS O(n²), LIS O(n log n), Variants
 * Level   : ⭐⭐⭐ Advanced
 * ============================================================================
 *
 * LIS PROBLEM (LeetCode 300):
 *   Find the length of the longest strictly increasing subsequence.
 *
 * APPROACH 1: O(n²) DP
 *   dp[i] = LIS ending at index i
 *   dp[i] = max(dp[j] + 1) for all j < i where a[j] < a[i]
 *
 * APPROACH 2: O(n log n) Binary Search (Patience Sorting)
 *   Maintain array 'tails' where tails[i] = smallest tail element
 *   of all increasing subsequences of length i+1.
 *   For each element: binary search for position to insert.
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// LIS O(n²) — with reconstruction
pair<int, vector<int>> lis_n2(vector<int>& arr) {
    int n = arr.size();
    vector<int> dp(n, 1), parent(n, -1);
    int maxLen = 1, maxIdx = 0;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        if (dp[i] > maxLen) {
            maxLen = dp[i];
            maxIdx = i;
        }
    }

    // Reconstruct
    vector<int> lis;
    for (int i = maxIdx; i != -1; i = parent[i])
        lis.push_back(arr[i]);
    reverse(lis.begin(), lis.end());
    return {maxLen, lis};
}

// LIS O(n log n) — Patience Sorting
int lis_nlogn(vector<int>& arr) {
    vector<int> tails;  // tails[i] = smallest ending of IS of length i+1

    for (int x : arr) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end())
            tails.push_back(x);
        else
            *it = x;
    }
    return tails.size();
}

// LIS O(n log n) with reconstruction
pair<int, vector<int>> lis_nlogn_reconstruct(vector<int>& arr) {
    int n = arr.size();
    vector<int> tails, tailIdx, parent(n, -1);
    vector<int> pos(n);

    for (int i = 0; i < n; i++) {
        auto it = lower_bound(tails.begin(), tails.end(), arr[i]);
        int idx = it - tails.begin();

        if (it == tails.end()) {
            tails.push_back(arr[i]);
            tailIdx.push_back(i);
        } else {
            *it = arr[i];
            tailIdx[idx] = i;
        }

        parent[i] = (idx > 0) ? tailIdx[idx - 1] : -1;
        pos[i] = idx;
    }

    int len = tails.size();
    vector<int> lis(len);
    int k = tailIdx[len - 1];
    for (int i = len - 1; i >= 0; i--) {
        lis[i] = arr[k];
        k = parent[k];
    }
    return {len, lis};
}

// Number of LIS (LeetCode 673)
int numberOfLIS(vector<int>& nums) {
    int n = nums.size();
    vector<int> len(n, 1), cnt(n, 1);
    int maxLen = 1;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) {
                if (len[j] + 1 > len[i]) {
                    len[i] = len[j] + 1;
                    cnt[i] = cnt[j];
                } else if (len[j] + 1 == len[i]) {
                    cnt[i] += cnt[j];
                }
            }
        }
        maxLen = max(maxLen, len[i]);
    }

    int total = 0;
    for (int i = 0; i < n; i++)
        if (len[i] == maxLen) total += cnt[i];
    return total;
}

// Longest Bitonic Subsequence
// Bitonic = first increasing then decreasing
int longestBitonic(vector<int>& arr) {
    int n = arr.size();
    vector<int> lis(n, 1), lds(n, 1);

    // LIS from left
    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
            if (arr[j] < arr[i]) lis[i] = max(lis[i], lis[j] + 1);

    // LDS from right (= LIS from right)
    for (int i = n - 2; i >= 0; i--)
        for (int j = n - 1; j > i; j--)
            if (arr[j] < arr[i]) lds[i] = max(lds[i], lds[j] + 1);

    int maxBitonic = 0;
    for (int i = 0; i < n; i++)
        maxBitonic = max(maxBitonic, lis[i] + lds[i] - 1);
    return maxBitonic;
}

// Russian Doll Envelopes (LeetCode 354)
// Sort by width ascending, then LIS on heights
// For same width, sort height descending (to avoid using both)
int maxEnvelopes(vector<pair<int,int>>& envelopes) {
    sort(envelopes.begin(), envelopes.end(), [](auto& a, auto& b) {
        return a.first < b.first || (a.first == b.first && a.second > b.second);
    });

    // LIS on heights
    vector<int> tails;
    for (auto& [w, h] : envelopes) {
        auto it = lower_bound(tails.begin(), tails.end(), h);
        if (it == tails.end()) tails.push_back(h);
        else *it = h;
    }
    return tails.size();
}

// Max Sum Increasing Subsequence
int maxSumIS(vector<int>& arr) {
    int n = arr.size();
    vector<int> dp(arr);  // dp[i] = max sum IS ending at i

    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
            if (arr[j] < arr[i])
                dp[i] = max(dp[i], dp[j] + arr[i]);

    return *max_element(dp.begin(), dp.end());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== LIS & SEQUENCE DP ===" << endl;

    vector<int> arr = {10, 9, 2, 5, 3, 7, 101, 18};

    // LIS O(n²)
    auto [len1, seq1] = lis_n2(arr);
    cout << "\n--- LIS O(n²) ---" << endl;
    cout << "Length: " << len1 << ", Sequence: ";
    for (int x : seq1) cout << x << " ";
    cout << endl;

    // LIS O(n log n)
    cout << "\n--- LIS O(n log n) ---" << endl;
    cout << "Length: " << lis_nlogn(arr) << endl;

    auto [len2, seq2] = lis_nlogn_reconstruct(arr);
    cout << "Reconstructed: ";
    for (int x : seq2) cout << x << " ";
    cout << endl;

    // Number of LIS
    vector<int> arr2 = {1, 3, 5, 4, 7};
    cout << "\n--- Number of LIS ---" << endl;
    cout << "Count: " << numberOfLIS(arr2) << endl;

    // Bitonic
    vector<int> arr3 = {1, 11, 2, 10, 4, 5, 2, 1};
    cout << "\n--- Longest Bitonic ---" << endl;
    cout << "Length: " << longestBitonic(arr3) << endl;

    // Russian Doll
    vector<pair<int,int>> env = {{5,4},{6,4},{6,7},{2,3}};
    cout << "\n--- Russian Doll Envelopes ---" << endl;
    cout << "Max nesting: " << maxEnvelopes(env) << endl;

    // Max Sum IS
    vector<int> arr4 = {1, 101, 2, 3, 100, 4, 5};
    cout << "\n--- Max Sum Increasing Subsequence ---" << endl;
    cout << "Max sum: " << maxSumIS(arr4) << endl;

    return 0;
}

