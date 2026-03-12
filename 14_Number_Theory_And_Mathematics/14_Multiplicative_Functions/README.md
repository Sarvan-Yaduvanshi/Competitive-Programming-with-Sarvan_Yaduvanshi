# 📘 Level 13 — Multiplicative Functions

> **Dirichlet convolution, Möbius inversion, and multiplicative function theory.**  
> _Reference: [cp-algorithms.com — Multiplicative Functions](https://cp-algorithms.com/algebra/phi-function.html)_

---

## 1️⃣ Multiplicative Functions

### Definition
$f$ is **multiplicative** if $f(1) = 1$ and $f(ab) = f(a)f(b)$ whenever $\gcd(a,b) = 1$.

$f$ is **completely multiplicative** if $f(ab) = f(a)f(b)$ for ALL $a, b$.

### Examples
| Function | Formula | Multiplicative? | Completely? |
|----------|---------|-----------------|-------------|
| $\phi(n)$ | Euler totient | ✓ | ✗ |
| $\mu(n)$ | Möbius | ✓ | ✗ |
| $\tau(n)$ | Divisor count | ✓ | ✗ |
| $\sigma(n)$ | Divisor sum | ✓ | ✗ |
| $\text{id}(n) = n$ | Identity | ✓ | ✓ |
| $\mathbf{1}(n) = 1$ | Constant 1 | ✓ | ✓ |
| $\epsilon(n) = [n=1]$ | Unit | ✓ | ✗ |

---

## 2️⃣ Dirichlet Convolution

### Definition
$$(f * g)(n) = \sum_{d \mid n} f(d) \cdot g(n/d)$$

### Properties
- Associative: $(f * g) * h = f * (g * h)$
- Commutative: $f * g = g * f$
- Identity: $f * \epsilon = f$ where $\epsilon(n) = [n=1]$
- If $f, g$ multiplicative, then $f * g$ is multiplicative

### Key Identities
1. $\mu * \mathbf{1} = \epsilon$ (Möbius function is inverse of constant 1)
2. $\phi * \mathbf{1} = \text{id}$ (i.e., $\sum_{d|n} \phi(d) = n$)
3. $\mu * \text{id} = \phi$

---

## 3️⃣ Möbius Inversion

### Theorem
If $f(n) = \sum_{d \mid n} g(d)$, then $g(n) = \sum_{d \mid n} \mu(d) \cdot f(n/d)$.

Equivalently: $f = g * \mathbf{1}$ implies $g = f * \mu$.

### Proof
> $f * \mu = (g * \mathbf{1}) * \mu = g * (\mathbf{1} * \mu) = g * \epsilon = g$ ∎

### Application: Recovering φ from id
> We know $\sum_{d|n} \phi(d) = n$, i.e., $\phi * \mathbf{1} = \text{id}$.  
> By Möbius inversion: $\phi = \text{id} * \mu$, so $\phi(n) = \sum_{d|n} \mu(d) \cdot (n/d)$.

---

## 📁 Files in This Section

| File | Description |
|------|-------------|
| [01_Multiplicative_Functions.cpp](01_Multiplicative_Functions.cpp) | Sieve computation, verification |
| [02_Dirichlet_Convolution.cpp](02_Dirichlet_Convolution.cpp) | Convolution + Möbius inversion |
| [03_Mobius_Sieve.cpp](03_Mobius_Sieve.cpp) | μ(n) sieve and applications |

---

## 🎯 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [Sum of GCD](https://codeforces.com/problemset/problem/1780/F) | CF 1780F | Möbius inversion |
| [Coprime Subsequences](https://codeforces.com/problemset/problem/803/F) | CF 803F | Möbius function |
| [GCD Counting](https://codeforces.com/problemset/problem/1034/A) | CF 1034A | Dirichlet series |
| 🟢 [Counting Coprime Pairs](https://cses.fi/problemset/task/2417) | CSES | Möbius / IE |
| 🟢 [Sum of Divisors](https://cses.fi/problemset/task/1082) | CSES | Dirichlet-style block sum |
| 🟢 [Divisor Analysis](https://cses.fi/problemset/task/2182) | CSES | Multiplicative functions |

---
