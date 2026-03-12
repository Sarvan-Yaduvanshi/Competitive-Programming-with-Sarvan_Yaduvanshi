# 🔢 Number Theory & Mathematics — Zero to GM / ICPC

> **Pure Mathematics for Competitive Programming**  
> Every concept: Definition → Proof → Dry Run → Code → Practice  
> _Reference: [cp-algorithms.com](https://cp-algorithms.com/)_

---

## 📋 Table of Contents

| # | Level | Topic | Key Concepts | Difficulty |
|---|-------|-------|-------------|------------|
| 01 | 0 | [Number System & Divisibility](01_Number_Theory_Foundations/) | Integer properties, divisibility, FTA, prime factorization | ⭐ |
| 02 | 1 | [GCD & Euclidean Algorithms](02_GCD_And_Euclidean_Algorithm/) | Euclidean, Extended Euclidean, Binary GCD, LCM | ⭐ |
| 03 | 2 | [Binary Exponentiation](03_Binary_Exponentiation/) | Fast power, modular exp, matrix exp | ⭐⭐ |
| 04 | 3 | [Modular Arithmetic](04_Modular_Arithmetic/) | Mod operations, Fermat, Euler theorem | ⭐⭐ |
| 05 | 4 | [Modular Inverse](05_Modular_Inverse/) | Extended Euclid, Fermat, precomputation | ⭐⭐ |
| 06 | 5 | [Linear Diophantine Equations](06_Linear_Diophantine_Equations/) | ax + by = c, solution existence, all solutions | ⭐⭐ |
| 07 | 6 | [Prime Generation](07_Prime_Generation/) | Trial division, Sieve, Linear sieve, Segmented sieve | ⭐⭐ |
| 08 | 7 | [Primality Testing](08_Primality_Testing/) | Fermat test, Miller-Rabin, deterministic tests | ⭐⭐⭐ |
| 09 | 8 | [Integer Factorization](09_Integer_Factorization/) | Trial division, Pollard's Rho, SPF sieve | ⭐⭐⭐ |
| 10 | 9 | [Number-Theoretic Functions](10_Number_Theoretic_Functions/) | φ(n), μ(n), τ(n), σ(n) | ⭐⭐⭐ |
| 11 | 10 | [Chinese Remainder Theorem](11_Chinese_Remainder_Theorem/) | Standard CRT, non-coprime CRT, Garner's algorithm | ⭐⭐⭐ |
| 12 | 11 | [Combinatorics](12_Combinatorics/) | nCr, Lucas, Catalan, Stars & Bars | ⭐⭐⭐ |
| 13 | 12 | [Inclusion-Exclusion Principle](13_Inclusion_Exclusion_Principle/) | Overcounting, coprime count, subset counting | ⭐⭐⭐ |
| 14 | 13 | [Multiplicative Functions](14_Multiplicative_Functions/) | Dirichlet convolution, Möbius inversion | ⭐⭐⭐⭐ |
| 15 | 14 | [Discrete Logarithm](15_Discrete_Logarithm/) | Baby-step Giant-step, applications | ⭐⭐⭐⭐ |
| 16 | 15 | [Primitive Roots](16_Primitive_Roots/) | Cyclic groups, generators mod p | ⭐⭐⭐⭐ |
| 17 | 16 | [Modular Square Root](17_Modular_Square_Root/) | Tonelli-Shanks, Cipolla | ⭐⭐⭐⭐ |
| 18 | 17 | [Polynomial Algorithms](18_Polynomial_Algorithms/) | Poly multiply, interpolation, formal power series | ⭐⭐⭐⭐ |
| 19 | 18 | [FFT & NTT](19_FFT_And_NTT/) | Fast Fourier Transform, NTT, convolution | ⭐⭐⭐⭐⭐ |
| 20 | 19 | [Advanced Number Theory](20_Advanced_Number_Theory/) | Montgomery mult, continued fractions, lattice | ⭐⭐⭐⭐⭐ |
| 21 | 20 | [ICPC / GM Level Mathematics](21_ICPC_Level_Number_Theory/) | Pollard-Rho optimizations, generating functions | ⭐⭐⭐⭐⭐ |

---

## 🗺️ Dependency Graph

```
Level 0: [01 Number System & Divisibility]
              │
Level 1: [02 GCD & Euclidean]
              │
Level 2: [03 Binary Exponentiation]
              │
Level 3: [04 Modular Arithmetic] ──────────────────────┐
              │                                         │
Level 4: [05 Modular Inverse] ◄─────────────────┐      │
              │                                  │      │
Level 5: [06 Linear Diophantine Equations]       │      │
              │                                  │      │
Level 6: [07 Prime Generation]                   │      │
              │                                  │      │
Level 7: [08 Primality Testing]                  │      │
              │                                  │      │
Level 8: [09 Integer Factorization]              │      │
              │                                  │      │
Level 9: [10 Number-Theoretic Functions] ────────┘      │
              │                                         │
Level 10: [11 Chinese Remainder Theorem]                │
              │                                         │
Level 11: [12 Combinatorics] ◄──────────────────────────┘
              │
Level 12: [13 Inclusion-Exclusion]
              │
Level 13: [14 Multiplicative Functions]
              │
Level 14: [15 Discrete Logarithm]
              │
Level 15: [16 Primitive Roots]
              │
Level 16: [17 Modular Square Root]
              │
Level 17: [18 Polynomial Algorithms]
              │
Level 18: [19 FFT & NTT]
              │
Level 19: [20 Advanced Number Theory]
              │
Level 20: [21 ICPC / GM Level]
```

---

## ⏱️ Complexity Cheat Sheet

| Algorithm | Time | Space | Notes |
|-----------|------|-------|-------|
| GCD (Euclidean) | O(log min(a,b)) | O(1) | Foundation of everything |
| Extended Euclidean | O(log min(a,b)) | O(1) | Finds x,y: ax+by=gcd |
| Binary Exponentiation | O(log n) | O(1) | a^n mod m |
| Matrix Exponentiation | O(k³ log n) | O(k²) | k = matrix dimension |
| Sieve of Eratosthenes | O(n log log n) | O(n) | All primes ≤ n |
| Linear Sieve | O(n) | O(n) | Also gives SPF |
| Segmented Sieve | O(n log log n) | O(√n) | Primes in [L,R] |
| Miller-Rabin | O(k log² n) | O(1) | k = witnesses |
| Pollard's Rho | O(n^{1/4}) expected | O(1) | Factorization |
| Euler Totient (single) | O(√n) | O(1) | Via factorization |
| Euler Totient (sieve) | O(n log log n) | O(n) | All φ(1..n) |
| CRT (k equations) | O(k log M) | O(1) | M = product of moduli |
| nCr mod p (precomp) | O(n) preprocess, O(1) query | O(n) | Factorial + inverse |
| Lucas Theorem | O(p log_p n) | O(p) | nCr mod small prime |
| Baby-step Giant-step | O(√m) | O(√m) | Discrete log |
| Tonelli-Shanks | O(log² p) | O(1) | Square root mod p |
| FFT | O(n log n) | O(n) | Polynomial multiply |
| NTT | O(n log n) | O(n) | Exact (mod) convolution |

---

## 📅 Study Plan (5 Weeks)

### Week 1: Foundations (Level 0–4)
- Day 1–2: Number System, Divisibility, Prime Factorization
- Day 3: GCD, Extended Euclidean Algorithm
- Day 4: Binary Exponentiation, Matrix Exponentiation
- Day 5–6: Modular Arithmetic, Fermat's Little Theorem
- Day 7: Modular Inverse (all methods)

### Week 2: Primes & Equations (Level 5–8)
- Day 1: Linear Diophantine Equations
- Day 2–3: Sieve of Eratosthenes, Linear Sieve, Segmented Sieve
- Day 4: Miller-Rabin Primality Testing
- Day 5–6: Integer Factorization, Pollard's Rho
- Day 7: Practice problems

### Week 3: Functions & Counting (Level 9–12)
- Day 1–2: Euler Totient, Möbius Function, Divisor Functions
- Day 3: Chinese Remainder Theorem
- Day 4–5: Combinatorics (nCr, Lucas, Catalan)
- Day 6: Inclusion-Exclusion Principle
- Day 7: Practice problems

### Week 4: Advanced Modular (Level 13–16)
- Day 1: Multiplicative Functions, Dirichlet Convolution
- Day 2–3: Discrete Logarithm (BSGS)
- Day 4: Primitive Roots
- Day 5: Modular Square Root (Tonelli-Shanks)
- Day 6–7: Practice problems

### Week 5: Polynomials & GM/ICPC Level (Level 17–20)
- Day 1–2: Polynomial Algorithms
- Day 3–4: FFT & NTT
- Day 5: Advanced Number Theory
- Day 6–7: ICPC Level Problems & Contest Practice

---

## 🧰 Template

All implementations use the [CP Template](../My%20Competitive%20Programming%20Template.cpp).

---

## 📚 References

- [cp-algorithms.com](https://cp-algorithms.com/) — Primary reference
- [OEIS](https://oeis.org/) — Integer sequences
- [Project Euler](https://projecteuler.net/) — Mathematical problems
- [Art of Problem Solving](https://artofproblemsolving.com/) — Math olympiad
- _Elementary Number Theory_ — David M. Burton
- _Concrete Mathematics_ — Graham, Knuth, Patashnik

---

## 👤 Author

**Sarvan Yaduvanshi**  
Competitive Programmer | Number Theory Enthusiast

> _"Mathematics is the queen of the sciences and number theory is the queen of mathematics."_ — Carl Friedrich Gauss

---

