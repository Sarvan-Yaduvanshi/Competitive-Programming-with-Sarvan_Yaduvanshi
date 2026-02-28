# Module 13: Advanced Variable Window — Complete Coverage (Zero to GM)

> **Level:** ⭐⭐⭐ Advanced → ⭐⭐⭐⭐⭐ GM  
> **Prerequisites:** Modules 11-12, Binary Search, Bit Manipulation

## Concepts Covered

| # | File | Topic | Difficulty |
|---|------|-------|-----------|
| 1 | `01_Minimum_Window_Substring.cpp` | LC 76 — Shrink + frequency matching | Hard |
| 2 | `02_Longest_Repeating_And_No_Repeating.cpp` | LC 424, 3, 395 — Classic variable window | Medium |
| 3 | `03_Advanced_Window_Problems.cpp` | LC 862, 795, 2302, 2009 — Expert-level | Hard |
| 4 | `04_Bit_Manipulation_Variable_Window.cpp` | XOR=K, AND≥K, OR≥K, Parity mask, LC 1371/1542/1915/2401 | Hard-Expert |
| 5 | `05_Monotonic_Queue_Variable_Window.cpp` | max-min≤K, Two deques, LC 1438/2762, CF 602B/514D | Medium-Hard |
| 6 | `06_Prefix_BinarySearch_Hybrid.cpp` | LC 862 (negatives!), Parametric search, BS on answer | Hard-Expert |
| 7 | `07_Multiset_Heap_Window.cpp` | Sliding Median, K-th smallest, Two heaps, CSES 1077/1076 | Hard-Expert |
| 8 | `08_Contribution_Counting_Variable.cpp` | Count valid subarrays, AtMost trick, LC 713/992/2537/2444 | Medium-Hard |
| 9 | `09_Sorted_Array_Value_Space_Window.cpp` | Sort+window on values, LC 1838/2779/1498 | Medium-Hard |
| 10 | `10_Bitmask_DP_Window.cpp` | Mask transitions, Cover all chars, Small alphabet, LC 1358 | Hard-Expert |
| 11 | `11_Circular_Variable_Window.cpp` | Circular + variable, Double array + shrink, LC 918/1658 | Medium-Hard |
| 12 | `12_Modular_Arithmetic_Window.cpp` | Sum%K, Remainder pairs, LC 974/523/1590/1497, CSES 1662 | Medium-Hard |

## Key Takeaways
- **XOR is NOT monotone** → use prefix XOR + hashmap (not sliding window!)
- **AND is monotone decreasing** → window AND ≥ K is shrinkable (bit frequency array)
- **OR is monotone increasing** → shortest window OR ≥ K via shrinking
- **Parity mask:** XOR bit per character → palindrome permutation iff ≤ 1 bit set
- **Two deques for variable max-min ≤ K:** maxDeque (decreasing) + minDeque (increasing)
- **Negative numbers break normal window!** → Prefix + monotonic deque (LC 862)
- **Multiset/Heap for median/k-th:** Two balanced halves, O(log K) per operation
- **"Exactly K" = AtMost(K) - AtMost(K-1):** The single most important counting trick
- **Contribution per index:** Element i in (i+1)*(n-i) subarrays total
- **Sort + window on VALUES:** Not contiguous subarrays, but sorted subsequence window
- **Circular variable:** Double array + restrict length ≤ N, or complement trick
- **Mod arithmetic:** prefix[r] % K == prefix[l] % K → subarray sum divisible by K
