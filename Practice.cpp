#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

 void Decreasing(int num){
	 // Base Case
 	if (num == 1){
 		cout << num << "\n";
 		return;
 	}

 	// Call Nxt Function
 	cout << num << " ";
 	Decreasing(num - 1);
 }

void inCreasing(int num){
	 // Base Case
 	if (num == 1){
 		cout << num << " ";
 		return;
 	}

 	// call first than print
 	inCreasing(num - 1);
 	cout << num << " ";
 }

int main(){
	int n; cin >> n;

 	Decreasing(n);
 	inCreasing(n);
}

