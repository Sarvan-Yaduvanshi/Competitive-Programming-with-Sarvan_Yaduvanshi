# 11 — Digit DP

## What You'll Learn
- Digit DP template — count numbers in [L, R] with digit properties
- Tight constraint handling
- Leading zeros handling
- Digit sum constraints (≤ S, divisible by K)
- Avoid certain digits
- All unique digits (bitmask inside digit DP)
- No adjacent same digits (CSES Counting Numbers)
- Sum of all digits in range
- Count digit D appearances (LeetCode 233 generalized)
- Numbers divisible by K
- Palindrome counting
- Numbers with increasing digits

## Files
| File | Topics Covered |
|------|---------------|
| `01_Digit_DP_Complete_Guide.cpp` | Template, digit sum ≤ S, avoid digit, unique digits, divisible by K, no adjacent same |
| `02_Advanced_Digit_DP.cpp` | Sum of digits in range, count digit D, divisible by K, palindromes, increasing digits |

## Digit DP Template
```
solve(pos, tight, ...extra...) {
    if (pos == n) return check();
    if (memo[pos][tight][extra] != -1) return memo;
    limit = tight ? digit[pos] : 9;
    for (d = 0; d <= limit; d++)
        result += solve(pos+1, tight && d==limit, update(extra, d));
    return memo[pos][tight][extra] = result;
}
answer(L, R) = f(R) - f(L-1)
```

## Practice Problems
- LeetCode: 233, 357, 600, 902, 1012
- CSES: Counting Numbers
- AtCoder DP: S (Digit Sum)
- CF: 1542E2

