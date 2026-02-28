# Module 05: Sorted Array Merge, Partition, Reverse Technique & Misc Patterns

> **Level:** ⭐⭐ Intermediate  
> **Prerequisites:** Module 01

## Concepts Covered

| # | File | Topic | Difficulty |
|---|------|-------|-----------|
| 1 | `01_Sort_Colors_Dutch_National_Flag.cpp` | LC 75, 905, 2161 — 3-way partition, parity sort | Medium |
| 2 | `02_Remove_Duplicates_And_Compaction.cpp` | LC 26, 80, 27, 283, GFG Merge — Reader-writer compaction | Easy-Medium |
| 3 | `03_Merge_Intersection_Intervals.cpp` | LC 88, 349, 350, 922, 986, GFG — Merge, Intersection, Interval Intersections | Easy-Medium |
| 4 | `04_Next_Permutation_Rotate_Reverse.cpp` | LC 31, 189, 151 — Reverse technique, Next Permutation, Rotate Array | Medium |
| 5 | `05_String_Compression_Backspace_Mountain.cpp` | LC 443, 844, 845 — String Compression, Backspace Compare, Longest Mountain | Easy-Medium |

## Key Takeaways
- **Dutch National Flag (LC 75):** 3 pointers (low, mid, high) partition into 3 groups
- **Remove Duplicates:** Reader-writer pattern, writer only advances for new values
- **Merge Sorted Array (LC 88):** Merge from the BACK to avoid overwriting
- **Intersection:** Two pointers on sorted arrays, advance the smaller
- **Interval Intersections (LC 986):** `[max(starts), min(ends)]`, advance earlier-ending interval
- **Next Permutation (LC 31):** Find dip → find swap partner → reverse suffix
- **Rotate Array (LC 189):** 3 reverses technique
- **String Compression (LC 443):** Reader-writer pattern on characters
- **Backspace Compare (LC 844):** Reverse two pointer (scan from back)
- **Longest Mountain (LC 845):** Expand from peak (like palindromic expand)
