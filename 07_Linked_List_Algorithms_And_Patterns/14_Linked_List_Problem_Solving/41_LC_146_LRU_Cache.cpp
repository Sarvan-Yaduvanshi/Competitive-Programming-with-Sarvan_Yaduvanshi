/*
Author: Sarvan Yaduvanshi
Created : 2026-11-01 00:06:20
*/

/*
 * ============================================================================
 *  146. LRU Cache
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 146
 *  Difficulty : Medium
 *  Topics     : Hash Table, Linked List, Design, Doubly-Linked List
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Uber
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Design a data structure that follows the constraints of a Least Recently
 *  Used (LRU) cache.
 *
 *  Implement the LRUCache class:
 *
 *      - LRUCache(int capacity)
 *            Initialize the LRU cache with positive size capacity.
 *
 *      - int get(int key)
 *            Return the value of the key if the key exists, otherwise
 *            return -1.
 *
 *      - void put(int key, int value)
 *            Update the value of the key if the key exists. Otherwise, add
 *            the key-value pair to the cache. If the number of keys exceeds
 *            the capacity from this operation, evict the least recently
 *            used key.
 *
 *  The functions get and put must each run in O(1) average time complexity.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      Input
 *      ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get",
 *       "get"]
 *      [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
 *
 *      Output
 *      [null, null, null, 1, null, -1, null, -1, 3, 4]
 *
 *  Explanation:
 *      LRUCache lRUCache = new LRUCache(2);
 *      lRUCache.put(1, 1); // cache is {1=1}
 *      lRUCache.put(2, 2); // cache is {1=1, 2=2}
 *      lRUCache.get(1);    // return 1
 *      lRUCache.put(3, 3); // LRU key was 2, evicts key 2,
 *                          // cache is {1=1, 3=3}
 *      lRUCache.get(2);    // returns -1 (not found)
 *      lRUCache.put(4, 4); // LRU key was 1, evicts key 1,
 *                          // cache is {4=4, 3=3}
 *      lRUCache.get(1);    // return -1 (not found)
 *      lRUCache.get(3);    // return 3
 *      lRUCache.get(4);    // return 4
 *
 * ----------------------------------------------------------------------------
 *  Picture (capacity = 2, order: MOST recent <-> LEAST recent):
 *
 *      put(1,1)  :  [1]
 *      put(2,2)  :  [2, 1]
 *      get(1)    :  [1, 2]          1 becomes most recent
 *      put(3,3)  :  [3, 1]          full, evict LRU = 2
 *      get(2)    :  [3, 1]          -1, key 2 gone
 *      put(4,4)  :  [4, 3]          full, evict LRU = 1
 *      get(1)    :  [4, 3]          -1, key 1 gone
 *      get(3)    :  [3, 4]          3 becomes most recent
 *      get(4)    :  [4, 3]          4 becomes most recent
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - 1 <= capacity <= 3000
 *      - 0 <= key <= 10^4
 *      - 0 <= value <= 10^5
 *      - At most 2 * 10^5 calls will be made to get and put.
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

/*
 * ============================================================================
 * DESIGN & FLATTEN PATTERN 1: 146. LRU Cache (Strict O(1) get & put)
 * ============================================================================
 *
 * - Core Architecture (Hash Map + Sentinel Doubly Linked List):
 *   1. `unordered_map<int, Node*> mp` : Maps `key -> Node*` in O(1) time.
 *   2. Doubly Linked List with 2 permanent dummy sentinels (`head` & `tail`):
 *        [head (MRU Sentinel)] <---> [Most Recent] ... [Least Recent] <---> [tail (LRU Sentinel)]
 *      - Right after `head` (`head->next`) = Most Recently Used (MRU) node.
 *      - Right before `tail` (`tail->prev`) = Least Recently Used (LRU) node.
 *
 * - Why Node MUST Store Both `key` and `val`:
 *   When the cache is full, we evict the LRU node sitting at `tail->prev`.
 *   To erase that entry from the Hash Map in O(1) (`mp.erase(lru->key)`), the
 *   DLL node itself MUST store `int key` so we know which key to erase!
 *
 * - The Two Zero-Branch O(1) DLL Primitives:
 *     1. `removeNode(node)` (Unlink `node` from its current spot):
 *          `node->prev->next = node->next;`
 *          `node->next->prev = node->prev;`
 *     2. `insertAfterHead(node)` (Place `node` at the MRU front right after `head`):
 *          `node->next = head->next;`
 *          `node->prev = head;`
 *          `head->next->prev = node;`
 *          `head->next = node;`
 *
 * - Quick Dry Run: capacity = 2
 *     Init        : [head] <-> [tail], mp = {}
 *     put(1, 10)  : [head] <-> [1:10] <-> [tail], mp = {1}
 *     put(2, 20)  : [head] <-> [2:20] <-> [1:10] <-> [tail], mp = {1, 2}
 *     get(1)      : Found [1:10]! `removeNode([1:10])` + `insertAfterHead([1:10])`.
 *                   List: [head] <-> [1:10] <-> [2:20] <-> [tail]. Returns 10.
 *     put(3, 30)  : Size == 2 (Full!). LRU victim is `tail->prev` ([2:20]).
 *                   `removeNode([2:20])`, `mp.erase(2)`, reuse/insert [3:30] at front:
 *                   List: [head] <-> [3:30] <-> [1:10] <-> [tail], mp = {1, 3}.
 *
 * - Complexity:
 *   Time  : O(1) for both `get` and `put` (O(1) hash lookup + 4 pointer rewires).
 *   Space : O(capacity) — Stores at most `capacity` nodes in the DLL and Hash Map.
 * ============================================================================
 */
class LRUCache{
private:
	// Doubly Linked List Node Structure
	struct Node{
		int key;
		int val;
		Node* next;
		Node* prev;

		explicit Node(const int k, const int v) : key(k), val(v), next(nullptr), prev(nullptr) {}
	};

	// Sentinel Nodes for the Doubly Linked List
	Node* head;
	Node* tail;
	int cap;
	unordered_map<int, Node*> map;

	// Helper 1: Unlink `node` from the Doubly Linked List in O(1)
	void removeNode(Node* node){
		Node* nextNode = node->next; // before unlinking, store the next node
		Node* prevNode = node->prev; // before unlinking, store the previous node

		prevNode->next = nextNode; // connect previous node to next node
		nextNode->prev = prevNode; // connect next node to previous node
	}

	// Helper 2: Insert `node` right after `head` (MRU position) in O(1)
	void insertAfterHead(Node* node){
		// Store the current first node (which is right after head) to link it later
		Node* nextNode = head->next;

		head->next = node; // link head to the new node
		node->next = nextNode; // link new node to the old first node

		node->prev = head; // link new node back to head
		nextNode->prev = node; // link old first node back to the new node
	}

	// Helper 3: Move an existing `node` to the MRU front in O(1)
	void moveToHead(Node* node){
		removeNode(node);
		insertAfterHead(node);
	}

public:
	// Constructor: Initialize the LRU Cache with given capacity
	explicit LRUCache(int capacity){
		cap = capacity;
		// initialize the head & tail with key = -1, val = -1 as sentinel nodes
        head = new Node(-1, -1); // MRU Sentinel (Most Recently Used)
        tail = new Node(-1, -1); // LRU Sentinel (Least Recently Used)

        head->next = tail; // connect head to tail
        tail->prev = head; // connect tail back to head
	}

	// Destructor: Clean up all nodes to prevent memory leaks
	~LRUCache() {
		Node* current = head;
		while (current != nullptr) {
			Node* next = current->next;
			delete current;
			current = next;
		}
	}

	// Get the value associated with `key` if it exists, else return -1.
	int get(int key) {
		// Step 1: Find the node in the hash map
		auto it = map.find(key);

		// Step 2: If not found, return -1
		if (it == map.end())
			return -1;

		// Step 3: If found, move the node to the MRU front and return its value
		Node* node = it->second; // Retrieve the node pointer from the hash map
		moveToHead(node); // move to the front (MRU position)
		return node->val; // return the value associated with the key
	}

	// Put the key-value pair into the cache. If the key exists, update its value.
	void put(int key, int value) {
		// If capacity is zero or negative, we cannot store anything.
		if (cap <= 0)
			return;

		// Find the key in the hash map
		auto it = map.find(key);

		// Case 1: Key already exists -> update value and move to MRU front
		if (it != map.end()){
			Node* node = it->second; // get the existing node
			node->val = value; // overwrite the value
			moveToHead(node); // move to the front (MRU position)
			return;
		}

		// Case 2: Key is new, check if cache is at full capacity
		if (static_cast<int>(map.size()) == cap){
			Node* lastNode = tail->prev; // Node right before `tail` is the LRU
			removeNode(lastNode);        // Unlink the LRU node from the DLL
			map.erase(lastNode->key);    // Erase using stored `key`!
			delete lastNode;             // Free heap memory
		}

		// Case 3: Insert the new key-value pair as a node at the MRU front
		Node* newNode = new Node(key, value); // Create a new node for the key-value pair
		insertAfterHead(newNode);                 // Insert it right after `head` (MRU position)
		map[key] = newNode;                       // Add the new node to the hash map for O(1) access
	}
};


/*
Input format:
    capacity
    number_of_operations
    operation [key] [value]

Use "get key" and "put key value", one operation per line.

Example:
    2
    10
    put 1 1
    put 2 2
    get 1
    put 3 3
    get 2
    put 4 4
    get 1
    get 3
    get 4
    get 5

Output:
    [null,null,1,null,-1,null,-1,3,4,-1]

The output uses the same convention as LeetCode: put returns null and get
returns the retrieved value.
*/
static void solve() {
	int capacity;
	int operationCount;
	if (!(cin >> capacity >> operationCount))
		return;

	LRUCache cache(capacity);
	cout << '[';

	for (int operation = 0; operation < operationCount; ++operation) {
		string command;
		cin >> command;

		if (operation > 0)
			cout << ',';

		if (command == "get") {
			int key;
			cin >> key;
			cout << cache.get(key);
		} else if (command == "put") {
			int key;
			int value;
			cin >> key >> value;
			cache.put(key, value);
			cout << "null";
		}
	}

	cout << "]\n";
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}
