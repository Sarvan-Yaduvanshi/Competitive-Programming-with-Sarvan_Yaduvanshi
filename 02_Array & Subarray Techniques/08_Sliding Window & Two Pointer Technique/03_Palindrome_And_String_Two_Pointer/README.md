# Module 03: Palindrome & String Two Pointer

> **Level:** ⭐⭐ Intermediate  
> **Prerequisites:** Module 01

## Concepts Covered

| # | File | Topic | Difficulty |
|---|------|-------|-----------|
| 1 | `01_Valid_Palindrome.cpp` | LC 125 — Two pointer + isalnum | Easy |
| 2 | `02_Valid_Palindrome_II.cpp` | LC 680 — Skip at most 1 char | Easy |
| 3 | `03_Valid_Palindrome_III.cpp` | LC 1216 — Remove at most K (DP bridge) | Hard |
| 4 | `04_Longest_Palindromic_Substring.cpp` | LC 5, 647 — Expand from center, count all palindromes | Medium |
| 5 | `05_Palindrome_Linked_List_And_More.cpp` | LC 234, 2108, 1332, 1793 — LL palindrome, Max Score expand | Easy-Medium |

## Key Takeaways
- Palindrome checking = opposite direction two pointer from both ends
- "Can remove at most 1" = try skipping left OR right on mismatch
- Expand from center = O(N²) technique for finding all palindromes
- For linked lists: find middle → reverse second half → compare
- LC 1793 (Max Score Good Subarray) = expand outward from center greedily

