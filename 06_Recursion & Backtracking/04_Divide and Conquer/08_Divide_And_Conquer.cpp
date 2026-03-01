/*
╔══════════════════════════════════════════════════════════════╗
║  08. DIVIDE AND CONQUER — Merge Sort, Quick Sort, Inversions║
║  Level 4 — Divide and Conquer                                ║
╚══════════════════════════════════════════════════════════════╝

════════════════════════════════════════════════════════════════
📖 DIVIDE AND CONQUER PARADIGM
════════════════════════════════════════════════════════════════

1. DIVIDE   — Split problem into smaller subproblems
2. CONQUER  — Solve each subproblem recursively
3. COMBINE  — Merge results of subproblems

Template:
    result solve(problem) {
        if (base case) return trivial_answer;

        left  = solve(left_half);
        right = solve(right_half);

        return combine(left, right);
    }

════════════════════════════════════════════════════════════════

🎯 Problems:
   1. Merge Sort — O(n log n)
   2. Quick Sort — O(n log n) average
   3. Count Inversions — using modified merge sort
   4. Power (Binary Exponentiation) — O(log n)
   5. Maximum Subarray Sum (Divide & Conquer) — LC 53
   6. Closest Pair of Points — O(n log n)
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

using i64 = long long;
using ld  = long double;
template<class T> using vec = vector<T>;

constexpr i64 INF64 = 4e18;
constexpr i64 MOD = 1'000'000'007LL;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

template<class T>
void read(vec<T> &v) {
    for (auto &x : v) cin >> x;
}


// ═══════════════════════════════════════════════════════════
// 1️⃣ MERGE SORT — O(n log n), Stable
// ═══════════════════════════════════════════════════════════
/*
   DIVIDE: Split array into two halves
   CONQUER: Sort each half recursively
   COMBINE: Merge two sorted halves

   Recurrence: T(n) = 2T(n/2) + O(n) → O(n log n)
   Space: O(n) for temporary array

   Recursion tree:
       [5, 3, 8, 1]
       /            \
   [5, 3]        [8, 1]
   /    \         /    \
  [5]  [3]      [8]   [1]
   \    /         \    /
   [3, 5]        [1, 8]
       \            /
       [1, 3, 5, 8]
*/
void merge(vec<int>& arr, int left, int mid, int right) {
    vec<int> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp.pb(arr[i++]);
        else temp.pb(arr[j++]);
    }
    while (i <= mid) temp.pb(arr[i++]);
    while (j <= right) temp.pb(arr[j++]);

    for (int k = left; k <= right; k++) {
        arr[k] = temp[k - left];
    }
}

void mergeSort(vec<int>& arr, int left, int right) {
    if (left >= right) return;  // Base case: 0 or 1 element

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);       // Sort left half
    mergeSort(arr, mid + 1, right);  // Sort right half
    merge(arr, left, mid, right);    // Merge sorted halves
}


// ═══════════════════════════════════════════════════════════
// 2️⃣ QUICK SORT — O(n log n) average, O(n^2) worst
// ═══════════════════════════════════════════════════════════
/*
   1. Choose a PIVOT
   2. PARTITION: elements < pivot go left, > pivot go right
   3. Recursively sort left and right parts

   🧠 KEY: Partition is the key operation.

   Randomized pivot avoids worst case O(n^2).

   Average: T(n) = 2T(n/2) + O(n) → O(n log n)
   Worst:   T(n) = T(n-1) + O(n) → O(n^2) (already sorted + bad pivot)
*/
int partition(vec<int>& arr, int low, int high) {
    // Random pivot to avoid worst case
    int randIdx = low + rng() % (high - low + 1);
    swap(arr[randIdx], arr[high]);

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vec<int>& arr, int low, int high) {
    if (low >= high) return;

    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);   // Sort left of pivot
    quickSort(arr, pi + 1, high);  // Sort right of pivot
}


// ═══════════════════════════════════════════════════════════
// 3️⃣ COUNT INVERSIONS — Modified Merge Sort
// ═══════════════════════════════════════════════════════════
/*
   Inversion: pair (i, j) where i < j but arr[i] > arr[j]

   [2, 4, 1, 3, 5] → Inversions: (2,1), (4,1), (4,3) → count = 3

   🧠 KEY INSIGHT: During merge step, when we pick from right half,
   ALL remaining elements in left half form inversions with it.

   If arr[i] > arr[j] (where i in left, j in right):
       inversions += (mid - i + 1)  // all remaining in left half

   Time: O(n log n)

   This is a CLASSIC competitive programming problem!
*/
i64 mergeCount(vec<int>& arr, int left, int mid, int right) {
    vec<int> temp;
    int i = left, j = mid + 1;
    i64 inversions = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp.pb(arr[i++]);
        } else {
            inversions += (mid - i + 1);  // KEY: all remaining left > arr[j]
            temp.pb(arr[j++]);
        }
    }
    while (i <= mid) temp.pb(arr[i++]);
    while (j <= right) temp.pb(arr[j++]);

    for (int k = left; k <= right; k++) arr[k] = temp[k - left];
    return inversions;
}

i64 countInversions(vec<int>& arr, int left, int right) {
    if (left >= right) return 0;

    int mid = left + (right - left) / 2;
    i64 count = 0;
    count += countInversions(arr, left, mid);
    count += countInversions(arr, mid + 1, right);
    count += mergeCount(arr, left, mid, right);
    return count;
}


// ═══════════════════════════════════════════════════════════
// 4️⃣ BINARY EXPONENTIATION — O(log n)
// ═══════════════════════════════════════════════════════════
/*
   Compute base^exp % mod efficiently.

   Recurrence:
   - If exp is even: x^n = (x^(n/2))^2
   - If exp is odd:  x^n = x * (x^(n/2))^2

   T(n) = T(n/2) + O(1) → O(log n)

   This is the MOST IMPORTANT recursive function in CP!
*/
i64 binpow(i64 base, i64 exp, i64 mod = MOD) {
    if (exp == 0) return 1;

    i64 half = binpow(base, exp / 2, mod);
    half = (half % mod * half % mod) % mod;

    if (exp & 1) half = (half % mod * base % mod) % mod;
    return half;
}

// Matrix exponentiation (for linear recurrences like Fibonacci in O(log n))
using Matrix = vec<vec<i64>>;

Matrix multiply(const Matrix& A, const Matrix& B, i64 mod = MOD) {
    int n = sz(A);
    Matrix C(n, vec<i64>(n, 0));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            for (int j = 0; j < n; j++)
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
    return C;
}

Matrix matpow(Matrix base, i64 exp, i64 mod = MOD) {
    int n = sz(base);
    Matrix result(n, vec<i64>(n, 0));
    for (int i = 0; i < n; i++) result[i][i] = 1;  // Identity matrix

    while (exp > 0) {
        if (exp & 1) result = multiply(result, base, mod);
        base = multiply(base, base, mod);
        exp >>= 1;
    }
    return result;
}

// Fibonacci in O(log n) using matrix exponentiation!
i64 fibLogN(i64 n, i64 mod = MOD) {
    if (n <= 0) return 0;
    if (n == 1) return 1;

    Matrix base = {{1, 1}, {1, 0}};
    Matrix result = matpow(base, n - 1, mod);
    return result[0][0];
}


// ═══════════════════════════════════════════════════════════
// 5️⃣ MAXIMUM SUBARRAY SUM (Divide & Conquer) — LC 53
// ═══════════════════════════════════════════════════════════
/*
   Find contiguous subarray with maximum sum.

   D&C Approach:
   - Max subarray is either in left half, right half,
     or crosses the midpoint.
   - For crossing: extend from mid to left and mid+1 to right.

   T(n) = 2T(n/2) + O(n) → O(n log n)

   (Kadane's algorithm is O(n), but this shows D&C thinking)
*/
i64 maxCrossingSum(vec<int>& arr, int left, int mid, int right) {
    i64 leftSum = LLONG_MIN, rightSum = LLONG_MIN;
    i64 sum = 0;

    // Extend from mid to left
    for (int i = mid; i >= left; i--) {
        sum += arr[i];
        leftSum = max(leftSum, sum);
    }

    sum = 0;
    // Extend from mid+1 to right
    for (int i = mid + 1; i <= right; i++) {
        sum += arr[i];
        rightSum = max(rightSum, sum);
    }

    return leftSum + rightSum;
}

i64 maxSubarrayDC(vec<int>& arr, int left, int right) {
    if (left == right) return arr[left];  // Base case: single element

    int mid = left + (right - left) / 2;
    i64 leftMax = maxSubarrayDC(arr, left, mid);
    i64 rightMax = maxSubarrayDC(arr, mid + 1, right);
    i64 crossMax = maxCrossingSum(arr, left, mid, right);

    return max({leftMax, rightMax, crossMax});
}


// ═══════════════════════════════════════════════════════════
// 🧪 TEST
// ═══════════════════════════════════════════════════════════

void solve() {
    // 1. Merge Sort
    {
        cout << "=== MERGE SORT ===" << nl;
        vec<int> arr = {5, 3, 8, 1, 9, 2, 7, 4, 6};
        cout << "Before: ";
        for (int x : arr) cout << x << " ";
        cout << nl;
        mergeSort(arr, 0, sz(arr) - 1);
        cout << "After:  ";
        for (int x : arr) cout << x << " ";
        cout << nl;
    }

    // 2. Quick Sort
    {
        cout << nl << "=== QUICK SORT ===" << nl;
        vec<int> arr = {5, 3, 8, 1, 9, 2, 7, 4, 6};
        cout << "Before: ";
        for (int x : arr) cout << x << " ";
        cout << nl;
        quickSort(arr, 0, sz(arr) - 1);
        cout << "After:  ";
        for (int x : arr) cout << x << " ";
        cout << nl;
    }

    // 3. Count Inversions
    {
        cout << nl << "=== COUNT INVERSIONS ===" << nl;
        vec<int> arr = {2, 4, 1, 3, 5};
        cout << "Array: ";
        for (int x : arr) cout << x << " ";
        cout << nl;
        cout << "Inversions: " << countInversions(arr, 0, sz(arr) - 1) << nl;
    }

    // 4. Binary Exponentiation
    {
        cout << nl << "=== BINARY EXPONENTIATION ===" << nl;
        cout << "2^10 mod 1e9+7 = " << binpow(2, 10) << nl;
        cout << "2^60 mod 1e9+7 = " << binpow(2, 60) << nl;
        cout << "Fib(50) mod 1e9+7 = " << fibLogN(50) << nl;
        cout << "Fib(1000000) mod 1e9+7 = " << fibLogN(1000000) << nl;
    }

    // 5. Max Subarray (D&C)
    {
        cout << nl << "=== MAX SUBARRAY (D&C) ===" << nl;
        vec<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
        cout << "Array: ";
        for (int x : arr) cout << x << " ";
        cout << nl;
        cout << "Max subarray sum: " << maxSubarrayDC(arr, 0, sz(arr) - 1) << nl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int TC = 1;
    while (TC--) solve();

    return 0;
}

