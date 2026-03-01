/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 05.06 — MEET IN THE MIDDLE USING BITMASK                 ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

CONCEPT:
════════
    When n is too large for O(2ⁿ) but small enough for O(2^(n/2)):
    Split array into two halves, enumerate subsets of each half, merge.

    n = 40: O(2⁴⁰) = 10¹² (too slow!)
    But: O(2 × 2²⁰) = O(2 × 10⁶) (fast!)

ALGORITHM:
══════════
    1. Split array A[0..n-1] into left A[0..n/2-1] and right A[n/2..n-1]
    2. Generate all 2^(n/2) subset sums for each half
    3. Sort one half's sums
    4. For each sum in the other half, binary search for complement

CLASSIC PROBLEM: Subset sum closest to target T.
    For each left subset sum L, find R in right sums closest to T - L.

DRY RUN — arr=[3,5,7,11], target=15:
    Left = {3,5}: sums = {0, 3, 5, 8}
    Right = {7,11}: sums = {0, 7, 11, 18}
    For L=8: need R close to 15-8=7 → R=7 → sum=15 ✓

TIME: O(2^(n/2) × log(2^(n/2))) = O(n × 2^(n/2))

PRACTICE PROBLEMS:
══════════════════
    CSES: Meet in the Middle
    LeetCode 1755: Closest Subsequence Sum
    Codeforces: 888E
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>
using namespace std;

// Generate all subset sums of arr
vector<long long> allSubsetSums(vector<int>& arr) {
    int n = arr.size();
    vector<long long> sums;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long s = 0;
        for (int i = 0; i < n; i++)
            if (mask & (1 << i)) s += arr[i];
        sums.push_back(s);
    }
    return sums;
}

// Find closest subset sum to target
long long closestSubsetSum(vector<int>& arr, long long target) {
    int n = arr.size();
    int half = n / 2;

    // Split
    vector<int> left(arr.begin(), arr.begin() + half);
    vector<int> right(arr.begin() + half, arr.end());

    // Generate subset sums
    vector<long long> leftSums = allSubsetSums(left);
    vector<long long> rightSums = allSubsetSums(right);

    // Sort right sums
    sort(rightSums.begin(), rightSums.end());

    // For each left sum, find best right sum
    long long best = LLONG_MAX;
    long long bestSum = 0;
    for (long long L : leftSums) {
        long long need = target - L;
        // Binary search for closest to 'need'
        auto it = lower_bound(rightSums.begin(), rightSums.end(), need);
        if (it != rightSums.end()) {
            long long diff = abs(L + *it - target);
            if (diff < best) { best = diff; bestSum = L + *it; }
        }
        if (it != rightSums.begin()) {
            --it;
            long long diff = abs(L + *it - target);
            if (diff < best) { best = diff; bestSum = L + *it; }
        }
    }
    return bestSum;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   MEET IN THE MIDDLE                            ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    vector<int> arr = {3, 5, 7, 11};
    long long target = 15;

    cout << "  Array: {3, 5, 7, 11}, Target: " << target << endl;
    long long result = closestSubsetSum(arr, target);
    cout << "  Closest subset sum: " << result << endl;
    assert(result == 15); // 3+5+7 = 15

    vector<int> arr2 = {1, 2, 3, 4, 5, 6};
    target = 10;
    cout << "\n  Array: {1,2,3,4,5,6}, Target: " << target << endl;
    result = closestSubsetSum(arr2, target);
    cout << "  Closest subset sum: " << result << endl;
    assert(result == 10); // 1+3+6 or 1+4+5 or 4+6

    cout << "\n✅ Meet in the middle verified!" << endl;
    return 0;
}

