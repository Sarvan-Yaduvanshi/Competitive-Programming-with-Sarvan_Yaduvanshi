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



static void solve(){
	int n; cin >> n;

	vector<int> a(n);
	for (auto &x : a)
		cin >> x;

	const auto subsequences = subq(a);
	cout << "Total Subsequences: " << subsequences.size() << "\n";
	cout << "[";
	for (int i = 0; i < subsequences.size(); i++){
		cout << "[";
		for (int j = 0; j < subsequences[i].size(); j++){
			cout << subsequences[i][j];
			if (j + 1 < subsequences[i].size())
				cout << ", ";
		}
		cout << "]";
		if (i + 1 < subsequences.size())
			cout << ", ";
	}
	cout << "]\n";

	const auto subsequences2 = subq2(a);
	cout << "[";
	for (int i = 0; i < subsequences2.size(); i++){
		cout << "[";
		for (int j = 0; j < subsequences2[i].size(); j++){
			cout << subsequences2[i][j];
			if (j + 1 < subsequences2[i].size())
				cout << ", ";
		}
		cout << "]";
		if (i + 1 < subsequences2.size())
			cout << ", ";
	}
	cout << "]\n";

}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
}