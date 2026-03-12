# 📘 Level 6 — Prime Generation (Sieves)

> **Generating all primes up to N efficiently.** The sieve is the bread and butter of number theory in CP.  
> _Reference: [cp-algorithms.com — Sieve of Eratosthenes](https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html)_

---

## 📋 Topics Covered

| # | Topic | Time | Space | Notes |
|---|-------|------|-------|-------|
| 1 | Trial Division | O(√n) per number | O(1) | Single number check |
| 2 | Sieve of Eratosthenes | O(n log log n) | O(n) | Classic sieve |
| 3 | Linear Sieve | O(n) | O(n) | Also gives SPF |
| 4 | Segmented Sieve | O(n log log n) | O(√n) | Primes in [L, R] |

---

## 1️⃣ Trial Division — O(√n)

### Algorithm
To check if $n$ is prime, test all divisors from 2 to $\sqrt{n}$.

**Why √n?** If $n = a \times b$ with $a \leq b$, then $a \leq \sqrt{n}$.

```
is_prime(n):
    if n < 2: return false
    for d = 2 to √n:
        if d | n: return false
    return true
```

---

## 2️⃣ Sieve of Eratosthenes

### Idea
Mark all composite numbers by crossing out multiples of each prime.

### Algorithm
```
sieve(N):
    is_prime[0..N] = true
    is_prime[0] = is_prime[1] = false
    for p = 2 to √N:
        if is_prime[p]:
            for j = p² to N step p:    // start from p², not 2p
                is_prime[j] = false
```

### Why start from $p^2$?
All smaller multiples $2p, 3p, \ldots, (p-1)p$ have already been marked by smaller primes.

### Dry Run: Sieve up to 30

```
Initial: 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30

p=2: cross 4,6,8,10,12,14,16,18,20,22,24,26,28,30
     → 2 3 . 5 . 7 . 9 . 11 . 13 . 15 . 17 . 19 . 21 . 23 . 25 . 27 . 29 .

p=3: cross 9,15,21,27
     → 2 3 . 5 . 7 . . . 11 . 13 . . . 17 . 19 . . . 23 . 25 . . . 29 .

p=5: cross 25
     → 2 3 . 5 . 7 . . . 11 . 13 . . . 17 . 19 . . . 23 . . . . . 29 .

p>√30≈5.47: STOP

Primes: 2, 3, 5, 7, 11, 13, 17, 19, 23, 29  ✓
```

### Complexity: $O(n \log \log n)$

**Proof sketch:**
> Work = $\sum_{p \text{ prime} \leq n} \frac{n}{p} = n \sum_{p \leq n} \frac{1}{p} \approx n \ln(\ln n)$  
> By Mertens' theorem: $\sum_{p \leq n} 1/p \approx \ln \ln n + M$ where $M \approx 0.2615$. ∎

---

## 3️⃣ Linear Sieve — O(n)

### Key Idea
Each composite number is marked **exactly once** by its **smallest prime factor (SPF)**.

### Algorithm
```
linear_sieve(N):
    spf[0..N] = 0     // smallest prime factor
    primes = []
    
    for i = 2 to N:
        if spf[i] == 0:     // i is prime
            spf[i] = i
            primes.append(i)
        
        for p in primes:
            if p > spf[i] or p*i > N: break
            spf[p * i] = p
```

### Why $O(n)$?
Each number $n$ is only marked when processing $n / \text{spf}(n)$ with prime $\text{spf}(n)$.

### Bonus: O(log n) Factorization
Using SPF, factorize any number by repeatedly dividing by spf[n]:
```
while n > 1:
    print spf[n]
    n /= spf[n]
```

---

## 4️⃣ Segmented Sieve

### Problem
Find primes in range $[L, R]$ where $R$ can be up to $10^{12}$ but $R - L \leq 10^6$.

### Algorithm
1. Sieve all primes up to $\sqrt{R}$ using regular sieve.
2. For each prime $p \leq \sqrt{R}$, mark multiples of $p$ in $[L, R]$.
3. Starting point: first multiple of $p$ that is $\geq L$ = $\lceil L/p \rceil \times p$.

### Complexity
- Time: $O(\sqrt{R} + (R-L) \log \log R)$
- Space: $O(\sqrt{R} + (R-L))$

---

## 📁 Files in This Section

| File | Description |
|------|-------------|
| [01_Trial_Division.cpp](01_Trial_Division.cpp) | Basic primality check |
| [02_Sieve_Of_Eratosthenes.cpp](02_Sieve_Of_Eratosthenes.cpp) | Classic sieve with dry run |
| [03_Linear_Sieve.cpp](03_Linear_Sieve.cpp) | O(n) sieve with SPF |
| [04_Segmented_Sieve.cpp](04_Segmented_Sieve.cpp) | Primes in range [L, R] |

---

## 🎯 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [Count Primes](https://leetcode.com/problems/count-primes/) | LC 204 | Sieve |
| [PRIME1](https://www.spoj.com/problems/PRIME1/) | SPOJ | Segmented sieve |
| [T-primes](https://codeforces.com/problemset/problem/230/B) | CF 230B | Sieve + perfect square |
| [Almost Prime](https://codeforces.com/problemset/problem/26/A) | CF 26A | Sieve + factor count |
| [Sieve of Eratosthenes](https://practice.geeksforgeeks.org/problems/sieve-of-eratosthenes/) | GFG | Basic sieve |
| 🟢 [Counting Divisors](https://cses.fi/problemset/task/1713) | CSES | Sieve + factor count |
| 🟢 [Prime Multiples](https://cses.fi/problemset/task/2185) | CSES | IE with prime factors |

---

