/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Codeforces Variable Size Sliding Window — Easy & Medium
 *  Level   : 800 → 1600
 * ============================================================================
 *
 *  CF 1692E — Binary Deque (1200) — Variable window / reverse thinking
 *             https://codeforces.com/problemset/problem/1692/E
 *
 *  CF 1354B — Ternary String (1200) — Min window containing all 3 types
 *             https://codeforces.com/problemset/problem/1354/B
 *
 *  CF 279B  — Books (1400) — Longest subarray with sum ≤ t
 *             https://codeforces.com/problemset/problem/279/B
 *
 *  CF 602B  — Approximating a Constant Range (1500) — max-min ≤ 1
 *             https://codeforces.com/problemset/problem/602/B
 *
 *  CF 1676F — Longest Strike (1300) — Longest subarray with freq ≥ k
 *             https://codeforces.com/problemset/problem/1676/F
 *
 *  CF 1462D — Add to Neighbour and Remove (1400)
 *             https://codeforces.com/problemset/problem/1462/D
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <unordered_map>
using namespace std;
using ll = long long;

// ============================================================================
// CF 1692E: Binary Deque
// ============================================================================
/*
 * Binary array. Remove minimum elements from front/back to get sum = s.
 * REVERSE: Find longest subarray with sum = s.
 * Answer = N - longest.
 */
void solve_1692E() {
    int t;
    cin >> t;
    while (t--) {
        int n, s;
        cin >> n >> s;
        vector<int> a(n);
        for (auto& x : a) cin >> x;

        int totalSum = 0;
        for (int x : a) totalSum += x;

        if (totalSum < s) { cout << -1 << "\n"; continue; }
        if (totalSum == s) { cout << 0 << "\n"; continue; }

        // Find longest subarray with sum = s
        int best = 0, left = 0, windowSum = 0;
        for (int right = 0; right < n; right++) {
            windowSum += a[right];
            while (windowSum > s) {
                windowSum -= a[left];
                left++;
            }
            if (windowSum == s)
                best = max(best, right - left + 1);
        }
        cout << (best == 0 && s > 0 ? -1 : n - best) << "\n";
    }
}

// ============================================================================
// CF 279B: Books — Longest subarray with sum ≤ t
// ============================================================================
void solve_279B() {
    int n;
    ll t;
    cin >> n >> t;
    vector<ll> a(n);
    for (auto& x : a) cin >> x;

    int best = 0, left = 0;
    ll sum = 0;
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
// CF 602B: Approximating a Constant Range — max - min ≤ 1
// ============================================================================
void solve_602B() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;

    deque<int> maxD, minD;
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
// CF 1354B: Ternary String — Shortest window with all 3 chars
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

    // Uncomment to test:
    // solve_1692E();
    // solve_279B();
    // solve_602B();
    // solve_1354B();

    return 0;
}

