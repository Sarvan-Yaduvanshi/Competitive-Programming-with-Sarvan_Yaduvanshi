/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Two Pointer + Greedy Technique
 *  Level   : Intermediate
 * ============================================================================
 *
 *  ▶ WHEN IS TWO-POINTER GREEDY?
 *  ─────────────────────────────
 *  Two-pointer becomes a greedy technique when:
 *  1. You sort the input first
 *  2. Use two pointers (left/right or both from left) to make greedy matches
 *  3. Each pointer decision is locally optimal and never reconsidered
 *
 *  ▶ COMMON PATTERNS:
 *  ──────────────────
 *  PATTERN 1: PAIRING (Smallest with Largest)
 *    Sort, use left + right pointers to pair greedily.
 *    Examples: Boats to Save People, Assign Cookies
 *
 *  PATTERN 2: MATCHING (Greedy assignment)
 *    Sort both arrays, advance pointers greedily.
 *    Examples: Assign Cookies (LC 455), Player-Trainer Matching (LC 2410)
 *
 *  PATTERN 3: PARTITION LABELS
 *    Track last occurrence, extend partition greedily.
 *    Example: Partition Labels (LC 763)
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ============================================================================
// PATTERN 1: Boats to Save People (LC 881)
// Each boat carries at most 2 people with total weight ≤ limit
// Minimize number of boats
// ============================================================================
int numRescueBoats(vector<int>& people, int limit) {
    sort(people.begin(), people.end());
    int left = 0, right = (int)people.size() - 1;
    int boats = 0;

    while (left <= right) {
        // Greedy: try to pair lightest with heaviest
        if (people[left] + people[right] <= limit) {
            left++;  // Lightest person fits with heaviest
        }
        right--;  // Heaviest person always gets on a boat
        boats++;
    }
    return boats;
}

// ============================================================================
// PATTERN 2: Assign Cookies (LC 455)
// Each child has a greed factor, each cookie has a size
// Assign cookies to maximize satisfied children
// ============================================================================
int assignCookies(vector<int>& children, vector<int>& cookies) {
    sort(children.begin(), children.end());
    sort(cookies.begin(), cookies.end());

    int child = 0, cookie = 0;
    while (child < (int)children.size() && cookie < (int)cookies.size()) {
        if (cookies[cookie] >= children[child]) {
            child++;  // This child is satisfied
        }
        cookie++;  // Move to next cookie regardless
    }
    return child;  // Number of satisfied children
}

// ============================================================================
// PATTERN 3: Partition Labels (LC 763)
// Partition string so each letter appears in at most one part
// Maximize number of parts
// ============================================================================
vector<int> partitionLabels(string s) {
    // Greedy: track last occurrence of each character
    vector<int> lastOccurrence(26, 0);
    for (int i = 0; i < (int)s.size(); i++)
        lastOccurrence[s[i] - 'a'] = i;

    vector<int> result;
    int start = 0, end = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        end = max(end, lastOccurrence[s[i] - 'a']);
        if (i == end) {
            result.push_back(end - start + 1);
            start = end + 1;
        }
    }
    return result;
}

int main() {
    // Boats
    vector<int> people = {3, 2, 2, 1};
    cout << "Boats needed: " << numRescueBoats(people, 3) << endl; // 3

    // Cookies
    vector<int> children = {1, 2, 3}, cookies = {1, 1};
    cout << "Satisfied children: " << assignCookies(children, cookies) << endl; // 1

    // Partition Labels
    string s = "ababcbacadefegdehijhklij";
    auto parts = partitionLabels(s);
    cout << "Partitions: ";
    for (int p : parts) cout << p << " ";
    cout << endl; // 9 7 8

    return 0;
}

