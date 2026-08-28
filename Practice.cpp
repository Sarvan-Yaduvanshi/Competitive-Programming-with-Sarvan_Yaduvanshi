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
static vector<vector<int>> subsetDup(vector<int>& nums){
	vector<vector<int>> ans;
	vector<int> curr;

	auto dfs = [&](auto&& self, int idx) -> void{
		// Base case
		if (idx == nums.size()){
			ans.push_back(curr);
			return;
		}

		// Take
		curr.push_back(nums[idx]);
		self(self, idx + 1);
		curr.pop_back();

		// Not take and skip all duplicates
		int nxt_idx = idx + 1;
		while (nxt_idx < nums.size() && nums[nxt_idx] == nums[idx])
			nxt_idx++;
		self(self, nxt_idx);
	};

	dfs(dfs, 0);
	return ans;
}

static vector<vector<int>> subsetDup2(vector<int>& nums){
	vector<vector<int>> ans;
	vector<int> curr;

	auto dfs = [&](auto&& self, int idx) -> void{
		ans.push_back(curr);

		for (int i = idx; i < nums.size(); i++){
			if (i > idx && nums[i] == nums[i - 1])
				continue;

			curr.push_back(nums[i]);
			self(self, i + 1); // not idx + 1
			curr.pop_back();
		}
	};

	dfs(dfs, 0);
	return ans;
}


static void solve(){
	int n; cin >> n;
	vector<int> arr(n);
	for (auto &x : arr)
		cin >> x;

	// Function one call
	vector<vector<int>> print1 = subsetDup2(arr);
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