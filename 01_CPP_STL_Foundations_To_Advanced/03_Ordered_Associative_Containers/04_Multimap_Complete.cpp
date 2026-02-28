/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           04 — MULTIMAP COMPLETE GUIDE                                     ║
║           From Zero to Grandmaster — Multiple Values per Key               ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

  multimap<K,V> = map that allows DUPLICATE KEYS.
  Keys are sorted, each key can map to multiple values.
  No operator[] — use insert/emplace/find/equal_range.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "═══ MULTIMAP COMPLETE GUIDE ═══\n\n";

    // ── SECTION 1: BASIC OPERATIONS ──
    multimap<string, int> mm;
    mm.insert({"alice", 95});
    mm.insert({"bob", 87});
    mm.insert({"alice", 88});  // Duplicate key OK!
    mm.insert({"alice", 92});
    mm.insert({"bob", 91});
    mm.emplace("charlie", 75);

    cout << "Multimap contents (sorted by key):\n";
    for (auto& [name, score] : mm) {
        cout << "  " << name << " → " << score << "\n";
    }
    cout << "Size: " << mm.size() << "\n\n";

    // ── SECTION 2: find AND equal_range ──
    // find returns iterator to FIRST occurrence
    auto it = mm.find("alice");
    if (it != mm.end()) {
        cout << "find(\"alice\"): first = " << it->second << "\n";
    }

    // equal_range gives ALL entries for a key
    auto [lo, hi] = mm.equal_range("alice");
    cout << "All alice scores: ";
    for (auto it = lo; it != hi; ++it) {
        cout << it->second << " ";
    }
    cout << "\n";

    // count
    cout << "count(\"alice\") = " << mm.count("alice") << "\n";
    cout << "count(\"bob\") = " << mm.count("bob") << "\n\n";

    // ── SECTION 3: ERASE ──
    // erase by key removes ALL entries for that key
    mm.erase("alice");
    cout << "After erase(\"alice\"): ";
    for (auto& [k, v] : mm) cout << k << ":" << v << " ";
    cout << "\n\n";

    // ── SECTION 4: CP USE CASE — EVENT SCHEDULING ──
    /*
     PROBLEM: Given events with start times, process all events at each time.

     DRY RUN:
       Events: (time=1, "Start A"), (time=1, "Start B"), (time=3, "End A"),
               (time=3, "Start C"), (time=5, "End B"), (time=5, "End C")

       Time 1: Process "Start A", "Start B"
       Time 3: Process "End A", "Start C"
       Time 5: Process "End B", "End C"
    */
    cout << "═══ CP: EVENT SCHEDULING ═══\n\n";

    multimap<int, string> events;
    events.insert({1, "Start A"});
    events.insert({1, "Start B"});
    events.insert({3, "End A"});
    events.insert({3, "Start C"});
    events.insert({5, "End B"});
    events.insert({5, "End C"});

    cout << "Processing events by time:\n";
    auto cur = events.begin();
    while (cur != events.end()) {
        int time = cur->first;
        auto [from, to] = events.equal_range(time);
        cout << "  Time " << time << ": ";
        for (auto it = from; it != to; ++it) {
            cout << "[" << it->second << "] ";
        }
        cout << "\n";
        cur = to;  // Jump to next time group
    }
    cout << "\n";

    // ── SECTION 5: MULTIMAP vs MAP<K, VECTOR<V>> ──
    /*
     COMPARISON:
     ┌─────────────────────┬──────────────────┬──────────────────────┐
     │ Feature             │ multimap         │ map<K, vector<V>>    │
     ├─────────────────────┼──────────────────┼──────────────────────┤
     │ Duplicate keys      │ Built-in ✓       │ Manual (push_back)   │
     │ Iteration order     │ By key, stable   │ By key, then vector  │
     │ Erase single entry  │ erase(iterator)  │ Remove from vector   │
     │ Group by key        │ equal_range      │ Direct access m[k]   │
     │ Random access val   │ No               │ Yes (m[k][i])        │
     │ CP preference       │ Rare             │ More common ✓        │
     └─────────────────────┴──────────────────┴──────────────────────┘

     GM TIP: In CP, map<K, vector<V>> is usually preferred over multimap.
             It's simpler to work with and more flexible.
    */

    // Equivalent using map<K, vector<V>>
    cout << "═══ ALTERNATIVE: map<K, vector<V>> ═══\n\n";
    map<int, vector<string>> events2;
    events2[1].push_back("Start A");
    events2[1].push_back("Start B");
    events2[3].push_back("End A");
    events2[3].push_back("Start C");
    events2[5].push_back("End B");
    events2[5].push_back("End C");

    for (auto& [time, evts] : events2) {
        cout << "  Time " << time << ": ";
        for (auto& e : evts) cout << "[" << e << "] ";
        cout << "\n";
    }
    cout << "\n";

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. multimap allows duplicate keys, sorted by key\n";
    cout << "2. No operator[] — use insert/emplace\n";
    cout << "3. equal_range() to get all values for a key\n";
    cout << "4. In CP, map<K, vector<V>> is usually simpler\n";
    cout << "5. Good for event scheduling / sweep line problems\n";

    return 0;
}

