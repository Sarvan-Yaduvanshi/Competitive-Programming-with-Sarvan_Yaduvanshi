# 📐 01 — Math Problem Solving Foundations

> The essential mathematical reasoning toolkit for competitive programming and FAANG interviews. These principles appear in *constructive*, *proof-based*, and *ad-hoc* problems across all platforms.

---

## 📚 Topics Covered

| # | Topic | Key Idea |
|---|-------|----------|
| 1 | Pigeonhole Principle | If n+1 objects go into n boxes, some box has ≥ 2 |
| 2 | Parity Arguments | Odd/even analysis to prove impossibility or determine winner |
| 3 | Invariants | A quantity that never changes — proves states unreachable |
| 4 | Monovariants | A quantity that strictly increases/decreases — proves termination |
| 5 | Mathematical Induction | Base case + inductive step — proves statements for all n |
| 6 | Counting Arguments | Counting the same thing two ways, double counting |
| 7 | Symmetry in Problems | Exploit symmetrical structure to simplify |
| 8 | **Constructive Algorithms** | Build a valid answer that satisfies all constraints |
| 9 | **Floor / Ceiling Tricks** | ⌊a/b⌋, ⌈a/b⌉ properties — crucial for math problems |

---

## 1️⃣ Pigeonhole Principle

### Definition
> If **n + 1** objects are placed into **n** containers, then at least one container has **at least 2** objects.

**Generalized**: If **kn + 1** objects → **n** containers, some container has **≥ k + 1** objects.

### Classic Examples

**Example 1**: Among any 13 integers, at least 2 have the same remainder mod 12.
- 13 numbers, 12 possible remainders → pigeonhole!

**Example 2**: In a sequence of n+1 distinct integers from {1, ..., 2n}, there exist two that are consecutive.
- Pair up: (1,2), (3,4), ..., (2n-1,2n) → n pairs, n+1 numbers → two land in the same pair.

### CP Application
**Problem**: Given an array of n+1 integers in range [1, n], find a duplicate. (LeetCode 287)
- By pigeonhole, a duplicate must exist.
- Floyd's cycle detection solves it in O(n) time, O(1) space.

### Tips for CP
- Look for pigeonhole when the **number of objects > number of categories**
- Remainder-based pigeonhole: n+1 numbers → n possible remainders
- Substring pigeonhole: if string length > 26², some length-2 substring repeats

---

## 2️⃣ Parity Arguments (Odd/Even Analysis)

### Key Idea
> Many problems become trivial once you analyze the **parity** (odd vs even) of some quantity.

### Classic Applications

**Chessboard Coloring**: A standard 8×8 chessboard with 2 opposite corners removed cannot be tiled by 2×1 dominoes.
- Each domino covers 1 black + 1 white square
- Removing 2 same-color corners leaves 30 of one color and 32 of the other → impossible

**Sum Parity**: If you can only add/subtract odd numbers, the parity of the total changes each step. So you can never reach an even number from an odd starting point in an odd number of steps.

### CP Patterns
1. **Game winner by parity**: If total moves is odd → first player wins, even → second player wins
2. **Array manipulation**: Some operations preserve parity of sum/count
3. **Graph coloring**: Bipartiteness is a parity argument on cycle lengths

### Template Thinking
```
if (total_moves % 2 == 1) → First player wins
else → Second player wins
```

---

## 3️⃣ Invariants

### Definition
> An **invariant** is a property that remains unchanged under all allowed operations.

### How to Use Invariants
1. **Identify** a quantity preserved by every operation
2. **Check** the invariant's value at start vs desired end
3. If they **differ** → impossible; if they **match** → construct the solution

### Classic Example: Coin Flip Puzzle
You have n coins, all heads up. Each move: flip exactly 3 coins. Can you make all tails?
- **Invariant**: parity of the number of heads
- Start: n heads (parity = n % 2)
- Flipping 3 coins changes the number of heads by ±3 or ±1 → parity always changes
- End goal: 0 heads (even parity)
- If n is odd → you can never reach 0 heads (parity mismatch)

### CP Tip
> When a problem says "is it possible to reach state X?", **look for an invariant first**.

---

## 4️⃣ Monovariants

### Definition
> A **monovariant** is a quantity that **strictly increases or decreases** with each operation. Since it's bounded, the process must **terminate**.

### Classic Example
**Problem**: Given n points in a plane, repeatedly find the closest pair and merge them into their midpoint. Prove this terminates.
- **Monovariant**: The maximum distance between any two points strictly decreases
- Bounded below by 0 → terminates

### CP Application
> Monovariants prove that greedy algorithms terminate and help bound the number of operations.

**Example**: Array operations where each step decreases the sum → at most `initial_sum` steps.

---

## 5️⃣ Mathematical Induction

### Structure
1. **Base case**: Prove P(1) (or P(0))
2. **Inductive step**: Assume P(k), prove P(k+1)
3. **Conclusion**: P(n) holds for all n ≥ 1

### Strong Induction
- Assume P(1), P(2), ..., P(k) are all true, prove P(k+1)
- Useful when you need more than just the previous case

### CP Application
- Proving correctness of recursive/DP solutions
- Proving game theory strategies (if all positions < n are correctly classified, classify position n)
- Proving formulas (sum of first n odds = n², etc.)

---

## 6️⃣ Counting Arguments

### Double Counting
> Count the same set in two different ways to derive an identity.

**Example**: Handshaking Lemma
- Sum of all vertex degrees = 2 × number of edges
- Left side counts each edge endpoint; right side counts each edge twice

### Bijection Principle
> If there's a bijection between sets A and B, then |A| = |B|.

### CP Application
- Counting paths, arrangements, valid states
- Proving that two seemingly different formulas give the same answer

---

## 7️⃣ Symmetry in Problems

### Key Idea
> If a problem has symmetry, exploit it to reduce work or simplify arguments.

### Types of Symmetry
1. **Rotational**: Circular arrangements — fix one element, arrange the rest
2. **Reflective**: Palindrome problems — work from both ends
3. **Player symmetry**: In some games, both players have identical strategies
4. **Complement symmetry**: Sometimes counting the complement is easier

### CP Application
- Circular permutation: n!/n = (n-1)!
- In a symmetric game, if first player has a winning strategy, they can "mirror" second player
- Count arrangements where property holds = Total - arrangements where property doesn't hold

---

## 8️⃣ Constructive Algorithms (Codeforces Staple)

### Key Idea
> Instead of proving a solution exists, **build one** that satisfies all constraints.

### Common Strategies
1. **Greedy construction**: Build the answer left-to-right, making locally optimal choices
2. **Start from a known good state**: Begin with a trivial valid arrangement and modify
3. **Use the parity/invariant**: If you've proven something must exist, construct it by maintaining the invariant
4. **Transform the problem**: Sometimes easier to construct the inverse, complement, or reversed version

### CP Tips
- Codeforces tags: `constructive algorithms` — one of the most common tags
- Often combined with parity, invariants, or greedy reasoning
- If the problem says "print any valid answer" → constructive approach

---

## 9️⃣ Floor / Ceiling Function Tricks

### Key Formulas
```
⌈a/b⌉ = ⌊(a + b - 1) / b⌋ = (a + b - 1) / b    (for positive a, b in C++)
⌊a/b⌋ = a / b                                       (integer division in C++)
```

### Important Properties
```
⌊a/b⌋ takes at most O(√a) distinct values as b ranges over 1..a
    → Basis for "harmonic lemma" and sum optimizations

Σ_{i=1}^{n} ⌊n/i⌋ ≈ n × ln(n) + O(n)    (harmonic sum)

⌊⌊a/b⌋/c⌋ = ⌊a/(b×c)⌋                    (floor composition)

a mod b = a - b × ⌊a/b⌋
```

### CP Application
- **Counting divisors in range**: group by ⌊n/i⌋ values → O(√n) blocks
- **Binary search with floor**: be careful with rounding direction
- **Distribute n items into k groups**: ⌊n/k⌋ and ⌈n/k⌉

---

## 🧠 Quick Reference

| Technique | When to Use | Key Question |
|-----------|-------------|-------------|
| Pigeonhole | Objects > Categories | "Must some category have ≥ 2?" |
| Parity | Operations change odd/even | "Does parity ever change?" |
| Invariant | "Is it reachable?" | "What quantity never changes?" |
| Monovariant | "Does it terminate?" | "What quantity always goes one way?" |
| Induction | Prove for all n | "Can I build case n+1 from case n?" |
| Counting | Derive identity / count set | "Can I count this two ways?" |
| Symmetry | Reduce complexity | "Is there a mirror / rotation?" |
| Constructive | "Print any valid answer" | "Can I build a solution step by step?" |
| Floor/Ceiling | Integer division / distribution | "How many groups / remainder?" |

---

## 🔗 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/) | LeetCode 287 | Pigeonhole |
| [Domino and Tromino Tiling](https://leetcode.com/problems/domino-and-tromino-tiling/) | LeetCode 790 | Invariant / Recurrence |
| [Chessboard Coloring](https://codeforces.com/problemset/problem/1879/A) | Codeforces | Parity |
| [Constructive Problems](https://codeforces.com/problemset?tags=constructive+algorithms) | Codeforces | Invariant, Parity |
| [Game of Nim](https://cses.fi/problemset/task/1730) | CSES | Parity / XOR |

---

*Next: [02 — Number Pattern Problems →](../02_Number_Pattern_Problems/)*

