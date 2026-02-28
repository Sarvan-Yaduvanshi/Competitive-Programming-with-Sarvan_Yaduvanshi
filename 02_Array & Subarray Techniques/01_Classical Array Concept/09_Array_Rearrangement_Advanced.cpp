/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-28 12:00:00
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

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

// --- Type Definitions ---
using i64 = long long;
using u64 = unsigned long long;
using ld  = long double;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, int>;
using pll = pair<i64, i64>;

// --- Constants ---
constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD   = 1'000'000'007LL;
constexpr i64 MOD9  = 998'244'353LL;
constexpr ld PI     = 3.14159265358979323846;

// --- Random Number Generator ---
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// --- Macros ---
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

// Input helper
template<class T>
void read(vec<T> &v) {
    for (auto &x : v) cin >> x;
}
#define nl '\n'
#define YES cout << "YES" << nl
#define NO cout << "NO" << nl

inline i64 gcd(i64 a, i64 b) { return std::gcd(a, b); }
inline i64 lcm(i64 a, i64 b) { return (a / std::gcd(a, b)) * b; }

inline i64 modpow(i64 base, i64 exp, i64 mod = MOD) {
    i64 res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

// =============================================================================
//  MODULE 09: ARRAY REARRANGEMENT — ADVANCED
//  Level: ⭐⭐⭐⭐ Expert
//  Topics: Next permutation, leaders, equilibrium, Boyer-Moore, stock buy/sell
// =============================================================================

void printArr(const string& label, const vec<int>& arr) {
    cout << label << ": ";
    for (int i = 0; i < sz(arr); i++) {
        if (i > 0) cout << ' ';
        cout << arr[i];
    }
    cout << nl;
}

// -------------------------------------------------------------
// 1. NEXT PERMUTATION (LC 31)
// -------------------------------------------------------------
// Given a permutation, rearrange it to the next lexicographically
// greater permutation. If already the largest, wrap to smallest.
//
// Algorithm:
//   Step 1: From right, find first i where arr[i] < arr[i+1]
//           (This is the "dip" — the rightmost position we can increase)
//   Step 2: From right, find first j where arr[j] > arr[i]
//           (Smallest element greater than arr[i] to the right)
//   Step 3: Swap arr[i] and arr[j]
//   Step 4: Reverse arr[i+1..end]
//           (Make the suffix the smallest possible)
//
// Example: [1, 3, 5, 4, 2]
//   Step 1: i=1 (arr[1]=3 < arr[2]=5)
//   Step 2: j=3 (arr[3]=4 > arr[1]=3)
//   Step 3: Swap → [1, 4, 5, 3, 2]
//   Step 4: Reverse [2..4] → [1, 4, 2, 3, 5]
//
// Time: O(N), Space: O(1)

void nextPermutation(vec<int>& arr) {
    int n = sz(arr);

    // Step 1: Find the dip
    int i = n - 2;
    while (i >= 0 && arr[i] >= arr[i + 1]) {
        i--;
    }

    if (i >= 0) {
        // Step 2: Find the swap partner
        int j = n - 1;
        while (arr[j] <= arr[i]) {
            j--;
        }
        // Step 3: Swap
        swap(arr[i], arr[j]);
    }
    // Step 4: Reverse the suffix (also handles wrap-around case when i < 0)
    reverse(arr.begin() + i + 1, arr.end());
}

// STL version: next_permutation(all(arr))
// Returns true if next permutation exists, false if wrapped around.

void previousPermutation(vec<int>& arr) {
    int n = sz(arr);

    // Mirror: find first i from right where arr[i] > arr[i+1]
    int i = n - 2;
    while (i >= 0 && arr[i] <= arr[i + 1]) i--;

    if (i >= 0) {
        int j = n - 1;
        while (arr[j] >= arr[i]) j--;
        swap(arr[i], arr[j]);
    }
    reverse(arr.begin() + i + 1, arr.end());
}

// Generate all permutations of an array
void generateAllPermutations(vec<int> arr) {
    sort(all(arr)); // Start from smallest permutation
    cout << "All permutations:" << nl;
    do {
        for (int x : arr) cout << x << " ";
        cout << nl;
    } while (next_permutation(all(arr)));
}

// -------------------------------------------------------------
// 2. LEADERS IN AN ARRAY
// -------------------------------------------------------------
// A "leader" is an element that is GREATER than all elements to its right.
// The rightmost element is always a leader.
//
// Approach: Traverse right to left, track maximum.
// Time: O(N), Space: O(1)

vec<int> findLeaders(const vec<int>& arr) {
    int n = sz(arr);
    if (n == 0) return {};

    vec<int> leaders;
    int maxFromRight = arr[n - 1];
    leaders.pb(maxFromRight); // Rightmost is always a leader

    for (int i = n - 2; i >= 0; i--) {
        if (arr[i] > maxFromRight) {
            leaders.pb(arr[i]);
            maxFromRight = arr[i];
        }
    }

    reverse(all(leaders)); // To maintain left-to-right order
    return leaders;
}

// Example: [16, 17, 4, 3, 5, 2]
// Leaders: 17, 5, 2 (each is greater than all elements to its right)

// -------------------------------------------------------------
// 3. EQUILIBRIUM INDEX (Pivot Index) — LC 724
// -------------------------------------------------------------
// Find index where left sum == right sum.
// Sum of arr[0..i-1] == Sum of arr[i+1..n-1]
//
// Approach: totalSum - leftSum - arr[i] = rightSum
//           If leftSum == rightSum → equilibrium!
// Time: O(N), Space: O(1)

int equilibriumIndex(const vec<int>& arr) {
    i64 totalSum = accumulate(all(arr), 0LL);
    i64 leftSum = 0;

    for (int i = 0; i < sz(arr); i++) {
        i64 rightSum = totalSum - leftSum - arr[i];
        if (leftSum == rightSum) return i;
        leftSum += arr[i];
    }
    return -1; // No equilibrium
}

// -------------------------------------------------------------
// 4. MAJORITY ELEMENT — BOYER-MOORE VOTING ALGORITHM (LC 169)
// -------------------------------------------------------------
// Find element that appears MORE than N/2 times.
// Guaranteed to exist in the problem.
//
// Algorithm:
//   Phase 1: Find candidate
//     - Maintain a candidate and count
//     - If count == 0, pick current as new candidate
//     - If current == candidate, count++
//     - Else count--
//   Phase 2: Verify (if not guaranteed to exist)
//
// WHY IT WORKS (GM Proof):
//   Think of it as a "battle royale". Each element fights the candidate.
//   The majority element has > N/2 soldiers, so it survives all battles.
//   Every cancellation removes one majority and one minority → majority wins.
//
// Time: O(N), Space: O(1)

int majorityElement(const vec<int>& arr) {
    // Phase 1: Find candidate
    int candidate = 0;
    int count = 0;

    for (int x : arr) {
        if (count == 0) {
            candidate = x;
            count = 1;
        }
        else if (x == candidate) {
            count++;
        }
        else {
            count--;
        }
    }

    // Phase 2: Verify (needed if majority not guaranteed)
    /*
    count = 0;
    for (int x : arr) {
        if (x == candidate) count++;
    }
    if (count <= sz(arr) / 2) return -1; // No majority
    */

    return candidate;
}

// Extended: Find ALL elements appearing > N/3 times (LC 229)
// There can be at most 2 such elements.
vec<int> majorityElementII(const vec<int>& arr) {
    int n = sz(arr);
    int c1 = 0, c2 = 0, cnt1 = 0, cnt2 = 0;

    // Phase 1: Find two candidates
    for (int x : arr) {
        if (x == c1) cnt1++;
        else if (x == c2) cnt2++;
        else if (cnt1 == 0) { c1 = x; cnt1 = 1; }
        else if (cnt2 == 0) { c2 = x; cnt2 = 1; }
        else { cnt1--; cnt2--; }
    }

    // Phase 2: Verify
    cnt1 = cnt2 = 0;
    for (int x : arr) {
        if (x == c1) cnt1++;
        else if (x == c2) cnt2++;
    }

    vec<int> result;
    if (cnt1 > n / 3) result.pb(c1);
    if (cnt2 > n / 3) result.pb(c2);
    return result;
}

// -------------------------------------------------------------
// 5. BEST TIME TO BUY AND SELL STOCK (LC 121)
// -------------------------------------------------------------
// Given array of prices. Buy one day, sell a later day. Maximize profit.
//
// Approach: Track minimum price seen so far. At each day, compute
//           profit = price[i] - minPrice, update maxProfit.
// Time: O(N), Space: O(1)

int maxProfit_oneTransaction(const vec<int>& prices) {
    int minPrice = INT_MAX;
    int maxProfit = 0;

    for (int price : prices) {
        minPrice = min(minPrice, price);
        maxProfit = max(maxProfit, price - minPrice);
    }
    return maxProfit;
}

// LC 122: Buy and sell MULTIPLE times (unlimited transactions)
// Greedy: Buy every valley, sell every peak.
// Simpler: Add every positive difference.
int maxProfit_unlimited(const vec<int>& prices) {
    int profit = 0;
    for (int i = 1; i < sz(prices); i++) {
        if (prices[i] > prices[i - 1]) {
            profit += prices[i] - prices[i - 1];
        }
    }
    return profit;
}

// -------------------------------------------------------------
// 6. PRODUCT OF ARRAY EXCEPT SELF (LC 238)
// -------------------------------------------------------------
// For each i, compute product of all elements except arr[i].
// CONSTRAINT: No division!
//
// Approach: Use prefix product and suffix product.
//   prefix[i] = product of arr[0..i-1]
//   suffix[i] = product of arr[i+1..n-1]
//   answer[i] = prefix[i] * suffix[i]
//
// O(N) time, O(1) extra space (using output array)

vec<int> productExceptSelf(const vec<int>& arr) {
    int n = sz(arr);
    vec<int> result(n, 1);

    // Pass 1: Fill with prefix products
    int prefix = 1;
    for (int i = 0; i < n; i++) {
        result[i] = prefix;
        prefix *= arr[i];
    }

    // Pass 2: Multiply with suffix products
    int suffix = 1;
    for (int i = n - 1; i >= 0; i--) {
        result[i] *= suffix;
        suffix *= arr[i];
    }

    return result;
}

// -------------------------------------------------------------
// 7. TRAPPING RAIN WATER (LC 42)
// -------------------------------------------------------------
// Given elevation map, compute how much water can be trapped.
//
// At each position i:
//   water[i] = min(maxLeft[i], maxRight[i]) - height[i]
//
// Method 1: Precompute maxLeft and maxRight arrays → O(N) space
// Method 2: Two pointer → O(1) space

int trapWater(const vec<int>& height) {
    int n = sz(height);
    if (n < 3) return 0;

    int left = 0, right = n - 1;
    int leftMax = 0, rightMax = 0;
    int water = 0;

    while (left < right) {
        if (height[left] <= height[right]) {
            if (height[left] >= leftMax) {
                leftMax = height[left];
            } else {
                water += leftMax - height[left];
            }
            left++;
        } else {
            if (height[right] >= rightMax) {
                rightMax = height[right];
            } else {
                water += rightMax - height[right];
            }
            right--;
        }
    }
    return water;
}

// -------------------------------------------------------------
// 8. LONGEST CONSECUTIVE SEQUENCE (LC 128)
// -------------------------------------------------------------
// Find length of longest consecutive elements sequence.
// Time: O(N), Space: O(N)
//
// Approach: Use HashSet. For each number, if (num - 1) not in set,
//           it's the START of a sequence. Count forward.

int longestConsecutive(const vec<int>& arr) {
    set<int> s(all(arr));
    int maxLen = 0;

    for (int num : s) {
        // Only start counting if num is the START of a sequence
        if (s.find(num - 1) == s.end()) {
            int currentNum = num;
            int currentLen = 1;

            while (s.find(currentNum + 1) != s.end()) {
                currentNum++;
                currentLen++;
            }
            maxLen = max(maxLen, currentLen);
        }
    }
    return maxLen;
}

void solve() {
    cout << "╔════════════════════════════════════════╗" << nl;
    cout << "║  MODULE 09: Advanced Rearrangement     ║" << nl;
    cout << "╚════════════════════════════════════════╝" << nl;

    // 1. Next Permutation
    cout << "--- Next Permutation ---" << nl;
    vec<int> perm = {1, 3, 5, 4, 2};
    printArr("Before", perm);
    nextPermutation(perm);
    printArr("After ", perm); // 1 4 2 3 5

    // All permutations of small array
    cout << nl;
    generateAllPermutations({1, 2, 3});

    // 2. Leaders
    cout << nl << "--- Leaders ---" << nl;
    vec<int> lead = {16, 17, 4, 3, 5, 2};
    vec<int> leaders = findLeaders(lead);
    printArr("Leaders of {16,17,4,3,5,2}", leaders); // 17 5 2

    // 3. Equilibrium Index
    cout << nl << "--- Equilibrium Index ---" << nl;
    vec<int> eq = {-7, 1, 5, 2, -4, 3, 0};
    cout << "Equilibrium index: " << equilibriumIndex(eq) << nl; // 3

    // 4. Majority Element
    cout << nl << "--- Majority Element ---" << nl;
    vec<int> maj = {2, 2, 1, 1, 1, 2, 2};
    cout << "Majority: " << majorityElement(maj) << nl; // 2

    vec<int> maj2 = {3, 2, 3};
    vec<int> majII = majorityElementII(maj2);
    printArr("Majority (>N/3)", majII); // 3

    // 5. Stock Buy/Sell
    cout << nl << "--- Stock Buy/Sell ---" << nl;
    vec<int> prices = {7, 1, 5, 3, 6, 4};
    cout << "One transaction: " << maxProfit_oneTransaction(prices) << nl; // 5
    cout << "Unlimited: " << maxProfit_unlimited(prices) << nl; // 7

    // 6. Product Except Self
    cout << nl << "--- Product Except Self ---" << nl;
    vec<int> prod = {1, 2, 3, 4};
    vec<int> result = productExceptSelf(prod);
    printArr("Product", result); // 24 12 8 6

    // 7. Trapping Rain Water
    cout << nl << "--- Trapping Rain Water ---" << nl;
    vec<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << "Trapped water: " << trapWater(height) << nl; // 6

    // 8. Longest Consecutive Sequence
    cout << nl << "--- Longest Consecutive ---" << nl;
    vec<int> lcs = {100, 4, 200, 1, 3, 2};
    cout << "Longest consecutive: " << longestConsecutive(lcs) << nl; // 4
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    solve();

    return 0;
}

