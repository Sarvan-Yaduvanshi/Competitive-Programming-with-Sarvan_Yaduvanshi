# 📘 Chapter 03 — Ordered Associative Containers

## Overview
Ordered associative containers maintain elements in **sorted order** using balanced BSTs (Red-Black Trees). They provide O(log n) operations and are essential for problems requiring sorted queries.

## Files in This Chapter

| # | File | Topic | Key Concepts |
|:-:|------|-------|-------------|
| 01 | `01_Set_Complete.cpp` | set | insert, erase, find, lower/upper_bound, custom comparator |
| 02 | `02_Multiset_Complete.cpp` | multiset | Duplicates, erase-one trick, sliding window median |
| 03 | `03_Map_Complete.cpp` | map | key-value, [], at(), structured bindings, frequency counting |
| 04 | `04_Multimap_Complete.cpp` | multimap | equal_range, multiple keys, event scheduling |
| 05 | `05_Ordered_Container_Tricks.cpp` | Advanced Tricks | Node handles, interval set, sorted array replacement |

## 🎯 GM Tips
- **ALWAYS use member `.find()`, `.lower_bound()`** — NOT `std::find()`, `std::lower_bound()`
- Member functions are O(log n), std:: versions are O(n) on set/map!
- Erase ONE from multiset: `ms.erase(ms.find(x))` NOT `ms.erase(x)` (erases ALL!)
- Custom comparator with `set<T, Comp>` for non-default ordering
- set = unique sorted elements, multiset = sorted with duplicates

