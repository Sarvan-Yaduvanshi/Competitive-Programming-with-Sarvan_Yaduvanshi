/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 02.06 — CLEAR i-th BIT                                   ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

FORMULA: n = n & ~(1 << i)
═══════════════════════════
    Create mask with bit i set: (1 << i)
    Invert it: ~(1 << i) → all 1s EXCEPT position i
    AND with n: forces bit i to 0, others unchanged.

DRY RUN — Clear bit 2 in n=13 (1101₂):
    1 << 2   = 0100
    ~(1 << 2) = 1011
    n & mask  = 1101 & 1011 = 1001 = 9 ✓

TIME: O(1)
*/

#include <iostream>
#include <bitset>
#include <cassert>
using namespace std;

int clearBit(int n, int i) {
    return n & ~(1 << i);
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   CLEAR i-th BIT                                ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    int n = 13; // 1101₂
    cout << "\nOriginal: " << n << " = " << bitset<4>(n) << "₂" << endl;

    for (int i = 0; i < 4; i++) {
        int result = clearBit(n, i);
        cout << "  Clear bit " << i << ": " << bitset<4>(n) << " & " << bitset<4>(~(1<<i))
             << " = " << bitset<4>(result) << " = " << result << endl;
    }

    assert(clearBit(13, 2) == 9);  // 1101 & 1011 = 1001
    assert(clearBit(13, 0) == 12); // 1101 & 1110 = 1100
    assert(clearBit(13, 1) == 13); // bit 1 already 0, no change

    cout << "\n✅ Clear i-th bit verified!" << endl;
    return 0;
}

