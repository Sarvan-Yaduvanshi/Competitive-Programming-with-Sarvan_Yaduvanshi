# 📘 Level 20 — ICPC / GM Level Number Theory

> **Contest-level techniques combining multiple NT concepts.** Optimized implementations for the hardest problems.  
> _Reference: [cp-algorithms.com](https://cp-algorithms.com/), ICPC problem archives_

---

## 📋 Topics Covered

| # | Topic | Prerequisite |
|---|-------|-------------|
| 1 | Pollard-Rho Optimized | Factorization + Miller-Rabin |
| 2 | Advanced CRT Systems | CRT + Garner |
| 3 | Modular Linear Algebra | Gaussian elimination mod p |
| 4 | Generating Functions | Combinatorics + FFT/NTT |
| 5 | Multiplicative Function Sieve | Linear sieve + Dirichlet |
| 6 | Sum over Divisors Tricks | Möbius + Block decomposition |

---

## 1️⃣ Optimized Pollard-Rho + Miller-Rabin

The complete factorization toolkit for $n \leq 10^{18}$:
- Deterministic Miller-Rabin with 12 witnesses
- Pollard-Rho with Brent's cycle detection + batch GCD
- Combined: factorize any 64-bit number in milliseconds

---

## 2️⃣ Garner's Algorithm for CRT

When the result needs to be computed modulo some other value (e.g., $10^9+7$), Garner's mixed-radix representation avoids big numbers.

### Mixed Radix Representation
$$x = a_1 + r_1(a_2 + r_2(a_3 + \ldots))$$

where $r_i$ are the moduli and $a_i$ are computed iteratively.

---

## 3️⃣ Gaussian Elimination mod p

Solve systems of linear equations over $\mathbb{Z}_p$:
- Standard Gaussian elimination with modular inverse for pivoting
- Applications: counting solutions, finding rank, determinant mod p

---

## 4️⃣ Generating Functions

Express counting problems as formal power series:
$$f(x) = \sum_{n \geq 0} a_n x^n$$

Operations:
- Addition, multiplication (via NTT)
- Inverse: $f^{-1}(x)$ such that $f \cdot f^{-1} = 1$
- Logarithm, exponential
- All in $O(n \log n)$ via Newton's method

### Classic GF Examples
- Partition function: $\prod_{k \geq 1} \frac{1}{1 - x^k}$
- Catalan: $C(x) = \frac{1 - \sqrt{1 - 4x}}{2x}$
- Fibonacci: $\frac{x}{1 - x - x^2}$

---

## 5️⃣ Dirichlet Series Tricks

$$\sum_{n=1}^{N} f(n) = \sum_{d=1}^{N} g(d) \cdot h\left(\left\lfloor \frac{N}{d} \right\rfloor\right)$$

Computed in $O(\sqrt{N})$ using block decomposition when $h$ has known prefix sums.

---

## 6️⃣ Contest Templates

### Complete Number Theory Template for ICPC

```cpp
// Miller-Rabin + Pollard-Rho + Euler Totient + nCr + CRT
// All in one file, ready to paste.
```

---

## 📁 Files in This Section

| File | Description |
|------|-------------|
| [01_Complete_NT_Template.cpp](01_Complete_NT_Template.cpp) | All-in-one ICPC template |
| [02_Garner_Algorithm.cpp](02_Garner_Algorithm.cpp) | CRT with arbitrary output mod |
| [03_Generating_Functions.cpp](03_Generating_Functions.cpp) | GF operations via NTT |

---

## 🎯 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [Coprime Subsequences](https://codeforces.com/problemset/problem/803/F) | CF 803F | Möbius |
| [Power Tower](https://codeforces.com/problemset/problem/906/D) | CF 906D | Euler chain |
| [Sum of GCD](https://codeforces.com/problemset/problem/1780/F) | CF 1780F | Möbius inversion |
| 🟢 [Counting Coprime Pairs](https://cses.fi/problemset/task/2417) | CSES | Möbius / advanced counting |
| 🟢 [Divisor Analysis](https://cses.fi/problemset/task/2182) | CSES | Full NT function analysis |
| 🟢 [Sum of Divisors](https://cses.fi/problemset/task/1082) | CSES | Block decomposition + NT |
| 🟢 [Bracket Sequences II](https://cses.fi/problemset/task/2187) | CSES | Advanced Catalan |
| 🟢 [Counting Necklaces](https://cses.fi/problemset/task/2209) | CSES | Burnside + Euler + primitive root |
| 🟢 [Graph Paths II](https://cses.fi/problemset/task/1203) | CSES | Matrix exp + min-plus semiring |

---

