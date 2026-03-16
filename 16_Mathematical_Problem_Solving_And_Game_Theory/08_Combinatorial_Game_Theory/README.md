# 🧩 08 — Combinatorial Game Theory (Advanced Games)

> Beyond classic Nim — subtraction games, Wythoff's game, Moore's Nim, and take-and-break games. These are the patterns that separate Experts from Grandmasters.

---

## 📚 Topics Covered

| # | Topic | Key Idea |
|---|-------|----------|
| 1 | Subtraction Games | Take from a fixed set S — Grundy is periodic |
| 2 | Wythoff's Game | Take from one pile or equal from both — golden ratio |
| 3 | Moore's Nim (k-Nim) | Take from at most k piles simultaneously |
| 4 | Turning Turtles | Flip coins — XOR of positions of heads |
| 5 | Take-and-Break | Remove from pile, optionally split remainder |
| 6 | Green Hackenbush | Edge-deletion game on graphs |
| 7 | **Euclid's Game** | Subtract multiples of smaller from larger — GCD game |
| 8 | **Chomp** | Eat from grid — strategy stealing proves first wins |
| 9 | **Nim on General Graph / DAG** | Sprague-Grundy on game DAG |

---

## 1️⃣ Subtraction Games

### Rules
- One pile of n stones
- Allowed moves: take exactly s stones, where s ∈ S (the "subtraction set")
- Last to move wins

### Grundy Values
```
G(0) = 0
G(n) = mex({ G(n - s) : s ∈ S, s ≤ n })
```

### Key Property: **Grundy values are eventually periodic!**
The period divides lcm of elements + some transient.

### Examples
| Subtraction Set S | Grundy Pattern | Period |
|------------------|----------------|--------|
| {1, 2, 3} | 0,1,2,3,0,1,2,3,... | 4 |
| {1, 3} | 0,1,0,1,2,0,1,0,1,2,... | 5 |
| {2, 5} | 0,0,1,0,0,1,2,0,0,1,... | compute |

### Strategy
1. Compute Grundy for small values
2. Find the period
3. Use `G(n) = G(n % period)` for large n

---

## 2️⃣ Wythoff's Game

### Rules
- Two piles of sizes (a, b)
- Each turn: remove any positive number from ONE pile, OR remove the SAME positive number from BOTH piles
- Last to move wins

### Cold Positions (Losing Positions)
The losing positions are:
```
(0, 0), (1, 2), (3, 5), (4, 7), (6, 10), (8, 13), ...
```

### Formula — The Golden Ratio!
```
φ = (1 + √5) / 2 ≈ 1.618...

The k-th cold position is:
  aₖ = ⌊k × φ⌋
  bₖ = ⌊k × φ²⌋ = aₖ + k

where φ² = φ + 1 ≈ 2.618...
```

### Check if (a, b) is a cold position
```
Given (a, b) with a ≤ b:
k = b - a
Check if a == ⌊k × φ⌋
```

### Properties
- Every non-negative integer appears exactly ONCE in the cold positions (as aₖ or bₖ)
- This is a **Beatty sequence** partition
- Related to Fibonacci / Zeckendorf representation

---

## 3️⃣ Moore's Nim (k-Nim)

### Rules
- Same as Nim, but each turn a player can take from **at most k piles** (instead of exactly 1)

### Theorem (Moore, 1910)
> First player wins ⟺ when you write all pile sizes in binary and sum each bit position **modulo (k+1)**, at least one bit position sum is **non-zero**.

### Special Cases
- k = 1: Standard Nim (sum bits mod 2 = XOR)
- k = 2: Sum bits mod 3

### Implementation
```cpp
bool mooresNim(vector<int>& piles, int k) {
    for (int bit = 0; bit < 30; bit++) {
        int sum = 0;
        for (int p : piles) sum += (p >> bit) & 1;
        if (sum % (k + 1) != 0) return true;  // first wins
    }
    return false;  // second wins
}
```

---

## 4️⃣ Turning Turtles (Coin-Turning Games)

### Rules
- n coins in a row, some heads (H), some tails (T)
- Each turn: flip a head coin to tails, and optionally flip ONE other coin to the LEFT of it
- Game ends when all coins are tails
- Last to move wins

### Analysis
- Each heads coin at position i has Grundy value i
- The game = independent sub-games (one per heads coin)
- **Total Grundy = XOR of positions of all heads coins**

### Why?
- Flipping position i from H to T = removing pile of size i
- Optionally flipping position j < i = adding pile of size j
- This is equivalent to Nim-like operations

---

## 5️⃣ Take-and-Break Games

### Rules
- A pile of n stones
- Move: remove some stones AND optionally split the remaining stones into 2 piles
- Rules vary by specific game

### Common Variant: Sprague-Grundy on DAG
- Each pile position is a node
- Each move leads to 0, 1, or 2 child piles
- G(n) = mex({ G(a) ⊕ G(b) : for all valid splits (a, b) of n after taking })

### Example: Lasker's Nim
- Take any number from a pile, OR split a pile into two non-empty piles
- Grundy(n) = n if n % 4 ≠ 0
- Grundy(n) = specific values for n % 4 == 0

---

## 6️⃣ Green Hackenbush

### Rules
- A graph with some vertices grounded
- Each turn: remove an edge; any part disconnected from ground is also removed
- Last to move wins

### For Trees (Bamboo Stalks)
- Grundy value of a path of length n = n
- Grundy value of a tree rooted at ground = XOR of Grundy values of branches

### Colon Principle
> Any vertex can be replaced by a single edge if we XOR the Grundy values of all branches.

---

## 7️⃣ Euclid's Game

### Rules
- Two numbers (a, b). Each turn: subtract any positive multiple of the smaller from the larger (result must stay ≥ 0).
- Player who makes a number 0 wins.

### Analysis
```
If a ≥ 2b → Current player WINS (has strategic choice)
If b < a < 2b → Forced move (a - b, b), switch turns
If a == b → Current player takes all, WINS
```
The game follows the Euclidean algorithm! First player who faces a ≥ 2b wins.

### Time: O(log(max(a,b)))

---

## 8️⃣ Chomp

### Rules
- m × n grid (chocolate bar). Each turn: eat a cell and everything above-right.
- Player who eats bottom-left cell (poisoned) LOSES.

### Result
> **First player ALWAYS wins** for any grid > 1×1 (by strategy stealing argument).
> But no efficient explicit strategy is known for general m×n!

### For 2×n: First eats (2,2), leaving L-shape, then mirrors opponent.

---

## 9️⃣ Nim on General Graph / DAG

### Setup
Token on a DAG. Players alternate moving along edges. Can't move = lose.

### Grundy on DAG
```
G(v) = mex({ G(u) : u is a successor of v })
Sinks: G = 0 (losing)
```

For multiple tokens on independent DAGs: XOR Grundy values.

---

## 🧠 Quick Reference Table

| Game | Losing Condition | Key Formula |
|------|-----------------|-------------|
| Subtraction S | G(n) = 0, periodic | mex of reachable Grundy |
| Wythoff's | (⌊kφ⌋, ⌊kφ²⌋) | Golden ratio φ |
| Moore's k-Nim | All bit sums ≡ 0 (mod k+1) | Bit-sum mod k+1 |
| Turning Turtles | XOR of heads positions = 0 | XOR of positions |
| Take-and-Break | G = 0 | mex of XOR-split Grundy |
| Green Hackenbush | XOR of edge values = 0 | Tree: XOR of branch lengths |
| **Euclid's Game** | Recurse like GCD | First to face a ≥ 2b wins |
| **Chomp** | Strategy stealing | First always wins (existence) |
| **Nim on DAG** | G(v) = 0 at start | mex on DAG, XOR for multi-token |

---

## 🔗 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [Staircase Nim](https://cses.fi/problemset/task/1099) | CSES | Staircase Nim |
| [Another Game on Nim](https://codeforces.com/problemset/problem/1537/E) | Codeforces | Nim variant |
| [Wythoff's Game](https://www.spoj.com/problems/MWYTHON/) | SPOJ | Wythoff |
| [Turning Turtles](https://www.hackerrank.com/challenges/turning-turtles) | HackerRank | Coin turning |
| [Nim with Powers](https://codeforces.com/problemset/problem/850/C) | Codeforces | Advanced Nim |
| [Game on Graph](https://codeforces.com/problemset/problem/936/B) | Codeforces | Graph game |
| [Flip Game](https://leetcode.com/problems/flip-game-ii/) | LeetCode 294 | Game state DP |
| [Coin Game](https://cses.fi/problemset/task/1727) | CSES | Game theory |
| [Euclid's Game](https://www.spoj.com/problems/EUCLID/) | SPOJ | Euclid Game |
| [Euclid Game](https://codeforces.com/problemset/problem/1178/C) | Codeforces | Euclid variant |

---

*Next: [09 — Math Optimization Problems →](../09_Math_Optimization_Problems/)*

