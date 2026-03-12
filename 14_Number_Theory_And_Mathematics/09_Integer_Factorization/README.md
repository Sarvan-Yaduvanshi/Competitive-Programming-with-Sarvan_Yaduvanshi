# 📘 Level 8 — Integer Factorization

> **Breaking $n$ into its prime factors.** Trial division for small $n$, Pollard's Rho for large $n$.  
> _Reference: [cp-algorithms.com — Factorization](https://cp-algorithms.com/algebra/factorization.html)_

---

## 📋 Topics Covered

| # | Algorithm | Time | Range |
|---|-----------|------|-------|
| 1 | Trial Division | O(√n) | n ≤ 10^{14} |
| 2 | SPF Sieve | O(n) preprocess, O(log n) query | n ≤ 10^7 |
| 3 | Pollard's Rho | O(n^{1/4}) expected | n ≤ 10^{18} |

---

## 1️⃣ Trial Division — O(√n)

Try dividing by 2, 3, 5, 7, 11, ... up to √n.

---

## 2️⃣ SPF Sieve Factorization

Precompute smallest prime factor for all numbers up to N using linear sieve. Then factorize in O(log n) by repeatedly dividing by spf[n].

---

## 3️⃣ Pollard's Rho Algorithm

### Idea
Find a non-trivial factor of $n$ using a pseudo-random sequence and the Birthday Paradox.

### Algorithm (Brent's optimization)
1. Pick random $x$, $c$. Define $f(x) = (x^2 + c) \bmod n$.
2. Generate sequence: $x_1, x_2, x_3, \ldots$ using tortoise-and-hare cycle detection.
3. Check $d = \gcd(|x_i - x_j|, n)$ periodically.
4. If $1 < d < n$: found a factor!

### Why $O(n^{1/4})$?
By the Birthday Paradox, collision happens after $O(\sqrt{p})$ steps where $p$ is the smallest prime factor. Since $p \leq n^{1/2}$, expected steps = $O(n^{1/4})$.

### Complete Factorization
Combine with Miller-Rabin:
1. If $n$ is prime (Miller-Rabin): done.
2. Find a factor $d$ using Pollard's Rho.
3. Recursively factorize $d$ and $n/d$.

---

## 📁 Files in This Section

| File | Description |
|------|-------------|
| [01_Trial_Division_Factor.cpp](01_Trial_Division_Factor.cpp) | O(√n) factorization |
| [02_SPF_Sieve.cpp](02_SPF_Sieve.cpp) | Linear sieve factorization |
| [03_Pollard_Rho.cpp](03_Pollard_Rho.cpp) | O(n^{1/4}) for large n |

---

## 🎯 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [FACT0](https://www.spoj.com/problems/FACT0/) | SPOJ | Pollard's Rho |
| [Ugly Number](https://leetcode.com/problems/ugly-number/) | LC 263 | Factor checking |
| 🟢 [Counting Divisors](https://cses.fi/problemset/task/1713) | CSES | Factorize + count τ(n) |
| 🟢 [Divisor Analysis](https://cses.fi/problemset/task/2182) | CSES | Full factorization analysis |

---

