/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           03 — MODIFICATION ALGORITHMS                                     ║
║           From Zero to Grandmaster                                         ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ── reverse ──
    cout << "═══ reverse() ═══\n";
    vector<int> v = {1, 2, 3, 4, 5};
    reverse(v.begin(), v.end());
    cout << "Reversed: "; for (int x : v) cout << x << " "; cout << "\n";
    // Reverse substring
    string s = "Hello World";
    reverse(s.begin() + 6, s.end());
    cout << "Partial reverse: " << s << "\n\n";

    // ── rotate ──
    cout << "═══ rotate() ═══\n";
    /*
     rotate(first, new_first, last)
     Rotates so that new_first becomes the new beginning

     DRY RUN: {1,2,3,4,5}, rotate to position 2
       → {3,4,5,1,2}
    */
    v = {1, 2, 3, 4, 5};
    rotate(v.begin(), v.begin() + 2, v.end());
    cout << "Left rotate by 2: "; for (int x : v) cout << x << " "; cout << "\n";

    v = {1, 2, 3, 4, 5};
    rotate(v.begin(), v.end() - 2, v.end());
    cout << "Right rotate by 2: "; for (int x : v) cout << x << " "; cout << "\n\n";

    // ── fill & fill_n ──
    cout << "═══ fill() ═══\n";
    vector<int> filled(10);
    fill(filled.begin(), filled.end(), 42);
    cout << "fill(42): "; for (int x : filled) cout << x << " "; cout << "\n";
    fill_n(filled.begin(), 5, 0);
    cout << "fill_n(0,5): "; for (int x : filled) cout << x << " "; cout << "\n\n";

    // ── replace ──
    cout << "═══ replace() ═══\n";
    v = {1, 2, 3, 2, 4, 2, 5};
    replace(v.begin(), v.end(), 2, 99);
    cout << "replace 2→99: "; for (int x : v) cout << x << " "; cout << "\n";

    v = {1, 2, 3, 4, 5, 6, 7, 8};
    replace_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; }, 0);
    cout << "replace even→0: "; for (int x : v) cout << x << " "; cout << "\n\n";

    // ── remove + erase-remove idiom ──
    cout << "═══ erase-remove idiom ═══\n";
    v = {1, 2, 3, 2, 4, 2, 5};
    v.erase(remove(v.begin(), v.end(), 2), v.end());
    cout << "Remove all 2s: "; for (int x : v) cout << x << " "; cout << "\n";

    v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    v.erase(remove_if(v.begin(), v.end(), [](int x) { return x > 5; }), v.end());
    cout << "Remove >5: "; for (int x : v) cout << x << " "; cout << "\n\n";

    // ── unique (remove consecutive duplicates — needs sorted!) ──
    cout << "═══ unique() ═══\n";
    v = {1, 1, 2, 2, 3, 3, 3, 4, 4, 5};
    v.erase(unique(v.begin(), v.end()), v.end());
    cout << "unique: "; for (int x : v) cout << x << " "; cout << "\n";

    // CLASSIC: sort + unique to get distinct elements
    v = {5, 3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    cout << "sort+unique: "; for (int x : v) cout << x << " "; cout << "\n\n";

    // ── shuffle ──
    cout << "═══ shuffle() ═══\n";
    v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    shuffle(v.begin(), v.end(), rng);
    cout << "Shuffled: "; for (int x : v) cout << x << " "; cout << "\n\n";

    // ── next_permutation / prev_permutation ──
    cout << "═══ next_permutation() ═══\n";
    v = {1, 2, 3};
    cout << "All permutations of {1,2,3}:\n";
    do {
        cout << "  "; for (int x : v) cout << x << " "; cout << "\n";
    } while (next_permutation(v.begin(), v.end()));
    cout << "\n";

    // ── transform ──
    cout << "═══ transform() ═══\n";
    v = {1, 2, 3, 4, 5};
    vector<int> result(v.size());
    transform(v.begin(), v.end(), result.begin(), [](int x) { return x * x; });
    cout << "Squared: "; for (int x : result) cout << x << " "; cout << "\n\n";

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. reverse, rotate — in-place O(N)\n";
    cout << "2. erase-remove idiom for removing elements from vector\n";
    cout << "3. sort + unique for distinct elements\n";
    cout << "4. next_permutation for generating all permutations\n";
    cout << "5. shuffle with mt19937 for random ordering\n";

    return 0;
}

