/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 06.02 — SUBARRAY XOR EQUALS K                            ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Find if any subarray has XOR = K.
KEY: xor(L..R) = prefix[R+1] ⊕ prefix[L] = K
     ⟹ prefix[L] = prefix[R+1] ⊕ K

METHOD: Use hashset of prefix XOR values. For each new prefix, check if prefix ⊕ K exists.

DRY RUN — arr=[4,2,2,6,4], K=6:
    prefix: 0,4,6,4,2,6
    At prefix=6 (index 2): need 6⊕6=0, exists (index 0) → subarray [0..1] ✓

TIME: O(n), SPACE: O(n)
LeetCode: subarray XOR problems
*/
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>
using namespace std;

bool subarrayXorEqualsK(vector<int>& arr, int k) {
    unordered_set<int> seen;
    int prefix = 0;
    seen.insert(0);
    for (int x : arr) {
        prefix ^= x;
        if (seen.count(prefix ^ k)) return true;
        seen.insert(prefix);
    }
    return false;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   SUBARRAY XOR = K                              ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    vector<int> arr = {4, 2, 2, 6, 4};
    cout << "  [4,2,2,6,4], K=6: " << (subarrayXorEqualsK(arr, 6) ? "YES" : "NO") << endl;
    assert(subarrayXorEqualsK(arr, 6) == true);

    cout << "  [4,2,2,6,4], K=100: " << (subarrayXorEqualsK(arr, 100) ? "YES" : "NO") << endl;
    assert(subarrayXorEqualsK(arr, 100) == false);

    cout << "\n✅ Subarray XOR = K verified!" << endl;
    return 0;
}

