/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 05.05 — BITMASK COMBINATION GENERATION                   ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TECHNIQUES for generating specific bitmask combinations:
    1. All masks of size k: Gosper's hack (see 05.03)
    2. All masks with constraint: iterate + filter
    3. Next combination: use Gosper's hack

EXAMPLE: Generate all 4-bit masks with bits 0 and 1 set (mandatory), others optional.
    Fix bits: mandatory = 0b0011
    Vary bits: optional = 0b1100
    For each submask of optional: result = mandatory | submask
*/
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

// Generate all masks with mandatory bits set and any subset of optional bits
vector<int> generateWithConstraint(int mandatory, int optional_bits) {
    vector<int> result;
    for (int s = optional_bits; ; s = (s - 1) & optional_bits) {
        result.push_back(mandatory | s);
        if (s == 0) break;
    }
    return result;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   BITMASK COMBINATION GENERATION                ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // Mandatory: bits 0,1. Optional: bits 2,3
    int mandatory = 0b0011;
    int optional_bits = 0b1100;
    auto masks = generateWithConstraint(mandatory, optional_bits);

    cout << "\n--- Mandatory={0,1}, Optional={2,3} ---" << endl;
    for (int m : masks) {
        cout << "  " << bitset<4>(m) << " (" << m << ")" << endl;
    }
    cout << "  Total: " << masks.size() << " = 2^" << __builtin_popcount(optional_bits) << endl;

    // Generate all masks with exactly k bits from a set
    cout << "\n--- All ways to choose 2 from {0,1,2,3} ---" << endl;
    int n = 4, k = 2;
    int mask = (1 << k) - 1;
    while (mask < (1 << n)) {
        cout << "  " << bitset<4>(mask) << " (" << mask << ")" << endl;
        int c = mask & (-mask);
        int r = mask + c;
        mask = (((r ^ mask) >> (__builtin_ctz(c) + 2))) | r;
    }

    cout << "\n✅ Bitmask combination generation demonstrated!" << endl;
    return 0;
}

