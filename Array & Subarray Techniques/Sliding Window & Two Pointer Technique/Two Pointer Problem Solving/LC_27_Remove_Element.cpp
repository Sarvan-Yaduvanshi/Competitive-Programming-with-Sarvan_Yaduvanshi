/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-20 00:35:11
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

/* Problem: Remove Element
Given an integer array nums and an integer val, remove all occurrences of val in nums in-place.
The relative order of the elements may be changed.
Since it is impossible to change the length of the array in some languages, you must instead have the result
be placed in the first part of the array nums. More formally, if there are k elements after removing the duplicates,
then the first k elements of nums should hold the final result. It does not matter what you leave beyond the first k elements.

Return k after placing the final result in the first k slots of nums.
Do not allocate extra space for another array. You must do this by modifying the input array in-place with O(1) extra memory.

Example 1:
Input: nums = [3,2,2,3], val = 3
Output: 2, nums = [2,2,_,_]
Explanation: Your function should return k = 2, with the first two elements of nums being 2.
It does not matter what you leave beyond the returned k (hence they are underscores).
Example 2:

Input: nums = [0,1,2,2,3,0,4,2], val = 2
Output: 5, nums = [0,1,3,0,4,_,_,_]
Explanation: Your function should return k = 5, with the first five elements of nums containing 0, 1, 3, 0, and 4.
Note that the five elements can be returned in any order.
It does not matter what you leave beyond the returned k (hence they are underscores).

Constraints:
0 <= nums.length <= 100
0 <= nums[i] <= 50
0 <= val <= 100
*/

/* * GM ANALYSIS:
 * Approach: Optimized Two-Pointer (Swap & Discard)
 * * Logic:
 * Instead of shifting all elements down (which causes unnecessary writes),
 * we simply swap the element to be removed with the last available element.
 * * Why this is GM level:
 * 1. O(N) Time: We traverse the list at most once.
 * 2. O(1) Space: In-place modification.
 * 3. Minimal Writes: This is superior to the "shift" approach when valid elements
 * are rare, as it avoids moving valid elements multiple times.
 * * Edge Case Handled:
 * When we swap nums[left] with nums[right], we do NOT increment 'left' immediately.
 * We must re-check the new value at nums[left] in the next iteration, just in case
 * the element we swapped in is also equal to 'val'.
 */

int removeElement(vec<int>& nums, int val) {
    int left = 0;
    int right = sz(nums) - 1;

    while (left <= right) {
        if (nums[left] == val) {
            // Found 'val'. Don't shift; overwrite it with the last element.
            // Reduce the search space (right--) effectively "discarding" the last slot.
            nums[left] = nums[right];
            right--;
        } else {
            // Current element is valid, keep it and move forward.
            left++;
        }
    }

    // 'left' is now the count of valid elements (the new size)
    return left;
}

/* * GM ANALYSIS:
 * Approach: Reader-Writer Two-Pointer (Stable Compaction)
 * * * Core Logic:
 * We maintain two indices:
 * - 'i' (Reader): Scans every element.
 * - 'k' (Writer): Points to the next position where a valid element belongs.
 * * * Invariant:
 * At any point, the subarray nums[0...k-1] contains only valid elements
 * in their original relative order.
 * * * Performance Characteristics:
 * 1. Sequential Access: excellent cache locality compared to the swap method.
 * 2. Stability: Preserves the original order of non-'val' elements.
 * 3. Write Heavy: If 'val' is rare, we might perform many self-assignments (nums[k] = nums[i] where k==i).
 * - Optimization: Can add 'if (k != i)' check before assignment to avoid self-writes.
 */

// Time Complexity: O(N) | Space Complexity: O(1)
int removeElementShift(vec<int>& nums, int val) {
    int k = 0; // The "Writer" pointer

    // 'i' is the "Reader" pointer
    for (int i = 0; i < nums.size(); i++) {
        // Filter Logic: If the current element is valid (not 'val')
        if (nums[i] != val) {
            // Write the valid element to the 'k' position
            // This effectively "shifts" valid data to the front
            nums[k] = nums[i];

            // Increment the writer to prepare for the next valid element
            k++;
        }
        // Implicit Else: If nums[i] == val, we simply skip it (Reader advances, Writer stays).
    }

    // 'k' now represents the count of valid elements (new logical size)
    return k;
}

void solve() {
    int n, val;
    // Assuming Input format: n (size), val (target), then the array elements
    if (!(cin >> n >> val)) return;

    vec<int> nums(n);
    read(nums);

    int newLength = removeElement(nums, val);

    // Formatting output exactly as requested: "2, nums = [2,2]"
    cout << newLength << ", nums = [";
    for (int i = 0; i < newLength; i++) {
        cout << nums[i] << (i == newLength - 1 ? "" : ",");
    }
    cout << "]" << nl;
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

