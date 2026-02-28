# Module 06: Advanced Two Pointer Techniques (BS, Circular, Prefix-Suffix, Meet-in-Middle, Sweep, Mo's)

> **Level:** ⭐⭐⭐ Advanced → ⭐⭐⭐⭐⭐ GM  
> **Prerequisites:** Modules 01-05, Binary Search, Sorting

## Concepts Covered

| # | File | Topic | Difficulty |
|---|------|-------|-----------|
| 1 | `01_Kth_Smallest_Pair_Distance.cpp` | LC 719, 2824, 532, 1679, 1855 — BS on answer + 2Ptr count | Easy-Hard |
| 2 | `02_K_Closest_Subsequences_Spells.cpp` | LC 658, 1498, 2300, 826, CSES 2428 — BS+2Ptr combos | Medium-Hard |
| 3 | `03_Circular_Array_Two_Pointer.cpp` | LC 918, 2134, 503 — Circular max sum, circular window, 2N trick | Medium-Hard |
| 4 | `04_Prefix_Suffix_Balancing.cpp` | LC 238, 2270, 1525, 2256, 334 — Prefix-suffix split/balance | Easy-Hard |
| 5 | `05_Advanced_Pair_Counting_Range.cpp` | LC 2563, 327, CF 1538C, 1324D — Count pairs in range [L,R] | Medium-Hard |
| 6 | `06_Meet_In_The_Middle.cpp` | LC 1755, CF 888E — Split + merge with 2Ptr, N≤40 | Hard-Expert |
| 7 | `07_Sweep_Line_Geometry_Two_Pointer.cpp` | LC 253, 1288, CF 1462F, Closest Pair — Sweep + 2Ptr | Hard-GM |
| 8 | `08_Mos_Algorithm.cpp` | CF 86D, 617E, SPOJ DQUERY — Offline queries with pointer movement | Expert-GM |

## Key Takeaways
- **BS on Answer + 2Ptr:** Binary search the answer, validate with two pointer count
- **Circular Arrays:** `totalSum - minSubarray` trick, or double-the-array / modular indexing
- **Prefix-Suffix Balance:** Compute prefix from left + suffix from right, find optimal split
- **Range Pair Counting:** `countInRange(L,R) = countAtMost(R) - countAtMost(L-1)` — golden trick
- **Meet in the Middle:** Split N≤40 into halves, enumerate 2^(N/2) each, combine with 2Ptr/BS
- **Sweep Line + 2Ptr:** Process sorted events, maintain active window with two pointers
- **Mo's Algorithm:** Offline range queries, curL/curR pointers move O(N√N) total
- **Mo's IS two pointer:** curL and curR slide across the array — it's conceptually a 2Ptr technique
