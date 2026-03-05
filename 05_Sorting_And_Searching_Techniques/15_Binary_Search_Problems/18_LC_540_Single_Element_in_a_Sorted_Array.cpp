/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-05 14:28:23
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

/* Problem: LeetCode 540 - Single Element in a Sorted Array
 * Difficulty: Medium
 * You are given a sorted array consisting of only integers where every element appears exactly twice,
 * except for one element which appears exactly once. Find this single element that appears only once.
 *
 * You must write an algorithm that runs in O(log n) time and O(1) space.
 *
 * Example 1:
 * Input: nums = [1,1,2,3,3,4,4,8,8]
 * Output: 2
 *
 * Example 2:
 * Input: nums = [3,3,7,7,10,11,11]
 * Output: 10
 *
 * Constraints:
 * - 1 <= nums.length <= 10^5
 * - 0 <= nums[i] <= 10^5
 */

// Method 1: Bit Manipulation (XOR)
// Time Complexity -> O(N)
// Space Complexity -> O(1)
int singleNonDuplicateXOR(const vec<int>& nums) {
    int result = 0;
    for (int num : nums) {
        result ^= num; // XOR will cancel out pairs and leave the unique element
    }
    return result;
}

// Method 2: Binary Search (1st Version - Check Pairs)
// Time Complexity -> O(log N)
// Space Complexity -> O(1)
int singleNonDuplicateBinarySearch(const vec<int>& nums){
    int n = sz(nums);
    // Edge case: If the single element is at the beginning or end
    if (n == 1) return nums[0];

    int lo = 0, hi = n - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        // Case 1: if mid == a[0] than answer -> mid or a[0]
        if (mid == 0 && nums[0] != nums[1]) return nums[mid];
        // Case 2: if mid == n - 1 than answer -> mid or n - 1
        if (mid == n - 1 && nums[n - 1] != nums[n - 2]) return nums[mid];

        // case 3: if mid == unique -> a[mid - 1] != a[mid] && a[mid] != a[mid + 1]
        if (nums[mid - 1] != nums[mid] && nums[mid] != nums[mid + 1]) return nums[mid];

        // Case 4: mid is even than check mid == mid - 1 than left part exist answer or mid == mid + 1 than right part exist answer
        if (!(mid & 1)) {
            if (nums[mid - 1] == nums[mid]) hi = mid - 1;
            else lo = mid + 1;
        }
        // Case 5 : mid is odd than check mid == mid - 1 than right part exist answer or mid == mid + 1 than left part exist answer
        else {
            if (nums[mid - 1] == nums[mid]) lo = mid + 1;
            else hi = mid - 1;
        }
    }

    return -1; // This line should never be reached if input is valid
}

/*
SINGLE NON-DUPLICATE (Sorted Array) — GM Notes
Problem Pattern
- Array is SORTED
- Every element appears EXACTLY TWICE
- Only ONE element appears ONCE (unique)

Key Invariant (Core Trick)
1) Before the single element:
   - Pairs start at EVEN indices
   - Pattern: (0,1), (2,3), (4,5), ...

2) After the single element:
   - Pairing shifts by 1
   - Pairs start at ODD indices
   - Pattern: (1,2), (3,4), (5,6), ...

Why shift happens?
- The single element “breaks” the alignment
- After it, every pair’s starting index moves by +1 (even → odd)

Example
nums  = [1,1,2,3,3,4,4,8,8]
index =  0 1 2 3 4 5 6 7 8
single = 2 at index 2

Before single:
- (0,1) = (1,1)  starts at EVEN

After single:
- (3,4) = (3,3)  starts at ODD
- (5,6) = (4,4)  starts at ODD
- (7,8) = (8,8)  starts at ODD

🎯 Binary Search Decision (Pair Alignment)
Always compare an EVEN index pair: (mid, mid+1)

Case A: nums[mid] == nums[mid+1]
- Pair is perfectly aligned
- Means we are still BEFORE the single element
➡️ Single cannot be on the left (including this pair)
➡️ Move RIGHT: lo = mid + 2

Case B: nums[mid] != nums[mid+1]
- Pair alignment is broken at mid
- Single is either at mid OR somewhere LEFT
➡️ Keep LEFT: hi = mid

Final Result
- Search converges to the single element using pair-alignment shift.
*/
int singleNonDuplicateBinarySearchParity(const vec<int>& nums){
    int n = sz(nums);
    int lo = 0, hi = n - 1;

    while (lo < hi){
        int mid = lo + (hi - lo) / 2;

        // make mid even so (mid, mid+1) is a pair index
        if (mid & 1) mid--;

        // if pair is correct, single is on right side
        if (nums[mid] == nums[mid + 1]) lo = mid + 2;
        else hi = mid;
    }

    return nums[lo]; // lo will point to the single element
}
void solve() {
    int n; cin >> n;

    vec<int> nums(n);
    read(nums);

    int result = singleNonDuplicateBinarySearchParity(nums);
    cout << result << nl;
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

