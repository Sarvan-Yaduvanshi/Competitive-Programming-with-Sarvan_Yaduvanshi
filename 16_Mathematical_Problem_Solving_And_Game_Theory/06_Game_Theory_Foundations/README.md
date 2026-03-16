# 🎮 06 — Game Theory Foundations

> The core framework for ALL game theory problems in competitive programming. Understanding W/L states and backward induction is the foundation for Nim, Sprague-Grundy, and every game problem.

---

## 📚 Topics Covered

| # | Topic | Key Idea |
|---|-------|----------|
| 1 | Types of Games | Impartial vs Partisan, Normal vs Misère |
| 2 | Game States | Positions, Winning (W) vs Losing (L) states |
| 3 | Normal Play Convention | Last player to move wins |
| 4 | Backward Induction | Classify states from terminal positions backward |
| 5 | Game Trees | Visualizing game states as a tree/DAG |
| 6 | Strategy Stealing | Prove first player wins without knowing strategy |
| 7 | **Game on DAG** | BFS/DFS to classify W/L on directed game graphs |
| 8 | **Minimax Algorithm** | Optimal play for partisan games (maximize vs minimize) |
| 9 | **Alpha-Beta Pruning** | Optimize minimax by pruning irrelevant branches |

---

## 1️⃣ Types of Games

### Combinatorial Game Theory deals with games that are:
1. **Two players** — alternating turns
2. **Perfect information** — both players see the entire game state
3. **No chance** — no randomness (no dice, no cards)
4. **Finite** — the game must end in finite moves
5. **Deterministic** — outcome depends only on play, not luck

### Impartial vs Partisan

| Type | Definition | Example |
|------|-----------|---------|
| **Impartial** | Both players have the **same** available moves from any position | Nim, take-away games |
| **Partisan** | Players have **different** available moves | Chess, Go, Checkers |

> **In CP, 90% of game problems are IMPARTIAL games** → Sprague-Grundy theory applies!

### Normal Play vs Misère Play

| Convention | Rule | Nim XOR trick |
|-----------|------|---------------|
| **Normal** | Last player to move **WINS** | XOR ≠ 0 → First wins |
| **Misère** | Last player to move **LOSES** | Special handling needed |

---

## 2️⃣ Game States: Winning (W) vs Losing (L)

### Definitions
- **Losing State (L)**: The player whose turn it is WILL LOSE with optimal play
- **Winning State (W)**: The player whose turn it is CAN WIN with optimal play

### The Key Rules (Backward Induction)
```
Rule 1: A terminal state with NO moves is a LOSING state (L)
        (under normal play convention — player can't move, so they lose)

Rule 2: A state is WINNING (W) if there exists AT LEAST ONE move 
        leading to a LOSING state for the opponent

Rule 3: A state is LOSING (L) if ALL moves lead to WINNING states 
        for the opponent
```

### Visual Example: Take-Away Game
> n stones. Each turn: take 1 or 2 stones. Last to take wins.

```
State:  0   1   2   3   4   5   6   7   8   9
W/L:    L   W   W   L   W   W   L   W   W   L
```
Pattern: L when n % 3 == 0!

**Proof by backward induction**:
- n=0: No moves → L
- n=1: Take 1 → reach 0 (L) → W
- n=2: Take 1 → reach 1 (W), Take 2 → reach 0 (L) → W (has move to L)
- n=3: Take 1 → reach 2 (W), Take 2 → reach 1 (W) → L (all moves lead to W)
- Pattern repeats with period 3

---

## 3️⃣ Backward Induction Algorithm

### Steps
1. **Identify terminal states** → mark as L
2. **Work backward**: for each state, check all moves:
   - If ANY successor is L → mark as W
   - If ALL successors are W → mark as L
3. **Answer**: check if the starting state is W or L

### Implementation
```cpp
// game[i] = list of states reachable from state i
// W/L classification using backward induction (BFS/DFS)

vector<int> classify(int n, vector<vector<int>>& moves) {
    vector<int> state(n + 1, -1);  // -1 = unclassified
    
    // Terminal states (no moves) are L
    for (int i = 0; i <= n; i++)
        if (moves[i].empty()) state[i] = 0;  // 0 = Losing
    
    // BFS from terminal states
    // ... (or recursive DFS with memoization)
    
    return state;
}
```

---

## 4️⃣ Common Game Patterns

### Pattern 1: Divisibility / Modular
If taking 1..k items from n, and last take wins:
- **L when n % (k+1) == 0**
- Strategy: always leave opponent at a multiple of (k+1)

### Pattern 2: Parity
If only 1 item per move:
- **n odd → First wins, n even → Second wins**

### Pattern 3: Nim (XOR)
Multiple piles, take any number from one pile:
- **XOR of all pile sizes ≠ 0 → First wins**
- (Covered in detail in Chapter 07)

### Pattern 4: Symmetry / Mirroring
If the game has a symmetric structure:
- First player moves, then mirrors opponent's moves
- Example: two players alternately place coins on a round table

---

## 5️⃣ Strategy Stealing Argument

### Idea
> If Second player had a winning strategy, First player could "steal" it by making an arbitrary first move and then following Second's strategy.

### Application
> Proves that First player can ALWAYS win (or at worst draw) in many symmetric games. But it doesn't tell you **how** to win — it's a pure existence proof.

### Example
In Chomp (take a square and everything above-right), First player wins for all boards except 1×1. Proof by strategy stealing: if Second had a winning strategy, First could use it (since First's initial move gives Second a strictly smaller board).

---

## 6️⃣ Misère Games

### Normal vs Misère in Simple Games
- Normal: can't move = **lose**
- Misère: can't move = **win**

### Misère Nim
> For standard Nim under misère play:
- If all piles have size ≤ 1:
  - Odd number of piles → **Second wins** (they get stuck with last)
  - Even number of piles → **First wins**
- If any pile has size > 1:
  - XOR ≠ 0 → **First wins** (same as normal!)
  - XOR = 0 → **Second wins** (same as normal!)

---

## 🧠 Quick Decision Framework

```
Is it a game theory problem?
│
├─ Single pile, take items → Check modular pattern
│   └─ Take 1..k: L iff n % (k+1) == 0
│
├─ Multiple piles → Think Nim / Sprague-Grundy
│   └─ Each pile independent? XOR Grundy values
│
├─ Move to smaller state → Backward induction
│   └─ Compute W/L for small cases, find pattern
│
└─ Symmetric game → Strategy stealing / mirroring
```

---

## 🔗 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [Nim Game](https://leetcode.com/problems/nim-game/) | LeetCode 292 | Modular pattern |
| [Can I Win](https://leetcode.com/problems/can-i-win/) | LeetCode 464 | Game DP with bitmask |
| [Predict the Winner](https://leetcode.com/problems/predict-the-winner/) | LeetCode 486 | Minimax DP |
| [Stone Game](https://leetcode.com/problems/stone-game/) | LeetCode 877 | Strategy stealing |
| [Stick Game](https://cses.fi/problemset/task/1729) | CSES | Take-away game |
| [Game of Nim](https://cses.fi/problemset/task/1730) | CSES | Classic Nim |
| [Staircase Nim](https://cses.fi/problemset/task/1099) | CSES | Staircase Nim |
| [Grundy's Game](https://cses.fi/problemset/task/2207) | CSES | Sprague-Grundy |

---

*Next: [07 — Nim & Sprague-Grundy →](../07_Nim_And_Sprague_Grundy/)*

