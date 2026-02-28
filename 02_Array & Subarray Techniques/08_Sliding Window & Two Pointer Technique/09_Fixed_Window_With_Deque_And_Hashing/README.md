# Module 09: Fixed Window + Deque, Hashing, Rolling Hash, GCD, 2D, Advanced Patterns

> **Level:** ⭐⭐⭐ Advanced → ⭐⭐⭐⭐⭐ GM  
> **Prerequisites:** Module 08, Deque, HashMap, Binary Search

## Concepts Covered

| # | File | Topic | Difficulty |
|---|------|-------|-----------|
| 1 | `01_Sliding_Window_Maximum_Deque.cpp` | LC 239, 1438, 480 — Monotonic Deque, Two Deques, Window Median | Medium-Hard |
| 2 | `02_Anagram_Permutation_In_String.cpp` | LC 567, 438, 187, 1876 — Frequency matching, DNA sequences | Medium |
| 3 | `03_Fixed_Window_GCD_LCM.cpp` | GCD/LCM of every K-window, Sparse Table, Two-Stack trick, CF 1548B | Medium-Hard |
| 4 | `04_Rolling_Hash_Rabin_Karp.cpp` | Rabin-Karp, LC 187/1044/28, Double hashing, Repeated substrings | Medium-Hard |
| 5 | `05_2D_Fixed_Sliding_Window.cpp` | 2D prefix sum, k×k max/sum, LC 363/304/1074, 2D monotonic deque | Hard |
| 6 | `06_Advanced_Competitive_Patterns.cpp` | LC 2444/2762/992/1248, Contribution trick, BS+window, "Exactly K" pattern | Hard-GM |

## Key Takeaways
- **Monotonic Deque:** Stores indices, O(1) amortized max/min. Pop smaller from back, expired from front
- **GCD not removable:** Use Sparse Table O(1) query, or Two-Stack trick (amortized O(1))
- **Rolling Hash:** `hash = (hash - s[left]*B^(k-1)) * B + s[right+1]` → O(1) per slide
- **Double Hash:** Two (base, mod) pairs → near-zero collision probability
- **2D Window Max:** Horizontal deque pass + Vertical deque pass → O(M*N) total
- **"Exactly K" = AtMost(K) - AtMost(K-1)** — the most important counting pattern!
- **Contribution per index:** Element i appears in min(i+1, K, N-i, N-K+1) windows
- **Binary Search on K:** Parametric search for minimum window size satisfying a property
