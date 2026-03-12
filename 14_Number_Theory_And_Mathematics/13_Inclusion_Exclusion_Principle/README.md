# 📘 Level 12 — Inclusion-Exclusion Principle

> **Counting with overlaps.** One of the most powerful counting techniques in CP.  
> _Reference: [cp-algorithms.com — Inclusion-Exclusion](https://cp-algorithms.com/combinatorics/inclusion-exclusion.html)_

---

## 1️⃣ The Principle

### Statement
$$\left|\bigcup_{i=1}^{n} A_i\right| = \sum_{i} |A_i| - \sum_{i<j} |A_i \cap A_j| + \sum_{i<j<k} |A_i \cap A_j \cap A_k| - \cdots + (-1)^{n+1} |A_1 \cap \cdots \cap A_n|$$

### Compact Form
$$\left|\bigcup_{i=1}^{n} A_i\right| = \sum_{\emptyset \neq S \subseteq [n]} (-1)^{|S|+1} \left|\bigcap_{i \in S} A_i\right|$$

### Complement Form (more useful in CP)
$$\left|\overline{A_1} \cap \overline{A_2} \cap \cdots \cap \overline{A_n}\right| = |U| - \left|\bigcup A_i\right|$$

Count elements satisfying **none** of the conditions = Total − (those satisfying at least one).

---

## 2️⃣ Proof (by indicator)

> For any element $x$ in exactly $k$ of the sets $A_1, \ldots, A_n$ ($k \geq 1$):  
> Its contribution to the RHS = $\binom{k}{1} - \binom{k}{2} + \binom{k}{3} - \cdots = 1 - (1-1)^k = 1$.  
> For $k = 0$: contribution = 0.  
> So every element in $\bigcup A_i$ is counted exactly once. ∎

---

## 3️⃣ Applications

### Coprime Count
Count of integers in $[1, N]$ coprime to $m = p_1^{a_1} \cdots p_k^{a_k}$:

$$\text{Count} = N - \sum \lfloor N/p_i \rfloor + \sum \lfloor N/(p_i p_j) \rfloor - \cdots$$

### Derangements
$$D_n = n! \sum_{i=0}^{n} \frac{(-1)^i}{i!}$$

### Surjections
Number of surjections from $[n]$ onto $[k]$:
$$k! \cdot S(n,k) = \sum_{i=0}^{k} (-1)^i \binom{k}{i} (k-i)^n$$

---

## 📁 Files in This Section

| File | Description |
|------|-------------|
| [01_Basic_IE.cpp](01_Basic_IE.cpp) | Inclusion-Exclusion framework |
| [02_Coprime_Count.cpp](02_Coprime_Count.cpp) | Count coprime integers in range |
| [03_Derangements.cpp](03_Derangements.cpp) | Derangement computation |

---

## 🎯 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [Coprime Count](https://codeforces.com/problemset/problem/1462/D) | CF 1462D | IE + coprime |
| [Derangements](https://codeforces.com/problemset/problem/340/A) | CF 340A | Derangement formula |
| [Numbers with Repeated Digits](https://leetcode.com/problems/numbers-with-repeated-digits/) | LC 1012 | IE + digits |
| 🟢 [Prime Multiples](https://cses.fi/problemset/task/2185) | CSES | IE with prime factors |
| 🟢 [Christmas Party](https://cses.fi/problemset/task/1717) | CSES | Derangements via IE |
| 🟢 [Counting Coprime Pairs](https://cses.fi/problemset/task/2417) | CSES | Möbius / IE application |

---
