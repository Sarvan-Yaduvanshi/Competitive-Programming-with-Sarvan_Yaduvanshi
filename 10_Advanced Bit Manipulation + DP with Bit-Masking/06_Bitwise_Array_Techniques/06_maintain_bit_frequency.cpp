/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 06.06 — MAINTAIN BIT FREQUENCY (0–31)                    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

CONCEPT: Maintain count[b] = number of elements with bit b set.
    Can reconstruct AND/OR of window from bit frequencies:
    - Bit b is 1 in AND ⟺ count[b] == window_size (all elements have it)
    - Bit b is 1 in OR  ⟺ count[b] > 0 (at least one has it)

USEFUL FOR: Sliding window AND/OR queries (add/remove elements).

DRY RUN — arr=[5,6,7], 3-element window:
    5=101, 6=110, 7=111
    freq[0]=2, freq[1]=2, freq[2]=3
    AND: only bit 2 has freq=3 → AND=4... wait 5&6&7=4 ✓
    OR: bits 0,1,2 have freq>0 → OR=7 ✓
*/
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   MAINTAIN BIT FREQUENCY (0-31)                 ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    vector<int> arr = {5, 6, 7};
    int n = arr.size();
    int freq[32] = {};

    // Add all elements
    for (int x : arr)
        for (int b = 0; b < 32; b++)
            if (x & (1 << b)) freq[b]++;

    cout << "\n  Array: [5(101), 6(110), 7(111)]" << endl;
    cout << "  Bit frequencies: ";
    for (int b = 0; b < 5; b++) cout << "bit" << b << "=" << freq[b] << " ";
    cout << endl;

    // Reconstruct AND and OR
    int andVal = 0, orVal = 0;
    for (int b = 0; b < 32; b++) {
        if (freq[b] == n) andVal |= (1 << b);
        if (freq[b] > 0) orVal |= (1 << b);
    }
    cout << "  AND = " << andVal << " (verify: " << (5&6&7) << ")" << endl;
    cout << "  OR  = " << orVal << " (verify: " << (5|6|7) << ")" << endl;

    // Sliding window demo
    cout << "\n--- Sliding Window AND (size=2) ---" << endl;
    vector<int> arr2 = {7, 6, 5, 4};
    int wFreq[32] = {};
    int w = 2;
    for (int i = 0; i < (int)arr2.size(); i++) {
        // Add arr2[i]
        for (int b = 0; b < 32; b++)
            if (arr2[i] & (1 << b)) wFreq[b]++;
        // Remove arr2[i-w] if window exceeded
        if (i >= w) {
            for (int b = 0; b < 32; b++)
                if (arr2[i-w] & (1 << b)) wFreq[b]--;
        }
        if (i >= w - 1) {
            int windowAND = 0;
            for (int b = 0; b < 32; b++)
                if (wFreq[b] == w) windowAND |= (1 << b);
            cout << "  Window [" << i-w+1 << ".." << i << "]: AND=" << windowAND << endl;
        }
    }

    cout << "\n✅ Bit frequency maintenance demonstrated!" << endl;
    return 0;
}

