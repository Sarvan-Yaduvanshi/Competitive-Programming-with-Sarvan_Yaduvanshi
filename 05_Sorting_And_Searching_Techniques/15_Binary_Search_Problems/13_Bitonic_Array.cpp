/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-05 10:09:43
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

/*
 * Problem: Bitonic Array
 * Description:
 * Given a bitonic array A consisting of N integers and an integer Q.
 * In each query, you will be given an integer K, find the positions of K in A. Integer K exists in A.
 *
 *  A bitonic array is a sequence with A[1] < A[2] < A[3] ... A[K] > A[K +1] > A[K + 2] ... A[N] for some 1 <= K <= N.
 *
 * Input Format:
 * The first line contains T, the number of test cases(1 <= T <= 10000).
 * For each test case, the first line contains two integers N and Q (1 <= N, Q <= 10^5).
 * The second line contains N space-separated integers A[i] (-10^9 <= A[i] <= 10^9).
 * The next Q lines contain a single integer K (-10^9 <= K <= 10^9).
 * Sum of N over all test cases does not exceed 10^6.
 *
 * Output Format:
 * For each test case print the positions of K in A in sorted order in a new line.
 * Positions are 1-indexed.
 *
 * Constraints:
 * 1 <= T <= 10000
 * 1 <= N, Q <= 10^5
 * -10^9 <= A[i], K <= 10^9
 * Sum of N over all test cases does not exceed 10^6
 *
 * Sample Input:         Sample Output:
 * 1                      1 6
 * 6 4                    2 5
 * 1 2 5 3 2 1            3
 * 1                      4
 * 2
 * 5
 * 3
 */

// Approach:
// 1. First, find the peak element in the bitonic array using a modified binary search. This will give us the index of the maximum element.
// 2. Once we have the peak index, we can perform two separate binary searches:
//    a. An increasing binary search on the left side of the peak (from index 0 to peak index) to find the target K.
//    b. A decreasing binary search on the right side of the peak (from peak index + 1 to end of the array) to find the target K.
// 3. Collect the results from both binary searches, sort them, and print the positions in sorted order.

// Step 1: Function to find the peak element in a bitonic array
int peakFind(const vec<int>& arr){
    int lo = 0;
    int hi = sz(arr) - 1;

    while (lo < hi){
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] < arr[mid + 1]){
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return lo; // lo == hi points to the peak element
}

// Step 2 a: Increasing binary search
int increasingBS(const vec<int>& arr, int lo, int hi, int k){
    while (lo <= hi){
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == k) return mid;
        else if (arr[mid] < k) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1; // Not found
}

// Step 2 b: Decreasing binary search
int decreasingBS(const vec<int>& arr, int lo, int hi, int k){
    while (lo <= hi){
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == k) return mid;
        else if (arr[mid] > k) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1; // Not found
}

void solve() {
    int n, q;
    cin >> n >> q;

    vec<int> a(n); read(a);

    // Step 1: Find the peak index
    int peak = peakFind(a);

    while (q--){
        int k; cin >> k;

        vec<int> ans;

        // Step 2 a: Search in the left (increasing) half
        int p1 = increasingBS(a, 0, peak, k);
        // Step 2 b: Search in the right (decreasing) half
        int p2 = decreasingBS(a, peak + 1, n - 1, k);

        if (p1 != -1) ans.pb(p1 + 1); // Convert to 1-based index
        if (p2 != -1) ans.pb(p2 + 1);

        sort(all(ans)); // Sort positions in ascending order

        for (int pos : ans) cout << pos << " ";
        cout << nl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << fixed << setprecision(10);
    
    // Multi-test case support (commented out for this demo)
    int TC = 1;
    cin >> TC;
    while (TC--) solve();
    
    solve();
    return 0;
}

