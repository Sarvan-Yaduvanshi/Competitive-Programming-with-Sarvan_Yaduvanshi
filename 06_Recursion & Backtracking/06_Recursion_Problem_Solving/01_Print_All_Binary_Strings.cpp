/*
Author: Sarvan.DP.GrandMaster
Created : 2026-08-15 23:22:12
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


/* Problem: Generate all binary strings
 * Given an integer n, generate all binary strings of length n.
 * A binary string is a string that consists only of the characters '0' and '1'.
 * Note: Return the strings in ascending order.
 * Example:
 * input: n = 3
 * Output: ["000", "001", "010", "011", "100", "101", "110", "111"]
 * input: n = 2
 * Output: ["00", "01", "10", "11"]
 * Explanation: As each position can be either 0 or 1, the total possible combinations are 4.
 */

int n;
void generateBinaryStr(string str){
	// Base Case: if str.size() == n than simple return & print
	if (str.size() == n){
		cout << str;
		if (str != string(n, '1')){
			cout << ", ";
		}
		return;
	}

	// left part recursion
	generateBinaryStr(str + "0");
	// right part recursion
	generateBinaryStr(str + "1");
}
void solve(){
	cin >> n;
	cout << "[";
	generateBinaryStr("");
	cout << "]";
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}
