# 📘 Level 15 — Primitive Roots

> **Generators of the multiplicative group modulo $n$.** Required for discrete logarithm and index calculus.  
> _Reference: [cp-algorithms.com — Primitive Root](https://cp-algorithms.com/algebra/primitive-root.html)_

---

## 1️⃣ Definition

An integer $g$ is a **primitive root** modulo $n$ if the multiplicative order of $g$ modulo $n$ equals $\phi(n)$:

$$\text{ord}_n(g) = \phi(n)$$

i.e., $g^1, g^2, \ldots, g^{\phi(n)}$ are all distinct modulo $n$ and cover all elements coprime to $n$.

---

## 2️⃣ Existence

Primitive roots exist modulo $n$ if and only if $n$ is one of:
$$1, 2, 4, p^k, 2p^k$$
where $p$ is an odd prime and $k \geq 1$.

---

## 3️⃣ Finding a Primitive Root

### Algorithm
1. Compute $\phi(n)$.
2. Find prime factors of $\phi(n)$: $\phi(n) = q_1^{e_1} \cdot q_2^{e_2} \cdots$
3. For each candidate $g = 2, 3, 5, \ldots$:
   - Check: $g^{\phi(n)/q_i} \not\equiv 1 \pmod{n}$ for all prime factors $q_i$ of $\phi(n)$.
   - If all checks pass, $g$ is a primitive root.

### Why this works
If $g^{\phi(n)/q_i} \equiv 1$ for some $q_i$, then $\text{ord}(g) \mid \phi(n)/q_i < \phi(n)$, so $g$ is not a primitive root.

### Complexity
The smallest primitive root is $O(n^{1/4})$ (heuristic), so the search is fast.

### Dry Run: Primitive root mod 7

```
φ(7) = 6 = 2 × 3
Prime factors of 6: {2, 3}

g=2: 2^(6/2) = 2³ = 8 ≡ 1 (mod 7)  ✗ (equals 1!)
g=3: 3^(6/2) = 3³ = 27 ≡ 6 (mod 7) ✓
     3^(6/3) = 3² = 9 ≡ 2 (mod 7)  ✓
     → g = 3 is a primitive root mod 7 ✓

Powers of 3 mod 7: 3,2,6,4,5,1 — all 6 residues ✓
```

---

## 📁 Files in This Section

| File | Description |
|------|-------------|
| [01_Primitive_Root.cpp](01_Primitive_Root.cpp) | Finding primitive roots |
| [02_Discrete_Log_Via_Roots.cpp](02_Discrete_Log_Via_Roots.cpp) | Index table using primitive root |

---

## 🎯 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [Primitive Root](https://codeforces.com/problemset/problem/284/A) | CF 284A | Finding generators |
| 🟢 [Counting Necklaces](https://cses.fi/problemset/task/2209) | CSES | Burnside + cyclic group |
| 🟢 [Counting Grids](https://cses.fi/problemset/task/2210) | CSES | Group symmetry |

---
