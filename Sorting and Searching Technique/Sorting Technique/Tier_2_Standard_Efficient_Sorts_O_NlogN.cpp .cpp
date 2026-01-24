/*
Author: Sarvan.DP.GrandMaster
Created : 2026-01-09 00:19:56
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

/**
 * Algorithm 1 : Merge Sort (Divide & Conquer)
 *
 * Core Idea:
 * - Recursively divide the array into two halves
 * - Sort each half
 * - Merge the two sorted halves into one
 *
 * Why Merge Sort is Important:
 * - Guaranteed O(N log N) time complexity
 * - Stable sorting algorithm
 * - Very strong foundation for advanced sorting & DP concepts
 *
 * Time Complexity:
 * - Best Case    : O(N log N)
 * - Average Case : O(N log N)
 * - Worst Case   : O(N log N)
 *
 * Space Complexity:
 * - O(N) extra space (temporary array during merge)
 *
 * NOTE:
 * This is a BEGINNER-SAFE implementation.
 * Future optimizations:
 * - Early-exit if already sorted
 * - Half-copy merge strategy
 * - Iterative merge sort
 */
void merge(vec<int>& arr, int st, int mid, int en) {
    // Temporary array to store merged result
    vec<int> temp;
    int i = st;       // Pointer for left subarray
    int j = mid + 1;  // Pointer for right subarray

    // Merge both halves while elements remain in both
    while (i <= mid && j <= en) {
        if (arr[i] <= arr[j]) {
            temp.pb(arr[i]);   // Take from left
            i++;
        } else {
            temp.pb(arr[j]);   // Take from right
            j++;
        }
    }

    // Copy remaining elements from LEFT half (if any)
    while (i <= mid) {
        temp.pb(arr[i]);
        i++;
    }
    // Copy remaining elements from RIGHT half (if any)
    while (j <= en) {
        temp.pb(arr[j]);
        j++;
    }
    // Copy merged result back to original array
    // Important: write starts from index 'st'
    for (int idx = 0; idx < temp.size(); idx++) {
        arr[st + idx] = temp[idx];
    }
}
void mergeSortAlgo(vec<int>& arr, int st, int en) {
    // BASE CASE:
    // When there is only one element (or none), stop recursion
    if (st >= en) return;

    int mid = st + (en - st) / 2;  // STEP 1: Calculate middle index safely
    mergeSortAlgo(arr, st, mid); // STEP 2: Sort left half
    mergeSortAlgo(arr, mid + 1, en);  // STEP 3: Sort right half
    merge(arr, st, mid, en);  // STEP 4: Merge both sorted halves
}

/**
 * Algorithm : Optimized Merge Sort (Divide & Conquer)
 *
 * Optimization Summary:
 * 1. Early-Exit Optimization:
 *    - If the maximum element of the left subarray is <=
 *      the minimum element of the right subarray,
 *      the range is already sorted.
 *    - Skips the merge step entirely.
 *
 * 2. Half-Copy Merge Strategy:
 *    - Only the LEFT subarray is copied into a temporary buffer.
 *    - The RIGHT subarray remains in the original array.
 *    - This reduces memory writes and improves cache efficiency.
 *
 * 3. No Right-Subarray Copy Back:
 *    - If the left subarray finishes first, the remaining
 *      right elements are already in correct positions.
 *    - Eliminates an unnecessary loop found in naive merge.
 *
 * Time Complexity:
 * - Best Case    : O(N)    (Already sorted input; all merge calls exit early)
 * - Average Case : O(N log N)
 * - Worst Case   : O(N log N)
 *
 * Space Complexity:
 * - O(N) auxiliary space (single reusable temp buffer)
 * - O(log N) recursion stack
 *
 * Educational Note:
 * - This is an optimized, non-trivial merge sort
 * - Requires careful pointer and invariant management
 * - Not recommended as a first-time learning implementation
 */

void mergeOptimize(vec<int>& arr, vec<int>& temp, int st, int mid, int en){
    // Optimization 1: Copy ONLY Left Half to temp
    int n1 = mid - st + 1;
    for (int i = 0; i < n1; i++){
        temp[i] = arr[i + st];
    }

    int i = 0;           // Pointer for temp (Left Part)
    int j = mid + 1;     // Pointer for arr (Right Part)
    int k = st;          // Write Pointer for arr

    // Compare temp[i] (Left) vs arr[j] (Right)
    while (i < n1 && j <= en){
        if (temp[i] <= arr[j]){
            arr[k++] = temp[i++];
        } else{
            arr[k++] = arr[j++];
        }
    }

    // Optimization 2: Copy remaining elements from temp (Left Part)
    while (i < n1){
        arr[k++] = temp[i++];
    }
}
void mergeSortAlgoOptimize(vec<int>& arr, vec<int>& temp, int st, int en) {
    if (st >= en) return;

    int mid = st + (en - st) / 2;

    mergeSortAlgoOptimize(arr, temp, st, mid);
    mergeSortAlgoOptimize(arr, temp, mid + 1, en);

    // GM Optimization 3: Check if already sorted before merging
    if (arr[mid] <= arr[mid + 1]) return;

    mergeOptimize(arr, temp, st, mid, en);
}

// Algorithm 2 : Quick Sort (Divide & Conquer)
int partition(vec<int>& arr, const int st, const int en){
    int Idx = st - 1;  //  To make place for element smaller than pivot
    int pivot = arr[en];

    for (int j = st; j < en; j++){
        if (arr[j] <= pivot){
            Idx++;
            swap(arr[j], arr[Idx]);
        }
    }

    // Place pivot in its correct position
    Idx++;
    swap(arr[en],arr[Idx]);

    return Idx;
}

void QuickSort(vec<int>& arr, const int st, const int en){
    if (st < en){
        int pivotIdx = partition(arr, st, en);

        QuickSort(arr, st, pivotIdx - 1); // Left Part
        QuickSort(arr, pivotIdx + 1, en); // Right Part
    }
}

/**
 * GM Level Randomized Quick Sort
 * Logic: Uses Divide & Conquer.
 * Critical Optimization: Picks a RANDOM pivot to destroy worst-case patterns.
 * * * Time Complexity:
 * - Average Case: O(N log N) [Pivot splits array roughly in half]
 * - Worst Case: O(N^2) [Extremely rare, probability is 1 / N!]
 * * * Space Complexity:
 * - O(log N) Stack space (Average)
 * - O(N) Stack space (Worst case without tail-call optimization)
 */

// Helper: Generates random number between [l, r]
int getRandom(int l, int r) {
    uniform_int_distribution<int> dist(l, r);
    return dist(rng);
}

// Standard Lomuto Partition
int partitionOptimized(vector<int>& arr, int st, int en) {
    int pivot = arr[en]; // Pivot is at the end
    int i = st - 1;      // Index for smaller elements

    for (int j = st; j < en; j++) {
        // If current element is smaller than pivot
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    // Place pivot in correct sorted position
    swap(arr[i + 1], arr[en]);
    return i + 1; // Return the pivot index
}

// GM Optimization: Randomized Partition wrapper
int randomizedPartition(vector<int>& arr, int st, int en) {
    // 1. Pick a random index between st and en
    int randomIdx = getRandom(st, en);

    // 2. Swap it with the end element to make it the pivot
    swap(arr[randomIdx], arr[en]);

    // 3. Call standard partition
    return partitionOptimized(arr, st, en);
}

void quickSortAlgo(vector<int>& arr, int st, int en) {
    // Base Case
    if (st >= en) return;

    // Step 1: Get pivot index using Randomized Partition
    int pivotIdx = randomizedPartition(arr, st, en);

    // Step 2: Recursively sort Left and Right parts
    quickSortAlgo(arr, st, pivotIdx - 1);
    quickSortAlgo(arr, pivotIdx + 1, en);
}

void solve() {
    int n; cin >> n;
    vec<int> arr(n); read(arr);

    vec<int> temp(n);

    cout << "Before Sort Array Print" << nl;
    for (auto val : arr) cout << val << " ";
    cout << nl;

    // mergeSortAlgo(arr, 0, n - 1);  // Beginner Level
    // mergeSortAlgoOptimize(arr, temp, 0, n - 1); // Optimized Merge Sort
    // cout << "After Sort Array Print" << nl;
    // for (int i = 0; i < n; i++){
    //     cout << arr[i] << (i == n - 1 ? "" : " ");
    // }
    cout << nl;

    cout << "<------------Quick Sort  ------------->" << nl;
    // QuickSort(arr, 0, n - 1);
    quickSortAlgo(arr, 0, n - 1) // Optimized Quick Sort
    cout << "After Sort Array Print" << nl;
    for (int i = 0; i < n; i++){
        cout << arr[i] << (i == n - 1 ? "" : " ");
    }
    cout << nl;
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

