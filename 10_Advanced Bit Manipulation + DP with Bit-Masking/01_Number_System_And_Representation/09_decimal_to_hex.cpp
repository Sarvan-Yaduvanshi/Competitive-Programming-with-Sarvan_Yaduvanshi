/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 01.09 — DECIMAL TO HEXADECIMAL CONVERSION                ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

ALGORITHM: Repeated division by 16, read remainders bottom→top.

DRY RUN — 755₁₀ TO HEX:
════════════════════════
    755 ÷ 16 = 47  R 3   → '3'
     47 ÷ 16 =  2  R 15  → 'F'
      2 ÷ 16 =  0  R 2   → '2'
    Result: 2F3₁₆
    Verify: 2×256 + 15×16 + 3 = 512+240+3 = 755 ✓

DRY RUN — 1000₁₀ TO HEX:
═════════════════════════
    1000 ÷ 16 = 62  R 8  → '8'
      62 ÷ 16 =  3  R 14 → 'E'
       3 ÷ 16 =  0  R 3  → '3'
    Result: 3E8₁₆
    Verify: 3×256 + 14×16 + 8 = 768+224+8 = 1000 ✓

TIME/SPACE: O(log₁₆ N)
*/

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

string decimalToHex(long long n, bool trace = false) {
    if (n == 0) return "0";
    string result = "";
    const char hexDigits[] = "0123456789ABCDEF";
    if (trace) cout << "  Step\tN\tN÷16\tN%16\tChar" << endl;
    int step = 1;
    while (n > 0) {
        int r = n % 16;
        long long q = n / 16;
        if (trace) cout << "  " << step++ << "\t" << n << "\t" << q << "\t" << r << "\t" << hexDigits[r] << endl;
        result = hexDigits[r] + result;
        n = q;
    }
    return result;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   DECIMAL → HEXADECIMAL CONVERSION              ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    cout << "\n--- Convert 755₁₀ ---" << endl;
    string r1 = decimalToHex(755, true);
    cout << "  Result: " << r1 << "₁₆" << endl;

    cout << "\n--- Convert 1000₁₀ ---" << endl;
    string r2 = decimalToHex(1000, true);
    cout << "  Result: " << r2 << "₁₆" << endl;

    assert(r1 == "2F3");
    assert(r2 == "3E8");
    assert(decimalToHex(255) == "FF");
    assert(decimalToHex(16) == "10");
    assert(decimalToHex(0) == "0");

    cout << "\n✅ All decimal to hex conversions verified!" << endl;
    return 0;
}

