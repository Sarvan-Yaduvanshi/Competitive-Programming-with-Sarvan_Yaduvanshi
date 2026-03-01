/*
╔══════════════════════════════════════════════════════════════════════════════╗
║      05-08 — MORE MONOTONIC STACK: Remove K Digits, Daily Temps,             ║
║              Asteroid Collision, Sum of Subarray Maximums                    ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

This file contains 4 important monotonic stack problems combined.
*/

#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// 1. REMOVE K DIGITS (LC 402)
// ═══════════════════════════════════════════════════════════════
/*
  Remove k digits from num to get smallest possible number.

  Greedy + Monotonic Stack: maintain increasing stack.
  When current digit < stack.top(), pop (remove a digit, k--).

  DRY RUN: num="1432219", k=3
  stack=[], k=3
  '1': push → [1]
  '4': 4>1, push → [1,4]
  '3': 3<4, pop 4(k=2) → [1], 3>1 push → [1,3]
  '2': 2<3, pop 3(k=1) → [1], 2>1 push → [1,2]
  '2': 2>=2, push → [1,2,2]
  '1': 1<2, pop 2(k=0) → [1,2], 1<2 but k=0 → push → [1,2,1]
  '9': push → [1,2,1,9]

  Result: "1219" ✅
*/

string removeKdigits(string num, int k) {
    string st;  // Use string as stack
    for (char c : num) {
        while (!st.empty() && k > 0 && st.back() > c) {
            st.pop_back();
            k--;
        }
        st.push_back(c);
    }
    while (k > 0) { st.pop_back(); k--; }

    // Remove leading zeros
    int start = 0;
    while (start < (int)st.size() && st[start] == '0') start++;
    string result = st.substr(start);
    return result.empty() ? "0" : result;
}

// ═══════════════════════════════════════════════════════════════
// 2. DAILY TEMPERATURES (LC 739)
// ═══════════════════════════════════════════════════════════════
/*
  Find how many days until a warmer temperature.
  This is just NGE but return (index difference) instead of value.

  DRY RUN: [73,74,75,71,69,72,76,73]
  Output:  [1, 1, 4, 2, 1, 1, 0, 0]
*/

vector<int> dailyTemperatures(vector<int>& temps) {
    int n = temps.size();
    vector<int> result(n, 0);
    stack<int> st;  // Indices, decreasing temps

    for (int i = 0; i < n; i++) {
        while (!st.empty() && temps[st.top()] < temps[i]) {
            result[st.top()] = i - st.top();
            st.pop();
        }
        st.push(i);
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// 3. ASTEROID COLLISION (LC 735)
// ═══════════════════════════════════════════════════════════════
/*
  Positive = moving right, Negative = moving left.
  When they meet, smaller one explodes. Equal = both explode.

  DRY RUN: [5, 10, -5]
  stack = [5, 10], then -5: |-5| < 10, -5 destroyed → [5, 10]

  DRY RUN: [8, -8]
  stack = [8], then -8: |8| == |-8|, both destroyed → []

  DRY RUN: [10, 2, -5]
  stack = [10, 2], then -5: |-5| > 2, destroy 2.
  |-5| < 10, destroy -5. → [10]
*/

vector<int> asteroidCollision(vector<int>& asteroids) {
    stack<int> st;
    for (int a : asteroids) {
        bool destroyed = false;
        while (!st.empty() && st.top() > 0 && a < 0) {
            if (st.top() < -a) {
                st.pop(); // Right asteroid destroyed
                continue;
            } else if (st.top() == -a) {
                st.pop(); // Both destroyed
            }
            destroyed = true;
            break;
        }
        if (!destroyed) st.push(a);
    }

    vector<int> result(st.size());
    for (int i = st.size() - 1; i >= 0; i--) {
        result[i] = st.top();
        st.pop();
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  MONOTONIC STACK PATTERNS: 4 CLASSIC PROBLEMS            ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Remove K Digits
    cout << "═══ REMOVE K DIGITS (LC 402) ═══\n";
    cout << "  \"1432219\", k=3 → " << removeKdigits("1432219", 3) << "\n";
    cout << "  \"10200\", k=1   → " << removeKdigits("10200", 1) << "\n";
    cout << "  \"10\", k=2      → " << removeKdigits("10", 2) << "\n\n";

    // Daily Temperatures
    cout << "═══ DAILY TEMPERATURES (LC 739) ═══\n";
    vector<int> temps = {73,74,75,71,69,72,76,73};
    auto dt = dailyTemperatures(temps);
    cout << "  Temps:  "; for (int x : temps) cout << x << " "; cout << "\n";
    cout << "  Answer: "; for (int x : dt) cout << x << " "; cout << "\n\n";

    // Asteroid Collision
    cout << "═══ ASTEROID COLLISION (LC 735) ═══\n";
    vector<int> a1 = {5, 10, -5};
    auto r1 = asteroidCollision(a1);
    cout << "  [5,10,-5] → ["; for (int i=0;i<(int)r1.size();i++) cout<<r1[i]<<(i+1<(int)r1.size()?",":""); cout<<"]\n";

    vector<int> a2 = {8, -8};
    auto r2 = asteroidCollision(a2);
    cout << "  [8,-8] → ["; for (int i=0;i<(int)r2.size();i++) cout<<r2[i]<<(i+1<(int)r2.size()?",":""); cout<<"]\n";

    vector<int> a3 = {10, 2, -5};
    auto r3 = asteroidCollision(a3);
    cout << "  [10,2,-5] → ["; for (int i=0;i<(int)r3.size();i++) cout<<r3[i]<<(i+1<(int)r3.size()?",":""); cout<<"]\n";

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE: LC 402, 739, 735, 456 (132 Pattern)\n";
    cout << "═══════════════════════════════════════════════════════════\n";
    return 0;
}

