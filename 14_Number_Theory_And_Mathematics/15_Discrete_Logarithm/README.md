# 📘 Level 14 — Discrete Logarithm

> **Find $x$ such that $a^x \equiv b \pmod{m}$.** Baby-step Giant-step algorithm.  
> _Reference: [cp-algorithms.com — Discrete Logarithm](https://cp-algorithms.com/algebra/discrete-log.html)_

---

## 1️⃣ Problem

Given $a, b, m$, find the smallest non-negative $x$ such that:
$$a^x \equiv b \pmod{m}$$

---

## 2️⃣ Baby-step Giant-step (BSGS)

### Idea (Meet in the Middle)
Let $k = \lceil\sqrt{m}\rceil$. Write $x = ik - j$ where $0 \leq j < k$.

Then $a^{ik} \equiv b \cdot a^j \pmod{m}$.

- **Baby steps:** Compute $b \cdot a^j \bmod m$ for $j = 0, 1, \ldots, k-1$. Store in hash map.
- **Giant steps:** Compute $a^{ik} \bmod m$ for $i = 1, 2, \ldots, k$. Look up in hash map.

### Complexity: $O(\sqrt{m})$ time and space.

### Dry Run: Find $x$: $3^x \equiv 13 \pmod{17}$

```
k = ceil(√17) = 5

Baby steps (b × aʲ mod m):
  j=0: 13 × 3⁰ = 13
  j=1: 13 × 3¹ = 39 mod 17 = 5
  j=2: 13 × 3² = 117 mod 17 = 15
  j=3: 13 × 3³ = 351 mod 17 = 11
  j=4: 13 × 3⁴ = 1053 mod 17 = 16

Table: {13→0, 5→1, 15→2, 11→3, 16→4}

Giant steps (aⁱᵏ mod m):
  a^k = 3⁵ = 243 mod 17 = 5
  i=1: 5 → found in table! j=1
  x = 1×5 - 1 = 4

Check: 3⁴ = 81 mod 17 = 81 - 4×17 = 13 ✓
```

---

## 📁 Files in This Section

| File | Description |
|------|-------------|
| [01_Baby_Step_Giant_Step.cpp](01_Baby_Step_Giant_Step.cpp) | BSGS implementation |

---

## 🎯 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [Discrete Logging](https://www.spoj.com/problems/DISCRETE/) | SPOJ | BSGS |
| [Modular Equations](https://codeforces.com/problemset/problem/495/A) | CF 495A | Discrete log variant |
| 🟢 [Exponentiation II](https://cses.fi/problemset/task/1712) | CSES | Euler / discrete log idea |

---
