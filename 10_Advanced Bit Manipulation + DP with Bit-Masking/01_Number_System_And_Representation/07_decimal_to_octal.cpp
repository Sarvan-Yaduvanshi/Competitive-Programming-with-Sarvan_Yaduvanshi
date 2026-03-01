/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 01.07 — DECIMAL TO OCTAL CONVERSION                      ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

ALGORITHM: Repeated division by 8, read remainders bottom→top.

    N mod 8 = least significant octal digit
    N / 8   = remaining value

DRY RUN — 239₁₀ TO OCTAL:
══════════════════════════
    Step  N      N÷8    N%8
    ─────────────────────────
    1     239    29     7   (o₀)
    2      29     3     5   (o₁)
    3       3     0     3   (o₂)
    Result: 357₈
    Verify: 3×64 + 5×8 + 7×1 = 192+40+7 = 239 ✓

DRY RUN — 500₁₀ TO OCTAL:
══════════════════════════
    500 ÷ 8 = 62 R 4
     62 ÷ 8 =  7 R 6
      7 ÷ 8 =  0 R 7
    Result: 764₈
    Verify: 7×64 + 6×8 + 4 = 448+48+4 = 500 ✓

TIME/SPACE: O(log₈ N)
*/

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

string decimalToOctal(long long n, bool trace = false) {
    if (n == 0) return "0";
    string result = "";
    if (trace) cout << "  Step  N\tN÷8\tN%8" << endl;
    int step = 1;
    while (n > 0) {
        int r = n % 8;
        long long q = n / 8;
        if (trace) cout << "  " << step++ << "     " << n << "\t" << q << "\t" << r << endl;
        result = (char)('0' + r) + result;
        n = q;
    }
    return result;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   DECIMAL → OCTAL CONVERSION                    ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    cout << "\n--- Convert 239₁₀ ---" << endl;
    string r1 = decimalToOctal(239, true);
    cout << "  Result: " << r1 << "₈" << endl;

    cout << "\n--- Convert 500₁₀ ---" << endl;
    string r2 = decimalToOctal(500, true);
    cout << "  Result: " << r2 << "₈" << endl;

    assert(r1 == "357");
    assert(r2 == "764");
    assert(decimalToOctal(0) == "0");
    assert(decimalToOctal(8) == "10");
    assert(decimalToOctal(255) == "377");

    cout << "\n✅ All decimal to octal conversions verified!" << endl;
    return 0;
}

