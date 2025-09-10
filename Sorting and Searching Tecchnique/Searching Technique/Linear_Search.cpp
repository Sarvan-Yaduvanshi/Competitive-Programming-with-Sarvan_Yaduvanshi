#include <bits/stdc++.h>
using namespace std;

// ---- Your linear search implementations ----

// Method 1 : Basic Implementation
int linearSearch(const vector<int>& arr, int t) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == t) return i;
    }
    return -1;
}

// Method 2 : Sentinel Linear Search
int sentinelLinearSearch(vector<int> arr, int t) { // pass by value
    int n = arr.size();
    if (n == 0) return -1;

    int last = arr[n - 1];
    arr[n - 1] = t;

    int i = 0;
    while (arr[i] != t) i++;

    arr[n - 1] = last;

    if (i < n - 1 || arr[n - 1] == t) return i;
    return -1;
}

// Method 3 : Using C++ STL
int usingSTL(const vector<int>& arr, int t) {
    auto it = find(arr.begin(), arr.end(), t);
    return (it != arr.end() ? distance(arr.begin(), it) : -1);
}

// Method 4 : Searching with a Condition (first even number)
int searchConditionLS(const vector<int>& arr, int t) {
    auto it = find_if(arr.begin(), arr.end(), [](int num) {
        return num % 2 == 0;
    });
    return (it != arr.end() ? distance(arr.begin(), it) : -1);
}

// ---- Stress Test ----
int main() {
    srand(time(0));
    for (int test = 1; test <= 100000; test++) {
        int n = rand() % 20; // small arrays for debugging
        vector<int> arr(n);
        for (int i = 0; i < n; i++) arr[i] = rand() % 10; // values 0..9

        int t = rand() % 12; // target can be 0..11

        int m1 = linearSearch(arr, t);
        int m2 = sentinelLinearSearch(arr, t);
        int m3 = usingSTL(arr, t);

        // Only methods 1-3 should agree (method 4 is special condition)
        if (!(m1 == m2 && m2 == m3)) {
            cout << "❌ Mismatch found on test " << test << "\n";
            cout << "Array: ";
            for (int x : arr) cout << x << " ";
            cout << "\nTarget: " << t << "\n";
            cout << "Method1=" << m1 << " Method2=" << m2 << " Method3=" << m3 << "\n";
            return 0;
        }
    }
    cout << "✅ All tests passed!\n";
}
