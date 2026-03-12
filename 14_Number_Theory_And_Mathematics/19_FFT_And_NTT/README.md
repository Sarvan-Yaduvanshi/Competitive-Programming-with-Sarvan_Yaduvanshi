# 📘 Level 18 — FFT & NTT

> **Fast polynomial multiplication in $O(n \log n)$.** The crown jewel of algebraic algorithms.  
> _Reference: [cp-algorithms.com — FFT](https://cp-algorithms.com/algebra/fft.html)_

---

## 1️⃣ Problem

Multiply two polynomials $A(x)$ and $B(x)$ of degree $n$:
$$C(x) = A(x) \cdot B(x)$$
Naive: $O(n^2)$. FFT/NTT: $O(n \log n)$.

---

## 2️⃣ FFT (Fast Fourier Transform)

### Idea
1. **Evaluate** $A$ and $B$ at $2n$ special points (roots of unity).
2. **Multiply** point-wise: $C(\omega_k) = A(\omega_k) \cdot B(\omega_k)$.
3. **Interpolate** (inverse FFT) to recover coefficients of $C$.

### Roots of Unity
The $n$-th roots of unity are $\omega_n^k = e^{2\pi i k/n}$ for $k = 0, 1, \ldots, n-1$.

### Key Property (Halving Lemma)
$(\omega_{2n}^k)^2 = \omega_n^k$ — allows divide-and-conquer splitting.

### Cooley-Tukey Algorithm
Split $A(x) = A_{\text{even}}(x^2) + x \cdot A_{\text{odd}}(x^2)$, recursively compute.

### Complexity: $O(n \log n)$

---

## 3️⃣ NTT (Number Theoretic Transform)

### Idea
Same as FFT but over $\mathbb{Z}_p$ instead of $\mathbb{C}$. Uses primitive root of unity modulo a prime.

### Common NTT Primes
| Prime $p$ | $p - 1$ | Max $n$ | Primitive Root |
|-----------|---------|---------|----------------|
| 998244353 | $2^{23} \times 7 \times 17$ | $2^{23} \approx 8.4 \times 10^6$ | 3 |
| 985661441 | $2^{23} \times \ldots$ | $2^{23}$ | 3 |
| 754974721 | $2^{24} \times \ldots$ | $2^{24}$ | 11 |

### Advantages over FFT
- **Exact**: no floating-point errors
- **Modular**: results are mod $p$
- Works perfectly for CP problems asking answer mod $998244353$

---

## 4️⃣ Applications

1. **Polynomial multiplication** — the direct application
2. **Big integer multiplication** — treat digits as polynomial coefficients
3. **String matching** — wildcard matching via convolution
4. **Counting problems** — generating function convolutions
5. **Divide & conquer optimization** — when combined with FFT

---

## 📁 Files in This Section

| File | Description |
|------|-------------|
| [01_FFT.cpp](01_FFT.cpp) | Fast Fourier Transform |
| [02_NTT.cpp](02_NTT.cpp) | Number Theoretic Transform |
| [03_Convolution_Applications.cpp](03_Convolution_Applications.cpp) | Practical applications |

---

## 🎯 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [POLYMUL](https://www.spoj.com/problems/POLYMUL/) | SPOJ | FFT |
| [Convolution](https://atcoder.jp/contests/atc001/tasks/fft_c) | AC | NTT |
| [Multiply Strings](https://leetcode.com/problems/multiply-strings/) | LC 43 | FFT concept |
| 🟢 [Polynomial Queries](https://cses.fi/problemset/task/1736) | CSES | Polynomial updates + query |

---

