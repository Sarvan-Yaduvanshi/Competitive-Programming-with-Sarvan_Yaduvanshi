# 📘 Level 1 — GCD & Euclidean Algorithms

> **The most fundamental algorithm in number theory.** GCD is used everywhere: modular inverse, Diophantine equations, CRT, and more.  
> _Reference: [cp-algorithms.com — Euclidean Algorithm](https://cp-algorithms.com/algebra/euclid-algorithm.html)_

---

## 📋 Topics Covered

| # | Topic | Key Idea |
|---|-------|----------|
| 1 | GCD Definition & Properties | Greatest common divisor |
| 2 | Euclidean Algorithm | gcd(a,b) = gcd(b, a mod b) |
| 3 | Extended Euclidean Algorithm | Find x,y: ax + by = gcd(a,b) |
| 4 | Binary GCD (Stein's Algorithm) | Bitwise GCD |
| 5 | LCM Relationship | lcm(a,b) = a*b / gcd(a,b) |

---

## 1️⃣ GCD — Definition

### Definition
The **greatest common divisor** of integers $a$ and $b$ (not both zero) is the largest positive integer that divides both $a$ and $b$.

$$\gcd(a, b) = \max\{d > 0 : d \mid a \text{ and } d \mid b\}$$

### Properties

1. $\gcd(a, 0) = |a|$
2. $\gcd(a, b) = \gcd(b, a)$ (commutative)
3. $\gcd(a, b) = \gcd(|a|, |b|)$ 
4. $\gcd(a, b) = \gcd(a - b, b)$ for $a \geq b > 0$
5. $\gcd(a, b) = \gcd(a \mod b, b)$
6. If $g = \gcd(a, b)$, then $\gcd(a/g, b/g) = 1$ (coprime)
7. $\gcd(ka, kb) = k \cdot \gcd(a, b)$ for $k > 0$
8. If $p$ is prime and $p \mid ab$, then $p \mid a$ or $p \mid b$ (Euclid's Lemma)

---

## 2️⃣ Euclidean Algorithm

### Key Insight (Why It Works)

**Theorem:** $\gcd(a, b) = \gcd(b, a \mod b)$

**Proof:**
> Let $d = \gcd(a, b)$ and $d' = \gcd(b, a \mod b)$.  
> Write $a = bq + r$ where $r = a \mod b$.  
>  
> **Show $d \mid d'$:** Since $d \mid a$ and $d \mid b$, we have $d \mid (a - bq) = r$. So $d$ divides both $b$ and $r$, meaning $d \mid d'$.  
>  
> **Show $d' \mid d$:** Since $d' \mid b$ and $d' \mid r$, we have $d' \mid (bq + r) = a$. So $d'$ divides both $a$ and $b$, meaning $d' \mid d$.  
>  
> Since $d \mid d'$ and $d' \mid d$ and both are positive, $d = d'$. ∎

### Algorithm

```
gcd(a, b):
    if b == 0: return a
    return gcd(b, a mod b)
```

### Dry Run: gcd(48, 18)

```
gcd(48, 18)
= gcd(18, 48 mod 18) = gcd(18, 12)
= gcd(12, 18 mod 12) = gcd(12, 6)
= gcd(6, 12 mod 6)   = gcd(6, 0)
= 6

Verification: 48 = 6 × 8, 18 = 6 × 3  ✓
```

### Dry Run: gcd(252, 105)

```
gcd(252, 105)
= gcd(105, 252 mod 105) = gcd(105, 42)
= gcd(42, 105 mod 42)   = gcd(42, 21)
= gcd(21, 42 mod 21)    = gcd(21, 0)
= 21

Verification: 252 = 21 × 12, 105 = 21 × 5  ✓
```

### Complexity: $O(\log(\min(a, b)))$

**Proof sketch:** After two steps, the larger number is reduced by at least half (by the Fibonacci argument). So the number of steps ≤ $2 \log_2(\min(a,b)) + 1$.

**Worst case:** Consecutive Fibonacci numbers. $\gcd(F_{n+1}, F_n) = 1$ takes $n$ steps.

---

## 3️⃣ Extended Euclidean Algorithm

### Problem
Find integers $x, y$ such that:
$$ax + by = \gcd(a, b)$$

This is called **Bézout's Identity**: such $x, y$ always exist.

### Proof of Bézout's Identity

> Let $S = \{ax + by : x, y \in \mathbb{Z}, ax + by > 0\}$.  
> $S$ is non-empty (contains $|a|$ and $|b|$).  
> Let $d$ be the smallest element of $S$, so $d = ax_0 + by_0$.  
>  
> **Claim:** $d = \gcd(a, b)$.  
>  
> *$d$ divides $a$:* By division algorithm, $a = qd + r$ with $0 \leq r < d$.  
> Then $r = a - qd = a - q(ax_0 + by_0) = a(1 - qx_0) + b(-qy_0)$.  
> If $r > 0$, then $r \in S$ and $r < d$, contradicting minimality. So $r = 0$, meaning $d \mid a$.  
> Similarly, $d \mid b$.  
>  
> *$d$ is the greatest:* If $c \mid a$ and $c \mid b$, then $c \mid (ax_0 + by_0) = d$, so $c \leq d$. ∎

### Algorithm

```
extended_gcd(a, b):
    if b == 0:
        return (a, 1, 0)    // gcd = a, x = 1, y = 0  (a*1 + 0*0 = a)
    
    (g, x1, y1) = extended_gcd(b, a mod b)
    
    // We know: b * x1 + (a mod b) * y1 = g
    // Since a mod b = a - ⌊a/b⌋ * b:
    //   b * x1 + (a - ⌊a/b⌋ * b) * y1 = g
    //   a * y1 + b * (x1 - ⌊a/b⌋ * y1) = g
    
    x = y1
    y = x1 - ⌊a/b⌋ * y1
    
    return (g, x, y)
```

### Dry Run: extended_gcd(30, 12)

```
extended_gcd(30, 12):
  extended_gcd(12, 6):
    extended_gcd(6, 0):
      return (6, 1, 0)          // 6*1 + 0*0 = 6 ✓
    
    g=6, x1=1, y1=0
    x = y1 = 0
    y = x1 - ⌊12/6⌋ * y1 = 1 - 2*0 = 1
    return (6, 0, 1)            // 12*0 + 6*1 = 6 ✓
  
  g=6, x1=0, y1=1
  x = y1 = 1
  y = x1 - ⌊30/12⌋ * y1 = 0 - 2*1 = -2
  return (6, 1, -2)             // 30*1 + 12*(-2) = 30 - 24 = 6 ✓

Answer: 30(1) + 12(-2) = 6 = gcd(30, 12) ✓
```

---

## 4️⃣ Binary GCD (Stein's Algorithm)

Uses only subtraction, halving, and comparison (no modulo — useful on hardware without division).

### Rules:
1. $\gcd(0, b) = b$
2. $\gcd(2a, 2b) = 2 \cdot \gcd(a, b)$
3. $\gcd(2a, b) = \gcd(a, b)$ if $b$ is odd
4. $\gcd(a, b) = \gcd(|a - b|, \min(a, b))$ if both odd

### Complexity: $O(\log^2(\max(a,b)))$

---

## 5️⃣ LCM — Least Common Multiple

### Definition
$$\text{lcm}(a, b) = \frac{|a \cdot b|}{\gcd(a, b)}$$

### Proof
> Let $g = \gcd(a, b)$, $a = g \cdot a'$, $b = g \cdot b'$ where $\gcd(a', b') = 1$.  
> Any common multiple of $a$ and $b$ must be divisible by $g \cdot a' \cdot b' = \frac{ab}{g}$.  
> Since $\gcd(a', b') = 1$, this is indeed the smallest. ∎

### CP Trick: Avoid Overflow
```cpp
// WRONG: a * b might overflow
i64 lcm = a * b / gcd(a, b);

// RIGHT: divide first
i64 lcm = (a / gcd(a, b)) * b;
```

### Properties
1. $\text{lcm}(a, b) \cdot \gcd(a, b) = |a \cdot b|$
2. $\text{lcm}(a, b, c) = \text{lcm}(\text{lcm}(a, b), c)$
3. $\text{lcm}(ka, kb) = k \cdot \text{lcm}(a, b)$

---

## 📁 Files in This Section

| File | Description |
|------|-------------|
| [01_Euclidean_Algorithm.cpp](01_Euclidean_Algorithm.cpp) | Basic GCD with dry run traces |
| [02_Extended_Euclidean.cpp](02_Extended_Euclidean.cpp) | Extended GCD, Bézout coefficients |
| [03_GCD_Applications.cpp](03_GCD_Applications.cpp) | LCM, Binary GCD, coprime check, array GCD |

---

## 🎯 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [GCD Problem](https://codeforces.com/problemset/problem/1617/B) | CF 1617B | GCD properties |
| [Gregor and Cryptography](https://codeforces.com/problemset/problem/1549/A) | CF 1549A | GCD + division |
| [LCM Challenge](https://codeforces.com/problemset/problem/235/A) | CF 235A | LCM maximization |
| [CEQU](https://www.spoj.com/problems/CEQU/) | SPOJ | Extended Euclidean |
| [GCD & LCM](https://practice.geeksforgeeks.org/problems/lcm-and-gcd/) | GFG | Basic |
| 🟢 [Common Divisors](https://cses.fi/problemset/task/1081) | CSES | Max GCD in array |

---

