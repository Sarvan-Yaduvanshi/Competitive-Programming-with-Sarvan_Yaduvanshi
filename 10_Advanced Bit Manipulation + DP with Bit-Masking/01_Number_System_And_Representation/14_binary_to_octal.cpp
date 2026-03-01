/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 01.14 — BINARY TO OCTAL CONVERSION                       ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

ALGORITHM: Group binary bits into 3-bit groups from RIGHT, convert each to octal.

DRY RUN — 11101111₂ TO OCTAL:
══════════════════════════════
    Pad to 9 bits: 011 101 111
    Groups:  011  101  111
    Octal:    3    5    7
    Result: 357₈ ✓

TIME/SPACE: O(k)
*/

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

string binaryToOctal(string bin) {
    while (bin.size() % 3 != 0) bin = "0" + bin;
    string result = "";
    for (int i = 0; i < (int)bin.size(); i += 3) {
        int val = (bin[i]-'0')*4 + (bin[i+1]-'0')*2 + (bin[i+2]-'0');
        result += (char)('0' + val);
    }
    int start = 0;
    while (start < (int)result.size() - 1 && result[start] == '0') start++;
    return result.substr(start);
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   BINARY → OCTAL CONVERSION                     ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    cout << "11101111₂ = " << binaryToOctal("11101111") << "₈" << endl;  // 357
    cout << "1000₂     = " << binaryToOctal("1000") << "₈" << endl;      // 10
    cout << "111₂      = " << binaryToOctal("111") << "₈" << endl;       // 7

    assert(binaryToOctal("11101111") == "357");
    assert(binaryToOctal("1000") == "10");
    assert(binaryToOctal("111") == "7");

    cout << "\n✅ All binary to octal conversions verified!" << endl;
    return 0;
}

