/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 02.07 — TOGGLE i-th BIT                                  ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

FORMULA: n = n ^ (1 << i)
═════════════════════════
    XOR with 1 flips the bit: 0→1, 1→0
    XOR with 0 keeps the bit unchanged

DRY RUN — Toggle bit 2 in n=13 (1101₂):
    1101 ^ 0100 = 1001 = 9 (was 1, now 0)

Toggle bit 1 in n=13 (1101₂):
    1101 ^ 0010 = 1111 = 15 (was 0, now 1)

TIME: O(1)
*/

#include <iostream>
#include <bitset>
#include <cassert>
using namespace std;

int toggleBit(int n, int i) {
    return n ^ (1 << i);
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   TOGGLE i-th BIT                               ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    int n = 13;
    cout << "\nOriginal: " << n << " = " << bitset<4>(n) << "₂" << endl;

    for (int i = 0; i < 4; i++) {
        int result = toggleBit(n, i);
        cout << "  Toggle bit " << i << ": " << bitset<4>(n) << " ^ " << bitset<4>(1<<i)
             << " = " << bitset<4>(result) << " = " << result << endl;
    }

    // Double toggle = original
    cout << "\n--- Double Toggle = Original ---" << endl;
    int x = 42;
    cout << "  x = " << x << ", toggle bit 3 twice: "
         << toggleBit(toggleBit(x, 3), 3) << " (same!)" << endl;

    assert(toggleBit(13, 2) == 9);
    assert(toggleBit(13, 1) == 15);
    assert(toggleBit(toggleBit(42, 3), 3) == 42);

    cout << "\n✅ Toggle i-th bit verified!" << endl;
    return 0;
}

