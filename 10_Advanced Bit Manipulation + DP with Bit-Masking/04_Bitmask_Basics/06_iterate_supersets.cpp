/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 04.06 — ITERATE SUPERSETS                                ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Given mask m and universe size n, iterate all supermasks s ⊇ m.
    s is a superset of m if s contains all bits of m (and possibly more).
    Condition: (s & m) == m, or equivalently (s | m) == s.

METHOD: Iterate complements of submasks of ~m.
    complement = ((1<<n)-1) ^ m   (bits NOT in m)
    For each submask c of complement:
        superset = m | c

ALTERNATIVE (direct iteration):
    for (int s = m; s < (1<<n); s = (s + 1) | m)

DRY RUN — m=0101₂ (5), n=4:
    Supersets: 0101, 0111, 1101, 1111  (add any combo of bits 1,3)
    That's 2^(n-popcount(m)) = 2^2 = 4 supersets ✓
*/
#include <iostream>
#include <bitset>
#include <cassert>
using namespace std;

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   ITERATE SUPERSETS                             ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    int m = 0b0101; // {0, 2}
    int n = 4;
    int full = (1 << n) - 1;

    cout << "  m = " << bitset<4>(m) << ", n = " << n << endl;

    // Method 1: Iterate using (s+1)|m trick
    cout << "\n--- Method 1: (s+1)|m ---" << endl;
    int count = 0;
    for (int s = m; s < (1 << n); s = (s + 1) | m) {
        cout << "  " << bitset<4>(s) << " (" << s << ")" << endl;
        assert((s & m) == m); // verify it's a superset
        count++;
    }
    cout << "  Count: " << count << " (= 2^" << (n - __builtin_popcount(m)) << ")" << endl;

    // Method 2: Complement submask method
    cout << "\n--- Method 2: complement submasks ---" << endl;
    int complement = full ^ m;
    int count2 = 0;
    for (int c = complement; ; c = (c - 1) & complement) {
        int superset = m | c;
        cout << "  " << bitset<4>(superset) << " (" << superset << ")" << endl;
        count2++;
        if (c == 0) break;
    }
    assert(count == count2);

    cout << "\n✅ Superset iteration verified!" << endl;
    return 0;
}

