/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 03.06 — FIND DUPLICATE USING XOR                         ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Array of n+1 integers in [1,n], exactly one duplicate. Find it.
METHOD: XOR all elements with 1..n → duplicate remains.
    result = (a₀⊕a₁⊕...⊕aₙ) ⊕ (1⊕2⊕...⊕n)
    All non-duplicate values cancel, duplicate XORed odd number of times remains.

DRY RUN — [1,3,4,2,2] (n=4):
    XOR array = 1⊕3⊕4⊕2⊕2 = 1⊕3⊕4⊕(2⊕2) = 1⊕3⊕4 = 6
    XOR 1..4  = 1⊕2⊕3⊕4 = 4
    result = 6 ⊕ 4 = 2 ✓

NOTE: This only works if exactly one number is duplicated exactly once extra.
      For general duplicate finding, use Floyd's cycle detection.

TIME: O(n), SPACE: O(1)
LeetCode 287: Find the Duplicate Number (general version needs different approach)
*/
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

int findDuplicate_xor(vector<int>& nums) {
    int n = nums.size() - 1;
    int result = 0;
    for (int x : nums) result ^= x;
    for (int i = 1; i <= n; i++) result ^= i;
    return result;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   FIND DUPLICATE USING XOR                      ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    vector<int> a1 = {1, 3, 4, 2, 2};
    cout << "  [1,3,4,2,2] → duplicate = " << findDuplicate_xor(a1) << endl;
    assert(findDuplicate_xor(a1) == 2);

    vector<int> a2 = {3, 1, 3, 4, 2};
    cout << "  [3,1,3,4,2] → duplicate = " << findDuplicate_xor(a2) << endl;
    assert(findDuplicate_xor(a2) == 3);

    cout << "\n✅ Find duplicate using XOR verified!" << endl;
    return 0;
}

