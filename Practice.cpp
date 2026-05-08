#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <random>
#include <chrono>

using namespace std;

void solve(){
	string str;
	cin >> str;

	stack<char> st;

	auto isValid = [&]() -> bool {
		for (char ch : str){
			if (ch == '(' || ch == '[' || ch == '{')
				st.push(ch);
			else{
				if (st.empty()) return false;
				char top = st.top();
				if ((ch == ')' && top == '(' || ch == '}' && top == '{' || ch == ']' && top == '['))
					st.pop();
				else return false;
			}
		}

		return st.empty();
	};

	cout << (isValid() ? "true" : "false") << "\n";

}

int main(){
	solve();

	return 0;
}
