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

static vector<string> binStr(const int n, const int k){
	vector<string> ans;
	string curr_str;
	curr_str.reserve(n);

	auto dfs = [&](auto&& self, const int idx, const int ones_cnt) -> void{
		if (ones_cnt > k)
			return;

		int space_left = n - idx;
		int ones_needed = k - ones_cnt;
		if (ones_needed > space_left)
			return;

		if (idx == n){
			ans.emplace_back(curr_str);
			return;
		}

		curr_str.push_back('0');
		self(self, idx + 1, ones_cnt);
		curr_str.pop_back();

		curr_str.push_back('1');
		self(self, idx + 1, ones_cnt + 1);
		curr_str.pop_back();
	};

	dfs(dfs, 0, 0);
	return ans;
}

static void solve(){
	int n, k; cin >> n >> k;

	const vector<string> ans = binStr(n, k);
	cout << "[";
	for (int i = 0; i < ans.size(); i++){
		cout << ans[i] << (i == ans.size() - 1 ? "" : ", ");
	}
	cout << "]";
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
}