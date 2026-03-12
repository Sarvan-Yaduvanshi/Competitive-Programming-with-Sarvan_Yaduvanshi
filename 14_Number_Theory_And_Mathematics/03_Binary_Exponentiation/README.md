# 📘 Level 2 — Binary Exponentiation

> **Computing $a^n$ in $O(\log n)$ — the single most important algorithm in CP modular arithmetic.**  
> _Reference: [cp-algorithms.com — Binary Exponentiation](https://cp-algorithms.com/algebra/binary-exp.html)_

---

## 📋 Topics Covered

| # | Topic | Key Idea |
|---|-------|----------|
| 1 | Binary Exponentiation | a^n in O(log n) |
| 2 | Modular Exponentiation | a^n mod m |
| 3 | Matrix Exponentiation | M^n for recurrences |

---

## 1️⃣ Binary Exponentiation

### Problem
Compute $a^n$ where $n$ can be very large (up to $10^{18}$).

**Naive approach:** Multiply $a$ by itself $n$ times → $O(n)$ — way too slow!

### Key Insight
Express $n$ in binary: $n = b_k b_{k-1} \ldots b_1 b_0$ (binary digits)

$$a^n = a^{b_k \cdot 2^k + b_{k-1} \cdot 2^{k-1} + \ldots + b_0 \cdot 2^0} = \prod_{i: b_i = 1} a^{2^i}$$

We can compute $a^1, a^2, a^4, a^8, \ldots$ by repeated squaring.

### Algorithm

```
power(a, n):
    result = 1
    while n > 0:
        if n is odd:        // last bit is 1
            result = result × a
        a = a × a           // square the base
        n = n >> 1           // shift right (divide by 2)
    return result
```

### Dry Run: $3^{13}$

$13 = 1101_2$ (binary), so $3^{13} = 3^8 \cdot 3^4 \cdot 3^1$

```
Step  | n (binary) | n odd? | result      | a (base)
------|------------|--------|-------------|----------
  0   | 1101 (13)  | YES    | 1 × 3 = 3  | 3² = 9
  1   | 0110 (6)   | NO     | 3           | 9² = 81
  2   | 0011 (3)   | YES    | 3 × 81=243  | 81² = 6561
  3   | 0001 (1)   | YES    | 243×6561    | 6561² (done)
                             = 1594323

Verify: 3^13 = 1594323 ✓
```

### Proof of Correctness

**Loop invariant:** At the start of each iteration, the answer is `result × a^n`.

> - Initially: `result = 1`, so answer = $1 \times a^n = a^n$. ✓  
> - If $n$ is odd: `result *= a`, `a *= a`, `n >>= 1`.  
>   New answer = `(result × a) × (a²)^{(n-1)/2}` = `result × a × a^{n-1}` = `result × a^n`. ✓  
> - If $n$ is even: `a *= a`, `n >>= 1`.  
>   New answer = `result × (a²)^{n/2}` = `result × a^n`. ✓  
> - When $n = 0$: answer = `result × a^0 = result`. ∎

### Complexity
- **Time:** $O(\log n)$ multiplications
- **Space:** $O(1)$

---

## 2️⃣ Modular Exponentiation

### Formula
$$a^n \mod m$$

Just take modulo at every multiplication step to prevent overflow.

### Why $(a \cdot b) \mod m = ((a \mod m) \cdot (b \mod m)) \mod m$?

**Proof:**
> Let $a = q_1 m + r_1$ and $b = q_2 m + r_2$.  
> $ab = (q_1 m + r_1)(q_2 m + r_2) = m(\ldots) + r_1 r_2$  
> So $ab \mod m = r_1 r_2 \mod m = (a \mod m)(b \mod m) \mod m$. ∎

### Overflow Prevention
For $m \leq 10^9$: `(a % m) * (b % m)` fits in `long long` (at most ~$10^{18}$).  
For $m \leq 10^{18}$: Use `__int128` or binary multiplication.

---

## 3️⃣ Matrix Exponentiation

### Idea
If a recurrence can be written as matrix multiplication:
$$\vec{v}_n = M \cdot \vec{v}_{n-1}$$

Then $\vec{v}_n = M^n \cdot \vec{v}_0$, and we compute $M^n$ via binary exponentiation.

### Example: Fibonacci Numbers
$$F_n = F_{n-1} + F_{n-2}$$

$$\begin{pmatrix} F_{n+1} \\ F_n \end{pmatrix} = \begin{pmatrix} 1 & 1 \\ 1 & 0 \end{pmatrix} \begin{pmatrix} F_n \\ F_{n-1} \end{pmatrix}$$

$$\begin{pmatrix} F_{n+1} \\ F_n \end{pmatrix} = \begin{pmatrix} 1 & 1 \\ 1 & 0 \end{pmatrix}^n \begin{pmatrix} 1 \\ 0 \end{pmatrix}$$

### Complexity
For $k \times k$ matrix: $O(k^3 \log n)$

---

## 📁 Files in This Section

| File | Description |
|------|-------------|
| [01_Iterative_BinExp.cpp](01_Iterative_BinExp.cpp) | Iterative binary exponentiation with dry run |
| [02_Recursive_BinExp.cpp](02_Recursive_BinExp.cpp) | Recursive version + modular exponentiation |
| [03_Matrix_Exponentiation.cpp](03_Matrix_Exponentiation.cpp) | Matrix power for Fibonacci and recurrences |

---

## 🎯 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [Pow(x,n)](https://leetcode.com/problems/powx-n/) | LC 50 | Binary exp |
| [The Last Digit](https://www.spoj.com/problems/LASTDIG/) | SPOJ | a^b mod 10 |
| [Magic Gems](https://codeforces.com/problemset/problem/1117/D) | CF 1117D | Matrix exp |
| [Super Pow](https://leetcode.com/problems/super-pow/) | LC 372 | Modular exp |
| 🟢 [Exponentiation](https://cses.fi/problemset/task/1095) | CSES | a^b mod 10^9+7 |
| 🟢 [Exponentiation II](https://cses.fi/problemset/task/1712) | CSES | a^(b^c) mod m, Euler thm |
| 🟢 [Fibonacci Numbers](https://cses.fi/problemset/task/1722) | CSES | Matrix exponentiation |
| 🟢 [Throwing Dice](https://cses.fi/problemset/task/1096) | CSES | Matrix exp + recurrence |
| 🟢 [Graph Paths I](https://cses.fi/problemset/task/1202) | CSES | Matrix exp + adjacency |

---

