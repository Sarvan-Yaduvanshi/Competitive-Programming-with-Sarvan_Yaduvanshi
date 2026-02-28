# 📘 Chapter 11 — STL Performance & Optimization

## 🔥 Why This Chapter Matters
> *"The difference between AC and TLE is NOT your algorithm — it's your STL usage.  
> A GM-level coder with the SAME algorithm beats you by choosing the right container, avoiding copies, and knowing the hidden constants."*

## Overview
This chapter covers **everything** about making your STL code as fast as physically possible. Every concept has **benchmarks**, **dry runs**, **common TLE traps**, and **Codeforces-tested fixes**.

---

## Files in This Chapter

| # | File | Topic | Key Concepts |
|:-:|------|-------|-------------|
| 01 | `01_Time_Complexity_Of_All_Containers.cpp` | Time Complexity Master Table | Every operation for every container, amortized vs worst-case, hidden constants |
| 02 | `02_Vector_Vs_List_Deep_Dive.cpp` | vector vs list | Cache locality, benchmark proof, when list actually wins, splice vs insert |
| 03 | `03_Map_Vs_Unordered_Map_Battle.cpp` | map vs unordered_map | When each wins, string keys, anti-hash TLE, sorted-order needs |
| 04 | `04_Avoid_TLE_In_Unordered_Map.cpp` | Avoid TLE in unordered_map | Anti-hack hash, reserve, rehash, load factor tuning, CF blowup cases |
| 05 | `05_Reserve_Optimization.cpp` | Reserve Optimization | vector::reserve, unordered_map::reserve, capacity growth, shrink_to_fit |
| 06 | `06_Emplace_Vs_Push.cpp` | emplace vs push | emplace_back vs push_back, emplace vs insert, in-place construction, benchmarks |
| 07 | `07_Fast_IO_Complete.cpp` | Fast I/O | sync_with_stdio, cin.tie, endl vs \\n, scanf/printf, custom fast reader |
| 08 | `08_Avoid_Unnecessary_Copying.cpp` | Avoid Unnecessary Copies | const ref, auto&, pass-by-ref, return value optimization, string copies |
| 09 | `09_Move_Semantics.cpp` | Move Semantics | std::move, rvalue references, move constructor, when compiler moves for you |
| 10 | `10_Memory_Layout_And_Cache.cpp` | Memory Layout & Cache | Cache lines, AoS vs SoA, contiguous vs node-based, false sharing, practical tips |

---

## 🎯 GM-Level Optimization Checklist

```
MUST-DO (saves you from 90% of TLEs):
  ☑ ios::sync_with_stdio(false); cin.tie(nullptr);
  ☑ '\n' not endl
  ☑ const auto& in range-for loops
  ☑ reserve() vectors when size is known
  ☑ reserve() + custom hash for unordered_map
  ☑ Pass vectors/strings by const reference

ADVANCED (Expert → GM gap):
  ☑ emplace_back over push_back for pairs/structs
  ☑ Use member .find()/.lower_bound() on set/map
  ☑ nth_element O(N) instead of sort O(NlogN) for k-th
  ☑ bitset for boolean DP (64x speedup)
  ☑ #pragma GCC optimize("O2,unroll-loops")
  ☑ Avoid allocations inside hot loops
```

## ⏱️ Quick Reference: Operation Counts per Second
```
Simple operations (add, compare):     ~10^8 - 10^9 / sec
Vector random access:                 ~10^9 / sec
Map insert/find:                      ~10^7 / sec (log factor + cache miss)
Unordered_map insert/find (avg):      ~5×10^7 / sec
Set insert/find:                      ~10^7 / sec
Sorting N elements:                   N ≤ 10^6 easily in 1s
Priority_queue push/pop:              ~2×10^7 / sec
```

