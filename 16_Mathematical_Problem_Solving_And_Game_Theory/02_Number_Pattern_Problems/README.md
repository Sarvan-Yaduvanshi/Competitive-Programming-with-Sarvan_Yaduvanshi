# 🔢 02 — Number Pattern Problems

> Interview-style math pattern problems — digit tricks, palindromes, base conversions. These are **FAANG favorites** and appear frequently on LeetCode.

---

## 📚 Topics Covered

| # | Topic | Key Idea |
|---|-------|----------|
| 1 | Digit Manipulation | Extract, reverse, sum digits |
| 2 | Digit Sum Tricks | Divisibility by 3/9, digital root, casting out nines |
| 3 | Palindrome Numbers | Check, generate, next palindrome |
| 4 | Base Conversion | Convert between bases, base-k representations |
| 5 | Number Pattern Observations | Spotting patterns, OEIS, small case analysis |

---

## 1️⃣ Digit Manipulation

### Core Operations
```cpp
// Extract digits of n (right to left)
while (n > 0) {
    int digit = n % 10;
    n /= 10;
}

// Count digits
int numDigits = (n == 0) ? 1 : (int)log10(n) + 1;

// Reverse a number
int reverse(int n) {
    int rev = 0;
    while (n > 0) {
        rev = rev * 10 + n % 10;
        n /= 10;
    }
    return rev;
}
```

### CP Tips
- **Overflow**: When reversing, use `long long` or check before multiplying
- **Leading zeros**: After reversal, leading zeros disappear (100 → 001 = 1)
- **Digit frequency**: Use array `cnt[10]` to count each digit

---

## 2️⃣ Digit Sum Tricks

### Digital Root
> Repeatedly sum digits until single digit. Formula: `digitalRoot(n) = 1 + (n-1) % 9` for n > 0.

### Divisibility Rules via Digit Sum
| Divisor | Rule |
|---------|------|
| 3 | Digit sum divisible by 3 |
| 9 | Digit sum divisible by 9 |
| 11 | Alternating digit sum divisible by 11 |

### Casting Out Nines
> `n % 9 == digitSum(n) % 9` — useful for quick verification

### Key Formula
```
Digital Root = 1 + (n - 1) % 9     (for n ≥ 1)
Digital Root = 0                     (for n = 0)
```

---

## 3️⃣ Palindrome Numbers

### Check Palindrome
```cpp
bool isPalindrome(int n) {
    if (n < 0 || (n % 10 == 0 && n != 0)) return false;
    int rev = 0;
    while (n > rev) {
        rev = rev * 10 + n % 10;
        n /= 10;
    }
    return n == rev || n == rev / 10;
}
```

### Next Palindrome Algorithm
1. Mirror left half to right half
2. If result ≤ original, increment middle and re-mirror
3. Handle carry (999 → 1001)

### CP Applications
- Count palindromes in a range [L, R] — digit DP
- Generate all k-digit palindromes — only need first ⌈k/2⌉ digits
- Sum of palindromes — mathematical pattern

---

## 4️⃣ Base Conversion

### Base-10 to Base-k
```cpp
string toBase(int n, int k) {
    if (n == 0) return "0";
    string res;
    while (n > 0) {
        res += char('0' + n % k);  // for k ≤ 10
        n /= k;
    }
    reverse(res.begin(), res.end());
    return res;
}
```

### Base-k to Base-10
```cpp
int fromBase(string& s, int k) {
    int res = 0;
    for (char c : s) {
        res = res * k + (c - '0');
    }
    return res;
}
```

### Important Patterns
- **Binary representation**: base 2 — appears in bit manipulation
- **Ternary (base 3)**: balanced ternary, Wythoff's game
- **Base-k digit sum**: analogous to decimal digit sum

---

## 5️⃣ Number Pattern Observations

### Strategy for Pattern Problems
1. **Compute small cases** (n = 1, 2, 3, ..., 10)
2. **Look for pattern** in the sequence
3. **Check OEIS** (https://oeis.org/) — paste the sequence
4. **Prove the pattern** using induction or direct argument

### Common Patterns
| Sequence | Formula | OEIS |
|----------|---------|------|
| 1, 1, 2, 3, 5, 8... | Fibonacci: F(n) = F(n-1) + F(n-2) | A000045 |
| 1, 2, 5, 14, 42... | Catalan: C(n) = C(2n,n)/(n+1) | A000108 |
| 1, 1, 2, 5, 14, 42... | Catalan (0-indexed) | A000108 |
| 1, 3, 6, 10, 15... | Triangular: T(n) = n(n+1)/2 | A000217 |
| 1, 4, 9, 16, 25... | Perfect squares | A000290 |

### CP Tips
- **Always try small cases first** — pattern may be obvious
- **Use OEIS** — search by first few terms
- **Modular patterns**: sequences often become periodic mod m

---

## 🔗 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [Palindrome Number](https://leetcode.com/problems/palindrome-number/) | LeetCode 9 | Palindrome check |
| [Reverse Integer](https://leetcode.com/problems/reverse-integer/) | LeetCode 7 | Digit manipulation |
| [Happy Number](https://leetcode.com/problems/happy-number/) | LeetCode 202 | Digit sum + cycle |
| [Add Digits](https://leetcode.com/problems/add-digits/) | LeetCode 258 | Digital root |
| [Base 7](https://leetcode.com/problems/base-7/) | LeetCode 504 | Base conversion |
| [Smallest Integer Divisible by K](https://leetcode.com/problems/smallest-integer-divisible-by-k/) | LeetCode 1015 | Pigeonhole + mod |
| [Next Palindrome](https://leetcode.com/problems/next-palindrome-using-same-digits/) | LeetCode 1842 | Next palindrome |
| [Sum of Digits](https://codeforces.com/problemset/problem/1553/A) | Codeforces | Digit sum |
| [Digit Game](https://codeforces.com/problemset/problem/1430/B) | Codeforces | Parity + digits |

---

*Next: [03 — Modular Arithmetic Problem Solving →](../03_Modular_Arithmetic_Problem_Solving/)*

