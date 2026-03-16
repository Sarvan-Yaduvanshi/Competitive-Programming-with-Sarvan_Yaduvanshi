# 🎲 04 — Combinatorics Problem Solving

> Counting problems are the backbone of competitive programming. Master these patterns and you can solve 80% of combinatorics problems in contests.

---

## 📚 Topics Covered

| # | Topic | Key Idea |
|---|-------|----------|
| 1 | Permutations & Combinations | nPr, nCr, with repetition |
| 2 | Stars and Bars | Distributing identical items into distinct bins |
| 3 | Derangements | Permutations where no element is in its original position |
| 4 | Catalan Numbers | Binary trees, balanced parentheses, non-crossing partitions |
| 5 | Counting Paths | Grid paths, lattice paths with obstacles |
| 6 | Counting Sequences | Counting arrays/strings with certain properties |
| 7 | **Inclusion-Exclusion Principle** | |A∪B| = |A|+|B|-|A∩B|, sieve counting |
| 8 | Burnside's Lemma | Count distinct objects under symmetry/rotation |
| 9 | Stirling Numbers | Partition n elements into k non-empty subsets |

---

## 1️⃣ Permutations & Combinations

### Formulas
| Type | Formula | Meaning |
|------|---------|---------|
| nPr | n! / (n-r)! | Ordered arrangements of r from n |
| nCr | n! / (r! × (n-r)!) | Unordered selections of r from n |
| With repetition (P) | n^r | Each of r positions can be any of n items |
| With repetition (C) | C(n+r-1, r) | Stars and Bars |
| Multiset permutation | n! / (k₁! × k₂! × ... × kₘ!) | Arrange with duplicates |

### Key Properties of nCr
```
C(n, 0) = C(n, n) = 1
C(n, r) = C(n, n-r)                    (symmetry)
C(n, r) = C(n-1, r-1) + C(n-1, r)     (Pascal's identity)
Σ C(n, k) for k=0..n = 2^n             (sum of row)
C(n, r) * C(r, k) = C(n, k) * C(n-k, r-k)  (Vandermonde-like)
```

### Pascal's Triangle (DP for nCr)
```cpp
// Build Pascal's triangle up to row n
vvec<i64> pascal(n + 1, vec<i64>(n + 1, 0));
pascal[0][0] = 1;
for (int i = 1; i <= n; i++) {
    pascal[i][0] = 1;
    for (int j = 1; j <= i; j++)
        pascal[i][j] = (pascal[i-1][j-1] + pascal[i-1][j]) % MOD;
}
```

---

## 2️⃣ Stars and Bars

### The Problem
> Distribute **n identical** items into **k distinct** bins.

### Formulas
| Constraint | Formula |
|-----------|---------|
| Each bin ≥ 0 items | C(n + k - 1, k - 1) |
| Each bin ≥ 1 item | C(n - 1, k - 1) |
| Each bin ≥ aᵢ items | Substitute n' = n - Σaᵢ, then C(n' + k - 1, k - 1) |

### Example
Distribute 10 identical balls into 3 distinct boxes, each box ≥ 0:
- Answer = C(10 + 3 - 1, 3 - 1) = C(12, 2) = 66

### CP Application
> "Number of solutions to x₁ + x₂ + ... + xₖ = n where xᵢ ≥ 0" → Stars and Bars

---

## 3️⃣ Derangements

### Definition
> A **derangement** is a permutation where **no element** appears in its original position.

### Formula
```
D(n) = (n-1) × (D(n-1) + D(n-2))
D(0) = 1, D(1) = 0
```

### Closed Form
```
D(n) = n! × Σ_{k=0}^{n} (-1)^k / k!
     ≈ n! / e  (rounded to nearest integer)
```

### First Values
```
D(0)=1, D(1)=0, D(2)=1, D(3)=2, D(4)=9, D(5)=44, D(6)=265
```

### CP Application
- "How many ways can n people get someone else's hat?"
- Inclusion-exclusion counting
- Probability that no one gets their own item = D(n)/n! ≈ 1/e ≈ 0.368

---

## 4️⃣ Catalan Numbers

### Definition
```
C(n) = C(2n, n) / (n + 1)
C(n) = Σ_{i=0}^{n-1} C(i) × C(n-1-i)     (convolution recurrence)
```

### First Values
```
C(0)=1, C(1)=1, C(2)=2, C(3)=5, C(4)=14, C(5)=42, C(6)=132
```

### What Catalan Numbers Count
| Problem | Count |
|---------|-------|
| Balanced parentheses with n pairs | C(n) |
| Full binary trees with n+1 leaves | C(n) |
| Triangulations of (n+2)-gon | C(n) |
| Monotonic lattice paths from (0,0) to (n,n) not crossing diagonal | C(n) |
| Stack-sortable permutations of length n | C(n) |
| Non-crossing partitions of n elements | C(n) |

---

## 5️⃣ Counting Paths on a Grid

### Basic Grid Path
From (0,0) to (m,n) using only right and down moves:
```
paths = C(m + n, m) = C(m + n, n)
```

### With Obstacles (Inclusion-Exclusion)
- Count paths avoiding forbidden cells
- Use inclusion-exclusion or DP

### Lindström-Gessel-Viennot Lemma
> Count tuples of non-intersecting lattice paths = determinant of a path-count matrix

---

## 6️⃣ Counting Sequences

### Common Patterns
1. **Binary strings of length n with no two consecutive 1s** → Fibonacci(n+2)
2. **Sequences with fixed sum** → Stars and Bars
3. **Sequences with elements in range** → Inclusion-Exclusion
4. **Circular arrangements** → (n-1)! or use Burnside's lemma

---

## 7️⃣ Inclusion-Exclusion Principle (CRITICAL for CP!)

### Statement
> |A₁ ∪ A₂ ∪ ... ∪ Aₙ| = Σ|Aᵢ| − Σ|Aᵢ ∩ Aⱼ| + Σ|Aᵢ ∩ Aⱼ ∩ Aₖ| − ... + (−1)ⁿ⁺¹|A₁ ∩ ... ∩ Aₙ|

### Complementary Form (More Common in CP)
> Count elements NOT in any set = Total − |A₁ ∪ A₂ ∪ ... ∪ Aₙ|

### Classic Applications

**Count integers in [1,n] divisible by at least one of p₁, p₂, ..., pₖ:**
```
Answer = Σ⌊n/pᵢ⌋ − Σ⌊n/(pᵢpⱼ)⌋ + Σ⌊n/(pᵢpⱼpₖ)⌋ − ...
```

**Count integers in [1,n] coprime to m:**
```
Factorize m = p₁^a₁ × p₂^a₂ × ... × pₖ^aₖ
Use IE over the k prime factors
= Euler's totient function relationship!
```

**Stars and Bars with UPPER BOUNDS (xᵢ ≤ bᵢ):**
```
Total without upper bounds − (overcounted subsets via IE)
```

### Implementation Pattern (Bitmask IE)
```cpp
// Count integers in [1,n] NOT divisible by any prime in primes[]
i64 inclusionExclusion(i64 n, vec<i64>& primes) {
    int k = primes.size();
    i64 result = 0;
    for (int mask = 1; mask < (1 << k); mask++) {
        i64 prod = 1;
        int bits = __builtin_popcount(mask);
        for (int i = 0; i < k; i++) {
            if (mask & (1 << i)) {
                prod *= primes[i];
                if (prod > n) break;
            }
        }
        if (bits % 2 == 1) result += n / prod;
        else result -= n / prod;
    }
    return n - result;  // coprime count
}
```

### CP Tips
- IE over prime factors → at most ~15 primes (since 2×3×5×...×43 > 10¹⁸)
- Bitmask iteration: O(2ᵏ) where k = number of sets/primes
- **Derangements ARE inclusion-exclusion** on fixed points

---

## 8️⃣ Burnside's Lemma (Counting Under Symmetry)

### Statement
> Number of distinct objects under group G = (1/|G|) × Σ_{g∈G} |Fix(g)|

Where Fix(g) = number of objects unchanged by symmetry operation g.

### Classic Application: Counting Distinct Necklaces
**n beads, k colors, rotational equivalence:**
```
Answer = (1/n) × Σ_{d|n} φ(n/d) × k^d
```
Where φ = Euler's totient function.

### Example
3 beads, 2 colors → (1/3)(2³ + 2¹ + 2¹) = (8+2+2)/3 = 4 necklaces

---

## 9️⃣ Stirling Numbers

### Stirling Numbers of the Second Kind S(n, k)
> Number of ways to partition n elements into exactly k non-empty subsets.

**Recurrence:**
```
S(n, k) = k × S(n-1, k) + S(n-1, k-1)
S(n, 1) = S(n, n) = 1
```

### Connection to Other Concepts
- S(n,k) × k! = number of onto functions from n elements to k elements
- Bell number B(n) = Σ S(n,k) for k=1..n = total partitions
- Used in combinatorial identities and polynomial conversion

---

## 🔗 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [Unique Paths](https://leetcode.com/problems/unique-paths/) | LeetCode 62 | Grid path counting |
| [Unique Paths II](https://leetcode.com/problems/unique-paths-ii/) | LeetCode 63 | With obstacles |
| [Generate Parentheses](https://leetcode.com/problems/generate-parentheses/) | LeetCode 22 | Catalan |
| [Different Ways to Add Parentheses](https://leetcode.com/problems/different-ways-to-add-parentheses/) | LeetCode 241 | Catalan-like |
| [Distributing Apples](https://cses.fi/problemset/task/1716) | CSES | Stars and Bars |
| [Bracket Sequences I](https://cses.fi/problemset/task/2064) | CSES | Catalan |
| [Counting Necklaces](https://cses.fi/problemset/task/2209) | CSES | Burnside |
| [Christmas Party](https://cses.fi/problemset/task/1717) | CSES | Derangements |
| [Binomial Coefficients](https://cses.fi/problemset/task/1079) | CSES | nCr mod p |
| [Inclusion-Exclusion](https://cses.fi/problemset/task/2185) | CSES | Inclusion-Exclusion |
| [Count Primes](https://leetcode.com/problems/count-primes/) | LeetCode 204 | Sieve / IE |
| [Ugly Number III](https://leetcode.com/problems/ugly-number-iii/) | LeetCode 1201 | Inclusion-Exclusion + Binary Search |
| [K-th Smallest in Lexicographical Order](https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/) | LeetCode 440 | Counting |

---

*Next: [05 — Probability Problems →](../05_Probability_Problems/)*

