/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 01.11 — BINARY TO HEXADECIMAL CONVERSION                 ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

KEY INSIGHT: 16 = 2⁴, so each hex digit = exactly 4 binary bits (nibble).

ALGORITHM:
══════════
    1. Pad binary from LEFT with 0s until length is multiple of 4
    2. Group into 4-bit nibbles from RIGHT to LEFT
    3. Convert each nibble to hex digit

DRY RUN — 11010110₂ TO HEX:
════════════════════════════
    Already 8 bits (multiple of 4). Group:
    1101  0110
      D     6
    Result: D6₁₆
    Verify: 13×16 + 6 = 214₁₀, 11010110₂ = 128+64+16+4+2 = 214 ✓

DRY RUN — 10110₂ TO HEX:
═════════════════════════
    5 bits → pad to 8: 00010110
    Group: 0001  0110
             1     6
    Result: 16₁₆
    Verify: 1×16+6 = 22₁₀, 10110₂ = 16+4+2 = 22 ✓

NIBBLE TABLE:
    0000→0  0100→4  1000→8  1100→C
    0001→1  0101→5  1001→9  1101→D
    0010→2  0110→6  1010→A  1110→E
    0011→3  0111→7  1011→B  1111→F

TIME/SPACE: O(k) where k = number of bits
*/

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

string nibbleToHex(const string& nibble) {
    int val = 0;
    for (char c : nibble) val = val * 2 + (c - '0');
    return string(1, "0123456789ABCDEF"[val]);
}

string binaryToHex(string bin) {
    // Pad to multiple of 4
    while (bin.size() % 4 != 0) bin = "0" + bin;

    string hex = "";
    for (int i = 0; i < (int)bin.size(); i += 4) {
        string nibble = bin.substr(i, 4);
        hex += nibbleToHex(nibble);
    }
    // Remove leading zeros
    int start = 0;
    while (start < (int)hex.size() - 1 && hex[start] == '0') start++;
    return hex.substr(start);
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   BINARY → HEXADECIMAL CONVERSION               ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    cout << "11010110₂ = " << binaryToHex("11010110") << "₁₆" << endl;  // D6
    cout << "10110₂    = " << binaryToHex("10110") << "₁₆" << endl;     // 16
    cout << "11111111₂ = " << binaryToHex("11111111") << "₁₆" << endl;  // FF

    assert(binaryToHex("11010110") == "D6");
    assert(binaryToHex("10110") == "16");
    assert(binaryToHex("11111111") == "FF");
    assert(binaryToHex("1") == "1");

    cout << "\n✅ All binary to hex conversions verified!" << endl;
    return 0;
}

