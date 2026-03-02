/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-28 10:30:00
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
//  MODULE 03: TRAVERSAL PATTERNS
//  Level: ⭐ Beginner
//  Topics: Forward, reverse, zigzag, even/odd, iterator, for_each, transform
// =============================================================================

// Helper: Print array with label
void printArr(const string& label, const vec<int>& arr) {
    cout << label << ": ";
    for (int i = 0; i < sz(arr); i++) {
        if (i > 0) cout << ' ';
        cout << arr[i];
    }
    cout << nl;
}

// -------------------------------------------------------------
// 1. FORWARD TRAVERSAL (Left to Right)
// -------------------------------------------------------------
// The most basic and most common traversal.
// Time: O(N), Space: O(1)

void traversal_forward(const vec<int>& arr) {
    cout << "--- Forward Traversal ---" << nl;

    // Method 1: Classic index-based (MOST COMMON in CP)
    cout << "Index-based: ";
    for (int i = 0; i < sz(arr); i++) {
        cout << arr[i] << " ";
    }
    cout << nl;

    // Method 2: Range-based for (C++11) — clean & readable
    cout << "Range-based: ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << nl;

    // Method 3: Range-based with const reference (avoids copying complex types)
    // GM Tip: Always use `const auto&` for non-primitive types
    cout << "Const ref:   ";
    for (const auto& x : arr) {
        cout << x << " ";
    }
    cout << nl;

    // Method 4: Iterator-based
    cout << "Iterator:    ";
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        cout << *it << " ";
    }
    cout << nl;

    // Method 5: Pointer arithmetic (C-style, rarely used in modern CP)
    cout << "Pointer:     ";
    for (const int* p = arr.data(); p < arr.data() + arr.size(); ++p) {
        cout << *p << " ";
    }
    cout << nl;
}

// -------------------------------------------------------------
// 2. REVERSE TRAVERSAL (Right to Left)
// -------------------------------------------------------------
// Used in: finding leaders, right-to-left DP, suffix computations

void traversal_reverse(const vec<int>& arr) {
    cout << nl << "--- Reverse Traversal ---" << nl;

    // Method 1: Reverse index loop (MOST COMMON)
    cout << "Index (i--):    ";
    for (int i = sz(arr) - 1; i >= 0; i--) {
        cout << arr[i] << " ";
    }
    cout << nl;

    // Method 2: Reverse iterators
    cout << "Reverse iter:   ";
    for (auto it = arr.rbegin(); it != arr.rend(); ++it) {
        cout << *it << " ";
    }
    cout << nl;

    // Method 3: Using rall macro
    cout << "rall() range:   ";
    for (auto it = rall(arr).first; it != rall(arr).second; ++it) {
        // Note: rall expands to rbegin(), rend()
        // But this is awkward; prefer Method 1 or 2
    }
    // In practice, just use the index loop or reverse iterators
}

// -------------------------------------------------------------
// 3. EVEN / ODD INDEX TRAVERSAL
// -------------------------------------------------------------
// Used in: problems with alternating patterns, bit manipulation indexing

void traversal_even_odd(const vec<int>& arr) {
    cout << nl << "--- Even/Odd Index Traversal ---" << nl;

    // Even indices: 0, 2, 4, ...
    cout << "Even indices: ";
    for (int i = 0; i < sz(arr); i += 2) {
        cout << arr[i] << " ";
    }
    cout << nl;

    // Odd indices: 1, 3, 5, ...
    cout << "Odd indices:  ";
    for (int i = 1; i < sz(arr); i += 2) {
        cout << arr[i] << " ";
    }
    cout << nl;
}

// -------------------------------------------------------------
// 4. STEP / SKIP TRAVERSAL
// -------------------------------------------------------------
// Used in: sampling, every K-th element, stride patterns

void traversal_step(const vec<int>& arr, int step) {
    cout << nl << "--- Step Traversal (step=" << step << ") ---" << nl;

    cout << "Every " << step << "-th: ";
    for (int i = 0; i < sz(arr); i += step) {
        cout << arr[i] << " ";
    }
    cout << nl;
}

// -------------------------------------------------------------
// 5. ZIGZAG / SNAKE TRAVERSAL
// -------------------------------------------------------------
// Used in: matrix problems, wave-sort, rearrangement

void traversal_zigzag(const vec<int>& arr) {
    cout << nl << "--- Zigzag Traversal ---" << nl;
    // For 1D: Print from left, then right, alternating halves
    // More commonly used in 2D matrices (row zigzag)

    int n = sz(arr);
    int left = 0, right = n - 1;
    bool fromLeft = true;

    cout << "Zigzag: ";
    while (left <= right) {
        if (fromLeft) {
            cout << arr[left++] << " ";
        } else {
            cout << arr[right--] << " ";
        }
        fromLeft = !fromLeft;
    }
    cout << nl;
    // For {1,2,3,4,5}: Output: 1 5 2 4 3
}

// -------------------------------------------------------------
// 6. TWO-POINTER TRAVERSAL (Inward Walk)
// -------------------------------------------------------------
// Used in: palindrome check, two-sum, container with most water

void traversal_two_pointer(const vec<int>& arr) {
    cout << nl << "--- Two-Pointer Inward Traversal ---" << nl;

    int left = 0, right = sz(arr) - 1;

    cout << "Pairs (L,R): ";
    while (left < right) {
        cout << "(" << arr[left] << "," << arr[right] << ") ";
        left++;
        right--;
    }
    // If odd length, middle element is unpaired
    if (left == right) {
        cout << "Middle: " << arr[left];
    }
    cout << nl;
}

// -------------------------------------------------------------
// 7. PARALLEL TRAVERSAL (Two Arrays)
// -------------------------------------------------------------
// Used in: merge operations, comparing arrays, zip-like patterns

void traversal_parallel(const vec<int>& a, const vec<int>& b) {
    cout << nl << "--- Parallel Traversal ---" << nl;

    int i = 0, j = 0;

    // Method 1: Traverse both simultaneously
    cout << "Simultaneous: ";
    int minLen = min(sz(a), sz(b));
    for (int k = 0; k < minLen; k++) {
        cout << "(" << a[k] << "," << b[k] << ") ";
    }
    cout << nl;

    // Method 2: Merge-style (both sorted, advance smaller)
    cout << "Merge-style: ";
    i = 0; j = 0;
    while (i < sz(a) && j < sz(b)) {
        if (a[i] <= b[j]) {
            cout << a[i++] << " ";
        } else {
            cout << b[j++] << " ";
        }
    }
    while (i < sz(a)) cout << a[i++] << " ";
    while (j < sz(b)) cout << b[j++] << " ";
    cout << nl;
}

// -------------------------------------------------------------
// 8. STL ALGORITHM-BASED TRAVERSAL
// -------------------------------------------------------------

void traversal_stl(vec<int>& arr) {
    cout << nl << "--- STL Traversal ---" << nl;

    // for_each: Apply function to each element
    cout << "for_each (print): ";
    for_each(all(arr), [](int x) { cout << x << " "; });
    cout << nl;

    // for_each (modify): Double each element
    for_each(all(arr), [](int& x) { x *= 2; });
    cout << "After doubling: ";
    for (int x : arr) cout << x << " ";
    cout << nl;

    // Restore
    for_each(all(arr), [](int& x) { x /= 2; });

    // transform: Apply function and store result
    vec<int> squared(sz(arr));
    transform(all(arr), squared.begin(), [](int x) { return x * x; });
    cout << "Squared: ";
    for (int x : squared) cout << x << " ";
    cout << nl;

    // count_if: Count elements matching predicate
    int evenCount = count_if(all(arr), [](int x) { return x % 2 == 0; });
    cout << "Even count: " << evenCount << nl;

    // any_of / all_of / none_of
    bool hasNegative = any_of(all(arr), [](int x) { return x < 0; });
    bool allPositive = all_of(all(arr), [](int x) { return x > 0; });
    cout << "Has negative: " << hasNegative << ", All positive: " << allPositive << nl;

    // find_if: Find first element matching predicate
    auto it = find_if(all(arr), [](int x) { return x > 3; });
    if (it != arr.end()) {
        cout << "First > 3: " << *it << " at index " << (it - arr.begin()) << nl;
    }
}

// -------------------------------------------------------------
// 9. TRAVERSAL WITH INDEX TRACKING
// -------------------------------------------------------------
// GM Tip: Many problems need both the value AND the index.

void traversal_with_index(const vec<int>& arr) {
    cout << nl << "--- Traversal with Index ---" << nl;

    // Method 1: Classic (always works)
    for (int i = 0; i < sz(arr); i++) {
        // Use arr[i] for value, i for index
    }

    // Method 2: Using enumerate-style (manual in C++)
    cout << "Enumerate: ";
    {
        int idx = 0;
        for (int x : arr) {
            cout << "[" << idx << "]=" << x << " ";
            idx++;
        }
    }
    cout << nl;

    // Method 3: Create index array and sort by value
    // (Very useful pattern for problems)
    vec<int> indices(sz(arr));
    iota(all(indices), 0); // {0, 1, 2, ..., n-1}
    sort(all(indices), [&](int a, int b) {
        return arr[a] < arr[b]; // Sort indices by corresponding values
    });
    cout << "Sorted indices (by value): ";
    for (int i : indices) cout << i << " ";
    cout << nl;
}

// -------------------------------------------------------------
// 10. CACHE-FRIENDLY TRAVERSAL (GM Performance Insight)
// -------------------------------------------------------------
/*
 * CPU caches work in CACHE LINES (64 bytes = 16 ints).
 * Sequential access (forward traversal) is ~100x faster than random access
 * because of prefetching.
 *
 * ┌──────────────┬─────────────────┬──────────────┐
 * │ Access       │ Cache Behavior  │ Performance  │
 * ├──────────────┼─────────────────┼──────────────┤
 * │ Sequential   │ Perfect prefetch│ ~10 GB/s     │
 * │ Stride (skip)│ Some misses     │ ~2-5 GB/s    │
 * │ Random       │ Constant misses │ ~0.1 GB/s    │
 * └──────────────┴─────────────────┴──────────────┘
 *
 * GM Implication:
 *   - Row-major 2D traversal: for(i) for(j) grid[i][j]  ✓ Fast
 *   - Column-major:           for(j) for(i) grid[i][j]  ✗ Slow
 *   - This matters for N > 10^4 in tight TL problems
 */

void solve() {
    cout << "╔════════════════════════════════════════╗" << nl;
    cout << "║  MODULE 03: Traversal Patterns         ║" << nl;
    cout << "╚════════════════════════════════════════╝" << nl;

    vec<int> arr = {1, 2, 3, 4, 5, 6, 7};
    vec<int> a = {1, 3, 5, 7};
    vec<int> b = {2, 4, 6, 8, 10};

    traversal_forward(arr);
    traversal_reverse(arr);
    traversal_even_odd(arr);
    traversal_step(arr, 3);
    traversal_zigzag(arr);
    traversal_two_pointer(arr);
    traversal_parallel(a, b);
    traversal_stl(arr);
    traversal_with_index(arr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    solve();

    return 0;
}

