/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Codeforces Fixed Size Sliding Window Problems
 *  Level   : All Levels (800 → 2400+)
 * ============================================================================
 *
 *  PROBLEM LIST WITH LINKS:
 *  ─────────────────────────
 *
 *  CF 1352B — Same Parity Summands (800)
 *             https://codeforces.com/problemset/problem/1352/B
 *
 *  CF 1669D — Colorful Stamp (1000)
 *             https://codeforces.com/problemset/problem/1669/D
 *
 *  CF 1551B2 — Wonderful String Hard (1400)
 *              https://codeforces.com/problemset/problem/1551/B2
 *
 *  CF 1598D — Training Session (1700)
 *             https://codeforces.com/problemset/problem/1598/D
 *
 *  CF 514D  — R2D2 and Droid Army (1800) — SW + Segment Tree / Deque
 *             https://codeforces.com/problemset/problem/514/D
 *
 *  CF 1849E — (2200) — Advanced SW + Deque
 *             https://codeforces.com/problemset/problem/1849/E
 *
 * ============================================================================
 *
 *  EXAMPLE: CF 514D — R2D2 and Droid Army
 *  ─────────────────────────────────────────
 *  Given N droids with M attributes each, and K shots total.
 *  Each shot on attribute j kills all droids in some range with attr[j] > 0.
 *  Find max consecutive droids you can destroy with K total shots.
 *
 *  APPROACH: Binary search on answer + sliding window with segment tree / deque
 *  to find max of each attribute in window. Total shots needed = sum of maxes.
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;
using ll = long long;

// ============================================================================
// CF 514D: R2D2 and Droid Army — Sliding Window + M Deques
// ============================================================================
void solve_514D() {
    int n, m;
    ll k;
    cin >> n >> m >> k;

    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];

    // For each attribute, maintain a max-deque
    vector<deque<int>> maxDq(m);

    int best = 0, bestLeft = 0;
    int left = 0;

    for (int right = 0; right < n; right++) {
        // Add right to all deques
        for (int j = 0; j < m; j++) {
            while (!maxDq[j].empty() && a[maxDq[j].back()][j] <= a[right][j])
                maxDq[j].pop_back();
            maxDq[j].push_back(right);
        }

        // Compute cost = sum of max of each attribute in window
        auto cost = [&]() -> ll {
            ll total = 0;
            for (int j = 0; j < m; j++)
                total += a[maxDq[j].front()][j];
            return total;
        };

        // Shrink while cost > k
        while (cost() > k) {
            for (int j = 0; j < m; j++)
                if (maxDq[j].front() == left)
                    maxDq[j].pop_front();
            left++;
        }

        if (right - left + 1 > best) {
            best = right - left + 1;
            bestLeft = left;
        }
    }

    // Output: max of each attribute in the best window
    if (best == 0) {
        for (int j = 0; j < m; j++) cout << 0 << " \n"[j == m-1];
    } else {
        for (int j = 0; j < m; j++) {
            int mx = 0;
            for (int i = bestLeft; i < bestLeft + best; i++)
                mx = max(mx, a[i][j]);
            cout << mx << " \n"[j == m-1];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // solve_514D();
    return 0;
}

