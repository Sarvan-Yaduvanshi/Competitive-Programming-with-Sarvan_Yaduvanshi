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
using i64 = long long;
constexpr int MOD = 1e9 + 7;

string removeStr(const string& str, const int idx, char ch){
	// Base Case
	if (idx == str.size()){
		return "";
	}

	string rest = removeStr(str, idx + 1, ch);
	if (str[idx] == ch) return rest;
	return string(1, str[idx]) + rest;
}

// 4. Replace character (pi → 3.14)
string replace(string str, const int idx){
	if (idx == str.size()) return "";
	if (idx + 1 < str.size() && str[idx] == 'p' && str[idx + 1] == 'i')
		return "3.14" + replace(str, idx + 2);

	return string(1, str[idx]) + replace(str, idx + 1);
}
// Move all 'x' to end
string move(string str, const int idx){
	if (idx == str.size()) return "";
	string rest = move(str, idx + 1);
	if (str[idx] == 'x') return rest + 'x';
	return string(1, str[idx]) + rest;
}

int powerFun(int base, int exp){
	// Base Case
	if (exp == 0) return 1;
	return base * powerFun(base, exp - 1);
}
void solve(){
	int base, exp;
	cin >> base >> exp;

	cout << "power(" << base << "^" << exp << ")" << " = " << powerFun(base, exp) << endl;
}
int main(){
	solve();
	return 0;
}