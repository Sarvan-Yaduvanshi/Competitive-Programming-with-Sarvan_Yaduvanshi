/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           04 — FORWARD_LIST (Singly Linked List)                           ║
║           From Zero to Grandmaster                                         ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

  forward_list = singly linked list. Each node: [data | next]
  Minimal memory overhead, only forward iteration.

  Rarely used in CP — included for completeness.
  Key difference from list: no size(), no push_back, no reverse iteration.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "═══ FORWARD_LIST GUIDE ═══\n\n";

    // Creation
    forward_list<int> fl = {3, 1, 4, 1, 5};
    cout << "Initial: ";
    for (int x : fl) cout << x << " ";
    cout << "\n";

    // push_front (only front operations!)
    fl.push_front(0);
    cout << "push_front(0): ";
    for (int x : fl) cout << x << " ";
    cout << "\n";

    // insert_after (not insert!)
    auto it = fl.begin();
    advance(it, 2);
    fl.insert_after(it, 99);
    cout << "insert_after(pos2, 99): ";
    for (int x : fl) cout << x << " ";
    cout << "\n";

    // erase_after
    fl.erase_after(fl.begin());  // Erases element AFTER begin
    cout << "erase_after(begin): ";
    for (int x : fl) cout << x << " ";
    cout << "\n";

    // before_begin — special iterator before the first element
    fl.insert_after(fl.before_begin(), -1);
    cout << "insert_after(before_begin, -1): ";
    for (int x : fl) cout << x << " ";
    cout << "\n";

    // sort
    fl.sort();
    cout << "sort(): ";
    for (int x : fl) cout << x << " ";
    cout << "\n";

    // remove
    fl.remove(1);
    cout << "remove(1): ";
    for (int x : fl) cout << x << " ";
    cout << "\n";

    // unique (after sort)
    fl.unique();
    cout << "unique(): ";
    for (int x : fl) cout << x << " ";
    cout << "\n";

    // reverse
    fl.reverse();
    cout << "reverse(): ";
    for (int x : fl) cout << x << " ";
    cout << "\n\n";

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. forward_list = singly linked, forward-only\n";
    cout << "2. No size() — must use distance(fl.begin(), fl.end())\n";
    cout << "3. No push_back — only push_front\n";
    cout << "4. insert_after, erase_after (not insert, erase)\n";
    cout << "5. before_begin() for inserting at front\n";
    cout << "6. Rarely used in CP — prefer vector or list\n";

    return 0;
}

