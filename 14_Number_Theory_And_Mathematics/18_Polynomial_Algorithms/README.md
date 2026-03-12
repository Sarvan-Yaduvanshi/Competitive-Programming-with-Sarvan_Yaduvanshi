# 📘 Level 17 — Polynomial Algorithms

> **Polynomial multiplication, interpolation, and formal power series.**  
> _Reference: [cp-algorithms.com — Polynomials](https://cp-algorithms.com/algebra/polynomial.html)_

---

## 1️⃣ Polynomial Representation

A polynomial $P(x) = a_0 + a_1 x + a_2 x^2 + \cdots + a_n x^n$ is stored as a vector of coefficients `[a_0, a_1, ..., a_n]`.

---

## 2️⃣ Polynomial Multiplication (Naive) — $O(n^2)$

$$(A \cdot B)[k] = \sum_{i+j=k} A[i] \cdot B[j]$$

This is a **convolution**. FFT/NTT reduces this to $O(n \log n)$ (see Section 19).

---

## 3️⃣ Polynomial Evaluation — $O(n)$

**Horner's Method:** $P(x) = a_0 + x(a_1 + x(a_2 + \cdots + x \cdot a_n))$

---

## 4️⃣ Lagrange Interpolation — $O(n^2)$

### Problem
Given $n+1$ points $(x_0, y_0), \ldots, (x_n, y_n)$, find the unique polynomial $P$ of degree $\leq n$ passing through all points.

### Formula
$$P(x) = \sum_{i=0}^{n} y_i \prod_{j \neq i} \frac{x - x_j}{x_i - x_j}$$

### Proof
> Define $L_i(x) = \prod_{j \neq i} \frac{x - x_j}{x_i - x_j}$.  
> Then $L_i(x_i) = 1$ and $L_i(x_j) = 0$ for $j \neq i$.  
> So $P(x) = \sum y_i L_i(x)$ satisfies $P(x_i) = y_i$ for all $i$.  
> Uniqueness: if $Q$ also works, $P - Q$ has degree $\leq n$ but $n+1$ roots, so $P = Q$. ∎

### Special Case: Consecutive $x_i = 0, 1, 2, \ldots, n$

This simplifies to $O(n)$ per evaluation using prefix/suffix products.

### Dry Run: Interpolate through (0,1), (1,3), (2,7)

```
L₀(x) = (x-1)(x-2) / (0-1)(0-2) = (x-1)(x-2) / 2
L₁(x) = (x-0)(x-2) / (1-0)(1-2) = x(x-2) / (-1) = -x(x-2)
L₂(x) = (x-0)(x-1) / (2-0)(2-1) = x(x-1) / 2

P(x) = 1 × L₀ + 3 × L₁ + 7 × L₂
     = (x²-3x+2)/2 - 3x(x-2) + 7x(x-1)/2
     = (x²-3x+2)/2 - 3x²+6x + (7x²-7x)/2
     = (x²-3x+2-6x²+12x+7x²-7x) / 2
     = (2x²+2x+2) / 2 = x²+x+1

Check: P(0)=1 ✓, P(1)=3 ✓, P(2)=7 ✓
```

---

## 5️⃣ Formal Power Series

Treating polynomials as infinite series, operations like inverse, log, exp, and sqrt can be defined and computed in $O(n \log n)$.

---

## 📁 Files in This Section

| File | Description |
|------|-------------|
| [01_Polynomial_Basics.cpp](01_Polynomial_Basics.cpp) | Representation, evaluation, multiplication |
| [02_Lagrange_Interpolation.cpp](02_Lagrange_Interpolation.cpp) | O(n²) and O(n) interpolation |

---

## 🎯 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [Lagrange Interpolation](https://codeforces.com/problemset/problem/622/F) | CF 622F | Interpolation |
| [Polynomial Multiplication](https://practice.geeksforgeeks.org/problems/multiply-two-polynomials/) | GFG | Naive multiply |
| 🟢 [Fibonacci Numbers](https://cses.fi/problemset/task/1722) | CSES | Polynomial / matrix approach |
| 🟢 [Throwing Dice](https://cses.fi/problemset/task/1096) | CSES | Linear recurrence → poly |
| 🟢 [Bracket Sequences I](https://cses.fi/problemset/task/2064) | CSES | Catalan via GF |

---

