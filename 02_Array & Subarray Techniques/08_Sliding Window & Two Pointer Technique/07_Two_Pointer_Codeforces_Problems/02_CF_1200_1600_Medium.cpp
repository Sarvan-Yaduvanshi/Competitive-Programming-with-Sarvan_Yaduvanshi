/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Codeforces Two Pointer — Medium (1200-1600)
 *  Level   : Medium
 * ============================================================================
 *
 *  CF 279B  — Books (1400) — Classic variable-size two pointer
 *             https://codeforces.com/problemset/problem/279/B
 *
 *  CF 602B  — Approximating a Constant Range (1500) — 2Ptr + Deque
 *             https://codeforces.com/problemset/problem/602/B
 *
 *  CF 1354B — Ternary String (1200) — Min window containing all 3 chars
 *             https://codeforces.com/problemset/problem/1354/B
 *
 *  CF 1358D — Buying Lemonade (1500) — Sort + greedy sweep
 *             https://codeforces.com/problemset/problem/1358/D
 *
 *  CF 1676E — Eating Queries (1100) — Prefix sum + binary search
 *             https://codeforces.com/problemset/problem/1676/E
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;
using ll = long long;

// ============================================================================
// CF 279B: Books — Max consecutive books you can read within time t
// Classic two pointer / sliding window on sum ≤ t
// ============================================================================
void solve_279B() {
    int n;
    ll t;
    cin >> n >> t;
    vector<ll> a(n);
    for (auto& x : a) cin >> x;

    int best = 0;
    ll sum = 0;
    int left = 0;
    for (int right = 0; right < n; right++) {
        sum += a[right];
        while (sum > t) {
            sum -= a[left];
            left++;
        }
        best = max(best, right - left + 1);
    }
    cout << best << "\n";
}

// ============================================================================
// CF 602B: Approximating a Constant Range
// Longest subarray where max - min ≤ 1. Use two deques (max & min).
// ============================================================================
void solve_602B() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;

    deque<int> maxD, minD; // Store indices
    int best = 0, left = 0;

    for (int right = 0; right < n; right++) {
        while (!maxD.empty() && a[maxD.back()] <= a[right]) maxD.pop_back();
        maxD.push_back(right);
        while (!minD.empty() && a[minD.back()] >= a[right]) minD.pop_back();
        minD.push_back(right);

        while (a[maxD.front()] - a[minD.front()] > 1) {
            left++;
            if (maxD.front() < left) maxD.pop_front();
            if (minD.front() < left) minD.pop_front();
        }
        best = max(best, right - left + 1);
    }
    cout << best << "\n";
}

// ============================================================================
// CF 1354B: Ternary String — Shortest substring containing all of 1, 2, 3
// ============================================================================
void solve_1354B() {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int n = s.size();
        int freq[4] = {};
        int have = 0, best = n + 1;
        int left = 0;

        for (int right = 0; right < n; right++) {
            int c = s[right] - '0';
            if (freq[c] == 0) have++;
            freq[c]++;

            while (have == 3) {
                best = min(best, right - left + 1);
                int lc = s[left] - '0';
                freq[lc]--;
                if (freq[lc] == 0) have--;
                left++;
            }
        }
        cout << (best > n ? 0 : best) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Uncomment the problem to test:
    // solve_279B();
    // solve_602B();
    // solve_1354B();

    return 0;
}

