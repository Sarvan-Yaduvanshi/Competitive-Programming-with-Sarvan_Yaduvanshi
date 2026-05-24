#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <random>
#include <chrono>

using namespace std;


void solve(){
	int n; cin >> n;

	vector<vector<int>> adj(n);
	for (int i = 0; i < n - 1; i++){
		int u, v;
		cin >> u >> v;
		u--; v--;

		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	int root = 0;
	vector<int> ans;

	auto dfs = [&](auto&& self, int currNode, int parent) -> void{
		ans.push_back(currNode);

		for (int nbr : adj[currNode]){
			if (nbr != parent)
				self(self, nbr , currNode);
		}
	};

	dfs(dfs, 0 , -1);

	for (int x : ans)
		cout << x + 1 << " ";
}

int main(){
	solve();

	return 0;
}
