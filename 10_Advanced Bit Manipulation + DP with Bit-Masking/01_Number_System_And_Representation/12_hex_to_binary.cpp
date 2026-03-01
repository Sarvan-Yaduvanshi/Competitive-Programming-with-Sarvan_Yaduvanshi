/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 01.12 — HEXADECIMAL TO BINARY CONVERSION                 ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

KEY INSIGHT: Each hex digit → exactly 4 binary bits.

DRY RUN — D6₁₆ TO BINARY:
══════════════════════════
    D = 13 = 1101₂
    6 =  6 = 0110₂
    Result: 11010110₂ ✓

DRY RUN — 3E8₁₆ TO BINARY:
═══════════════════════════
    3 = 0011₂
    E = 14 = 1110₂
    8 = 1000₂
    Result: 001111101000₂ = 1111101000₂ (remove leading zeros)

TIME/SPACE: O(k) where k = number of hex digits
*/

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

string hexDigitToBinary(char c) {
    int val;
    if (c >= '0' && c <= '9') val = c - '0';
    else if (c >= 'A' && c <= 'F') val = c - 'A' + 10;
    else val = c - 'a' + 10;

    string bits = "";
    for (int i = 3; i >= 0; i--) bits += ((val >> i) & 1) ? '1' : '0';
    return bits;
}

string hexToBinary(const string& hex) {
    string result = "";
    for (char c : hex) result += hexDigitToBinary(c);
    // Remove leading zeros
    int start = 0;
    while (start < (int)result.size() - 1 && result[start] == '0') start++;
    return result.substr(start);
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   HEXADECIMAL → BINARY CONVERSION               ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    cout << "D6₁₆  = " << hexToBinary("D6") << "₂" << endl;
    cout << "3E8₁₆ = " << hexToBinary("3E8") << "₂" << endl;
    cout << "FF₁₆  = " << hexToBinary("FF") << "₂" << endl;

    assert(hexToBinary("D6") == "11010110");
    assert(hexToBinary("FF") == "11111111");
    assert(hexToBinary("1") == "1");

    cout << "\n✅ All hex to binary conversions verified!" << endl;
    return 0;
}

