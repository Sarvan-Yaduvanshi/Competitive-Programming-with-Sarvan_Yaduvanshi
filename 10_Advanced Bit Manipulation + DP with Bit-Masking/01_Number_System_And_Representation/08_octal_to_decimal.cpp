/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 01.08 — OCTAL TO DECIMAL CONVERSION                      ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

FORMULA: N = Σ (i=0 to k-1) [ o_i × 8^i ]

DRY RUN — 357₈:
    3×8² + 5×8¹ + 7×8⁰ = 192+40+7 = 239₁₀ ✓

HORNER'S METHOD (more efficient):
    Process left→right: ((3)×8 + 5)×8 + 7 = (29)×8 + 7 = 239 ✓

TIME/SPACE: O(k)
*/

#include <iostream>
#include <string>
#include <cmath>
#include <cassert>
using namespace std;

long long octalToDecimal_positional(const string& oct) {
    long long result = 0;
    int k = oct.size();
    cout << "  Positional expansion of " << oct << "₈:" << endl;
    for (int i = 0; i < k; i++) {
        int pos = k - 1 - i;
        int digit = oct[i] - '0';
        long long val = digit * (long long)pow(8, pos);
        cout << "  " << digit << " × 8^" << pos << " = " << val << endl;
        result += val;
    }
    return result;
}

long long octalToDecimal_horner(const string& oct) {
    long long result = 0;
    for (char c : oct) {
        result = result * 8 + (c - '0');
    }
    return result;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   OCTAL → DECIMAL CONVERSION                    ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    cout << "\n--- Positional: 357₈ ---" << endl;
    long long r1 = octalToDecimal_positional("357");
    cout << "  = " << r1 << "₁₀" << endl;

    cout << "\n--- Horner's: 764₈ ---" << endl;
    long long r2 = octalToDecimal_horner("764");
    cout << "  764₈ = " << r2 << "₁₀" << endl;

    assert(r1 == 239);
    assert(r2 == 500);
    assert(octalToDecimal_horner("377") == 255);
    assert(octalToDecimal_horner("10") == 8);

    cout << "\n✅ All octal to decimal conversions verified!" << endl;
    return 0;
}

