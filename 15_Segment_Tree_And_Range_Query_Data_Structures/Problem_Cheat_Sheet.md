<div align="center">

# 🏆 Segment Tree & Range Query — Problem Cheat Sheet

### 150+ Curated Problems from LeetCode, CSES, Codeforces, CodeChef, SPOJ, AtCoder, GFG

[![Problems](https://img.shields.io/badge/Problems-150%2B-blueviolet?style=for-the-badge)](.)
[![Platforms](https://img.shields.io/badge/Platforms-8-orange?style=for-the-badge)](.)
[![Difficulty](https://img.shields.io/badge/Level-Easy%20→%20ICPC-red?style=for-the-badge)](.)
[![Author](https://img.shields.io/badge/Author-Sarvan%20Yaduvanshi-green?style=for-the-badge)](https://github.com/Sarvan-Yaduvanshi)

> *"You don't master segment trees by reading — you master them by solving 100+ problems. This sheet is your roadmap."*

</div>

---

## 📋 Platform Legend

| Abbreviation | Platform | URL |
|:---:|----------|-----|
| **LC** | LeetCode | https://leetcode.com |
| **CSES** | CSES Problem Set | https://cses.fi/problemset |
| **CF** | Codeforces | https://codeforces.com |
| **CC** | CodeChef | https://www.codechef.com |
| **SPOJ** | Sphere Online Judge | https://www.spoj.com |
| **GFG** | GeeksForGeeks | https://practice.geeksforgeeks.org |
| **AC** | AtCoder | https://atcoder.jp |
| **LG** | Luogu | https://www.luogu.com.cn |

## 🏷️ Difficulty Legend

| Symbol | Meaning | Approx CF Rating |
|:------:|---------|:-----------------:|
| ⭐ | Easy | 800–1200 |
| ⭐⭐ | Medium | 1200–1600 |
| ⭐⭐⭐ | Hard | 1600–2100 |
| ⭐⭐⭐⭐ | Very Hard | 2100–2400 |
| ⭐⭐⭐⭐⭐ | ICPC/GM | 2400+ |

---

## 📑 Table of Contents

1. [Prefix Sum & Difference Array](#1--prefix-sum--difference-array)
2. [Basic Segment Tree (Point Update + Range Query)](#2--basic-segment-tree-point-update--range-query)
3. [Segment Tree Variants (Min/Max/GCD/XOR)](#3--segment-tree-variants-minmaxgcdxor)
4. [Lazy Propagation (Range Update + Range Query)](#4--lazy-propagation-range-update--range-query)
5. [Advanced Segment Tree Operations](#5--advanced-segment-tree-operations)
6. [Persistent Segment Tree](#6--persistent-segment-tree)
7. [Fenwick Tree / BIT](#7--fenwick-tree--bit)
8. [Advanced Fenwick Tree](#8--advanced-fenwick-tree)
9. [Sparse Table](#9--sparse-table)
10. [Mo's Algorithm & Offline Techniques](#10--mos-algorithm--offline-techniques)
11. [Segment Tree + Binary Search](#11--segment-tree--binary-search)
12. [Segment Tree on Trees (Euler Tour / HLD)](#12--segment-tree-on-trees-euler-tour--hld)
13. [2D / Multidimensional Range Queries](#13--2d--multidimensional-range-queries)
14. [Segment Tree Beats & Advanced Techniques](#14--segment-tree-beats--advanced-techniques)
15. [Wavelet Tree / Li Chao Tree / Merge Sort Tree / ICPC Structures](#15--wavelet-tree--li-chao-tree--merge-sort-tree--icpc-structures)

---

## 1. 📊 Prefix Sum & Difference Array

| # | Problem | Platform | Difficulty | Technique | Hint |
|:-:|---------|:--------:|:----------:|-----------|------|
| 1 | [Range Sum Query - Immutable](https://leetcode.com/problems/range-sum-query-immutable/) | LC 303 | ⭐ | Prefix Sum | `prefix[r+1] - prefix[l]` |
| 2 | [Range Sum Query 2D - Immutable](https://leetcode.com/problems/range-sum-query-2d-immutable/) | LC 304 | ⭐⭐ | 2D Prefix Sum | Inclusion-exclusion on 4 corners |
| 3 | [Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/) | LC 560 | ⭐⭐ | Prefix Sum + HashMap | Count `prefix[i] - k` in map |
| 4 | [Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/) | LC 238 | ⭐⭐ | Prefix/Suffix Product | Left prefix × right suffix |
| 5 | [Corporate Flight Bookings](https://leetcode.com/problems/corporate-flight-bookings/) | LC 1109 | ⭐⭐ | Difference Array | `diff[l] += val, diff[r+1] -= val` |
| 6 | [Car Pooling](https://leetcode.com/problems/car-pooling/) | LC 1094 | ⭐⭐ | Difference Array | Same as flight bookings |
| 7 | [Static Range Sum Queries](https://cses.fi/problemset/task/1646) | CSES | ⭐ | Prefix Sum | Classic prefix sum |
| 8 | [Subarray Sums I](https://cses.fi/problemset/task/1660) | CSES | ⭐⭐ | Prefix Sum + Two Pointer | Sliding window / prefix map |
| 9 | [Subarray Sums II](https://cses.fi/problemset/task/1661) | CSES | ⭐⭐ | Prefix Sum + HashMap | Handle negative numbers |
| 10 | [Subarray Divisibility](https://cses.fi/problemset/task/1662) | CSES | ⭐⭐ | Prefix Sum + Modulo | Count prefix[i] % n |
| 11 | [Forest Queries](https://cses.fi/problemset/task/1652) | CSES | ⭐⭐ | 2D Prefix Sum | Grid prefix sums |
| 12 | [Range XOR Queries](https://cses.fi/problemset/task/1650) | CSES | ⭐ | Prefix XOR | `prefix[r] ^ prefix[l-1]` |
| 13 | [Running Sum of 1d Array](https://leetcode.com/problems/running-sum-of-1d-array/) | LC 1480 | ⭐ | Prefix Sum | Simplest prefix sum |
| 14 | [Prefix Sum](https://practice.geeksforgeeks.org/problems/prefix-sum-of-matrix-sub-matrix/1) | GFG | ⭐ | 2D Prefix Sum | Matrix sub-sum |
| 15 | [Number of Ways to Split Array](https://leetcode.com/problems/number-of-ways-to-split-array-into-two-parts/) | LC 2270 | ⭐⭐ | Prefix Sum | Compare left sum vs right sum |

---

## 2. 🌲 Basic Segment Tree (Point Update + Range Query)

| # | Problem | Platform | Difficulty | Technique | Hint |
|:-:|---------|:--------:|:----------:|-----------|------|
| 1 | [Range Sum Query - Mutable](https://leetcode.com/problems/range-sum-query-mutable/) | LC 307 | ⭐⭐ | Segment Tree / BIT | Classic point update + range sum |
| 2 | [Dynamic Range Sum Queries](https://cses.fi/problemset/task/1648) | CSES | ⭐⭐ | Segment Tree / BIT | Point update, range sum |
| 3 | [Dynamic Range Minimum Queries](https://cses.fi/problemset/task/1649) | CSES | ⭐⭐ | Segment Tree | Point update, range min |
| 4 | [Xenia and Bit Operations](https://codeforces.com/contest/339/problem/D) | CF 339D | ⭐⭐ | Segment Tree | Alternating OR/XOR per level |
| 5 | [Curious Robin Hood](https://lightoj.com/problem/curious-robin-hood) | LightOJ | ⭐⭐ | Segment Tree / BIT | Point update, range sum, point query |
| 6 | [Range Minimum Query](https://practice.geeksforgeeks.org/problems/range-minimum-query/1) | GFG | ⭐⭐ | Segment Tree | Classic RMQ |
| 7 | [KQUERY](https://www.spoj.com/problems/KQUERY/) | SPOJ | ⭐⭐⭐ | Offline + BIT / Merge Sort Tree | Count elements > K in range |
| 8 | [Distinct Characters Queries](https://codeforces.com/contest/1234/problem/D) | CF 1234D | ⭐⭐ | Segment Tree (bitmask) | Store character bitmask per node |
| 9 | [A Simple Task](https://codeforces.com/contest/558/problem/E) | CF 558E | ⭐⭐⭐ | 26 Segment Trees | One ST per character, sort substring |
| 10 | [Inversions](https://cses.fi/problemset/task/1751) | CSES | ⭐⭐⭐ | BIT / Segment Tree | Process right-to-left, count |

---

## 3. 🔀 Segment Tree Variants (Min/Max/GCD/XOR)

| # | Problem | Platform | Difficulty | Technique | Hint |
|:-:|---------|:--------:|:----------:|-----------|------|
| 1 | [Static Range Minimum Queries](https://cses.fi/problemset/task/1647) | CSES | ⭐⭐ | Sparse Table / Min ST | Static = Sparse Table preferred |
| 2 | [Ant Colony](https://codeforces.com/contest/474/problem/F) | CF 474F | ⭐⭐⭐ | GCD Segment Tree | GCD of range, count elements equal to GCD |
| 3 | [Segtree (GCD)](https://atcoder.jp/contests/abc125/tasks/abc125_c) | AC | ⭐⭐ | GCD Segment Tree / Prefix | Remove one element, compute GCD |
| 4 | [Hard problem about GCD](https://codeforces.com/contest/475/problem/D) | CF 475D | ⭐⭐⭐ | GCD properties + ST | Count pairs with GCD = g |
| 5 | [XOR on Segment](https://codeforces.com/contest/242/problem/E) | CF 242E | ⭐⭐⭐ | 20 Segment Trees (bit-wise) | One ST per bit position + lazy XOR |
| 6 | [Salary Queries](https://cses.fi/problemset/task/1144) | CSES | ⭐⭐⭐ | BIT + Coord Compress | Count employees with salary in [a,b] |
| 7 | [Range AND / OR / XOR Queries](https://practice.geeksforgeeks.org/problems/range-and-query/1) | GFG | ⭐⭐ | Segment Tree Variant | Different merge operations |
| 8 | [Frequent values](https://www.spoj.com/problems/FREQUENT/) | SPOJ | ⭐⭐⭐ | Segment Tree (custom merge) | Store (prefix, suffix, max_freq) |
| 9 | [Nikita and String](https://codeforces.com/contest/877/problem/E) | CF 877E | ⭐⭐⭐ | Segment Tree (custom) | Maximum "good" subsequence |
| 10 | [Lucky Queries](https://codeforces.com/contest/145/problem/E) | CF 145E | ⭐⭐⭐ | Segment Tree (LIS merge) | Merge LIS info in segment tree |

---

## 4. 😴 Lazy Propagation (Range Update + Range Query)

| # | Problem | Platform | Difficulty | Technique | Hint |
|:-:|---------|:--------:|:----------:|-----------|------|
| 1 | [Range Update Queries](https://cses.fi/problemset/task/1651) | CSES | ⭐⭐ | Lazy ST / BIT range update | Range add, point query |
| 2 | [HORRIBLE - Horrible Queries](https://www.spoj.com/problems/HORRIBLE/) | SPOJ | ⭐⭐⭐ | Lazy Propagation | Range add + range sum (classic!) |
| 3 | [Polynomial Queries](https://cses.fi/problemset/task/1736) | CSES | ⭐⭐⭐ | Lazy Propagation | Add 1,2,3,...,k to range. Use two lazy values |
| 4 | [A Simple Task](https://codeforces.com/contest/558/problem/E) | CF 558E | ⭐⭐⭐⭐ | 26 Lazy Segment Trees | Sort substring = set range |
| 5 | [Circular RMQ](https://codeforces.com/contest/52/problem/C) | CF 52C | ⭐⭐⭐ | Lazy Propagation | Handle circular range = split into 2 |
| 6 | [Greg and Array](https://codeforces.com/contest/295/problem/A) | CF 295A | ⭐⭐⭐ | Two-level Lazy | Apply operation ranges, then value ranges |
| 7 | [Aggressive cows](https://www.codechef.com/problems/AGGRCOW) | CC | ⭐⭐ | Binary Search (not lazy, but range) | Binary search on answer |
| 8 | [Copying Data](https://codeforces.com/contest/292/problem/E) | CF 292E | ⭐⭐⭐ | Lazy (Range Assignment) | Assign value of one range to another |
| 9 | [DZY Loves Fibonacci](https://codeforces.com/contest/446/problem/C) | CF 446C | ⭐⭐⭐⭐ | Lazy with Fibonacci | Lazy stores two Fibonacci seeds |
| 10 | [Tufurama](https://codeforces.com/contest/961/problem/E) | CF 961E | ⭐⭐⭐ | BIT / Merge Sort Tree | Count pairs `a[i] >= j` and `a[j] >= i` |
| 11 | [LZRANGEQ - Lazy Range Queries](https://www.spoj.com/problems/LZRANGEQ/) | SPOJ | ⭐⭐⭐ | Lazy Propagation | Range add + range sum |
| 12 | [Range Sum and Update](https://practice.geeksforgeeks.org/problems/range-sum-and-update/1) | GFG | ⭐⭐ | Lazy Propagation | Basic lazy practice |
| 13 | [Flip Coins](https://cses.fi/problemset/task/2210) | CSES | ⭐⭐⭐ | Lazy (Range XOR) | Flip = XOR 1 on range |
| 14 | [Addition to Segment](https://codeforces.com/edu/course/2/lesson/5/1/practice/contest/279634/problem/A) | CF EDU | ⭐⭐ | Lazy Segment Tree | Educational: range add + point query |
| 15 | [Assign to Segment](https://codeforces.com/edu/course/2/lesson/5/2/practice/contest/279653/problem/A) | CF EDU | ⭐⭐⭐ | Lazy (Range Assign) | Educational: range assign + range sum |

---

## 5. 🔧 Advanced Segment Tree Operations

| # | Problem | Platform | Difficulty | Technique | Hint |
|:-:|---------|:--------:|:----------:|-----------|------|
| 1 | [GSS1 - Max Sum](https://www.spoj.com/problems/GSS1/) | SPOJ | ⭐⭐⭐ | Max Subarray Sum on ST | Node stores: (prefix, suffix, total, answer) |
| 2 | [GSS3 - Max Sum with Update](https://www.spoj.com/problems/GSS3/) | SPOJ | ⭐⭐⭐ | Max Subarray Sum + Point Update | Same as GSS1 + point update |
| 3 | [GSS4 - Sqrt on Range](https://www.spoj.com/problems/GSS4/) | SPOJ | ⭐⭐⭐ | Segment Tree + Brute Force | After ~6 sqrt operations, element becomes 0/1 |
| 4 | [GSS5 - More Complex Max Sum](https://www.spoj.com/problems/GSS5/) | SPOJ | ⭐⭐⭐⭐ | Max Subarray with constraints | Constrained left/right endpoints |
| 5 | [Sereja and Brackets](https://codeforces.com/contest/380/problem/C) | CF 380C | ⭐⭐⭐ | Segment Tree (bracket merge) | Node: (matched, unmatched_open, unmatched_close) |
| 6 | [Kth Number](https://www.spoj.com/problems/MKTHNUM/) | SPOJ | ⭐⭐⭐⭐ | Persistent ST / Merge Sort Tree | Kth smallest in range [l,r] |
| 7 | [Number of Minimums on a Segment](https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/C) | CF EDU | ⭐⭐ | Segment Tree | Store (min_value, min_count) |
| 8 | [First element ≥ X](https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/B) | CF EDU | ⭐⭐⭐ | ST + Walking/Binary Search | Walk on segment tree |
| 9 | [Inversions 2](https://codeforces.com/edu/course/2/lesson/4/3/practice/contest/274545/problem/A) | CF EDU | ⭐⭐⭐ | Segment Tree | Build permutation from inversion counts |
| 10 | [Maximum Sum](https://codeforces.com/contest/1746/problem/F) | CF 1746F | ⭐⭐⭐⭐ | Segment Tree (complex merge) | DP-like merge in segment tree nodes |

---

## 6. 🕰️ Persistent Segment Tree

| # | Problem | Platform | Difficulty | Technique | Hint |
|:-:|---------|:--------:|:----------:|-----------|------|
| 1 | [Range Queries and Copies](https://cses.fi/problemset/task/1737) | CSES | ⭐⭐⭐ | Persistent ST | Copy array = new root, query old versions |
| 2 | [MKTHNUM - K-th Number](https://www.spoj.com/problems/MKTHNUM/) | SPOJ | ⭐⭐⭐⭐ | Persistent ST | Build PST on sorted values, query version r - version l |
| 3 | [Count on a Tree](https://www.spoj.com/problems/COT/) | SPOJ | ⭐⭐⭐⭐ | Persistent ST + LCA | PST on tree paths via LCA |
| 4 | [DQUERY - D-query](https://www.spoj.com/problems/DQUERY/) | SPOJ | ⭐⭐⭐ | Persistent ST / Offline BIT | Count distinct in range |
| 5 | [Array Restoration](https://codeforces.com/contest/1023/problem/D) | CF 1023D | ⭐⭐⭐ | Persistent-like thinking | Reconstruct from segment operations |
| 6 | [Persistent Array](https://judge.yosupo.jp/problem/persistent_unionfind) | YosupoOJ | ⭐⭐⭐⭐ | Persistent ST (as array) | Array with versioning |
| 7 | [Kth Smallest - Range](https://practice.geeksforgeeks.org/problems/kth-smallest-in-a-subarray/1) | GFG | ⭐⭐⭐ | Persistent ST / Merge Sort Tree | Kth smallest in subarray |
| 8 | [Super Nim](https://codeforces.com/contest/906/problem/D) | CF 906D | ⭐⭐⭐⭐⭐ | Persistent ST + Game Theory | Versioned updates |
| 9 | [Gotta Catch Em All](https://www.codechef.com/problems/POKEMON) | CC | ⭐⭐⭐⭐ | Persistent Trie / PST | Range distinct with persistence |
| 10 | [Functional Graph](https://cses.fi/problemset/task/1751) | CSES | ⭐⭐⭐ | Binary Lifting (related concept) | Versioned jumping |

---

## 7. 🔢 Fenwick Tree / BIT

| # | Problem | Platform | Difficulty | Technique | Hint |
|:-:|---------|:--------:|:----------:|-----------|------|
| 1 | [Range Sum Query - Mutable](https://leetcode.com/problems/range-sum-query-mutable/) | LC 307 | ⭐⭐ | BIT | Point update + prefix sum |
| 2 | [Dynamic Range Sum Queries](https://cses.fi/problemset/task/1648) | CSES | ⭐⭐ | BIT | Simplest BIT application |
| 3 | [Count of Smaller Numbers After Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/) | LC 315 | ⭐⭐⭐ | BIT + Coord Compress | Process right to left, BIT count |
| 4 | [Reverse Pairs](https://leetcode.com/problems/reverse-pairs/) | LC 493 | ⭐⭐⭐ | BIT / Merge Sort | Count pairs `a[i] > 2*a[j]` |
| 5 | [Create Sorted Array through Instructions](https://leetcode.com/problems/create-sorted-array-through-instructions/) | LC 1649 | ⭐⭐⭐ | BIT | Cost = min(count_less, count_greater) |
| 6 | [Inversion Count](https://practice.geeksforgeeks.org/problems/inversion-of-array-1587115620/1) | GFG | ⭐⭐ | BIT / Merge Sort | Classic inversion counting |
| 7 | [Inversions](https://cses.fi/problemset/task/1751) | CSES | ⭐⭐⭐ | BIT | Process and count |
| 8 | [List Removals](https://cses.fi/problemset/task/1749) | CSES | ⭐⭐⭐ | BIT + Binary Search | Find kth active element using BIT |
| 9 | [Nested Ranges Check](https://cses.fi/problemset/task/2168) | CSES | ⭐⭐⭐ | BIT + Sorting | Sort by left, BIT on right endpoints |
| 10 | [Nested Ranges Count](https://cses.fi/problemset/task/2169) | CSES | ⭐⭐⭐ | BIT + Sorting | Count containing/contained ranges |
| 11 | [Josephus Problem II](https://cses.fi/problemset/task/2163) | CSES | ⭐⭐⭐ | BIT + Binary Search | Find kth remaining person |
| 12 | [UPDATEIT](https://www.spoj.com/problems/UPDATEIT/) | SPOJ | ⭐⭐ | BIT (Range Update) | Range add, point query |

---

## 8. 🔥 Advanced Fenwick Tree

| # | Problem | Platform | Difficulty | Technique | Hint |
|:-:|---------|:--------:|:----------:|-----------|------|
| 1 | [Range Update Queries](https://cses.fi/problemset/task/1651) | CSES | ⭐⭐ | BIT (Range Add + Point Query) | Difference BIT |
| 2 | [Forest Queries II](https://cses.fi/problemset/task/1739) (if exists) | CSES | ⭐⭐⭐ | 2D BIT | 2D point update + rectangle sum |
| 3 | [MATSUM - Matrix Summation](https://www.spoj.com/problems/MATSUM/) | SPOJ | ⭐⭐⭐ | 2D BIT | 2D Fenwick tree |
| 4 | [Stars](https://codeforces.com/contest/1662/problem/F) | CF | ⭐⭐⭐ | 2D BIT / Sweep | Count points in rectangle |
| 5 | [Increasing Subsequence II](https://cses.fi/problemset/task/1748) | CSES | ⭐⭐⭐ | BIT + DP | Count increasing subsequences of length k |
| 6 | [RACETIME](https://www.spoj.com/problems/RACETIME/) | SPOJ | ⭐⭐⭐ | BIT range update range query | Two BIT trick |
| 7 | [Salary Queries](https://cses.fi/problemset/task/1144) | CSES | ⭐⭐⭐ | BIT + Coordinate Compression | Compress salary values, BIT count |
| 8 | [Distinct Values Queries](https://cses.fi/problemset/task/1734) | CSES | ⭐⭐⭐ | Offline + BIT | Sort by right endpoint, maintain last occurrence |
| 9 | [Count Good Triplets in Array](https://leetcode.com/problems/count-good-triplets-in-an-array/) | LC 2179 | ⭐⭐⭐ | BIT | Count elements less/greater using BIT |
| 10 | [Number of Pairs Satisfying Inequality](https://leetcode.com/problems/number-of-pairs-satisfying-inequality/) | LC 2426 | ⭐⭐⭐ | BIT + Coord Compress | Transform condition, BIT count |

---

## 9. 📐 Sparse Table

| # | Problem | Platform | Difficulty | Technique | Hint |
|:-:|---------|:--------:|:----------:|-----------|------|
| 1 | [Static Range Minimum Queries](https://cses.fi/problemset/task/1647) | CSES | ⭐⭐ | Sparse Table | O(1) RMQ after O(n log n) build |
| 2 | [Range Minimum Query](https://practice.geeksforgeeks.org/problems/range-minimum-query/1) | GFG | ⭐⭐ | Sparse Table | Classic RMQ |
| 3 | [RMQSQ - Range Minimum Query](https://www.spoj.com/problems/RMQSQ/) | SPOJ | ⭐⭐ | Sparse Table | Static RMQ |
| 4 | [THRBL](https://www.spoj.com/problems/THRBL/) | SPOJ | ⭐⭐ | Sparse Table (max) | Range max query |
| 5 | [GCD Table](https://codeforces.com/contest/475/problem/D) | CF 475D | ⭐⭐⭐ | Sparse Table GCD | Use ST for range GCD queries |
| 6 | [Strip](https://codeforces.com/contest/487/problem/B) | CF 487B | ⭐⭐⭐ | Sparse Table + DP + Deque | RMQ in DP transitions |
| 7 | [TNVFC1M - Movie Collection](https://www.spoj.com/problems/TNVFC1M/) | SPOJ | ⭐⭐ | BIT (related) | Simulation with BIT |
| 8 | [Maximum of Minimums on Segments](https://codeforces.com/contest/1197/problem/E) | CF 1197E | ⭐⭐⭐ | Sparse Table + Binary Search | Max of min on all segments of length k |
| 9 | [LCA](https://practice.geeksforgeeks.org/problems/lca-in-a-bst/1) | GFG | ⭐⭐ | Sparse Table on Euler Tour | LCA via RMQ |
| 10 | [Static Range GCD](https://judge.yosupo.jp/problem/staticrmq) | YosupoOJ | ⭐⭐ | Sparse Table | Static range GCD |

---

## 10. 🔄 Mo's Algorithm & Offline Techniques

| # | Problem | Platform | Difficulty | Technique | Hint |
|:-:|---------|:--------:|:----------:|-----------|------|
| 1 | [Distinct Values Queries](https://cses.fi/problemset/task/1734) | CSES | ⭐⭐⭐ | Mo's Algorithm / Offline BIT | Count distinct in [l, r] |
| 2 | [DQUERY - D-query](https://www.spoj.com/problems/DQUERY/) | SPOJ | ⭐⭐⭐ | Mo's Algorithm | Count distinct elements |
| 3 | [Powerful array](https://codeforces.com/contest/86/problem/D) | CF 86D | ⭐⭐⭐ | Mo's Algorithm | Sum of cnt[x]² × x |
| 4 | [Sherlock and Inversions](https://www.codechef.com/problems/IITI15) | CC | ⭐⭐⭐ | Mo's + BIT | Count inversions in [l,r] |
| 5 | [XOR and Favorite Number](https://codeforces.com/contest/617/problem/E) | CF 617E | ⭐⭐⭐ | Mo's Algorithm | Count pairs with XOR = k (prefix XOR) |
| 6 | [Tree and Queries](https://codeforces.com/contest/375/problem/D) | CF 375D | ⭐⭐⭐⭐ | Mo's on Trees | Flatten with Euler tour, then Mo's |
| 7 | [Candy Distribution](https://codeforces.com/contest/1514/problem/D) | CF | ⭐⭐⭐ | Mo's / Offline | Distribute candies queries |
| 8 | [Ann and Books](https://codeforces.com/contest/840/problem/D) | CF 840D | ⭐⭐⭐⭐ | Mo's Algorithm | Complex counting with Mo's |
| 9 | [GERALD07](https://www.codechef.com/problems/GERALD07) | CC | ⭐⭐⭐⭐⭐ | Mo's on Trees + DSU | Offline queries on spanning forest |
| 10 | [Arpa and a list of numbers](https://codeforces.com/contest/850/problem/C) | CF 850C | ⭐⭐⭐⭐ | Offline + Sieve | Make GCD of array > 1 |
| 11 | [Jeff and Removing Periods](https://codeforces.com/contest/352/problem/D) | CF 352D | ⭐⭐⭐ | Offline techniques | Process queries offline |
| 12 | [Array Queries](https://codeforces.com/contest/797/problem/E) | CF 797E | ⭐⭐⭐ | Sqrt Decomposition / Offline | Small k: brute force, large k: DP |

---

## 11. 🔍 Segment Tree + Binary Search

| # | Problem | Platform | Difficulty | Technique | Hint |
|:-:|---------|:--------:|:----------:|-----------|------|
| 1 | [Hotel Queries](https://cses.fi/problemset/task/1143) | CSES | ⭐⭐⭐ | ST + Walking | Find first segment with max ≥ x |
| 2 | [List Removals](https://cses.fi/problemset/task/1749) | CSES | ⭐⭐⭐ | BIT/ST + Binary Search | Find kth active position |
| 3 | [Josephus Problem II](https://cses.fi/problemset/task/2163) | CSES | ⭐⭐⭐ | ST + Walking / BIT + BS | Find kth remaining in circle |
| 4 | [First element ≥ X (Right)](https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/B) | CF EDU | ⭐⭐⭐ | Walking on ST | Descend ST to find first ≥ X |
| 5 | [First element ≥ X (Left)](https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/C) | CF EDU | ⭐⭐⭐ | Walking on ST | Same but from left side |
| 6 | [Kth One](https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/A) | CF EDU | ⭐⭐⭐ | Walking on ST | Find position of kth 1 |
| 7 | [Salary Queries](https://cses.fi/problemset/task/1144) | CSES | ⭐⭐⭐ | BIT + Coord Compress + BS | Count in range |
| 8 | [Inversions 2](https://codeforces.com/edu/course/2/lesson/4/3/practice/contest/274545/problem/A) | CF EDU | ⭐⭐⭐ | ST + Walking | Reconstruct permutation |
| 9 | [Number of Minimums](https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/C) | CF EDU | ⭐⭐ | ST (min, count) | Count minimums in range |
| 10 | [Order Statistics](https://www.codechef.com/problems/ORDERSET) | CC | ⭐⭐⭐ | BIT/ST + BS / PBDS | Kth smallest, count < x |

---

## 12. 🌳 Segment Tree on Trees (Euler Tour / HLD)

| # | Problem | Platform | Difficulty | Technique | Hint |
|:-:|---------|:--------:|:----------:|-----------|------|
| 1 | [Subtree Queries](https://cses.fi/problemset/task/1137) | CSES | ⭐⭐⭐ | Euler Tour + BIT/ST | Subtree = contiguous range in Euler tour |
| 2 | [Path Queries](https://cses.fi/problemset/task/1138) | CSES | ⭐⭐⭐ | Euler Tour + BIT | Path sum = root-to-u + root-to-v - 2×root-to-lca |
| 3 | [Path Queries II](https://cses.fi/problemset/task/2134) | CSES | ⭐⭐⭐⭐ | HLD + Segment Tree | Path max query with updates |
| 4 | [Distance Queries](https://cses.fi/problemset/task/1135) | CSES | ⭐⭐⭐ | LCA + Euler Tour | dist(u,v) = depth[u]+depth[v]-2×depth[lca] |
| 5 | [New Year Tree](https://codeforces.com/contest/620/problem/E) | CF 620E | ⭐⭐⭐⭐ | Euler Tour + Bitmask Lazy ST | Subtree color assign, count distinct (bitmask) |
| 6 | [Distinct Colors](https://cses.fi/problemset/task/1139) | CSES | ⭐⭐⭐ | Euler Tour + Small-to-Large | Count distinct in subtree |
| 7 | [QTREE - Query on a Tree](https://www.spoj.com/problems/QTREE/) | SPOJ | ⭐⭐⭐⭐ | HLD + Segment Tree | Path max with edge updates |
| 8 | [QTREE3 - Query on a Tree III](https://www.spoj.com/problems/QTREE3/) | SPOJ | ⭐⭐⭐⭐ | HLD + ST Binary Search | First black node on path to root |
| 9 | [Tree Painting](https://codeforces.com/contest/1187/problem/E) | CF 1187E | ⭐⭐⭐ | Rerooting / Euler Tour | Max sum of subtree sizes |
| 10 | [Vertex Set Path Composite](https://judge.yosupo.jp/problem/vertex_set_path_composite) | YosupoOJ | ⭐⭐⭐⭐ | HLD + Segment Tree | Compose linear functions on path |
| 11 | [GRASSPLA](https://www.spoj.com/problems/GRASSPLA/) | SPOJ | ⭐⭐⭐⭐ | HLD + BIT | Path increment, path sum |
| 12 | [Centroid Decomposition](https://codeforces.com/blog/entry/81661) | CF Blog | ⭐⭐⭐⭐ | Centroid Decomp + ST | Learn the technique |

---

## 13. 📐 2D / Multidimensional Range Queries

| # | Problem | Platform | Difficulty | Technique | Hint |
|:-:|---------|:--------:|:----------:|-----------|------|
| 1 | [Forest Queries](https://cses.fi/problemset/task/1652) | CSES | ⭐⭐ | 2D Prefix Sum | Count trees in rectangle |
| 2 | [Forest Queries II](https://cses.fi/problemset/task/1739) | CSES | ⭐⭐⭐ | 2D BIT | Toggle + rectangle sum |
| 3 | [MATSUM - Matrix Summation](https://www.spoj.com/problems/MATSUM/) | SPOJ | ⭐⭐⭐ | 2D BIT | Point update + rectangle sum |
| 4 | [Range Sum Query 2D - Mutable](https://leetcode.com/problems/range-sum-query-2d-mutable/) | LC 308 | ⭐⭐⭐ | 2D BIT / 2D ST | (Premium) 2D point update + rect sum |
| 5 | [Count Points in Rectangle](https://codeforces.com/contest/1662/problem/F) | CF | ⭐⭐⭐ | 2D BIT / Sweep + BIT | Offline: sort by x, BIT on y |
| 6 | [2D Range Queries](https://practice.geeksforgeeks.org/problems/2d-range-query/1) | GFG | ⭐⭐⭐ | 2D BIT | Practice problem |
| 7 | [IOPC1207 - 2D RMQ](https://www.spoj.com/problems/IOPC1207/) | SPOJ | ⭐⭐⭐⭐ | 2D Sparse Table | Static 2D minimum |
| 8 | [Stars in Your Window](https://poj.org/problem?id=2482) | POJ | ⭐⭐⭐⭐ | Sweep Line + ST/BIT | Rectangle max sum |
| 9 | [Candy Box](https://codeforces.com/contest/1183/problem/H) | CF | ⭐⭐⭐ | 2D ideas | Multidimensional optimization |
| 10 | [2D Segment Tree](https://judge.yosupo.jp/problem/rectangle_sum) | YosupoOJ | ⭐⭐⭐⭐ | 2D ST / Persistent ST | Rectangle sum queries |

---

## 14. ⚡ Segment Tree Beats & Advanced Techniques

| # | Problem | Platform | Difficulty | Technique | Hint |
|:-:|---------|:--------:|:----------:|-----------|------|
| 1 | [Ynoi2016: Range chmin + Range Sum](https://www.luogu.com.cn/problem/P4117) | LG | ⭐⭐⭐⭐⭐ | Segment Tree Beats | Ji Driver: chmin on range, query sum |
| 2 | [Gorgeous Sequence](https://www.luogu.com.cn/problem/P6242) | LG | ⭐⭐⭐⭐⭐ | Segment Tree Beats | Range chmin + range sum + range max |
| 3 | [The Child and Sequence](https://codeforces.com/contest/438/problem/D) | CF 438D | ⭐⭐⭐ | ST + Brute Force | Range mod = brute force (values shrink fast) |
| 4 | [Destiny](https://codeforces.com/contest/840/problem/D) | CF 840D | ⭐⭐⭐⭐ | Persistent ST + Randomized | Find frequent element in range |
| 5 | [Alyona and a Tree](https://codeforces.com/contest/739/problem/B) | CF 739B | ⭐⭐⭐ | DFS + Binary Search + BIT | Count nodes controlled by each vertex |
| 6 | [Parallel Binary Search Template](https://codeforces.com/blog/entry/44351) | CF Blog | ⭐⭐⭐⭐ | Parallel Binary Search | Multi-query binary search |
| 7 | [Meteors](https://www.spoj.com/problems/METEORS/) | SPOJ | ⭐⭐⭐⭐⭐ | Parallel Binary Search + BIT | When does each country collect enough? |
| 8 | [Range Module](https://leetcode.com/problems/range-module/) | LC 715 | ⭐⭐⭐ | Segment Tree / Intervals | Track ranges, add/remove/query |
| 9 | [GSS7 - Max Sum on Tree Path](https://www.spoj.com/problems/GSS7/) | SPOJ | ⭐⭐⭐⭐⭐ | HLD + GSS-style ST + Lazy | Max subarray sum on tree path + assign |
| 10 | [Segment Beats Template](https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum) | YosupoOJ | ⭐⭐⭐⭐⭐ | Segment Tree Beats | chmin + chmax + add + sum |
| 11 | [Doremy's Paint 2](https://codeforces.com/contest/1764/problem/G2) | CF | ⭐⭐⭐⭐ | Segment Tree + Lazy | Complex range operations |
| 12 | [Sequence Query](https://codeforces.com/contest/1547/problem/F) | CF | ⭐⭐⭐ | ST + Divide & Conquer | Divide & conquer optimization |

---

## 15. 🏅 Wavelet Tree / Li Chao Tree / Merge Sort Tree / ICPC Structures

| # | Problem | Platform | Difficulty | Technique | Hint |
|:-:|---------|:--------:|:----------:|-----------|------|
| 1 | [MKTHNUM - K-th Number](https://www.spoj.com/problems/MKTHNUM/) | SPOJ | ⭐⭐⭐⭐ | Merge Sort Tree / Wavelet Tree | Kth smallest in [l, r] |
| 2 | [Count of Range Sum](https://leetcode.com/problems/count-of-range-sum/) | LC 327 | ⭐⭐⭐ | Merge Sort Tree / BIT | Count range sums in [lower, upper] |
| 3 | [KQUERY - K-Query](https://www.spoj.com/problems/KQUERY/) | SPOJ | ⭐⭐⭐ | Merge Sort Tree | Count > K in [l, r] |
| 4 | [KQUERYO - K-Query Online](https://www.spoj.com/problems/KQUERYO/) | SPOJ | ⭐⭐⭐⭐ | Merge Sort Tree / Persistent ST | Online version of KQUERY |
| 5 | [Li Chao Tree](https://judge.yosupo.jp/problem/line_add_get_min) | YosupoOJ | ⭐⭐⭐⭐ | Li Chao Tree | Add line, query min at x |
| 6 | [Segment Add Get Min](https://judge.yosupo.jp/problem/segment_add_get_min) | YosupoOJ | ⭐⭐⭐⭐ | Li Chao Tree (segments) | Add segment, query min at x |
| 7 | [Covered Points Count](https://codeforces.com/contest/1000/problem/C) | CF 1000C | ⭐⭐ | Sweep Line / Diff Array | Count coverage at each point |
| 8 | [ILKQUERY](https://www.spoj.com/problems/ILKQUERY/) | SPOJ | ⭐⭐⭐⭐ | Wavelet Tree / Persistent ST | Count value x in [l, r], kth occurrence |
| 9 | [Wavelet Tree - Range Freq](https://www.codechef.com/problems/QUERY) | CC | ⭐⭐⭐⭐ | Wavelet Tree | Range frequency & quantile queries |
| 10 | [Frog 3](https://atcoder.jp/contests/dp/tasks/dp_z) | AC | ⭐⭐⭐ | Li Chao Tree / CHT | DP + Convex Hull Trick |
| 11 | [NKLEAVES](https://www.spoj.com/problems/NKLEAVES/) | SPOJ | ⭐⭐⭐⭐ | Li Chao Tree / CHT | DP optimization |
| 12 | [Dynamic Connectivity Offline](https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum) | YosupoOJ | ⭐⭐⭐⭐⭐ | Link-Cut / Euler Tour Tree | Dynamic tree structure |
| 13 | [Implicit Segment Tree](https://codeforces.com/blog/entry/19080) | CF Blog | ⭐⭐⭐⭐ | Dynamic/Implicit ST | When coordinate range is huge |
| 14 | [Colorful Array](https://codeforces.com/contest/1741/problem/F) | CF | ⭐⭐⭐⭐ | Merge Sort Tree / ST | Count distinct in range queries |
| 15 | [XOR Sum](https://codeforces.com/contest/1516/problem/D) | CF 1516D | ⭐⭐⭐ | Wavelet / Greedy | Split array into two subsequences, min XOR sum |

---

## 🎯 Topic-Wise Quick Reference

### "I want to practice ___" — Problem Finder

| Topic | Must-Solve Problems (in order) |
|-------|-------------------------------|
| **Prefix Sum** | LC 303 → LC 304 → CSES 1646 → LC 560 → LC 1109 → CSES 1652 |
| **Basic Segment Tree** | CSES 1648 → CSES 1649 → CF 339D → LC 307 → CF EDU ST problems |
| **Lazy Propagation** | CSES 1651 → SPOJ HORRIBLE → CSES 1736 → CF 52C → CF 558E |
| **Max Subarray on ST** | SPOJ GSS1 → SPOJ GSS3 → SPOJ GSS4 → SPOJ GSS5 → CF 380C |
| **Fenwick Tree** | CSES 1648 → LC 307 → LC 315 → CSES 1751 → CSES 1749 |
| **Sparse Table** | CSES 1647 → SPOJ RMQSQ → GFG RMQ → CF 475D |
| **Mo's Algorithm** | SPOJ DQUERY → CF 86D → CF 617E → CF 375D → CSES 1734 |
| **Persistent ST** | CSES 1737 → SPOJ MKTHNUM → SPOJ COT → CF 840D |
| **HLD + ST** | CSES 2134 → SPOJ QTREE → CF 620E → SPOJ GSS7 |
| **ST Binary Search** | CSES 1143 → CF EDU First≥X → CSES 1749 → CSES 2163 |
| **2D Range Query** | CSES 1652 → CSES 1739 → SPOJ MATSUM → LC 308 |
| **ST Beats** | CF 438D → LG P4117 → LG P6242 → YosupoOJ chmin/chmax |
| **Li Chao Tree** | AC Frog 3 → YosupoOJ line_add → YosupoOJ segment_add → SPOJ NKLEAVES |
| **Merge Sort Tree** | SPOJ MKTHNUM → SPOJ KQUERY → SPOJ KQUERYO → LC 327 |
| **Wavelet Tree** | SPOJ MKTHNUM → SPOJ ILKQUERY → CC QUERY |

---

## 📊 Codeforces Educational Course — Segment Tree Problems

The **CF EDU Segment Tree** course is one of the best structured resources. Here's the complete problem list:

### Part 1: Segment Tree for the Minimum

| # | Problem | Link | Key Concept |
|:-:|---------|------|-------------|
| A | Segment Tree for the Minimum | [Contest 273169/A](https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/A) | Basic min ST |
| B | Segment Tree for the Minimum (with update) | [Contest 273169/B](https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/B) | Point update + min query |
| C | Number of Minimums on a Segment | [Contest 273169/C](https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/C) | (min, count) pair |

### Part 2: Walking on Segment Tree

| # | Problem | Link | Key Concept |
|:-:|---------|------|-------------|
| A | Kth One | [Contest 273278/A](https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/A) | Find kth 1 |
| B | First ≥ X | [Contest 273278/B](https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/B) | First element ≥ x |
| C | First ≥ X (from position) | [Contest 273278/C](https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/C) | First ≥ x after pos |

### Part 3: Mass Operations (Lazy)

| # | Problem | Link | Key Concept |
|:-:|---------|------|-------------|
| A | Assignment to Segment | [Contest 279634/A](https://codeforces.com/edu/course/2/lesson/5/1/practice/contest/279634/problem/A) | Range add + point query |
| B | Assignment to Segment (range query) | [Contest 279653/A](https://codeforces.com/edu/course/2/lesson/5/2/practice/contest/279653/problem/A) | Range assign + range query |

---

## 📈 CSES Range Query Section — Complete List

| # | Problem | Link | Key Data Structure | Difficulty |
|:-:|---------|------|--------------------|:----------:|
| 1 | Static Range Sum Queries | [Task 1646](https://cses.fi/problemset/task/1646) | Prefix Sum | ⭐ |
| 2 | Static Range Minimum Queries | [Task 1647](https://cses.fi/problemset/task/1647) | Sparse Table | ⭐⭐ |
| 3 | Dynamic Range Sum Queries | [Task 1648](https://cses.fi/problemset/task/1648) | BIT / Segment Tree | ⭐⭐ |
| 4 | Dynamic Range Minimum Queries | [Task 1649](https://cses.fi/problemset/task/1649) | Segment Tree | ⭐⭐ |
| 5 | Range Xor Queries | [Task 1650](https://cses.fi/problemset/task/1650) | Prefix XOR | ⭐ |
| 6 | Range Update Queries | [Task 1651](https://cses.fi/problemset/task/1651) | BIT / Lazy ST | ⭐⭐ |
| 7 | Forest Queries | [Task 1652](https://cses.fi/problemset/task/1652) | 2D Prefix Sum | ⭐⭐ |
| 8 | Hotel Queries | [Task 1143](https://cses.fi/problemset/task/1143) | ST + Walking | ⭐⭐⭐ |
| 9 | List Removals | [Task 1749](https://cses.fi/problemset/task/1749) | BIT + BS / ST | ⭐⭐⭐ |
| 10 | Salary Queries | [Task 1144](https://cses.fi/problemset/task/1144) | BIT + Compression | ⭐⭐⭐ |
| 11 | Prefix Sum Queries | [Task 2166](https://cses.fi/problemset/task/2166) | Segment Tree | ⭐⭐⭐ |
| 12 | Pizzeria Queries | [Task 2206](https://cses.fi/problemset/task/2206) | Segment Tree | ⭐⭐⭐ |
| 13 | Subarray Sum Queries | [Task 1190](https://cses.fi/problemset/task/1190) | Max Subarray ST | ⭐⭐⭐ |
| 14 | Distinct Values Queries | [Task 1734](https://cses.fi/problemset/task/1734) | Mo's / Offline BIT | ⭐⭐⭐ |
| 15 | Increasing Array Queries | [Task 2416](https://cses.fi/problemset/task/2416) | Stack + ST | ⭐⭐⭐⭐ |
| 16 | Forest Queries II | [Task 1739](https://cses.fi/problemset/task/1739) | 2D BIT | ⭐⭐⭐ |
| 17 | Range Queries and Copies | [Task 1737](https://cses.fi/problemset/task/1737) | Persistent ST | ⭐⭐⭐⭐ |
| 18 | Polynomial Queries | [Task 1736](https://cses.fi/problemset/task/1736) | Lazy ST (two lazy) | ⭐⭐⭐ |

---

## 🏅 SPOJ Classical Range Query Problems

These are the **gold standard** problems for learning range query structures:

| # | Problem Code | Problem Name | Key Structure | Difficulty |
|:-:|:-------------|-------------|---------------|:----------:|
| 1 | [RMQSQ](https://www.spoj.com/problems/RMQSQ/) | Range Minimum Query | Sparse Table | ⭐⭐ |
| 2 | [HORRIBLE](https://www.spoj.com/problems/HORRIBLE/) | Horrible Queries | Lazy Segment Tree | ⭐⭐⭐ |
| 3 | [GSS1](https://www.spoj.com/problems/GSS1/) | Can you answer queries I | Max Subarray ST | ⭐⭐⭐ |
| 4 | [GSS3](https://www.spoj.com/problems/GSS3/) | Can you answer queries III | Max Subarray ST + Update | ⭐⭐⭐ |
| 5 | [GSS4](https://www.spoj.com/problems/GSS4/) | Can you answer queries IV | ST + Sqrt brute force | ⭐⭐⭐ |
| 6 | [GSS5](https://www.spoj.com/problems/GSS5/) | Can you answer queries V | Max Subarray (constrained) | ⭐⭐⭐⭐ |
| 7 | [GSS7](https://www.spoj.com/problems/GSS7/) | Can you answer queries VII | HLD + Max Subarray ST | ⭐⭐⭐⭐⭐ |
| 8 | [MKTHNUM](https://www.spoj.com/problems/MKTHNUM/) | K-th Number | Persistent ST / MST | ⭐⭐⭐⭐ |
| 9 | [COT](https://www.spoj.com/problems/COT/) | Count on a Tree | Persistent ST + LCA | ⭐⭐⭐⭐ |
| 10 | [DQUERY](https://www.spoj.com/problems/DQUERY/) | D-query | Mo's / Offline BIT | ⭐⭐⭐ |
| 11 | [KQUERY](https://www.spoj.com/problems/KQUERY/) | K-Query | Offline + BIT / MST | ⭐⭐⭐ |
| 12 | [KQUERYO](https://www.spoj.com/problems/KQUERYO/) | K-Query Online | Merge Sort Tree / PST | ⭐⭐⭐⭐ |
| 13 | [MATSUM](https://www.spoj.com/problems/MATSUM/) | Matrix Summation | 2D BIT | ⭐⭐⭐ |
| 14 | [UPDATEIT](https://www.spoj.com/problems/UPDATEIT/) | Update the Array | BIT / Difference Array | ⭐⭐ |
| 15 | [QTREE](https://www.spoj.com/problems/QTREE/) | Query on a Tree | HLD + ST | ⭐⭐⭐⭐ |
| 16 | [QTREE3](https://www.spoj.com/problems/QTREE3/) | Query on a Tree III | HLD + ST + Walking | ⭐⭐⭐⭐ |
| 17 | [METEORS](https://www.spoj.com/problems/METEORS/) | Meteors | Parallel Binary Search + BIT | ⭐⭐⭐⭐⭐ |
| 18 | [FREQUENT](https://www.spoj.com/problems/FREQUENT/) | Frequent Values | ST (custom merge) | ⭐⭐⭐ |
| 19 | [ILKQUERY](https://www.spoj.com/problems/ILKQUERY/) | I Love Kth Query | Wavelet / Persistent | ⭐⭐⭐⭐ |
| 20 | [NKLEAVES](https://www.spoj.com/problems/NKLEAVES/) | Leaves | Li Chao Tree / CHT | ⭐⭐⭐⭐ |

---

## 🎯 30-Day Challenge — Master Range Queries

Follow this plan to solve the most important problems in order:

### Week 1: Foundation + Basic ST + BIT
```
Day 1: LC 303, CSES 1646, CSES 1650 (Prefix Sum / XOR)
Day 2: LC 304, CSES 1652, LC 1109 (2D Prefix Sum, Diff Array)
Day 3: CSES 1648, LC 307 (Basic Segment Tree / BIT)
Day 4: CSES 1649, CF 339D (Min Segment Tree)
Day 5: LC 315, CSES 1751 (BIT + Inversions)
Day 6: CSES 1749, CSES 2163 (BIT + Binary Search)
Day 7: Revise + Solve 3 more from Section 2 & 7
```

### Week 2: Lazy Propagation + Variants
```
Day 8:  CSES 1651 (Range Update — basic lazy)
Day 9:  SPOJ HORRIBLE (Range Add + Range Sum — must do!)
Day 10: CSES 1736 (Polynomial Queries — two lazy values)
Day 11: CF 52C (Circular RMQ — tricky lazy)
Day 12: SPOJ GSS1 (Max Subarray Sum on ST — crucial!)
Day 13: SPOJ GSS3 (GSS1 + updates)
Day 14: CF 380C (Sereja and Brackets — custom merge)
```

### Week 3: Sparse Table + Mo's + Advanced
```
Day 15: CSES 1647, SPOJ RMQSQ (Sparse Table)
Day 16: SPOJ DQUERY (Mo's Algorithm — first Mo's problem)
Day 17: CF 86D (Powerful Array — classic Mo's)
Day 18: CF 617E (XOR and Favorite Number — Mo's)
Day 19: CSES 1143 (Hotel Queries — ST Walking)
Day 20: CF EDU ST Walking problems (First ≥ X, Kth One)
Day 21: Revise + Solve 3 more from Section 10 & 11
```

### Week 4: Trees + Persistent + ICPC
```
Day 22: CSES 1137 (Subtree Queries — Euler Tour + BIT)
Day 23: CSES 1138 (Path Queries — Euler Tour)
Day 24: CSES 2134 (Path Queries II — HLD!)
Day 25: CF 620E (New Year Tree — Euler Tour + Bitmask)
Day 26: CSES 1737 (Range Queries and Copies — Persistent ST)
Day 27: SPOJ MKTHNUM (Kth Number — Persistent ST / MST)
Day 28: SPOJ COT (Count on a Tree — PST + LCA)
Day 29: CF 438D + LG P4117 (ST Beats basics)
Day 30: YosupoOJ Li Chao Tree + AC Frog 3 (Li Chao / CHT)
```

---

## 📊 Problem Count by Platform

| Platform | Count | Focus Areas |
|----------|:-----:|-------------|
| CSES | 25+ | Full range query section, tree queries |
| Codeforces | 35+ | All difficulty levels, CF EDU course |
| SPOJ | 20+ | Classical problems (GSS series, MKTHNUM) |
| LeetCode | 15+ | Prefix sum, BIT, ST basics |
| GFG | 5+ | Practice and learning |
| AtCoder | 3+ | DP + CHT, string problems |
| CodeChef | 5+ | Mo's, wavelet tree |
| YosupoOJ | 5+ | Library checker (Li Chao, ST Beats, HLD) |
| Luogu | 3+ | ST Beats, advanced Chinese OI problems |

**Total: 150+ problems covering every range query technique from beginner to ICPC level!**

---

<div align="center">

### Made with ❤️ for the Competitive Programming Community

*"Don't just read about segment trees — solve problems until your fingers build them from muscle memory."*  
— **Sarvan Yaduvanshi**

**⭐ Star this repo if it helped you! ⭐**

</div>

