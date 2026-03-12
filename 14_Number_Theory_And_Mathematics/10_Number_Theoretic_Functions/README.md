# 📘 Level 9 — Number-Theoretic Functions

> **Euler's Totient $\phi(n)$, Möbius $\mu(n)$, Divisor count $\tau(n)$, Divisor sum $\sigma(n)$.**  
> _Reference: [cp-algorithms.com — Euler's Totient](https://cp-algorithms.com/algebra/phi-function.html)_

---

## 1️⃣ Euler's Totient Function φ(n)

### Definition
$\phi(n) = |\{k : 1 \leq k \leq n, \gcd(k, n) = 1\}|$

### Formula
If $n = p_1^{a_1} \cdot p_2^{a_2} \cdots p_k^{a_k}$:

$$\phi(n) = n \prod_{p \mid n} \left(1 - \frac{1}{p}\right) = n \cdot \frac{p_1 - 1}{p_1} \cdot \frac{p_2 - 1}{p_2} \cdots$$

### Proof
> By Inclusion-Exclusion: count integers in $[1, n]$ not divisible by any prime factor of $n$.  
> Total = $n$  
> Subtract: divisible by $p_1$: $n/p_1$, by $p_2$: $n/p_2$, ...  
> Add back: divisible by $p_1 p_2$: $n/(p_1 p_2)$, ...  
> Result: $n(1 - 1/p_1)(1 - 1/p_2)\cdots$ ∎

### Properties
1. $\phi(1) = 1$
2. $\phi(p) = p - 1$ for prime $p$
3. $\phi(p^k) = p^{k-1}(p - 1)$
4. **Multiplicative:** If $\gcd(a, b) = 1$, then $\phi(ab) = \phi(a)\phi(b)$
5. **Divisor Sum Identity:** $\sum_{d \mid n} \phi(d) = n$
6. $\sum_{k=1}^{n} [\gcd(k, n) = 1] \cdot k = \frac{n \cdot \phi(n)}{2}$ for $n > 1$

### Dry Run: φ(36)
$36 = 2^2 \times 3^2$  
$\phi(36) = 36 \times (1 - 1/2) \times (1 - 1/3) = 36 \times 1/2 \times 2/3 = 12$

Verification: $\{1,5,7,11,13,17,19,23,25,29,31,35\}$ → 12 numbers coprime to 36 ✓

---

## 2️⃣ Möbius Function μ(n)

### Definition
$$\mu(n) = \begin{cases} 1 & \text{if } n = 1 \\ (-1)^k & \text{if } n = p_1 p_2 \cdots p_k \text{ (squarefree, distinct primes)} \\ 0 & \text{if } p^2 \mid n \text{ for some prime } p \end{cases}$$

### Key Identity
$$\sum_{d \mid n} \mu(d) = [n = 1] = \begin{cases} 1 & n = 1 \\ 0 & n > 1 \end{cases}$$

### Möbius Inversion Formula
If $f(n) = \sum_{d \mid n} g(d)$, then $g(n) = \sum_{d \mid n} \mu(d) \cdot f(n/d)$.

---

## 3️⃣ Divisor Functions τ(n) and σ(n)

See [Section 01](../01_Number_Theory_Foundations/README.md) for detailed coverage.

---

## 📁 Files in This Section

| File | Description |
|------|-------------|
| [01_Euler_Totient.cpp](01_Euler_Totient.cpp) | Single φ(n), sieve of φ, properties |
| [02_Mobius_Function.cpp](02_Mobius_Function.cpp) | μ(n) computation, sieve, inversion |
| [03_Divisor_Functions.cpp](03_Divisor_Functions.cpp) | τ(n), σ(n) sieve |

---

## 🎯 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [ETF](https://www.spoj.com/problems/ETF/) | SPOJ | Euler totient |
| [Power Tower](https://codeforces.com/problemset/problem/906/D) | CF 906D | Euler's theorem chain |
| [GCD Sum](https://codeforces.com/problemset/problem/1613/D) | CF 1613D | φ(n) + Euler product |
| 🟢 [Divisor Analysis](https://cses.fi/problemset/task/2182) | CSES | τ, σ, product of divisors |
| 🟢 [Sum of Divisors](https://cses.fi/problemset/task/1082) | CSES | Σ σ(i) via blocks |
| 🟢 [Counting Coprime Pairs](https://cses.fi/problemset/task/2417) | CSES | φ / Möbius application |
| 🟢 [Counting Necklaces](https://cses.fi/problemset/task/2209) | CSES | Burnside + φ |

---

