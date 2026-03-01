/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Multiset Greedy — Ordered Set for Greedy Assignment
 *  Level   : Advanced
 * ============================================================================
 *
 *  PATTERN: Use std::multiset (balanced BST) to:
 *  - Find the best match for a query in O(log N)
 *  - Erase used elements in O(log N)
 *  - Maintain sorted order dynamically
 *
 *  CLASSIC PROBLEMS:
 *  - CSES Movie Festival II (assign K members to movies)
 *  - CSES Room Allocation (assign rooms to guests)
 *  - Greedy interval assignment
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

// ============================================================================
// CSES 1632: Movie Festival II — K members, maximize total movies watched
// ============================================================================
int movieFestivalII(int n, int k, vector<pair<int,int>>& movies) {
    // Sort by end time
    sort(movies.begin(), movies.end(), [](auto& a, auto& b) {
        return a.second < b.second;
    });

    // Multiset stores the "last end time" of each member
    multiset<int> members;
    for (int i = 0; i < k; i++) members.insert(0); // All members free from time 0

    int count = 0;
    for (auto& [start, end] : movies) {
        // Find a member whose last movie ended at or before 'start'
        auto it = members.upper_bound(start);
        if (it != members.begin()) {
            --it;
            members.erase(it);
            members.insert(end); // This member is now busy until 'end'
            count++;
        }
    }
    return count;
}

// ============================================================================
// CSES 1164: Room Allocation — Assign minimum rooms to N guests
// ============================================================================
vector<int> roomAllocation(int n, vector<pair<pair<int,int>, int>>& guests) {
    // guests[i] = {{arrival, departure}, original_index}
    sort(guests.begin(), guests.end());

    // Min-heap of {departure_time, room_number}
    // Or use multiset<pair<int,int>> for {end_time, room_id}
    multiset<pair<int,int>> freeRooms; // {end_time, room_id}
    vector<int> assignment(n);
    int nextRoom = 1;

    for (auto& [interval, idx] : guests) {
        auto [arrival, departure] = interval;

        // Find a room that's free (end_time < arrival)
        auto it = freeRooms.begin();
        if (it != freeRooms.end() && it->first < arrival) {
            assignment[idx] = it->second;
            freeRooms.erase(it);
        } else {
            assignment[idx] = nextRoom++;
        }
        freeRooms.insert({departure, assignment[idx]});
    }

    return assignment;
}

int main() {
    // Movie Festival II
    vector<pair<int,int>> movies = {{1,5}, {8,10}, {3,6}, {2,4}, {6,9}};
    cout << "Max movies (k=2): " << movieFestivalII(5, 2, movies) << endl;

    return 0;
}

