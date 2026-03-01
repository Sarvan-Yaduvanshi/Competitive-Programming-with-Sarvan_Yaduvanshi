/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 06.01 — PREFIX XOR                                       ║
║           Bit Manipulation — Bitwise Array Techniques                      ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

CONCEPT:
════════
    prefix[0] = 0
    prefix[i] = a[0] ⊕ a[1] ⊕ ... ⊕ a[i-1]

    XOR of subarray [L, R]:
    xor(L..R) = prefix[R+1] ⊕ prefix[L]

PROOF: prefix[R+1] ⊕ prefix[L]
    = (a[0]⊕...⊕a[R]) ⊕ (a[0]⊕...⊕a[L-1])
    = a[L] ⊕ a[L+1] ⊕ ... ⊕ a[R]   (common prefix cancels by XOR self-inverse)

DRY RUN — arr=[3,5,7,2]:
    prefix = [0, 3, 6, 1, 3]
    xor(1..3) = prefix[4] ⊕ prefix[1] = 3 ⊕ 3 = 0
    Verify: 5⊕7⊕2 = 0 ✓
    xor(0..2) = prefix[3] ⊕ prefix[0] = 1 ⊕ 0 = 1
    Verify: 3⊕5⊕7 = 1 ✓

TIME: O(n) build, O(1) query
*/
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   PREFIX XOR                                    ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    vector<int> arr = {3, 5, 7, 2};
    int n = arr.size();
    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) prefix[i+1] = prefix[i] ^ arr[i];

    cout << "\n  Array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    cout << "  Prefix XOR: ";
    for (int x : prefix) cout << x << " ";
    cout << endl;

    // Query
    auto queryXOR = [&](int L, int R) { return prefix[R+1] ^ prefix[L]; };

    cout << "\n--- Range XOR Queries ---" << endl;
    cout << "  XOR(1..3) = " << queryXOR(1, 3) << endl; // 5^7^2 = 0
    cout << "  XOR(0..2) = " << queryXOR(0, 2) << endl; // 3^5^7 = 1
    cout << "  XOR(0..3) = " << queryXOR(0, 3) << endl; // 3^5^7^2 = 3
    cout << "  XOR(2..2) = " << queryXOR(2, 2) << endl; // 7

    assert(queryXOR(1, 3) == (5^7^2));
    assert(queryXOR(0, 2) == (3^5^7));
    assert(queryXOR(2, 2) == 7);

    cout << "\n✅ Prefix XOR verified!" << endl;
    return 0;
}

