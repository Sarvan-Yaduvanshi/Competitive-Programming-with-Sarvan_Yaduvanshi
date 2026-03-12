# 📘 Level 3 — Modular Arithmetic

> **The backbone of competitive programming.** Almost every CP problem involves computing answers modulo $10^9+7$ or $998244353$.  
> _Reference: [cp-algorithms.com — Modular Arithmetic](https://cp-algorithms.com/algebra/module-inverse.html)_

---

## 📋 Topics Covered

| # | Topic | Key Idea |
|---|-------|----------|
| 1 | Congruence | a ≡ b (mod m) |
| 2 | Modular Operations | +, −, ×, ÷ under mod |
| 3 | Fermat's Little Theorem | a^(p-1) ≡ 1 (mod p) |
| 4 | Euler's Theorem | a^φ(n) ≡ 1 (mod n) |
| 5 | Lifting the Exponent (LTE) | v_p(a^n ± b^n) exact formula |

---

## 1️⃣ Congruence

### Definition
We say $a \equiv b \pmod{m}$ if $m \mid (a - b)$, i.e., $a$ and $b$ have the same remainder when divided by $m$.

$$a \equiv b \pmod{m} \iff m \mid (a - b) \iff a \bmod m = b \bmod m$$

### Properties
1. **Reflexive:** $a \equiv a$
2. **Symmetric:** $a \equiv b \implies b \equiv a$
3. **Transitive:** $a \equiv b, b \equiv c \implies a \equiv c$
4. **Addition:** $a \equiv b, c \equiv d \implies a+c \equiv b+d$
5. **Multiplication:** $a \equiv b, c \equiv d \implies ac \equiv bd$
6. **Power:** $a \equiv b \implies a^k \equiv b^k$

**⚠️ Division is NOT always valid!** $6 \equiv 0 \pmod{6}$ but $6/3 \not\equiv 0/3 \pmod{6}$ (i.e., $2 \not\equiv 0 \pmod{6}$). Division requires modular inverse.

---

## 2️⃣ Modular Operations

### Addition
$$(a + b) \bmod m = ((a \bmod m) + (b \bmod m)) \bmod m$$

### Subtraction
$$(a - b) \bmod m = ((a \bmod m) - (b \bmod m) + m) \bmod m$$
The $+m$ ensures non-negative result.

### Multiplication
$$(a \times b) \bmod m = ((a \bmod m) \times (b \bmod m)) \bmod m$$

### Division
$$(a / b) \bmod m = (a \times b^{-1}) \bmod m$$
where $b^{-1}$ is the **modular inverse** of $b$ (exists iff $\gcd(b, m) = 1$).

### Proof of Multiplication Property

> Let $a = q_1 m + r_1$ and $b = q_2 m + r_2$.  
> Then $ab = (q_1 m + r_1)(q_2 m + r_2) = m(q_1 q_2 m + q_1 r_2 + q_2 r_1) + r_1 r_2$  
> So $ab \bmod m = r_1 r_2 \bmod m = (a \bmod m)(b \bmod m) \bmod m$. ∎

---

## 3️⃣ Fermat's Little Theorem

### Statement
If $p$ is prime and $\gcd(a, p) = 1$, then:
$$a^{p-1} \equiv 1 \pmod{p}$$

Equivalently: $a^p \equiv a \pmod{p}$ for all integers $a$.

### Proof (Counting Argument)

> Consider the set $S = \{1, 2, 3, \ldots, p-1\}$.  
> Multiply every element by $a$: $S' = \{a, 2a, 3a, \ldots, (p-1)a\}$.  
>  
> **Claim:** $S' \bmod p$ is a permutation of $S$.  
> - No two elements are equal mod $p$: If $ia \equiv ja \pmod{p}$ with $i \neq j$, then $p \mid (i-j)a$. Since $\gcd(a,p) = 1$, we need $p \mid (i-j)$, impossible for $1 \leq i, j \leq p-1$.  
> - No element is $0$ mod $p$: $ia \equiv 0 \implies p \mid ia \implies p \mid i$, impossible.  
>  
> Therefore:
> $$\prod_{k=1}^{p-1} (ka) \equiv \prod_{k=1}^{p-1} k \pmod{p}$$
> $$(p-1)! \cdot a^{p-1} \equiv (p-1)! \pmod{p}$$
>  
> Since $\gcd((p-1)!, p) = 1$, we can divide both sides:
> $$a^{p-1} \equiv 1 \pmod{p}$$ ∎

### Example
$p = 7, a = 3$: $3^6 = 729 = 104 \times 7 + 1 \equiv 1 \pmod{7}$ ✓

### Application: Modular Inverse
$$a^{-1} \equiv a^{p-2} \pmod{p}$$

---

## 4️⃣ Euler's Theorem (Generalization)

### Euler's Totient Function
$\phi(n)$ = count of integers in $\{1, 2, \ldots, n\}$ coprime to $n$.

### Statement
If $\gcd(a, n) = 1$, then:
$$a^{\phi(n)} \equiv 1 \pmod{n}$$

### Note
Fermat's Little Theorem is the special case where $n = p$ (prime), since $\phi(p) = p - 1$.

### Dry Run: Euler's Theorem with n = 10

$\phi(10) = |\{1, 3, 7, 9\}| = 4$

For $a = 3$: $3^4 = 81 \equiv 1 \pmod{10}$ ✓  
For $a = 7$: $7^4 = 2401 \equiv 1 \pmod{10}$ ✓  
For $a = 9$: $9^4 = 6561 \equiv 1 \pmod{10}$ ✓

---

## 📁 Files in This Section

| File | Description |
|------|-------------|
| [01_Modular_Basics.cpp](01_Modular_Basics.cpp) | Modular add/sub/mul with examples |
| [02_Fermats_And_Euler.cpp](02_Fermats_And_Euler.cpp) | Fermat's theorem, Euler's theorem verification |
| [03_Large_Modular_Arithmetic.cpp](03_Large_Modular_Arithmetic.cpp) | __int128, overflow-safe operations |
| [04_Lifting_The_Exponent.cpp](04_Lifting_The_Exponent.cpp) | LTE lemma: v_p(aⁿ ± bⁿ) |

---

## 🎯 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [Add Modulo 10](https://codeforces.com/problemset/problem/1714/C) | CF 1714C | Mod cycle |
| [Modulo Sum](https://codeforces.com/problemset/problem/577/B) | CF 577B | Pigeonhole + mod |
| [Modular Exponentiation](https://practice.geeksforgeeks.org/problems/modular-exponentiation/) | GFG | Mod arithmetic |
| 🟢 [Exponentiation II](https://cses.fi/problemset/task/1712) | CSES | Euler's theorem in practice |

---

