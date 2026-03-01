/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Optimal Merge Pattern — Min Cost to Merge
 *  Level   : Intermediate
 * ============================================================================
 *
 *  PROBLEM: Given N sorted files of different sizes, merge them into a single file.
 *           Cost of merging two files = sum of their sizes.
 *           Find minimum total merge cost.
 *
 *  GREEDY: Always merge the two SMALLEST files first (like Huffman coding).
 *  DATA STRUCTURE: Min-Heap
 *  TIME: O(N log N)
 *
 *  Same idea as CSES "Stick Lengths" and many other merge problems.
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

long long optimalMergeCost(vector<int>& sizes) {
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    for (int s : sizes) pq.push(s);

    long long totalCost = 0;
    while (pq.size() > 1) {
        long long a = pq.top(); pq.pop();
        long long b = pq.top(); pq.pop();
        totalCost += a + b;
        pq.push(a + b);
    }
    return totalCost;
}

int main() {
    vector<int> sizes = {2, 3, 4, 5, 6, 7};
    cout << "Min merge cost: " << optimalMergeCost(sizes) << endl; // 68
    return 0;
}

