/*
╔══════════════════════════════════════════════════════════════╗
║  11. DIGIT DP, MEET IN THE MIDDLE, GAME THEORY, TREE DFS    ║
║  Level 5 — Advanced Recursion (GM Level)                     ║
╚══════════════════════════════════════════════════════════════╝

These are the HARDEST recursion patterns. Master these and you're
ready for Codeforces Div 1 C/D problems.

🎯 Topics:
   1. Digit DP — Count numbers with property in range [L, R]
   2. Meet in the Middle — Split + combine (like 2-pointer on recursion)
   3. Sprague-Grundy — Game theory with recursion
   4. Tree DFS — Subtree DP, Rerooting technique
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
#include <functional>
#include <unordered_map>

using namespace std;

using i64 = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;

constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD = 1'000'000'007LL;

#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

template<class T>
void read(vec<T> &v) { for (auto &x : v) cin >> x; }


// ═══════════════════════════════════════════════════════════
// 1️⃣ DIGIT DP — Count numbers in [1, N] with digit sum = S
// ═══════════════════════════════════════════════════════════
/*
   Digit DP is a recursion pattern to count numbers in range [L, R]
   satisfying some digit-based property.

   🧠 KEY IDEA: Build the number digit by digit, left to right.

   State: (position, tight, some_property)

   - position: which digit we're filling (0 to len-1)
   - tight: are we still bounded by the upper limit?
     If tight = true, current digit can be at most digits[pos]
     If tight = false, current digit can be 0-9
   - property: whatever we're tracking (digit sum, etc.)

   ════════════════════════════════════════════════
   TEMPLATE:
   ════════════════════════════════════════════════

   i64 solve(int pos, bool tight, int property, string& num) {
       if (pos == len) return (property satisfies condition);
       if (cached) return cache;

       int limit = tight ? (num[pos] - '0') : 9;
       i64 result = 0;

       for (int digit = 0; digit <= limit; digit++) {
           result += solve(pos + 1,
                          tight && (digit == limit),
                          update_property(property, digit),
                          num);
       }
       return cache = result;
   }

   answer for [L, R] = count(R) - count(L - 1)

   ════════════════════════════════════════════════

   Example: Count numbers in [1, N] whose digit sum equals S

   Time: O(positions * 2 * max_sum * 10) per digit
*/
class DigitDP {
    string num;
    int targetSum;
    // dp[pos][tight][currentSum]
    // tight is 0 or 1, currentSum up to 9*18 = 162
    i64 dp[20][2][200];
    bool visited[20][2][200];

    i64 solve(int pos, bool tight, int curSum) {
        if (curSum > targetSum) return 0;  // Pruning
        if (pos == sz(num)) {
            return (curSum == targetSum) ? 1 : 0;
        }

        if (visited[pos][tight][curSum]) return dp[pos][tight][curSum];
        visited[pos][tight][curSum] = true;

        int limit = tight ? (num[pos] - '0') : 9;
        i64 result = 0;

        for (int d = 0; d <= limit; d++) {
            result += solve(pos + 1, tight && (d == limit), curSum + d);
        }

        return dp[pos][tight][curSum] = result;
    }

public:
    // Count numbers in [1, N] with digit sum = S
    i64 countWithDigitSum(i64 N, int S) {
        if (N <= 0) return 0;
        num = to_string(N);
        targetSum = S;
        memset(visited, 0, sizeof(visited));
        return solve(0, true, 0);
    }

    // Count in range [L, R]
    i64 countInRange(i64 L, i64 R, int S) {
        return countWithDigitSum(R, S) - countWithDigitSum(L - 1, S);
    }
};


// ═══════════════════════════════════════════════════════════
// 2️⃣ MEET IN THE MIDDLE
// ═══════════════════════════════════════════════════════════
/*
   When n is too large for 2^n but small enough for 2 * 2^(n/2).

   Split array into two halves, generate all subsets for each half,
   then combine cleverly.

   n ≤ 40: 2^40 too large, but 2 * 2^20 ≈ 2M is fine!

   🧠 PATTERN:
   1. Split into halves A and B
   2. Generate all 2^(n/2) subset sums for each half
   3. Sort one half
   4. For each sum in other half, binary search for complement

   Example: Count subsets with sum = T (where n ≤ 40)
*/

// Count subsets of arr[0..n-1] with sum exactly = target
i64 meetInMiddle(vec<i64>& arr, i64 target) {
    int n = sz(arr);
    int half = n / 2;

    // Generate all subset sums for first half
    vec<i64> leftSums;
    for (int mask = 0; mask < (1 << half); mask++) {
        i64 sum = 0;
        for (int i = 0; i < half; i++)
            if ((mask >> i) & 1) sum += arr[i];
        leftSums.pb(sum);
    }

    // Generate all subset sums for second half
    vec<i64> rightSums;
    int half2 = n - half;
    for (int mask = 0; mask < (1 << half2); mask++) {
        i64 sum = 0;
        for (int i = 0; i < half2; i++)
            if ((mask >> i) & 1) sum += arr[half + i];
        rightSums.pb(sum);
    }

    // Sort right half and binary search
    sort(all(rightSums));

    i64 count = 0;
    for (i64 ls : leftSums) {
        i64 need = target - ls;
        // Count occurrences of `need` in rightSums
        count += upper_bound(all(rightSums), need) - lower_bound(all(rightSums), need);
    }

    return count;
}

// Meet in Middle: Closest subset sum to target
// Find subset with sum closest to T (when n ≤ 40)
i64 closestSubsetSum(vec<i64>& arr, i64 target) {
    int n = sz(arr);
    int half = n / 2;

    vec<i64> leftSums;
    for (int mask = 0; mask < (1 << half); mask++) {
        i64 sum = 0;
        for (int i = 0; i < half; i++)
            if ((mask >> i) & 1) sum += arr[i];
        leftSums.pb(sum);
    }

    vec<i64> rightSums;
    int half2 = n - half;
    for (int mask = 0; mask < (1 << half2); mask++) {
        i64 sum = 0;
        for (int i = 0; i < half2; i++)
            if ((mask >> i) & 1) sum += arr[half + i];
        rightSums.pb(sum);
    }

    sort(all(rightSums));

    i64 bestDiff = INF64;
    for (i64 ls : leftSums) {
        i64 need = target - ls;
        // Find closest in rightSums using lower_bound
        auto it = lower_bound(all(rightSums), need);
        if (it != rightSums.end()) {
            bestDiff = min(bestDiff, abs(ls + *it - target));
        }
        if (it != rightSums.begin()) {
            --it;
            bestDiff = min(bestDiff, abs(ls + *it - target));
        }
    }

    return target - bestDiff;  // Return closest achievable sum
}


// ═══════════════════════════════════════════════════════════
// 3️⃣ SPRAGUE-GRUNDY THEOREM (Game Theory)
// ═══════════════════════════════════════════════════════════
/*
   For impartial games (both players have same moves):

   Grundy number g(state):
   - g(losing state) = 0
   - g(state) = mex({g(next_state) for all possible moves})

   mex = Minimum EXcludant = smallest non-negative integer NOT in set

   For combined games: XOR of Grundy numbers
   If XOR > 0: first player wins
   If XOR = 0: second player wins

   This is THE technique for solving game problems on Codeforces!
*/

int mex(set<int>& s) {
    int val = 0;
    while (s.count(val)) val++;
    return val;
}

// Example: Nim-like game
// Given piles, each move: remove 1, 2, or 3 stones from one pile
// Who wins? (First player or Second player)
int grundy(int n, vec<int>& memo) {
    if (n == 0) return 0;
    if (memo[n] != -1) return memo[n];

    set<int> reachable;
    for (int move = 1; move <= 3 && move <= n; move++) {
        reachable.insert(grundy(n - move, memo));
    }

    return memo[n] = mex(reachable);
}

string whoWins(vec<int>& piles) {
    int xorSum = 0;
    int maxPile = *max_element(all(piles));
    vec<int> memo(maxPile + 1, -1);

    for (int pile : piles) {
        xorSum ^= grundy(pile, memo);
    }

    return xorSum > 0 ? "First" : "Second";
}


// ═══════════════════════════════════════════════════════════
// 4️⃣ TREE DFS — Subtree DP & Rerooting
// ═══════════════════════════════════════════════════════════
/*
   🌳 Tree problems often use recursive DFS.

   Pattern A: SUBTREE DP
   Process children first, then combine at parent.

   dp[v] = some function of dp[children of v]

   Pattern B: REROOTING (very powerful!)
   Compute answer for root, then "reroot" to each child in O(1).
   Total: O(n) instead of O(n^2)
*/

// Example: Find the farthest node from each node (diameter-related)
// Subtree DP: compute depth of subtree rooted at each node

class TreeDP {
    int n;
    vvec<int> adj;
    vec<i64> subtreeSize;
    vec<i64> depth;
    vec<i64> answer;  // answer[v] = sum of distances from v to all other nodes

    // DFS 1: Compute subtree sizes and answer for root
    void dfs1(int u, int parent, int d) {
        subtreeSize[u] = 1;
        depth[u] = d;
        for (int v : adj[u]) {
            if (v == parent) continue;
            dfs1(v, u, d + 1);
            subtreeSize[u] += subtreeSize[v];
        }
    }

    // DFS 2: Rerooting — compute answer for all nodes
    void dfs2(int u, int parent) {
        for (int v : adj[u]) {
            if (v == parent) continue;
            // When we move root from u to v:
            // - Nodes in subtree(v): distance decreases by 1 → subtract subtreeSize[v]
            // - Nodes NOT in subtree(v): distance increases by 1 → add (n - subtreeSize[v])
            answer[v] = answer[u] - subtreeSize[v] + (n - subtreeSize[v]);
            dfs2(v, u);
        }
    }

public:
    // Sum of distances from each node to all other nodes
    // LC 834: Sum of Distances in Tree
    vec<i64> sumOfDistances(int _n, vvec<int>& edges) {
        n = _n;
        adj.assign(n, {});
        for (auto& e : edges) {
            adj[e[0]].pb(e[1]);
            adj[e[1]].pb(e[0]);
        }

        subtreeSize.assign(n, 0);
        depth.assign(n, 0);
        answer.assign(n, 0);

        // Step 1: Root at 0, compute subtree sizes and answer[0]
        dfs1(0, -1, 0);

        // answer[0] = sum of all depths
        for (int i = 0; i < n; i++) answer[0] += depth[i];

        // Step 2: Reroot to compute all answers
        dfs2(0, -1);

        return answer;
    }
};


// ═══════════════════════════════════════════════════════════
// 5️⃣ RECURSIVE SEGMENT TREE — Build & Query
// ═══════════════════════════════════════════════════════════
/*
   Segment tree is fundamentally recursive!

   Build: split range into halves, recurse, combine
   Query: if range inside query → return; else recurse on halves
   Update: find position, update, recombine going up
*/
class SegTree {
    int n;
    vec<i64> tree;

    void build(vec<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = (start + end) / 2;
        build(arr, 2*node, start, mid);
        build(arr, 2*node+1, mid+1, end);
        tree[node] = tree[2*node] + tree[2*node+1];
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid) update(2*node, start, mid, idx, val);
        else update(2*node+1, mid+1, end, idx, val);
        tree[node] = tree[2*node] + tree[2*node+1];
    }

    i64 query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;           // Out of range
        if (l <= start && end <= r) return tree[node]; // Fully inside
        int mid = (start + end) / 2;
        return query(2*node, start, mid, l, r) + query(2*node+1, mid+1, end, l, r);
    }

public:
    void init(vec<int>& arr) {
        n = sz(arr);
        tree.assign(4 * n, 0);
        build(arr, 1, 0, n - 1);
    }

    void update(int idx, int val) { update(1, 0, n - 1, idx, val); }
    i64 query(int l, int r) { return query(1, 0, n - 1, l, r); }
};


// ═══════════════════════════════════════════════════════════
// 🧪 TEST
// ═══════════════════════════════════════════════════════════

void solve() {
    // 1. Digit DP
    {
        cout << "=== DIGIT DP ===" << nl;
        DigitDP ddp;
        cout << "Numbers in [1, 100] with digit sum 5: "
             << ddp.countWithDigitSum(100, 5) << nl;
        // 5, 14, 23, 32, 41, 50 → 6
        cout << "Numbers in [1, 1000] with digit sum 10: "
             << ddp.countWithDigitSum(1000, 10) << nl;
    }

    // 2. Meet in the Middle
    {
        cout << nl << "=== MEET IN THE MIDDLE ===" << nl;
        vec<i64> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        cout << "Subsets with sum = 15: " << meetInMiddle(arr, 15) << nl;
    }

    // 3. Game Theory
    {
        cout << nl << "=== SPRAGUE-GRUNDY ===" << nl;
        vec<int> piles = {3, 4, 5};
        cout << "Piles [3,4,5]: " << whoWins(piles) << " player wins" << nl;
    }

    // 4. Tree Rerooting
    {
        cout << nl << "=== TREE DFS REROOTING ===" << nl;
        int n = 6;
        vvec<int> edges = {{0,1}, {0,2}, {2,3}, {2,4}, {2,5}};
        TreeDP tdp;
        auto ans = tdp.sumOfDistances(n, edges);
        cout << "Sum of distances from each node:" << nl;
        for (int i = 0; i < n; i++) {
            cout << "Node " << i << ": " << ans[i] << nl;
        }
    }

    // 5. Segment Tree
    {
        cout << nl << "=== SEGMENT TREE ===" << nl;
        vec<int> arr = {1, 3, 5, 7, 9, 11};
        SegTree st;
        st.init(arr);
        cout << "Sum [1,3] = " << st.query(1, 3) << nl;  // 3+5+7 = 15
        st.update(2, 10);  // arr[2] = 10
        cout << "After update(2,10): Sum [1,3] = " << st.query(1, 3) << nl;  // 3+10+7 = 20
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int TC = 1;
    while (TC--) solve();

    return 0;
}

