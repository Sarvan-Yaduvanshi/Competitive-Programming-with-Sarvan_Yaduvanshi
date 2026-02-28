# 🏆 Two Pointer & Sliding Window — Zero to Grandmaster (GM) Level

> **Author:** Sarvan Yaduvanshi  
> **Level:** Beginner → Intermediate → Advanced → Expert → Grandmaster  
> **Language:** C++ (C++20)

---

## 📋 What is Two Pointer & Sliding Window?

**Two Pointer** uses two indices that move through the data structure in a coordinated way to solve problems in O(N) instead of O(N²).

**Sliding Window** is a special case of two pointer where we maintain a "window" (contiguous subarray/substring) and slide it across the data — either with a **fixed** or **variable** size.

### Why Are These Techniques So Important?
1. **80%+ of array/string interview questions** use one of these patterns
2. **Codeforces Div2 A-D** frequently tests sliding window and two pointer
3. Reduces **O(N²) brute force** to **O(N)** — the most common optimization trick
4. Foundation for advanced techniques: **convex hull trick, deque optimization, segment tree + sliding window**

---

## 🗺️ Complete Roadmap (14 Modules)

```
                    ┌────────────────────────────────────────────────┐
                    │   TWO POINTER & SLIDING WINDOW ROADMAP         │
                    │   Zero ────────────────────────► GM Level      │
                    └────────────────────────────────────────────────┘

╔═══════════════════════════════════════════════════════════════════════════════╗
║                    SECTION A: TWO POINTER TECHNIQUE                         ║
╚═══════════════════════════════════════════════════════════════════════════════╝

    ┌─────────────────────┐     ┌──────────────────────────┐     ┌─────────────────────────────┐
    │ 01. Two Pointer      │────►│ 02. Opposite Direction   │────►│ 03. Palindrome & String     │
    │   Fundamentals       │     │ (2Sum,3Sum,4Sum,Trap)    │     │   Two Pointer               │
    └──────────┬──────────┘     └──────────┬───────────────┘     └─────────────┬───────────────┘
               │                           │                                   │
               ▼                           ▼                                   ▼
    ┌─────────────────────┐     ┌──────────────────────────┐     ┌─────────────────────────────┐
    │ 04. Fast & Slow      │────►│ 05. Sorted Array Merge   │────►│ 06. Binary Search + Two Ptr │
    │ (Floyd's Cycle)      │     │ & Partition (DNF)        │     │   (Pair Distance, Count)    │
    └──────────┬──────────┘     └──────────┬───────────────┘     └─────────────┬───────────────┘
               │                           │                                   │
               ▼                           ▼                                   ▼
                              ┌──────────────────────────┐
                              │ 07. Two Pointer CF Probs  │
                              │ (800 → 2400+ Rating)      │
                              └──────────────────────────┘

╔═══════════════════════════════════════════════════════════════════════════════╗
║                    SECTION B: FIXED SIZE SLIDING WINDOW                     ║
╚═══════════════════════════════════════════════════════════════════════════════╝

    ┌─────────────────────┐     ┌──────────────────────────┐     ┌─────────────────────────────┐
    │ 08. Fixed Window     │────►│ 09. Fixed Window + Deque │────►│ 10. Fixed Window CF Probs   │
    │   Fundamentals       │     │ & Hashing (Anagram)      │     │   (800 → 2400+ Rating)      │
    └──────────────────────┘     └──────────────────────────┘     └─────────────────────────────┘

╔═══════════════════════════════════════════════════════════════════════════════╗
║                    SECTION C: VARIABLE SIZE SLIDING WINDOW                  ║
╚═══════════════════════════════════════════════════════════════════════════════╝

    ┌─────────────────────┐     ┌──────────────────────────┐     ┌─────────────────────────────┐
    │ 11. Variable Window  │────►│ 12. Distinct & Frequency │────►│ 13. Advanced Variable Win   │
    │   Fundamentals       │     │ (AtMostK, ExactK)        │     │ (Min Window, Median, etc.)  │
    └──────────┬──────────┘     └──────────┬───────────────┘     └─────────────┬───────────────┘
               │                           │                                   │
               ▼                           ▼                                   ▼
                              ┌──────────────────────────┐
                              │ 14. Variable Window CF    │
                              │ (800 → 2400+ Rating)      │
                              └──────────────────────────┘
```

---

## 📁 Module Index

### Section A: Two Pointer Technique

| # | Module | Level | Key Concepts |
|---|--------|-------|-------------|
| 01 | [Two Pointer Fundamentals](01_Two_Pointer_Fundamentals/) | ⭐ Beginner | Definition, 3 Types, Templates, When to Use |
| 02 | [Opposite Direction Problems](02_Opposite_Direction_Problems/) | ⭐⭐ Intermediate | 2Sum, 3Sum, 4Sum, KSum, Container Water, Trapping Rain Water |
| 03 | [Palindrome & String Two Pointer](03_Palindrome_And_String_Two_Pointer/) | ⭐⭐ Intermediate | Valid Palindrome, Palindrome II/III, Longest Palindromic Substring |
| 04 | [Fast & Slow Pointers](04_Fast_Slow_Pointers_And_Cycle_Detection/) | ⭐⭐ Intermediate | Floyd's Cycle, Linked List Cycle, Duplicate Number, Happy Number |
| 05 | [Sorted Array Merge & Partition](05_Sorted_Array_Merge_And_Partition/) | ⭐⭐ Intermediate | Merge Sorted, Remove Duplicates, Dutch National Flag, Sort Colors |
| 06 | [Binary Search + Two Pointer](06_Binary_Search_Plus_Two_Pointer/) | ⭐⭐⭐ Advanced | Pair Distance, Count Pairs, Boats to Save People, KSum Combos |
| 07 | [Two Pointer CF Problems](07_Two_Pointer_Codeforces_Problems/) | ⭐⭐⭐⭐⭐ All | CF 800→2400+ Curated Two Pointer Problems |

### Section B: Fixed Size Sliding Window

| # | Module | Level | Key Concepts |
|---|--------|-------|-------------|
| 08 | [Fixed Window Fundamentals](08_Fixed_Window_Fundamentals/) | ⭐ Beginner | Template, Max/Min Sum, First Negative, Count Distinct |
| 09 | [Fixed Window + Deque & Hashing](09_Fixed_Window_With_Deque_And_Hashing/) | ⭐⭐⭐ Advanced | Sliding Max/Min (Deque), Anagram, Permutation in String |
| 10 | [Fixed Window CF Problems](10_Fixed_Window_Codeforces_Problems/) | ⭐⭐⭐⭐⭐ All | CF 800→2400+ Curated Fixed Window Problems |

### Section C: Variable Size Sliding Window

| # | Module | Level | Key Concepts |
|---|--------|-------|-------------|
| 11 | [Variable Window Fundamentals](11_Variable_Window_Fundamentals/) | ⭐⭐ Intermediate | Expand-Shrink, Longest/Shortest Subarray, Max Consecutive Ones |
| 12 | [Distinct & Frequency Patterns](12_Variable_Window_Distinct_And_Frequency/) | ⭐⭐⭐ Advanced | AtMostK Distinct, ExactK Trick, Fruit Baskets, Binary Subarrays |
| 13 | [Advanced Variable Window](13_Variable_Window_Advanced/) | ⭐⭐⭐⭐ Expert | Min Window Substring, Sliding Median, Bounded Max, Count Nice |
| 14 | [Variable Window CF Problems](14_Variable_Window_Codeforces_Problems/) | ⭐⭐⭐⭐⭐ All | CF 800→2400+ Curated Variable Window Problems |

---

## 📊 Difficulty Progression

```
Problems:  Easy ──────► Medium ──────► Hard ──────► Expert ──────► GM
CF Rating: 800-1200     1200-1600      1600-2000    2000-2400      2400+
LC Level:  Easy          Medium         Hard         Hard+          —
Module:    01,08         02-05,11       06,09,12     07,10,13       07,10,14
```

---

## 🔥 Master Problem Cheat Sheet

See **[00_Two_Pointer_Sliding_Window_Master_CheatSheet.cpp](00_Two_Pointer_Sliding_Window_Master_CheatSheet.cpp)** for all 200+ curated problems organized by pattern with links, difficulty, and key technique.

---

## 💡 How to Study This Module

1. **Read theory files first** (numbered `.cpp` files with detailed comments)
2. **Understand the template** — memorize the core patterns
3. **Solve problems in order** — Easy → Medium → Hard → Expert → GM
4. **For Codeforces**: Sort by rating and solve upward
5. **Pattern Recognition**: After solving 10+ problems per pattern, you'll auto-detect which technique to use

---

## 🎯 Pattern Recognition Quick Guide

| If the problem says... | Think about... | Module |
|------------------------|----------------|--------|
| "Find pair with sum/difference" | Two Pointer (Opposite Direction) | 02 |
| "3Sum / 4Sum / KSum" | Nested Two Pointer | 02 |
| "Trapping rain water" | Two Pointer + Prefix Max | 02 |
| "Is palindrome / make palindrome" | Two Pointer from ends | 03 |
| "Detect cycle in linked list" | Fast & Slow pointer | 04 |
| "Find duplicate number" | Floyd's cycle | 04 |
| "Merge sorted arrays" | Same direction two pointer | 05 |
| "Sort 0s, 1s, 2s" | Dutch National Flag | 05 |
| "Fixed size K subarray" | Fixed Sliding Window | 08 |
| "Maximum in every window of K" | Deque-based Sliding Window | 09 |
| "Anagram / permutation check in string" | Fixed Window + Hashing | 09 |
| "Longest subarray/substring with condition" | Variable Sliding Window | 11-12 |
| "Shortest subarray with sum ≥ K" | Variable Sliding Window | 11 |
| "At most K distinct elements" | Variable Window + HashMap | 12 |
| "Exactly K → use atMost(K) - atMost(K-1)" | Variable Window Trick | 12 |
| "Minimum window containing all chars" | Variable Window (shrink) | 13 |

---

## 📈 Total Problems: 200+

- **LeetCode:** 80+ problems
- **Codeforces:** 80+ problems (800 → 2400+)
- **CSES:** 15+ problems
- **GFG:** 15+ problems
- **CodeChef:** 10+ problems

---

> *"Two Pointer and Sliding Window are not just techniques — they are a way of thinking. Master the templates, and every array/string problem becomes solvable."*
> — Sarvan Yaduvanshi

