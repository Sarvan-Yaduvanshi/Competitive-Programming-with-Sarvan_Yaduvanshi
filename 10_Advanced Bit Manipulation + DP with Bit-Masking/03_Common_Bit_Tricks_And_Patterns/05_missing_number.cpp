/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 03.05 — MISSING NUMBER                                   ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Given array [0..n] with one missing. Find the missing number.

METHOD 1 (XOR): XOR all elements with 0,1,...,n → pairs cancel, missing remains.
    missing = (0⊕1⊕...⊕n) ⊕ (a₀⊕a₁⊕...⊕aₙ₋₁)

METHOD 2 (Math): missing = n(n+1)/2 - sum(array)

DRY RUN — [3,0,1] (n=3, missing=2):
    XOR(0..3) = 0⊕1⊕2⊕3 = 0  (since 3%4==3)
    XOR(array) = 3⊕0⊕1 = 2
    missing = 0 ⊕ 2 = 2 ✓

TIME: O(n), SPACE: O(1)
LeetCode 268: Missing Number
*/
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

int missingNumber_xor(vector<int>& nums) {
    int n = nums.size();
    int result = n;  // Start with n
    for (int i = 0; i < n; i++) {
        result ^= i ^ nums[i];  // XOR with index and value
    }
    return result;
}

int missingNumber_math(vector<int>& nums) {
    int n = nums.size();
    int expected = n * (n + 1) / 2;
    int actual = 0;
    for (int x : nums) actual += x;
    return expected - actual;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   MISSING NUMBER                                ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    vector<int> a1 = {3, 0, 1};
    cout << "  [3,0,1] → missing = " << missingNumber_xor(a1) << endl;
    assert(missingNumber_xor(a1) == 2);

    vector<int> a2 = {0, 1};
    cout << "  [0,1] → missing = " << missingNumber_xor(a2) << endl;
    assert(missingNumber_xor(a2) == 2);

    vector<int> a3 = {9,6,4,2,3,5,7,0,1};
    cout << "  [9,6,4,2,3,5,7,0,1] → missing = " << missingNumber_xor(a3) << endl;
    assert(missingNumber_xor(a3) == 8);

    cout << "\n✅ Missing number verified!" << endl;
    return 0;
}

