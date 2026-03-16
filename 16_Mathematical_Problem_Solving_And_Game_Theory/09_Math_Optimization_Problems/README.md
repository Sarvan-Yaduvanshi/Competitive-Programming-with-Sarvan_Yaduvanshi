# 📈 09 — Math Optimization Problems

> Advanced mathematical reasoning for optimization — greedy math, AM-GM, convexity, and inequality tricks that appear in hard contest problems and FAANG interviews.

---

## 📚 Topics Covered

| # | Topic | Key Idea |
|---|-------|----------|
| 1 | Greedy Math | Mathematical justification for greedy choices |
| 2 | AM-GM Inequality | Arithmetic Mean ≥ Geometric Mean — optimize products |
| 3 | Cauchy-Schwarz | Bounding sums of products |
| 4 | Convexity Arguments | Jensen's inequality, ternary search |
| 5 | Inequality Tricks | Rearrangement, Chebyshev's, power mean |
| 6 | Minimizing / Maximizing Expressions | Common optimization patterns |
| 7 | **Ternary Search** | Find extremum of unimodal function in O(log n) |
| 8 | **Binary Search on Answer** | "Minimize the max" or "Maximize the min" pattern |

---

## 1️⃣ Greedy Math

### When Greedy Works (Mathematical Proof)
1. **Exchange argument**: Show that swapping any two elements in a non-greedy solution improves or maintains the objective
2. **Stays ahead**: Show greedy is always ≥ optimal at every step

### Common Greedy Math Patterns

**Split n into parts to maximize product**:
- Split into as many 3s as possible!
- If remainder is 1: use one 4 instead of 3+1
- If remainder is 2: use one 2
- Why? AM-GM shows 3 is optimal split point (e/1 ≈ 2.718, closest integer = 3)

**Minimize sum of squares**:
- Distribute values as equally as possible (by convexity of x²)

**Maximize sum of products**:
- Sort and pair largest with largest (rearrangement inequality)

---

## 2️⃣ AM-GM Inequality

### Statement
> For non-negative reals a₁, a₂, ..., aₙ:
> **(a₁ + a₂ + ... + aₙ) / n ≥ (a₁ × a₂ × ... × aₙ)^(1/n)**
> Equality iff a₁ = a₂ = ... = aₙ

### Key Applications

**Maximize product with fixed sum**:
```
Given: a₁ + a₂ + ... + aₙ = S (fixed)
Maximize: a₁ × a₂ × ... × aₙ
Answer: All equal! Each aᵢ = S/n
```

**Minimize sum with fixed product**:
```
Given: a₁ × a₂ × ... × aₙ = P (fixed)
Minimize: a₁ + a₂ + ... + aₙ
Answer: All equal! Each aᵢ = P^(1/n)
```

### CP Application
- **Integer Break (LeetCode 343)**: Split n into integers to maximize product
  - Answer: Use 3s (and 2s for remainder)
  - Why: AM-GM → optimal real split is e ≈ 2.718 → round to 3

---

## 3️⃣ Convexity and Jensen's Inequality

### Convex Function
> f is convex if f(λx + (1-λ)y) ≤ λf(x) + (1-λ)f(y) for λ ∈ [0,1]

Common convex functions: x², eˣ, x log x, |x|

### Jensen's Inequality
> For convex f: f(Σaᵢ/n) ≤ Σf(aᵢ)/n

### Application: Minimizing Sum of Convex Functions
```
Minimize Σ f(xᵢ) subject to Σ xᵢ = S
→ By Jensen: optimal when all xᵢ equal = S/n
```

### Ternary Search (for unimodal functions)
If f is unimodal (one peak or valley), use ternary search to find the extremum:
```cpp
ld ternarySearchMin(ld lo, ld hi, function<ld(ld)> f) {
    for (int iter = 0; iter < 200; iter++) {
        ld m1 = lo + (hi - lo) / 3;
        ld m2 = hi - (hi - lo) / 3;
        if (f(m1) < f(m2)) hi = m2;
        else lo = m1;
    }
    return (lo + hi) / 2;
}
```

---

## 4️⃣ Rearrangement Inequality

### Statement
> For sorted sequences a₁ ≤ a₂ ≤ ... ≤ aₙ and b₁ ≤ b₂ ≤ ... ≤ bₙ:
> Σ aᵢbᵢ (same order) ≥ Σ aᵢbσ(i) (any permutation) ≥ Σ aᵢbₙ₊₁₋ᵢ (reverse order)

### Application
- **Maximize Σ aᵢbᵢ**: Sort both in same order
- **Minimize Σ aᵢbᵢ**: Sort in opposite orders
- **Minimize sum of absolute differences**: Sort and pair same indices

---

## 5️⃣ Common Optimization Patterns

### Pattern 1: Minimize Maximum
Often solved by **binary search on answer** + greedy check.

### Pattern 2: Maximize Minimum
Also binary search + greedy validation.

### Pattern 3: Minimize Sum of |xᵢ - c|
Optimal c = **median** of xᵢ values.

### Pattern 4: Minimize Sum of (xᵢ - c)²
Optimal c = **mean** of xᵢ values.

### Pattern 5: Maximize Product with Constraints
Use AM-GM or take logarithm to convert to sum maximization.

---

## 6️⃣ Ternary Search (Unimodal Function Optimization)

### When to Use
- Function has a single peak (maximum) or single valley (minimum)
- Need to find the x that gives extremum
- Works on both continuous and integer domains

### Algorithm
```
For MINIMUM of convex f on [lo, hi]:
  m1 = lo + (hi - lo) / 3
  m2 = hi - (hi - lo) / 3
  if f(m1) < f(m2): hi = m2
  else: lo = m1
  Repeat ~200 times for floating point, or until hi - lo < 3 for integer.
```

### Time: O(log(range / eps))

### CP Tips
- **Continuous**: 200 iterations gives ~10⁻¹⁵ precision
- **Integer**: stop when `hi - lo < 3`, then check all remaining
- Alternative: if f is differentiable, binary search on f'(x) = 0

---

## 7️⃣ Binary Search on Answer

### The Pattern
> "Minimize the maximum" or "Maximize the minimum" → Binary search the answer.

### Template
```cpp
i64 lo = min_possible, hi = max_possible;
while (lo < hi) {
    i64 mid = lo + (hi - lo) / 2;
    if (check(mid))  // can we achieve answer ≤ mid?
        hi = mid;
    else
        lo = mid + 1;
}
// answer = lo
```

### Classic Applications
| Problem Pattern | Binary Search On | Check Function |
|----------------|-----------------|----------------|
| Split array into k parts, minimize max sum | Max allowed sum | Greedy: can split into ≤ k parts? |
| Ship packages in d days, min capacity | Ship capacity | Greedy: can fit in d days? |
| Place k stations, minimize max gap | Max allowed gap | Count stations needed |
| Eating rate, finish in h hours | Eating speed | Count total hours needed |

---

## 🔗 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [Integer Break](https://leetcode.com/problems/integer-break/) | LeetCode 343 | AM-GM / Greedy |
| [Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/) | LeetCode 152 | DP optimization |
| [Minimum Moves to Equal Array](https://leetcode.com/problems/minimum-moves-to-equal-array-elements/) | LeetCode 453 | Math trick |
| [Minimize Max Diff of Pairs](https://leetcode.com/problems/minimize-the-maximum-difference-of-pairs/) | LeetCode 2616 | Binary search |
| [Best Time to Buy Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/) | LeetCode 121 | Greedy math |
| [Minimize Deviation](https://leetcode.com/problems/minimize-deviation-in-array/) | LeetCode 1675 | Greedy + heap |
| [Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/) | LeetCode 410 | BS on answer |
| [Capacity to Ship Packages](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/) | LeetCode 1011 | BS on answer |
| [Koko Eating Bananas](https://leetcode.com/problems/koko-eating-bananas/) | LeetCode 875 | BS on answer |
| [Codeforces Greedy Math](https://codeforces.com/problemset?tags=greedy,math) | Codeforces | Various |
| [Codeforces Ternary Search](https://codeforces.com/problemset?tags=ternary+search) | Codeforces | Ternary search |

---

*Next: [10 — Advanced Contest Math →](../10_Advanced_Contest_Math/)*

