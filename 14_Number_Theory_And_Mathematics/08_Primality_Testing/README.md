# 📘 Level 7 — Primality Testing

> **Is $n$ prime? Probabilistic and deterministic tests for numbers up to $10^{18}$.**  
> _Reference: [cp-algorithms.com — Primality Tests](https://cp-algorithms.com/algebra/primality_tests.html)_

---

## 📋 Topics Covered

| # | Algorithm | Time | Correctness | Range |
|---|-----------|------|-------------|-------|
| 1 | Trial Division | O(√n) | Deterministic | Any |
| 2 | Fermat Test | O(k log n) | Probabilistic | Any |
| 3 | Miller-Rabin | O(k log² n) | Probabilistic | Any |
| 4 | Deterministic Miller-Rabin | O(log² n × witnesses) | Deterministic | n < 3.3×10¹⁸ |

---

## 1️⃣ Fermat Primality Test

### Basis: Fermat's Little Theorem
If $p$ is prime, then $a^{p-1} \equiv 1 \pmod{p}$ for all $a$ with $\gcd(a, p) = 1$.

### Contrapositive
If $a^{n-1} \not\equiv 1 \pmod{n}$ for some $a$, then $n$ is **composite**.

### Problem: Carmichael Numbers
Numbers like 561, 1105, 1729 pass the Fermat test for ALL bases coprime to them, yet are composite! These are called **Carmichael numbers**.

---

## 2️⃣ Miller-Rabin Primality Test

### Key Improvement Over Fermat
Uses the fact that if $p$ is an odd prime and $x^2 \equiv 1 \pmod{p}$, then $x \equiv \pm 1 \pmod{p}$.

### Setup
Write $n - 1 = 2^s \cdot d$ where $d$ is odd.

### Test for witness $a$:
1. Compute $x = a^d \bmod n$
2. If $x = 1$ or $x = n-1$: **probably prime** (for this witness)
3. Repeat $s-1$ times: $x = x^2 \bmod n$
   - If $x = n-1$: probably prime
   - If $x = 1$: **composite** (found non-trivial square root of 1)
4. If never hit $n-1$: **composite**

### Dry Run: Test n = 221, a = 174

```
n - 1 = 220 = 2² × 55, so s=2, d=55

Step 1: x = 174^55 mod 221
  174^55 mod 221 = 47  (computed via fast power)
  x ≠ 1 and x ≠ 220

Step 2: x = 47² mod 221 = 2209 mod 221 = 220 = n-1  ✓
  → Hit n-1, so "probably prime" for witness 174.

But 221 = 13 × 17 (composite!). Try witness a = 137:
  x = 137^55 mod 221 = 188
  x = 188² mod 221 = 205
  Never hit n-1 → COMPOSITE ✓
```

### Deterministic Witnesses
For $n < 3.3 \times 10^{18}$, testing witnesses $\{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37\}$ is sufficient.

| Range | Witnesses Needed |
|-------|-----------------|
| n < 2,047 | {2} |
| n < 1,373,653 | {2, 3} |
| n < 3,215,031,751 | {2, 3, 5, 7} |
| n < 3,317,044,064,679,887,385,961,981 | {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37} |

---

## 📁 Files in This Section

| File | Description |
|------|-------------|
| [01_Trial_Division_Primality.cpp](01_Trial_Division_Primality.cpp) | O(√n) primality check |
| [02_Miller_Rabin.cpp](02_Miller_Rabin.cpp) | Probabilistic + deterministic Miller-Rabin |

---

## 🎯 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [PON](https://www.spoj.com/problems/PON/) | SPOJ | Miller-Rabin |
| [Primality Test](https://practice.geeksforgeeks.org/problems/primality-test/) | GFG | Optimized trial |
| 🟢 [Counting Divisors](https://cses.fi/problemset/task/1713) | CSES | Primality + factorization |
| 🟢 [Divisor Analysis](https://cses.fi/problemset/task/2182) | CSES | Prime power factorization |

---

