/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Circular Fixed Window Problems
 *  Level   : Medium → Hard
 * ============================================================================
 *
 *  ▶ CIRCULAR FIXED WINDOW TECHNIQUES:
 *  ────────────────────────────────────
 *  1. Double Array Trick: Concatenate arr with itself → arr + arr
 *     Now any circular window of size K is a normal window in arr+arr.
 *  2. Modular Indexing: Access arr[i % N] instead of doubling.
 *  3. Complement Trick: Circular max window = totalSum - min normal window.
 *
 *  PROBLEMS:
 *  LC 2134 — Min Swaps to Group All 1s Together II (circular fixed window)
 *            https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together-ii/
 *  LC 918  — Maximum Sum Circular Subarray (covered in Module 06)
 *            https://leetcode.com/problems/maximum-sum-circular-subarray/
 *  LC 1652 — Defuse the Bomb (circular window sum)
 *            https://leetcode.com/problems/defuse-the-bomb/
 *  CF 1343C — Alternating Subsequence → related circular pattern (1200)
 *            https://codeforces.com/problemset/problem/1343/C
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// ============================================================================
// Circular Fixed Window — Modular Indexing Template
// ============================================================================
/*
 * Window of size K on circular array of size N.
 * There are exactly N windows (one starting at each index).
 * Access: arr[(start + offset) % N]
 */
vector<int> circularWindowSums(vector<int>& arr, int k) {
    int n = arr.size();
    vector<int> result(n);

    // Initialize: sum of first window
    int windowSum = 0;
    for (int i = 0; i < k; i++)
        windowSum += arr[i];
    result[0] = windowSum;

    // Slide circularly
    for (int i = 1; i < n; i++) {
        windowSum += arr[(i + k - 1) % n]; // Add new right
        windowSum -= arr[(i - 1) % n];      // Remove old left (= arr[i-1])
        result[i] = windowSum;
    }
    return result;
}

// ============================================================================
// Circular Max Window Sum of Size K
// ============================================================================
int circularMaxWindowSum(vector<int>& arr, int k) {
    auto sums = circularWindowSums(arr, k);
    return *max_element(sums.begin(), sums.end());
}

// ============================================================================
// LC 2134: Min Swaps to Group All 1s Together II (Circular)
// ============================================================================
/*
 * Binary circular array. Group all 1s together. Min swaps.
 *
 * Window size = total 1s count.
 * Find circular window of that size with MOST 1s already.
 * Answer = totalOnes - maxOnesInWindow.
 *
 * Use modular indexing for circular windows.
 */
int minSwaps(vector<int>& nums) {
    int n = nums.size();
    int totalOnes = 0;
    for (int x : nums) totalOnes += x;
    if (totalOnes <= 1) return 0;

    int k = totalOnes;
    int onesInWin = 0;
    for (int i = 0; i < k; i++) onesInWin += nums[i];
    int maxOnes = onesInWin;

    for (int i = 1; i < n; i++) {
        onesInWin += nums[(i + k - 1) % n];
        onesInWin -= nums[i - 1];
        maxOnes = max(maxOnes, onesInWin);
    }
    return k - maxOnes;
}

// ============================================================================
// Double Array Trick — Alternative to Modular Indexing
// ============================================================================
/*
 * Concatenate array with itself: doubled = arr + arr (size 2N).
 * Any circular window of size K starting at index i is:
 *   doubled[i .. i+K-1] (normal subarray).
 *
 * Apply standard fixed window on doubled, but only consider
 * windows starting at i = 0..N-1.
 */
int circularMaxWindowSum_double(vector<int>& arr, int k) {
    int n = arr.size();
    vector<int> doubled(2 * n);
    for (int i = 0; i < 2 * n; i++) doubled[i] = arr[i % n];

    int windowSum = 0, maxSum = INT_MIN;
    for (int i = 0; i < 2 * n; i++) {
        windowSum += doubled[i];
        if (i >= k) windowSum -= doubled[i - k];
        if (i >= k - 1 && i - k + 1 < n) // Only valid starting positions
            maxSum = max(maxSum, windowSum);
    }
    return maxSum;
}

// ============================================================================
// LC 1652: Defuse the Bomb — Circular Window Sum (forward/backward)
// ============================================================================
/*
 * code[i] replaced by sum of next K elements (circular) if K > 0,
 * or sum of previous |K| elements if K < 0, or 0 if K == 0.
 */
vector<int> decrypt(vector<int>& code, int k) {
    int n = code.size();
    vector<int> result(n, 0);
    if (k == 0) return result;

    for (int i = 0; i < n; i++) {
        int sum = 0;
        if (k > 0) {
            for (int j = 1; j <= k; j++)
                sum += code[(i + j) % n];
        } else {
            for (int j = 1; j <= -k; j++)
                sum += code[(i - j + n) % n];
        }
        result[i] = sum;
    }
    return result;
}

// Optimized with prefix sum
vector<int> decrypt_fast(vector<int>& code, int k) {
    int n = code.size();
    vector<int> result(n, 0);
    if (k == 0) return result;

    // Build circular prefix sum (double the array)
    vector<int> prefix(2 * n + 1, 0);
    for (int i = 0; i < 2 * n; i++)
        prefix[i + 1] = prefix[i] + code[i % n];

    for (int i = 0; i < n; i++) {
        if (k > 0) {
            result[i] = prefix[i + k + 1] - prefix[i + 1];
        } else {
            // Sum of |k| elements before i (circular)
            int start = ((i + k) % n + n) % n;
            // Use double array: sum from start to start+|k|-1
            result[i] = prefix[start + (-k)] - prefix[start];
            // Handle wrap: simpler with double array
        }
    }
    return result;
}

// ============================================================================
// Circular String Matching — Fixed Window on Circular String
// ============================================================================
/*
 * Does pattern appear anywhere in the circular string?
 * Double the string: s + s. Then search for pattern normally.
 */
bool circularContains(string s, string pattern) {
    string doubled = s + s;
    return doubled.find(pattern) != string::npos;
}

int main() {
    // Circular window sums
    vector<int> arr = {1, 2, 3, 4, 5};
    auto cs = circularWindowSums(arr, 3);
    cout << "Circular window sums (k=3): ";
    for (int x : cs) cout << x << " ";
    cout << "\n"; // 6 9 12 10 8

    // Min swaps to group 1s
    vector<int> nums = {0, 1, 0, 1, 1, 0, 0};
    cout << "Min swaps: " << minSwaps(nums) << "\n"; // 1

    // Defuse the bomb
    vector<int> code = {5, 7, 1, 4};
    auto dec = decrypt(code, 3);
    cout << "Defused: ";
    for (int x : dec) cout << x << " ";
    cout << "\n"; // 12 10 16 13

    // Circular string matching
    cout << "Circular contains 'cda' in 'abcd': "
         << circularContains("abcd", "cda") << "\n"; // 1

    return 0;
}

