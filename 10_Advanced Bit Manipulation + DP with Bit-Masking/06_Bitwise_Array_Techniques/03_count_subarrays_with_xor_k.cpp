/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 06.03 — COUNT SUBARRAYS WITH XOR K                       ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Count number of subarrays with XOR = K.
METHOD: Use hashmap to count prefix XOR frequencies.
    count += freq[prefix ⊕ K]

DRY RUN — arr=[4,2,2,6,4], K=6:
    prefix=0: freq={0:1}
    prefix=4: need 4⊕6=2, freq[2]=0, freq={0:1,4:1}
    prefix=6: need 6⊕6=0, freq[0]=1→count=1, freq={0:1,4:1,6:1}
    prefix=4: need 4⊕6=2, freq[2]=0, freq={0:1,4:2,6:1}
    prefix=2: need 2⊕6=4, freq[4]=2→count=3, freq={0:1,4:2,6:1,2:1}
    prefix=6: need 6⊕6=0, freq[0]=1→count=4, freq={0:1,4:2,6:2,2:1}
    Answer: 4 ✓

TIME: O(n), SPACE: O(n)
Codeforces: Subarrays XOR, similar to CSES problems
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>
using namespace std;

int countSubarrayXorK(vector<int>& arr, int k) {
    unordered_map<int, int> freq;
    int prefix = 0, count = 0;
    freq[0] = 1;
    for (int x : arr) {
        prefix ^= x;
        count += freq[prefix ^ k];
        freq[prefix]++;
    }
    return count;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   COUNT SUBARRAYS WITH XOR = K                  ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    vector<int> arr = {4, 2, 2, 6, 4};
    cout << "  [4,2,2,6,4], K=6: " << countSubarrayXorK(arr, 6) << endl;
    assert(countSubarrayXorK(arr, 6) == 4);

    vector<int> arr2 = {5, 6, 7, 8, 9};
    cout << "  [5,6,7,8,9], K=5: " << countSubarrayXorK(arr2, 5) << endl;

    cout << "\n✅ Count subarrays with XOR K verified!" << endl;
    return 0;
}

