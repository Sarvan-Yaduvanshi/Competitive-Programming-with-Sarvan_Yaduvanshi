/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-28 10:00:00
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
#include <array>  // for std::array

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
//  MODULE 01: STATIC ARRAY & VECTOR BASICS
//  Level: ⭐ Beginner
//  Topics: C-style arrays, std::array, std::vector, initialization, 2D vectors
// =============================================================================

// -------------------------------------------------------------
// 1. C-STYLE ARRAY (Stack allocated, fixed size)
// -------------------------------------------------------------
// GM Note: C-style arrays have NO bounds checking → undefined behavior if
//          you access out of range. Use in CP only for global arrays.
//
// Declaration:  int arr[100];          // uninitialized (garbage values!)
//               int arr[100] = {};     // zero-initialized
//               int arr[] = {1,2,3};   // size deduced as 3
//
// GLOBAL vs LOCAL:
//   Global: automatically zero-initialized, can be up to ~5×10^8 bytes
//   Local:  stack limit ~1-8 MB, so max ~250,000 ints locally
//
// GM Tip for CF/CSES: Declare large arrays GLOBALLY to avoid stack overflow.

void demo_c_style_array() {
    cout << "=== C-Style Array ===" << nl;

    // Method 1: Uninitialized (DON'T rely on values)
    int a[5];
    // a[0]..a[4] contain garbage unless assigned

    // Method 2: Zero-initialized
    int b[5] = {};  // All zeros
    for (int i = 0; i < 5; i++) cout << b[i] << " ";
    cout << nl; // Output: 0 0 0 0 0

    // Method 3: Partially initialized (rest are 0)
    int c[5] = {1, 2, 3};
    for (int i = 0; i < 5; i++) cout << c[i] << " ";
    cout << nl; // Output: 1 2 3 0 0

    // Method 4: Size deduced from initializer
    int d[] = {10, 20, 30, 40};
    int n = sizeof(d) / sizeof(d[0]); // GM: This gives array size for C-arrays
    cout << "Size: " << n << nl; // Output: Size: 4

    // Method 5: Using memset (ONLY safe for 0 and -1)
    int e[5];
    memset(e, 0, sizeof(e));   // All zeros
    memset(e, -1, sizeof(e));  // All -1 (because -1 in binary is all 1s)
    // WARNING: memset(e, 1, ...) does NOT set to 1! It sets each BYTE to 1.
    for (int i = 0; i < 5; i++) cout << e[i] << " ";
    cout << nl; // Output: -1 -1 -1 -1 -1

    // Method 6: fill (safe for any value)
    int f[5];
    fill(f, f + 5, 42);
    for (int i = 0; i < 5; i++) cout << f[i] << " ";
    cout << nl; // Output: 42 42 42 42 42
}

// -------------------------------------------------------------
// 2. STD::ARRAY (C++11, Stack allocated, fixed size, bounds-safe)
// -------------------------------------------------------------
// GM Note: std::array is a thin wrapper over C-array.
//          Same performance, but with .size(), .begin(), .end(), .at()
//          .at() does bounds checking (throws exception), [] does not.
//
// When to use: When size is known at COMPILE TIME and you want STL compatibility.

void demo_std_array() {
    cout << nl << "=== std::array ===" << nl;

    // Declaration
    array<int, 5> arr = {1, 2, 3, 4, 5};

    // Size (always constexpr)
    cout << "Size: " << arr.size() << nl;

    // Access
    cout << "arr[0] = " << arr[0] << nl;      // No bounds check
    cout << "arr.at(0) = " << arr.at(0) << nl; // Bounds check (throws out_of_range)

    // Fill
    array<int, 5> zeros;
    zeros.fill(0);

    // Works with STL algorithms
    sort(arr.begin(), arr.end());
    auto it = find(arr.begin(), arr.end(), 3);
    if (it != arr.end()) cout << "Found 3 at index: " << (it - arr.begin()) << nl;

    // Structured bindings (C++17) for small arrays
    auto [a, b, c, d, e] = arr;
    cout << a << " " << b << " " << c << " " << d << " " << e << nl;
}

// -------------------------------------------------------------
// 3. STD::VECTOR (Heap allocated, dynamic size)
// -------------------------------------------------------------
// GM Note: This is THE data structure for CP. 99% of the time, use vector.
//
// Internal: Manages a dynamic array on the heap.
//           Doubles capacity when full → amortized O(1) push_back.
//
// KEY CONCEPTS:
//   size()     = number of elements currently stored
//   capacity() = allocated memory (always >= size)
//   reserve(n) = pre-allocate for n elements (avoids reallocations)
//   shrink_to_fit() = reduce capacity to match size (rarely needed)
//   resize(n)  = change size (adds default elements or truncates)

void demo_vector_basics() {
    cout << nl << "=== std::vector Basics ===" << nl;

    // --- Construction Patterns ---

    // 1. Empty
    vec<int> v1;
    cout << "Empty: size=" << v1.size() << " cap=" << v1.capacity() << nl;

    // 2. N elements, all zero
    vec<int> v2(5);
    cout << "vec(5): ";
    for (int x : v2) cout << x << " ";
    cout << nl; // 0 0 0 0 0

    // 3. N elements, all val
    vec<int> v3(5, 42);
    cout << "vec(5,42): ";
    for (int x : v3) cout << x << " ";
    cout << nl; // 42 42 42 42 42

    // 4. Initializer list
    vec<int> v4 = {1, 2, 3, 4, 5};

    // 5. From another container (range constructor)
    vec<int> v5(v4.begin(), v4.begin() + 3); // {1, 2, 3}

    // 6. Copy constructor
    vec<int> v6 = v4; // Deep copy

    // 7. Move constructor (C++11) — steals the memory, O(1)
    vec<int> v7 = std::move(v6); // v6 is now empty!
    cout << "After move: v6.size()=" << v6.size() << " v7.size()=" << v7.size() << nl;

    // --- Size vs Capacity ---
    vec<int> v;
    cout << nl << "Growth pattern:" << nl;
    for (int i = 0; i < 20; i++) {
        v.pb(i);
        cout << "size=" << v.size() << " cap=" << v.capacity() << nl;
    }
    // Typically: 1,2,4,8,16,32... (doubles each time)

    // --- Reserve (Pre-allocate) ---
    // GM Tip: If you know the final size, RESERVE to avoid reallocations.
    //         This can be 2-3x faster for large N (10^6+).
    vec<int> fast;
    fast.reserve(1000000); // Allocate space for 1M elements
    // Now push_back won't cause any reallocation until 1M elements

    // --- Resize ---
    vec<int> r(3, 10); // {10, 10, 10}
    r.resize(5);       // {10, 10, 10, 0, 0}    — new elements are 0
    r.resize(7, 99);   // {10, 10, 10, 0, 0, 99, 99} — new elements are 99
    r.resize(2);       // {10, 10}               — truncated

    // --- Shrink to Fit ---
    vec<int> s(100);
    s.resize(5);
    cout << nl << "Before shrink: cap=" << s.capacity() << nl; // 100
    s.shrink_to_fit();
    cout << "After shrink: cap=" << s.capacity() << nl;  // 5

    // --- Clear vs Assign ---
    vec<int> c = {1, 2, 3, 4, 5};
    c.clear();          // size=0, capacity unchanged
    c.assign(5, -1);    // {-1, -1, -1, -1, -1}
}

// -------------------------------------------------------------
// 4. PUSH_BACK vs EMPLACE_BACK
// -------------------------------------------------------------
// push_back(val)    → copies/moves val into vector
// emplace_back(args) → constructs element in-place (no copy)
//
// GM Note: For primitive types (int, long long), NO difference.
//          For complex types (pair, struct), emplace_back can be faster.

void demo_push_vs_emplace() {
    cout << nl << "=== push_back vs emplace_back ===" << nl;

    // For pairs:
    vec<pii> pairs;
    pairs.push_back({1, 2});      // Creates pair, then copies
    pairs.emplace_back(3, 4);     // Constructs pair directly in vector memory
    // Both work; emplace_back is marginally faster for complex types

    // For structs:
    struct Point { int x, y, z; };
    vec<Point> points;
    points.push_back({1, 2, 3});
    points.emplace_back(Point{4, 5, 6});

    cout << "Pairs: " << pairs[0].fi << "," << pairs[0].se << nl;
    cout << "Points: " << points[0].x << "," << points[0].y << nl;
}

// -------------------------------------------------------------
// 5. 2D VECTOR INITIALIZATION
// -------------------------------------------------------------
// GM Tip: 2D vectors are used in DP, grids, adjacency lists.
//         Know ALL initialization patterns.

void demo_2d_vector() {
    cout << nl << "=== 2D Vector Initialization ===" << nl;

    int n = 3, m = 4;

    // Method 1: N rows, M cols, all zeros
    vvec<int> grid1(n, vec<int>(m, 0));

    // Method 2: N rows, M cols, all -1 (common in DP memo)
    vvec<int> dp(n, vec<int>(m, -1));

    // Method 3: Initializer list
    vvec<int> grid2 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Method 4: Adjacency list (N+1 empty vectors, 1-indexed)
    int V = 5;
    vvec<int> adj(V + 1); // adj[1]..adj[V] are empty vectors

    // Method 5: Dynamic row sizes (jagged array)
    vvec<int> jagged(3);
    jagged[0] = {1, 2};
    jagged[1] = {3, 4, 5, 6};
    jagged[2] = {7};

    // Print 2D grid
    cout << "Grid:" << nl;
    for (auto& row : grid2) {
        for (int val : row) cout << val << " ";
        cout << nl;
    }
    // Output:
    // 1 2 3
    // 4 5 6
    // 7 8 9
}

// -------------------------------------------------------------
// 6. USEFUL VECTOR OPERATIONS (STL)
// -------------------------------------------------------------

void demo_vector_operations() {
    cout << nl << "=== Useful Vector Operations ===" << nl;

    vec<int> v = {5, 3, 1, 4, 2};

    // Sort (ascending)
    sort(all(v));
    // v = {1, 2, 3, 4, 5}

    // Sort (descending)
    sort(all(v), greater<int>());
    // v = {5, 4, 3, 2, 1}

    // Reverse
    reverse(all(v));
    // v = {1, 2, 3, 4, 5}

    // Sum of all elements
    i64 total = accumulate(all(v), 0LL); // GM: Use 0LL to avoid int overflow
    cout << "Sum: " << total << nl;

    // Min/Max element
    cout << "Min: " << *min_element(all(v)) << nl;
    cout << "Max: " << *max_element(all(v)) << nl;

    // Count occurrences
    v = {1, 2, 2, 3, 2, 4};
    cout << "Count of 2: " << count(all(v), 2) << nl; // 3

    // Remove duplicates (sort first!)
    sort(all(v));
    v.erase(unique(all(v)), v.end());
    // v = {1, 2, 3, 4}
    cout << "After unique: ";
    for (int x : v) cout << x << " ";
    cout << nl;

    // Iota (fill with 0, 1, 2, ...)
    vec<int> idx(5);
    iota(all(idx), 0); // {0, 1, 2, 3, 4}

    // Fill
    fill(all(v), 7); // All 7s

    // Swap two vectors (O(1))
    vec<int> a = {1, 2, 3}, b = {4, 5};
    swap(a, b); // a={4,5}, b={1,2,3}
}

// -------------------------------------------------------------
// 7. GLOBAL ARRAY vs VECTOR (GM-Level Decision Making)
// -------------------------------------------------------------
/*
 * ┌────────────────┬───────────────────────────────────┬──────────────────────────┐
 * │ Feature        │ Global C-Array                    │ std::vector              │
 * ├────────────────┼───────────────────────────────────┼──────────────────────────┤
 * │ Memory         │ BSS segment (up to ~500MB)        │ Heap (up to ~500MB)      │
 * │ Init           │ Auto zero-initialized             │ Must specify             │
 * │ Size           │ Fixed at compile time             │ Dynamic                  │
 * │ Speed          │ Slightly faster (no indirection)  │ Nearly identical         │
 * │ Bounds check   │ None                              │ .at() available          │
 * │ STL compat     │ Partial (pointer arithmetic)      │ Full                     │
 * │ CP Usage       │ When N is very large (10^7+)      │ Default choice           │
 * │ Cache          │ Excellent (contiguous)            │ Excellent (contiguous)   │
 * └────────────────┴───────────────────────────────────┴──────────────────────────┘
 *
 * GM Verdict: Use vector by default. Use global C-array only when:
 *   1. N > 10^6 and you need multiple arrays (heap allocation overhead)
 *   2. You need memset for fast re-initialization across test cases
 *   3. The problem has tight memory constraints
 */

void solve() {
    cout << "╔════════════════════════════════════════╗" << nl;
    cout << "║  MODULE 01: Static Array & Vector      ║" << nl;
    cout << "╚════════════════════════════════════════╝" << nl;

    demo_c_style_array();
    demo_std_array();
    demo_vector_basics();
    demo_push_vs_emplace();
    demo_2d_vector();
    demo_vector_operations();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    solve();

    return 0;
}

