# 14 — Probability DP

## What You'll Learn
- **Expected Value DP** — E[state] = Σ P(event) × (E[next] + cost)
- **Linearity of Expectation** — E[X+Y] = E[X] + E[Y] (even if dependent!)
- Dice probability DP
- Coin toss probability (AtCoder DP I)
- **Coupon Collector Problem** — expected draws for all items
- **Sushi Problem** (AtCoder DP J) — expected value with state compression
- **Random Walk** on line
- **Gambler's Ruin** — probability of reaching N before 0
- Markov chain DP

## Files
| File | Topics Covered |
|------|---------------|
| `01_Expected_Value_And_Probability.cpp` | Dice prob, Coin prob, Coupon Collector, Sushi, Random Walk, Gambler's Ruin |

## Key Formula
```
E[state] = Σ P(transition) × (E[next_state] + cost_of_transition)
```
> **Pro Tip:** If E[state] appears on both sides of the equation, rearrange algebraically before coding!

## Practice Problems
- AtCoder DP: I (Coins), J (Sushi)
- CF: 1156F (Card Bag), 235B, 518D
- LeetCode: 688, 808, 837

