/*
Author: Sarvan.DP.GrandMaster
Created : 2026-08-29 01:38:03
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>
using namespace std;

/*
 * Problem: Combinations (LeetCode 77)
 * Given two integers n and k, return all possible combinations of k numbers chosen from the range [1, n].
 * You may return the answer in any order.
 *
 * Example 1:
 * Input: n = 4, k = 2
 * Output: [[2,4],[3,4],[2,3],[1,2],[1,3],[1,4]]
 * Note: C(n, k) = n! / (k! * (n - k)!) -> C(4, 2) = 4! / (2! * (4 - 2)!) = 6
 * Explanation: There are 4 choose 2 = 6 total combinations.
 * Note that combinations are unordered, i.e., [1,2] and [2,1] are considered to be the same combination.
 *
 * Example 2:
 * Input: n = 1, k = 1
 * Output: [[1]]
 * Explanation: There is 1 choose 1 = 1 total combination.
 *
 * Constraints:
 * 1 <= n <= 20
 * 1 <= k <= n
 *
 * Topics: Backtracking, Recursion

 <========= COMBINATION BACKTRACKING — CORE LOGIC ==========>
1. STATE
   current → combination built so far.
   start   → smallest number allowed for the next selection.

2. BASE CASE
   If current.size() == k:
       → Combination is complete.
       → Store it.
       → Return.

3. NEED
   need = k - current.size()
   Meaning:
       → How many more numbers are required?

4. LIMIT — MAIN PRUNING
   limit = n - need + 1
   Meaning:
       → Largest number we can choose while still having enough numbers left to complete the combination.
   Therefore:
       → Never enter a branch that cannot possibly reach size k.

5. CHOICE
   Try every i from start to limit.

6. CHOOSE → EXPLORE → UNCHOOSE
   CHOOSE:
       → Add i to current.
   EXPLORE:
       → Recurse with i + 1.
   UNCHOOSE:
       → Remove i from current.

7. WHY i + 1?
   → Prevents reusing the same number.
   → Guarantees increasing elements.
   → Automatically prevents duplicate combinations.
   → No visited[] required.

8. LEXICOGRAPHICAL ORDER
   i = start → limit
   → Always iterate from SMALL → LARGE.
   → DFS completely explores the smaller prefix before moving
     to the next prefix.
   → Therefore combinations are generated directly in
     lexicographical order.
   → No sorting required.

9. CORE INVARIANT
   current is always a valid increasing combination
   AND
   start is the first possible number for the next position
   AND
   limit guarantees enough numbers remain.

10. COMPLEXITY
    Time: O(C(n,k) × k)
    Auxiliary Space: O(k)
    Output Space: O(C(n,k) × k)

Tips: MEMORY TRICK: START -> No duplicates, NEED -> How many more?, LIMIT -> Prune impossible choices,
		i + 1 -> Maintain increasing order, SMALL → LARGE -> Lexicographical order, CHOOSE → EXPLORE → UNCHOOSE -> Backtracking
*/

// Method 1: Without pre-allocation of answer vector (may cause reallocations)
static vector<vector<int>> combi(const int n, const int k){
	// Edge case safety
	if (k < 0 || k > n)
		return {};

	vector<vector<int>> ans;
	vector<int> current;
	current.reserve(k);

	auto dfs = [&](auto&& self, const int start_num) -> void{
		// Base Case: if current.size() == k that means done
		if (current.size() == k){
			ans.emplace_back(current);
			return;
		}

		const int needed = k - current.size();
		const int limit = n - needed + 1;

		for (int i = start_num; i <= limit; i++){
			current.emplace_back(i);
			self(self, i + 1);
			current.pop_back();
		}
	};

	dfs(dfs, 1);
	return ans;
}

// Method 2: With pre-allocation of answer vector (eliminates reallocations)
// This is the preferred method for large n and k
// Pre-allocate the answer vector to the exact size of nCk
static vector<vector<int>> combination(const int n, const int k){
	// Edge case safety
	if (k < 0 || k > n)
		return {};

	// 1. Calculate nCr mathematically to pre-allocate the exact size of 'ans'
	// This completely eliminates outer vector reallocations.
	long long combinations_count = 1;
	for (int i = 1; i <= k; i++){
		combinations_count = combinations_count * (n - i + 1) / i;
	}
	vector<vector<int>> ans;
	ans.reserve(combinations_count);

	vector<int> current;
	current.reserve(k);

	// 2. Pass 'needed' directly into the lambda state
	auto dfs = [&](auto&& self, const int start_num, const int needed) -> void{
		// Base Case: 0 numbers needed means we are done
		if (needed == 0){
			ans.emplace_back(current); // emplace_back is slightly faster
			return;
		}

		// Tree Pruning is intact, but no longer relies on .size() subtraction
		const int limit = n - needed + 1;

		for (int i = start_num; i <= limit; i++){
			current.emplace_back(i);

			// Pass (needed - 1) down to the next level
			self(self, i + 1, needed - 1);
			current.pop_back();
		}
	};

	// Start with 'k' needed
	dfs(dfs, 1, k);
	return ans;
}

void solve() {
    int n, k; cin >> n >> k;

	// Method 1: Without pre-allocation of answer vector (may cause reallocations)
	// vector<vector<int>> print = combi(n, k);

	// Method 2: With pre-allocation of answer vector (eliminates reallocations)
	vector<vector<int>> print1 = combination(n, k);
	cout << "[";
	for (int i = 0; i < print1.size(); i++){
		cout << "[";
		for (int j = 0; j < print1[i].size(); j++){
			cout << print1[i][j];
			if (j + 1 < print1[i].size())
				cout << ", ";
		}
		cout << "]";
		if (i + 1 < print1.size())
			cout << ", ";
	}
	cout << "]\n";
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << fixed << setprecision(10);
    
    // Multi-test case support (commented out for this demo)
    // int TC = 1;
    // cin >> TC;
    // while (TC--) solve();
    
    solve();
    return 0;
}

