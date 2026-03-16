# 🔄 03 — Modular Arithmetic Problem Solving

> Applied modular arithmetic for contests and interviews. These tricks are used in **almost every** competitive programming problem involving large numbers.

---

## 📚 Topics Covered

| # | Topic | Key Idea |
|---|-------|----------|
| 1 | Modular Arithmetic Properties | (a+b)%m, (a*b)%m, distribution |
| 2 | Large Number Computation | Handle numbers that overflow with mod |
| 3 | Modular Exponentiation | Fast power: a^b mod m in O(log b) |
| 4 | Modular Inverse | a^(-1) mod m — Fermat's little theorem / Extended GCD |
| 5 | Modular Combinatorics | nCr mod p, Lucas' theorem |

---

## 1️⃣ Modular Arithmetic Properties

### Basic Properties
```
(a + b) mod m = ((a mod m) + (b mod m)) mod m
(a - b) mod m = ((a mod m) - (b mod m) + m) mod m    ← add m to avoid negative
(a * b) mod m = ((a mod m) * (b mod m)) mod m
(a ^ b) mod m = fast exponentiation (see below)
```

### ⚠️ Division Does NOT Distribute
```
(a / b) mod m ≠ ((a mod m) / (b mod m)) mod m
→ Use modular inverse instead!
```

### Common Pitfalls
1. **Negative remainders**: `(-5) % 3` in C++ can be `-2`. Fix: `((x % m) + m) % m`
2. **Overflow in multiplication**: `(a * b) % m` can overflow if a, b are `long long`. Use `__int128` or modular multiplication.

### Modular Multiplication (Avoiding Overflow)
```cpp
i64 mulmod(i64 a, i64 b, i64 m) {
    return (__int128)a * b % m;
}
```

---

## 2️⃣ Modular Exponentiation (Binary Exponentiation)

### Algorithm
```
a^0 = 1
a^b = (a^(b/2))^2           if b is even
a^b = a * (a^(b/2))^2       if b is odd
```

### Implementation — O(log b)
```cpp
i64 modpow(i64 base, i64 exp, i64 mod) {
    i64 res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}
```

### Applications
- Compute large powers mod m
- Fermat's little theorem: `a^(p-1) ≡ 1 (mod p)` for prime p
- Modular inverse: `a^(-1) ≡ a^(p-2) (mod p)`

---

## 3️⃣ Modular Inverse

### When Do We Need It?
> Whenever we need to **divide** under modular arithmetic: `(a / b) mod m = a * b^(-1) mod m`

### Method 1: Fermat's Little Theorem (m is prime)
```
b^(-1) ≡ b^(m-2) (mod m)
```
Time: O(log m)

### Method 2: Extended GCD (m not necessarily prime)
```cpp
i64 extgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    i64 x1, y1;
    i64 g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

i64 modinv(i64 a, i64 m) {
    i64 x, y;
    i64 g = extgcd(a, m, x, y);
    if (g != 1) return -1;  // inverse doesn't exist
    return (x % m + m) % m;
}
```

### Method 3: Precompute Inverses 1..n (O(n))
```cpp
vec<i64> inv(n + 1);
inv[1] = 1;
for (int i = 2; i <= n; i++)
    inv[i] = (m - (m / i) * inv[m % i] % m) % m;
```

---

## 4️⃣ Modular Combinatorics

### nCr mod p (p prime, n ≤ 10^6)
Precompute factorials and inverse factorials:
```cpp
vec<i64> fact(MAXN), ifact(MAXN);
void precompute() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++)
        fact[i] = fact[i-1] * i % MOD;
    ifact[MAXN-1] = modpow(fact[MAXN-1], MOD-2, MOD);
    for (int i = MAXN-2; i >= 0; i--)
        ifact[i] = ifact[i+1] * (i+1) % MOD;
}

i64 C(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] % MOD * ifact[r] % MOD * ifact[n-r] % MOD;
}
```

### Lucas' Theorem (n very large, p small prime)
```
C(n, r) mod p = C(n/p, r/p) * C(n%p, r%p) mod p
```

### Key Formulas
| Formula | Expression |
|---------|-----------|
| nCr | n! / (r! × (n-r)!) |
| nPr | n! / (n-r)! |
| Stars & Bars | C(n+k-1, k-1) |
| Catalan | C(2n, n) / (n+1) |
| Derangement | n! × Σ(-1)^k / k! |

---

## 🧠 Quick Tips

1. **Always mod after every operation** — don't accumulate and mod at the end
2. **Use `1LL *` before multiplication** to avoid int overflow
3. **Precompute factorials** if you need many nCr queries
4. **MOD = 1e9+7 or 998244353** are the two most common contest mods
5. **998244353 = 119 × 2^23 + 1** — supports NTT (Number Theoretic Transform)

---

## 🔗 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [Pow(x, n)](https://leetcode.com/problems/powx-n/) | LeetCode 50 | Binary exponentiation |
| [Super Pow](https://leetcode.com/problems/super-pow/) | LeetCode 372 | Modular exponentiation |
| [Count Good Numbers](https://leetcode.com/problems/count-good-numbers/) | LeetCode 1922 | Mod exp + mod inverse |
| [Exponentiation](https://cses.fi/problemset/task/1095) | CSES | Modular exponentiation |
| [Exponentiation II](https://cses.fi/problemset/task/1712) | CSES | Euler's theorem |
| [Binomial Coefficients](https://cses.fi/problemset/task/1079) | CSES | nCr mod p |
| [Inverse Element](https://codeforces.com/edu/course/2/lesson/6) | Codeforces EDU | Mod inverse |

---

*Next: [04 — Combinatorics Problem Solving →](../04_Combinatorics_Problem_Solving/)*

