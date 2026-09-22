/*
Author: Sarvan.DP.GrandMaster
Created : 2026-08-24 11:39:36
*/

#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>
using namespace std;

/*
	Problem: W - Reach Value (Codeforces)
	Given a number 𝑁. Initially you have a value equal 1 and you can perform one of the following operation any number of times:
			1.y the current value by 10. Multipl
			2. Multiply the current value by 20.
			Determine if your value can reach 𝑁 or not.
			Note: Solve the problem using recursion and backtracking.
    Example 1:
    Input: 100
    Output: YES
    Explanation: We can reach 100 by multiplying 1 by 10 twice (1 * 10 * 10 = 100).
    Example 2:
    Input: 200
    Output: YES
    Explanation: We can reach 200 by multiplying 1 by 20 once (1 * 20 = 20) and then multiplying by 10 once (20 * 10 = 200).
    Example 3:
    Input: 300
    Output: NO
    Explanation: There is no combination of operations that can reach 300 from 1.
*/

using i64  = long long;

// Approach 1: Recursive Backtracking
// Time Complexity: Best Case = O(1) || Worst Case = O(2^log10(N))
// Space Complexity: O(log10(N))
static void solve() {
    i64 n; cin >> n;

	auto divisible = [&](auto&& self, i64 num) -> bool{
		// Base Case: if any number reach 1 than return true
		if (num == 1) return true;

		// Can I repeatedly divide num by either 10 or 20, whenever possible, and eventually reach exactly 1?
		if (num % 10 == 0 && self(self, num / 10))
			return true;
		if (num % 20 == 0 && self(self, num / 20))
			return true;

		// Condition 3: not number divisible by 10 or 20 to reached 1 so return false
	    return false;
	};

	const bool ans = divisible(divisible, n);
	cout << (ans ? "YES" : "NO") << "\n";
}

// Approach 2: Iterative (used stack data structure to simulate recursion)
// Time Complexity: O(2^log10(N)) in the generic worst-case branching analysis
// Space Complexity: O(2^log10(N)) worst-case for the explicit DFS stack
static void solve_iterative(){
	i64 n; cin >> n;

	stack<i64> st;
	st.push(n);

	while (!st.empty()){
		const i64 x = st.top();
		st.pop();

		if (x == 1){
			cout << "YES\n";
			return;
		}

		if (x % 10 == 0)
			st.push(x / 10);

		if (x % 20 == 0)
			st.push(x / 20);
	}

	cout << "NO\n";
}



int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	// Multi-test case support (commented out for this demo)
	int TC = 1;
	cin >> TC;
	while (TC--) solve();
	return 0;
}

