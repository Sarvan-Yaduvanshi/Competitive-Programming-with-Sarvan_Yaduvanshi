/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 06.04 — OR MONOTONIC PROPERTY                            ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

KEY PROPERTY: For a subarray, as we extend it, OR can only INCREASE (or stay same).
    OR(a[L..R]) ≤ OR(a[L..R+1])  because OR only sets bits, never clears them.

This means: OR is MONOTONICALLY NON-DECREASING as we extend the window.

IMPLICATION: At most O(log(MAX)) distinct OR values per starting point.
    Each new element can set at most log(MAX) new bits.

TOTAL DISTINCT SUBARRAY OR VALUES: O(n × log(MAX))

APPLICATION: Count distinct subarray OR values.
    For each position, maintain set of current OR values.
*/
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
using namespace std;

// Count distinct subarray OR values
int countDistinctSubarrayOR(vector<int>& arr) {
    unordered_set<int> allValues;
    unordered_set<int> current; // OR values ending at current position

    for (int x : arr) {
        unordered_set<int> newSet;
        newSet.insert(x);
        for (int val : current) {
            newSet.insert(val | x);
        }
        current = newSet;
        for (int v : current) allValues.insert(v);
    }
    return allValues.size();
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   OR MONOTONIC PROPERTY                         ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // Demonstrate monotonicity
    vector<int> arr = {1, 2, 4};
    cout << "\n--- OR Monotonicity Demo [1,2,4] ---" << endl;
    for (int L = 0; L < 3; L++) {
        int orVal = 0;
        cout << "  L=" << L << ": ";
        for (int R = L; R < 3; R++) {
            orVal |= arr[R];
            cout << "OR(L.." << R << ")=" << orVal << " ";
        }
        cout << "(non-decreasing ✓)" << endl;
    }

    cout << "\n--- Distinct Subarray OR Values ---" << endl;
    vector<int> arr2 = {1, 1, 2};
    cout << "  [1,1,2]: " << countDistinctSubarrayOR(arr2) << " distinct values" << endl;

    vector<int> arr3 = {1, 2, 4};
    cout << "  [1,2,4]: " << countDistinctSubarrayOR(arr3) << " distinct values" << endl;

    cout << "\n✅ OR monotonic property demonstrated!" << endl;
    return 0;
}

