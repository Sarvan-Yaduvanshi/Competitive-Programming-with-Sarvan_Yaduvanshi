/*
Author: Sarvan Yaduvanshi
Created : 2026-11-01 23:32:20
*/

/*
 * ============================================================================
 *  432. All O`one Data Structure
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 432
 *  Difficulty : Hard
 *  Topics     : Hash Table, Linked List, Design, Doubly-Linked List
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Uber
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Design a data structure to store the strings' count with the ability to
 *  return the strings with minimum and maximum counts.
 *
 *  Implement the AllOne class:
 *
 *      - AllOne()
 *            Initializes the object of the data structure.
 *
 *      - inc(String key)
 *            Increments the count of the string key by 1. If key does not
 *            exist in the data structure, insert it with count 1.
 *
 *      - dec(String key)
 *            Decrements the count of the string key by 1. If the count of
 *            key is 0 after the decrement, remove it from the data
 *            structure. It is guaranteed that key exists in the data
 *            structure before the decrement.
 *
 *      - getMaxKey()
 *            Returns one of the keys with the maximal count. If no element
 *            exists, return an empty string "".
 *
 *      - getMinKey()
 *            Returns one of the keys with the minimum count. If no element
 *            exists, return an empty string "".
 *
 *  Note that each function must run in O(1) average time complexity.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      Input
 *      ["AllOne", "inc", "inc", "getMaxKey", "getMinKey", "inc",
 *       "getMaxKey", "getMinKey"]
 *      [[], ["hello"], ["hello"], [], [], ["leet"], [], []]
 *
 *      Output
 *      [null, null, null, "hello", "hello", null, "hello", "leet"]
 *
 *  Explanation:
 *      AllOne allOne = new AllOne();
 *      allOne.inc("hello");
 *      allOne.inc("hello");
 *      allOne.getMaxKey(); // return "hello"
 *      allOne.getMinKey(); // return "hello"
 *      allOne.inc("leet");
 *      allOne.getMaxKey(); // return "hello"
 *      allOne.getMinKey(); // return "leet"
 *
 * ----------------------------------------------------------------------------
 *  Picture (buckets of keys grouped by count, small count on the LEFT):
 *
 *      new              :  (empty)
 *      inc("hello")     :  [1: hello]
 *      inc("hello")     :  [2: hello]
 *      getMaxKey()      :  max bucket = 2 -> "hello"
 *      getMinKey()      :  min bucket = 2 -> "hello"
 *      inc("leet")      :  [1: leet] <-> [2: hello]
 *      getMaxKey()      :  max bucket = 2 -> "hello"
 *      getMinKey()      :  min bucket = 1 -> "leet"
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - 1 <= key.length <= 10
 *      - key consists of lowercase English letters.
 *      - It is guaranteed that for each call to dec, key is existing in the
 *        data structure.
 *      - At most 5 * 10^4 calls will be made to inc, dec, getMaxKey, and
 *        getMinKey.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <iomanip>
#include <random>
#include <chrono>

using namespace std;

class AllOne {
	// Doubly Linked List Node
	struct Bucket {
		int freq;                    // Frequency of the keys in this bucket
		unordered_set<string> keys;  // Set of keys with the same frequency
		Bucket* next;
		Bucket* prev;

		explicit Bucket(const int f) : freq(f), next(nullptr), prev(nullptr) {};
	};

	Bucket* head;   // Dummy Min Sentinel (left end)
	Bucket* tail;   // Dummy Max Sentinel (right end)
	unordered_map<string, Bucket*> keyBucket;  // Maps each key to its corresponding bucket (key -> Bucket*)

	// Helper 1: Insert `newBucket` immediately AFTER `prevBucket` in O(1)
	Bucket* insertAfterBucket(Bucket* prevBucket, const int freq) {
		Bucket* newBucket = new Bucket(freq);   // Create a new bucket with the given frequency
		Bucket* nextBucket = prevBucket->next;  // The bucket that comes after prevBucket

		// Forward link: prevBucket -> newBucket -> nextBucket
		prevBucket->next = newBucket;
		newBucket->next = nextBucket;

		// Backward link: prevBucket <- newBucket <- nextBucket
		newBucket->prev = prevBucket;
		nextBucket->prev = newBucket;

		return newBucket; // Return the newly created bucket
	}

	// Helper 2: Unlink and delete an empty `bucket` from the DLL in O(1)
	void removeBucket(const Bucket* bucket) {
		Bucket* prevBucket = bucket->prev;   // The bucket that comes before the current bucket
		Bucket* nextBucket = bucket->next;   // The bucket that comes after the current bucket

		// Unlink the current bucket from the DLL
		prevBucket->next = nextBucket;
		nextBucket->prev = prevBucket;

		// Delete the bucket to free memory
		delete bucket;
	}

public:
	// Constructor to initialize the AllOne data structure
	AllOne() {
		head = new Bucket(0);  // Dummy Min Sentinel (left end)
		tail = new Bucket(0);  // Dummy Max Sentinel (right end)

		head->next = tail;
		tail->prev = head;
	}

	// Destructor to clean up memory
	~AllOne() {
		const Bucket* curr = head;
		while (curr != nullptr){
			const Bucket* nextBucket = curr->next;
			delete curr;
			curr = nextBucket;
		}
	}

	// Function to increment the count of a key
	// Time Complexity: O(1) average
	// Space Complexity: O(1) average
	void inc(const string& key) {
		// Case 1: `key` is brand-new -> belongs in `freq = 1` right after `head`
		if (!keyBucket.contains(key)){
			// Check if the first bucket after head is for frequency 1
			Bucket* firstBucket = head->next;

			// If the first bucket is the tail or its frequency is not 1, we need to create a new bucket for frequency 1
			if (firstBucket == tail || firstBucket->freq != 1)
				firstBucket = insertAfterBucket(head, 1);

			// Insert the new key into the first bucket and update the keyBucket mapping
			firstBucket->keys.insert(key);
			keyBucket[key] = firstBucket;
			return;
		}

		// Case 2: `key` already exists -> promote from `currBucket` (f) to `nextBucket` (f + 1)
		// DO NOT create a new bucket if `nextBucket` already exists for frequency `f + 1`
		Bucket* currentBucket = keyBucket.at(key);
		int targetFreq = currentBucket->freq + 1;
		Bucket* nextBucket = currentBucket->next;

		// If the bucket right after `currBucket` isn't `freq + 1`, create it right after `currBucket`
		if (nextBucket == tail || nextBucket->freq != targetFreq)
			nextBucket = insertAfterBucket(currentBucket, targetFreq);

		// Move `key` into `nextBucket`
		nextBucket->keys.insert(key);
		keyBucket[key] = nextBucket;

		// Remove `key` from `currBucket`; if `currBucket` becomes empty, delete it!
		currentBucket->keys.erase(key);
		if (currentBucket->keys.empty())
			removeBucket(currentBucket);
	}

	// Function to decrement the count of a key
	// Time Complexity: O(1) average
	// Space Complexity: O(1) average
	void dec(string key) {
		// Probelem guarantees that `key` exists in the data structure before the decrement
		Bucket* currentBucket = keyBucket.at(key);
		int targetFreq = currentBucket->freq - 1;

		// Case 1: Count drops to 0 -> remove `key` from data structure completely
		if (targetFreq == 0)
			keyBucket.erase(key);

		// Case 2: Demote `key` to `prevBucket` (f - 1) immediately LEFT of `currBucket`
		else {
			Bucket* prevBucket = currentBucket->prev;
			if (prevBucket == head || prevBucket->freq != targetFreq)
				// Insert right after `currBucket->prev` (which places it right BEFORE `currBucket`!)
				prevBucket = insertAfterBucket(currentBucket->prev, targetFreq);

			// Move `key` into `prevBucket`
			prevBucket->keys.insert(key);
			keyBucket[key] = prevBucket;
		}

		// Remove `key` from `currBucket`; if `currBucket` becomes empty, delete it!
		currentBucket->keys.erase(key);
		if (currentBucket->keys.empty())
			removeBucket(currentBucket);
	}

	// Function to get the key with the maximum count
	// Time Complexity: O(1) average
	// Space Complexity: O(1) average
	string getMaxKey() {
		// If the list is empty (only head and tail), return an empty string
		if (tail->prev == head)
			return "";

		// Return any string sitting inside the rightmost bucket (`tail->prev`)
		return *(tail->prev->keys.begin());
	}

	string getMinKey() {
		// If the list is empty (only head and tail), return an empty string
		if (head->next == tail)
			return "";

		// Return any string sitting inside the leftmost bucket (`head->next`)
		return *(head->next->keys.begin());
	}
};

static void solve(){
	int operationCount;

	// Input format:
	// operationCount
	// inc key
	// dec key
	// getMaxKey
	// getMinKey
	if (!(cin >> operationCount))
		return;

	AllOne allOne;
	vector<string> results;

	for (int operation = 0; operation < operationCount; ++operation) {
		string command;
		cin >> command;

		if (command == "inc") {
			string key;
			cin >> key;
			allOne.inc(key);
			results.push_back("null");

			cout << "inc " << key << '\n';
			cout << "null\n";
		} else if (command == "dec") {
			string key;
			cin >> key;
			allOne.dec(key);
			results.push_back("null");

			cout << "dec " << key << '\n';
			cout << "null\n";
		} else if (command == "getMaxKey") {
			string result = allOne.getMaxKey();
			results.push_back('"' + result + '"');

			cout << "getMaxKey\n";
			cout << '"' << result << '"' << '\n';
		} else if (command == "getMinKey") {
			string result = allOne.getMinKey();
			results.push_back('"' + result + '"');

			cout << "getMinKey\n";
			cout << '"' << result << '"' << '\n';
		}
	}

	cout << "\nFinal LeetCode Output:\n[";
	for (int operation = 0; operation < static_cast<int>(results.size()); ++operation) {
		if (operation > 0)
			cout << ", ";
		cout << results[operation];
	}
	cout << "]\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}