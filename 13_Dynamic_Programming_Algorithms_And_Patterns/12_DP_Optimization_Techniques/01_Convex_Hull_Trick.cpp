/*
 * ============================================================================
 *          DP OPTIMIZATION — CONVEX HULL TRICK (CHT)
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : DP Optimization — Convex Hull Trick
 * Level   : ⭐⭐⭐⭐ Expert / GM
 * ============================================================================
 *
 * WHEN TO USE CHT:
 *   Recurrence of the form:
 *     dp[i] = min/max( dp[j] + b[j] * a[i] )  for j < i
 *
 *   This is equivalent to: given a set of lines y = m*x + c,
 *   query the minimum/maximum y at a specific x.
 *
 * KEY IDEA:
 *   - Each dp[j] defines a LINE: y = b[j]*x + dp[j]
 *   - For each i, we query at x = a[i]
 *   - Maintain a CONVEX HULL of lines
 *   - Remove lines that are never optimal (dominated)
 *
 * TWO VARIANTS:
 *   1. Slopes are monotonic → Use a deque, O(n) total
 *   2. Slopes NOT monotonic → Use Li Chao Tree, O(n log n)
 *
 * CLASSIC PROBLEMS:
 *   - APIO 2014 — Sequence
 *   - CF 319C — Kalila and Dimna in the Logging Industry
 *   - AtCoder DP Z — Frog 3
 *   - CF 660F — Bear and Bowling
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * ============================================================
 * CONVEX HULL TRICK — Monotonic Slopes (Deque-based)
 * ============================================================
 * Lines added with DECREASING slopes.
 * Queries at INCREASING x values.
 * Answers MINIMUM queries.
 * Time: O(n) amortized.
 */
struct Line {
    long long m, b;  // y = m*x + b
    long long eval(long long x) { return m * x + b; }
};

class ConvexHullTrickMin {
    deque<Line> hull;

    // Check if line b is made redundant by lines a and c
    bool bad(Line a, Line b, Line c) {
        // b is bad if intersection of a,c is below b at that point
        // Cross multiplication to avoid floating point:
        // (b.b - a.b) * (c.m - a.m) >= (c.b - a.b) * (b.m - a.m)
        return (__int128)(c.b - a.b) * (b.m - a.m) <=
               (__int128)(b.b - a.b) * (c.m - a.m);
    }

public:
    // Add line y = mx + b (slopes must be in decreasing order for min queries)
    void addLine(long long m, long long b) {
        Line newLine = {m, b};
        while (hull.size() >= 2 && bad(hull[hull.size()-2], hull[hull.size()-1], newLine))
            hull.pop_back();
        hull.push_back(newLine);
    }

    // Query minimum y at x (x must be increasing)
    long long query(long long x) {
        while (hull.size() >= 2 && hull[0].eval(x) >= hull[1].eval(x))
            hull.pop_front();
        return hull[0].eval(x);
    }
};

/*
 * ============================================================
 * LI CHAO TREE — Non-monotonic slopes
 * ============================================================
 * Supports:
 *   - Add line y = mx + b
 *   - Query min y at x
 * Time: O(log(RANGE)) per operation
 * Works for any order of slopes and queries.
 */
class LiChaoTree {
    struct Node {
        long long m = 0, b = 1e18;  // default line at infinity
        int left = -1, right = -1;
    };

    vector<Node> tree;
    long long lo, hi;

    long long eval(int node, long long x) {
        return tree[node].m * x + tree[node].b;
    }

    void addLine(int node, long long l, long long r, long long m, long long b) {
        if (l > r) return;
        long long mid = (l + r) / 2;

        bool leftBetter = m * l + b < eval(node, l);
        bool midBetter = m * mid + b < eval(node, mid);

        if (midBetter) {
            swap(tree[node].m, m);
            swap(tree[node].b, b);
        }

        if (l == r) return;

        if (leftBetter != midBetter) {
            if (tree[node].left == -1) {
                tree[node].left = tree.size();
                tree.push_back({});
            }
            addLine(tree[node].left, l, mid, m, b);
        } else {
            if (tree[node].right == -1) {
                tree[node].right = tree.size();
                tree.push_back({});
            }
            addLine(tree[node].right, mid + 1, r, m, b);
        }
    }

    long long query(int node, long long l, long long r, long long x) {
        if (node == -1) return 1e18;
        long long res = eval(node, x);
        long long mid = (l + r) / 2;

        if (x <= mid)
            return min(res, query(tree[node].left, l, mid, x));
        else
            return min(res, query(tree[node].right, mid + 1, r, x));
    }

public:
    LiChaoTree(long long lo = 0, long long hi = 1e9) : lo(lo), hi(hi) {
        tree.push_back({});
    }

    void addLine(long long m, long long b) {
        addLine(0, lo, hi, m, b);
    }

    long long query(long long x) {
        return query(0, lo, hi, x);
    }
};

/*
 * ============================================================
 * EXAMPLE: AtCoder DP Z — Frog 3
 * ============================================================
 * N frogs on stones at heights h[]. Jump from i to j costs:
 *   (h[i] - h[j])² + C
 * Find min cost from stone 1 to stone N.
 *
 * dp[i] = min(dp[j] + (h[i]-h[j])² + C)
 *       = min(dp[j] + h[j]² - 2*h[i]*h[j]) + h[i]² + C
 *
 * Line form: dp[j] + h[j]² is the y-intercept, -2*h[j] is slope
 *            queried at x = h[i]
 */
vector<long long> frog3(vector<long long>& h, long long C) {
    int n = h.size();
    vector<long long> dp(n, 0);
    ConvexHullTrickMin cht;

    // Add line for j=0: slope = -2*h[0], intercept = dp[0] + h[0]^2
    cht.addLine(-2 * h[0], dp[0] + h[0] * h[0]);

    for (int i = 1; i < n; i++) {
        dp[i] = cht.query(h[i]) + h[i] * h[i] + C;
        cht.addLine(-2 * h[i], dp[i] + h[i] * h[i]);
    }
    return dp;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== CONVEX HULL TRICK DP ===" << endl;

    // Frog 3 example
    vector<long long> h = {10, 30, 40, 20, 60};
    long long C = 10;

    auto dp = frog3(h, C);
    cout << "\n--- Frog 3 (CHT) ---" << endl;
    cout << "Heights: "; for (auto x : h) cout << x << " ";
    cout << "\nC = " << C << endl;
    cout << "Min costs: ";
    for (auto x : dp) cout << x << " ";
    cout << "\nAnswer: " << dp.back() << endl;

    // Li Chao Tree example
    cout << "\n--- Li Chao Tree Demo ---" << endl;
    LiChaoTree lct(0, 100);
    lct.addLine(1, 0);    // y = x
    lct.addLine(-1, 10);  // y = -x + 10
    lct.addLine(0, 3);    // y = 3

    for (int x = 0; x <= 10; x++) {
        cout << "min at x=" << x << " → " << lct.query(x) << endl;
    }

    /*
     * CHT SUMMARY:
     * ============
     * Recurrence: dp[i] = min(dp[j] + b[j]*a[i] + cost)
     *
     * Step 1: Identify the line form: slope = b[j], intercept = dp[j]+...
     * Step 2: Query point = a[i]
     * Step 3: Check if slopes are monotonic:
     *         YES → Deque CHT (O(n))
     *         NO  → Li Chao Tree (O(n log n))
     */

    return 0;
}

