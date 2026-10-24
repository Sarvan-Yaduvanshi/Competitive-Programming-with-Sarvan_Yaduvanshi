/*
Author: Sarvan Yaduvanshi
Created : 2026-10-24 18:22:36
*/

/*
 * ============================================================================
 *  202. Happy Number
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 202
 *  Difficulty : Easy
 *  Topics     : Hash Table, Math, Two Pointers
 *  Companies  : Amazon, Google, Microsoft, Apple, Meta, Uber, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Write an algorithm to determine if a number n is happy.
 *
 *  A happy number is a number defined by the following process:
 *      - Starting with any positive integer, replace the number by the sum
 *        of the squares of its digits.
 *      - Repeat the process until the number equals 1 (where it will stay),
 *        or it loops endlessly in a cycle which does not include 1.
 *      - Those numbers for which this process ends in 1 are happy.
 *
 *  Return true if n is a happy number, and false if not.
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      19 -> 82 -> 68 -> 100 -> 1
 *
 *  Input  : n = 19
 *  Output : true
 *  Explanation:
 *      1^2 + 9^2       = 82
 *      8^2 + 2^2       = 68
 *      6^2 + 8^2       = 100
 *      1^2 + 0^2 + 0^2 = 1
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      2 -> 4 -> 16 -> 37 -> 58 -> 89 -> 145 -> 42 -> 20 -> 4 (cycle)
 *
 *  Input  : n = 2
 *  Output : false
 *  Explanation: The sequence never reaches 1. It falls into the endless
 *               cycle 4 -> 16 -> 37 -> 58 -> 89 -> 145 -> 42 -> 20 -> 4.
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - 1 <= n <= 2^31 - 1
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>

using namespace std;

/*
 * Approach: Floyd's Cycle Detection (Tortoise and Hare)
 *
 * The operation "replace a number by the sum of the squares of its digits"
 * creates a sequence of numbers:
 *
 *     n -> next(n) -> next(next(n)) -> ...
 *
 * There are only two possible outcomes:
 *   1. The sequence reaches 1. Since next(1) = 1, it remains at 1.
 *      Therefore, n is a happy number.
 *   2. The sequence enters a cycle that does not contain 1.
 *      Therefore, n is not a happy number.
 *
 * Instead of storing every number in a set, use two pointers:
 *   - slow moves one number at a time.
 *   - fast moves two numbers at a time.
 *
 * If a cycle exists, slow and fast must eventually meet inside that cycle.
 * After they meet, slow == 1 means the cycle is the happy cycle {1};
 * otherwise, the number belongs to a cycle that does not contain 1.
 *
 * Helper function:
 *   Extract each digit using x % 10, add digit * digit to the answer,
 *   and remove the last digit using x /= 10.
 *
 * Dry run 1: n = 19
 *   Number sequence:
 *       19 -> 82 -> 68 -> 100 -> 1
 *
 *   Floyd's pointers:
 *       Iteration       slow       fast
 *           1             82         68
 *           2             68          1
 *           3            100          1
 *           4              1          1   <- pointers meet at 1
 *
 *   Return slow == 1, so 19 is happy.
 *
 * Dry run 2: n = 2
 *   Number sequence:
 *       2 -> 4 -> 16 -> 37 -> 58 -> 89 -> 145 -> 42 -> 20 -> 4 ...
 *       The sequence repeats from 4, so it is an endless cycle.
 *
 *   Floyd's pointers:
 *       Iteration       slow       fast
 *           1              4         16
 *           2             16         58
 *           3             37        145
 *           4             58         20
 *           5             89         16
 *           6            145         58
 *           7             42        145
 *           8             20         20   <- pointers meet in the cycle
 *
 *   Return slow == 1, so 2 is not happy.
 *
 * Complexity:
 *   Let d be the number of digits in n.
 *   - Each sumOfSquares call takes O(d) time.
 *   - Floyd's algorithm uses O(1) extra space.
 *   - The number of iterations is bounded because digit-square sums quickly
 *     become small and then either reach 1 or enter a fixed cycle.
 *   - Time: O(k * d), where k is the number of pointer iterations
 *           (commonly written as O(d) for this problem's bounded state space).
 *   - Space: O(1).
 */
static bool isHappy(int n){
	// Calculate the sum of the squares of all digits in x.
	auto sumOfSquares = [&](int x) -> int{
		int sum = 0;
		while (x != 0){
			const int digit = x % 10;
			sum += digit * digit;
			x /= 10;
		}

		return sum;
	};

	// Start both pointers at n; the do-while loop advances them before checking.
	int slow = n;
	int fast = n;

	// Move slow one step and fast two steps until they meet.
	do{
		slow = sumOfSquares(slow);
		fast = sumOfSquares(sumOfSquares(fast));
	} while (slow != fast);

	// Meeting at 1 means the sequence reached the happy-number cycle.
	return slow == 1;
}

static void solve(){
	int n;
	cout << "Enter a number to check if it's happy: ";
	cin >> n;

	if (isHappy(n)){
        cout << n << " is a HAPPY number! 😊\n";
    } else{
        cout << n << " is NOT a happy number. 😢\n";
    }
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cout << fixed << setprecision(10);

	// Multi-test case support (commented out for this demo)
	// int TC = 1;
	// cin >> TC;
	// while (TC--) solve();

	solve();
	return 0;
}
