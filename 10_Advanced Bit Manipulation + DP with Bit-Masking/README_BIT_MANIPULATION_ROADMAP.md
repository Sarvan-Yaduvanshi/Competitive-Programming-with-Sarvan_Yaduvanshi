# 🧮 Advanced Bit Manipulation + DP with Bit-Masking — Complete Roadmap

### Author: **Sarvan Yaduvanshi**
### Level: **Zero → Grandmaster**

---

## 📋 Table of Contents

| # | Folder | Topics | Difficulty |
|---|--------|--------|------------|
| 01 | `01_Number_System_And_Representation` | Decimal, Binary, Octal, Hex, Conversions, 2's Complement, IEEE 754, Endianness | ⭐ Foundation |
| 02 | `02_Bit_Basics_And_Operators` | AND, OR, XOR, NOT, Shifts, Check/Set/Clear/Toggle bits, Popcount, Parity | ⭐ Foundation |
| 03 | `03_Common_Bit_Tricks_And_Patterns` | XOR tricks, Swap, Single number, Missing number, Fast power, Brian Kernighan | ⭐⭐ Intermediate |
| 04 | `04_Bitmask_Basics` | Subset ↔ Bitmask, CRUD ops, Submask/Superset iteration, Mask compression | ⭐⭐ Intermediate |
| 05 | `05_Subset_Enumeration_And_Combinations` | All subsets, Gosper's Hack, Gray Code, Meet in the Middle | ⭐⭐⭐ Advanced |
| 06 | `06_Bitwise_Array_Techniques` | Prefix XOR, Subarray XOR=K, OR/AND monotonicity, Contribution per bit | ⭐⭐⭐ Advanced |
| 07 | `07_Bitmask_With_Sliding_Window` | Parity mask, Palindrome permutation, Awesome substring, Window AND/OR | ⭐⭐⭐ Advanced |
| 08 | `08_Bitmask_DP_Fundamentals` | DP over subsets, TSP, Assignment, Perfect Matching, Hamiltonian Path | ⭐⭐⭐⭐ Expert |
| 09 | `09_Advanced_Bitmask_DP` | SOS DP, Subset Convolution, Inclusion-Exclusion, Steiner Tree, Broken Profile | ⭐⭐⭐⭐⭐ Grandmaster |
| 10 | `10_XOR_Basis_And_Linear_Algebra` | XOR Basis, Gaussian Elimination GF(2), Max XOR subset, Linear Independence | ⭐⭐⭐⭐ Expert |
| 11 | `11_Bitset_And_Optimization_Tricks` | bitset<N>, Bitset DP, __int128, Popcount optimizations, Bit-parallel | ⭐⭐⭐⭐ Expert |
| 12 | `12_Bitwise_Transforms_And_Theory` | Walsh-Hadamard, XOR/AND/OR Convolution, Zeta/Möbius Transform | ⭐⭐⭐⭐⭐ Grandmaster |

---

## 🔥 Complexity Cheat Sheet

| Operation | Formula | Time |
|-----------|---------|------|
| Check i-th bit | `(n >> i) & 1` | O(1) |
| Set i-th bit | `n \| (1 << i)` | O(1) |
| Clear i-th bit | `n & ~(1 << i)` | O(1) |
| Toggle i-th bit | `n ^ (1 << i)` | O(1) |
| Count set bits | `__builtin_popcount(n)` | O(1) |
| Lowest set bit | `n & (-n)` | O(1) |
| Remove lowest set bit | `n & (n - 1)` | O(1) |
| All subsets of n elements | `for mask 0..2^n-1` | O(2^n) |
| All submasks of mask | `for s=m; s>0; s=(s-1)&m` | O(3^n) total |
| SOS DP | Sum over Subsets | O(n · 2^n) |
| TSP DP | `dp[mask][i]` | O(2^n · n²) |
| Subset Convolution | Ranked Möbius | O(n² · 2^n) |
| Walsh-Hadamard | FWT | O(n · 2^n) |

---

## 📚 Study Order

1. **Weeks 1–2**: Folders 01–03 (Number systems + Bit basics + Tricks)
2. **Weeks 3–4**: Folders 04–05 (Bitmask basics + Subset enumeration)
3. **Weeks 5–6**: Folders 06–07 (Array techniques + Sliding window)
4. **Weeks 7–9**: Folder 08 (Bitmask DP fundamentals — practice heavily!)
5. **Weeks 10–12**: Folders 09–10 (Advanced DP + XOR basis)
6. **Weeks 13–14**: Folders 11–12 (Optimization + Transforms)

---

## 🏆 Key Problem Sources

- **LeetCode**: Bit manipulation tag (50+ problems)
- **Codeforces**: Bitmasks tag, Edu rounds
- **CSES**: Introductory problems, Advanced techniques
- **AtCoder**: ABC/ARC bitmask problems
- **SPOJ**: Classical bitmask DP problems

---

> **Note**: Legacy folders (`Basic Problem Solving/`, `Binary Number System/`, `BitWise Operators/`) contain older implementations. The new numbered folders above provide the complete, structured course.

