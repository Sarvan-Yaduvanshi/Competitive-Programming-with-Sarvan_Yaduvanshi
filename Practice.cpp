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

vector<vector<int>> subq(const vector<int>& nums){
	vector<vector<int>> ans;
	vector<int> curr;
	curr.reserve(nums.size());

	auto dfs = [&](auto&& self, const int idx) -> void{
		if (idx == nums.size()){
			ans.emplace_back(curr);
			return;
		}

		// not take
		self(self, idx + 1);

		// take
		curr.push_back(nums[idx]);
		self(self, idx + 1);
		curr.pop_back();
	};

	dfs(dfs, 0);
	return ans;
}

vector<vector<int>> subq2(vector<int>& nums){
	vector<vector<int>> ans;
	set<vector<int>> st;
	vector<int> curr;
	curr.reserve(nums.size());

	auto dfs = [&](auto&& self, const int idx) -> void{
		if (idx == nums.size()){
			if (!st.contains(curr)){
				ans.emplace_back(curr);
				st.insert(curr);
			}
			return;
		}

		curr.push_back(nums[idx]);
		self(self, idx + 1);
		curr.pop_back();

		int nxt_idx = idx + 1;
		while (nxt_idx < nums.size() && nums[nxt_idx] == nums[idx])
			nxt_idx++;

		self(self, nxt_idx);
	};

	dfs(dfs, 0);
	return ans;
}



static void solve(){
	int n; cin >> n;
	vector<int> arr(n);
	for (auto &x : arr)
		cin >> x;

	const auto subsequences = subq(arr);
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

	const auto subsequences2 = subq2(arr);
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
	struct Node{
		int data;
		Node* next;
	};

	Node* first = new Node(10, nullptr);
	Node* second = new Node(20, nullptr);
	Node* third = new Node(30, nullptr);
	Node* fourth = new Node(40, nullptr);

	first->next = second;
	second->next = third;
	third->next = fourth;

	Node* head = first;
	while (head != nullptr){
		cout << head->data << "->";
		head = head->next;
	}

	return 0;
}