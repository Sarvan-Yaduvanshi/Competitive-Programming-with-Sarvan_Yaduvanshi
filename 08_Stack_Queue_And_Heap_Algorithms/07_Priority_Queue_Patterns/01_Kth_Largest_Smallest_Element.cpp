/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — KTH LARGEST / SMALLEST ELEMENT (LC 215)                       ║
║           From Zero to Grandmaster — Priority Queue Patterns                ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Find the Kth largest element in an unsorted array.
  Input: [3,2,1,5,6,4], k=2  → Answer: 5

APPROACH 1: Sort → O(n log n)
APPROACH 2: Min Heap of size K → O(n log k)
APPROACH 3: Quick Select → O(n) average

MIN HEAP OF SIZE K — The Classic Pattern:
────────────────────────────────────────
  Maintain a min-heap of size k.
  The ROOT (minimum of heap) = the Kth largest overall.

  Why? The heap contains the K largest elements.
  The smallest among them (root) is the Kth largest.

  DRY RUN: [3,2,1,5,6,4], k=2

  i=0: push 3 → heap=[3]        (size<k, just push)
  i=1: push 2 → heap=[2,3]      (size=k, stop pushing freely)
  i=2: 1 < heap.top()=2 → skip  (1 can't be in top-2)
  i=3: 5 > heap.top()=2 → pop 2, push 5 → heap=[3,5]
  i=4: 6 > heap.top()=3 → pop 3, push 6 → heap=[5,6]
  i=5: 4 < heap.top()=5 → skip

  Answer: heap.top() = 5 ✅ (2nd largest)

TIME: O(n log k)  SPACE: O(k)
When k is small, this is much better than sorting!
*/

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// Kth LARGEST — Min Heap of size K
// ═══════════════════════════════════════════════════════════════

int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;

    for (int num : nums) {
        minHeap.push(num);
        if ((int)minHeap.size() > k) {
            minHeap.pop();  // Remove smallest, keep k largest
        }
    }
    return minHeap.top();  // Kth largest
}

// ═══════════════════════════════════════════════════════════════
// Kth SMALLEST — Max Heap of size K
// ═══════════════════════════════════════════════════════════════

int findKthSmallest(vector<int>& nums, int k) {
    priority_queue<int> maxHeap;

    for (int num : nums) {
        maxHeap.push(num);
        if ((int)maxHeap.size() > k) {
            maxHeap.pop();  // Remove largest, keep k smallest
        }
    }
    return maxHeap.top();  // Kth smallest
}

// ═══════════════════════════════════════════════════════════════
// K CLOSEST POINTS TO ORIGIN (LC 973)
// ═══════════════════════════════════════════════════════════════

vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
    // Max heap — keep k smallest distances
    auto cmp = [](vector<int>& a, vector<int>& b) {
        return a[0]*a[0]+a[1]*a[1] < b[0]*b[0]+b[1]*b[1];
    };
    priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> maxH(cmp);

    for (auto& p : points) {
        maxH.push(p);
        if ((int)maxH.size() > k) maxH.pop();
    }

    vector<vector<int>> result;
    while (!maxH.empty()) {
        result.push_back(maxH.top());
        maxH.pop();
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// SORT NEARLY SORTED ARRAY (K-sorted)
// ═══════════════════════════════════════════════════════════════
/*
  Each element is at most K positions from its sorted position.
  Use min-heap of size K+1.

  DRY RUN: [6,5,3,2,8,10,9], k=3
  Heap: push first k+1=4 elements: {6,5,3,2} → min=2
  Extract min → sorted[0] = 2
  Push 8, extract min → sorted[1] = 3 (from {5,6,8})... etc.

  Time: O(n log k)
*/

vector<int> sortNearlySorted(vector<int>& arr, int k) {
    priority_queue<int, vector<int>, greater<int>> minH;
    vector<int> result;

    for (int i = 0; i < (int)arr.size(); i++) {
        minH.push(arr[i]);
        if ((int)minH.size() > k + 1) {
            result.push_back(minH.top());
            minH.pop();
        }
    }
    while (!minH.empty()) {
        result.push_back(minH.top());
        minH.pop();
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  KTH LARGEST / SMALLEST + K-ELEMENT PATTERNS             ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Kth Largest
    vector<int> nums = {3, 2, 1, 5, 6, 4};
    cout << "Array: [3,2,1,5,6,4]\n";
    cout << "2nd largest: " << findKthLargest(nums, 2) << "\n";
    cout << "3rd smallest: " << findKthSmallest(nums, 3) << "\n\n";

    // Sort nearly sorted
    vector<int> nearly = {6, 5, 3, 2, 8, 10, 9};
    auto sorted = sortNearlySorted(nearly, 3);
    cout << "Nearly sorted [6,5,3,2,8,10,9] k=3:\n  Sorted: ";
    for (int x : sorted) cout << x << " ";
    cout << "\n";

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PATTERN: For Kth LARGEST  → use MIN heap of size K\n";
    cout << "         For Kth SMALLEST → use MAX heap of size K\n";
    cout << "\nPRACTICE:\n";
    cout << "  LC 215  — Kth Largest Element\n";
    cout << "  LC 973  — K Closest Points to Origin\n";
    cout << "  LC 703  — Kth Largest Element in Stream\n";
    cout << "  LC 378  — Kth Smallest in Sorted Matrix\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

