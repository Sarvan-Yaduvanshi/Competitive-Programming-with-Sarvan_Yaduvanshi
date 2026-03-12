# 📘 Level 10 — Chinese Remainder Theorem

> **Solving systems of simultaneous congruences.** CRT is essential for large number reconstruction.  
> _Reference: [cp-algorithms.com — CRT](https://cp-algorithms.com/algebra/chinese-remainder-theorem.html)_

---

## 1️⃣ Statement (Coprime Moduli)

Given pairwise coprime moduli $m_1, m_2, \ldots, m_k$ and remainders $r_i$:

$$x \equiv r_1 \pmod{m_1}, \quad x \equiv r_2 \pmod{m_2}, \quad \ldots, \quad x \equiv r_k \pmod{m_k}$$

There exists a **unique** solution modulo $M = m_1 \cdot m_2 \cdots m_k$.

### Proof (Constructive)
> Let $M_i = M / m_i$. Since $\gcd(M_i, m_i) = 1$, the inverse $M_i^{-1} \pmod{m_i}$ exists.  
> Set $x = \sum_{i=1}^{k} r_i \cdot M_i \cdot M_i^{-1} \bmod M$.  
> For each $j$: $x \equiv r_j \cdot M_j \cdot M_j^{-1} \equiv r_j \pmod{m_j}$ (other terms vanish). ∎

### Dry Run: x ≡ 2 (mod 3), x ≡ 3 (mod 5), x ≡ 2 (mod 7)

```
M = 3 × 5 × 7 = 105
M₁ = 105/3 = 35, M₁⁻¹ mod 3: 35 mod 3 = 2, 2⁻¹ mod 3 = 2 (2×2=4≡1)
M₂ = 105/5 = 21, M₂⁻¹ mod 5: 21 mod 5 = 1, 1⁻¹ mod 5 = 1
M₃ = 105/7 = 15, M₃⁻¹ mod 7: 15 mod 7 = 1, 1⁻¹ mod 7 = 1

x = 2×35×2 + 3×21×1 + 2×15×1 = 140 + 63 + 30 = 233
233 mod 105 = 23

Check: 23 mod 3 = 2 ✓, 23 mod 5 = 3 ✓, 23 mod 7 = 2 ✓
```

---

## 2️⃣ Non-Coprime CRT

For $x \equiv r_1 \pmod{m_1}$ and $x \equiv r_2 \pmod{m_2}$:

Solution exists iff $\gcd(m_1, m_2) \mid (r_2 - r_1)$.

If so: $x \equiv r_1 + m_1 \cdot t \pmod{\text{lcm}(m_1, m_2)}$ where $t$ is found via Extended Euclid.

---

## 3️⃣ Garner's Algorithm

Computes CRT in a mixed-radix representation, useful when final answer needs to be stored modulo some other value.

---

## 📁 Files in This Section

| File | Description |
|------|-------------|
| [01_CRT_Coprime.cpp](01_CRT_Coprime.cpp) | Standard CRT for coprime moduli |
| [02_CRT_General.cpp](02_CRT_General.cpp) | Non-coprime moduli CRT |
| [03_Garner_Algorithm.cpp](03_Garner_Algorithm.cpp) | Garner's mixed-radix CRT |

---

## 🎯 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [Remainder](https://atcoder.jp/contests/abc193/tasks/abc193_e) | AtCoder | CRT |
| [Strange Function](https://codeforces.com/problemset/problem/1542/C) | CF 1542C | CRT thinking |
| [Remainder Problem](https://codeforces.com/problemset/problem/1165/E) | CF 1165E | Modular thinking |
| 🟢 [Exponentiation II](https://cses.fi/problemset/task/1712) | CSES | a^(b^c), Euler + CRT idea |
| 🟢 [Distributing Apples](https://cses.fi/problemset/task/1716) | CSES | Stars & bars + mod inverse |

---
