#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <iomanip>
#include <random>
#include <chrono>
#include <algorithm>
using namespace std;


// Template 1: Take or Not Take used dp 0/1 knapsack problem
static bool subsetDup(vector<int>& nums, int k){
	int n = nums.size();

	vector<int> suffix_sum(n + 1, 0);
	for (int i = n - 1; i >= 0; i--)
		suffix_sum[i] = suffix_sum[i + 1] + nums[i];

	auto dfs = [&](auto&& self, const int idx, int curr_sum) -> bool {
		if (curr_sum > k) return false;
		if (curr_sum + suffix_sum[idx] < k) return false;

		if (idx == n){
			if (k == curr_sum)
				return true;
			return false;
		}

		if (self(self, idx + 1, curr_sum + nums[idx]) == true)
			return true;
		if (self(self, idx + 1, curr_sum) == true)
			return true;
		return false;
	};

	return dfs(dfs, 0, 0);
}


static void solve(){
	int n, k; cin >> n >> k;
	vector<int> arr(n);
	for (auto &x : arr)
		cin >> x;

	// Function one call
	vector<vector<int>> print1 = subsetDup(arr, k);
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
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
}