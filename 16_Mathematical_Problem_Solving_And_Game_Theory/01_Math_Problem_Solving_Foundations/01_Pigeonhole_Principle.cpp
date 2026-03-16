/*
 * ============================================================
 *  Topic   : Pigeonhole Principle — Finding Duplicates
 *  Pattern : If n+1 items in n slots → at least one duplicate
 *
 *  Problem : Given array of n+1 integers in [1, n], find a
 *            duplicate (LeetCode 287 — Find the Duplicate Number)
 *
 *  Approach: Floyd's Tortoise & Hare (Cycle Detection)
 *            — O(n) time, O(1) space
 * ============================================================
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
using u64 = unsigned long long;
using ld  = long double;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, int>;
using pll = pair<i64, i64>;

constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD   = 1'000'000'007LL;
constexpr i64 MOD9  = 998'244'353LL;
constexpr ld PI     = 3.14159265358979323846;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

template<class T>
void read(vec<T> &v) { for (auto &x : v) cin >> x; }
#define nl '\n'
#define YES cout << "YES" << nl
#define NO cout << "NO" << nl

/*
 * ============================================================
 *  PIGEONHOLE PRINCIPLE
 * ============================================================
 *
 *  Statement: If n+1 objects are distributed into n containers,
 *  at least one container has at least 2 objects.
 *
 *  Generalized: If kn+1 objects → n containers, some container
 *  has ≥ k+1 objects.
 *
 *  APPLICATION 1: Find the Duplicate Number
 *  -----------------------------------------
 *  Array of n+1 integers in range [1..n].
 *  By pigeonhole, at least one value repeats.
 *
 *  Approach: Treat array as a linked list where a[i] → next node.
 *  Since there's a duplicate value, there's a cycle.
 *  Use Floyd's cycle detection to find the entrance = duplicate.
 *
 *  Time:  O(n)
 *  Space: O(1)
 * ============================================================
 */

// Floyd's Cycle Detection to find duplicate
int findDuplicate(vec<int>& nums) {
    int slow = nums[0], fast = nums[0];

    // Phase 1: Find intersection point inside cycle
    do {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while (slow != fast);

    // Phase 2: Find entrance to cycle = duplicate value
    slow = nums[0];
    while (slow != fast) {
        slow = nums[slow];
        fast = nums[fast];
    }

    return slow;
}

/*
 *  APPLICATION 2: Pigeonhole on Remainders
 *  ----------------------------------------
 *  Given n+1 integers, prove at least 2 have same remainder mod n.
 *
 *  Practical use: Find a subset with sum divisible by n.
 *  Prefix sums mod n: s[0]=0, s[1], s[2], ..., s[n]
 *  n+1 values, n possible remainders (0..n-1)
 *  → Two prefix sums have same remainder mod n
 *  → Their difference (a subarray sum) is divisible by n.
 */

// Find subarray whose sum is divisible by n (guaranteed to exist)
pair<int,int> subarrayDivisibleByN(vec<int>& a) {
    int n = sz(a);
    map<int,int> rem_to_idx;
    rem_to_idx[0] = 0;  // prefix sum 0 at index 0

    i64 prefix = 0;
    for (int i = 0; i < n; i++) {
        prefix += a[i];
        int r = ((prefix % n) + n) % n;
        if (rem_to_idx.count(r)) {
            return {rem_to_idx[r], i};  // subarray [rem_to_idx[r], i]
        }
        rem_to_idx[r] = i + 1;
    }
    return {-1, -1};  // should never reach here by pigeonhole
}

void solve() {
    int n;
    cin >> n;

    vec<int> nums(n);
    read(nums);

    // Demo: Find duplicate using Floyd's cycle detection
    cout << "Duplicate found: " << findDuplicate(nums) << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    int TC = 1;
    cin >> TC;
    while (TC--) solve();

    return 0;
}

