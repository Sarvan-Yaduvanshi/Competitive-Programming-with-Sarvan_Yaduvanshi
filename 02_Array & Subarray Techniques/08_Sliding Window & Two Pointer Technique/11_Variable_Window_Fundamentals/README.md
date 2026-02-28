# Module 11: Variable Size Sliding Window Fundamentals

> **Level:** ⭐⭐ Intermediate  
> **Prerequisites:** Module 08 (Fixed Window)

## Concepts Covered

| # | File | Topic | Difficulty |
|---|------|-------|-----------|
| 1 | `01_Variable_Window_Template.cpp` | Expand-Shrink template, longest vs shortest patterns | Intermediate |
| 2 | `02_Longest_Subarray_Problems.cpp` | LC 1004, 1493, 487, 2024, 1658 — Max consecutive / longest | Medium |
| 3 | `03_Shortest_Subarray_Problems.cpp` | LC 209, 713 — Minimum size subarray with sum | Medium |

## Key Takeaways
- **Variable window:** size changes dynamically based on condition
- **Longest pattern:** Expand right, shrink left ONLY when condition violated
- **Shortest pattern:** Expand right until condition met, then shrink left to minimize
- **Reverse thinking (LC 1658):** Find longest middle subarray → answer = N - length
- **Product window (LC 713):** Use product instead of sum, divide on shrink

