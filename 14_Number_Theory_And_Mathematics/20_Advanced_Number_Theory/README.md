# 📘 Level 19 — Advanced Number Theory

> **Floor sums, continued fractions, Stern-Brocot tree, Farey sequences, and advanced modular tricks.**  
> _Reference: [cp-algorithms.com — Advanced](https://cp-algorithms.com/algebra/)_

---

## 1️⃣ Floor Function Properties

### Key Identities
- $\lfloor n/a \rfloor$ takes at most $O(\sqrt{n})$ distinct values as $a$ varies from 1 to $n$.
- **Block decomposition:** For each distinct value $v = \lfloor n/a \rfloor$, the range of $a$ giving this value is $[\lfloor n/(v+1) \rfloor + 1, \lfloor n/v \rfloor]$.

### Application: Sum $\sum_{i=1}^{n} \lfloor n/i \rfloor$ in $O(\sqrt{n})$

---

## 2️⃣ Floor Sum (Hermite / Algorithmic)

Compute $\sum_{i=0}^{n-1} \lfloor (ai + b) / m \rfloor$ in $O(\log m)$ using a reduction similar to the Euclidean algorithm.

This is the **floor_sum** function from AtCoder Library.

---

## 3️⃣ Continued Fractions

### Definition
Every real number $\alpha$ has a continued fraction representation:
$$\alpha = a_0 + \cfrac{1}{a_1 + \cfrac{1}{a_2 + \cfrac{1}{\ddots}}}$$
written as $[a_0; a_1, a_2, \ldots]$.

### Properties
- Rational $\iff$ finite continued fraction
- Best rational approximations are convergents $p_k/q_k$
- $p_k = a_k p_{k-1} + p_{k-2}$, $q_k = a_k q_{k-1} + q_{k-2}$

---

## 4️⃣ Stern-Brocot Tree

A binary tree containing all positive rationals in lowest terms, ordered.

### Construction
- Root: $1/1$
- Between $a/b$ and $c/d$, insert mediant $(a+c)/(b+d)$
- Start with sentinels $0/1$ and $1/0$

### Applications
- Finding best rational approximation with bounded denominator
- Solving Diophantine inequalities

---

## 5️⃣ Farey Sequence

$F_n$ = sequence of all fractions $a/b$ with $0 \leq a/b \leq 1$, $b \leq n$, in ascending order.

**Property:** If $a/b$ and $c/d$ are consecutive in $F_n$, then $bc - ad = 1$.

---

## 📁 Files in This Section

| File | Description |
|------|-------------|
| [01_Floor_Sum.cpp](01_Floor_Sum.cpp) | Floor sum in O(log m), block decomposition |
| [02_Continued_Fractions.cpp](02_Continued_Fractions.cpp) | CF representation, convergents |
| [03_Stern_Brocot.cpp](03_Stern_Brocot.cpp) | Stern-Brocot tree, best approximation |

---

## 🎯 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [Floor Sum](https://atcoder.jp/contests/practice2/tasks/practice2_c) | AtCoder Library | Floor sum |
| [Stern-Brocot](https://codeforces.com/problemset/problem/802/C) | CF 802C | Continued fractions |
| 🟢 [Sum of Divisors](https://cses.fi/problemset/task/1082) | CSES | Floor block decomposition |
| 🟢 [Common Divisors](https://cses.fi/problemset/task/1081) | CSES | Floor/divisor tricks |

---

