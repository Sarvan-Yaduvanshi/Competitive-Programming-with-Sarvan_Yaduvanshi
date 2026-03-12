# 📘 Level 11 — Combinatorics

> **Counting: nCr, nPr, Catalan, Lucas, Stars & Bars.** The most frequently tested topic in CP.  
> _Reference: [cp-algorithms.com — Combinatorics](https://cp-algorithms.com/combinatorics/binomial-coefficients.html)_

---

## 1️⃣ Binomial Coefficients

### Definition
$$\binom{n}{r} = \frac{n!}{r!(n-r)!}$$

Number of ways to choose $r$ items from $n$ items.

### Pascal's Identity
$$\binom{n}{r} = \binom{n-1}{r-1} + \binom{n-1}{r}$$

**Proof:** The $n$-th item is either chosen (pick $r-1$ from remaining $n-1$) or not ($r$ from $n-1$). ∎

### Properties
1. $\binom{n}{0} = \binom{n}{n} = 1$
2. $\binom{n}{r} = \binom{n}{n-r}$ (symmetry)
3. $\sum_{r=0}^{n} \binom{n}{r} = 2^n$
4. $\sum_{r=0}^{n} (-1)^r \binom{n}{r} = 0$
5. $\binom{n}{r} \binom{r}{k} = \binom{n}{k} \binom{n-k}{r-k}$ (Vandermonde-like)

### Computing nCr mod p (prime p)
1. **Precompute factorials and inverse factorials** — O(n) preprocess, O(1) query
2. **Lucas Theorem** — when p is small and n is large

---

## 2️⃣ Lucas Theorem

### Statement
For prime $p$ and $n, r$ written in base $p$ as $n = n_k n_{k-1} \ldots n_0$ and $r = r_k r_{k-1} \ldots r_0$:

$$\binom{n}{r} \equiv \prod_{i=0}^{k} \binom{n_i}{r_i} \pmod{p}$$

### Dry Run: C(10, 3) mod 3

$10 = 101_3$, $3 = 010_3$

$\binom{10}{3} \equiv \binom{1}{0} \times \binom{0}{1} \times \binom{1}{0} = 1 \times 0 \times 1 = 0 \pmod{3}$

Check: $\binom{10}{3} = 120 = 40 \times 3 \equiv 0 \pmod{3}$ ✓

---

## 3️⃣ Catalan Numbers

$$C_n = \frac{1}{n+1}\binom{2n}{n} = \binom{2n}{n} - \binom{2n}{n+1}$$

### First few: 1, 1, 2, 5, 14, 42, 132, 429, 1430, ...

### Applications
- Number of valid parenthesizations of $n$ pairs
- Number of full binary trees with $n+1$ leaves
- Number of paths from $(0,0)$ to $(n,n)$ that don't cross the diagonal
- Number of triangulations of a polygon with $n+2$ sides

### Proof (Reflection Principle)
> Paths from $(0,0)$ to $(2n, 0)$ with steps $(+1, +1)$ and $(+1, -1)$ that never go below $y=0$:  
> Total paths = $\binom{2n}{n}$ (choose $n$ up-steps out of $2n$)  
> Bad paths (touch $y=-1$): reflect at first touch → bijection with paths to $(2n, -2)$ = $\binom{2n}{n-1}$  
> Good paths = $\binom{2n}{n} - \binom{2n}{n-1} = \frac{1}{n+1}\binom{2n}{n}$ ∎

---

## 4️⃣ Stars and Bars

Number of ways to put $n$ identical balls into $k$ distinct boxes:

$$\binom{n + k - 1}{k - 1}$$

With each box having at least 1: $\binom{n - 1}{k - 1}$

---

## 5️⃣ Stirling Numbers

**First kind** $\left[\begin{smallmatrix}n\\k\end{smallmatrix}\right]$: Permutations of $n$ with exactly $k$ cycles.

**Second kind** $\left\{\begin{smallmatrix}n\\k\end{smallmatrix}\right\}$: Ways to partition $n$ elements into $k$ non-empty subsets.

---

## 6️⃣ Burnside's Lemma (Counting Under Symmetry)

### Theorem
$$|\text{orbits}| = \frac{1}{|G|} \sum_{g \in G} |\text{Fix}(g)|$$

Count distinct objects under group of symmetries $G$.

### Necklace Counting (n beads, k colors, rotations only)
$$\text{Answer} = \frac{1}{n} \sum_{d \mid n} \phi(n/d) \cdot k^d$$

### Dry Run: n=4 beads, k=2 colors
- d=1: φ(4)×2¹ = 2×2 = 4
- d=2: φ(2)×2² = 1×4 = 4
- d=4: φ(1)×2⁴ = 1×16 = 16
- Total = 24/4 = **6 necklaces** ✓

---

## 📁 Files in This Section

| File | Description |
|------|-------------|
| [01_nCr_Modular.cpp](01_nCr_Modular.cpp) | Factorial + inverse precomputation |
| [02_Pascals_Triangle.cpp](02_Pascals_Triangle.cpp) | Pascal's triangle + properties |
| [03_Lucas_Theorem.cpp](03_Lucas_Theorem.cpp) | nCr for large n mod small p |
| [04_Catalan_And_Counting.cpp](04_Catalan_And_Counting.cpp) | Catalan, Stars & Bars, Stirling |
| [05_Burnside_Lemma.cpp](05_Burnside_Lemma.cpp) | Burnside's lemma, necklaces, grids |

---

## 🎯 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [Unique Paths](https://leetcode.com/problems/unique-paths/) | LC 62 | nCr |
| [Unique Binary Search Trees](https://leetcode.com/problems/unique-binary-search-trees/) | LC 96 | Catalan |
| [Pascal's Triangle](https://leetcode.com/problems/pascals-triangle/) | LC 118 | Pascal |
| [Binomial Coefficients](https://codeforces.com/problemset/problem/785/D) | CF 785D | nCr mod p |
| [BCOEF](https://www.spoj.com/problems/BCOEF/) | SPOJ | Lucas theorem |
| 🟢 [Binomial Coefficients](https://cses.fi/problemset/task/1079) | CSES | nCr mod p queries |
| 🟢 [Creating Strings II](https://cses.fi/problemset/task/1715) | CSES | Multinomial coefficient |
| 🟢 [Distributing Apples](https://cses.fi/problemset/task/1716) | CSES | Stars and Bars |
| 🟢 [Christmas Party](https://cses.fi/problemset/task/1717) | CSES | Derangements |
| 🟢 [Bracket Sequences I](https://cses.fi/problemset/task/2064) | CSES | Catalan numbers |
| 🟢 [Bracket Sequences II](https://cses.fi/problemset/task/2187) | CSES | Catalan + prefix |
| 🟢 [Counting Necklaces](https://cses.fi/problemset/task/2209) | CSES | Burnside + φ(n) |
| 🟢 [Counting Grids](https://cses.fi/problemset/task/2210) | CSES | Burnside's lemma |

---

