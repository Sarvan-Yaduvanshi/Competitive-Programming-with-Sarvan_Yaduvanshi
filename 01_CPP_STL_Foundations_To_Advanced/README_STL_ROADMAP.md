<div align="center">

# 🏗️ C++ STL Foundations to Advanced — Zero to Grandmaster

### Complete Competitive Programming STL Mastery Guide

[![C++17](https://img.shields.io/badge/C%2B%2B-17%2F20-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Chapters](https://img.shields.io/badge/Chapters-12-blueviolet?style=for-the-badge)](.)
[![Files](https://img.shields.io/badge/Files-56%20CPP%20%2B%2013%20READMEs-orange?style=for-the-badge)](.)
[![Difficulty](https://img.shields.io/badge/Level-Zero%20→%20Grandmaster-red?style=for-the-badge)](.)
[![Author](https://img.shields.io/badge/Author-Sarvan%20Yaduvanshi-green?style=for-the-badge)](https://github.com/Sarvan-Yaduvanshi)

> *"STL is not just a library — it's the weapon that separates a 1200-rated coder from a Grandmaster. Master it, and you master competitive programming."*  
> — **Sarvan Yaduvanshi**

</div>

---

## 📖 About This Module

This module is the **most comprehensive C++ STL resource** for competitive programmers. Every concept is taught from **absolute zero** to **Grandmaster-level tricks**, with dry runs, real contest examples, and battle-tested patterns.

**What makes this different?**
- 🧠 **Concept-first approach** — Every STL component explained with internals, not just API
- 💻 **Separate .cpp per concept** — Clean, focused, runnable files with test cases
- 📊 **Complexity tables** — Every operation's time/space at a glance
- 🏆 **100+ practice problems** — Curated from Codeforces, LeetCode, CSES, AtCoder
- 🎯 **GM-level tricks** — Anti-hash attacks, PBDS, bitset DP, monotonic structures
- 🔄 **Progressive difficulty** — From "What is STL?" to "PBDS + Coordinate Compression"

---

## 🗂️ Chapter Index

### 🟢 Level 1 — Foundation (Newbie → Pupil)

| # | Chapter | Key Topics | Difficulty |
|:-:|---------|------------|:----------:|
| 01 | [**STL Introduction & Basics**](01_STL_Introduction_And_Basics/) | What is STL, Containers vs Algorithms, Iterators, Time Complexity, Headers, Namespaces, Auto, Range loops, Lambda basics | ⭐ |
| 02 | [**Sequence Containers**](02_Sequence_Containers/) | vector, deque, list, forward_list, array — all operations, 2D vectors, iteration | ⭐ |

### 🟡 Level 2 — Intermediate (Pupil → Specialist)

| # | Chapter | Key Topics | Difficulty |
|:-:|---------|------------|:----------:|
| 03 | [**Ordered Associative Containers**](03_Ordered_Associative_Containers/) | set, multiset, map, multimap, custom comparators, lower/upper_bound, structured bindings | ⭐⭐ |
| 04 | [**Unordered Containers**](04_Unordered_Containers/) | unordered_set/map, hashing internals, custom hash, collision attacks, performance | ⭐⭐ |
| 05 | [**Container Adaptors**](05_Container_Adaptors/) | stack, queue, priority_queue, min-heap, custom comparators, monotonic patterns | ⭐⭐⭐ |

### 🔴 Level 3 — Advanced (Specialist → Expert)

| # | Chapter | Key Topics | Difficulty |
|:-:|---------|------------|:----------:|
| 06 | [**Iterators & Utilities**](06_Iterators_And_Utilities/) | Iterator types, advance/distance/next/prev, invalidation rules, pair, tuple, tie | ⭐⭐⭐ |
| 07 | [**STL Algorithms**](07_STL_Algorithms/) | sort, binary_search, lower/upper_bound, rotate, accumulate, set operations, erase-remove | ⭐⭐⭐ |
| 08 | [**Functional & Lambda**](08_Functional_And_Lambda/) | Lambda syntax, capture list, mutable, std::function, bind, recursive lambdas | ⭐⭐⭐ |

### 🟣 Level 4 — Master (Expert → Master)

| # | Chapter | Key Topics | Difficulty |
|:-:|---------|------------|:----------:|
| 09 | [**Advanced STL Utilities**](09_Advanced_STL_Utilities/) | bitset, optional, variant, chrono, random, smart pointers, string_view | ⭐⭐⭐⭐ |
| 10 | [**Policy-Based Data Structures**](10_Policy_Based_Data_Structures/) | PBDS ordered set, fast IO, move semantics, container selection guide, performance tuning | ⭐⭐⭐⭐ |
| 11 | [**STL Performance & Optimization**](11_STL_Performance_And_Optimization/) | Container complexity, vector vs list, map vs unordered_map, avoid TLE, reserve, emplace vs push, fast IO, avoid copies, move semantics, memory layout & cache | ⭐⭐⭐⭐ |

### 💎 Level 5 — Grandmaster (Master → Grandmaster)

| # | Chapter | Key Topics | Difficulty |
|:-:|---------|------------|:----------:|
| 12 | [**Advanced STL Tricks for CP**](12_Advanced_STL_Tricks_For_CP/) | Coordinate compression, multiset sliding window, interval set, monotonic queue, bitset DP, PBDS advanced | ⭐⭐⭐⭐⭐ |

---

## 📊 Master Complexity Reference

### Container Operations Cheat Sheet

```
┌─────────────────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
│ Container           │ Access   │ Insert   │ Erase    │ Find     │ Space    │
├─────────────────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
│ vector              │ O(1)     │ O(1)*    │ O(n)     │ O(n)     │ O(n)     │
│ deque               │ O(1)     │ O(1)*    │ O(n)     │ O(n)     │ O(n)     │
│ list                │ O(n)     │ O(1)     │ O(1)     │ O(n)     │ O(n)     │
│ forward_list        │ O(n)     │ O(1)     │ O(1)     │ O(n)     │ O(n)     │
│ array               │ O(1)     │ N/A      │ N/A      │ O(n)     │ O(n)     │
│ set / multiset      │ O(logn)  │ O(logn)  │ O(logn)  │ O(logn)  │ O(n)     │
│ map / multimap      │ O(logn)  │ O(logn)  │ O(logn)  │ O(logn)  │ O(n)     │
│ unordered_set       │ O(1)     │ O(1)     │ O(1)     │ O(1)     │ O(n)     │
│ unordered_map       │ O(1)     │ O(1)     │ O(1)     │ O(1)     │ O(n)     │
│ stack               │ O(1)top  │ O(1)push │ O(1)pop  │ N/A      │ O(n)     │
│ queue               │ O(1)frt  │ O(1)push │ O(1)pop  │ N/A      │ O(n)     │
│ priority_queue      │ O(1)top  │ O(logn)  │ O(logn)  │ N/A      │ O(n)     │
│ PBDS ordered set    │ O(logn)  │ O(logn)  │ O(logn)  │ O(logn)  │ O(n)     │
└─────────────────────┴──────────┴──────────┴──────────┴──────────┴──────────┘
  * = amortized. Unordered = average case; worst case is O(n) per operation.
```

### When to Use What? Decision Flowchart

```
Need ordered data?
├── YES → Need key-value? 
│         ├── YES → Duplicates? → multimap : map
│         └── NO  → Duplicates? → multiset : set
└── NO  → Need O(1) lookup?
          ├── YES → Need key-value?
          │         ├── YES → unordered_map
          │         └── NO  → unordered_set
          └── NO  → Need random access?
                    ├── YES → Fixed size? → array : vector
                    └── NO  → Need front insert? → deque : list
```

---

## 🏆 GM Tips — The Meta-Knowledge

### 🔥 Top 10 STL Rules for Competitive Programming

1. **Always use `ios::sync_with_stdio(false); cin.tie(0);`** — 10x faster I/O
2. **`emplace_back` > `push_back`** — Avoids copy construction
3. **`reserve()` your vectors** — Prevents reallocation overhead
4. **Use custom hash for `unordered_map`** — Prevents anti-hash attacks on Codeforces
5. **`lower_bound` on set uses `.lower_bound()`** — Member function is O(log n), `std::lower_bound` is O(n)!
6. **Erase ONE element from multiset: `s.erase(s.find(x))`** — NOT `s.erase(x)` which erases ALL
7. **`nth_element` for k-th smallest** — O(n) average vs O(n log n) for full sort
8. **Bitset can speed up DP by 64x** — Use it for knapsack, reachability
9. **PBDS `order_of_key` + `find_by_order`** — O(log n) k-th element queries
10. **`__builtin_popcount` + `__builtin_clz`** — Faster than manual bit counting

### ⚡ Fast I/O Template for CP
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Your code here
    
    return 0;
}
```

---

## 📚 Curated Problem Sets

### Beginner (Rating 800-1200)
| Problem | Platform | Key STL Concept |
|---------|----------|-----------------|
| [Sort the Array](https://codeforces.com/problemset/problem/451/B) | CF | `sort()` |
| [Two Sum](https://leetcode.com/problems/two-sum/) | LC | `unordered_map` |
| [Next Greater Element](https://leetcode.com/problems/next-greater-element-i/) | LC | `stack + unordered_map` |
| [Distinct Numbers](https://cses.fi/problemset/task/1621) | CSES | `set` |

### Intermediate (Rating 1200-1600)
| Problem | Platform | Key STL Concept |
|---------|----------|-----------------|
| [Playlist](https://cses.fi/problemset/task/1141) | CSES | `set + sliding window` |
| [Top K Frequent](https://leetcode.com/problems/top-k-frequent-elements/) | LC | `priority_queue + map` |
| [Towers](https://cses.fi/problemset/task/1073) | CSES | `multiset` |
| [Sum of Two Values](https://cses.fi/problemset/task/1640) | CSES | `map` |

### Advanced (Rating 1600-2100)
| Problem | Platform | Key STL Concept |
|---------|----------|-----------------|
| [Josephus Problem II](https://cses.fi/problemset/task/2163) | CSES | `PBDS ordered set` |
| [Sliding Window Median](https://leetcode.com/problems/sliding-window-median/) | LC | `two multisets` |
| [Dynamic Range Sum](https://cses.fi/problemset/task/1648) | CSES | `BIT / Segment Tree` |

### Grandmaster (Rating 2100+)
| Problem | Platform | Key STL Concept |
|---------|----------|-----------------|
| [Inversions](https://cses.fi/problemset/task/1751) | CSES | `PBDS + coordinate compression` |
| [Knapsack (bitset)](https://atcoder.jp/contests/abc032/tasks/abc032_d) | AtCoder | `bitset DP` |
| [Range Queries Pack](https://codeforces.com/problemset/problem/1354/D) | CF | `multiset + binary search` |

---

## 🎓 How to Study This Module

```
Week 1: Chapters 01-02 (Basics + Sequence Containers)
Week 2: Chapters 03-05 (Associative + Adaptors)
Week 3: Chapters 06-08 (Iterators + Algorithms + Lambdas)
Week 4: Chapters 09-11 (Advanced Utilities + PBDS + Performance)
Week 5: Chapter 12 (GM Tricks — practice with real problems)
```

**For each chapter:**
1. 📖 Read the README first for overview
2. 💻 Run each .cpp file and study the output
3. 🧪 Modify the code — break things and fix them
4. 🏆 Solve the practice problems at the end of each file
5. 📝 Build your own template with the tricks you learn

---

<div align="center">

### Made with ❤️ for the Competitive Programming Community

*"The best competitive programmers don't write more code — they write smarter code using STL."*  
— **Sarvan Yaduvanshi**

**⭐ Star this repo if it helped you! ⭐**

</div>

