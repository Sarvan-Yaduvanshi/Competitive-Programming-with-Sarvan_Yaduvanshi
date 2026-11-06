/*
Author: Sarvan Yaduvanshi
Created : 2026-11-01 23:31:34
*/

/*
 * ============================================================================
 *  460. LFU Cache
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 460
 *  Difficulty : Hard
 *  Topics     : Hash Table, Linked List, Design, Doubly-Linked List
 *  Companies  : Amazon, Google, Microsoft, Meta, Apple, Bloomberg, Uber
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Design and implement a data structure for a Least Frequently Used (LFU)
 *  cache.
 *
 *  Implement the LFUCache class:
 *
 *      - LFUCache(int capacity)
 *            Initializes the object with the capacity of the data
 *            structure.
 *
 *      - int get(int key)
 *            Gets the value of the key if the key exists in the cache.
 *            Otherwise, returns -1.
 *
 *      - void put(int key, int value)
 *            Update the value of the key if present, or inserts the key if
 *            not already present. When the cache reaches its capacity, it
 *            should invalidate and remove the least frequently used key
 *            before inserting a new item. For this problem, when there is a
 *            tie (i.e., two or more keys with the same frequency), the
 *            least recently used key would be invalidated.
 *
 *  To determine the least frequently used key, a use counter is maintained
 *  for each key in the cache. The key with the smallest use counter is the
 *  least frequently used key.
 *
 *  When a key is first inserted into the cache, its use counter is set to 1
 *  (due to the put operation). The use counter for a key in the cache is
 *  incremented either a get or put operation is called on it.
 *
 *  The functions get and put must each run in O(1) average time complexity.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      Input
 *      ["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get",
 *       "get", "get"]
 *      [[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]
 *
 *      Output
 *      [null, null, null, 1, null, -1, 3, null, -1, 3, 4]
 *
 *  Explanation:
 *      // cnt(x) = the use counter for key x
 *      // cache=[] will show the last used order for tiebreakers
 *      // (leftmost element is most recent)
 *      LFUCache lfu = new LFUCache(2);
 *      lfu.put(1, 1);
 *          // cache=[1,_], cnt(1)=1
 *      lfu.put(2, 2);
 *          // cache=[2,1], cnt(2)=1, cnt(1)=1
 *      lfu.get(1);
 *          // return 1
 *          // cache=[1,2], cnt(2)=1, cnt(1)=2
 *      lfu.put(3, 3);
 *          // 2 is the LFU key because cnt(2)=1 is the smallest,
 *          // invalidate 2.
 *          // cache=[3,1], cnt(3)=1, cnt(1)=2
 *      lfu.get(2);
 *          // return -1 (not found)
 *      lfu.get(3);
 *          // return 3
 *          // cache=[3,1], cnt(3)=2, cnt(1)=2
 *      lfu.put(4, 4);
 *          // Both 1 and 3 have the same cnt, but 1 is LRU, invalidate 1.
 *          // cache=[4,3], cnt(4)=1, cnt(3)=2
 *      lfu.get(1);
 *          // return -1 (not found)
 *      lfu.get(3);
 *          // return 3
 *          // cache=[3,4], cnt(4)=1, cnt(3)=3
 *      lfu.get(4);
 *          // return 4
 *          // cache=[4,3], cnt(4)=2, cnt(3)=3
 *
 * ----------------------------------------------------------------------------
 *  Picture (capacity = 2, key:count, grouped by count, recent on the left):
 *
 *      put(1,1)  :  cnt1 = [1]
 *      put(2,2)  :  cnt1 = [2, 1]
 *      get(1)    :  cnt1 = [2]          cnt2 = [1]
 *      put(3,3)  :  full, evict LFU = 2 (cnt1, only one there)
 *                   cnt1 = [3]          cnt2 = [1]
 *      get(2)    :  -1, key 2 gone
 *      get(3)    :  cnt2 = [3, 1]       (3 moved to cnt2, most recent)
 *      put(4,4)  :  full, min count = 2, tie 3 and 1, LRU = 1, evict 1
 *                   cnt1 = [4]          cnt2 = [3]
 *      get(1)    :  -1, key 1 gone
 *      get(3)    :  cnt1 = [4]          cnt3 = [3]
 *      get(4)    :  cnt2 = [4]          cnt3 = [3]
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - 1 <= capacity <= 10^4
 *      - 0 <= key <= 10^5
 *      - 0 <= value <= 10^9
 *      - At most 2 * 10^5 calls will be made to get and put.
 * ============================================================================
 */

/*
 * ============================================================================
 *  REVISION APPROACH — HOW THIS CODE ACHIEVES O(1) get() AND put()
 * ============================================================================
 *
 *  LFU means:
 *      1. Evict the key with the smallest frequency.
 *      2. If frequencies tie, evict the least recently used key.
 *
 *  Why two hash maps?
 *
 *      keyNode:
 *          key -> Node*
 *          This finds any key in O(1), so get() and update-put() do not
 *          need to scan every cached key.
 *
 *      freqMap:
 *          frequency -> DLL*
 *          Every frequency owns one doubly linked list. The list stores all
 *          nodes having that frequency, with the most recently used node
 *          immediately after head and the least recently used node immediately
 *          before tail.
 *
 *  Why does every Node store key, value, frequency, next and prev?
 *
 *      - key/value: the cache data.
 *      - freq: tells us which frequency bucket currently owns the node.
 *      - next/prev: allow unlinking a node from a DLL in O(1).
 *      - key is also stored inside the node so eviction can erase the correct
 *        entry from keyNode before the node is deleted.
 *
 *  Why are dummy head and tail nodes used?
 *
 *      They remove special cases. Insertion always happens after head, and
 *      eviction always happens before tail. Therefore, inserting or removing
 *      the first/last real node uses the same four pointer updates.
 *
 *  Why is the node moved on both get() and existing-key put()?
 *
 *      LeetCode defines both operations as a use of the key. Therefore,
 *      promoteNode() removes the node from its old frequency list, increments
 *      its frequency, and inserts it at the MRU position of the next bucket.
 *
 *  Why does minFreq work?
 *
 *      minFreq always identifies the only bucket from which eviction can
 *      happen. If that bucket becomes empty after promotion, minFreq moves
 *      to the next frequency. A new node always starts at frequency 1, so a
 *      new insertion resets minFreq to 1.
 *
 *  Why does eviction remove from tail?
 *
 *      Nodes are inserted after head, so the node nearest tail is the oldest
 *      node in that frequency bucket. Removing it gives the required LRU
 *      tie-breaker while keeping the operation O(1).
 *
 *  Complexity:
 *      get()  : O(1) average
 *      put()  : O(1) average
 *      Space  : O(capacity) cached nodes, plus frequency buckets
 *
 *  ONE BEST DRY RUN (capacity = 2):
 *
 *      put(1,1)
 *          freqMap[1] = [1], minFreq = 1
 *
 *      put(2,2)
 *          freqMap[1] = [2,1], minFreq = 1
 *          2 is MRU and 1 is LRU because 2 was inserted later.
 *
 *      get(1) -> 1
 *          Remove 1 from freqMap[1], increase freq to 2, and insert it at
 *          the front of freqMap[2].
 *          freqMap[1] = [2], freqMap[2] = [1], minFreq = 1
 *
 *      put(3,3)
 *          Cache is full. minFreq is 1, so evict the tail of freqMap[1]:
 *          key 2 is removed. Then insert 3 at the front of freqMap[1].
 *          freqMap[1] = [3], freqMap[2] = [1], minFreq = 1
 *
 *      get(3) -> 3
 *          3 moves from frequency 1 to frequency 2:
 *          freqMap[2] = [3,1], and the old frequency-1 bucket becomes empty.
 *          Since minFreq was 1, promoteNode() increments minFreq to 2.
 *
 *      put(4,4)
 *          Both keys 3 and 1 have frequency 2. The list is [3,1], so 1 is
 *          nearest tail and is the LRU tie-breaker. Evict 1, insert 4 with
 *          frequency 1, and reset minFreq to 1.
 *          Final buckets: freqMap[1] = [4], freqMap[2] = [3]
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Implementation of LFU Cache using HashMap + Frequency-Bucketed Doubly Linked Lists.
class LFUCache {
private:
    // A) Node — Individual linked-list node(Actual node storing key, value, frequency)
    struct Node {
        int key;
        int val;
        int freq;
        Node* next;
        Node* prev;

        explicit Node(const int k, const int v) : key(k), val(v), freq(1), next(nullptr), prev(nullptr) {}
    };

    // B) DLL - Doubly Linked List container
    // Self-contained Sentinel Doubly Linked List for a single frequency bucket
    struct DLL {
        Node* head;
        Node* tail;
        size_t _size;

        // Constructor: Initialize the DLL with sentinel head and tail nodes and set size to 0
        DLL() {
            // Create two dummy sentinel nodes for the head and tail of the DLL
            head = new Node(-1, -1);
            tail = new Node(-1, -1);

            // Link the head and tail sentinels to each other
            head->next = tail;
            tail->prev = head;

            // Initialize the size of the DLL to 0
            _size = 0;
        }

        // Function 1: Insert `node` right after `head` (MRU position of this frequency bucket)
        void insertAfterHead(Node* node) {
            // Step 1: Before inserting new node save next node
            Node* nextNode = head->next;

            // Step 2: Link the new node between head and nextNode
            head->next = node;
            node->next = nextNode;

            // Step 3: Link back pointers
            node->prev = head;
            nextNode->prev = node;

            _size++; // Increase linked list size
        }

        // Function 2: Remove `node` from the DLL in O(1) time
        void removeNode(Node* node) {
            // Step 1: Store the next and previous nodes of the node to be removed
            Node* nextNode = node->next;
            Node* prevNode = node->prev;

            // Step 2: Connect each other
            prevNode->next = nextNode;
            nextNode->prev = prevNode;

            _size--; // Decrease linked list size
        }

        // Function 3: Remove the least recently used node (the one right before `tail`) from the DLL and return it
        Node* removeLRU() {
            // If the DLL is empty, return nullptr
            if (_size == 0)
                return nullptr;

            // Get the least recently used node (the one right before `tail`)
            Node* lru = tail->prev;
            removeNode(lru); // Unlink it from the DLL

            // Return the removed node because future delete keyNode map (free map memory) will be done in LFUCache class
            return lru;
        }
    };

    // Private Members of LFUCache
    int minFreq;                       // Track the minimum frequency of any key in the cache
    int cap;                           // Maximum capacity of the LFU Cache
    unordered_map<int, Node*> keyNode; // key  -> Node*
    unordered_map<int, DLL*> freqMap;  // freq -> DLL* bucket

    // Helper: Get the DLL bucket for a given frequency, creating it if it doesn't exist
    DLL* getBucket(int f) {
        // Case 1: If the frequency bucket does not exist, create a new DLL for it
        if (!freqMap.contains(f))
            freqMap[f] = new DLL();

        // Case 2: Return the existing or newly created DLL for the frequency
        return freqMap[f];
    }

    // Core Engine: Move `node` from bucket `freq` to bucket `freq + 1` in O(1)
    void promoteNode(Node* node) {
        // Step 1: Get the current frequency and its corresponding DLL bucket
        int oldFreq = node->freq;
        DLL* oldBucket = freqMap[oldFreq];

        // Step 2: Remove the node from its current frequency bucket
        oldBucket->removeNode(node);

        // Step 3: If the old frequency was the minimum frequency and its bucket is now empty, increment minFreq
        if (oldFreq == minFreq && oldBucket->_size == 0)
            minFreq++;

        // Step 4: Increment the node's frequency and insert it into the new frequency bucket
        node->freq++;
        getBucket(node->freq)->insertAfterHead(node); // Also insert as front(MRU)
    }

public:
    // Constructor: Initialize the LFU Cache with given capacity
    LFUCache(int capacity) {
        cap = capacity;
        minFreq = 0;
    }

    // Get the value associated with `key` if it exists, else return -1.
    int get(int key) {
        // Step 1: Find the node in the keyNode hash map
        auto it = keyNode.find(key);

        // Step 2: If not found, return -1
        if (it == keyNode.end())
            return -1;

        // Step 3: If found, promote the node to the next frequency bucket and return its value
        Node* node = it->second;
        promoteNode(node);
        return node->val;
    }

    // Put the key-value pair into the cache. If the key exists, update its value.
    void put(int key, int value) {
        // Invalid condition
        if (cap <= 0)
            return;

        // Get the node from the keyNode map if it exists
        auto it = keyNode.find(key);

        // Case 1: Key already exists -> update value and promote its frequency
        if (it != keyNode.end()) {
            Node* node = it->second;
            node->val = value;
            promoteNode(node);
            return;
        }

        // Case 2: Key is new, check if cache is full
        if (keyNode.size() == cap) {
            // Evict the least frequently used node from the minFreq bucket
            DLL* minBucket = freqMap[minFreq];
            Node* deleteNode = minBucket->removeLRU();
            keyNode.erase(deleteNode->key);
            delete deleteNode;
        }

        // Insert brand-new node with `freq = 1` and reset `minFreq = 1`
        Node* newNode = new Node(key, value);
        keyNode[key] = newNode;
        getBucket(1)->insertAfterHead(newNode);
        minFreq = 1;
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
    get 3
    put 4 4
    get 1
    get 3
    get 4

Output:
    [null,null,1,null,-1,3,null,-1,3,4]

After every operation, the driver also prints the operation and its result.
At the end, it prints the complete result list in LeetCode's format.
*/
static void solve(){
    int capacity;
    int operationCount;

    // If input is unavailable, stop without printing a misleading result.
    if (!(cin >> capacity >> operationCount))
        return;

    LFUCache cache(capacity);
    vector<string> results;

    for (int operation = 0; operation < operationCount; ++operation) {
        string command;
        cin >> command;

        if (command == "get") {
            int key;
            cin >> key;
            int result = cache.get(key);
            results.push_back(to_string(result));

            // Print this operation immediately for easy dry-run revision.
            cout << "get " << key << '\n';
            cout << result << '\n';
        } else if (command == "put") {
            int key;
            int value;
            cin >> key >> value;
            cache.put(key, value);
            results.push_back("null");

            // put has no return value in LeetCode, so print null.
            cout << "put " << key << ' ' << value << '\n';
            cout << "null\n";
        }
    }

    // Print the final complete result list after all operations finish.
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