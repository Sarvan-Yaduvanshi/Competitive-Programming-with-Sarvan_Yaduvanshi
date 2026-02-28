/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Codeforces Two Pointer Problems — Easy (800-1200)
 *  Level   : Easy
 * ============================================================================
 *
 *  PROBLEMS:
 *  ─────────
 *  CF 1538C — Number of Pairs (1300)
 *             https://codeforces.com/problemset/problem/1538/C
 *             Sort + Two Pointer to count pairs with L ≤ a[i]+a[j] ≤ R
 *
 *  CF 1921D — Very Different Array (1100)
 *             https://codeforces.com/problemset/problem/1921/D
 *             Sort both, pair smallest of one with largest of other
 *
 *  CF 6A    — Triangle (800)
 *             https://codeforces.com/problemset/problem/6/A
 *
 *  CF 1462C — Unique Number (1100)
 *             https://codeforces.com/problemset/problem/1462/C
 *
 *  CF 1385A — Three Pairwise Maximums (800)
 *             https://codeforces.com/problemset/problem/1385/A
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
using ll = long long;

// ============================================================================
// CF 1538C: Number of Pairs
// Count pairs (i,j) i<j such that L ≤ a[i]+a[j] ≤ R
// Trick: count(sum ≤ R) - count(sum ≤ L-1)
// ============================================================================
ll countPairsAtMost(vector<ll>& a, ll target) {
    int n = a.size();
    ll cnt = 0;
    int left = 0, right = n - 1;
    while (left < right) {
        if (a[left] + a[right] <= target) {
            cnt += (right - left);
            left++;
        } else {
            right--;
        }
    }
    return cnt;
}

void solve_1538C() {
    int n;
    ll l, r;
    cin >> n >> l >> r;
    vector<ll> a(n);
    for (auto& x : a) cin >> x;
    sort(a.begin(), a.end());

    ll ans = countPairsAtMost(a, r) - countPairsAtMost(a, l - 1);
    cout << ans << "\n";
}

// ============================================================================
// CF 1921D: Very Different Array
// Sort a ascending, b descending. Pair and sum |a[i]-b[i]| for first m pairs.
// ============================================================================
void solve_1921D() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end(), greater<int>());

    // Two pointer: match a's smallest with b's largest, a's largest with b's smallest
    ll ans = 0;
    int left = 0, right = n - 1;
    int bleft = 0, bright = m - 1;
    int taken = 0;

    while (taken < n) {
        ll opt1 = abs((ll)a[left] - b[bleft]);
        ll opt2 = abs((ll)a[right] - b[bright]);
        if (opt1 >= opt2) {
            ans += opt1;
            left++; bleft++;
        } else {
            ans += opt2;
            right--; bright--;
        }
        taken++;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Uncomment the problem you want to test:
    // solve_1538C();
    // solve_1921D();

    // Example test for 1538C
    // Input: 4 5 8 / 1 2 3 4 → pairs: (1,4)=5, (2,3)=5, (2,4)=6, (3,4)=7 → 4 pairs in [5,8]

    return 0;
}

