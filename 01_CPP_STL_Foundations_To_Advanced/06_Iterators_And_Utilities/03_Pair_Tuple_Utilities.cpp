/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           03 — PAIR, TUPLE, AND UTILITY FUNCTIONS                          ║
║           From Zero to Grandmaster                                         ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ── PAIR ──
    cout << "═══ PAIR ═══\n\n";
    pair<int, string> p1 = {42, "hello"};
    auto p2 = make_pair(3.14, true);

    cout << "p1: (" << p1.first << ", " << p1.second << ")\n";
    cout << "p2: (" << p2.first << ", " << p2.second << ")\n";

    // Pair comparison (lexicographic — first, then second)
    pair<int, int> a = {1, 5}, b = {1, 3}, c = {2, 1};
    cout << "(1,5) < (1,3): " << (a < b) << "\n";  // 0 (5 > 3)
    cout << "(1,5) < (2,1): " << (a < c) << "\n";  // 1 (1 < 2)

    // Sort vector of pairs
    vector<pair<int, int>> vp = {{3, 1}, {1, 4}, {2, 2}, {1, 3}};
    sort(vp.begin(), vp.end());
    cout << "Sorted pairs: ";
    for (auto& [x, y] : vp) cout << "(" << x << "," << y << ") ";
    cout << "\n\n";

    // ── TUPLE ──
    cout << "═══ TUPLE ═══\n\n";
    tuple<int, string, double> t1 = {1, "CP", 3.14};
    auto t2 = make_tuple(42, "GM", 2.71);

    // Access
    cout << "get<0>: " << get<0>(t1) << "\n";
    cout << "get<1>: " << get<1>(t1) << "\n";
    cout << "get<2>: " << get<2>(t1) << "\n";

    // Structured binding
    auto [id, name, score] = t1;
    cout << "Binding: " << id << ", " << name << ", " << score << "\n";

    // tie for unpacking
    int x; string s; double d;
    tie(x, s, d) = t2;
    cout << "tie: " << x << ", " << s << ", " << d << "\n";

    // tie with ignore
    tie(x, ignore, d) = t1;
    cout << "tie(ignore): " << x << ", " << d << "\n";

    // Tuple comparison (lexicographic)
    auto ta = make_tuple(1, 2, 3);
    auto tb = make_tuple(1, 2, 4);
    cout << "(1,2,3) < (1,2,4): " << (ta < tb) << "\n\n";

    // GM TRICK: Use tuple for multi-key sorting
    cout << "═══ TUPLE FOR MULTI-KEY SORT ═══\n\n";
    struct Student { string name; int grade; double gpa; };
    vector<Student> students = {
        {"Alice", 3, 3.8}, {"Bob", 2, 3.9}, {"Charlie", 3, 3.5}, {"David", 2, 3.7}
    };
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        // Sort by grade ASC, then GPA DESC, then name ASC
        return tie(a.grade, b.gpa, a.name) < tie(b.grade, a.gpa, b.name);
    });
    cout << "Sorted students (grade asc, gpa desc, name asc):\n";
    for (auto& st : students) {
        cout << "  " << st.name << " grade=" << st.grade << " gpa=" << st.gpa << "\n";
    }
    cout << "\n";

    // ── UTILITY FUNCTIONS ──
    cout << "═══ UTILITY FUNCTIONS ═══\n\n";

    // swap
    int p = 5, q = 10;
    swap(p, q);
    cout << "swap(5,10): p=" << p << ", q=" << q << "\n";

    // min, max, minmax
    cout << "min(3,7) = " << min(3, 7) << "\n";
    cout << "max(3,7) = " << max(3, 7) << "\n";
    auto [lo, hi] = minmax({5, 2, 8, 1, 9});
    cout << "minmax({5,2,8,1,9}) = (" << lo << ", " << hi << ")\n";

    // clamp (C++17)
    cout << "clamp(15, 0, 10) = " << clamp(15, 0, 10) << "\n";
    cout << "clamp(-5, 0, 10) = " << clamp(-5, 0, 10) << "\n";
    cout << "clamp(5, 0, 10) = " << clamp(5, 0, 10) << "\n";

    // exchange (C++14)
    int old = exchange(p, 100);  // p becomes 100, old = previous p
    cout << "exchange: old=" << old << ", new p=" << p << "\n\n";

    // ── GM TRICK: pair for sorting by value ──
    cout << "═══ PAIR TRICK: SORT BY VALUE ═══\n\n";
    // Sort map entries by value using vector of pairs
    map<string, int> freq = {{"apple", 3}, {"banana", 1}, {"cherry", 5}};
    vector<pair<int, string>> byValue;
    for (auto& [k, v] : freq) byValue.push_back({v, k});
    sort(byValue.rbegin(), byValue.rend());  // Descending by value
    for (auto& [cnt, word] : byValue) {
        cout << "  " << word << ": " << cnt << "\n";
    }
    cout << "\n";

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. pair: two values, lexicographic comparison\n";
    cout << "2. tuple: N values, get<i>(), tie(), structured binding\n";
    cout << "3. tie() for multi-key comparison in sort\n";
    cout << "4. swap, min, max, minmax, clamp — know them all\n";
    cout << "5. Pair trick: swap key-value for sorting by value\n";

    return 0;
}

