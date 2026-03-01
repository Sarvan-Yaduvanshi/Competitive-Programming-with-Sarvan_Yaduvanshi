/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 01.13 — OCTAL TO BINARY CONVERSION                       ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

KEY INSIGHT: 8 = 2³, so each octal digit = exactly 3 binary bits.

DRY RUN — 357₈ TO BINARY:
══════════════════════════
    3 = 011₂
    5 = 101₂
    7 = 111₂
    Result: 011101111₂ = 11101111₂
    Verify: 128+64+32+8+4+2+1 = 239₁₀, 357₈ = 239₁₀ ✓

MAPPING TABLE:
    0→000  1→001  2→010  3→011
    4→100  5→101  6→110  7→111

TIME/SPACE: O(k)
*/

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

string octalDigitToBinary(char c) {
    int val = c - '0';
    string bits = "";
    for (int i = 2; i >= 0; i--) bits += ((val >> i) & 1) ? '1' : '0';
    return bits;
}

string octalToBinary(const string& oct) {
    string result = "";
    for (char c : oct) result += octalDigitToBinary(c);
    int start = 0;
    while (start < (int)result.size() - 1 && result[start] == '0') start++;
    return result.substr(start);
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   OCTAL → BINARY CONVERSION                     ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    cout << "357₈ = " << octalToBinary("357") << "₂" << endl;   // 11101111
    cout << "764₈ = " << octalToBinary("764") << "₂" << endl;   // 111110100
    cout << "10₈  = " << octalToBinary("10") << "₂" << endl;    // 1000

    assert(octalToBinary("357") == "11101111");
    assert(octalToBinary("10") == "1000");
    assert(octalToBinary("7") == "111");

    cout << "\n✅ All octal to binary conversions verified!" << endl;
    return 0;
}

