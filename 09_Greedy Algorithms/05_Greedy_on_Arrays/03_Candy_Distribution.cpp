/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Candy Distribution — Two-Pass Greedy
 *  Level   : Hard
 * ============================================================================
 *
 *  PROBLEM (LC 135): N children in a line, each with a rating.
 *  Each child gets at least 1 candy.
 *  Children with higher rating than neighbor must get more candies.
 *  Minimize total candies.
 *
 *  TWO-PASS GREEDY:
 *  Pass 1 (Left→Right): If rating[i] > rating[i-1], candy[i] = candy[i-1]+1
 *  Pass 2 (Right→Left): If rating[i] > rating[i+1], candy[i] = max(candy[i], candy[i+1]+1)
 *
 *  WHY TWO PASSES?
 *  One pass can't satisfy both left and right neighbors simultaneously.
 *  First pass handles left neighbor constraint.
 *  Second pass handles right neighbor constraint (taking max to not violate left).
 *
 *  TIME: O(N), SPACE: O(N)
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int candy(vector<int>& ratings) {
    int n = ratings.size();
    vector<int> candies(n, 1); // Everyone gets at least 1

    // Pass 1: Left → Right (handle left neighbor)
    for (int i = 1; i < n; i++) {
        if (ratings[i] > ratings[i - 1])
            candies[i] = candies[i - 1] + 1;
    }

    // Pass 2: Right → Left (handle right neighbor)
    for (int i = n - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1])
            candies[i] = max(candies[i], candies[i + 1] + 1);
    }

    return accumulate(candies.begin(), candies.end(), 0);
}

int main() {
    vector<int> ratings1 = {1, 0, 2};
    cout << "Candies: " << candy(ratings1) << endl; // 5 (2+1+2)

    vector<int> ratings2 = {1, 2, 2};
    cout << "Candies: " << candy(ratings2) << endl; // 4 (1+2+1)

    vector<int> ratings3 = {1, 3, 4, 5, 2};
    cout << "Candies: " << candy(ratings3) << endl; // 11 (1+2+3+4+1)

    return 0;
}

