/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-28 11:45:00
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
//  MODULE 08: INDEX SHIFTING & MATH TRICKS
//  Level: ⭐⭐⭐ Advanced
//  Topics: Cyclic indexing, in-place encoding, sign marking, coordinate
//          compression, 0-indexed vs 1-indexed, missing number tricks
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
// 1. CYCLIC INDEXING — (i + k) % n
// -------------------------------------------------------------
// The MOST IMPORTANT formula in array manipulation.
//
// Used in: rotations, circular buffers, ring queues, clock arithmetic
//
// Key formulas:
//   Next position:     (i + 1) % n
//   Previous position: (i - 1 + n) % n   ← Adding N handles negative values!
//   K steps forward:   (i + k) % n
//   K steps backward:  (i - k % n + n) % n
//
// GM Warning: (i - 1) % n can give NEGATIVE result in C++!
//   -1 % 5 = -1 (not 4!) → Always add N: (-1 + 5) % 5 = 4

void demo_cyclic_indexing() {
    cout << "--- Cyclic Indexing ---" << nl;

    int n = 5;
    vec<int> arr = {10, 20, 30, 40, 50};

    // Traverse circularly starting from index 2
    cout << "Circular from idx 2: ";
    for (int step = 0; step < n; step++) {
        int idx = (2 + step) % n;
        cout << arr[idx] << " ";
    }
    cout << nl; // 30 40 50 10 20

    // Next/Previous element
    int i = 0;
    cout << "arr[0] = " << arr[i] << nl;
    cout << "Next = arr[" << (i + 1) % n << "] = " << arr[(i + 1) % n] << nl;
    cout << "Prev = arr[" << (i - 1 + n) % n << "] = " << arr[(i - 1 + n) % n] << nl;

    // Josephus Problem uses cyclic indexing:
    // next = (current + k - 1) % remaining_people
}

// -------------------------------------------------------------
// 2. IN-PLACE ENCODING — Store Two Values in One Cell
// -------------------------------------------------------------
// Trick: If values are in range [0, N), store:
//   arr[i] = arr[i] + (new_value % N) * N
//
// Decode:
//   Old value = arr[i] % N
//   New value = arr[i] / N
//
// Used in: LC 1920, rearrange array, build from permutation
//
// WHY IT WORKS:
//   If original value < N and new value < N:
//   encoded = original + new * N
//   original = encoded % N   (since original < N)
//   new = encoded / N

void demo_inplace_encoding() {
    cout << nl << "--- In-Place Encoding ---" << nl;

    // LC 1920: Build Array from Permutation
    // Given arr = [0, 2, 1, 5, 3, 4], build ans[i] = arr[arr[i]]
    // CONSTRAINT: Do it in O(1) extra space!

    vec<int> arr = {0, 2, 1, 5, 3, 4};
    int n = sz(arr);

    printArr("Original", arr);

    // Step 1: Encode both old and new values
    for (int i = 0; i < n; i++) {
        // arr[arr[i]] might already be modified → use % n to get original
        int newVal = arr[arr[i] % n];
        arr[i] = arr[i] + (newVal % n) * n;
    }

    // Step 2: Extract new values
    for (int i = 0; i < n; i++) {
        arr[i] = arr[i] / n;
    }

    printArr("After (arr[arr[i]])", arr);
    // Expected: {0, 1, 2, 4, 5, 3}
}

// -------------------------------------------------------------
// 3. SIGN MARKING — Use Sign Bit as a Flag
// -------------------------------------------------------------
// When values are positive and in range [1, N]:
//   Visit index (val - 1) and negate arr[val - 1]
//   If already negative → value was seen before (duplicate!)
//
// Used in: LC 442 (find duplicates), LC 448 (find missing)

void demo_sign_marking() {
    cout << nl << "--- Sign Marking ---" << nl;

    // LC 442: Find All Duplicates in an Array
    // Values are in [1, N], each appears once or twice.
    vec<int> arr = {4, 3, 2, 7, 8, 2, 3, 1};
    int n = sz(arr);

    vec<int> duplicates;
    for (int i = 0; i < n; i++) {
        int idx = abs(arr[i]) - 1; // Map value to index
        if (arr[idx] < 0) {
            // Already visited → arr[i] is a duplicate
            duplicates.pb(abs(arr[i]));
        } else {
            arr[idx] = -arr[idx]; // Mark as visited
        }
    }

    cout << "Duplicates: ";
    for (int x : duplicates) cout << x << " ";
    cout << nl; // 2 3

    // Restore array (undo sign marking)
    for (int i = 0; i < n; i++) arr[i] = abs(arr[i]);
}

// LC 448: Find All Numbers Disappeared in an Array
vec<int> findDisappearedNumbers(vec<int> arr) {
    int n = sz(arr);
    // Mark presence
    for (int i = 0; i < n; i++) {
        int idx = abs(arr[i]) - 1;
        if (arr[idx] > 0) arr[idx] = -arr[idx];
    }

    vec<int> missing;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) missing.pb(i + 1);
    }
    return missing;
}

// -------------------------------------------------------------
// 4. MISSING NUMBER — Math / XOR Tricks
// -------------------------------------------------------------
// LC 268: Array of N numbers from [0, N], one is missing. Find it.

// Method 1: Sum formula — O(N) time, O(1) space
int missingNumber_sum(const vec<int>& arr) {
    int n = sz(arr);
    i64 expectedSum = (i64)n * (n + 1) / 2;
    i64 actualSum = accumulate(all(arr), 0LL);
    return (int)(expectedSum - actualSum);
}

// Method 2: XOR — O(N) time, O(1) space
// Property: a ^ a = 0, a ^ 0 = a
// XOR all numbers [0..N] with all array elements → missing number remains
int missingNumber_xor(const vec<int>& arr) {
    int n = sz(arr);
    int xorAll = 0;
    for (int i = 0; i <= n; i++) xorAll ^= i;
    for (int x : arr) xorAll ^= x;
    return xorAll;
}

// GM Tip: XOR method is overflow-safe (no large sum needed).

// -------------------------------------------------------------
// 5. FIND THE DUPLICATE (Cycle Detection) — LC 287
// -------------------------------------------------------------
// Array of N+1 integers in range [1, N]. Exactly one duplicate.
// Floyd's Tortoise and Hare (Cycle Detection)
// Time: O(N), Space: O(1), Read-only!

int findDuplicate(const vec<int>& arr) {
    // Phase 1: Find intersection point
    int slow = arr[0];
    int fast = arr[0];

    do {
        slow = arr[slow];           // Move 1 step
        fast = arr[arr[fast]];      // Move 2 steps
    } while (slow != fast);

    // Phase 2: Find entry point of cycle
    slow = arr[0];
    while (slow != fast) {
        slow = arr[slow];
        fast = arr[fast];
    }

    return slow; // The duplicate number
}

// WHY THIS WORKS:
// Think of arr as a function f(i) = arr[i].
// Following the chain 0 → arr[0] → arr[arr[0]] → ... creates a linked list.
// Since there's a duplicate, two indices point to the same value → cycle!
// Floyd's algorithm finds the cycle entry point = the duplicate.

// -------------------------------------------------------------
// 6. FIRST MISSING POSITIVE — LC 41
// -------------------------------------------------------------
// Given unsorted array, find smallest missing positive integer.
// Must be O(N) time, O(1) space.
//
// Key Idea: Use the array itself as a hash table!
//   For array of size N, answer is in [1, N+1].
//   Place each number i at index i-1 (if possible).
//   Then scan: first index where arr[i] != i+1 → answer is i+1.

int firstMissingPositive(vec<int> arr) {
    int n = sz(arr);

    // Place each value at its "correct" index
    for (int i = 0; i < n; i++) {
        // Keep swapping arr[i] to its correct position
        while (arr[i] >= 1 && arr[i] <= n && arr[arr[i] - 1] != arr[i]) {
            swap(arr[i], arr[arr[i] - 1]);
        }
    }

    // Find first mismatch
    for (int i = 0; i < n; i++) {
        if (arr[i] != i + 1) return i + 1;
    }
    return n + 1; // All [1..N] present
}

// GM Note: The while loop looks O(N²) but is actually O(N) amortized!
// Each element is swapped at most once to its correct position.

// -------------------------------------------------------------
// 7. COORDINATE COMPRESSION
// -------------------------------------------------------------
// Map large values to small consecutive integers [0, K).
// Used in: segment trees, BIT, when values up to 10^9 but count ≤ 10^5.
//
// Steps:
//   1. Copy and sort
//   2. Remove duplicates
//   3. Use lower_bound to map original values to compressed indices

vec<int> coordinateCompress(const vec<int>& arr) {
    // Step 1-2: Sort and unique
    vec<int> sorted_unique = arr;
    sort(all(sorted_unique));
    sorted_unique.erase(unique(all(sorted_unique)), sorted_unique.end());

    // Step 3: Map each value to its compressed index
    vec<int> compressed(sz(arr));
    for (int i = 0; i < sz(arr); i++) {
        compressed[i] = lower_bound(all(sorted_unique), arr[i]) - sorted_unique.begin();
    }

    return compressed;
}

void demo_coordinate_compression() {
    cout << nl << "--- Coordinate Compression ---" << nl;

    vec<int> arr = {100, 5, 1000000, 5, 200, 100};
    vec<int> compressed = coordinateCompress(arr);

    printArr("Original   ", arr);
    printArr("Compressed ", compressed);
    // 100→1, 5→0, 1000000→3, 5→0, 200→2, 100→1
    // Output: 1 0 3 0 2 1
}

// -------------------------------------------------------------
// 8. 0-INDEXED vs 1-INDEXED (GM Practical Guide)
// -------------------------------------------------------------
/*
 * Most CP problems use 1-indexed input/output.
 * C++ arrays are 0-indexed.
 *
 * THREE STRATEGIES:
 *
 * Strategy 1: Read into 0-indexed, adjust mentally
 *   vec<int> arr(n); read(arr);
 *   // arr[0] = first element
 *   // Access: arr[i-1] for "i-th element"
 *
 * Strategy 2: Use 1-indexed vector (size n+1)
 *   vec<int> arr(n + 1);
 *   for (int i = 1; i <= n; i++) cin >> arr[i];
 *   // arr[1] = first element, arr[0] is unused
 *   // GM Tip: Common for graph problems (adj[1..n])
 *
 * Strategy 3: Use 1-indexed internally with macro
 *   #define A(i) arr[(i)-1]
 *   // Dangerous but some people use it
 *
 * GM Recommendation: Use Strategy 2 for graphs, Strategy 1 for arrays.
 */

// -------------------------------------------------------------
// 9. FREQUENCY ARRAY (Index as Value)
// -------------------------------------------------------------
// When values are in [0, MAXVAL], use array index as the value.
// Time: O(N + MAXVAL), Space: O(MAXVAL)

void demo_frequency_array() {
    cout << nl << "--- Frequency Array ---" << nl;

    vec<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int maxVal = *max_element(all(arr));

    vec<int> freq(maxVal + 1, 0);
    for (int x : arr) freq[x]++;

    cout << "Frequencies:" << nl;
    for (int i = 0; i <= maxVal; i++) {
        if (freq[i] > 0) cout << "  " << i << " → " << freq[i] << nl;
    }

    // GM Tip: If maxVal > 10^6, use unordered_map instead.
    // If values can be negative, shift by |minVal|:
    //   freq[x - minVal]++
}

// -------------------------------------------------------------
// 10. COUNTING SORT CONCEPT (Index as Value, Extended)
// -------------------------------------------------------------
// Sort in O(N + K) where K = range of values.
// Only works for non-negative integers with small range.

void countingSort(vec<int>& arr) {
    if (arr.empty()) return;

    int maxVal = *max_element(all(arr));
    int minVal = *min_element(all(arr));
    int range = maxVal - minVal + 1;

    vec<int> count(range, 0);
    for (int x : arr) count[x - minVal]++;

    int idx = 0;
    for (int i = 0; i < range; i++) {
        while (count[i]-- > 0) {
            arr[idx++] = i + minVal;
        }
    }
}

void solve() {
    cout << "╔════════════════════════════════════════╗" << nl;
    cout << "║  MODULE 08: Index Shifting & Math      ║" << nl;
    cout << "╚════════════════════════════════════════╝" << nl;

    // 1. Cyclic Indexing
    demo_cyclic_indexing();

    // 2. In-Place Encoding
    demo_inplace_encoding();

    // 3. Sign Marking
    demo_sign_marking();

    // 4. Missing Number
    cout << nl << "--- Missing Number ---" << nl;
    vec<int> miss = {3, 0, 1}; // Missing: 2
    cout << "Sum method: " << missingNumber_sum(miss) << nl;
    cout << "XOR method: " << missingNumber_xor(miss) << nl;

    // 5. Find Disappeared Numbers
    cout << nl << "--- Find Disappeared Numbers ---" << nl;
    vec<int> dis = {4, 3, 2, 7, 8, 2, 3, 1};
    vec<int> missing = findDisappearedNumbers(dis);
    printArr("Missing", missing); // 5 6

    // 6. Find Duplicate
    cout << nl << "--- Find Duplicate ---" << nl;
    vec<int> dup = {1, 3, 4, 2, 2};
    cout << "Duplicate: " << findDuplicate(dup) << nl; // 2

    // 7. First Missing Positive
    cout << nl << "--- First Missing Positive ---" << nl;
    vec<int> fmp = {3, 4, -1, 1};
    cout << "First missing positive: " << firstMissingPositive(fmp) << nl; // 2

    // 8. Coordinate Compression
    demo_coordinate_compression();

    // 9. Frequency Array
    demo_frequency_array();

    // 10. Counting Sort
    cout << nl << "--- Counting Sort ---" << nl;
    vec<int> cs = {4, 2, 2, 8, 3, 3, 1};
    countingSort(cs);
    printArr("Sorted", cs);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    solve();

    return 0;
}

