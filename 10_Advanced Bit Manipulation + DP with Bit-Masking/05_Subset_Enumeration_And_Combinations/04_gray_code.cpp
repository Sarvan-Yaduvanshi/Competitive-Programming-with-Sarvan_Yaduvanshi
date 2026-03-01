/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 05.04 — GRAY CODE                                        ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

DEFINITION: Gray code is a binary encoding where consecutive values differ by exactly 1 bit.

FORMULA: G(n) = n ⊕ (n >> 1)
INVERSE: Given gray code g, find n: n = g ⊕ (g>>1) ⊕ (g>>2) ⊕ ...

DRY RUN — First 8 Gray codes:
    n=0: G=0⊕0=0 (000)    n=4: G=4⊕2=6 (110)
    n=1: G=1⊕0=1 (001)    n=5: G=5⊕2=7 (111)
    n=2: G=2⊕1=3 (011)    n=6: G=6⊕3=5 (101)
    n=3: G=3⊕1=2 (010)    n=7: G=7⊕3=4 (100)

    Consecutive differ by 1 bit: 000→001→011→010→110→111→101→100 ✓

APPLICATIONS:
═════════════
    • Minimize bit flips in hardware
    • Solve Tower of Hanoi
    • Subset enumeration changing one element at a time
    • Error correction codes

LeetCode 89: Gray Code
*/
#include <iostream>
#include <vector>
#include <bitset>
#include <cassert>
using namespace std;

int toGray(int n) {
    return n ^ (n >> 1);
}

int fromGray(int g) {
    int n = 0;
    while (g) { n ^= g; g >>= 1; }
    return n;
}

vector<int> grayCodeSequence(int bits) {
    vector<int> result;
    for (int i = 0; i < (1 << bits); i++)
        result.push_back(toGray(i));
    return result;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   GRAY CODE                                     ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    cout << "\n--- 3-bit Gray Code Sequence ---" << endl;
    cout << "  n\tBinary\tGray\tGray Binary" << endl;
    auto seq = grayCodeSequence(3);
    for (int i = 0; i < 8; i++) {
        cout << "  " << i << "\t" << bitset<3>(i) << "\t" << seq[i]
             << "\t" << bitset<3>(seq[i]) << endl;
    }

    // Verify consecutive differ by 1 bit
    cout << "\n--- Verify: consecutive differ by exactly 1 bit ---" << endl;
    bool valid = true;
    for (int i = 0; i < 7; i++) {
        int diff = seq[i] ^ seq[i+1];
        bool oneBit = (diff & (diff-1)) == 0; // power of 2 = exactly 1 bit
        cout << "  " << bitset<3>(seq[i]) << " → " << bitset<3>(seq[i+1])
             << " diff=" << bitset<3>(diff) << (oneBit ? " ✓" : " ✗") << endl;
        if (!oneBit) valid = false;
    }
    assert(valid);

    // Inverse
    cout << "\n--- Gray → Binary (inverse) ---" << endl;
    for (int g : {0, 1, 3, 2, 6, 7, 5, 4}) {
        cout << "  Gray " << g << " → n = " << fromGray(g) << endl;
        assert(toGray(fromGray(g)) == g);
    }

    cout << "\n✅ Gray code verified!" << endl;
    return 0;
}

