/*
Author: Sarvan.DP.GrandMaster
Created : 2026-08-24 11:39:36
*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/*
	Problem: W - Reach Value (Codeforces)
	Given a number 𝑁. Initially you have a value equal 1 and you can perform one of the following operation any number of times:
			1. Multiply the current value by 10.
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

	bool ans = divisible(divisible, n);
	cout << (ans ? "YES" : "NO") << "\n";
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

