/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 02.05 — SET i-th BIT                                     ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

FORMULA: n = n | (1 << i)
═════════════════════════
    Creates a mask with ONLY bit i set, then OR with n.
    OR with 1 forces that bit to 1, other bits unchanged (OR with 0).

DRY RUN — Set bit 1 in n=13 (1101₂):
    Mask: 1 << 1 = 0010
    n | mask = 1101 | 0010 = 1111 = 15 ✓

TIME: O(1)
*/

#include <iostream>
#include <bitset>
#include <cassert>
using namespace std;

int setBit(int n, int i) {
    return n | (1 << i);
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   SET i-th BIT                                  ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    int n = 13; // 1101₂
    cout << "\nOriginal: " << n << " = " << bitset<4>(n) << "₂" << endl;

    for (int i = 0; i < 4; i++) {
        int result = setBit(n, i);
        cout << "  Set bit " << i << ": " << bitset<4>(n) << " | " << bitset<4>(1<<i)
             << " = " << bitset<4>(result) << " = " << result << endl;
    }

    assert(setBit(13, 1) == 15);  // 1101 | 0010 = 1111
    assert(setBit(0, 3) == 8);    // 0000 | 1000 = 1000
    assert(setBit(13, 0) == 13);  // already set, no change

    cout << "\n✅ Set i-th bit verified!" << endl;
    return 0;
}

