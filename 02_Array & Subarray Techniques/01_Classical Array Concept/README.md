# 🏆 Classical Array Concepts — Zero to Grandmaster (GM) Level

> **Author:** Sarvan Yaduvanshi  
> **Level:** Beginner → Intermediate → Advanced → Expert → Grandmaster  
> **Language:** C++ (C++20)

---

## 📋 What is an Array?

An **Array** is the most fundamental data structure in competitive programming. It stores elements in **contiguous memory**, enabling **O(1) random access** by index. Mastering arrays is the gateway to every advanced topic — sliding windows, prefix sums, segment trees, and beyond.

### Why Master Arrays First?
1. **Foundation** — 90% of CP problems involve arrays in some form
2. **Speed** — Cache-friendly, O(1) access → fastest data structure
3. **Versatility** — Building block for stacks, queues, heaps, hash tables
4. **Patterns** — Traversal, rotation, partition, merge → reused everywhere

---

## 🗺️ Complete Roadmap (10 Modules + 4 Existing)

```
                        ┌──────────────────────────────────────┐
                        │   CLASSICAL ARRAY CONCEPTS ROADMAP   │
                        │   Zero ──────────► GM Level          │
                        └──────────────────────────────────────┘

   ┌──────────────────┐     ┌──────────────────────┐     ┌──────────────────────┐
   │ 01. Static Array  │────►│ 02. Input / Output   │────►│ 03. Traversal        │
   │  & Vector Basics  │     │  Patterns            │     │  Patterns            │
   └────────┬─────────┘     └──────────┬───────────┘     └──────────┬───────────┘
            │                          │                             │
            ▼                          ▼                             ▼
   ┌──────────────────┐     ┌──────────────────────┐     ┌──────────────────────┐
   │ 04. Searching in  │────►│ 05. Array Rotation   │────►│ 06. Reversal &       │
   │  Arrays           │     │  Concepts            │     │  Rearrangement       │
   └────────┬─────────┘     └──────────┬───────────┘     └──────────┬───────────┘
            │                          │                             │
            ▼                          ▼                             ▼
   ┌──────────────────┐     ┌──────────────────────┐     ┌──────────────────────┐
   │ 07. Kth Largest & │────►│ 08. Index Shifting & │────►│ 09. Advanced         │
   │  Second Element   │     │  Math Tricks         │     │  Rearrangement       │
   └────────┬─────────┘     └──────────┬───────────┘     └──────────┬───────────┘
            │                          │                             │
            ▼                          ▼                             ▼
   ┌──────────────────┐     ┌──────────────────────────────────────────────────┐
   │ 10. Merge &       │────►│  EXISTING: Max/Min, Pairs, Subarray, Hashing    │
   │  Partition         │     │  (Foundation already built)                     │
   └───────────────────┘     └──────────────────────────────────────────────────┘
```

---

## 📁 Module Index

| #  | File | Topic | Level |
|----|------|-------|-------|
| 00 | `00_Array_Master_Problem_CheatSheet.cpp` | 100+ curated problems with links | All Levels |
| 01 | `01_Static_Array_and_Vector_Basics.cpp` | C-array, std::array, std::vector, init patterns | ⭐ Beginner |
| 02 | `02_Input_Output_Patterns.cpp` | Fast I/O, read/print patterns, EOF handling | ⭐ Beginner |
| 03 | `03_Traversal_Patterns.cpp` | Forward, reverse, zigzag, iterator-based | ⭐ Beginner |
| 04 | `04_Searching_in_Array.cpp` | Linear, binary, STL, rotated sorted search | ⭐⭐ Intermediate |
| 05 | `05_Array_Rotation_Concepts.cpp` | Reversal algo, juggling, cyclic replacement | ⭐⭐ Intermediate |
| 06 | `06_Reversal_and_Rearrangement.cpp` | Dutch National Flag, segregate, move zeros | ⭐⭐ Intermediate |
| 07 | `07_Second_Largest_and_Kth_Element.cpp` | Kth via heap, Quickselect, nth_element | ⭐⭐⭐ Advanced |
| 08 | `08_Index_Shifting_and_Math_Tricks.cpp` | Cyclic index, encoding, coord compression | ⭐⭐⭐ Advanced |
| 09 | `09_Array_Rearrangement_Advanced.cpp` | Next permutation, Boyer-Moore, leaders | ⭐⭐⭐⭐ Expert |
| 10 | `10_Merge_and_Partition_Techniques.cpp` | Merge sorted, Hoare/Lomuto partition | ⭐⭐⭐⭐ Expert |
| 11 | `Pairs_in_Array.cpp` | Cartesian, combinations, sum/diff/XOR pairs, 2Sum, 3Sum, 4Sum, pair sorting | ⭐⭐ Intermediate |
| 12 | `Subarray_All_Concept.cpp` | Print all, brute→Kadane's, circular, product, prefix+hash, XOR, sliding window, 2D Kadane's | ⭐⭐⭐⭐ Expert |
| 13 | `Maximum_and_Minimum.cpp` | Min/Max (linear, tournament, STL) | ⭐ Beginner |

---

## 📊 Difficulty Progression

```
⭐ Beginner        → Modules 01, 02, 03, Max/Min
⭐⭐ Intermediate   → Modules 04, 05, 06, Pairs, Hashing
⭐⭐⭐ Advanced      → Modules 07, 08, Subarray
⭐⭐⭐⭐ Expert       → Modules 09, 10
⭐⭐⭐⭐⭐ GM          → Combine all techniques (see Cheat Sheet)
```

---

## 🎯 How to Study

1. **Read each file top to bottom** — Comments explain WHY, not just WHAT
2. **Run with small inputs** — Understand the output before scaling up
3. **Trace by hand** — Dry-run algorithms on paper for arrays of size 5-8
4. **Solve the cheat sheet problems** — Sorted by difficulty within each module
5. **Time yourself** — Real GM skill = speed × accuracy

---

## 💡 GM Tips

- **Always use `i64` (long long) for sums** — `int` overflows at ~2×10⁹
- **Prefer `vec<int>` over C-arrays** — Bounds-safe, resizable, STL-compatible
- **Know your STL** — `rotate`, `nth_element`, `partition`, `next_permutation`
- **Think before coding** — O(N) beats O(N²) by 1000x at N = 10⁶
- **Edge cases** — Empty array, single element, all same, all negative

