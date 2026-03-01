/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 04.03 — COUNT BITS IN MASK                               ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

= popcount(mask) = |S| = number of elements in subset S.
Use __builtin_popcount(mask) for O(1).
See Chapter 02.08 for full details on counting set bits.
*/
#include <iostream>
#include <bitset>
#include <cassert>
using namespace std;

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   COUNT BITS IN MASK                            ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    for (int mask : {0, 0b0101, 0b1111, 0b10101010, 0b11111111}) {
        cout << "  mask=" << bitset<8>(mask) << ": |S|=" << __builtin_popcount(mask) << endl;
    }

    // DP trick: popcount[mask] = popcount[mask >> 1] + (mask & 1)
    cout << "\n--- DP Popcount for all masks 0..15 ---" << endl;
    int pc[16];
    pc[0] = 0;
    for (int m = 1; m < 16; m++) {
        pc[m] = pc[m >> 1] + (m & 1);
        cout << "  pc[" << m << "] = pc[" << (m>>1) << "] + " << (m&1)
             << " = " << pc[m] << endl;
        assert(pc[m] == __builtin_popcount(m));
    }

    cout << "\n✅ Count bits in mask verified!" << endl;
    return 0;
}

