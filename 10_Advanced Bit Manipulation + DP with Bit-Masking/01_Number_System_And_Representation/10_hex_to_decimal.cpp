/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 01.10 — HEXADECIMAL TO DECIMAL CONVERSION                ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

FORMULA: N = Σ (i=0 to k-1) [ h_i × 16^i ]

DRY RUN — 2F3₁₆:
    2×16² + F(15)×16¹ + 3×16⁰ = 512+240+3 = 755₁₀ ✓

HORNER'S: ((2)×16 + 15)×16 + 3 = (47)×16 + 3 = 755 ✓

TIME/SPACE: O(k)
*/

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int hexVal(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0;
}

long long hexToDecimal(const string& hex, bool trace = false) {
    long long result = 0;
    if (trace) cout << "  Horner's trace for " << hex << "₁₆:" << endl;
    for (int i = 0; i < (int)hex.size(); i++) {
        result = result * 16 + hexVal(hex[i]);
        if (trace) cout << "  Step " << i+1 << ": process '" << hex[i] << "'=" << hexVal(hex[i])
                        << " → result = " << result << endl;
    }
    return result;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   HEXADECIMAL → DECIMAL CONVERSION              ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    cout << "\n--- Convert 2F3₁₆ ---" << endl;
    long long r1 = hexToDecimal("2F3", true);
    cout << "  = " << r1 << "₁₀" << endl;

    cout << "\n--- Convert 3E8₁₆ ---" << endl;
    long long r2 = hexToDecimal("3E8", true);
    cout << "  = " << r2 << "₁₀" << endl;

    assert(r1 == 755);
    assert(r2 == 1000);
    assert(hexToDecimal("FF") == 255);
    assert(hexToDecimal("FFFF") == 65535);

    cout << "\n✅ All hex to decimal conversions verified!" << endl;
    return 0;
}

