/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 06.05 — AND MONOTONIC PROPERTY                           ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

KEY PROPERTY: AND is MONOTONICALLY NON-INCREASING as we extend the window.
    AND(a[L..R]) ≥ AND(a[L..R+1])  because AND only clears bits, never sets them.

IMPLICATION: At most O(log(MAX)) distinct AND values per starting point.
APPLICATION: Use binary search or two pointers for AND-based range queries.
*/
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int countDistinctSubarrayAND(vector<int>& arr) {
    unordered_set<int> allValues;
    unordered_set<int> current;

    for (int x : arr) {
        unordered_set<int> newSet;
        newSet.insert(x);
        for (int val : current) newSet.insert(val & x);
        current = newSet;
        for (int v : current) allValues.insert(v);
    }
    return allValues.size();
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   AND MONOTONIC PROPERTY                        ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    vector<int> arr = {7, 6, 5};
    cout << "\n--- AND Monotonicity Demo [7,6,5] ---" << endl;
    for (int L = 0; L < 3; L++) {
        int andVal = ~0;
        cout << "  L=" << L << ": ";
        for (int R = L; R < 3; R++) {
            andVal &= arr[R];
            cout << "AND(L.." << R << ")=" << andVal << " ";
        }
        cout << "(non-increasing ✓)" << endl;
    }

    cout << "\n--- Distinct Subarray AND Values ---" << endl;
    cout << "  [7,6,5]: " << countDistinctSubarrayAND(arr) << " distinct values" << endl;

    cout << "\n✅ AND monotonic property demonstrated!" << endl;
    return 0;
}

