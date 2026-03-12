# 🏆 Number Theory — Problem Cheat Sheet

> **Curated problems from top CP platforms sorted by topic**  
> Platforms: Codeforces (CF), CodeChef (CC), AtCoder (AC), LeetCode (LC), GFG, SPOJ, **CSES**

---

## 📌 How to Use This Sheet

1. Solve problems **in order** (topic-wise, then difficulty-wise)
2. After solving, note the technique used
3. ⭐ = Must solve, 🔥 = Frequently asked, 💎 = Contest classic, 🟢 = CSES

---

## 🟢 CSES Mathematics Section — Complete Problem List

> **CSES Problem Set → Mathematics** is one of the BEST problem sets for NT practice.  
> Link: [https://cses.fi/problemset/list/](https://cses.fi/problemset/list/)

### Divisibility & Primes

| # | Problem | CSES Link | Technique | Section |
|---|---------|-----------|-----------|---------|
| 1 | 🟢 Counting Divisors | [Link](https://cses.fi/problemset/task/1713) | Sieve / trial division | 01, 07 |
| 2 | 🟢 Common Divisors | [Link](https://cses.fi/problemset/task/1081) | Max GCD in array | 02 |
| 3 | 🟢 Divisor Analysis | [Link](https://cses.fi/problemset/task/2182) | τ(n), σ(n), product of divisors | 01, 10 |
| 4 | 🟢 Prime Multiples | [Link](https://cses.fi/problemset/task/2185) | Inclusion-Exclusion + primes | 07, 13 |
| 5 | 🟢 Sum of Divisors | [Link](https://cses.fi/problemset/task/1082) | Floor block decomposition | 10, 20 |

### Exponentiation & Modular Arithmetic

| # | Problem | CSES Link | Technique | Section |
|---|---------|-----------|-----------|---------|
| 6 | 🟢 Exponentiation | [Link](https://cses.fi/problemset/task/1095) | Binary exponentiation | 03 |
| 7 | 🟢 Exponentiation II | [Link](https://cses.fi/problemset/task/1712) | a^(b^c) mod m, Euler's thm | 03, 04 |
| 8 | 🟢 Fibonacci Numbers | [Link](https://cses.fi/problemset/task/1722) | Matrix exponentiation | 03 |

### Combinatorics

| # | Problem | CSES Link | Technique | Section |
|---|---------|-----------|-----------|---------|
| 9 | 🟢 Binomial Coefficients | [Link](https://cses.fi/problemset/task/1079) | nCr mod p (factorial precomp) | 12 |
| 10 | 🟢 Creating Strings II | [Link](https://cses.fi/problemset/task/1715) | Multinomial coefficient | 12 |
| 11 | 🟢 Distributing Apples | [Link](https://cses.fi/problemset/task/1716) | Stars and Bars | 12 |
| 12 | 🟢 Christmas Party | [Link](https://cses.fi/problemset/task/1717) | Derangements | 12, 13 |
| 13 | 🟢 Bracket Sequences I | [Link](https://cses.fi/problemset/task/2064) | Catalan numbers | 12 |
| 14 | 🟢 Bracket Sequences II | [Link](https://cses.fi/problemset/task/2187) | Catalan + prefix | 12 |

### GCD, Euler Totient & Advanced

| # | Problem | CSES Link | Technique | Section |
|---|---------|-----------|-----------|---------|
| 15 | 🟢 Counting Coprime Pairs | [Link](https://cses.fi/problemset/task/2417) | Euler totient / Möbius | 10, 14 |
| 16 | 🟢 Counting Necklaces | [Link](https://cses.fi/problemset/task/2209) | Burnside's lemma + φ | 10, 12 |
| 17 | 🟢 Counting Grids | [Link](https://cses.fi/problemset/task/2210) | Burnside's lemma | 12 |
| 18 | 🟢 Josephus Problem I | [Link](https://cses.fi/problemset/task/2162) | Josephus recurrence | — |
| 19 | 🟢 Josephus Problem II | [Link](https://cses.fi/problemset/task/2163) | Josephus + BIT/segment tree | — |
| 20 | 🟢 Throwing Dice | [Link](https://cses.fi/problemset/task/1096) | Matrix exponentiation | 03 |
| 21 | 🟢 Graph Paths I | [Link](https://cses.fi/problemset/task/1202) | Matrix exponentiation | 03 |
| 22 | 🟢 Graph Paths II | [Link](https://cses.fi/problemset/task/1203) | Matrix exp + shortest | 03 |
| 23 | 🟢 Nim Game I | [Link](https://cses.fi/problemset/task/1730) | XOR / Sprague-Grundy | — |
| 24 | 🟢 Nim Game II | [Link](https://cses.fi/problemset/task/1098) | Sprague-Grundy | — |
| 25 | 🟢 Stair Game | [Link](https://cses.fi/problemset/task/1099) | Nim variant | — |

### Polynomial & NTT

| # | Problem | CSES Link | Technique | Section |
|---|---------|-----------|-----------|---------|
| 26 | 🟢 Polynomial Queries | [Link](https://cses.fi/problemset/task/1736) | Segment tree + poly | 18 |

---

---

## 01 — Number System & Divisibility

| # | Problem | Platform | Difficulty | Technique | Link |
|---|---------|----------|------------|-----------|------|
| 1 | ⭐ Almost All Divisors | CF 1165D | 1400 | Divisor enumeration | [Link](https://codeforces.com/problemset/problem/1165/D) |
| 2 | ⭐ K-Factorization | CF 797A | 1100 | Prime factorization | [Link](https://codeforces.com/problemset/problem/797/A) |
| 3 | Different Divisors | CF 1474B | 1100 | Consecutive primes | [Link](https://codeforces.com/problemset/problem/1474/B) |
| 4 | 🔥 Count Primes | LC 204 | Medium | Sieve + counting | [Link](https://leetcode.com/problems/count-primes/) |
| 5 | Sherlock and Divisors | CC | Easy | Divisor count parity | [Link](https://www.codechef.com/problems/DIVSUBS) |
| 6 | Divisor Summation | SPOJ DIVSUM | Easy | σ(n) computation | [Link](https://www.spoj.com/problems/DIVSUM/) |
| 7 | 💎 Noldbach Problem | CF 17A | 1000 | Prime + Goldbach | [Link](https://codeforces.com/problemset/problem/17/A) |
| 8 | Largest Prime Factor | GFG | Easy | Trial division | [Link](https://practice.geeksforgeeks.org/problems/largest-prime-factor/) |
| 9 | 🟢 Counting Divisors | CSES | Medium | τ(n) via trial division | [Link](https://cses.fi/problemset/task/1713) |
| 10 | 🟢 Divisor Analysis | CSES | Hard | τ,σ,product of divisors | [Link](https://cses.fi/problemset/task/2182) |
| 11 | 🟢 Sum of Divisors | CSES | Hard | Σ_{i=1}^{n} σ(i) | [Link](https://cses.fi/problemset/task/1082) |

---

## 02 — GCD & Euclidean Algorithms

| # | Problem | Platform | Difficulty | Technique | Link |
|---|---------|----------|------------|-----------|------|
| 1 | ⭐ GCD Problem | CF 1617B | 900 | GCD properties | [Link](https://codeforces.com/problemset/problem/1617/B) |
| 2 | ⭐ Gregor and Cryptography | CF 1549A | 800 | GCD + division | [Link](https://codeforces.com/problemset/problem/1549/A) |
| 3 | 🔥 GCD of Array | LC 1979 | Easy | Iterative GCD | [Link](https://leetcode.com/problems/find-greatest-common-divisor-of-array/) |
| 4 | GCD Queries | CF 1609D | 1900 | Interactive GCD | [Link](https://codeforces.com/problemset/problem/1609/D) |
| 5 | 💎 GCD Table | CF 582A | 1700 | Constructive + GCD | [Link](https://codeforces.com/problemset/problem/582/A) |
| 6 | LCM Challenge | CF 235A | 1600 | LCM maximization | [Link](https://codeforces.com/problemset/problem/235/A) |
| 7 | CEQU - Crucial Equation | SPOJ | Easy | Extended Euclidean | [Link](https://www.spoj.com/problems/CEQU/) |
| 8 | GCD & LCM | GFG | Medium | GCD-LCM relationship | [Link](https://practice.geeksforgeeks.org/problems/lcm-and-gcd/) |
| 9 | 🟢 Common Divisors | CSES | Medium | Max GCD in array | [Link](https://cses.fi/problemset/task/1081) |

---

## 03 — Binary Exponentiation

| # | Problem | Platform | Difficulty | Technique | Link |
|---|---------|----------|------------|-----------|------|
| 1 | ⭐ Pow(x, n) | LC 50 | Medium | Binary exp | [Link](https://leetcode.com/problems/powx-n/) |
| 2 | ⭐ Zuma and His Army | CF 999A | 1600 | Modular exp | [Link](https://codeforces.com/problemset/problem/999/A) |
| 3 | 🔥 Matrix Exponentiation | CF 185A | 1500 | Matrix exp + Fibonacci | [Link](https://codeforces.com/problemset/problem/185/A) |
| 4 | LASTDIG - The Last Digit | SPOJ | Easy | a^b mod 10 | [Link](https://www.spoj.com/problems/LASTDIG/) |
| 5 | 💎 Magic Gems | CF 1117D | 1600 | Matrix exp + recurrence | [Link](https://codeforces.com/problemset/problem/1117/D) |
| 6 | Power of Two | CC | Medium | Binary exp variants | [Link](https://www.codechef.com/problems/TWOPOWER) |
| 7 | Super Pow | LC 372 | Medium | Modular exp | [Link](https://leetcode.com/problems/super-pow/) |
| 8 | 🟢 Exponentiation | CSES | Easy | a^b mod 10^9+7 | [Link](https://cses.fi/problemset/task/1095) |
| 9 | 🟢 Exponentiation II | CSES | Medium | a^(b^c) mod m, Euler thm | [Link](https://cses.fi/problemset/task/1712) |
| 10 | 🟢 Fibonacci Numbers | CSES | Medium | Matrix exponentiation | [Link](https://cses.fi/problemset/task/1722) |
| 11 | 🟢 Throwing Dice | CSES | Medium | Matrix exp + recurrence | [Link](https://cses.fi/problemset/task/1096) |
| 12 | 🟢 Graph Paths I | CSES | Hard | Matrix exp + adj matrix | [Link](https://cses.fi/problemset/task/1202) |

---

## 04 — Modular Arithmetic

| # | Problem | Platform | Difficulty | Technique | Link |
|---|---------|----------|------------|-----------|------|
| 1 | ⭐ Modular Arithmetic | CF 913A | 900 | Basic mod | [Link](https://codeforces.com/problemset/problem/913/A) |
| 2 | ⭐ Add Modulo 10 | CF 1714C | 1100 | Mod cycle detection | [Link](https://codeforces.com/problemset/problem/1714/C) |
| 3 | 🔥 Remainder Game | CF 687B | 1800 | Modular properties | [Link](https://codeforces.com/problemset/problem/687/B) |
| 4 | Modulo Sum | CF 577B | 1900 | Pigeonhole + mod | [Link](https://codeforces.com/problemset/problem/577/B) |
| 5 | 💎 Product of Three Numbers | CF 1294C | 1300 | Division + mod | [Link](https://codeforces.com/problemset/problem/1294/C) |
| 6 | Modular Exponentiation | GFG | Medium | Mod arithmetic | [Link](https://practice.geeksforgeeks.org/problems/modular-exponentiation/) |
| 7 | 🟢 Exponentiation II | CSES | Medium | Euler's theorem in action | [Link](https://cses.fi/problemset/task/1712) |

---

## 05 — Modular Inverse

| # | Problem | Platform | Difficulty | Technique | Link |
|---|---------|----------|------------|-----------|------|
| 1 | ⭐ Modular Inverse | SPOJ MODINV | Easy | Extended Euclid | [Link](https://www.spoj.com/problems/MODINV/) |
| 2 | 🔥 Paths on a Grid | CF 697C | 1600 | nCr with mod inverse | [Link](https://codeforces.com/problemset/problem/697/C) |
| 3 | Expected Value | CF 1187E | 2000 | Mod inverse in probability | [Link](https://codeforces.com/problemset/problem/1187/E) |
| 4 | 💎 Binomial Coefficient | SPOJ | Medium | Mod inverse + nCr | [Link](https://www.spoj.com/problems/BCOEF/) |
| 5 | Fraction to Decimal | LC 166 | Medium | Mod inverse concept | [Link](https://leetcode.com/problems/fraction-to-recurring-decimal/) |

---

## 06 — Linear Diophantine Equations

| # | Problem | Platform | Difficulty | Technique | Link |
|---|---------|----------|------------|-----------|------|
| 1 | ⭐ CEQU | SPOJ | Easy | ax + by = c | [Link](https://www.spoj.com/problems/CEQU/) |
| 2 | 🔥 Indefinite Equation | CF 1244C | 1300 | Diophantine + bounds | [Link](https://codeforces.com/problemset/problem/1244/C) |
| 3 | Frog Position | CF 1146D | 2000 | Extended Euclid app | [Link](https://codeforces.com/problemset/problem/1146/D) |
| 4 | 💎 Chicken McNugget | Classic | Medium | Frobenius / coin problem | — |
| 5 | Water Testing | AC abc186_e | Medium | Modular linear equation | [Link](https://atcoder.jp/contests/abc186/tasks/abc186_e) |

---

## 07 — Prime Generation (Sieves)

| # | Problem | Platform | Difficulty | Technique | Link |
|---|---------|----------|------------|-----------|------|
| 1 | ⭐ Count Primes | LC 204 | Medium | Sieve of Eratosthenes | [Link](https://leetcode.com/problems/count-primes/) |
| 2 | ⭐ PRIME1 - Prime Generator | SPOJ | Medium | Segmented sieve | [Link](https://www.spoj.com/problems/PRIME1/) |
| 3 | 🔥 Printing Some Primes | SPOJ TDPRIMES | Medium | Sieve | [Link](https://www.spoj.com/problems/TDPRIMES/) |
| 4 | Almost Prime | CF 26A | 900 | Sieve + factor count | [Link](https://codeforces.com/problemset/problem/26/A) |
| 5 | 💎 Prime Distance | CF 1076D | 1900 | Segmented sieve | [Link](https://codeforces.com/problemset/problem/1076/D) |
| 6 | T-primes | CF 230B | 1300 | Sieve + perfect square | [Link](https://codeforces.com/problemset/problem/230/B) |
| 7 | Goldbach Conjecture | SPOJ GOLDB | Medium | Sieve + check | [Link](https://www.spoj.com/problems/GOLDB/) |
| 8 | Sieve of Eratosthenes | GFG | Easy | Basic sieve | [Link](https://practice.geeksforgeeks.org/problems/sieve-of-eratosthenes/) |
| 9 | 🟢 Counting Divisors | CSES | Medium | Sieve + factor count | [Link](https://cses.fi/problemset/task/1713) |
| 10 | 🟢 Prime Multiples | CSES | Medium | IE with primes | [Link](https://cses.fi/problemset/task/2185) |

---

## 08 — Primality Testing

| # | Problem | Platform | Difficulty | Technique | Link |
|---|---------|----------|------------|-----------|------|
| 1 | ⭐ Primes or Not | SPOJ PON | Medium | Miller-Rabin | [Link](https://www.spoj.com/problems/PON/) |
| 2 | 🔥 Primality Test | GFG | Medium | Optimized trial division | [Link](https://practice.geeksforgeeks.org/problems/primality-test/) |
| 3 | Millar Rabin | CC | Hard | Deterministic Miller-Rabin | [Link](https://www.codechef.com/problems/MILRB) |
| 4 | 💎 Large Primes | CF (various) | 2200+ | Miller-Rabin + 128-bit | — |
| 5 | Check Prime | LC 2614 | Easy | Basic primality | [Link](https://leetcode.com/problems/prime-in-diagonal/) |

---

## 09 — Integer Factorization

| # | Problem | Platform | Difficulty | Technique | Link |
|---|---------|----------|------------|-----------|------|
| 1 | ⭐ Factorization | SPOJ FACT0 | Medium | Pollard's Rho | [Link](https://www.spoj.com/problems/FACT0/) |
| 2 | 🔥 Smallest Prime Factor | CF 1366D | 1800 | SPF sieve | [Link](https://codeforces.com/problemset/problem/1366/D) |
| 3 | Number of Divisors | SPOJ NDIV | Medium | Factorize + count | [Link](https://www.spoj.com/problems/NDIV/) |
| 4 | 💎 Dima and Lisa | CF 584D | 1800 | Goldbach + factorization | [Link](https://codeforces.com/problemset/problem/584/D) |
| 5 | Ugly Number | LC 263 | Easy | Factor checking | [Link](https://leetcode.com/problems/ugly-number/) |

---

## 10 — Number-Theoretic Functions

| # | Problem | Platform | Difficulty | Technique | Link |
|---|---------|----------|------------|-----------|------|
| 1 | ⭐ Euler Totient Function | SPOJ ETF | Medium | φ(n) computation | [Link](https://www.spoj.com/problems/ETF/) |
| 2 | ⭐ GCD Sum | CF 1613D | 1800 | φ(n) + Euler product | [Link](https://codeforces.com/problemset/problem/1613/D) |
| 3 | 🔥 Totient Sum | SPOJ TTTTTTT | Hard | Euler totient sieve | [Link](https://www.spoj.com/problems/TTTTTTT/) |
| 4 | Divisor Sum | SPOJ DIVSUM | Easy | σ(n) | [Link](https://www.spoj.com/problems/DIVSUM/) |
| 5 | 💎 Power Tower | CF 906D | 2400 | Euler's theorem chain | [Link](https://codeforces.com/problemset/problem/906/D) |
| 6 | Count of Coprime Pairs | GFG | Medium | Euler totient | [Link](https://practice.geeksforgeeks.org/problems/euler-totient/) |
| 7 | 🟢 Divisor Analysis | CSES | Hard | τ, σ, product of divisors | [Link](https://cses.fi/problemset/task/2182) |
| 8 | 🟢 Sum of Divisors | CSES | Hard | Σσ(i) via block decomp | [Link](https://cses.fi/problemset/task/1082) |
| 9 | 🟢 Counting Coprime Pairs | CSES | Hard | φ / Möbius application | [Link](https://cses.fi/problemset/task/2417) |

---

## 11 — Chinese Remainder Theorem

| # | Problem | Platform | Difficulty | Technique | Link |
|---|---------|----------|------------|-----------|------|
| 1 | ⭐ Remainder | AC abc193_e | Medium | CRT | [Link](https://atcoder.jp/contests/abc193/tasks/abc193_e) |
| 2 | 🔥 Strange Function | CF 1542C | 1600 | CRT thinking | [Link](https://codeforces.com/problemset/problem/1542/C) |
| 3 | Hacking the Random Number Generator | CC | Hard | CRT application | — |
| 4 | 💎 Garner's Algorithm | CF (various) | 2200+ | Big number CRT | — |
| 5 | Remainder Problem | CF 1165E | 2100 | Modular thinking | [Link](https://codeforces.com/problemset/problem/1165/E) |

---

## 12 — Combinatorics

| # | Problem | Platform | Difficulty | Technique | Link |
|---|---------|----------|------------|-----------|------|
| 1 | ⭐ Unique Paths | LC 62 | Medium | nCr | [Link](https://leetcode.com/problems/unique-paths/) |
| 2 | ⭐ Pascal's Triangle | LC 118 | Easy | Binomial coefficients | [Link](https://leetcode.com/problems/pascals-triangle/) |
| 3 | 🔥 Binomial Coefficients | CF 785D | 2000 | nCr mod p | [Link](https://codeforces.com/problemset/problem/785/D) |
| 4 | 🔥 Count Balanced Parentheses | Classic | Medium | Catalan numbers | — |
| 5 | 💎 Randomized BST | LC 96 | Medium | Catalan | [Link](https://leetcode.com/problems/unique-binary-search-trees/) |
| 6 | Stars and Bars | CF 553A | 1500 | Stars & bars | [Link](https://codeforces.com/problemset/problem/553/A) |
| 7 | Necklace of Beads | CF 1189D1 | 1600 | Burnside's lemma | [Link](https://codeforces.com/problemset/problem/1189/D1) |
| 8 | Binomial Coefficient | SPOJ BCOEF | Medium | Lucas theorem | [Link](https://www.spoj.com/problems/BCOEF/) |
| 9 | Combination Sum | LC 377 | Medium | Combinatorics DP | [Link](https://leetcode.com/problems/combination-sum-iv/) |
| 10 | 🟢 Binomial Coefficients | CSES | Medium | nCr mod p | [Link](https://cses.fi/problemset/task/1079) |
| 11 | 🟢 Creating Strings II | CSES | Medium | Multinomial coefficient | [Link](https://cses.fi/problemset/task/1715) |
| 12 | 🟢 Distributing Apples | CSES | Medium | Stars and Bars | [Link](https://cses.fi/problemset/task/1716) |
| 13 | 🟢 Christmas Party | CSES | Medium | Derangements | [Link](https://cses.fi/problemset/task/1717) |
| 14 | 🟢 Bracket Sequences I | CSES | Hard | Catalan numbers | [Link](https://cses.fi/problemset/task/2064) |
| 15 | 🟢 Bracket Sequences II | CSES | Hard | Catalan + prefix | [Link](https://cses.fi/problemset/task/2187) |
| 16 | 🟢 Counting Necklaces | CSES | Hard | Burnside + φ(n) | [Link](https://cses.fi/problemset/task/2209) |
| 17 | 🟢 Counting Grids | CSES | Hard | Burnside's lemma | [Link](https://cses.fi/problemset/task/2210) |

---

## 13 — Inclusion-Exclusion Principle

| # | Problem | Platform | Difficulty | Technique | Link |
|---|---------|----------|------------|-----------|------|
| 1 | ⭐ Coprime Count | CF 1462D | 1500 | IE + coprime | [Link](https://codeforces.com/problemset/problem/1462/D) |
| 2 | 🔥 Derangements | CF 340A | 1400 | Derangement formula | [Link](https://codeforces.com/problemset/problem/340/A) |
| 3 | Ugly Numbers | SPOJ | Medium | IE counting | [Link](https://www.spoj.com/problems/UGLY/) |
| 4 | 💎 Coprime Triples | CF 1267G | 2200 | Möbius + IE | [Link](https://codeforces.com/problemset/problem/1267/G) |
| 5 | Number with No Repeated Digits | LC 1012 | Hard | IE + digits | [Link](https://leetcode.com/problems/numbers-with-repeated-digits/) |
| 6 | 🟢 Prime Multiples | CSES | Medium | IE with prime factors | [Link](https://cses.fi/problemset/task/2185) |
| 7 | 🟢 Christmas Party | CSES | Medium | Derangements via IE | [Link](https://cses.fi/problemset/task/1717) |

---

## 14 — Multiplicative Functions

| # | Problem | Platform | Difficulty | Technique | Link |
|---|---------|----------|------------|-----------|------|
| 1 | ⭐ Möbius Function | SPOJ | Medium | μ(n) sieve | — |
| 2 | 🔥 Sum of GCD | CF 1780F | 2300 | Möbius inversion | [Link](https://codeforces.com/problemset/problem/1780/F) |
| 3 | 💎 Coprime Subsequences | CF 803F | 2000 | Möbius function | [Link](https://codeforces.com/problemset/problem/803/F) |
| 4 | GCD Counting | CF 1034A | 2400 | Dirichlet series | [Link](https://codeforces.com/problemset/problem/1034/A) |

---

## 15 — Discrete Logarithm

| # | Problem | Platform | Difficulty | Technique | Link |
|---|---------|----------|------------|-----------|------|
| 1 | ⭐ Discrete Logging | SPOJ DISCRETE | Medium | BSGS | [Link](https://www.spoj.com/problems/DISCRETE/) |
| 2 | 🔥 Discrete Log | CF (Gym) | Hard | Baby-step Giant-step | — |
| 3 | 💎 Modular Equations | CF 495A | 1500 | Discrete log variant | [Link](https://codeforces.com/problemset/problem/495/A) |

---

## 16 — Primitive Roots

| # | Problem | Platform | Difficulty | Technique | Link |
|---|---------|----------|------------|-----------|------|
| 1 | ⭐ Primitive Root | SPOJ | Medium | Finding generators | — |
| 2 | 🔥 Order Finding | CF (various) | 2000+ | Multiplicative order | — |
| 3 | 💎 Discrete Log via Primitive Root | CF | 2200+ | Root + indexing | — |

---

## 17 — Modular Square Root

| # | Problem | Platform | Difficulty | Technique | Link |
|---|---------|----------|------------|-----------|------|
| 1 | ⭐ Square Root Mod | SPOJ SQRMOD | Medium | Tonelli-Shanks | [Link](https://www.spoj.com/problems/SQRMOD/) |
| 2 | 🔥 Quadratic Residues | CF | 2000+ | Euler criterion | — |
| 3 | 💎 Cipolla's Algorithm | Various | Hard | Non-residue | — |

---

## 18 — Polynomial Algorithms

| # | Problem | Platform | Difficulty | Technique | Link |
|---|---------|----------|------------|-----------|------|
| 1 | ⭐ Polynomial Multiplication | GFG | Medium | Naive multiply | [Link](https://practice.geeksforgeeks.org/problems/multiply-two-polynomials/) |
| 2 | 🔥 Lagrange Interpolation | CF 622F | 2400 | Polynomial interpolation | [Link](https://codeforces.com/problemset/problem/622/F) |
| 3 | 💎 Power Sum | CF 837D | 2300 | Generating functions | [Link](https://codeforces.com/problemset/problem/837/D) |

---

## 19 — FFT & NTT

| # | Problem | Platform | Difficulty | Technique | Link |
|---|---------|----------|------------|-----------|------|
| 1 | ⭐ Multiply Strings | LC 43 | Medium | FFT concept | [Link](https://leetcode.com/problems/multiply-strings/) |
| 2 | ⭐ POLYMUL | SPOJ | Hard | FFT | [Link](https://www.spoj.com/problems/POLYMUL/) |
| 3 | 🔥 Convolution | AC ATC001_c | Hard | NTT | [Link](https://atcoder.jp/contests/atc001/tasks/fft_c) |
| 4 | 🔥 Big Number Multiply | CF 632E | 2200 | FFT application | [Link](https://codeforces.com/problemset/problem/632/E) |
| 5 | 💎 Kinetic Energy | CF 993E | 2600 | FFT + counting | [Link](https://codeforces.com/problemset/problem/993/E) |
| 6 | MAXMATCH | SPOJ | Hard | FFT + string | [Link](https://www.spoj.com/problems/MAXMATCH/) |

---

## 20 — Advanced Number Theory

| # | Problem | Platform | Difficulty | Technique | Link |
|---|---------|----------|------------|-----------|------|
| 1 | ⭐ Floor Sum | AC abc283_e | Hard | Floor function sum | [Link](https://atcoder.jp/contests/abc283/tasks/abc283_e) |
| 2 | 🔥 Stern-Brocot | CF 802C | 2100 | Continued fractions | [Link](https://codeforces.com/problemset/problem/802/C) |
| 3 | 💎 Farey Sequence | SPOJ FSEQ | Hard | Euler totient + Farey | [Link](https://www.spoj.com/problems/FSEQ/) |

---

## 21 — ICPC / GM Level

| # | Problem | Platform | Difficulty | Technique | Link |
|---|---------|----------|------------|-----------|------|
| 1 | ⭐ Factorize Large N | CF (Gym) | 2500+ | Pollard-Rho optimized | — |
| 2 | 🔥 CRT System | CF 687C | 2400 | Advanced CRT | [Link](https://codeforces.com/problemset/problem/687/C) |
| 3 | 💎 Sum of Totient | SPOJ GCDEX | Hard | Möbius + convolution | [Link](https://www.spoj.com/problems/GCDEX/) |
| 4 | Generating Function | CF 1548C | 2500 | Formal power series | [Link](https://codeforces.com/problemset/problem/1548/C) |
| 5 | 💎 Project Euler 108+ | PE | Expert | Combined NT techniques | [Link](https://projecteuler.net/) |

---

## 🎯 Recommended Solve Order for Beginners

1. **Start with:** 01 (divisibility) → 02 (GCD) → 07 (sieve) → 03 (fast power) → 04 (modular arith)
2. **Then:** 05 (mod inverse) → 12 (combinatorics) → 06 (Diophantine)
3. **Intermediate:** 08 (Miller-Rabin) → 09 (factorization) → 10 (NT functions) → 13 (IE)
4. **Advanced:** 11 (CRT) → 14 (multiplicative) → 15 (discrete log) → 16 (primitive roots)
5. **Expert:** 17 (mod sqrt) → 18 (polynomials) → 19 (FFT/NTT) → 20–21 (GM/ICPC)

---

## 🟢 CSES Mathematics — Recommended Solve Order

> **Solve these in order for a structured CSES journey**

### Phase 1: Basics (After sections 01–05)
| # | Problem | Why |
|---|---------|-----|
| 1 | [Exponentiation](https://cses.fi/problemset/task/1095) | Binary exp warmup |
| 2 | [Exponentiation II](https://cses.fi/problemset/task/1712) | Euler's theorem application |
| 3 | [Counting Divisors](https://cses.fi/problemset/task/1713) | Trial division / sieve |
| 4 | [Common Divisors](https://cses.fi/problemset/task/1081) | GCD thinking |

### Phase 2: Combinatorics (After sections 07, 12)
| # | Problem | Why |
|---|---------|-----|
| 5 | [Binomial Coefficients](https://cses.fi/problemset/task/1079) | Factorial + mod inverse |
| 6 | [Creating Strings II](https://cses.fi/problemset/task/1715) | Multinomial |
| 7 | [Distributing Apples](https://cses.fi/problemset/task/1716) | Stars and Bars |
| 8 | [Christmas Party](https://cses.fi/problemset/task/1717) | Derangements |
| 9 | [Bracket Sequences I](https://cses.fi/problemset/task/2064) | Catalan numbers |
| 10 | [Bracket Sequences II](https://cses.fi/problemset/task/2187) | Catalan + counting |

### Phase 3: Matrix Exp & NT Functions (After sections 03, 10)
| # | Problem | Why |
|---|---------|-----|
| 11 | [Fibonacci Numbers](https://cses.fi/problemset/task/1722) | Matrix exponentiation |
| 12 | [Throwing Dice](https://cses.fi/problemset/task/1096) | Matrix exp + recurrence |
| 13 | [Graph Paths I](https://cses.fi/problemset/task/1202) | Matrix exp + adjacency |
| 14 | [Divisor Analysis](https://cses.fi/problemset/task/2182) | τ, σ, product of divisors |
| 15 | [Sum of Divisors](https://cses.fi/problemset/task/1082) | Floor block decomposition |

### Phase 4: Advanced (After sections 10, 13, 14)
| # | Problem | Why |
|---|---------|-----|
| 16 | [Prime Multiples](https://cses.fi/problemset/task/2185) | Inclusion-Exclusion |
| 17 | [Counting Coprime Pairs](https://cses.fi/problemset/task/2417) | Möbius / Euler totient |
| 18 | [Counting Necklaces](https://cses.fi/problemset/task/2209) | Burnside + φ(n) |
| 19 | [Counting Grids](https://cses.fi/problemset/task/2210) | Burnside's lemma |
| 20 | [Graph Paths II](https://cses.fi/problemset/task/1203) | Matrix exp + min-plus |

---

> _"The problems of number theory are easily stated but very difficult to solve."_ — Adapted from Gauss

