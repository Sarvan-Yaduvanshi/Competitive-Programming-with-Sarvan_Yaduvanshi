/*
╔══════════════════════════════════════════════════════════════╗
║  02. RECURSION ON ARRAYS: Print, Sum, Max, Min, Search       ║
║  Level 1 — Recursion Fundamentals                            ║
╚══════════════════════════════════════════════════════════════╝

🎯 Problems:
   1. Print array elements recursively
   2. Sum of array
   3. Maximum element
   4. Minimum element
   5. Linear search (find element)
   6. Check if array is sorted
   7. Reverse an array recursively
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
template<class T> using vec = vector<T>;

constexpr i64 MOD = 1'000'000'007LL;

#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define nl '\n'

template<class T>
void read(vec<T> &v) {
    for (auto &x : v) cin >> x;
}

// ═══════════════════════════════════════════════════════════
// 1️⃣ PRINT ARRAY RECURSIVELY
// ═══════════════════════════════════════════════════════════
/*
   Pattern: Process element at index i, then recurse for i+1
   Base case: i == n (out of bounds)

   Time: O(n), Space: O(n) stack
*/
void printArray(vec<int>& arr, int i) {
    if (i == sz(arr)) return;       // Base case
    cout << arr[i] << " ";           // Process current
    printArray(arr, i + 1);          // Recurse for rest
}

// Print in reverse (head recursion)
void printArrayReverse(vec<int>& arr, int i) {
    if (i == sz(arr)) return;
    printArrayReverse(arr, i + 1);   // Recurse FIRST
    cout << arr[i] << " ";           // Print AFTER (reverse!)
}


// ═══════════════════════════════════════════════════════════
// 2️⃣ SUM OF ARRAY
// ═══════════════════════════════════════════════════════════
/*
   Recurrence: sum(arr, i) = arr[i] + sum(arr, i+1)
   Base case:  sum(arr, n) = 0 (empty remaining = 0)

   Time: O(n), Space: O(n)
*/
i64 sumArray(vec<int>& arr, int i) {
    if (i == sz(arr)) return 0;                  // Base case
    return (i64)arr[i] + sumArray(arr, i + 1);   // Current + rest
}


// ═══════════════════════════════════════════════════════════
// 3️⃣ MAXIMUM ELEMENT
// ═══════════════════════════════════════════════════════════
/*
   Recurrence: maxEl(arr, i) = max(arr[i], maxEl(arr, i+1))
   Base case:  maxEl(arr, n-1) = arr[n-1] (only one element left)

   🧠 KEY INSIGHT: "Trust" that maxEl(arr, i+1) gives correct max
                    of arr[i+1..n-1]. Then just compare with arr[i].
*/
int maxElement(vec<int>& arr, int i) {
    if (i == sz(arr) - 1) return arr[i];  // Last element
    return max(arr[i], maxElement(arr, i + 1));
}


// ═══════════════════════════════════════════════════════════
// 4️⃣ MINIMUM ELEMENT
// ═══════════════════════════════════════════════════════════
int minElement(vec<int>& arr, int i) {
    if (i == sz(arr) - 1) return arr[i];
    return min(arr[i], minElement(arr, i + 1));
}


// ═══════════════════════════════════════════════════════════
// 5️⃣ LINEAR SEARCH (Recursive)
// ═══════════════════════════════════════════════════════════
/*
   Find first index of target in arr[i..n-1]
   Returns -1 if not found

   Time: O(n), Space: O(n)
*/
int linearSearch(vec<int>& arr, int i, int target) {
    if (i == sz(arr)) return -1;          // Not found
    if (arr[i] == target) return i;        // Found!
    return linearSearch(arr, i + 1, target);
}

// Find ALL indices of target (store in result)
void findAll(vec<int>& arr, int i, int target, vec<int>& result) {
    if (i == sz(arr)) return;
    if (arr[i] == target) result.push_back(i);
    findAll(arr, i + 1, target, result);
}


// ═══════════════════════════════════════════════════════════
// 6️⃣ CHECK IF ARRAY IS SORTED (Non-decreasing)
// ═══════════════════════════════════════════════════════════
/*
   isSorted(arr, i): checks if arr[i..n-1] is sorted
   Base case: only 1 or 0 elements left → true
   Recursive: arr[i] <= arr[i+1] AND isSorted(arr, i+1)
*/
bool isSorted(vec<int>& arr, int i) {
    if (i >= sz(arr) - 1) return true;     // 0 or 1 element
    if (arr[i] > arr[i + 1]) return false;  // Violation found
    return isSorted(arr, i + 1);            // Check rest
}


// ═══════════════════════════════════════════════════════════
// 7️⃣ REVERSE AN ARRAY (Two-pointer recursion)
// ═══════════════════════════════════════════════════════════
/*
   Swap arr[left] and arr[right], then recurse inward
   Base case: left >= right

   Time: O(n), Space: O(n) stack (can be done O(1) iteratively)

   🧠 This is the "TWO-POINTER RECURSION" pattern:
      Two pointers moving toward each other
*/
void reverseArray(vec<int>& arr, int left, int right) {
    if (left >= right) return;
    swap(arr[left], arr[right]);
    reverseArray(arr, left + 1, right - 1);
}


// ═══════════════════════════════════════════════════════════
// 🧪 TEST ALL FUNCTIONS
// ═══════════════════════════════════════════════════════════

void solve() {
    vec<int> arr = {5, 3, 8, 1, 9, 2, 7};
    int n = sz(arr);

    cout << "Array: ";
    printArray(arr, 0);
    cout << nl;

    cout << "Reverse print: ";
    printArrayReverse(arr, 0);
    cout << nl;

    cout << "Sum: " << sumArray(arr, 0) << nl;
    cout << "Max: " << maxElement(arr, 0) << nl;
    cout << "Min: " << minElement(arr, 0) << nl;

    cout << "Search 8: index = " << linearSearch(arr, 0, 8) << nl;
    cout << "Search 99: index = " << linearSearch(arr, 0, 99) << nl;

    cout << "Is sorted? " << (isSorted(arr, 0) ? "YES" : "NO") << nl;

    vec<int> sorted = {1, 2, 3, 4, 5};
    cout << "Is {1,2,3,4,5} sorted? " << (isSorted(sorted, 0) ? "YES" : "NO") << nl;

    reverseArray(arr, 0, n - 1);
    cout << "After reverse: ";
    printArray(arr, 0);
    cout << nl;

    // Find all occurrences
    vec<int> arr2 = {1, 3, 5, 3, 7, 3};
    vec<int> indices;
    findAll(arr2, 0, 3, indices);
    cout << "All indices of 3 in {1,3,5,3,7,3}: ";
    for (int idx : indices) cout << idx << " ";
    cout << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int TC = 1;
    while (TC--) solve();

    return 0;
}

