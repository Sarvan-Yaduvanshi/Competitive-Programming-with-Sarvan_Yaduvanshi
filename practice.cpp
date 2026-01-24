//
// Created by Sarvan Yaduvanshi on 23/01/26.
//

// #include <iostream>
// #include <vector>
//
// using namespace std;
//
// int main(){
// 	int n; cin >> n;
// 	vector<int> a(n);
// 	for (auto &x : a) cin >> x;
//
// 	// Brute Force Prefix sum
// 	// vector<int> pref(n);
// 	// for (int i = 0; i < n; i++){
// 	// 	pref[i] = 0;
// 	// 	for (int j = 0; j <= i; j++){
// 	// 		pref[i] += a[j];
// 	// 	}
// 	// }
// 	//
// 	// for (auto p : pref) cout << p << " ";
// 	// cout << "\n";
// 	vector<int> pref(n + 1, 0);
// 	for (int i = 0; i < n; i++){
// 		pref[i + 1] = pref[i] + a[i];
// 	}
//
// 	int q; cin >> q;
// 	while (q--){
// 		int l, r;
// 		cin >> l >> r;
//
// 		int sum = pref[r + 1] - pref[l]; // 0 based index
// 		int sum1 = pref[r] - pref[l - 1]; // 1 based index
// 		cout << "sum of " << l << " to " << r << " : " << sum << "\n";
// 		cout << "sum of " << l << " to " << r << " : " << sum1 << "\n";
// 	}
// }