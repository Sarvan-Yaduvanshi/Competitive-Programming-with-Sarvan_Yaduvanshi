# 📘 Level 4 — Modular Inverse

> **Finding $a^{-1} \pmod{m}$: the element such that $a \cdot a^{-1} \equiv 1 \pmod{m}$.**  
> _Reference: [cp-algorithms.com — Modular Inverse](https://cp-algorithms.com/algebra/module-inverse.html)_

---

## 📋 Topics Covered

| # | Topic | Method | When to Use |
|---|-------|--------|------------|
| 1 | Extended Euclidean | extgcd(a, m, x, y) | Any m, gcd(a,m)=1 |
| 2 | Fermat's Little Theorem | a^(p-2) mod p | Prime modulus only |
| 3 | Euler's Theorem | a^(φ(m)-1) mod m | General, need φ(m) |
| 4 | Precomputation | inv[i] = -(m/i)*inv[m%i] | All inverses 1..n |

---

## 1️⃣ When Does Inverse Exist?

### Theorem
$a^{-1} \pmod{m}$ exists if and only if $\gcd(a, m) = 1$.

### Proof
> **If direction:** If $\gcd(a, m) = 1$, by Bézout's identity, $\exists x, y: ax + my = 1$.  
> So $ax \equiv 1 \pmod{m}$, meaning $x$ is the inverse.  
>  
> **Only if direction:** If $ax \equiv 1 \pmod{m}$, then $m \mid (ax - 1)$, so $ax - my = 1$ for some $y$.  
> Any common divisor of $a$ and $m$ divides 1, so $\gcd(a, m) = 1$. ∎

---

## 2️⃣ Method 1: Extended Euclidean Algorithm

From $ax + my = \gcd(a, m) = 1$, we get $x = a^{-1} \pmod{m}$.

### Dry Run: Find $3^{-1} \pmod{7}$

```
extgcd(3, 7):
  extgcd(7, 3):
    extgcd(3, 1):
      extgcd(1, 0): return (1, 1, 0)
      x=0, y=1-3*0=1 → 3*0 + 1*1 = 1 ✓
    x=1, y=0-2*1=-2 → 7*1 + 3*(-2) = 1 ✓
  x=-2, y=1-0*(-2)=1 → 3*(-2) + 7*1 = 1

x = -2, normalize: (-2 + 7) % 7 = 5
Check: 3 × 5 = 15 ≡ 1 (mod 7) ✓
```

---

## 3️⃣ Method 2: Fermat's Little Theorem

If $p$ is **prime**: $a^{-1} \equiv a^{p-2} \pmod{p}$

### Proof
> By Fermat: $a^{p-1} \equiv 1 \pmod{p}$  
> So $a \cdot a^{p-2} \equiv 1 \pmod{p}$  
> Therefore $a^{-1} = a^{p-2}$. ∎

This is the **most common method in CP** since modulus is usually prime.

### Dry Run: Find $5^{-1} \pmod{10^9+7}$

$5^{10^9+5} \bmod (10^9+7)$ — computed via binary exponentiation.

---

## 4️⃣ Method 3: Precomputation of All Inverses — O(n)

### Formula
$$\text{inv}[i] = -(m / i) \cdot \text{inv}[m \bmod i] \bmod m$$

### Proof
> Write $m = q \cdot i + r$ where $q = \lfloor m/i \rfloor$, $r = m \bmod i$.  
> Then $q \cdot i + r \equiv 0 \pmod{m}$  
> $i \equiv -r/q \equiv -(m \bmod i) / \lfloor m/i \rfloor \pmod{m}$  
> $i^{-1} \equiv -\lfloor m/i \rfloor / (m \bmod i) \equiv -\lfloor m/i \rfloor \cdot \text{inv}[m \bmod i] \pmod{m}$ ∎

### Dry Run: m = 7, compute inv[1..6]

```
inv[1] = 1
inv[2] = -(7/2) * inv[7%2] = -3 * inv[1] = -3 ≡ 4 (mod 7)    Check: 2×4=8≡1 ✓
inv[3] = -(7/3) * inv[7%3] = -2 * inv[1] = -2 ≡ 5 (mod 7)    Check: 3×5=15≡1 ✓
inv[4] = -(7/4) * inv[7%4] = -1 * inv[3] = -5 ≡ 2 (mod 7)    Check: 4×2=8≡1 ✓
inv[5] = -(7/5) * inv[7%5] = -1 * inv[2] = -4 ≡ 3 (mod 7)    Check: 5×3=15≡1 ✓
inv[6] = -(7/6) * inv[7%6] = -1 * inv[1] = -1 ≡ 6 (mod 7)    Check: 6×6=36≡1 ✓
```

---

## 📁 Files in This Section

| File | Description |
|------|-------------|
| [01_Fermats_Inverse.cpp](01_Fermats_Inverse.cpp) | Inverse via a^(p-2) |
| [02_ExtGCD_Inverse.cpp](02_ExtGCD_Inverse.cpp) | Inverse via Extended Euclidean |
| [03_Precompute_Inverses.cpp](03_Precompute_Inverses.cpp) | O(n) precomputation of inv[1..n] |

---

## 🎯 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [MODINV](https://www.spoj.com/problems/MODINV/) | SPOJ | Extended Euclid |
| [Paths on a Grid](https://codeforces.com/problemset/problem/697/C) | CF | nCr with mod inverse |
| [Fraction to Decimal](https://leetcode.com/problems/fraction-to-recurring-decimal/) | LC 166 | Mod inverse concept |
| 🟢 [Binomial Coefficients](https://cses.fi/problemset/task/1079) | CSES | nCr requires mod inverse |
| 🟢 [Creating Strings II](https://cses.fi/problemset/task/1715) | CSES | Multinomial via inverse |

---

