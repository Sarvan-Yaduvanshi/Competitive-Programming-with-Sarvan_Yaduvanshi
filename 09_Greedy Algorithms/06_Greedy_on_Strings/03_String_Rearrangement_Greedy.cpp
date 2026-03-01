/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : String Rearrangement Greedy — Frequency-Based PQ
 *  Level   : Advanced
 * ============================================================================
 *
 *  PATTERN: Rearrange string characters using a Max-Heap (Priority Queue)
 *  to avoid placing the same character adjacent or to satisfy constraints.
 *
 *  PROBLEMS:
 *  1. Reorganize String (LC 767) — No two adjacent same chars
 *  2. Longest Happy String (LC 1405) — At most 2 consecutive same chars
 *  3. Task Scheduler (LC 621) — Similar pattern with cooldown
 *  4. Dota2 Senate (LC 649) — Queue-based greedy elimination
 *
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;

// ============================================================================
// LC 767: Reorganize String — No two adjacent chars same
// ============================================================================
string reorganizeString(string s) {
    vector<int> freq(26, 0);
    for (char c : s) freq[c - 'a']++;

    // Check feasibility: max freq > (n+1)/2 → impossible
    int n = s.size();
    for (int f : freq)
        if (f > (n + 1) / 2) return "";

    // Max-heap of {frequency, character}
    priority_queue<pair<int,char>> pq;
    for (int i = 0; i < 26; i++)
        if (freq[i] > 0)
            pq.push({freq[i], 'a' + i});

    string result;
    while (pq.size() >= 2) {
        auto [f1, c1] = pq.top(); pq.pop();
        auto [f2, c2] = pq.top(); pq.pop();

        result += c1;
        result += c2;

        if (f1 - 1 > 0) pq.push({f1 - 1, c1});
        if (f2 - 1 > 0) pq.push({f2 - 1, c2});
    }

    if (!pq.empty()) result += pq.top().second;
    return result;
}

// ============================================================================
// LC 1405: Longest Happy String — At most 2 consecutive of same char
// ============================================================================
string longestHappyString(int a, int b, int c) {
    priority_queue<pair<int,char>> pq;
    if (a > 0) pq.push({a, 'a'});
    if (b > 0) pq.push({b, 'b'});
    if (c > 0) pq.push({c, 'c'});

    string result;
    while (!pq.empty()) {
        auto [f1, c1] = pq.top(); pq.pop();

        int len = result.size();
        // If last two chars are same as c1, pick second most frequent
        if (len >= 2 && result[len-1] == c1 && result[len-2] == c1) {
            if (pq.empty()) break;
            auto [f2, c2] = pq.top(); pq.pop();
            result += c2;
            if (f2 - 1 > 0) pq.push({f2 - 1, c2});
            pq.push({f1, c1}); // Put back the most frequent
        } else {
            result += c1;
            if (f1 - 1 > 0) pq.push({f1 - 1, c1});
        }
    }
    return result;
}

// ============================================================================
// LC 621: Task Scheduler — Minimum intervals with cooldown
// ============================================================================
int leastInterval(vector<char>& tasks, int n) {
    vector<int> freq(26, 0);
    for (char t : tasks) freq[t - 'A']++;

    int maxFreq = *max_element(freq.begin(), freq.end());
    int maxCount = count(freq.begin(), freq.end(), maxFreq);

    // Formula: (maxFreq - 1) * (n + 1) + maxCount
    // But result can't be less than total tasks
    return max((int)tasks.size(), (maxFreq - 1) * (n + 1) + maxCount);
}

int main() {
    // Reorganize
    cout << "Reorganize 'aab': " << reorganizeString("aab") << endl; // "aba"
    cout << "Reorganize 'aaab': " << reorganizeString("aaab") << endl; // "" (impossible)

    // Happy String
    cout << "Happy (1,1,7): " << longestHappyString(1, 1, 7) << endl; // "ccbccacc"

    // Task Scheduler
    vector<char> tasks = {'A','A','A','B','B','B'};
    cout << "Min intervals (n=2): " << leastInterval(tasks, 2) << endl; // 8

    return 0;
}

