<div align="center">

# 🌲 Segment Tree & Range Query Data Structures — Zero to GM/ICPC

### The Ultimate Competitive Programming Range Query Mastery Guide

[![C++17](https://img.shields.io/badge/C%2B%2B-17%2F20-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Chapters](https://img.shields.io/badge/Chapters-15-blueviolet?style=for-the-badge)](.)
[![Difficulty](https://img.shields.io/badge/Level-Zero%20→%20ICPC%20/%20GM-red?style=for-the-badge)](.)
[![Author](https://img.shields.io/badge/Author-Sarvan%20Yaduvanshi-green?style=for-the-badge)](https://github.com/Sarvan-Yaduvanshi)

> *"Segment Trees are the Swiss Army Knife of competitive programming. Master them, and no range query will ever scare you — from Div2A to ICPC Finals."*  
> — **Sarvan Yaduvanshi**

</div>

---

## 📖 About This Module

This module is the **most comprehensive Segment Tree & Range Query resource** ever created for competitive programmers. It covers **every data structure and technique** you need — from basic prefix sums all the way to **Wavelet Trees, Li Chao Trees, and Segment Tree Beats** used in ICPC World Finals and Grandmaster-rated Codeforces rounds.

**What makes this different?**
- 🧠 **Concept-first approach** — Every structure explained with internals, visualizations, and intuition
- 🌲 **15 progressive levels** — From "What is a range query?" to ICPC-level structures
- 💻 **Separate .cpp per concept** — Clean, focused, runnable files with full test cases
- 📊 **Complexity tables** — Build/Query/Update/Space for every structure at a glance
- 🏆 **150+ curated problems** — From LeetCode, CSES, Codeforces, CodeChef, SPOJ, AtCoder, GFG
- 🎯 **GM/ICPC-level techniques** — Persistent ST, HLD, Wavelet Tree, Li Chao Tree, ST Beats
- 🔄 **Progressive difficulty** — From prefix sums to World Finals data structures
- ⚡ **Battle-tested templates** — Ready-to-use in contests

---

## 🗂️ Chapter Index

### 🟢 LEVEL 0–2 — Foundation (Newbie → Pupil → Specialist)

| # | Chapter | Key Topics | Difficulty |
|:-:|---------|------------|:----------:|
| 01 | [**Range Query Foundations**](01_Range_Query_Foundations/) | Range query concepts, Static vs Dynamic queries, Prefix Sum 1D/2D, Difference Array 1D/2D, Offline vs Online queries, Range Update vs Point Update, Range Update vs Range Query | ⭐ |
| 02 | [**Segment Tree Basics**](02_Segment_Tree_Basics/) | Segment Tree structure & representation, Tree in array format, Build O(n), Range Query O(log n), Point Update O(log n), Recursive & Iterative implementations, Time & Space complexity analysis, 4N memory rule | ⭐⭐ |
| 03 | [**Segment Tree Variants**](03_Segment_Tree_Variants/) | Range Sum Query, Range Minimum Query (RMQ), Range Maximum Query, GCD Segment Tree, LCM Segment Tree, Count Segment Tree, Frequency Segment Tree, XOR/AND/OR Segment Trees | ⭐⭐ |

### 🟡 LEVEL 3–4 — Intermediate (Specialist → Expert)

| # | Chapter | Key Topics | Difficulty |
|:-:|---------|------------|:----------:|
| 04 | [**Lazy Propagation**](04_Lazy_Propagation/) | Why we need Lazy Propagation, Lazy propagation concept & internals, Range Add + Range Sum Query, Range Assignment + Range Query, Range Add + Range Max/Min Query, Range XOR with Lazy, Combined/Multi-operation Lazy, Push-down mechanics | ⭐⭐⭐ |
| 05 | [**Advanced Segment Tree Operations**](05_Advanced_Segment_Tree_Operations/) | Range Minimum with Index tracking, Maximum Subarray Sum on Segment Tree (Kadane's on ST), Range Majority Queries (Boyer-Moore on ST), Range Kth Element Queries, Segment Tree with Custom/Complex Nodes, Merge Segments technique, Segment Tree of Vectors | ⭐⭐⭐⭐ |

### 🔴 LEVEL 5–8 — Advanced (Expert → Candidate Master)

| # | Chapter | Key Topics | Difficulty |
|:-:|---------|------------|:----------:|
| 06 | [**Persistent Segment Tree**](06_Persistent_Segment_Tree/) | Persistence concept & path copying, Versioned segment trees, Kth Smallest in Range queries, Counting elements in range [L,R] with value in [a,b], Offline range queries with persistence, Persistent + Lazy (functional updates) | ⭐⭐⭐⭐ |
| 07 | [**Fenwick Tree / Binary Indexed Tree**](07_Fenwick_Tree_BIT/) | BIT structure & internals (lowbit trick), Prefix Sum Queries O(log n), Point Update O(log n), Range Sum Queries, O(n) Build technique, BIT vs Segment Tree comparison, BIT optimizations & tricks, 0-indexed vs 1-indexed BIT | ⭐⭐⭐ |
| 08 | [**Advanced Fenwick Tree**](08_Advanced_Fenwick_Tree/) | Range Update + Point Query BIT, Point Update + Range Query BIT, Range Update + Range Query BIT (two BITs trick), 2D Fenwick Tree (2D BIT), Fenwick Tree with Coordinate Compression, Order Statistics with BIT, BIT on permutations (inversions counting) | ⭐⭐⭐⭐ |

### 🟣 LEVEL 8–11 — Master (Candidate Master → Master → International Master)

| # | Chapter | Key Topics | Difficulty |
|:-:|---------|------------|:----------:|
| 09 | [**Sparse Table**](09_Sparse_Table/) | Sparse Table concept & construction O(n log n), Range Minimum Query O(1), Range Maximum Query O(1), GCD/LCM Sparse Table, Idempotent vs Non-Idempotent operations, Disjoint Sparse Table, Sparse Table vs Segment Tree trade-offs | ⭐⭐⭐ |
| 10 | [**Offline Range Query Techniques**](10_Offline_Range_Query_Techniques/) | Mo's Algorithm (sqrt decomposition for queries), Mo's Algorithm with Updates (3D Mo), Mo's Algorithm on Trees, Hilbert Curve ordering optimization, Offline queries with sorting, Block decomposition techniques, Rollback technique | ⭐⭐⭐⭐ |
| 11 | [**Segment Tree + Binary Search**](11_Segment_Tree_Binary_Search/) | Find First Element ≥ X in range, Kth Order Statistics on Segment Tree, Binary Search (Walking) on Segment Tree, Counting elements in value range, Order Statistics Tree concept (PBDS comparison), Merge Sort Tree for range order queries | ⭐⭐⭐⭐ |

### 💎 LEVEL 12–14 — Grandmaster / ICPC (IM → GM → Tourist Level)

| # | Chapter | Key Topics | Difficulty |
|:-:|---------|------------|:----------:|
| 12 | [**Segment Tree on Trees**](12_Segment_Tree_On_Trees/) | Euler Tour / DFS Order flattening, Subtree Queries (sum, min, max on subtree), Path Queries on Trees, Heavy-Light Decomposition (HLD) + Segment Tree, LCA with Sparse Table / Segment Tree, Centroid Decomposition + Range Queries, Small-to-Large merging | ⭐⭐⭐⭐⭐ |
| 13 | [**Multidimensional Segment Trees**](13_Multidimensional_Segment_Trees/) | 2D Segment Tree (Segment Tree of Segment Trees), 2D Range Sum / Min / Max Queries, 2D Range Update, Coordinate Compression for 2D, Fractional Cascading, KD-Tree basics for range queries | ⭐⭐⭐⭐⭐ |
| 14 | [**Advanced Range Query Techniques**](14_Advanced_Range_Query_Techniques/) | Segment Tree Beats (Ji Driver Segment Tree), Divide & Conquer with Segment Tree, Parallel Binary Search, Persistent Segment Tree + Lazy Propagation, Kinetic Segment Tree, Sqrt Decomposition + Segment Tree hybrid | ⭐⭐⭐⭐⭐ |
| 15 | [**ICPC Level Range Structures**](15_ICPC_Level_Range_Structures/) | Wavelet Tree (full theory + implementation), Merge Sort Tree (offline range order queries), Li Chao Tree (convex hull trick on segments), Implicit / Dynamic Segment Tree (sparse nodes), Link-Cut Trees overview, Euler Tour Tree (ETT), Top Tree concepts | ⭐⭐⭐⭐⭐ |

---

## 📊 Master Complexity Reference

### Range Query Data Structures — Complete Cheat Sheet

```
┌───────────────────────────┬───────────┬────────────┬────────────┬────────────┬──────────┐
│ Data Structure            │ Build     │ Point Upd  │ Range Qry  │ Range Upd  │ Space    │
├───────────────────────────┼───────────┼────────────┼────────────┼────────────┼──────────┤
│ Prefix Sum Array          │ O(n)      │ O(n)       │ O(1)       │ N/A        │ O(n)     │
│ Difference Array          │ O(n)      │ N/A        │ O(n)       │ O(1)       │ O(n)     │
│ Sqrt Decomposition        │ O(n)      │ O(1)       │ O(√n)      │ O(√n)      │ O(n)     │
│ Sparse Table              │ O(n logn) │ N/A        │ O(1)*      │ N/A        │ O(n logn)│
│ Segment Tree (basic)      │ O(n)      │ O(logn)    │ O(logn)    │ N/A        │ O(4n)    │
│ Segment Tree (lazy)       │ O(n)      │ O(logn)    │ O(logn)    │ O(logn)    │ O(4n)    │
│ Segment Tree (iterative)  │ O(n)      │ O(logn)    │ O(logn)    │ O(logn)**  │ O(2n)    │
│ Fenwick Tree (BIT)        │ O(n)      │ O(logn)    │ O(logn)    │ N/A        │ O(n)     │
│ BIT (range upd + range q) │ O(n)      │ N/A        │ O(logn)    │ O(logn)    │ O(2n)    │
│ 2D Fenwick Tree           │ O(nm)     │ O(logn·m)  │ O(logn·m)  │ N/A        │ O(nm)    │
│ 2D Segment Tree           │ O(nm)     │ O(log²nm)  │ O(log²nm)  │ O(log²nm)  │ O(4n·4m) │
│ Persistent Segment Tree   │ O(n logn) │ O(logn)*** │ O(logn)    │ N/A        │ O(n logn)│
│ Merge Sort Tree           │ O(n logn) │ N/A        │ O(log²n)   │ N/A        │ O(n logn)│
│ Wavelet Tree              │ O(n logσ) │ N/A        │ O(logσ)    │ N/A        │ O(n logσ)│
│ Li Chao Tree              │ O(n logC) │ O(logC)    │ O(logC)    │ N/A        │ O(n logC)│
│ Mo's Algorithm            │ O(n√n)    │ N/A        │ ~O(1) amrt │ N/A        │ O(n)     │
│ Mo's (with updates)       │ O(n^{5/3})│ incl.      │ ~O(1) amrt │ N/A        │ O(n)     │
│ HLD + Segment Tree        │ O(n)      │ O(log²n)   │ O(log²n)   │ O(log²n)   │ O(n)     │
│ Implicit/Dynamic Seg Tree │ on demand │ O(logn)    │ O(logn)    │ O(logn)    │ O(q logn)│
│ Segment Tree Beats        │ O(n)      │ O(logn)    │ O(logn)    │ O(log²n)†  │ O(4n)    │
└───────────────────────────┴───────────┴────────────┴────────────┴────────────┴──────────┘

*   Sparse Table: O(1) only for idempotent operations (min, max, GCD). For sum: O(logn).
**  Iterative ST: Lazy propagation is complex; recursive is easier for lazy.
*** Persistent ST: Creates a new version per update = O(logn) new nodes.
†   Segment Tree Beats: Amortized O(log²n) for chmin/chmax range updates.
σ   = alphabet/value range size.  C = coordinate range.
```

---

## 🧭 When to Use What? — Decision Flowchart

```
Is the array STATIC (no updates)?
├── YES → Is the operation IDEMPOTENT (min, max, GCD)?
│         ├── YES → ✅ Sparse Table (O(1) query, O(n logn) build)
│         └── NO  → ✅ Prefix Sum (O(1) query for sum)
│
└── NO (array has UPDATES) → What kind of updates?
    │
    ├── POINT UPDATES only?
    │   ├── Need range SUM? → ✅ Fenwick Tree (BIT) — simplest & fastest
    │   ├── Need range MIN/MAX/GCD? → ✅ Segment Tree (basic, no lazy needed)
    │   ├── Need kth element / count in range? → ✅ Merge Sort Tree / PBDS / ST + Binary Search
    │   └── Need multiple versions? → ✅ Persistent Segment Tree
    │
    ├── RANGE UPDATES + RANGE QUERIES?
    │   ├── Add on range + Sum query? → ✅ Segment Tree with Lazy / BIT with two arrays
    │   ├── Assign on range + any query? → ✅ Segment Tree with Lazy
    │   ├── chmin/chmax on range? → ✅ Segment Tree Beats (Ji Driver)
    │   └── Need multiple operations? → ✅ Segment Tree with combined Lazy
    │
    ├── RANGE UPDATES + POINT QUERIES?
    │   └── ✅ Difference Array / BIT (range update, point query)
    │
    └── OFFLINE queries allowed?
        ├── YES → ✅ Mo's Algorithm (no updates) / Mo's with updates
        └── NO  → ✅ Segment Tree / BIT (online)

Is the query on a TREE (not array)?
├── Subtree queries → ✅ Euler Tour + Segment Tree / BIT
├── Path queries → ✅ HLD + Segment Tree
├── Both → ✅ HLD + Euler Tour + Segment Tree
└── LCA queries → ✅ Sparse Table on Euler Tour / Binary Lifting

Is the value range HUGE (up to 10^9)?
├── YES → ✅ Implicit/Dynamic Segment Tree OR Coordinate Compression + normal ST/BIT
└── NO  → ✅ Normal Segment Tree / BIT

Need CONVEX HULL TRICK on segments?
└── YES → ✅ Li Chao Tree

Need RANGE ORDER STATISTICS (kth smallest in range)?
├── Online → ✅ Persistent Segment Tree / Wavelet Tree
└── Offline → ✅ Merge Sort Tree / Offline + BIT
```

---

## 🌲 Segment Tree Internals — Visual Reference

### Array Representation (1-indexed, size 4N)

```
                        [1]                          ← root = 1
                       /    \
                   [2]        [3]                    ← left = 2i, right = 2i+1
                  /    \     /    \
               [4]    [5]  [6]    [7]                ← leaves at depth log(n)
              /  \   /  \  /  \   /  \
            [8] [9][10][11][12][13][14][15]           ← leaf nodes = actual elements

For array a[] = {1, 3, 5, 7, 9, 11}:
Node values (range sum):
           [1] = 36
          /        \
      [2] = 9     [3] = 27
      /    \       /     \
   [4]=4  [5]=5  [6]=20  [7]=7(padding)
   / \    / \    /  \
 [8]=1[9]=3[10]=5[11]=7[12]=9[13]=11

Parent of node i = i/2
Left child  of i = 2*i
Right child of i = 2*i + 1
Leaf nodes  = indices [n, 2n-1]
```

### Lazy Propagation — Push Down Visualization

```
Before push_down(node):
  node.value = 10, node.lazy = +5
  left.value = 4,  right.value = 6

After push_down(node):
  node.value = 10, node.lazy = 0     ← lazy cleared
  left.value = 4 + 5*left_size       ← lazy pushed to children
  left.lazy += 5
  right.value = 6 + 5*right_size
  right.lazy += 5
```

---

## 🔥 Core Templates Quick Reference

### Basic Segment Tree (Range Sum + Point Update)

```cpp
struct SegTree {
    int n;
    vector<long long> tree;
    
    SegTree(int n) : n(n), tree(4 * n, 0) {}
    
    void build(vector<int>& a, int node, int start, int end) {
        if (start == end) { tree[node] = a[start]; return; }
        int mid = (start + end) / 2;
        build(a, 2*node, start, mid);
        build(a, 2*node+1, mid+1, end);
        tree[node] = tree[2*node] + tree[2*node+1];
    }
    
    void update(int node, int start, int end, int idx, int val) {
        if (start == end) { tree[node] = val; return; }
        int mid = (start + end) / 2;
        if (idx <= mid) update(2*node, start, mid, idx, val);
        else update(2*node+1, mid+1, end, idx, val);
        tree[node] = tree[2*node] + tree[2*node+1];
    }
    
    long long query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        return query(2*node, start, mid, l, r) + query(2*node+1, mid+1, end, l, r);
    }
};
```

### Segment Tree with Lazy Propagation (Range Add + Range Sum)

```cpp
struct LazySegTree {
    int n;
    vector<long long> tree, lazy;
    
    LazySegTree(int n) : n(n), tree(4*n, 0), lazy(4*n, 0) {}
    
    void push_down(int node, int start, int end) {
        if (lazy[node] != 0) {
            int mid = (start + end) / 2;
            tree[2*node] += lazy[node] * (mid - start + 1);
            tree[2*node+1] += lazy[node] * (end - mid);
            lazy[2*node] += lazy[node];
            lazy[2*node+1] += lazy[node];
            lazy[node] = 0;
        }
    }
    
    void update(int node, int start, int end, int l, int r, long long val) {
        if (r < start || end < l) return;
        if (l <= start && end <= r) {
            tree[node] += val * (end - start + 1);
            lazy[node] += val;
            return;
        }
        push_down(node, start, end);
        int mid = (start + end) / 2;
        update(2*node, start, mid, l, r, val);
        update(2*node+1, mid+1, end, l, r, val);
        tree[node] = tree[2*node] + tree[2*node+1];
    }
    
    long long query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        push_down(node, start, end);
        int mid = (start + end) / 2;
        return query(2*node, start, mid, l, r) + query(2*node+1, mid+1, end, l, r);
    }
};
```

### Fenwick Tree (BIT)

```cpp
struct BIT {
    int n;
    vector<long long> tree;
    
    BIT(int n) : n(n), tree(n + 1, 0) {}
    
    void update(int i, long long delta) {
        for (; i <= n; i += i & (-i))
            tree[i] += delta;
    }
    
    long long query(int i) {
        long long sum = 0;
        for (; i > 0; i -= i & (-i))
            sum += tree[i];
        return sum;
    }
    
    long long query(int l, int r) {
        return query(r) - query(l - 1);
    }
};
```

### Sparse Table (RMQ — O(1) Query)

```cpp
struct SparseTable {
    vector<vector<int>> table;
    vector<int> log2_floor;
    
    SparseTable(vector<int>& a) {
        int n = a.size();
        int K = __lg(n) + 1;
        table.assign(K, vector<int>(n));
        log2_floor.resize(n + 1);
        for (int i = 2; i <= n; i++) log2_floor[i] = log2_floor[i/2] + 1;
        table[0] = a;
        for (int k = 1; k < K; k++)
            for (int i = 0; i + (1 << k) <= n; i++)
                table[k][i] = min(table[k-1][i], table[k-1][i + (1 << (k-1))]);
    }
    
    int query(int l, int r) {
        int k = log2_floor[r - l + 1];
        return min(table[k][l], table[k][r - (1 << k) + 1]);
    }
};
```

---

## 🏆 GM Tips — The Meta-Knowledge

### 🔥 Top 15 Range Query Rules for Competitive Programming

1. **Always use 1-indexed BIT** — Saves you from off-by-one bugs in contests
2. **Segment Tree size = 4*N** — Not 2*N! Unless you're using iterative ST with exactly 2*N
3. **Lazy = "promise to children"** — Always push down BEFORE accessing children
4. **BIT for sums, ST for everything else** — BIT has smaller constant factor and less code
5. **Sparse Table for static RMQ** — Don't build a segment tree if array never changes
6. **Mo's block size = √N** — But use `N / max(1, (int)sqrt(Q))` for better constant
7. **Hilbert curve ordering in Mo's** — Can be 2-3x faster than naive block ordering
8. **Persistent ST = O(log N) new nodes per update** — Total memory = O((N + Q) log N)
9. **HLD reduces tree paths to O(log N) array segments** — Then use any range DS on each
10. **Euler Tour is the bridge from trees to arrays** — Subtree = contiguous range!
11. **Coordinate compression before BIT/ST** — When values up to 10^9 but count ≤ 10^5
12. **Segment Tree Beats handles range chmin/chmax** — No other structure does this efficiently
13. **Li Chao Tree for dynamic convex hull trick** — When lines are added online
14. **Wavelet Tree = persistent BIT on values** — Supports kth smallest in O(log σ)
15. **Iterative ST for speed** — ~2x faster than recursive in practice, but harder for lazy

### ⚡ Common Mistakes to Avoid

```
❌ Forgetting to push_down lazy before accessing children
❌ Using tree size 2*N instead of 4*N for recursive segment tree
❌ Not handling the "empty range" base case in queries
❌ Forgetting to call build() before queries
❌ Off-by-one errors: [l, r] vs [l, r) — be consistent!
❌ Using Mo's algorithm for online queries (it's OFFLINE only!)
❌ Not sorting queries properly in Mo's algorithm
❌ Forgetting coordinate compression when value range > N
❌ Using Sparse Table when array has updates (it's STATIC only!)
❌ Not accounting for overflow in range sum (use long long!)
```

### 🎯 Contest Strategy — Which Structure to Code First?

```
Reading Time (2 min):
├── See "range query" + "point update" → BIT (fastest to code, ~15 lines)
├── See "range update" + "range query" → Lazy Segment Tree (~40 lines)
├── See "minimum/maximum" + "static"  → Sparse Table (~20 lines)
├── See "offline" + "distinct count"  → Mo's Algorithm (~30 lines)
├── See "tree" + "path query"         → HLD + Segment Tree (~80 lines)
├── See "kth smallest in range"       → Persistent ST / Merge Sort Tree
├── See "convex hull trick online"    → Li Chao Tree
└── See "range assign/chmin/chmax"    → Segment Tree Beats

Coding Time Estimates:
├── BIT:                    3-5 minutes
├── Basic Segment Tree:     5-8 minutes
├── Lazy Segment Tree:      8-12 minutes
├── Sparse Table:           5-7 minutes
├── Mo's Algorithm:         8-10 minutes
├── Persistent ST:          12-18 minutes
├── HLD + Segment Tree:     15-25 minutes
├── Merge Sort Tree:        10-15 minutes
├── Li Chao Tree:           10-15 minutes
└── Segment Tree Beats:     15-20 minutes
```

---

## 📐 Mathematical Foundations

### Why Segment Tree has O(log N) query?

```
At each level, the query visits AT MOST 2 nodes that partially overlap with [l, r].
  - Proof: If 3+ nodes overlap at one level, the middle one is FULLY covered
    → contradiction (it would have been returned without going deeper)
  
Total levels = O(log N)
Nodes visited per level ≤ 2 (partial) + all fully covered (returned immediately)
⇒ Total work = O(log N)
```

### Why BIT uses `i & (-i)` (lowbit)?

```
i & (-i) extracts the lowest set bit of i.
  Example: i = 12 = 1100₂  →  i & (-i) = 0100₂ = 4

BIT[i] stores sum of range [i - lowbit(i) + 1, i]
  - BIT[12] stores sum of a[9..12]  (lowbit = 4, range length = 4)
  - BIT[8]  stores sum of a[1..8]   (lowbit = 8, range length = 8)
  - BIT[7]  stores sum of a[7..7]   (lowbit = 1, range length = 1)

Query(i):   sum a[1..i] = BIT[i] + BIT[i - lowbit(i)] + ...  (go down)
Update(i):  BIT[i] += delta, BIT[i + lowbit(i)] += delta, ... (go up)
```

### Sparse Table — Why O(1) for Idempotent Operations?

```
Idempotent: f(x, x) = x   →  min(x, x) = x,  max(x, x) = x,  gcd(x, x) = x

For query [l, r]:
  k = floor(log2(r - l + 1))
  answer = f(table[k][l], table[k][r - 2^k + 1])
  
These two ranges OVERLAP, but since f is idempotent, double-counting is fine!
  [l ........... l+2^k-1]
            [r-2^k+1 .......... r]
  ←— range 1 —→←— overlap —→←— range 2 —→
  
  NOT valid for SUM! (would double-count the overlap)
```

---

## 🧩 Key Concepts Dependency Graph

```
                    Prefix Sum / Difference Array
                              │
                              ▼
                    ┌─── Segment Tree (Basic) ───┐
                    │         │                   │
                    ▼         ▼                   ▼
               Fenwick    Variants          Sparse Table
               Tree(BIT)  (sum/min/max)     (static RMQ)
                    │         │
                    ▼         ▼
              Advanced   Lazy Propagation
              BIT           │
                            ▼
                   Advanced ST Operations
                   (max subarray, kth, etc.)
                            │
              ┌─────────────┼─────────────┐
              ▼             ▼             ▼
         Persistent    ST + Binary    Mo's Algorithm
         Seg Tree      Search         (offline)
              │             │
              ▼             ▼
         ST on Trees    Multidimensional
         (Euler/HLD)    Segment Trees
              │             │
              ▼             ▼
         Advanced       ICPC Structures
         Techniques     (Wavelet, Li Chao,
         (Beats, PBS)    Merge Sort Tree)
```

---

## 📚 Curated Problem Sets by Rating

### 🟢 Beginner (Rating 800–1200)

| Problem | Platform | Key Concept |
|---------|:--------:|-------------|
| [Range Sum Query - Immutable](https://leetcode.com/problems/range-sum-query-immutable/) | LC 303 | Prefix Sum |
| [Range Sum Query 2D - Immutable](https://leetcode.com/problems/range-sum-query-2d-immutable/) | LC 304 | 2D Prefix Sum |
| [Static Range Sum Queries](https://cses.fi/problemset/task/1646) | CSES | Prefix Sum |
| [Static Range Minimum Queries](https://cses.fi/problemset/task/1647) | CSES | Sparse Table / ST |
| [Corporate Flight Bookings](https://leetcode.com/problems/corporate-flight-bookings/) | LC 1109 | Difference Array |

### 🟡 Intermediate (Rating 1200–1600)

| Problem | Platform | Key Concept |
|---------|:--------:|-------------|
| [Dynamic Range Sum Queries](https://cses.fi/problemset/task/1648) | CSES | BIT / Segment Tree |
| [Dynamic Range Minimum Queries](https://cses.fi/problemset/task/1649) | CSES | Segment Tree |
| [Range Update Queries](https://cses.fi/problemset/task/1651) | CSES | BIT range update |
| [Range Sum Query - Mutable](https://leetcode.com/problems/range-sum-query-mutable/) | LC 307 | BIT / Segment Tree |
| [Count of Smaller Numbers After Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/) | LC 315 | BIT + Coord Compress |

### 🔴 Advanced (Rating 1600–2100)

| Problem | Platform | Key Concept |
|---------|:--------:|-------------|
| [Salary Queries](https://cses.fi/problemset/task/1144) | CSES | BIT + Compress |
| [Hotel Queries](https://cses.fi/problemset/task/1143) | CSES | ST + Binary Search |
| [Polynomial Queries](https://cses.fi/problemset/task/1736) | CSES | Lazy Propagation |
| [Range Queries and Copies](https://cses.fi/problemset/task/1737) | CSES | Persistent ST |
| [Distinct Values Queries](https://cses.fi/problemset/task/1734) | CSES | Mo's / Offline + BIT |
| [Sereja and Brackets](https://codeforces.com/contest/380/problem/C) | CF 380C | Segment Tree (custom merge) |
| [Xenia and Bit Operations](https://codeforces.com/contest/339/problem/D) | CF 339D | Segment Tree |

### 🟣 Expert (Rating 2100–2400)

| Problem | Platform | Key Concept |
|---------|:--------:|-------------|
| [Path Queries](https://cses.fi/problemset/task/1138) | CSES | Euler Tour + BIT |
| [Path Queries II](https://cses.fi/problemset/task/2134) | CSES | HLD + Segment Tree |
| [Subtree Queries](https://cses.fi/problemset/task/1137) | CSES | Euler Tour + BIT |
| [Lucky Array](https://codeforces.com/contest/121/problem/E) | CF | Sqrt Decomp / ST |
| [Subsequences](https://codeforces.com/contest/597/problem/C) | CF 597C | BIT DP |
| [Ant Colony](https://codeforces.com/contest/474/problem/F) | CF 474F | GCD Segment Tree |

### 💎 Grandmaster / ICPC (Rating 2400+)

| Problem | Platform | Key Concept |
|---------|:--------:|-------------|
| [MKTHNUM](https://www.spoj.com/problems/MKTHNUM/) | SPOJ | Persistent ST |
| [Count on a Tree](https://www.spoj.com/problems/COT/) | SPOJ | Persistent ST + LCA |
| [HORRIBLE](https://www.spoj.com/problems/HORRIBLE/) | SPOJ | Lazy Propagation |
| [GSS1 - Max Subarray Sum](https://www.spoj.com/problems/GSS1/) | SPOJ | Segment Tree (Kadane) |
| [GSS3 - Max Subarray Sum + Update](https://www.spoj.com/problems/GSS3/) | SPOJ | Segment Tree (Kadane) |
| [New Year Tree](https://codeforces.com/contest/620/problem/E) | CF 620E | Euler Tour + Bitmask ST |
| [Ynoi2016](https://www.luogu.com.cn/problem/P4117) | Luogu | Segment Tree Beats |

---

## 🎓 How to Study This Module

### 📅 Recommended Study Schedule

```
Week 1: Level 0-1 (Foundations + ST Basics)
  ├── Day 1-2: Ch 01 — Prefix Sum, Difference Array, Offline/Online concepts
  ├── Day 3-5: Ch 02 — Build, Query, Update segment tree from scratch
  └── Day 6-7: Practice 10 easy problems (CSES + LeetCode)

Week 2: Level 2-3 (Variants + Lazy Propagation)
  ├── Day 1-2: Ch 03 — Implement Sum, Min, Max, GCD, XOR segment trees
  ├── Day 3-5: Ch 04 — Lazy propagation (THE most important concept!)
  └── Day 6-7: Practice 10 medium problems (CSES + Codeforces)

Week 3: Level 4-5 (Advanced ST + Persistent ST)
  ├── Day 1-2: Ch 05 — Max subarray sum ST, custom nodes
  ├── Day 3-5: Ch 06 — Persistent segment tree
  └── Day 6-7: Practice 8 problems (SPOJ + Codeforces)

Week 4: Level 6-7 (BIT + Advanced BIT)
  ├── Day 1-3: Ch 07 — Fenwick tree from scratch, all operations
  ├── Day 4-5: Ch 08 — Range update BIT, 2D BIT, coordinate compression
  └── Day 6-7: Practice 8 problems (CSES + Codeforces)

Week 5: Level 8-9 (Sparse Table + Offline Techniques)
  ├── Day 1-2: Ch 09 — Sparse table build & query
  ├── Day 3-5: Ch 10 — Mo's algorithm (basic, with updates, on trees)
  └── Day 6-7: Practice 8 problems (CSES + SPOJ)

Week 6: Level 10-11 (ST Binary Search + ST on Trees)
  ├── Day 1-2: Ch 11 — Walking on segment tree, kth order statistics
  ├── Day 3-5: Ch 12 — Euler tour, HLD, path/subtree queries
  └── Day 6-7: Practice 8 problems (CSES + Codeforces)

Week 7: Level 12-14 (Multidimensional + Advanced + ICPC)
  ├── Day 1-2: Ch 13 — 2D segment tree, 2D range queries
  ├── Day 3-4: Ch 14 — ST Beats, Parallel Binary Search
  ├── Day 5-6: Ch 15 — Wavelet Tree, Li Chao Tree, Merge Sort Tree
  └── Day 7: Full revision + solve 5 ICPC-level problems
```

### 📖 For Each Chapter:
1. 📖 **Read the README** first for overview & intuition
2. 💻 **Study each .cpp file** — read theory comments, then code
3. 🧪 **Run the code** — modify inputs, break things, understand edge cases
4. 🏆 **Solve practice problems** from the Problem Cheat Sheet
5. 📝 **Build your own template** — distill each structure to contest-ready code
6. 🔄 **Re-implement from memory** — if you can't, go back to step 2

### 🎯 Mastery Checklist

```
□ Can implement Prefix Sum 1D/2D in under 2 minutes
□ Can implement Basic Segment Tree from scratch in under 5 minutes
□ Can implement Lazy Propagation from scratch in under 10 minutes
□ Can implement BIT from scratch in under 3 minutes
□ Can implement Sparse Table from scratch in under 5 minutes
□ Can recognize which structure to use within 30 seconds of reading a problem
□ Can implement Mo's Algorithm in under 8 minutes
□ Can implement HLD + Segment Tree in under 20 minutes
□ Can implement Persistent Segment Tree in under 15 minutes
□ Can implement Merge Sort Tree in under 12 minutes
□ Can implement Li Chao Tree in under 12 minutes
□ Can implement Wavelet Tree in under 20 minutes
□ Can implement Segment Tree Beats in under 15 minutes
□ Solved 100+ range query problems across all platforms
```

---

## 📂 File Structure

```
15_Segment_Tree_And_Range_Query_Data_Structures/
├── README.md                          ← You are here
├── Problem_Cheat_Sheet.md             ← 150+ curated problems by topic & platform
│
├── 01_Range_Query_Foundations/        ← Prefix Sum, Difference Array, Offline/Online
├── 02_Segment_Tree_Basics/            ← Build, Query, Update, Complexity
├── 03_Segment_Tree_Variants/          ← Sum, Min, Max, GCD, LCM, XOR ST
├── 04_Lazy_Propagation/               ← Range Add/Assign/Max/Sum with Lazy
├── 05_Advanced_Segment_Tree_Operations/ ← Custom nodes, Max Subarray, Kth Element
├── 06_Persistent_Segment_Tree/        ← Versioned ST, Kth Smallest in Range
├── 07_Fenwick_Tree_BIT/               ← BIT basics, Prefix Sum, Point Update
├── 08_Advanced_Fenwick_Tree/          ← Range Update BIT, 2D BIT, Compression
├── 09_Sparse_Table/                   ← Static RMQ, GCD, Idempotent ops
├── 10_Offline_Range_Query_Techniques/ ← Mo's Algorithm, Hilbert ordering
├── 11_Segment_Tree_Binary_Search/     ← Walking on ST, Kth Order Statistics
├── 12_Segment_Tree_On_Trees/          ← Euler Tour, HLD, Path Queries
├── 13_Multidimensional_Segment_Trees/ ← 2D ST, 2D Range Queries
├── 14_Advanced_Range_Query_Techniques/← ST Beats, Parallel Binary Search
└── 15_ICPC_Level_Range_Structures/    ← Wavelet Tree, Li Chao, Merge Sort Tree
```

---

<div align="center">

### Made with ❤️ for the Competitive Programming Community

*"Every range query problem is a segment tree problem in disguise. Learn to see the tree, and you'll see the solution."*  
— **Sarvan Yaduvanshi**

**⭐ Star this repo if it helped you! ⭐**

</div>

