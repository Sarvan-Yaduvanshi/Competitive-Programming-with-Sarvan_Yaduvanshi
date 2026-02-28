# Module 08: Fixed Size Sliding Window Fundamentals

> **Level:** ⭐ Beginner → ⭐⭐ Intermediate  
> **Prerequisites:** Basic arrays, prefix sums

## Concepts Covered

| # | File | Topic | Difficulty |
|---|------|-------|-----------|
| 1 | `01_Fixed_Window_Template.cpp` | Template, intuition, max/min sum, edge cases | Beginner |
| 2 | `02_Window_Problems_Collection.cpp` | First negative, Count distinct, Max vowels, Grumpy, LC 1456/1343/2090/2379/2461 | Easy-Medium |
| 3 | `03_Bit_Manipulation_Fixed_Window.cpp` | XOR/OR/AND of window, Parity mask, Palindrome permutation, LC 1461 | Medium-Hard |
| 4 | `04_Prefix_Sum_Hybrid_Contribution.cpp` | Prefix sum window, Contribution trick, Weighted window, LC 1588/1423 | Medium |
| 5 | `05_Circular_Fixed_Window.cpp` | Circular windows, Double array trick, Modular indexing, LC 2134/1652 | Medium-Hard |
| 6 | `06_Fixed_Window_Greedy.cpp` | Group 1s, Max consecutive with K flips, LC 1151/2009/2024/2516 | Medium |

## Key Takeaways
- **Fixed window**: size K. Add right, remove left, O(1) per slide
- **XOR removable** (a^a=0), **OR/AND need bit frequency** count[0..31]
- **Parity mask**: flip bit on add/remove → palindrome permutation = at most 1 bit set
- **Contribution trick**: element i appears in min(i+1, K, N-i, N-K+1) windows
- **Circular**: modular indexing `arr[(i+j)%N]` or double-the-array trick
- **Max cards from ends** (LC 1423) = prefix + suffix window
