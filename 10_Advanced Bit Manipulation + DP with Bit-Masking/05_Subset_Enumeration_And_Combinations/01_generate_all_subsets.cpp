/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 05.01 — GENERATE ALL SUBSETS                             ║
║           Bit Manipulation — Subset Enumeration                            ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

Three methods to generate all subsets of {0, 1, ..., n-1}:
    1. Bitmask iteration: for mask = 0 to 2^n - 1
    2. Recursive backtracking: include/exclude each element
    3. Iterative buildup: start from {{}}, double subsets per element

BITMASK METHOD (simplest for CP):
    for (int mask = 0; mask < (1 << n); mask++)
        // mask represents a subset

APPLICATION: Brute force all subsets for n ≤ 20.
    n=15: 32768 subsets
    n=20: ~10⁶ subsets
    n=23: ~8×10⁶ subsets (borderline)

TIME: O(n × 2ⁿ), SPACE: O(n) per subset
LeetCode 78: Subsets
*/
#include <iostream>
#include <vector>
using namespace std;

// Method 1: Bitmask
vector<vector<int>> subsets_bitmask(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> result;
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<int> subset;
        for (int i = 0; i < n; i++)
            if (mask & (1 << i)) subset.push_back(nums[i]);
        result.push_back(subset);
    }
    return result;
}

// Method 2: Recursive backtracking
void backtrack(vector<int>& nums, int idx, vector<int>& current, vector<vector<int>>& result) {
    result.push_back(current);
    for (int i = idx; i < (int)nums.size(); i++) {
        current.push_back(nums[i]);
        backtrack(nums, i + 1, current, result);
        current.pop_back();
    }
}

void printSubsets(vector<vector<int>>& subsets) {
    for (auto& s : subsets) {
        cout << "  {";
        for (int i = 0; i < (int)s.size(); i++) {
            if (i) cout << ",";
            cout << s[i];
        }
        cout << "}" << endl;
    }
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   GENERATE ALL SUBSETS                          ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    vector<int> nums = {1, 2, 3};

    cout << "\n--- Method 1: Bitmask (2^3 = 8 subsets) ---" << endl;
    auto res1 = subsets_bitmask(nums);
    printSubsets(res1);

    cout << "\n--- Method 2: Backtracking ---" << endl;
    vector<vector<int>> res2;
    vector<int> current;
    backtrack(nums, 0, current, res2);
    printSubsets(res2);

    cout << "\n✅ Generate all subsets demonstrated!" << endl;
    return 0;
}

