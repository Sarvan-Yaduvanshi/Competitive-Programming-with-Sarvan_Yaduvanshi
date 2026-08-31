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

vector<vector<int>> combination(int n, int k){
	if (k < 0 || k > n)
		return {};

	long long combination_cnt = 1;
	for (int i = 1; i <= k; i++){
		combination_cnt = combination_cnt * (n - i + 1) / i;
	}
	vector<vector<int>> ans;
	ans.reserve(combination_cnt);

	vector<int> current;
	current.reserve(k);

	auto dfs = [&](auto&& self, int start_num, int needed) -> void{
		// Base Case: if needed == 0 that means done
		if (needed == 0){
			ans.emplace_back(current);
			return;
		}

		int limit = n - needed + 1;
		for (int i = start_num; i <= limit; i++){
			current.emplace_back(i);
			self(self, i + 1, needed - 1);
			current.pop_back();
		}
	};

	dfs(dfs, 1, k);
	return ans;
}


static void solve(){
	int n, k; cin >> n >> k;
	// vector<int> arr(n);
	// for (auto &x : arr)
	// 	cin >> x;

	// Function one call
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
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
}