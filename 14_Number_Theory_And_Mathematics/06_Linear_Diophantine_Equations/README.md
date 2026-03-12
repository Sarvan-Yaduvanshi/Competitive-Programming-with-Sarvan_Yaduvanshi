# 📘 Level 5 — Linear Diophantine Equations

> **Solving $ax + by = c$ in integers.** Foundation for many CP problems.  
> _Reference: [cp-algorithms.com — Linear Diophantine Equation](https://cp-algorithms.com/algebra/linear-diophantine-equation.html)_

---

## 📋 Topics Covered

| # | Topic | Key Idea |
|---|-------|----------|
| 1 | Existence of Solutions | gcd(a,b) \| c |
| 2 | Finding One Solution | Via Extended Euclidean |
| 3 | All Solutions | Parametric family |
| 4 | Counting Solutions in Range | Bounds on parameter |

---

## 1️⃣ The Equation: $ax + by = c$

### Theorem (Existence)
The equation $ax + by = c$ has integer solutions if and only if $\gcd(a, b) \mid c$.

### Proof
> **If $\gcd(a,b) \mid c$:** By Bézout, $\exists x_0, y_0: ax_0 + by_0 = g = \gcd(a,b)$.  
> Multiply by $c/g$: $a(x_0 \cdot c/g) + b(y_0 \cdot c/g) = c$. ✓  
>  
> **Only if:** If $ax + by = c$ has a solution, then $g \mid a$ and $g \mid b$ imply $g \mid (ax + by) = c$. ∎

---

## 2️⃣ Finding One Solution

### Algorithm
1. Use Extended Euclidean: find $x_0, y_0$ such that $ax_0 + by_0 = g$.
2. Scale: $x = x_0 \cdot (c / g)$, $y = y_0 \cdot (c / g)$.

### Dry Run: $3x + 5y = 7$

```
Step 1: gcd(3, 5) = 1, and 1 | 7 ✓ → solution exists
Step 2: extgcd(3, 5): 3×2 + 5×(-1) = 1
Step 3: Scale by 7: x = 2×7 = 14, y = (-1)×7 = -7
Check: 3×14 + 5×(-7) = 42 - 35 = 7 ✓
```

---

## 3️⃣ All Solutions (Parametric Form)

If $(x_0, y_0)$ is one solution of $ax + by = c$, then ALL solutions are:

$$x = x_0 + \frac{b}{g} \cdot t, \quad y = y_0 - \frac{a}{g} \cdot t$$

for any integer $t$.

### Proof
> If $ax_1 + by_1 = c$ and $ax_0 + by_0 = c$, subtract:  
> $a(x_1 - x_0) + b(y_1 - y_0) = 0$  
> $a(x_1 - x_0) = -b(y_1 - y_0)$  
> $(a/g)(x_1 - x_0) = -(b/g)(y_1 - y_0)$  
> Since $\gcd(a/g, b/g) = 1$, we need $(b/g) \mid (x_1 - x_0)$.  
> So $x_1 - x_0 = (b/g) \cdot t$ for some integer $t$. ∎

### Dry Run: All solutions of $3x + 5y = 7$

```
One solution: (14, -7)
g = gcd(3, 5) = 1

General solution: x = 14 + 5t, y = -7 - 3t

t = -3: x = -1, y = 2    Check: 3(-1) + 5(2) = 7 ✓
t = -2: x = 4,  y = -1   Check: 3(4) + 5(-1) = 7 ✓
t = 0:  x = 14, y = -7   Check: 3(14) + 5(-7) = 7 ✓
t = 1:  x = 19, y = -10  Check: 3(19) + 5(-10) = 7 ✓
```

---

## 4️⃣ Solutions in a Given Range

Find solutions where $x_{\min} \leq x \leq x_{\max}$ and $y_{\min} \leq y \leq y_{\max}$.

From $x = x_0 + (b/g) \cdot t$:
$$t_{\min}^{(x)} = \lceil (x_{\min} - x_0) / (b/g) \rceil$$
$$t_{\max}^{(x)} = \lfloor (x_{\max} - x_0) / (b/g) \rfloor$$

Similarly for $y$ constraints. Take intersection of $t$ ranges.

---

## 📁 Files in This Section

| File | Description |
|------|-------------|
| [01_Linear_Diophantine.cpp](01_Linear_Diophantine.cpp) | Solve ax + by = c |
| [02_All_Solutions.cpp](02_All_Solutions.cpp) | Enumerate solutions in range |

---

## 🎯 Practice Problems

| Problem | Platform | Technique |
|---------|----------|-----------|
| [CEQU](https://www.spoj.com/problems/CEQU/) | SPOJ | ax + by = c existence |
| [Indefinite Equation](https://codeforces.com/problemset/problem/1244/C) | CF 1244C | Diophantine + bounds |
| [Water Testing](https://atcoder.jp/contests/abc186/tasks/abc186_e) | AtCoder | Modular linear equation |
| 🟢 [Common Divisors](https://cses.fi/problemset/task/1081) | CSES | GCD / divisibility thinking |
| 🟢 [Exponentiation II](https://cses.fi/problemset/task/1712) | CSES | Euler thm → linear mod eq |

---
