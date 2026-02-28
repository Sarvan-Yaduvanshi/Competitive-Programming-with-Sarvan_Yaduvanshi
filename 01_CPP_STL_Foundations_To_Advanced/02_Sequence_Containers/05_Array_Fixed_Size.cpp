/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           05 — std::array (Fixed-Size Container)                           ║
║           From Zero to Grandmaster                                         ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

  std::array<T, N> = fixed-size array with STL interface.
  Size known at COMPILE time. No heap allocation.
  Same performance as C-array but with bounds checking and STL compatibility.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "═══ std::array GUIDE ═══\n\n";

    // Declaration (size must be compile-time constant!)
    array<int, 5> arr = {10, 20, 30, 40, 50};

    // Access
    cout << "arr[0] = " << arr[0] << "\n";
    cout << "arr.at(2) = " << arr.at(2) << " (bounds-checked!)\n";
    cout << "front = " << arr.front() << ", back = " << arr.back() << "\n";
    cout << "size = " << arr.size() << "\n\n";

    // Iteration
    cout << "Range-for: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    // fill
    array<int, 5> filled;
    filled.fill(42);
    cout << "fill(42): ";
    for (int x : filled) cout << x << " ";
    cout << "\n";

    // sort (works because random-access iterators)
    array<int, 5> unsorted = {5, 3, 1, 4, 2};
    sort(unsorted.begin(), unsorted.end());
    cout << "sorted: ";
    for (int x : unsorted) cout << x << " ";
    cout << "\n";

    // Comparison (lexicographic!)
    array<int, 3> a = {1, 2, 3};
    array<int, 3> b = {1, 2, 4};
    cout << "\n{1,2,3} < {1,2,4}: " << (a < b ? "true" : "false") << "\n";
    cout << "{1,2,3} == {1,2,3}: " << (a == a ? "true" : "false") << "\n";

    // swap
    array<int, 3> x = {1, 2, 3};
    array<int, 3> y = {4, 5, 6};
    x.swap(y);
    cout << "\nAfter swap: x = ";
    for (int v : x) cout << v << " ";
    cout << ", y = ";
    for (int v : y) cout << v << " ";
    cout << "\n";

    // data() — get raw pointer
    int* ptr = arr.data();
    cout << "\ndata()[0] = " << ptr[0] << "\n\n";

    // std::array vs C-array
    cout << "═══ std::array vs C-array ═══\n";
    cout << "┌──────────────────┬──────────────┬──────────────┐\n";
    cout << "│ Feature          │ C-array      │ std::array   │\n";
    cout << "├──────────────────┼──────────────┼──────────────┤\n";
    cout << "│ Size at runtime  │ No .size()   │ .size() ✓    │\n";
    cout << "│ Bounds checking  │ No           │ .at() ✓      │\n";
    cout << "│ STL compatible   │ Partial      │ Full ✓       │\n";
    cout << "│ Pass by value    │ Decays to ptr│ Copies ✓     │\n";
    cout << "│ Comparison       │ Can't ==     │ ==, <, > ✓   │\n";
    cout << "│ Performance      │ Same         │ Same         │\n";
    cout << "└──────────────────┴──────────────┴──────────────┘\n\n";

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. std::array = C-array + STL features\n";
    cout << "2. Size is compile-time constant (can't resize)\n";
    cout << "3. Use in CP when size is known and small\n";
    cout << "4. Supports sort, fill, comparison, iteration\n";
    cout << "5. In CP, vector is usually preferred (dynamic size)\n";

    return 0;
}

