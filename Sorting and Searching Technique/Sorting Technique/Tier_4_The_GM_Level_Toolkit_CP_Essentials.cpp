/*
Author: Sarvan.DP.GrandMaster
Created : 2026-01-21
Topic: C++ STL Sorting - Complete Reference (Basic to GM Level)
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <iomanip>
#include <numeric>
#include <random>
#include <chrono>

using namespace std;

#define nl "\n"
#define ll long long
#define vec vector
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()

// =====================================================================
// 1. BASIC STL SORTING
// =====================================================================

// 1.1 Sorting Arrays
void sortArray() {
    cout << "\n=== 1.1 Sorting Arrays ===\n";
    int arr[] = {5, 2, 8, 1, 9};
    int n = 5;

    // Increasing Order
    sort(arr, arr + n);
    cout << "Increasing: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << nl;

    // Decreasing Order
    sort(arr, arr + n, greater<int>());
    cout << "Decreasing: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << nl;
}

// 1.2 Sorting Vectors
void sortVector() {
    cout << "\n=== 1.2 Sorting Vectors ===\n";
    vec<int> v = {5, 2, 8, 1, 9};

    // Increasing Order
    sort(v.begin(), v.end());
    cout << "Increasing: ";
    for (auto x : v) cout << x << " ";
    cout << nl;

    // Decreasing Order - Method 1
    sort(v.begin(), v.end(), greater<int>());
    cout << "Decreasing (Method 1): ";
    for (auto x : v) cout << x << " ";
    cout << nl;

    // Decreasing Order - Method 2 (using reverse iterators)
    sort(v.rbegin(), v.rend());
    cout << "Decreasing (Method 2): ";
    for (auto x : v) cout << x << " ";
    cout << nl;
}

// =====================================================================
// 2. CUSTOM COMPARATOR
// =====================================================================

// 2.1 Lambda Function (Modern C++)
void sortWithLambda() {
    cout << "\n=== 2.1 Custom Comparator (Lambda) ===\n";
    vec<int> v = {5, 2, 8, 1, 9};

    // Decreasing order using lambda
    sort(v.begin(), v.end(), [](int a, int b) {
        return a > b; // if true, 'a' comes before 'b'
    });
    cout << "Decreasing: ";
    for (auto x : v) cout << x << " ";
    cout << nl;
}

// 2.2 Comparison Function
bool decreasing(int a, int b) {
    return a > b;
}

bool increasing(int a, int b) {
    return a < b;
}

void sortWithFunction() {
    cout << "\n=== 2.2 Custom Comparator (Function) ===\n";
    vec<int> v = {5, 2, 8, 1, 9};

    sort(v.begin(), v.end(), decreasing);
    cout << "Decreasing: ";
    for (auto x : v) cout << x << " ";
    cout << nl;

    sort(v.begin(), v.end(), increasing);
    cout << "Increasing: ";
    for (auto x : v) cout << x << " ";
    cout << nl;
}

// =====================================================================
// 3. SORTING PAIRS
// =====================================================================

void sortingPairs() {
    cout << "\n=== 3. Sorting Pairs ===\n";
    vec<pair<int, int>> v = {{3, 5}, {1, 2}, {3, 1}, {2, 4}};

    // Default: sorts by first, then by second (both increasing)
    sort(v.begin(), v.end());
    cout << "Default (both increasing): ";
    for (auto p : v) cout << "{" << p.fi << "," << p.se << "} ";
    cout << nl;

    // Custom: first increasing, second DECREASING
    v = {{3, 5}, {1, 2}, {3, 1}, {2, 4}};
    sort(v.begin(), v.end(), [](pair<int,int> a, pair<int,int> b) {
        if (a.fi != b.fi) return a.fi < b.fi;  // first increasing
        return a.se > b.se;  // second decreasing
    });
    cout << "First inc, Second dec: ";
    for (auto p : v) cout << "{" << p.fi << "," << p.se << "} ";
    cout << nl;

    // Both decreasing
    v = {{3, 5}, {1, 2}, {3, 1}, {2, 4}};
    sort(v.begin(), v.end(), [](pair<int,int> a, pair<int,int> b) {
        if (a.fi != b.fi) return a.fi > b.fi;  // first decreasing
        return a.se > b.se;  // second decreasing
    });
    cout << "Both decreasing: ";
    for (auto p : v) cout << "{" << p.fi << "," << p.se << "} ";
    cout << nl;
}

// =====================================================================
// 4. SORTING CUSTOM OBJECTS (STRUCT/CLASS)
// =====================================================================

struct Student {
    string name;
    int marks;
    int age;
};

void sortStudent() {
    cout << "\n=== 4. Sorting Custom Objects (Student) ===\n";
    vec<Student> students = {
        {"Alice", 85, 20},
        {"Bob", 92, 19},
        {"Charlie", 85, 21},
        {"David", 78, 20}
    };

    // Sort by marks (DECREASING), if same then by age (INCREASING)
    sort(students.begin(), students.end(), [](Student a, Student b) {
        if (a.marks != b.marks) return a.marks > b.marks;
        return a.age < b.age;
    });

    cout << "Sorted by marks(desc), age(asc):\n";
    for (auto s : students) {
        cout << s.name << " " << s.marks << " " << s.age << nl;
    }
}

// =====================================================================
// 5. SORTING STRINGS
// =====================================================================

void sortString() {
    cout << "\n=== 5. Sorting Strings ===\n";
    vec<string> v = {"apple", "Banana", "cherry", "Date"};

    // Case Sensitive (default)
    sort(v.begin(), v.end());
    cout << "Case Sensitive: ";
    for (auto s : v) cout << s << " ";
    cout << nl;

    // Case Insensitive
    v = {"apple", "Banana", "cherry", "Date"};
    sort(v.begin(), v.end(), [](string a, string b) {
        transform(a.begin(), a.end(), a.begin(), ::tolower);
        transform(b.begin(), b.end(), b.begin(), ::tolower);
        return a < b;
    });
    cout << "Case Insensitive: ";
    for (auto s : v) cout << s << " ";
    cout << nl;

    // Sort by length (shorter first)
    v = {"apple", "Banana", "cherry", "Date"};
    sort(v.begin(), v.end(), [](string a, string b) {
        return a.length() < b.length();
    });
    cout << "By length: ";
    for (auto s : v) cout << s << " ";
    cout << nl;
}

// =====================================================================
// 6. SORTING BY ABSOLUTE VALUE
// =====================================================================

void sortByAbsoluteValue() {
    cout << "\n=== 6. Sorting by Absolute Value ===\n";
    vec<int> v = {-5, 3, -8, 1, 7, -2};

    // Sort by absolute value (increasing)
    sort(v.begin(), v.end(), [](int a, int b) {
        return abs(a) < abs(b);
    });

    cout << "By absolute value: ";
    for (auto x : v) cout << x << " ";
    cout << nl;
}

// =====================================================================
// 7. SORTING 2D VECTORS / MATRIX
// =====================================================================

void sort2DVector() {
    cout << "\n=== 7. Sorting 2D Vectors ===\n";
    vec<vec<int>> matrix = {
        {3, 1, 4},
        {1, 5, 9},
        {2, 6, 5}
    };

    // Sort each row
    for (auto &row : matrix) {
        sort(row.begin(), row.end());
    }
    cout << "After sorting each row:\n";
    for (auto row : matrix) {
        for (auto x : row) cout << x << " ";
        cout << nl;
    }

    // Sort rows by their first element
    sort(matrix.begin(), matrix.end(), [](vec<int> a, vec<int> b) {
        return a[0] < b[0];
    });
    cout << "After sorting rows by first element:\n";
    for (auto row : matrix) {
        for (auto x : row) cout << x << " ";
        cout << nl;
    }

    // Sort rows by sum (decreasing)
    sort(matrix.begin(), matrix.end(), [](vec<int> a, vec<int> b) {
        int sumA = accumulate(a.begin(), a.end(), 0);
        int sumB = accumulate(b.begin(), b.end(), 0);
        return sumA > sumB;
    });
    cout << "After sorting rows by sum (desc):\n";
    for (auto row : matrix) {
        for (auto x : row) cout << x << " ";
        cout << nl;
    }
}

// =====================================================================
// 8. PARTIAL SORTING
// =====================================================================

void partialSorting() {
    cout << "\n=== 8. Partial Sorting ===\n";
    vec<int> v = {5, 2, 8, 1, 9, 3, 7};

    // Sort only first 3 elements (smallest 3)
    partial_sort(v.begin(), v.begin() + 3, v.end());
    cout << "After partial_sort (first 3 smallest): ";
    for (auto x : v) cout << x << " ";
    cout << nl;
    // Output: 1 2 3 [remaining elements unsorted]
}

// =====================================================================
// 9. NTH ELEMENT - Finding Kth Smallest/Largest
// =====================================================================

void nthElementExample() {
    cout << "\n=== 9. Nth Element (Kth Smallest) ===\n";
    vec<int> v = {5, 2, 8, 1, 9, 3, 7};

    // Find 3rd smallest element (index 2)
    nth_element(v.begin(), v.begin() + 2, v.end());
    cout << "3rd smallest element: " << v[2] << nl;
    cout << "Array state: ";
    for (auto x : v) cout << x << " ";
    cout << nl;

    // Find 3rd largest (n-3 position)
    v = {5, 2, 8, 1, 9, 3, 7};
    nth_element(v.begin(), v.begin() + (v.size() - 3), v.end());
    cout << "3rd largest element: " << v[v.size() - 3] << nl;
}

// =====================================================================
// 10. STABLE SORT - Maintaining Relative Order
// =====================================================================

void stableSortExample() {
    cout << "\n=== 10. Stable Sort ===\n";
    vec<pair<int, string>> v = {
        {3, "Alice"}, {1, "Bob"}, {3, "Charlie"}, {2, "David"}, {3, "Eve"}
    };

    // Regular sort (may not maintain relative order)
    auto v1 = v;
    sort(v1.begin(), v1.end(), [](auto a, auto b) {
        return a.fi < b.fi;
    });
    cout << "Regular sort:\n";
    for (auto p : v1) cout << p.fi << " " << p.se << nl;

    // Stable sort (maintains relative order of equal elements)
    auto v2 = v;
    stable_sort(v2.begin(), v2.end(), [](auto a, auto b) {
        return a.fi < b.fi;
    });
    cout << "\nStable sort (maintains order for equal elements):\n";
    for (auto p : v2) cout << p.fi << " " << p.se << nl;
}

// =====================================================================
// 11. SORTING INDICES BASED ON VALUES
// =====================================================================

void sortIndices() {
    cout << "\n=== 11. Sorting Indices Based on Array Values ===\n";
    vec<int> arr = {5, 2, 8, 1, 9};
    int n = arr.size();

    vec<int> indices(n);
    iota(indices.begin(), indices.end(), 0);  // 0, 1, 2, 3, 4

    // Sort indices based on array values
    sort(indices.begin(), indices.end(), [&](int i, int j) {
        return arr[i] < arr[j];
    });

    cout << "Original array: ";
    for (auto x : arr) cout << x << " ";
    cout << nl;

    cout << "Sorted indices: ";
    for (auto i : indices) cout << i << " ";
    cout << nl;

    cout << "Values at sorted indices: ";
    for (auto i : indices) cout << arr[i] << " ";
    cout << nl;
}

// =====================================================================
// 12. SORTING WITH MULTIPLE CRITERIA
// =====================================================================

void sortMultipleCriteria() {
    cout << "\n=== 12. Sorting with Multiple Criteria ===\n";

    struct Employee {
        string name;
        int salary;
        int experience;
        int age;
    };

    vec<Employee> emp = {
        {"Alice", 50000, 5, 28},
        {"Bob", 60000, 3, 25},
        {"Charlie", 50000, 5, 30},
        {"David", 50000, 7, 28}
    };

    // Sort by: salary(desc) -> experience(desc) -> age(asc)
    sort(emp.begin(), emp.end(), [](Employee a, Employee b) {
        if (a.salary != b.salary) return a.salary > b.salary;
        if (a.experience != b.experience) return a.experience > b.experience;
        return a.age < b.age;
    });

    cout << "Sorted by salary(desc), experience(desc), age(asc):\n";
    for (auto e : emp) {
        cout << e.name << " " << e.salary << " " << e.experience << " " << e.age << nl;
    }
}

// =====================================================================
// 13. REVERSE WITHOUT SORTING
// =====================================================================

void reverseExample() {
    cout << "\n=== 13. Reverse Without Sorting ===\n";
    vec<int> v = {5, 2, 8, 1, 9};

    cout << "Original: ";
    for (auto x : v) cout << x << " ";
    cout << nl;

    reverse(v.begin(), v.end());
    cout << "Reversed: ";
    for (auto x : v) cout << x << " ";
    cout << nl;
}

// =====================================================================
// 14. CHECKING IF ARRAY IS SORTED
// =====================================================================

void checkSorted() {
    cout << "\n=== 14. Check if Array is Sorted ===\n";
    vec<int> v1 = {1, 2, 3, 4, 5};
    vec<int> v2 = {1, 3, 2, 4, 5};

    cout << "v1 is sorted: " << (is_sorted(v1.begin(), v1.end()) ? "YES" : "NO") << nl;
    cout << "v2 is sorted: " << (is_sorted(v2.begin(), v2.end()) ? "YES" : "NO") << nl;
}

// =====================================================================
// 15. SORTING WITH FREQUENCY
// =====================================================================

void sortByFrequency() {
    cout << "\n=== 15. Sort by Frequency ===\n";
    vec<int> v = {4, 5, 6, 5, 4, 3, 4};

    map<int, int> freq;
    for (auto x : v) freq[x]++;

    // Sort by frequency (decreasing), then by value (increasing)
    sort(v.begin(), v.end(), [&](int a, int b) {
        if (freq[a] != freq[b]) return freq[a] > freq[b];
        return a < b;
    });

    cout << "Sorted by frequency: ";
    for (auto x : v) cout << x << " ";
    cout << nl;
}

// =====================================================================
// 16. COMPETITIVE PROGRAMMING PATTERNS
// =====================================================================

void cpPatterns() {
    cout << "\n=== 16. CP Patterns ===\n";

    // Pattern 1: Sort with custom index tracking
    vec<pair<int, int>> v = {{5, 0}, {2, 1}, {8, 2}, {1, 3}};
    sort(v.begin(), v.end());
    cout << "Sorted with indices: ";
    for (auto p : v) cout << "{" << p.fi << "," << p.se << "} ";
    cout << nl;

    // Pattern 2: Sort only specific range
    vec<int> arr = {5, 2, 8, 1, 9, 3, 7};
    sort(arr.begin() + 1, arr.begin() + 5);  // Sort index 1 to 4
    cout << "Sorted range [1-4]: ";
    for (auto x : arr) cout << x << " ";
    cout << nl;
}

// =====================================================================
// MAIN FUNCTION - Run All Examples
// =====================================================================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    cout << "\n";
    cout << "========================================\n";
    cout << "C++ STL SORTING - COMPLETE REFERENCE\n";
    cout << "========================================\n";

    sortArray();
    sortVector();
    sortWithLambda();
    sortWithFunction();
    sortingPairs();
    sortStudent();
    sortString();
    sortByAbsoluteValue();
    sort2DVector();
    partialSorting();
    nthElementExample();
    stableSortExample();
    sortIndices();
    sortMultipleCriteria();
    reverseExample();
    checkSorted();
    sortByFrequency();
    cpPatterns();

    cout << "\n========================================\n";
    cout << "ALL EXAMPLES COMPLETED!\n";
    cout << "========================================\n";

    return 0;
}

/*
=============================================================================
                            QUICK REFERENCE CHEATSHEET
=============================================================================

TIME COMPLEXITY:
- sort()           : O(n log n)  - IntroSort (QuickSort + HeapSort + InsertionSort)
- stable_sort()    : O(n log n)  - Maintains relative order
- partial_sort()   : O(n log k)  - Only sort first k elements
- nth_element()    : O(n)        - Find kth element (faster than partial_sort)
- is_sorted()      : O(n)        - Check if sorted
- reverse()        : O(n)        - Reverse array

SYNTAX PATTERNS:
1. Basic:          sort(arr, arr + n);
2. Vector:         sort(v.begin(), v.end());
3. Decreasing:     sort(v.begin(), v.end(), greater<int>());
4. Reverse itr:    sort(v.rbegin(), v.rend());
5. Lambda:         sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
6. Range:          sort(v.begin() + l, v.begin() + r);

COMPARATOR RULES:
- Return TRUE if 'a' should come BEFORE 'b'
- Increasing: return a < b;
- Decreasing: return a > b;
- Multiple criteria: use if-else chain

COMMON MISTAKES TO AVOID:
1. Forgetting arr + n (not arr + n - 1)
2. Using = in comparator (must be < or >)
3. Not handling equal cases in custom comparator
4. Modifying container while sorting

GM LEVEL TIPS:
1. Use stable_sort() when relative order matters
2. Use nth_element() for kth smallest (O(n) vs O(n log n))
3. Use partial_sort() when you need only top k elements
4. Sort indices instead of moving heavy objects
5. Use lambda with capture [&] to access external variables

=============================================================================
*/

