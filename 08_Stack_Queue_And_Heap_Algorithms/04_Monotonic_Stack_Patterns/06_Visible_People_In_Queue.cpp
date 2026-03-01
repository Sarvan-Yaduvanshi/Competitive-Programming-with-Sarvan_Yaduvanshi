/*
╔══════════════════════════════════════════════════════════════════════════════╗
║       06 — VISIBLE PEOPLE IN A QUEUE (LC 1944)                               ║
║           From Zero to Grandmaster — Monotonic Stack Patterns               ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM:
────────
  n people standing in a queue. heights[i] is the height of the ith person.
  Person i can see person j (j > i) if:
    - All people between i and j are shorter than BOTH heights[i] and heights[j]
  Return array where answer[i] = # of people person i can see.

APPROACH: Monotonic Stack (Decreasing) — Right to Left
──────────────────────────────────────────────────────
  For each person i, process right to left.
  Stack maintains people visible from the right (decreasing heights).

  For person i:
    - Pop all shorter people (i can see them)
    - If stack not empty, i can also see the next taller person
    - Push i onto stack

DRY RUN: heights = [10, 6, 8, 5, 11, 9]

  i=5 (h=9):  stack=[] → count=0, push 9         stack=[9]
  i=4 (h=11): pop 9(≤11), count=1, stack empty    → count=1
              push 11                              stack=[11]
  i=3 (h=5):  stack=[11], 11>5 → can see 11       → count=1
              push 5                               stack=[11,5]
  i=2 (h=8):  pop 5(≤8), count=1. stack=[11], 11>8 → count+1=2
              push 8                               stack=[11,8]
  i=1 (h=6):  stack=[11,8], 8>6 → can see 8       → count=1
              push 6                               stack=[11,8,6]
  i=0 (h=10): pop 6(≤10), count=1. pop 8(≤10), count=2
              stack=[11], 11>10 → count+1=3
              push 10                              stack=[11,10]

  Result: [3, 1, 2, 1, 1, 0] ✅

TIME: O(n)  SPACE: O(n)
*/

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

vector<int> canSeePersonsCount(vector<int>& heights) {
    int n = heights.size();
    vector<int> answer(n, 0);
    stack<int> st;  // Decreasing stack of heights

    for (int i = n - 1; i >= 0; i--) {
        int count = 0;
        // Pop all shorter people (i can see each of them)
        while (!st.empty() && st.top() <= heights[i]) {
            st.pop();
            count++;
        }
        // If stack not empty, i can also see the next taller person
        if (!st.empty()) count++;
        answer[i] = count;
        st.push(heights[i]);
    }
    return answer;
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  VISIBLE PEOPLE IN A QUEUE (LC 1944)                     ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    vector<int> h1 = {10, 6, 8, 5, 11, 9};
    auto r1 = canSeePersonsCount(h1);
    cout << "Heights: [10,6,8,5,11,9]\n";
    cout << "Visible: [";
    for (int i = 0; i < (int)r1.size(); i++) {
        cout << r1[i]; if (i+1<(int)r1.size()) cout << ",";
    }
    cout << "]\n\n";

    vector<int> h2 = {5, 1, 2, 3, 10};
    auto r2 = canSeePersonsCount(h2);
    cout << "Heights: [5,1,2,3,10]\n";
    cout << "Visible: [";
    for (int i = 0; i < (int)r2.size(); i++) {
        cout << r2[i]; if (i+1<(int)r2.size()) cout << ",";
    }
    cout << "]\n";

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE: LC 1944 — Number of Visible People in a Queue\n";
    cout << "═══════════════════════════════════════════════════════════\n";
    return 0;
}

