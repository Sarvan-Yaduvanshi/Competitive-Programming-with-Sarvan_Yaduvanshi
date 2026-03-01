/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Stack-Based Greedy — Monotone Stack Patterns
 *  Level   : Advanced
 * ============================================================================
 *
 *  PATTERN: Maintain a monotone (increasing/decreasing) stack to greedily
 *  build an optimal sequence.
 *
 *  KEY IDEA: Before pushing an element, remove worse elements from the stack
 *  if we can still complete the solution without them.
 *
 *  APPLICATIONS:
 *  - Remove K Digits (LC 402) — smallest number
 *  - Remove Duplicate Letters (LC 316) — smallest subsequence
 *  - Next Greater Element patterns
 *  - Stock span / Temperature problems
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

// ============================================================================
// LC 402: Remove K Digits (covered in Module 06, shown here for reference)
// ============================================================================

// ============================================================================
// Next Greater Element (LC 496/503) — Monotone Decreasing Stack
// For each element, find the next element that is larger
// ============================================================================
vector<int> nextGreaterElement(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> st; // Indices, maintaining decreasing order of values

    for (int i = 0; i < n; i++) {
        while (!st.empty() && nums[st.top()] < nums[i]) {
            result[st.top()] = nums[i];
            st.pop();
        }
        st.push(i);
    }
    return result;
}

// ============================================================================
// LC 84: Largest Rectangle in Histogram — Monotone Increasing Stack
// ============================================================================
int largestRectangle(vector<int>& heights) {
    stack<int> st;
    int maxArea = 0;
    int n = heights.size();

    for (int i = 0; i <= n; i++) {
        int h = (i == n) ? 0 : heights[i];
        while (!st.empty() && heights[st.top()] > h) {
            int height = heights[st.top()]; st.pop();
            int width = st.empty() ? i : (i - st.top() - 1);
            maxArea = max(maxArea, height * width);
        }
        st.push(i);
    }
    return maxArea;
}

// ============================================================================
// Daily Temperatures (LC 739) — Stack-based greedy
// ============================================================================
vector<int> dailyTemperatures(vector<int>& temps) {
    int n = temps.size();
    vector<int> result(n, 0);
    stack<int> st;

    for (int i = 0; i < n; i++) {
        while (!st.empty() && temps[st.top()] < temps[i]) {
            result[st.top()] = i - st.top();
            st.pop();
        }
        st.push(i);
    }
    return result;
}

int main() {
    // Next Greater
    vector<int> nums = {4, 5, 2, 25};
    auto nge = nextGreaterElement(nums);
    cout << "Next Greater: ";
    for (int x : nge) cout << x << " ";
    cout << endl; // 5 25 25 -1

    // Largest Rectangle
    vector<int> heights = {2, 1, 5, 6, 2, 3};
    cout << "Largest Rectangle: " << largestRectangle(heights) << endl; // 10

    // Daily Temperatures
    vector<int> temps = {73, 74, 75, 71, 69, 72, 76, 73};
    auto dt = dailyTemperatures(temps);
    cout << "Daily Temps: ";
    for (int x : dt) cout << x << " ";
    cout << endl; // 1 1 4 2 1 1 0 0

    return 0;
}

