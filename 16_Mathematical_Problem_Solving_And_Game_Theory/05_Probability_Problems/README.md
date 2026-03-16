# 🎰 05 — Probability Problems

> Probability problems in competitive programming and FAANG interviews. Master expected value, linearity of expectation, and probability DP.

---

## 📚 Topics Covered

| # | Topic | Key Idea |
|---|-------|----------|
| 1 | Expected Value | E[X] = Σ x·P(X=x) |
| 2 | Linearity of Expectation | E[X+Y] = E[X] + E[Y] — always, even if dependent! |
| 3 | Random Walks | Probability of reaching a state, Gambler's ruin |
| 4 | Probability DP | State-based transition probabilities |
| 5 | Dice & Coin Problems | Classic interview problems |
| 6 | Probability with Combinatorics | Counting favorable outcomes |

---

## 1️⃣ Expected Value

### Definition
> E[X] = Σᵢ xᵢ · P(X = xᵢ)

### Properties
```
E[aX + b] = a·E[X] + b
E[X + Y]  = E[X] + E[Y]          (ALWAYS — linearity)
E[X · Y]  = E[X] · E[Y]          (ONLY if X, Y are independent)
```

### Linearity of Expectation — The Most Powerful Tool
> Instead of computing E[X] directly, **break X into indicator variables** and sum their expectations.

**Example**: Expected number of fixed points in a random permutation.
- Let Xᵢ = 1 if element i is in position i, 0 otherwise
- E[Xᵢ] = 1/n
- E[total fixed points] = Σ E[Xᵢ] = n · (1/n) = **1**
- Answer is 1, regardless of n! (Beautifully simple via linearity)

---

## 2️⃣ Classic Probability Problems

### Coupon Collector Problem
> Collect all n distinct coupons. Each trial gives random coupon. Expected trials?

- After collecting k coupons, probability of new one = (n-k)/n
- Expected trials for next = n/(n-k)
- E[total] = n/n + n/(n-1) + n/(n-2) + ... + n/1 = n·Hₙ ≈ n·ln(n)

### Birthday Problem
> With n people, probability that at least 2 share a birthday (365 days)?

- P(all different) = 365/365 × 364/365 × ... × (365-n+1)/365
- For n = 23, P(collision) ≈ 50.7%

### Geometric Distribution
> Repeat trials with success probability p until first success.
- E[trials] = 1/p

---

## 3️⃣ Random Walks

### Gambler's Ruin
> Start with $k. Each step: gain $1 with prob p, lose $1 with prob 1-p. Probability of reaching $n before $0?

**For p ≠ 1/2**:
```
P(reach n | start at k) = (1 - (q/p)^k) / (1 - (q/p)^n)
where q = 1 - p
```

**For p = 1/2**:
```
P(reach n | start at k) = k / n
```

---

## 4️⃣ Probability DP

### General Framework
```
dp[state] = probability of reaching this state
           (or expected cost/time from this state)

Transition: dp[state] = Σ P(state → next) × dp[next]
                        (+ cost of transition if expected value)
```

### Expected Value DP Pattern
```
E[state] = Σ P(transition) × (E[next_state] + cost)

For absorbing states: E[absorbing] = 0
```

### Classic: Expected Throws to Roll a 6
```
E = 1/6 · 0 + 5/6 · (E + 1)
E = 5/6 · E + 5/6 + 1/6 · 1
E/6 = 1
E = 6
```

---

## 5️⃣ Modular Probability in CP

> In CP, probability p/q is represented as `p × q^(-1) mod MOD`.

```cpp
// Probability p/q mod MOD
i64 prob = p % MOD * modpow(q, MOD - 2, MOD) % MOD;
```

---

## 🔗 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [Dice Combinations](https://cses.fi/problemset/task/1633) | CSES | Probability DP |
| [Throwing Dice](https://cses.fi/problemset/task/1096) | CSES | Matrix exp + probability |
| [Coin Probability](https://cses.fi/problemset/task/1725) | CSES | Expected value |
| [Soup Servings](https://leetcode.com/problems/soup-servings/) | LeetCode 808 | Probability DP |
| [New 21 Game](https://leetcode.com/problems/new-21-game/) | LeetCode 837 | Probability DP |
| [Knight Probability in Chessboard](https://leetcode.com/problems/knight-probability-in-chessboard/) | LeetCode 688 | Probability DP |
| [Random Pick with Weight](https://leetcode.com/problems/random-pick-with-weight/) | LeetCode 528 | Weighted probability |
| [Airplane Seat Assignment](https://leetcode.com/problems/airplane-seat-assignment-probability/) | LeetCode 1227 | Probability trick |

---

*Next: [06 — Game Theory Foundations →](../06_Game_Theory_Foundations/)*

