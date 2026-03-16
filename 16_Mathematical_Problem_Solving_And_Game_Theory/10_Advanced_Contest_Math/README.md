# 🚀 10 — Advanced Contest Math

> Grandmaster-level techniques — matrix exponentiation for recurrences, generating functions, Lagrange interpolation. These appear in Div 1 C/D problems on Codeforces and hard LeetCode.

---

## 📚 Topics Covered

| # | Topic | Key Idea |
|---|-------|----------|
| 1 | Linear Recurrences | f(n) = c₁f(n-1) + c₂f(n-2) + ... |
| 2 | Matrix Exponentiation | Compute f(n) in O(k³ log n) for k-th order recurrence |
| 3 | Generating Functions | Encode sequences as power series |
| 4 | Lagrange Interpolation | Reconstruct polynomial from values |
| 5 | Berlekamp-Massey | Find minimal recurrence from sequence values |

---

## 1️⃣ Linear Recurrences

### Definition
```
f(n) = c₁·f(n-1) + c₂·f(n-2) + ... + cₖ·f(n-k)
```

### Examples
| Sequence | Recurrence | Order |
|----------|-----------|-------|
| Fibonacci | f(n) = f(n-1) + f(n-2) | k = 2 |
| Tribonacci | f(n) = f(n-1) + f(n-2) + f(n-3) | k = 3 |
| Derangements | D(n) = (n-1)(D(n-1) + D(n-2)) | Non-linear! |

### Computing f(n)
- Naive DP: O(n × k)
- **Matrix exponentiation: O(k³ × log n)** ← the key technique

---

## 2️⃣ Matrix Exponentiation

### The Idea
Represent the recurrence as a matrix equation:
```
[f(n)  ]   [c₁ c₂ ... cₖ] [f(n-1)]
[f(n-1)] = [1  0  ... 0 ] [f(n-2)]
[  ...  ]   [0  1  ... 0 ] [ ...  ]
[f(n-k+1)] [0  0  ... 0 ] [f(n-k)]
```

So: **V(n) = M × V(n-1) = M^(n-k) × V(k)**

Compute M^(n-k) using binary exponentiation on matrices → O(k³ log n)

### Fibonacci Example
```
[F(n+1)]   [1 1]^n   [F(1)]   [1 1]^n   [1]
[F(n)  ] = [1 0]   × [F(0)] = [1 0]   × [0]
```

### Implementation
```cpp
typedef vector<vector<i64>> Matrix;

Matrix multiply(Matrix& A, Matrix& B, i64 mod) {
    int n = A.size();
    Matrix C(n, vector<i64>(n, 0));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++) if (A[i][k])
            for (int j = 0; j < n; j++)
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
    return C;
}

Matrix matpow(Matrix M, i64 p, i64 mod) {
    int n = M.size();
    Matrix res(n, vector<i64>(n, 0));
    for (int i = 0; i < n; i++) res[i][i] = 1;  // identity
    while (p > 0) {
        if (p & 1) res = multiply(res, M, mod);
        M = multiply(M, M, mod);
        p >>= 1;
    }
    return res;
}
```

### Applications Beyond Fibonacci
1. **Counting paths in a graph** of length exactly n: (adjacency matrix)^n
2. **Expected value DP** with matrix transitions
3. **CSES: Throwing Dice** — count sequences summing to n using dice

---

## 3️⃣ Generating Functions (Conceptual)

### Ordinary Generating Function (OGF)
```
A(x) = Σ aₙ xⁿ = a₀ + a₁x + a₂x² + ...
```

### Key Operations
| Operation | Effect on Sequence |
|-----------|-------------------|
| A(x) + B(x) | aₙ + bₙ |
| A(x) × B(x) | Convolution: cₙ = Σ aₖ bₙ₋ₖ |
| x·A(x) | Right shift by 1 |
| A'(x) | n·aₙ₋₁ |
| 1/(1-x) | 1, 1, 1, 1, ... |
| 1/(1-x)² | 1, 2, 3, 4, ... |

### CP Application
- Fibonacci: A(x) = x / (1 - x - x²)
- Catalan: C(x) = (1 - √(1-4x)) / (2x)
- Partition function via product of 1/(1-xⁱ)

---

## 4️⃣ Lagrange Interpolation

### Problem
Given k+1 points (x₀,y₀), (x₁,y₁), ..., (xₖ,yₖ), find the unique degree-k polynomial passing through all of them, and evaluate it at some point t.

### Formula
```
P(t) = Σᵢ yᵢ × ∏_{j≠i} (t - xⱼ) / (xᵢ - xⱼ)
```

### Complexity
- General: O(k²)
- If points are consecutive integers: O(k)

### CP Application
1. **Sum of k-th powers**: Σ i^k for i=1..n is a polynomial of degree k+1 in n.
   Compute for n = 0,1,...,k+1, then interpolate for any n.
2. **DP optimization**: If dp[n] is a polynomial in n, compute small values and interpolate.

---

## 5️⃣ Berlekamp-Massey Algorithm

### What It Does
Given a sequence a₀, a₁, ..., aₙ, find the **shortest linear recurrence** that generates it.

### Usage in CP
1. Compute first ~100 terms of a sequence using brute force
2. Run Berlekamp-Massey to find the recurrence
3. Use matrix exponentiation to compute the n-th term

This is incredibly powerful for problems where the recurrence isn't obvious!

---

## 🔗 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [Fibonacci Number](https://leetcode.com/problems/fibonacci-number/) | LeetCode 509 | Matrix exp (for practice) |
| [Fibonacci Numbers](https://cses.fi/problemset/task/1722) | CSES | Matrix exponentiation |
| [Throwing Dice](https://cses.fi/problemset/task/1096) | CSES | Matrix exponentiation |
| [Graph Paths I](https://cses.fi/problemset/task/1723) | CSES | Matrix exp on adj matrix |
| [Tribonacci Number](https://leetcode.com/problems/n-th-tribonacci-number/) | LeetCode 1137 | Matrix exp |
| [Sum of k-th Powers](https://codeforces.com/problemset/problem/622/F) | Codeforces | Lagrange interpolation |
| [Berlekamp-Massey](https://codeforces.com/blog/entry/61306) | CF Blog | Finding recurrences |
| [Knight Moves](https://codeforces.com/gym/102644) | Codeforces | Matrix exp |

---

*Next: [11 — 🏆 Top Game Theory Problem Solving →](../11_Top_Game_Theory_Problem_Solving/)*

