# 15 — Game Theory DP

## What You'll Learn
- **Winning/Losing States** — W if any move → L, L if all moves → W
- **Grundy Numbers** — G(state) = mex({G(next_states)})
- **Sprague-Grundy Theorem** — combined games: XOR of Grundy numbers
- **Nim Game** — first player wins iff XOR of piles ≠ 0
- **Minimax DP** — optimal play for two players
- Stone Game variants (LeetCode 877, 1140, 1406, 1510)
- Removal Game (CSES)
- **Bash Game** — n%(k+1) != 0
- **Wythoff's Game** — golden ratio positions
- **Staircase Nim** — only odd-indexed piles matter
- Finding and printing winning moves

## Files
| File | Topics Covered |
|------|---------------|
| `01_Grundy_Nim_Minimax.cpp` | Grundy numbers, Nim, Sprague-Grundy, Stone Game, Optimal Strategy, Bash, Wythoff, Staircase |
| `02_Stone_Game_Variants.cpp` | Stone Game II/III/IV, Removal Game, Predict the Winner |

## Key Insight
```
Winning: ∃ move to Losing state → Current player WINS
Losing:  ∀ moves lead to Winning state → Current player LOSES
Nim: XOR(all piles) ≠ 0 → First player wins
Combined: G(game) = G(sub1) XOR G(sub2) XOR ...
```

## Practice Problems
- LeetCode: 877, 1140, 1406, 1510, 486, 294
- CSES: Removal Game, Nim Game variants
- AtCoder DP: K (Stones), L (Deque)

