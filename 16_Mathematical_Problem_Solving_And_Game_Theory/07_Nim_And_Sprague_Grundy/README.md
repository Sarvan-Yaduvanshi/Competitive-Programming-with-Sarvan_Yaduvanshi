# ⚔️ 07 — Nim & Sprague-Grundy Theory

> The **Sprague-Grundy theorem** is the single most important result in combinatorial game theory for competitive programming. It reduces ANY impartial game to a game of Nim.

---

## 📚 Topics Covered

| # | Topic | Key Idea |
|---|-------|----------|
| 1 | Classic Nim | XOR of pile sizes determines winner |
| 2 | Nim Variants | Bounded Nim, Multi-pile, Staircase Nim |
| 3 | Mex Operation | Minimum excludant — foundation of Grundy numbers |
| 4 | Grundy Numbers | Assign a "Nim value" to every game position |
| 5 | Sprague-Grundy Theorem | Any impartial game = equivalent Nim pile |
| 6 | Composite Games | XOR of Grundy values of independent sub-games |

---

## 1️⃣ Classic Nim

### Rules
- k piles of stones with sizes n₁, n₂, ..., nₖ
- Each turn: pick ONE pile, remove ANY positive number of stones from it
- Player who takes the last stone **WINS** (normal play)

### Bouton's Theorem (1902)
> **First player wins ⟺ n₁ ⊕ n₂ ⊕ ... ⊕ nₖ ≠ 0**

(⊕ = bitwise XOR)

### Proof Sketch
1. Terminal state (all piles empty): XOR = 0 → L state ✓
2. From XOR ≠ 0, there ALWAYS exists a move to reach XOR = 0 ✓
3. From XOR = 0, EVERY move leads to XOR ≠ 0 ✓

### Strategy
When XOR ≠ 0:
1. Compute total XOR = X
2. Find a pile nᵢ such that nᵢ ⊕ X < nᵢ
3. Reduce pile i from nᵢ to nᵢ ⊕ X

### Dry Run
```
Piles: [3, 5, 7]
XOR = 3 ⊕ 5 ⊕ 7 = 011 ⊕ 101 ⊕ 111 = 001 ≠ 0
→ First player wins!

Strategy: Find pile where nᵢ ⊕ 1 < nᵢ
  3 ⊕ 1 = 2 < 3 ✓ → Reduce pile from 3 to 2
  New state: [2, 5, 7], XOR = 010 ⊕ 101 ⊕ 111 = 000 = 0 → opponent in L state
```

---

## 2️⃣ Nim Variants

### Bounded Nim (can take at most m stones per turn)
```
Grundy(n) = n % (m + 1)
First player wins ⟺ n % (m + 1) ≠ 0
```

### Staircase Nim (CSES 1099)
- Stones on a staircase with steps 0, 1, 2, ..., n
- Move: take any number of stones from step i and move to step i-1
- **Key insight**: Only ODD-indexed steps matter!
- **Winner: XOR of stones on odd steps ≠ 0 → First wins**

### Wythoff's Nim (take from one pile OR equal from both)
- See Chapter 08 for details

---

## 3️⃣ Mex (Minimum Excludant)

### Definition
> mex(S) = smallest non-negative integer NOT in set S

### Examples
```
mex({0, 1, 2})    = 3
mex({1, 2, 3})    = 0
mex({0, 2, 3})    = 1
mex({})            = 0
mex({0, 1, 3, 4}) = 2
```

### Implementation
```cpp
int mex(set<int>& S) {
    int m = 0;
    while (S.count(m)) m++;
    return m;
}
```

---

## 4️⃣ Grundy Numbers (Sprague-Grundy Values)

### Definition
> For any game position P:
> **G(P) = mex({ G(P') : P' is reachable from P in one move })**

### Terminal positions: G(terminal) = mex({}) = 0

### Key Property
```
G(P) = 0  ⟺  P is a LOSING position
G(P) > 0  ⟺  P is a WINNING position
```

### Example: Take 1 or 2 stones from a pile of n
```
G(0) = mex({})           = 0   (L)
G(1) = mex({G(0)})       = mex({0}) = 1   (W)
G(2) = mex({G(1),G(0)})  = mex({1,0}) = 2   (W)
G(3) = mex({G(2),G(1)})  = mex({2,1}) = 0   (L)
G(4) = mex({G(3),G(2)})  = mex({0,2}) = 1   (W)
G(5) = mex({G(4),G(3)})  = mex({1,0}) = 2   (W)
G(6) = mex({G(5),G(4)})  = mex({2,1}) = 0   (L)

Pattern: G(n) = n % 3
```

---

## 5️⃣ Sprague-Grundy Theorem

### The Theorem
> Every position in an impartial game is equivalent to a Nim pile of size G(P).

### For Composite (Independent) Games
> If a game consists of independent sub-games G₁, G₂, ..., Gₖ:
> **G(total) = G(G₁) ⊕ G(G₂) ⊕ ... ⊕ G(Gₖ)**

### How to Solve Any Impartial Game
1. **Decompose** the game into independent sub-games
2. **Compute** Grundy number for each sub-game
3. **XOR** all Grundy numbers
4. **Result ≠ 0 → First wins, Result = 0 → Second wins**

---

## 6️⃣ Computing Grundy Numbers

### Brute Force (for small games)
```cpp
int grundy[MAXN];

void computeGrundy(int n, vector<int>& moves) {
    grundy[0] = 0;
    for (int i = 1; i <= n; i++) {
        set<int> reachable;
        for (int m : moves) {
            if (i >= m) reachable.insert(grundy[i - m]);
        }
        grundy[i] = mex(reachable);
    }
}
```

### Finding Patterns
Often Grundy numbers are **periodic** or follow a **simple formula**:
- Take 1..k: G(n) = n % (k+1)
- Take powers of 2: compute and look for pattern
- Take any divisor: compute and look for pattern

### CP Strategy
1. Compute Grundy for small values (n = 0..100)
2. Look for periodicity or formula
3. Use that formula for large n

---

## 🧠 Sprague-Grundy Cheat Sheet

| Game | Grundy Number | Pattern |
|------|---------------|---------|
| Nim (take any from one pile) | G(n) = n | Identity |
| Take 1..k from one pile | G(n) = n % (k+1) | Modular |
| Take from set S | Compute via mex | Often periodic |
| Multiple independent piles | XOR of individual Grundy | Theorem |
| Staircase Nim | XOR of odd-indexed steps | Classic variant |

---

## 🔗 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [Nim Game](https://leetcode.com/problems/nim-game/) | LeetCode 292 | Basic Nim |
| [Game of Nim](https://cses.fi/problemset/task/1730) | CSES | Classic Nim XOR |
| [Staircase Nim](https://cses.fi/problemset/task/1099) | CSES | Staircase Nim |
| [Grundy's Game](https://cses.fi/problemset/task/2207) | CSES | Sprague-Grundy |
| [Stick Game](https://cses.fi/problemset/task/1729) | CSES | Grundy / W-L states |
| [Nim Game II](https://cses.fi/problemset/task/1098) | CSES | Bounded Nim |
| [Another Game on Nim](https://codeforces.com/problemset/problem/1537/E) | Codeforces | Nim variant |
| [Game on Graph](https://codeforces.com/problemset/problem/936/B) | Codeforces | Graph game + Grundy |
| [Stone Game II](https://leetcode.com/problems/stone-game-ii/) | LeetCode 1140 | Game DP |
| [Stone Game IV](https://leetcode.com/problems/stone-game-iv/) | LeetCode 1510 | Grundy / W-L |

---

*Next: [08 — Combinatorial Game Theory →](../08_Combinatorial_Game_Theory/)*

