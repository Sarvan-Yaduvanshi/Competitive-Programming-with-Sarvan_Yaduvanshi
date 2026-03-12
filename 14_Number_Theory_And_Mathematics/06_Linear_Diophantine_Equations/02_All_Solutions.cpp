/*
 * ============================================================================
 *  📘 02 — All Solutions of ax + by = c in a Given Range
 * ============================================================================
 *
 *  Given ax + by = c, find ALL solutions where x ∈ [x_min, x_max]
 *  and y ∈ [y_min, y_max].
 *
 *  GENERAL SOLUTION: x = x₀ + (b/g)t, y = y₀ - (a/g)t
 *
 *  Algorithm:
 *    1. Find one solution (x₀, y₀) via ExtGCD
 *    2. Compute t range from x bounds
 *    3. Compute t range from y bounds
 *    4. Intersect the two ranges
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
#include <algorithm>
#include <cmath>
#include <numeric>
#include <cassert>

using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
using pll = pair<i64, i64>;
#define nl '\n'
#define sz(x) ((int)(x).size())

i64 extgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    i64 x1, y1;
    i64 g = extgcd(b, a % b, x1, y1);
    x = y1; y = x1 - (a / b) * y1;
    return g;
}

// Floor division (handles negative correctly)
i64 floor_div(i64 a, i64 b) {
    return a / b - (a % b != 0 && (a ^ b) < 0);
}
i64 ceil_div(i64 a, i64 b) {
    return a / b + (a % b != 0 && (a ^ b) > 0);
}

// Count solutions of ax + by = c with x in [x_lo, x_hi], y in [y_lo, y_hi]
// Returns count, and also first/last valid (x, y) if needed
i64 count_solutions(i64 a, i64 b, i64 c, i64 x_lo, i64 x_hi, i64 y_lo, i64 y_hi) {
    i64 x0, y0;
    i64 g = extgcd(abs(a), abs(b), x0, y0);
    if (c % g != 0) return 0;

    if (a < 0) { x0 = -x0; a = -a; }
    if (b < 0) { y0 = -y0; b = -b; }

    x0 *= c / g;
    y0 *= c / g;

    i64 step_x = b / g;  // b/g
    i64 step_y = a / g;  // a/g

    // x = x0 + step_x * t  →  t range from x bounds
    // y = y0 - step_y * t  →  t range from y bounds

    i64 t_lo = LLONG_MIN / 2, t_hi = LLONG_MAX / 2;

    // From x bounds: x_lo ≤ x0 + step_x * t ≤ x_hi
    if (step_x > 0) {
        t_lo = max(t_lo, ceil_div(x_lo - x0, step_x));
        t_hi = min(t_hi, floor_div(x_hi - x0, step_x));
    } else if (step_x < 0) {
        t_lo = max(t_lo, ceil_div(x_hi - x0, step_x));
        t_hi = min(t_hi, floor_div(x_lo - x0, step_x));
    } else {
        if (x0 < x_lo || x0 > x_hi) return 0;
    }

    // From y bounds: y_lo ≤ y0 - step_y * t ≤ y_hi
    // -y_hi ≤ -y0 + step_y * t ≤ -y_lo
    // step_y * t ∈ [y0 - y_hi, y0 - y_lo]
    if (step_y > 0) {
        t_lo = max(t_lo, ceil_div(y0 - y_hi, step_y));
        t_hi = min(t_hi, floor_div(y0 - y_lo, step_y));
    } else if (step_y < 0) {
        t_lo = max(t_lo, ceil_div(y0 - y_lo, step_y));
        t_hi = min(t_hi, floor_div(y0 - y_hi, step_y));
    } else {
        if (y0 < y_lo || y0 > y_hi) return 0;
    }

    if (t_lo > t_hi) return 0;
    return t_hi - t_lo + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== All Solutions in Range ===" << nl << nl;

    // 3x + 5y = 7, x ∈ [-100, 100], y ∈ [-100, 100]
    cout << "--- 3x + 5y = 7, x,y ∈ [-10, 10] ---" << nl;
    i64 cnt = count_solutions(3, 5, 7, -10, 10, -10, 10);
    cout << "Count = " << cnt << nl;

    // Brute force verify
    int brute = 0;
    for (int x = -10; x <= 10; x++)
        for (int y = -10; y <= 10; y++)
            if (3*x + 5*y == 7) { cout << "  x=" << x << " y=" << y << nl; brute++; }
    cout << "Brute: " << brute << (cnt == brute ? " ✓" : " ✗") << nl;

    // 2x + 4y = 7 → no solution (gcd(2,4)=2, 2 ∤ 7)
    cout << nl << "--- 2x + 4y = 7 ---" << nl;
    cout << "Count = " << count_solutions(2, 4, 7, -100, 100, -100, 100) << " (no solution)" << nl;

    return 0;
}

