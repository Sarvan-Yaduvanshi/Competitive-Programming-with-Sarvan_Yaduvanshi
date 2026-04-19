#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

int main(){
	string str;
	getline(cin, str);

	bool newWord = true;
	for (char &ch : str){
		if (ch == ' '){
			newWord = true;
		} else{
			if (newWord && ch >= 'a' && ch <= 'z'){
				ch -= 32;
			}
			newWord = false;
		}
	}

	cout << str << "\n";
}

