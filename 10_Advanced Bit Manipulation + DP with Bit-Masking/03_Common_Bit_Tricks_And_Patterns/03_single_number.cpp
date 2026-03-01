/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 03.03 — SINGLE NUMBER (XOR Trick)                        ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Given array where every element appears twice except one. Find it.
FORMULA: XOR all elements. Pairs cancel (a⊕a=0), single remains.

DRY RUN — [2,3,5,3,2]:
    2⊕3⊕5⊕3⊕2 = (2⊕2)⊕(3⊕3)⊕5 = 0⊕0⊕5 = 5 ✓

TIME: O(n), SPACE: O(1)
LeetCode 136: Single Number
*/
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

int singleNumber(vector<int>& nums) {
    int result = 0;
    for (int x : nums) result ^= x;
    return result;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   SINGLE NUMBER                                 ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    vector<int> arr1 = {2, 3, 5, 3, 2};
    cout << "  [2,3,5,3,2] → " << singleNumber(arr1) << endl;
    assert(singleNumber(arr1) == 5);

    vector<int> arr2 = {4, 1, 2, 1, 2};
    cout << "  [4,1,2,1,2] → " << singleNumber(arr2) << endl;
    assert(singleNumber(arr2) == 4);

    vector<int> arr3 = {1};
    assert(singleNumber(arr3) == 1);

    cout << "\n✅ Single number verified!" << endl;
    return 0;
}

