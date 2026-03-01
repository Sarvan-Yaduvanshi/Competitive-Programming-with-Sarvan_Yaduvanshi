/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 04.04 — ITERATE ALL SUBSETS                              ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

METHOD: Simply iterate mask from 0 to 2^n - 1.
    for (int mask = 0; mask < (1 << n); mask++)

Each mask represents a unique subset. Total: 2ⁿ subsets.

DRY RUN — n=3, U={0,1,2}:
    mask=0(000)→{}, mask=1(001)→{0}, mask=2(010)→{1}, mask=3(011)→{0,1},
    mask=4(100)→{2}, mask=5(101)→{0,2}, mask=6(110)→{1,2}, mask=7(111)→{0,1,2}

TIME: O(2ⁿ) — exponential, only feasible for n ≤ 20-23.
*/
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

void printSubset(int mask, int n) {
    cout << "{";
    bool first = true;
    for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) {
            if (!first) cout << ",";
            cout << i;
            first = false;
        }
    }
    cout << "}";
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   ITERATE ALL SUBSETS                           ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    int n = 3;
    cout << "\n--- All 2^" << n << " = " << (1<<n) << " subsets of {0,1,...," << n-1 << "} ---" << endl;
    for (int mask = 0; mask < (1 << n); mask++) {
        cout << "  " << bitset<3>(mask) << " → ";
        printSubset(mask, n);
        cout << "  (size=" << __builtin_popcount(mask) << ")" << endl;
    }

    // Practical: sum of each subset
    cout << "\n--- Sum of Each Subset (arr={3,5,7}) ---" << endl;
    vector<int> arr = {3, 5, 7};
    n = arr.size();
    for (int mask = 0; mask < (1 << n); mask++) {
        int sum = 0;
        for (int i = 0; i < n; i++)
            if (mask & (1 << i)) sum += arr[i];
        cout << "  ";
        printSubset(mask, n);
        cout << " → sum=" << sum << endl;
    }

    cout << "\n✅ Iterate all subsets demonstrated!" << endl;
    return 0;
}

