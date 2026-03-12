# 📘 Level 16 — Modular Square Root

> **Find $x$ such that $x^2 \equiv a \pmod{p}$.** Tonelli-Shanks and Cipolla algorithms.  
> _Reference: [cp-algorithms.com — Square Root](https://cp-algorithms.com/algebra/quadratic_residue.html)_

---

## 1️⃣ Quadratic Residues

### Definition
$a$ is a **quadratic residue** mod $p$ if $\exists x: x^2 \equiv a \pmod{p}$.

### Euler's Criterion
For odd prime $p$ and $\gcd(a, p) = 1$:

$$a^{(p-1)/2} \equiv \begin{cases} 1 \pmod{p} & \text{if } a \text{ is QR} \\ -1 \pmod{p} & \text{if } a \text{ is QNR} \end{cases}$$

### Legendre Symbol
$$\left(\frac{a}{p}\right) = a^{(p-1)/2} \bmod p \in \{0, 1, -1\}$$

---

## 2️⃣ Tonelli-Shanks Algorithm

### When: $p$ is an odd prime, $a$ is a QR mod $p$.

### Setup
Write $p - 1 = 2^s \cdot q$ where $q$ is odd.

### Algorithm
1. Find a QNR $z$ (random, check Euler criterion).
2. Set $M = s$, $c = z^q$, $t = a^q$, $R = a^{(q+1)/2}$.
3. Loop: if $t \equiv 1$: return $R$. Else find smallest $i$ with $t^{2^i} \equiv 1$. Update.

### Complexity: $O(\log^2 p)$

---

## 3️⃣ Cipolla's Algorithm

Uses arithmetic in $\mathbb{F}_{p^2}$ (extension field). Useful when $p - 1$ has large power of 2.

---

## 📁 Files in This Section

| File | Description |
|------|-------------|
| [01_Tonelli_Shanks.cpp](01_Tonelli_Shanks.cpp) | Square root mod prime |
| [02_Cipolla.cpp](02_Cipolla.cpp) | Alternative algorithm |

---

## 🎯 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [SQRMOD](https://www.spoj.com/problems/SQRMOD/) | SPOJ | Tonelli-Shanks |
| [Quadratic Residues](https://codeforces.com/problemset/problem/715/A) | CF 715A | Euler criterion |
| 🟢 [Exponentiation](https://cses.fi/problemset/task/1095) | CSES | Modular power (building block) |

---
