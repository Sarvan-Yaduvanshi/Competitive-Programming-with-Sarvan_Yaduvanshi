/*
Author: Sarvan Yaduvanshi
Created : 2026-11-01 23:29:43
*/

/*
 * ============================================================================
 *  1472. Design Browser History
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 1472
 *  Difficulty : Medium
 *  Topics     : Array, Linked List, Stack, Design, Doubly-Linked List,
 *               Data Stream
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Uber
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  You have a browser of one tab where you start on the homepage and you can
 *  visit another url, get back in the history number of steps or move
 *  forward in the history number of steps.
 *
 *  Implement the BrowserHistory class:
 *
 *      - BrowserHistory(string homepage)
 *            Initializes the object with the homepage of the browser.
 *
 *      - void visit(string url)
 *            Visits url from the current page. It clears up all the forward
 *            history.
 *
 *      - string back(int steps)
 *            Move steps back in history. If you can only return x steps in
 *            the history and steps > x, you will return only x steps.
 *            Return the current url after moving back in history at most
 *            steps.
 *
 *      - string forward(int steps)
 *            Move steps forward in history. If you can only forward x steps
 *            in the history and steps > x, you will forward only x steps.
 *            Return the current url after forwarding in history at most
 *            steps.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      Input
 *      ["BrowserHistory","visit","visit","visit","back","back","forward",
 *       "visit","forward","back","back"]
 *      [["leetcode.com"],["google.com"],["facebook.com"],["youtube.com"],
 *       [1],[1],[1],["linkedin.com"],[2],[2],[7]]
 *
 *      Output
 *      [null,null,null,null,"facebook.com","google.com","facebook.com",
 *       null,"linkedin.com","google.com","leetcode.com"]
 *
 *  Explanation:
 *      BrowserHistory browserHistory = new BrowserHistory("leetcode.com");
 *      browserHistory.visit("google.com");
 *          // You are in "leetcode.com". Visit "google.com"
 *      browserHistory.visit("facebook.com");
 *          // You are in "google.com". Visit "facebook.com"
 *      browserHistory.visit("youtube.com");
 *          // You are in "facebook.com". Visit "youtube.com"
 *      browserHistory.back(1);
 *          // You are in "youtube.com", move back to "facebook.com"
 *          // return "facebook.com"
 *      browserHistory.back(1);
 *          // You are in "facebook.com", move back to "google.com"
 *          // return "google.com"
 *      browserHistory.forward(1);
 *          // You are in "google.com", move forward to "facebook.com"
 *          // return "facebook.com"
 *      browserHistory.visit("linkedin.com");
 *          // You are in "facebook.com". Visit "linkedin.com"
 *      browserHistory.forward(2);
 *          // You are in "linkedin.com", you cannot move forward any steps.
 *      browserHistory.back(2);
 *          // You are in "linkedin.com", move back two steps to
 *          // "facebook.com" then to "google.com". return "google.com"
 *      browserHistory.back(7);
 *          // You are in "google.com", you can move back only one step to
 *          // "leetcode.com". return "leetcode.com"
 *
 * ----------------------------------------------------------------------------
 *  Picture (history list, [ ] = current page):
 *
 *      start        :  [leetcode]
 *      visit google :  leetcode <-> [google]
 *      visit fb     :  leetcode <-> google <-> [facebook]
 *      visit yt     :  leetcode <-> google <-> facebook <-> [youtube]
 *      back(1)      :  leetcode <-> google <-> [facebook] <-> youtube
 *      back(1)      :  leetcode <-> [google] <-> facebook <-> youtube
 *      forward(1)   :  leetcode <-> google <-> [facebook] <-> youtube
 *      visit linkedin: leetcode <-> google <-> facebook <-> [linkedin]
 *                      (youtube = forward history, cleared)
 *      forward(2)   :  stays on [linkedin]  (nothing ahead)
 *      back(2)      :  leetcode <-> [google] <-> facebook <-> linkedin
 *      back(7)      :  [leetcode] <-> google <-> facebook <-> linkedin
 *                      (only 1 step possible)
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - 1 <= homepage.length <= 20
 *      - 1 <= url.length <= 20
 *      - 1 <= steps <= 100
 *      - homepage and url consist of '.' or lower case English letters.
 *      - At most 5000 calls will be made to visit, back, and forward.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <random>
#include <chrono>

using namespace std;

class BrowserHistory{
private:
	// Doubly Linked List Node Structure
	struct Node {
		string url;
		Node* next;
		Node* prev;

		explicit Node(const string& website) : url(website), next(nullptr), prev(nullptr) {}
	};

	Node* curr;

public:
	// Release every node owned by this browser history.
	~BrowserHistory() {
		Node* page = curr;
		while (page != nullptr && page->prev != nullptr) {
			page = page->prev;
		}

		while (page != nullptr) {
			Node* nextPage = page->next;
			delete page;
			page = nextPage;
		}
	}

	BrowserHistory(const BrowserHistory&) = delete;
	BrowserHistory& operator=(const BrowserHistory&) = delete;

	/*
 * ============================================================================
 * DESIGN & FLATTEN PATTERN 3A: 1472. Design Browser History (DLL Cursor Engine)
 * ============================================================================
 *
 * - Core Architecture (Doubly Linked List with Persistent `curr` Pointer):
 *   Maintain a single pointer `curr` pointing to the currently active webpage node:
 *     [homepage] <---> [page1] <---> [curr] <---> [forwardPage1]
 *
 *   1. `visit(url)` :
 *      - Optional C++ Memory Cleanup: Delete any abandoned forward nodes starting
 *        from `curr->next` so they don't leak on the heap.
 *      - Create `newNode = new Node(url)`, wire `curr->next = newNode` and
 *        `newNode->prev = curr`, then advance `curr = newNode`.
 *   2. `back(steps)` :
 *      - Loop `while (steps > 0 && curr->prev != nullptr)` -> `curr = curr->prev; steps--;`
 *   3. `forward(steps)` :
 *      - Loop `while (steps > 0 && curr->next != nullptr)` -> `curr = curr->next; steps--;`
 *
 * - Quick Dry Run:
 *     Init("leetcode.com") : [leetcode] (curr = leetcode)
 *     visit("google.com")  : [leetcode] <-> [google] (curr = google)
 *     visit("fb.com")      : [leetcode] <-> [google] <-> [fb] (curr = fb)
 *     back(1)              : `curr` moves to [google]. Returns "google.com".
 *     visit("youtube.com") : Clears [fb]! Links [google] <-> [youtube] (curr = youtube).
 *     forward(1)           : `curr->next` is nullptr -> stays at [youtube].
 *
 * - Complexity:
 *   Time  : O(1) for `visit` (amortized across created nodes), O(min(N, steps)) for `back`/`forward`.
 *   Space : O(N) — Stores active history nodes in the Doubly Linked List.
 * ============================================================================
 */
	// Constructor initializes the browser history with the homepage
	explicit BrowserHistory(string homepage) {
		// Initialize the current node with the homepage
        curr = new Node(homepage);
	}

	// Function to visit a new URL, clearing forward history
	void visit(string url) {
		// Step 1: Free any old forward history nodes to prevent memory leaks
		Node* temp = curr->next;
		while (temp != nullptr){
			Node* nextTemp = temp->next;
			delete temp;
			temp = nextTemp;
		}

		// Step 2: Create new page node, link it to the current node, and move the cursor
		Node* newNode = new Node(url);
		curr->next = newNode; // Link forward to the new node
		newNode->prev = curr; // Link back to the current node
		curr = newNode; // Move the current pointer to the new node
	}

	// Function to move back in history by a given number of steps
	string back(int steps) {
		// Walk backward until `steps` runs out OR we hit the homepage (`curr->prev == nullptr`)
		while (steps > 0 && curr->prev != nullptr){
			curr = curr->prev;
			steps--;
		}

		// Return the URL of the current page after moving back
		return curr->url;
	}

	// Function to move forward in history by a given number of steps
	string forward(int steps) {
		// Walk forward until `steps` runs out OR we hit the most recent page (`curr->next == nullptr`)
        while (steps > 0 && curr->next != nullptr){
	        curr = curr->next;
        	steps--;
        }

		// Return the URL of the current page after moving forward
		return curr->url;
	}

	// Print the complete history and mark the page currently being viewed.
	void printHistory() const {
		Node* firstPage = curr;
		while (firstPage->prev != nullptr) {
			firstPage = firstPage->prev;
		}

		cout << "History: ";
		for (Node* page = firstPage; page != nullptr; page = page->next) {
			if (page != firstPage) {
				cout << " <-> ";
			}

			if (page == curr) {
				cout << '[' << page->url << ']';
			} else {
				cout << page->url;
			}
		}
		cout << '\n';
	}

	// Print only the page currently being viewed.
	void printCurrentPage() const {
		cout << "Current page: " << curr->url << '\n';
	}
};


static void solve() {
	// The driver below imitates LeetCode's operation list. No input is required.
	// void methods produce "null", just like LeetCode's output.
	cout << "Input:\n";
	cout << "[\"BrowserHistory\",\"visit\",\"visit\",\"visit\",\"back\","
	        "\"back\",\"forward\",\"visit\",\"forward\",\"back\",\"back\"]\n";
	cout << "[[\"leetcode.com\"],[\"google.com\"],[\"facebook.com\"],[\"youtube.com\"],"
	        "[1],[1],[1],[\"linkedin.com\"],[2],[2],[7]]\n\n";

	BrowserHistory browserHistory("leetcode.com");
	vector<string> output{"null"};

	browserHistory.visit("google.com");
	output.push_back("null");

	browserHistory.visit("facebook.com");
	output.push_back("null");

	browserHistory.visit("youtube.com");
	output.push_back("null");

	output.push_back(browserHistory.back(1));
	output.push_back(browserHistory.back(1));
	output.push_back(browserHistory.forward(1));

	browserHistory.visit("linkedin.com");
	output.push_back("null");

	output.push_back(browserHistory.forward(2));
	output.push_back(browserHistory.back(2));
	output.push_back(browserHistory.back(7));

	cout << "Output: [";
	for (size_t i = 0; i < output.size(); ++i) {
		if (i > 0) {
			cout << ',';
		}

		if (output[i] == "null") {
			cout << "null";
		} else {
			cout << '"' << output[i] << '"';
		}
	}
	cout << "]\n\n";

	browserHistory.printHistory();
	browserHistory.printCurrentPage();
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    solve();
    return 0;
}
