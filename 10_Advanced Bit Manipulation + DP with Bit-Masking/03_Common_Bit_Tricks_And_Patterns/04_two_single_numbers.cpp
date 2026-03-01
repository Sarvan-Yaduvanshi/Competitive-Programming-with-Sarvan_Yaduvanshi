/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 03.04 — TWO SINGLE NUMBERS                               ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Array where every element appears twice except TWO elements. Find both.

ALGORITHM:
══════════
    1. XOR all → x = a ⊕ b (pairs cancel, we get XOR of the two singles)
    2. Find any set bit in x (use x & (-x) for lowest set bit)
       This bit is where a and b DIFFER.
    3. Partition array into two groups based on that bit.
       Each group has one single element + pairs.
    4. XOR each group separately.

DRY RUN — [1,2,3,2,1,4]:
    Step 1: XOR all = 1⊕2⊕3⊕2⊕1⊕4 = 3⊕4 = 7 (111₂)
    Step 2: Differentiating bit = 7 & (-7) = 1 (bit 0)
    Step 3: Bit 0 set: {1,3,1} → XOR = 3
            Bit 0 not set: {2,2,4} → XOR = 4
    Answer: {3, 4} ✓

TIME: O(n), SPACE: O(1)
LeetCode 260: Single Number III
*/
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

pair<int,int> twoSingleNumbers(vector<int>& nums) {
    int xorAll = 0;
    for (int x : nums) xorAll ^= x;  // a ⊕ b

    int diffBit = xorAll & (-xorAll);  // lowest set bit where a,b differ

    int group1 = 0, group2 = 0;
    for (int x : nums) {
        if (x & diffBit) group1 ^= x;
        else group2 ^= x;
    }
    return {min(group1, group2), max(group1, group2)};
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   TWO SINGLE NUMBERS                            ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    vector<int> arr = {1, 2, 3, 2, 1, 4};
    auto [a, b] = twoSingleNumbers(arr);
    cout << "  [1,2,3,2,1,4] → {" << a << ", " << b << "}" << endl;
    assert(a == 3 && b == 4);

    vector<int> arr2 = {1, 2, 1, 3, 2, 5};
    auto [c, d] = twoSingleNumbers(arr2);
    cout << "  [1,2,1,3,2,5] → {" << c << ", " << d << "}" << endl;
    assert(c == 3 && d == 5);

    cout << "\n✅ Two single numbers verified!" << endl;
    return 0;
}

