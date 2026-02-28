# 📘 Chapter 04 — Unordered Containers

## Overview
Hash-based containers providing **O(1) average** operations. The fastest lookup containers in C++, but with pitfalls you MUST know for competitive programming.

## Files in This Chapter

| # | File | Topic | Key Concepts |
|:-:|------|-------|-------------|
| 01 | `01_Unordered_Set_Complete.cpp` | unordered_set | insert, find, erase, bucket interface, load factor |
| 02 | `02_Unordered_Map_Complete.cpp` | unordered_map | frequency map, two-sum, subarray-sum patterns |
| 03 | `03_Hashing_Fundamentals.cpp` | Hashing Theory | hash functions, chaining, open addressing |
| 04 | `04_Custom_Hash.cpp` | Custom Hash | Anti-hack hash, pair/vector/struct hashing |
| 05 | `05_Collision_And_Performance.cpp` | Performance | Worst-case attacks, benchmarks, when to avoid |

## 🔥 CRITICAL GM TIP
On Codeforces, hackers can ATTACK your `unordered_map` with specially crafted inputs that cause O(n) per operation! **Always use custom hash** or switch to `map` for safety.

## 📊 Average vs Worst Case
```
┌─────────────────┬──────────┬──────────┐
│ Operation       │ Average  │ Worst    │
├─────────────────┼──────────┼──────────┤
│ insert          │ O(1)     │ O(n)     │
│ find            │ O(1)     │ O(n)     │
│ erase           │ O(1)     │ O(n)     │
│ bucket_count    │ O(1)     │ O(1)     │
└─────────────────┴──────────┴──────────┘
```

