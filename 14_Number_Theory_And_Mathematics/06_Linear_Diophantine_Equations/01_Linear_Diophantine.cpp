/*
 * ============================================================================
 *  📘 01 — Linear Diophantine Equation: ax + by = c
 * ============================================================================
 *
 *  EXISTENCE: Solution exists iff gcd(a,b) | c
 *
 *  ONE SOLUTION:
 *    1. extgcd(a, b) → x0, y0 such that ax0 + by0 = g
 *    2. Scale: x = x0 * (c/g), y = y0 * (c/g)
 *
 *  ALL SOLUTIONS:
 *    x = x0 + (b/g)*t,  y = y0 - (a/g)*t  for any integer t
 *
 *  Reference: https://cp-algorithms.com/algebra/linear-diophantine-equation.html
 * ============================================================================
 */

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <cassert>

using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
#define nl '\n'

i64 extgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    i64 x1, y1;
    i64 g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// ============================================================================
//  📌 SOLVE ax + by = c
// ============================================================================
//  Returns true if solution exists, sets x, y to one solution.
// ============================================================================

bool solve_diophantine(i64 a, i64 b, i64 c, i64 &x, i64 &y) {
    i64 g = extgcd(abs(a), abs(b), x, y);
    if (c % g != 0) return false;  // no solution

    x *= c / g;
    y *= c / g;

    if (a < 0) x = -x;
    if (b < 0) y = -y;

    return true;
}

// ============================================================================
//  📌 FIND ALL SOLUTIONS IN RANGE
// ============================================================================
//  Given ax + by = c, find number of solutions with x in [x1, x2], y in [y1, y2]
// ============================================================================

// Ceiling division that works for negative numbers
i64 ceil_div(i64 a, i64 b) {
    return a / b + (a % b != 0 && (a ^ b) > 0);
}

i64 floor_div(i64 a, i64 b) {
    return a / b - (a % b != 0 && (a ^ b) < 0);
}

i64 count_solutions(i64 a, i64 b, i64 c, i64 x_lo, i64 x_hi, i64 y_lo, i64 y_hi) {
    i64 x, y;
    if (!solve_diophantine(a, b, c, x, y)) return 0;

    i64 g = __gcd(abs(a), abs(b));
    i64 step_x = b / g;  // x changes by b/g per step
    i64 step_y = -a / g; // y changes by -a/g per step

    if (step_x < 0) { step_x = -step_x; step_y = -step_y; }

    // t range from x constraints: x_lo <= x + step_x * t <= x_hi
    i64 t_lo, t_hi;
    if (step_x > 0) {
        t_lo = ceil_div(x_lo - x, step_x);
        t_hi = floor_div(x_hi - x, step_x);
    } else {
        t_lo = LLONG_MIN / 2;
        t_hi = LLONG_MAX / 2;
    }

    // t range from y constraints: y_lo <= y + step_y * t <= y_hi
    if (step_y > 0) {
        t_lo = max(t_lo, ceil_div(y_lo - y, step_y));
        t_hi = min(t_hi, floor_div(y_hi - y, step_y));
    } else if (step_y < 0) {
        t_lo = max(t_lo, ceil_div(y_hi - y, step_y));
        t_hi = min(t_hi, floor_div(y_lo - y, step_y));
    } else {
        // step_y == 0, y is fixed
        if (y < y_lo || y > y_hi) return 0;
    }

    return max(0LL, t_hi - t_lo + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Linear Diophantine Equations ===" << nl << nl;

    // Example 1: 3x + 5y = 7
    cout << "--- 3x + 5y = 7 ---" << nl;
    {
        i64 x, y;
        bool ok = solve_diophantine(3, 5, 7, x, y);
        cout << "Solution exists: " << (ok ? "YES" : "NO") << nl;
        if (ok) {
            cout << "One solution: x=" << x << ", y=" << y << nl;
            cout << "Check: 3×" << x << " + 5×" << y << " = " << 3*x + 5*y << nl;
            cout << "General: x=" << x << "+5t, y=" << y << "-3t" << nl;

            cout << "First few solutions:" << nl;
            i64 g = 1;
            for (int t = -3; t <= 3; t++) {
                i64 xi = x + 5*t, yi = y - 3*t;
                cout << "  t=" << t << ": x=" << xi << ", y=" << yi
                     << "  [check: " << 3*xi + 5*yi << "]" << nl;
            }
        }
    }

    // Example 2: 6x + 9y = 12
    cout << nl << "--- 6x + 9y = 12 ---" << nl;
    {
        i64 x, y;
        bool ok = solve_diophantine(6, 9, 12, x, y);
        cout << "gcd(6,9) = 3, 3 | 12 → " << (ok ? "YES" : "NO") << nl;
        if (ok) {
            cout << "x=" << x << ", y=" << y
                 << "  [check: " << 6*x + 9*y << "]" << nl;
        }
    }

    // Example 3: No solution: 6x + 9y = 7
    cout << nl << "--- 6x + 9y = 7 ---" << nl;
    {
        i64 x, y;
        bool ok = solve_diophantine(6, 9, 7, x, y);
        cout << "gcd(6,9) = 3, 3 ∤ 7 → " << (ok ? "YES" : "NO") << nl;
    }

    // Example 4: Coin problem (Frobenius)
    cout << nl << "--- Coin Problem: pay exactly N using coins of 3 and 5 ---" << nl;
    cout << "(3x + 5y = N, x ≥ 0, y ≥ 0)" << nl;
    for (int N = 1; N <= 20; N++) {
        i64 cnt = count_solutions(3, 5, N, 0, N, 0, N);
        cout << "N=" << N << ": " << cnt << " way(s)" << nl;
    }

    return 0;
}

