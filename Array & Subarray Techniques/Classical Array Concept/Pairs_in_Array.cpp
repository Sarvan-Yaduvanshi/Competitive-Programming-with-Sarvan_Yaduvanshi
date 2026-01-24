/*
Author: Sarvan.DP.GrandMaster
Created : 2026-01-05 19:36:37
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <numeric>
#include <random>
#include <chrono>

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

// Method 1: Cartesian Product (All Ordered Pairs)
// Logic: A x A. Includes (i, i) and distinguishes (i, j) from (j, i).
// Complexity: O(N^2)
void printCartesian(const vec<int>& arr) {
    int n = sz(arr);

    // GM Safety: Don't print if N is huge (saves your terminal)
    if (n > 1000) {
        cout << "Skipping print (Size too large). Total: " << 1LL * n * n << nl;
        return;
    }

    cout << "--- Cartesian Product ---" << nl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "(" << arr[i] << "," << arr[j] << ") ";
        }
        cout << nl;
    }
    cout << "Total Pairs: " << 1LL * n * n << nl << nl;
}

// Method 2: Distinct Pairs / Combinations (Strictly Upper Triangular)
// Logic: Order doesn't matter ( (1,2) is same as (2,1) ), no (i, i).
// Complexity: O(N^2) but constant factor 1/2
void printCombinations(const vec<int>& arr) {
    int n = sz(arr);

    // GM Safety
    if (n > 2000) {
        cout << "Skipping print. Total: " << 1LL * n * (n - 1) / 2 << nl;
        return;
    }

    cout << "--- Combinations (i < j) ---" << nl;
    for (int i = 0; i < n; i++) {
        // Optimization: Start j from i + 1 immediately
        for (int j = i + 1; j < n; j++) {
            cout << "(" << arr[i] << "," << arr[j] << ") ";
        }
        // Only print newline if we actually printed pairs for this row
        if (i < n - 1) cout << nl;
    }
    cout << "Total Pairs: " << 1LL * n * (n - 1) / 2 << nl;
}

// Method 3: Permutations (Ordered Distinct Pairs)
// Use Case: When order matters but same elements not allowed.
// Formula: Total pairs = n(n-1)
// Permutations: All ordered pairs where i ≠ j
// Distinguishes (i,j) from (j,i), excludes (i,i)
void printPermutations(const vec<int>& arr) {
    int n = sz(arr);

    if (n > 1500) {
        cout << "Skipping print. Total: "
             << 1LL * n * (n - 1) << nl;
        return;
    }

    cout << "--- Permutations (i ≠ j) ---" << nl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                cout << "(" << arr[i] << "," << arr[j] << ") ";
            }
        }
        cout << nl;
    }
    cout << "Total Pairs: " << 1LL * n * (n - 1) << nl;
}

// Method 4: Count Pairs with Given Sum
// Problem: Find number of pairs where arr[i] + arr[j] = targetSum.
// Approach 1 : Using HashMap Time Complexity --> O(N)  Space Complexity --> O(N)
int countPairsWithSum(const vec<int>& arr,int n, int targetSum){
    // Map stores: <Number, How many times we've seen it so far>
    unordered_map<int, int> freq;
    int count = 0;

    for (int i = 0; i < n; i++) {
        // 1. Calculate what number we need to find to make the sum
        int complement = targetSum - arr[i];

        // 2. Look "Backwards": Did we see the complement earlier?
        if (freq.find(complement) != freq.end()) {
            // If yes, this current number (arr[i]) makes a pair
            // with EVERY instance of the complement we've seen.
            count += freq[complement];
        }

        // 3. Store "History": Add the current number to the map
        // so future numbers can pair with it.
        freq[arr[i]]++;
    }

    return count;
}

// Using Two Pointers (Sorted Array) - O(n log n)
int countPairsWithSumSorted(const vec<int>& arr, int n, int targetSum){
    int left = 0;
    int right = n - 1;
    int count = 0;

    while (left < right){
        int currSum = arr[left] + arr[right];

        if (currSum == targetSum){
            int leftCount = 1, rightCount = 1;

            // 1. Count how many times the number at 'left' repeats
            while (left + 1 < right && arr[left] == arr[left + 1]){
                leftCount++;
                left++;
            }

            // 2. Count how many times the number at 'right' repeats
            while (right - 1 > left && arr[right] == arr[right - 1]){
                rightCount++;
                right++;
            }

            // 3. CHECK: Are the left numbers and right numbers actually the SAME number?
            // Example: [3, 3, 3, 3] with target 6
            if (arr[left] == arr[right]){
                // Special Formula for combinations: n*(n+1)/2
                // (Note: here leftCount is essentially n-1)
                count += (leftCount * (leftCount - 1)) / 2;
            }
            // 4. NORMAL CASE: Different numbers
            // Example: [2, 2] and [4, 4, 4] with target 6
            else{
                count += (leftCount * rightCount); // 2 * 3 = 6 pairs
            }

            // Move pointers inward to escape the processed duplicates
            left++;
            right--;
        }
    }

    return count;
}

void solve() {
    int n; cin >> n;

    vec<int> arr(n); read(arr);

    printCartesian(arr);
    printCombinations(arr);
    printPermutations(arr);
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

