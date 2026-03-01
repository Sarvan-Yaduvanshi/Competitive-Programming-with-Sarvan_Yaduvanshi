/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — BINARY HEAP FROM SCRATCH                                      ║
║           From Zero to Grandmaster — Heap Basics & Implementation           ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. What is a Heap?
 2. Heap Property (Max & Min)
 3. Array Representation
 4. Parent-Child Index Formulas
 5. Complete Implementation
 6. Heapify Up (Bubble Up)
 7. Heapify Down (Sift Down)
 8. Insert & Extract
 9. Build Heap in O(n)
 10. Dry Run

WHAT IS A HEAP?
──────────────
  A Heap is a COMPLETE BINARY TREE stored in an array that satisfies
  the HEAP PROPERTY:

  MAX HEAP: Every parent ≥ its children
  MIN HEAP: Every parent ≤ its children

  Complete Binary Tree: All levels filled except possibly the last,
  which is filled from left to right.

  ✅ Get max/min in O(1)
  ✅ Insert in O(log n)
  ✅ Delete max/min in O(log n)
  ✅ Build heap in O(n)

ARRAY REPRESENTATION:
────────────────────
  For 0-indexed array:
    Parent of i:      (i - 1) / 2
    Left child of i:  2 * i + 1
    Right child of i: 2 * i + 2

  For 1-indexed array:
    Parent of i:      i / 2
    Left child of i:  2 * i
    Right child of i: 2 * i + 1

  Example MAX HEAP:
         50
        /  \
      30    40
     / \   /
    10  20 35

  Array (0-indexed): [50, 30, 40, 10, 20, 35]
  Index:               0   1   2   3   4   5

  Verification:
    Parent of idx 3 (val 10) = (3-1)/2 = 1 → val 30  ✅ (30 ≥ 10)
    Left child of idx 1 (val 30) = 2*1+1 = 3 → val 10  ✅
    Right child of idx 1 (val 30) = 2*1+2 = 4 → val 20  ✅

HEAPIFY UP (BUBBLE UP):
──────────────────────
  Used after INSERT. New element placed at end, then bubbles up.

  Insert 60 into [50, 30, 40, 10, 20, 35]:

  Step 1: Place at end → [50, 30, 40, 10, 20, 35, 60]
                                                     ↑ idx=6

  Step 2: Compare with parent: parent(6) = 2, arr[2]=40
          60 > 40 → swap → [50, 30, 60, 10, 20, 35, 40]
                                    ↑ now at idx=2

  Step 3: Compare with parent: parent(2) = 0, arr[0]=50
          60 > 50 → swap → [60, 30, 50, 10, 20, 35, 40]
                             ↑ now at idx=0 (root)

  Step 4: idx=0, no parent → STOP

HEAPIFY DOWN (SIFT DOWN):
────────────────────────
  Used after EXTRACT. Root removed, last element placed at root, sifts down.

  Extract max from [60, 30, 50, 10, 20, 35, 40]:

  Step 1: Save max=60, move last to root → [40, 30, 50, 10, 20, 35]
                                             ↑ idx=0

  Step 2: Children of 0: left=1(30), right=2(50)
          Largest child = 50 at idx 2
          40 < 50 → swap → [50, 30, 40, 10, 20, 35]
                                    ↑ now at idx=2

  Step 3: Children of 2: left=5(35), right=6(doesn't exist)
          Only child = 35
          40 > 35 → STOP

  Result: [50, 30, 40, 10, 20, 35], extracted 60

TIME COMPLEXITY:
───────────────
  ┌────────────────┬──────────┬─────────────────────────────┐
  │ Operation      │  Time    │ Why                         │
  ├────────────────┼──────────┼─────────────────────────────┤
  │ Insert         │ O(log n) │ Bubble up at most h levels  │
  │ Extract Max    │ O(log n) │ Sift down at most h levels  │
  │ Peek Max       │ O(1)     │ Always at index 0           │
  │ Build Heap     │ O(n)     │ Mathematical proof below    │
  │ Heap Sort      │O(n log n)│ n extractions × O(log n)    │
  └────────────────┴──────────┴─────────────────────────────┘
  where h = log₂(n) = height of tree
*/

#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// MAX HEAP IMPLEMENTATION
// ═══════════════════════════════════════════════════════════════

class MaxHeap {
private:
    vector<int> heap;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    // Bubble up: Move element at idx UP to maintain heap property
    void heapifyUp(int idx) {
        while (idx > 0 && heap[parent(idx)] < heap[idx]) {
            swap(heap[parent(idx)], heap[idx]);
            idx = parent(idx);
        }
    }

    // Sift down: Move element at idx DOWN to maintain heap property
    void heapifyDown(int idx) {
        int size = heap.size();
        while (true) {
            int largest = idx;
            int left = leftChild(idx);
            int right = rightChild(idx);

            if (left < size && heap[left] > heap[largest])
                largest = left;
            if (right < size && heap[right] > heap[largest])
                largest = right;

            if (largest == idx) break;  // Heap property satisfied

            swap(heap[idx], heap[largest]);
            idx = largest;
        }
    }

public:
    // Insert: Add element, bubble up — O(log n)
    void insert(int val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }

    // Extract Max: Remove root, sift down — O(log n)
    int extractMax() {
        if (heap.empty()) throw runtime_error("Heap is empty!");

        int maxVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty()) heapifyDown(0);
        return maxVal;
    }

    // Peek: View max without removing — O(1)
    int getMax() {
        if (heap.empty()) throw runtime_error("Heap is empty!");
        return heap[0];
    }

    bool empty() { return heap.empty(); }
    int size() { return heap.size(); }

    // Build heap from array — O(n)
    void buildHeap(vector<int>& arr) {
        heap = arr;
        // Start from last non-leaf node and heapify down
        for (int i = heap.size() / 2 - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }

    void display() {
        cout << "  Heap: [";
        for (int i = 0; i < (int)heap.size(); i++) {
            cout << heap[i];
            if (i + 1 < (int)heap.size()) cout << ", ";
        }
        cout << "]\n";
    }

    // Display as tree
    void displayTree() {
        if (heap.empty()) { cout << "  (empty)\n"; return; }
        int level = 0, count = 0;
        for (int i = 0; i < (int)heap.size(); i++) {
            if (count == 0) {
                cout << "  Level " << level << ": ";
            }
            cout << heap[i] << " ";
            count++;
            if (count == (1 << level)) {
                cout << "\n";
                level++;
                count = 0;
            }
        }
        if (count > 0) cout << "\n";
    }
};

// ═══════════════════════════════════════════════════════════════
// MIN HEAP IMPLEMENTATION
// ═══════════════════════════════════════════════════════════════

class MinHeap {
private:
    vector<int> heap;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void heapifyUp(int idx) {
        while (idx > 0 && heap[parent(idx)] > heap[idx]) {
            swap(heap[parent(idx)], heap[idx]);
            idx = parent(idx);
        }
    }

    void heapifyDown(int idx) {
        int size = heap.size();
        while (true) {
            int smallest = idx;
            int left = leftChild(idx);
            int right = rightChild(idx);

            if (left < size && heap[left] < heap[smallest]) smallest = left;
            if (right < size && heap[right] < heap[smallest]) smallest = right;

            if (smallest == idx) break;
            swap(heap[idx], heap[smallest]);
            idx = smallest;
        }
    }

public:
    void insert(int val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }

    int extractMin() {
        if (heap.empty()) throw runtime_error("Heap is empty!");
        int minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) heapifyDown(0);
        return minVal;
    }

    int getMin() { return heap[0]; }
    bool empty() { return heap.empty(); }
    int size() { return heap.size(); }
};

// ═══════════════════════════════════════════════════════════════
// BUILD HEAP O(n) PROOF
// ═══════════════════════════════════════════════════════════════
/*
  Why is build heap O(n) and not O(n log n)?

  Start from the bottom non-leaf nodes and heapify down.

  At height h, there are at most ⌈n / 2^(h+1)⌉ nodes.
  Each node at height h does O(h) work in heapifyDown.

  Total work = Σ (h=0 to log n) ⌈n / 2^(h+1)⌉ × O(h)
             = n × Σ (h=0 to ∞) h / 2^(h+1)
             = n × 2    (by geometric series)
             = O(n)

  Visual: For n=15 (height=3):
    Level 3 (leaves, 8 nodes):  0 swaps each  = 0
    Level 2 (4 nodes):          ≤1 swap each  = 4
    Level 1 (2 nodes):          ≤2 swaps each = 4
    Level 0 (root, 1 node):     ≤3 swaps each = 3
    Total = 0 + 4 + 4 + 3 = 11 << 15 × log(15) ≈ 58
*/

// ═══════════════════════════════════════════════════════════════
// HEAP SORT
// ═══════════════════════════════════════════════════════════════

void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Build max heap — O(n)
    for (int i = n / 2 - 1; i >= 0; i--) {
        // Sift down
        int idx = i;
        while (true) {
            int largest = idx;
            int left = 2 * idx + 1, right = 2 * idx + 2;
            if (left < n && arr[left] > arr[largest]) largest = left;
            if (right < n && arr[right] > arr[largest]) largest = right;
            if (largest == idx) break;
            swap(arr[idx], arr[largest]);
            idx = largest;
        }
    }

    // Extract max n times — O(n log n)
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);  // Move max to end
        // Sift down on reduced heap [0..i-1]
        int idx = 0;
        while (true) {
            int largest = idx;
            int left = 2 * idx + 1, right = 2 * idx + 2;
            if (left < i && arr[left] > arr[largest]) largest = left;
            if (right < i && arr[right] > arr[largest]) largest = right;
            if (largest == idx) break;
            swap(arr[idx], arr[largest]);
            idx = largest;
        }
    }
}

// ═══════════════════════════════════════════════════════════════
// DEMONSTRATION
// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  BINARY HEAP FROM SCRATCH + HEAP SORT                    ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Max Heap
    cout << "═══ MAX HEAP ═══\n";
    MaxHeap maxH;
    for (int v : {10, 30, 20, 50, 40, 35}) {
        maxH.insert(v);
        cout << "  Insert " << v << ": ";
        maxH.display();
    }
    cout << "\nTree view:\n";
    maxH.displayTree();

    cout << "\nExtract max: " << maxH.extractMax() << "\n";
    maxH.display();
    cout << "Extract max: " << maxH.extractMax() << "\n";
    maxH.display();

    // Build heap from array
    cout << "\n═══ BUILD HEAP O(n) ═══\n";
    vector<int> arr = {3, 1, 6, 5, 2, 4};
    cout << "Input: [3,1,6,5,2,4]\n";
    MaxHeap builtHeap;
    builtHeap.buildHeap(arr);
    builtHeap.display();
    builtHeap.displayTree();

    // Min Heap
    cout << "\n═══ MIN HEAP ═══\n";
    MinHeap minH;
    for (int v : {40, 10, 30, 5, 20}) {
        minH.insert(v);
    }
    cout << "Extract min order: ";
    while (!minH.empty()) {
        cout << minH.extractMin() << " ";
    }
    cout << "\n";

    // Heap Sort
    cout << "\n═══ HEAP SORT ═══\n";
    vector<int> sortArr = {38, 27, 43, 3, 9, 82, 10};
    cout << "Before: ";
    for (int x : sortArr) cout << x << " ";
    heapSort(sortArr);
    cout << "\nAfter:  ";
    for (int x : sortArr) cout << x << " ";
    cout << "\n";

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "COMPLEXITY SUMMARY:\n";
    cout << "  Insert:      O(log n)\n";
    cout << "  Extract:     O(log n)\n";
    cout << "  Peek:        O(1)\n";
    cout << "  Build Heap:  O(n)\n";
    cout << "  Heap Sort:   O(n log n) in-place, NOT stable\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

