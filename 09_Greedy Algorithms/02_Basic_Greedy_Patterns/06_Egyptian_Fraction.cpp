/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Egyptian Fraction — Greedy Decomposition
 *  Level   : Intermediate
 * ============================================================================
 *
 *  PROBLEM: Represent a fraction a/b as sum of distinct unit fractions 1/x.
 *  Example: 2/3 = 1/2 + 1/6
 *           6/14 = 1/3 + 1/11 + 1/231
 *
 *  GREEDY (Fibonacci's Algorithm):
 *  Repeatedly find the largest unit fraction 1/⌈b/a⌉ ≤ a/b, subtract it.
 *
 *  TIME: Not polynomial in worst case (can generate very large denominators)
 *        But works well in practice.
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<long long> egyptianFraction(long long a, long long b) {
    vector<long long> result;

    while (a > 0) {
        // Find smallest x such that 1/x ≤ a/b → x = ceil(b/a)
        long long x = (b + a - 1) / a; // ceil(b/a)
        result.push_back(x);

        // Subtract 1/x from a/b: a/b - 1/x = (a*x - b) / (b*x)
        a = a * x - b;
        b = b * x;

        // Simplify by GCD
        if (a > 0) {
            long long g = __gcd(a, b);
            a /= g;
            b /= g;
        }
    }

    return result;
}

int main() {
    long long a = 2, b = 3;
    cout << a << "/" << b << " = ";
    auto fractions = egyptianFraction(a, b);
    for (int i = 0; i < (int)fractions.size(); i++) {
        if (i > 0) cout << " + ";
        cout << "1/" << fractions[i];
    }
    cout << endl;
    // Output: 2/3 = 1/2 + 1/6

    a = 6; b = 14;
    cout << a << "/" << b << " = ";
    fractions = egyptianFraction(a, b);
    for (int i = 0; i < (int)fractions.size(); i++) {
        if (i > 0) cout << " + ";
        cout << "1/" << fractions[i];
    }
    cout << endl;

    return 0;
}

