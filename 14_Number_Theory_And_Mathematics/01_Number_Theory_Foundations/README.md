# 📘 Level 0 — Number System & Divisibility

> **The foundation of all number theory.** Every concept in competitive programming builds upon these ideas.  
> _Reference: [cp-algorithms.com — Algebra](https://cp-algorithms.com/algebra/)_

---

## 📋 Topics Covered

| # | Topic | Key Idea |
|---|-------|----------|
| 1 | Integer Properties | Even/odd, positive/negative, floor/ceil |
| 2 | Divisibility Rules | When does a \| b? |
| 3 | Prime vs Composite | Fundamental classification |
| 4 | Fundamental Theorem of Arithmetic | Unique prime factorization |
| 5 | Prime Factorization | Breaking n into prime powers |
| 6 | Divisor Count & Divisor Sum | τ(n) and σ(n) formulas |

---

## 1️⃣ Integer Properties

### Definition
The set of integers is $\mathbb{Z} = \{..., -2, -1, 0, 1, 2, ...\}$.

**Key Properties:**
- **Closure:** If $a, b \in \mathbb{Z}$, then $a + b, a - b, a \times b \in \mathbb{Z}$
- **Well-ordering principle:** Every non-empty subset of positive integers has a least element
- **Division algorithm:** For any $a \in \mathbb{Z}$ and $d > 0$, there exist unique $q, r$ such that:
  $$a = d \cdot q + r, \quad 0 \leq r < d$$

### Floor and Ceiling
- $\lfloor x \rfloor$ = largest integer $\leq x$
- $\lceil x \rceil$ = smallest integer $\geq x$
- $\lfloor 7/3 \rfloor = 2, \quad \lceil 7/3 \rceil = 3$

**CP Trick:** In C++, integer division truncates toward zero:
- `7 / 3 = 2` (same as floor for positives)
- `-7 / 3 = -2` (NOT floor! floor would be -3)
- For ceiling of positive a/b: `(a + b - 1) / b`

---

## 2️⃣ Divisibility

### Definition
We say **$a$ divides $b$** (written $a \mid b$) if there exists an integer $k$ such that:
$$b = a \cdot k$$

- $3 \mid 12$ because $12 = 3 \times 4$
- $5 \nmid 12$ because no integer $k$ satisfies $12 = 5k$

### Properties of Divisibility

**Theorem 1:** For all integers $a, b, c$:
1. $a \mid a$ (reflexivity)
2. If $a \mid b$ and $b \mid c$, then $a \mid c$ (transitivity)
3. If $a \mid b$ and $a \mid c$, then $a \mid (bx + cy)$ for any integers $x, y$ (linearity)
4. If $a \mid b$ and $b \neq 0$, then $|a| \leq |b|$
5. If $a \mid b$ and $b \mid a$, then $|a| = |b|$

**Proof of Property 3 (Linearity):**
> If $a \mid b$, then $b = a \cdot k_1$ for some integer $k_1$.  
> If $a \mid c$, then $c = a \cdot k_2$ for some integer $k_2$.  
> Then $bx + cy = a \cdot k_1 \cdot x + a \cdot k_2 \cdot y = a(k_1 x + k_2 y)$.  
> Since $k_1 x + k_2 y$ is an integer, $a \mid (bx + cy)$. ∎

### Divisibility Rules (Quick Reference)

| Divisor | Rule | Example |
|---------|------|---------|
| 2 | Last digit is even | 1234 → 4 is even ✓ |
| 3 | Digit sum divisible by 3 | 123 → 1+2+3=6, 3\|6 ✓ |
| 4 | Last 2 digits divisible by 4 | 1324 → 24/4=6 ✓ |
| 5 | Last digit is 0 or 5 | 125 → ends in 5 ✓ |
| 6 | Divisible by both 2 and 3 | 126 → even, 1+2+6=9, 3\|9 ✓ |
| 7 | Double last digit, subtract from rest | 371 → 37-2=35, 7\|35 ✓ |
| 8 | Last 3 digits divisible by 8 | 1024 → 024/8=3 ✓ |
| 9 | Digit sum divisible by 9 | 729 → 7+2+9=18, 9\|18 ✓ |
| 11 | Alternating digit sum divisible by 11 | 121 → 1-2+1=0, 11\|0 ✓ |

---

## 3️⃣ Prime vs Composite Numbers

### Definition
An integer $p > 1$ is **prime** if its only positive divisors are $1$ and $p$.  
An integer $n > 1$ that is not prime is **composite** (it has a divisor $d$ with $1 < d < n$).

**Note:** 1 is neither prime nor composite.

### First few primes
2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, ...

### Theorem: Infinitude of Primes (Euclid)

**Statement:** There are infinitely many prime numbers.

**Proof (by contradiction):**
> Assume there are finitely many primes: $p_1, p_2, \ldots, p_k$.  
> Consider the number $N = p_1 \cdot p_2 \cdot \ldots \cdot p_k + 1$.  
> For each prime $p_i$, we have $N \mod p_i = 1 \neq 0$.  
> So none of $p_1, \ldots, p_k$ divides $N$.  
> But $N > 1$, so $N$ must have a prime factor — contradiction!  
> Therefore, there are infinitely many primes. ∎

### Theorem: Every composite $n$ has a prime factor $\leq \sqrt{n}$

**Proof:**
> If $n$ is composite, then $n = a \cdot b$ where $1 < a \leq b < n$.  
> If $a > \sqrt{n}$, then $b \geq a > \sqrt{n}$, so $a \cdot b > n$ — contradiction.  
> Therefore $a \leq \sqrt{n}$.  
> Since $a > 1$, it has a prime factor $p \leq a \leq \sqrt{n}$, and $p \mid n$. ∎

**CP Application:** To check if $n$ is prime, we only need to test divisors up to $\sqrt{n}$. This gives $O(\sqrt{n})$ primality testing.

---

## 4️⃣ Fundamental Theorem of Arithmetic (FTA)

### Statement
Every integer $n > 1$ can be represented **uniquely** as a product of prime powers:

$$n = p_1^{a_1} \cdot p_2^{a_2} \cdot \ldots \cdot p_k^{a_k}$$

where $p_1 < p_2 < \ldots < p_k$ are primes and $a_i \geq 1$.

### Proof (Existence — by strong induction)

> **Base case:** $n = 2$ is prime, so $n = 2^1$. ✓  
> **Inductive step:** Assume every integer $2 \leq m < n$ can be written as a product of primes.  
> - If $n$ is prime: $n = n^1$. Done.  
> - If $n$ is composite: $n = a \cdot b$ where $1 < a, b < n$.  
>   By the inductive hypothesis, both $a$ and $b$ are products of primes.  
>   So $n = a \cdot b$ is also a product of primes. ∎

### Proof (Uniqueness — by contradiction using Euclid's Lemma)

> **Euclid's Lemma:** If $p$ is prime and $p \mid ab$, then $p \mid a$ or $p \mid b$.  
>  
> Suppose $n = p_1^{a_1} \cdots p_k^{a_k} = q_1^{b_1} \cdots q_m^{b_m}$ are two factorizations.  
> Since $p_1 \mid n = q_1^{b_1} \cdots q_m^{b_m}$, by Euclid's Lemma repeatedly, $p_1 \mid q_j$ for some $j$.  
> Since $q_j$ is prime, $p_1 = q_j$. By induction, the factorizations are identical. ∎

### Dry Run: Factor 360

```
360 ÷ 2 = 180    (count of 2: 1)
180 ÷ 2 = 90     (count of 2: 2)
90  ÷ 2 = 45     (count of 2: 3)
45  ÷ 3 = 15     (count of 3: 1)
15  ÷ 3 = 5      (count of 3: 2)
5   ÷ 5 = 1      (count of 5: 1)

Result: 360 = 2³ × 3² × 5¹
```

---

## 5️⃣ Prime Factorization Algorithm

### Trial Division — O(√n)

```
function factorize(n):
    factors = {}
    for d = 2 to √n:
        while d | n:
            factors[d] += 1
            n = n / d
    if n > 1:
        factors[n] = 1    // n is a remaining prime factor
    return factors
```

### Dry Run: Factorize n = 84

```
d = 2: 84 % 2 == 0 → n = 42, factors = {2: 1}
       42 % 2 == 0 → n = 21, factors = {2: 2}
       21 % 2 != 0 → move on
d = 3: 21 % 3 == 0 → n = 7, factors = {2: 2, 3: 1}
        7 % 3 != 0 → move on
d = 4: 4 > √7 ≈ 2.65 → STOP loop
n = 7 > 1, so add: factors = {2: 2, 3: 1, 7: 1}

Answer: 84 = 2² × 3 × 7 ✓
```

---

## 6️⃣ Divisor Count and Divisor Sum

### Given $n = p_1^{a_1} \cdot p_2^{a_2} \cdot \ldots \cdot p_k^{a_k}$:

### Number of Divisors — τ(n)

$$\tau(n) = (a_1 + 1)(a_2 + 1) \cdots (a_k + 1)$$

**Proof:**
> Any divisor of $n$ has the form $p_1^{e_1} \cdot p_2^{e_2} \cdots p_k^{e_k}$ where $0 \leq e_i \leq a_i$.  
> For each $p_i$, there are $(a_i + 1)$ choices for $e_i$.  
> By the multiplication principle, total divisors = $\prod (a_i + 1)$. ∎

### Sum of Divisors — σ(n)

$$\sigma(n) = \prod_{i=1}^{k} \frac{p_i^{a_i+1} - 1}{p_i - 1}$$

**Proof:**
> $\sigma(n) = \sum_{d \mid n} d = \prod_{i=1}^{k} (1 + p_i + p_i^2 + \cdots + p_i^{a_i})$  
> The inner sum is a geometric series: $\frac{p_i^{a_i+1} - 1}{p_i - 1}$. ∎

### Dry Run: n = 360 = 2³ × 3² × 5¹

**Divisor count:**
$$\tau(360) = (3+1)(2+1)(1+1) = 4 \times 3 \times 2 = 24$$

**Divisor sum:**
$$\sigma(360) = \frac{2^4 - 1}{2 - 1} \times \frac{3^3 - 1}{3 - 1} \times \frac{5^2 - 1}{5 - 1} = 15 \times 13 \times 6 = 1170$$

**Verification:** Divisors of 360 = {1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15, 18, 20, 24, 30, 36, 40, 45, 60, 72, 90, 120, 180, 360}  
Count = 24 ✓, Sum = 1170 ✓

---

## 📁 Files in This Section

| File | Description |
|------|-------------|
| [01_Divisibility_And_Properties.cpp](01_Divisibility_And_Properties.cpp) | Divisibility check, GCD basics, division algorithm |
| [02_Prime_Factorization.cpp](02_Prime_Factorization.cpp) | Trial division factorization with examples |
| [03_Divisor_Count_And_Sum.cpp](03_Divisor_Count_And_Sum.cpp) | τ(n) and σ(n) computation |

---

## 🎯 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [Almost All Divisors](https://codeforces.com/problemset/problem/1165/D) | CF 1165D | Divisor enumeration |
| [K-Factorization](https://codeforces.com/problemset/problem/797/A) | CF 797A | Prime factorization |
| [Different Divisors](https://codeforces.com/problemset/problem/1474/B) | CF 1474B | Consecutive primes |
| [Count Primes](https://leetcode.com/problems/count-primes/) | LC 204 | Sieve |
| [Largest Prime Factor](https://practice.geeksforgeeks.org/problems/largest-prime-factor/) | GFG | Trial division |
| 🟢 [Counting Divisors](https://cses.fi/problemset/task/1713) | CSES | τ(n) for multiple queries |
| 🟢 [Divisor Analysis](https://cses.fi/problemset/task/2182) | CSES | τ, σ, product of divisors |
| 🟢 [Sum of Divisors](https://cses.fi/problemset/task/1082) | CSES | Σ σ(i), floor block decomp |

---

