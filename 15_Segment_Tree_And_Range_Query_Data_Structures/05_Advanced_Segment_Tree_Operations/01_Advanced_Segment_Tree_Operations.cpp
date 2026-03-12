/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║        LEVEL 4 — ADVANCED SEGMENT TREE OPERATIONS                              ║
║        Custom Nodes, Max Subarray Sum, Kth Element, Merge Technique            ║
║        Author: Sarvan Yaduvanshi                                               ║
╚══════════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Range Minimum with Index Tracking
 2. Maximum Subarray Sum (Kadane's on Segment Tree) — GSS1/GSS3
 3. Range Majority Queries (Boyer-Moore on Segment Tree)
 4. Range Kth Element Queries
 5. Segment Tree with Custom/Complex Nodes
 6. Merge Segments Technique — The Key to All of These

KEY INSIGHT:
──────────────
Advanced ST operations require CUSTOM NODE STRUCTURES.
Instead of storing a single value per node, we store a STRUCT
with multiple fields, and define a custom MERGE function.

The merge function must be ASSOCIATIVE:
  merge(merge(A, B), C) == merge(A, merge(B, C))

═══════════════════════════════════════════════════════════════
SECTION 1: RANGE MINIMUM WITH INDEX
═══════════════════════════════════════════════════════════════

Store (min_value, min_index) in each node.
Merge: take the pair with smaller value.

  a[] = {3, 1, 4, 1, 5}

  Node stores: {value, index}
                  {1, 1}
                /        \
          {1, 1}          {1, 3}
          /    \          /    \
      {1, 1} {4, 2}   {1, 3} {5, 4}
      /   \
   {3,0} {1,1}

  query_min(2, 4) → {1, 3} (minimum is 1 at index 3)

═══════════════════════════════════════════════════════════════
SECTION 2: MAXIMUM SUBARRAY SUM (KADANE on Segment Tree)
═══════════════════════════════════════════════════════════════

This is the CLASSIC advanced segment tree problem (SPOJ GSS1/GSS3).

PROBLEM: Given array with positive AND negative numbers,
         find maximum sum subarray in range [l, r].

WHY is this hard?
  The max subarray might START in the left half and END in the right half!
  We can't just take max(left_answer, right_answer).

SOLUTION: Store 4 values in each node:
  • total_sum: sum of entire range
  • prefix_max: maximum prefix sum (starts from left)
  • suffix_max: maximum suffix sum (ends at right)
  • answer:     maximum subarray sum anywhere in range

MERGE(left, right):
  total_sum  = left.total + right.total
  prefix_max = max(left.prefix, left.total + right.prefix)
  suffix_max = max(right.suffix, right.total + left.suffix)
  answer     = max(left.answer, right.answer, left.suffix + right.prefix)
                    ↑ entirely in left
                              ↑ entirely in right
                                            ↑ crosses the boundary!

DRY RUN for a[] = {2, -1, 3, -2, 4}:

  Leaves:
    [2]:  total=2,  prefix=2,  suffix=2,  ans=2
    [-1]: total=-1, prefix=-1, suffix=-1, ans=-1
    [3]:  total=3,  prefix=3,  suffix=3,  ans=3
    [-2]: total=-2, prefix=-2, suffix=-2, ans=-2
    [4]:  total=4,  prefix=4,  suffix=4,  ans=4

  Merge [2] and [-1]:  (range [0,1])
    total = 2 + (-1) = 1
    prefix = max(2, 2+(-1)) = max(2, 1) = 2
    suffix = max(-1, -1+2) = max(-1, 1) = 1
    ans = max(2, -1, 2+(-1)) = max(2, -1, 1) = 2

  Merge [3] and [-2,4]:
    First, merge [-2] and [4]: (range [3,4])
      total = -2 + 4 = 2
      prefix = max(-2, -2+4) = max(-2, 2) = 2
      suffix = max(4, 4+(-2)) = max(4, 2) = 4
      ans = max(-2, 4, -2+4) = max(-2, 4, 2) = 4

    Now merge [3] and [-2,4]: (range [2,4])
      total = 3 + 2 = 5
      prefix = max(3, 3+2) = 5
      suffix = max(4, 2+3) = max(4, 5) = 5
      ans = max(3, 4, 3+2) = max(3, 4, 5) = 5

  Merge [0,1] and [2,4]: (range [0,4])
    total = 1 + 5 = 6
    prefix = max(2, 1+5) = max(2, 6) = 6
    suffix = max(5, 5+1) = max(5, 6) = 6
    ans = max(2, 5, 1+5) = max(2, 5, 6) = 6

  Max subarray sum of entire array = 6
  This is: 2 + (-1) + 3 + (-2) + 4 = 6 ✓
  (or equivalently the subarray [0,4])

  Query for [1, 3]: elements -1, 3, -2
    ans should be 3 (just element at index 2)
    Or 2 = (-1) + 3

    Merge [-1] and [3]: range [1,2]
      total = 2, prefix = max(-1, 2) = 2, suffix = max(3, 2) = 3, ans = max(-1, 3, -1+3) = 3
    Wait, the max is actually 3 (just the element 3).
    But also -1+3=2 which is less. So ans = 3.

    Merge [1,2] and [-2]: range [1,3]
      total = 0, prefix = max(2, 2+(-2)) = 2, suffix = max(-2, -2+2) = 0, ans = max(3, -2, 3+(-2)) = max(3, -2, 1) = 3 ✓

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

// --- Macros ---
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define nl '\n'

// ═══════════════════════════════════════════════════════════════
// IMPLEMENTATION 1: Range Minimum with Index
// ═══════════════════════════════════════════════════════════════

class MinIndexSegTree {
    int n;
    vector<pair<long long, int>> tree; // {min_value, min_index}

    pair<long long, int> merge(pair<long long, int> a, pair<long long, int> b) {
        return (a.first <= b.first) ? a : b;
    }

    void build(const vector<int>& a, int node, int s, int e) {
        if (s == e) { tree[node] = {a[s], s}; return; }
        int mid = (s + e) / 2;
        build(a, 2*node, s, mid);
        build(a, 2*node+1, mid+1, e);
        tree[node] = merge(tree[2*node], tree[2*node+1]);
    }

    pair<long long, int> query(int node, int s, int e, int l, int r) {
        if (r < s || e < l) return {LLONG_MAX, -1};
        if (l <= s && e <= r) return tree[node];
        int mid = (s + e) / 2;
        return merge(query(2*node, s, mid, l, r), query(2*node+1, mid+1, e, l, r));
    }

    void update(int node, int s, int e, int idx, int val) {
        if (s == e) { tree[node] = {val, idx}; return; }
        int mid = (s + e) / 2;
        if (idx <= mid) update(2*node, s, mid, idx, val);
        else update(2*node+1, mid+1, e, idx, val);
        tree[node] = merge(tree[2*node], tree[2*node+1]);
    }

public:
    MinIndexSegTree(const vector<int>& a) : n(a.size()), tree(4 * a.size()) {
        build(a, 1, 0, n-1);
    }

    pair<long long, int> query(int l, int r) { return query(1, 0, n-1, l, r); }
    void update(int idx, int val) { update(1, 0, n-1, idx, val); }
};

void demoMinIndex() {
    cout << "═══ RANGE MINIMUM WITH INDEX ═══\n\n";

    vector<int> a = {3, 1, 4, 1, 5, 9, 2, 6};
    cout << "Array: ";
    for (int x : a) cout << x << " ";
    cout << "\n\n";

    MinIndexSegTree st(a);

    auto [val1, idx1] = st.query(0, 7);
    cout << "min(0, 7) = " << val1 << " at index " << idx1 << "\n";

    auto [val2, idx2] = st.query(2, 5);
    cout << "min(2, 5) = " << val2 << " at index " << idx2 << "\n";

    auto [val3, idx3] = st.query(4, 7);
    cout << "min(4, 7) = " << val3 << " at index " << idx3 << "\n\n";

    cout << "Update: a[6] = 0\n";
    st.update(6, 0);
    auto [val4, idx4] = st.query(0, 7);
    cout << "min(0, 7) = " << val4 << " at index " << idx4 << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// IMPLEMENTATION 2: Maximum Subarray Sum (SPOJ GSS1/GSS3)
// ═══════════════════════════════════════════════════════════════

struct Node {
    long long total, prefix, suffix, answer;

    Node() : total(0), prefix(LLONG_MIN), suffix(LLONG_MIN), answer(LLONG_MIN) {}
    Node(long long val) : total(val), prefix(val), suffix(val), answer(val) {}
};

Node mergeNodes(const Node& L, const Node& R) {
    Node res;
    res.total = L.total + R.total;
    res.prefix = max(L.prefix, L.total + R.prefix);
    res.suffix = max(R.suffix, R.total + L.suffix);
    res.answer = max({L.answer, R.answer, L.suffix + R.prefix});
    return res;
}

class MaxSubarraySegTree {
    int n;
    vector<Node> tree;

    void build(const vector<int>& a, int node, int s, int e) {
        if (s == e) { tree[node] = Node(a[s]); return; }
        int mid = (s + e) / 2;
        build(a, 2*node, s, mid);
        build(a, 2*node+1, mid+1, e);
        tree[node] = mergeNodes(tree[2*node], tree[2*node+1]);
    }

    Node query(int node, int s, int e, int l, int r) {
        if (r < s || e < l) return Node(); // identity
        if (l <= s && e <= r) return tree[node];
        int mid = (s + e) / 2;
        Node leftRes = query(2*node, s, mid, l, r);
        Node rightRes = query(2*node+1, mid+1, e, l, r);
        if (leftRes.answer == LLONG_MIN) return rightRes;
        if (rightRes.answer == LLONG_MIN) return leftRes;
        return mergeNodes(leftRes, rightRes);
    }

    void update(int node, int s, int e, int idx, int val) {
        if (s == e) { tree[node] = Node(val); return; }
        int mid = (s + e) / 2;
        if (idx <= mid) update(2*node, s, mid, idx, val);
        else update(2*node+1, mid+1, e, idx, val);
        tree[node] = mergeNodes(tree[2*node], tree[2*node+1]);
    }

public:
    MaxSubarraySegTree(const vector<int>& a) : n(a.size()), tree(4 * a.size()) {
        build(a, 1, 0, n-1);
    }

    long long query(int l, int r) { return query(1, 0, n-1, l, r).answer; }
    void update(int idx, int val) { update(1, 0, n-1, idx, val); }

    void printNode(int l, int r) {
        Node res = query(1, 0, n-1, l, r);
        cout << "  [" << l << "," << r << "]: total=" << res.total
             << " prefix=" << res.prefix << " suffix=" << res.suffix
             << " answer=" << res.answer << "\n";
    }
};

void demoMaxSubarray() {
    cout << "═══ MAXIMUM SUBARRAY SUM (GSS1/GSS3 Style) ═══\n\n";

    vector<int> a = {2, -1, 3, -2, 4, -5, 1};
    cout << "Array: ";
    for (int x : a) cout << x << " ";
    cout << "\n\n";

    MaxSubarraySegTree st(a);

    cout << "Node values:\n";
    st.printNode(0, 6);
    st.printNode(0, 2);
    st.printNode(3, 6);
    cout << "\n";

    cout << "Max subarray sum queries:\n";
    cout << "  [0, 6] = " << st.query(0, 6) << " (2-1+3-2+4 = 6)\n";
    cout << "  [0, 2] = " << st.query(0, 2) << " (2-1+3 = 4)\n";
    cout << "  [1, 3] = " << st.query(1, 3) << " (-1+3 = 2 or just 3)\n";
    cout << "  [4, 6] = " << st.query(4, 6) << " (4)\n";
    cout << "  [5, 6] = " << st.query(5, 6) << " (1)\n\n";

    cout << "DRY RUN — merge for query [1, 3]:\n";
    cout << "  Left = [-1]:    total=-1, prefix=-1, suffix=-1, ans=-1\n";
    cout << "  Right = [3,-2]: total=1,  prefix=3,  suffix=-2→max(-2,1)=-2? \n";
    cout << "    Actually merge [3] and [-2]:\n";
    cout << "      total=1, prefix=max(3,3-2)=3, suffix=max(-2,-2+3)=1, ans=max(3,-2,3+(-2))=3\n";
    cout << "  Now merge [-1] with {total=1,prefix=3,suffix=1,ans=3}:\n";
    cout << "    total = -1+1 = 0\n";
    cout << "    prefix = max(-1, -1+3) = 2\n";
    cout << "    suffix = max(1, 1+(-1)) = 1\n";
    cout << "    ans = max(-1, 3, -1+3) = max(-1, 3, 2) = 3\n";
    cout << "  Answer = 3 ✓ (subarray [3] alone)\n\n";

    // Update demo
    cout << "Update: a[5] = 10 (was -5)\n";
    st.update(5, 10);
    cout << "Array now: [2, -1, 3, -2, 4, 10, 1]\n";
    cout << "  [0, 6] = " << st.query(0, 6) << " (entire array sum = 17)\n";
    cout << "  [3, 6] = " << st.query(3, 6) << " (-2+4+10+1 = 13)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// IMPLEMENTATION 3: Bracket Sequence (Sereja CF 380C Style)
// ═══════════════════════════════════════════════════════════════
/*
  PROBLEM: Given bracket string, query max matched brackets in [l, r].

  NODE stores: {matched, open, close}
    matched = count of matched pairs
    open = remaining unmatched '(' after matching
    close = remaining unmatched ')' after matching

  MERGE(L, R):
    new_matches = min(L.open, R.close)  ← left's open matches right's close
    matched = L.matched + R.matched + new_matches
    open = L.open + R.open - new_matches
    close = L.close + R.close - new_matches
*/

struct BracketNode {
    int matched, open, close;
    BracketNode() : matched(0), open(0), close(0) {}
    BracketNode(char c) : matched(0), open(c == '(' ? 1 : 0), close(c == ')' ? 1 : 0) {}
};

BracketNode mergeBracket(const BracketNode& L, const BracketNode& R) {
    BracketNode res;
    int new_matches = min(L.open, R.close);
    res.matched = L.matched + R.matched + new_matches;
    res.open = L.open + R.open - new_matches;
    res.close = L.close + R.close - new_matches;
    return res;
}

class BracketSegTree {
    int n;
    vector<BracketNode> tree;

    void build(const string& s, int node, int start, int end) {
        if (start == end) { tree[node] = BracketNode(s[start]); return; }
        int mid = (start + end) / 2;
        build(s, 2*node, start, mid);
        build(s, 2*node+1, mid+1, end);
        tree[node] = mergeBracket(tree[2*node], tree[2*node+1]);
    }

    BracketNode query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return BracketNode();
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        return mergeBracket(query(2*node, start, mid, l, r),
                            query(2*node+1, mid+1, end, l, r));
    }

public:
    BracketSegTree(const string& s) : n(s.size()), tree(4 * s.size()) {
        build(s, 1, 0, n-1);
    }

    int query(int l, int r) {
        return query(1, 0, n-1, l, r).matched * 2; // matched pairs × 2 = characters
    }
};

void demoBracket() {
    cout << "═══ BRACKET MATCHING (SEREJA CF 380C) ═══\n\n";

    string s = "())(())()(";
    cout << "String: " << s << "\n";
    cout << "Index:  0123456789\n\n";

    BracketSegTree st(s);

    cout << "Max matched brackets in range:\n";
    cout << "  [0, 9] = " << st.query(0, 9) << " chars\n";
    cout << "  [0, 3] = " << st.query(0, 3) << " chars  ('())(' → '()' matched = 2)\n";
    cout << "  [1, 6] = " << st.query(1, 6) << " chars\n";
    cout << "  [4, 7] = " << st.query(4, 7) << " chars  ('())(' → no wait, '())(': (())=4)\n\n";

    cout << "DRY RUN — merge for [0,3] = '())(': \n";
    cout << "  '(' : {matched=0, open=1, close=0}\n";
    cout << "  ')' : {matched=0, open=0, close=1}\n";
    cout << "  Merge '()': new_matches = min(1,1)=1\n";
    cout << "    {matched=1, open=0, close=0}\n";
    cout << "  ')' : {matched=0, open=0, close=1}\n";
    cout << "  Merge: new_matches = min(0,1)=0\n";
    cout << "    {matched=1, open=0, close=1}\n";
    cout << "  '(' : {matched=0, open=1, close=0}\n";
    cout << "  Merge: new_matches = min(0,0)=0\n";
    cout << "    {matched=1, open=1, close=1}\n";
    cout << "  Answer = 1 pair × 2 = 2 ✓\n\n";
}

// ═══════════════════════════════════════════════════════════════
// IMPLEMENTATION 4: Number of Minimums on a Segment
// ═══════════════════════════════════════════════════════════════
/*
  Store: {min_value, min_count}
  Merge: If min_values equal, add counts.
         Otherwise, take the smaller one's count.
*/

struct MinCountNode {
    long long minVal;
    int count;
    MinCountNode() : minVal(LLONG_MAX), count(0) {}
    MinCountNode(long long v) : minVal(v), count(1) {}
    MinCountNode(long long v, int c) : minVal(v), count(c) {}
};

MinCountNode mergeMinCount(const MinCountNode& a, const MinCountNode& b) {
    if (a.minVal < b.minVal) return a;
    if (b.minVal < a.minVal) return b;
    return {a.minVal, a.count + b.count};
}

void demoMinCount() {
    cout << "═══ NUMBER OF MINIMUMS ON A SEGMENT ═══\n\n";

    vector<int> a = {3, 1, 4, 1, 5, 1, 2, 6};
    cout << "Array: ";
    for (int x : a) cout << x << " ";
    cout << "\n\n";

    // Quick implementation inline
    int n = a.size();
    vector<MinCountNode> tree(4 * n);

    function<void(int, int, int)> build = [&](int node, int s, int e) {
        if (s == e) { tree[node] = MinCountNode(a[s]); return; }
        int mid = (s + e) / 2;
        build(2*node, s, mid);
        build(2*node+1, mid+1, e);
        tree[node] = mergeMinCount(tree[2*node], tree[2*node+1]);
    };

    function<MinCountNode(int, int, int, int, int)> query = [&](int node, int s, int e, int l, int r) -> MinCountNode {
        if (r < s || e < l) return MinCountNode();
        if (l <= s && e <= r) return tree[node];
        int mid = (s + e) / 2;
        return mergeMinCount(query(2*node, s, mid, l, r), query(2*node+1, mid+1, e, l, r));
    };

    build(1, 0, n-1);

    auto res1 = query(1, 0, n-1, 0, 7);
    cout << "min(0,7) = " << res1.minVal << ", count = " << res1.count << "\n";

    auto res2 = query(1, 0, n-1, 2, 5);
    cout << "min(2,5) = " << res2.minVal << ", count = " << res2.count << "\n";

    auto res3 = query(1, 0, n-1, 4, 7);
    cout << "min(4,7) = " << res3.minVal << ", count = " << res3.count << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║   LEVEL 4: ADVANCED SEGMENT TREE OPERATIONS                ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n\n";

    demoMinIndex();
    demoMaxSubarray();
    demoBracket();
    demoMinCount();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "  KEY TAKEAWAYS:\n";
    cout << "  1. Advanced ST = Custom Node struct + Custom Merge\n";
    cout << "  2. Max Subarray Sum: store (total, prefix, suffix, answer)\n";
    cout << "  3. Bracket Matching: store (matched, open, close)\n";
    cout << "  4. Min with Count: store (minVal, count)\n";
    cout << "  5. Merge must be ASSOCIATIVE!\n";
    cout << "  6. Think: 'What info from children do I need?'\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

