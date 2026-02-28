/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : More Opposite Direction Problems — Sorted Squares, Reverse String,
 *            Assign Cookies, Minimum Difference, Product Less Than K
 *  Level   : Easy → Medium
 * ============================================================================
 *
 *  THESE ARE CLASSIC TWO POINTER PROBLEMS THAT EVERY DSA LEARNER MUST KNOW:
 *
 *  LC 977  — Squares of a Sorted Array (opposite direction merge)
 *            https://leetcode.com/problems/squares-of-a-sorted-array/
 *
 *  LC 344  — Reverse String (in-place two pointer swap)
 *            https://leetcode.com/problems/reverse-string/
 *
 *  LC 455  — Assign Cookies (greedy two pointer on sorted arrays)
 *            https://leetcode.com/problems/assign-cookies/
 *
 *  LC 611  — Valid Triangle Number (sort + two pointer count)
 *            https://leetcode.com/problems/valid-triangle-number/
 *
 *  LC 1498 — Number of Subsequences That Satisfy Sum Condition
 *            https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/
 *
 *  LC 360  — Sort Transformed Array (two pointer on parabola)
 *            https://leetcode.com/problems/sort-transformed-array/
 *
 *  LC 1099 — Two Sum Less Than K (see file 01 also)
 *            https://leetcode.com/problems/two-sum-less-than-k/
 *
 *  CSES 1640 — Sum of Two Values
 *              https://cses.fi/problemset/task/1640
 *
 *  CSES 1641 — Sum of Three Values
 *              https://cses.fi/problemset/task/1641
 *
 *  CSES 1642 — Sum of Four Values
 *              https://cses.fi/problemset/task/1642
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;

// ============================================================================
// LC 977: Squares of a Sorted Array — Opposite Direction Merge
// ============================================================================
/*
 * Input: sorted array (may have negatives). Output: sorted squares.
 * Negatives squared become large positives, so largest square is at one of the ends.
 *
 * Two pointer from both ends: compare |arr[left]| vs |arr[right]|.
 * Fill result array from the END (largest first).
 *
 * Time: O(N), Space: O(N)
 */
vector<int> sortedSquares(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n);
    int left = 0, right = n - 1;
    int pos = n - 1; // Fill from end

    while (left <= right) {
        int lsq = nums[left] * nums[left];
        int rsq = nums[right] * nums[right];
        if (lsq > rsq) {
            result[pos--] = lsq;
            left++;
        } else {
            result[pos--] = rsq;
            right--;
        }
    }
    return result;
}

// ============================================================================
// LC 344: Reverse String — Two Pointer Swap
// ============================================================================
void reverseString(vector<char>& s) {
    int left = 0, right = (int)s.size() - 1;
    while (left < right) {
        swap(s[left], s[right]);
        left++; right--;
    }
}

// ============================================================================
// LC 455: Assign Cookies — Greedy Two Pointer
// ============================================================================
/*
 * Children have greed g[i], cookies have size s[j].
 * Each child gets at most one cookie. Cookie s[j] satisfies child g[i] if s[j] >= g[i].
 * Maximize content children.
 *
 * Sort both. Match smallest cookie to smallest greed.
 */
int findContentChildren(vector<int>& g, vector<int>& s) {
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    int child = 0, cookie = 0;

    while (child < (int)g.size() && cookie < (int)s.size()) {
        if (s[cookie] >= g[child])
            child++; // Satisfied
        cookie++;     // Cookie used either way
    }
    return child;
}

// ============================================================================
// LC 611: Valid Triangle Number — Sort + Two Pointer Count
// ============================================================================
/*
 * Count triplets (i,j,k) where arr[i] + arr[j] > arr[k] (triangle inequality).
 * Sort. Fix k (largest side), use two pointer for i,j.
 *
 * For fixed k: if arr[left] + arr[right] > arr[k], then ALL (left, left+1...right-1, right) work
 * → count += (right - left), then right--.
 * Else left++.
 *
 * Time: O(N²), Space: O(1)
 */
int triangleNumber(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size(), count = 0;

    for (int k = n - 1; k >= 2; k--) {
        int left = 0, right = k - 1;
        while (left < right) {
            if (nums[left] + nums[right] > nums[k]) {
                count += (right - left); // All pairs (left..right-1, right) are valid
                right--;
            } else {
                left++;
            }
        }
    }
    return count;
}

// ============================================================================
// LC 1498: Number of Subsequences — Sort + Two Pointer + Power of 2
// ============================================================================
/*
 * Count non-empty subsequences where min + max ≤ target.
 * Sort → fix left as min, find rightmost right as max.
 * Subsequences = 2^(right - left) (middle elements freely chosen).
 */
int numSubseq(vector<int>& nums, int target) {
    int n = nums.size();
    sort(nums.begin(), nums.end());

    vector<ll> pow2(n);
    pow2[0] = 1;
    for (int i = 1; i < n; i++)
        pow2[i] = pow2[i-1] * 2 % MOD;

    ll ans = 0;
    int left = 0, right = n - 1;
    while (left <= right) {
        if (nums[left] + nums[right] <= target) {
            ans = (ans + pow2[right - left]) % MOD;
            left++;
        } else {
            right--;
        }
    }
    return (int)ans;
}

// ============================================================================
// CSES 1640: Sum of Two Values — Two Pointer (return 1-indexed positions)
// ============================================================================
/*
 * Find two elements with sum = x. Print their 1-indexed positions.
 * Sort with original indices, then two pointer.
 */
void sumOfTwoValues(vector<int>& a, int x) {
    int n = a.size();
    vector<pair<int,int>> v(n); // (value, original_index)
    for (int i = 0; i < n; i++) v[i] = {a[i], i + 1};
    sort(v.begin(), v.end());

    int left = 0, right = n - 1;
    while (left < right) {
        int sum = v[left].first + v[right].first;
        if (sum == x) {
            cout << v[left].second << " " << v[right].second << "\n";
            return;
        }
        if (sum < x) left++;
        else right--;
    }
    cout << "IMPOSSIBLE\n";
}

int main() {
    // Sorted Squares
    vector<int> nums1 = {-4, -1, 0, 3, 10};
    auto sq = sortedSquares(nums1);
    cout << "Sorted Squares: ";
    for (int x : sq) cout << x << " ";
    cout << "\n"; // 0 1 9 16 100

    // Reverse String
    vector<char> s = {'h','e','l','l','o'};
    reverseString(s);
    cout << "Reversed: ";
    for (char c : s) cout << c;
    cout << "\n"; // olleh

    // Assign Cookies
    vector<int> g = {1, 2, 3}, cookies = {1, 1};
    cout << "Content children: " << findContentChildren(g, cookies) << "\n"; // 1

    // Valid Triangle Number
    vector<int> sides = {2, 2, 3, 4};
    cout << "Valid triangles: " << triangleNumber(sides) << "\n"; // 3

    // Number of Subsequences
    vector<int> nums2 = {3, 5, 6, 7};
    cout << "Subsequences (target=9): " << numSubseq(nums2, 9) << "\n"; // 4

    return 0;
}

