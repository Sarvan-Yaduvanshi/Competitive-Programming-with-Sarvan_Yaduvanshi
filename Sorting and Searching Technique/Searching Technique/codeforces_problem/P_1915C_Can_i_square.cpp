//
// Created by DynamicSarvan on 9/9/25.
//

#include "P_1915C_Can_i_square.h"

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<long long>;

#define end '\n'

void solve() {
    int n; cin >> n;
    vi arr(n);
    ll total_squares = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        total_squares += arr[i];
    }

    ll side = static_cast<long long>(sqrt(total_squares));

    if (side * side == total_squares) cout << "YES" << endl;
    else cout << "NO" << endl;


}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) solve();

    return 0;
}