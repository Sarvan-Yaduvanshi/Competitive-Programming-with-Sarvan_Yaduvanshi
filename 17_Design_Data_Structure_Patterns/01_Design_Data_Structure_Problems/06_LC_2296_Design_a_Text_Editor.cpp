/*
Author: Sarvan Yaduvanshi
Created : 2026-11-01 23:30:38
*/

/*
 * ============================================================================
 *  2296. Design a Text Editor
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 2296
 *  Difficulty : Hard
 *  Topics     : Linked List, String, Stack, Design, Simulation,
 *               Doubly-Linked List
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Uber
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Design a text editor with a cursor that can do the following:
 *
 *      - Add text to where the cursor is.
 *      - Delete text from where the cursor is (simulating the backspace
 *        key).
 *      - Move the cursor either left or right.
 *
 *  When deleting text, only characters to the left of the cursor will be
 *  deleted. The cursor will also remain within the actual text and cannot be
 *  moved beyond it. More formally, we have that
 *  0 <= cursor.position <= currentText.length always holds.
 *
 *  Implement the TextEditor class:
 *
 *      - TextEditor()
 *            Initializes the object with empty text.
 *
 *      - void addText(string text)
 *            Appends text to where the cursor is. The cursor ends to the
 *            right of text.
 *
 *      - int deleteText(int k)
 *            Deletes k characters to the left of the cursor. Returns the
 *            number of characters actually deleted.
 *
 *      - string cursorLeft(int k)
 *            Moves the cursor to the left k times. Returns the last
 *            min(10, len) characters to the left of the cursor, where len
 *            is the number of characters to the left of the cursor.
 *
 *      - string cursorRight(int k)
 *            Moves the cursor to the right k times. Returns the last
 *            min(10, len) characters to the left of the cursor, where len
 *            is the number of characters to the left of the cursor.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      Input
 *      ["TextEditor", "addText", "deleteText", "addText", "cursorRight",
 *       "cursorLeft", "deleteText", "cursorLeft", "cursorRight"]
 *      [[], ["leetcode"], [4], ["practice"], [3], [8], [10], [2], [6]]
 *
 *      Output
 *      [null, null, 4, null, "etpractice", "leet", 4, "", "practi"]
 *
 *  Explanation:
 *      TextEditor textEditor = new TextEditor();
 *          // The current text is "|". (The '|' character represents the
 *          // cursor)
 *      textEditor.addText("leetcode");
 *          // The current text is "leetcode|".
 *      textEditor.deleteText(4);
 *          // return 4
 *          // The current text is "leet|".
 *          // 4 characters were deleted.
 *      textEditor.addText("practice");
 *          // The current text is "leetpractice|".
 *      textEditor.cursorRight(3);
 *          // return "etpractice"
 *          // The current text is "leetpractice|".
 *          // The cursor cannot be moved beyond the actual text and thus
 *          // did not move.
 *          // "etpractice" is the last 10 characters to the left of the
 *          // cursor.
 *      textEditor.cursorLeft(8);
 *          // return "leet"
 *          // The current text is "leet|practice".
 *          // "leet" is the last min(10, 4) = 4 characters to the left of
 *          // the cursor.
 *      textEditor.deleteText(10);
 *          // return 4
 *          // The current text is "|practice".
 *          // Only 4 characters were deleted.
 *      textEditor.cursorLeft(2);
 *          // return ""
 *          // The current text is "|practice".
 *          // The cursor cannot be moved beyond the actual text and thus
 *          // did not move.
 *          // "" is the last min(10, 0) = 0 characters to the left of the
 *          // cursor.
 *      textEditor.cursorRight(6);
 *          // return "practi"
 *          // The current text is "practi|ce".
 *          // "practi" is the last min(10, 6) = 6 characters to the left
 *          // of the cursor.
 *
 * ----------------------------------------------------------------------------
 *  Picture (| = cursor):
 *
 *      new            :  |
 *      addText leetcode :  leetcode|
 *      deleteText(4)  :  leet|            returns 4
 *      addText practice:  leetpractice|
 *      cursorRight(3) :  leetpractice|    no move, returns "etpractice"
 *      cursorLeft(8)  :  leet|practice    returns "leet"
 *      deleteText(10) :  |practice        returns 4 (only 4 existed)
 *      cursorLeft(2)  :  |practice        no move, returns ""
 *      cursorRight(6) :  practi|ce        returns "practi"
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - 1 <= text.length, k <= 40
 *      - text consists of lowercase English letters.
 *      - At most 2 * 10^4 calls in total will be made to addText,
 *        deleteText, cursorLeft and cursorRight.
 *
 * ----------------------------------------------------------------------------
 *  Follow-up: Could you find a solution with time complexity of O(k) per
 *  call?
 * ============================================================================


 * DESIGN Text Editor (Hard — Sentinel DLL)
 * ============================================================================
 *
 * - Core Invariant (The "Left-of-Pipe" Cursor Definition):
 *   Use two permanent dummy sentinels (`head` and `tail`), and define `cursor`
 *   as the node IMMEDIATELY TO THE LEFT of the blinking pipe `|`:
 *     Text: "ab|cd"  ==>  [head] <-> ['a'] <-> ['b'] (cursor) | <-> ['c'] <-> ['d'] <-> [tail]
 *     Text: "|abcd"  ==>  [head] (cursor) | <-> ['a'] <-> ['b'] <-> ['c'] <-> ['d'] <-> [tail]
 *
 *   Because `head` and `tail` are permanent sentinels:
 *     - The cursor is at the far-left boundary iff `cursor == head`.
 *     - The cursor is at the far-right boundary iff `cursor->next == tail`.
 *     - Zero null-pointer checks are ever needed during insert or delete!
 *
 * - Quick Dry Run:
 *     Init              : [head (cursor)] <-> [tail]
 *     addText("abc")    : [head] <-> ['a'] <-> ['b'] <-> ['c' (cursor)] <-> [tail]
 *     cursorLeft(1)     : `cursor` moves to ['b'] ("ab|c"). Returns "ab".
 *     deleteText(1)     : Deletes ['b'], `cursor` moves to ['a'] ("a|c"). Returns 1.
 *     cursorRight(1)    : `cursor` moves to ['c'] ("ac|"). Returns "ac".
 *
 * - Complexity:
 *   Time  : O(|text|) for `addText`, O(k) for `deleteText`, `cursorLeft`, `cursorRight`.
 *   Space : O(N) — 1 DLL node per active character in the document.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;

class TextEditor {
private:
	// Node structure for the doubly linked list
	struct Node {
		char ch;    // Character stored in the node
		Node* next; // Pointer to the next node
		Node* prev; // Pointer to the previous node

		// Constructor to initialize a node with a character
		explicit Node(const char c) : ch(c), next(nullptr), prev(nullptr) {}
	};

	Node* head;    // head pointer
	Node* tail;    // tail pointer
	Node* cursor;  // Always sits on the character immediately LEFT of the cursor `|`

	// Helper: Return up to 10 characters to the left of `cursor` in forward order
	// Time Complexity: O(10) = O(1)
	string getLeftString() {
		const Node* temp = cursor;  // Start from the cursor position
		string ans = "";            // store the answer string
		int count = 10;             // We want to collect at most 10 characters

		// Walk up to 10 steps left from `cursor` (stopping at `head`)
		while (count > 0 && temp != head) {
			ans.push_back(temp->ch);  // store the curr char to ans
			temp = temp->prev;        // move to the previous node
			count--;                  // decrese count
		}

		// Since we collected characters right-to-left, reverse this tiny <=10-char string
		ranges::reverse(ans);
		return ans;
	}

public:
	// Constructor: Initialize the text editor object
	// Time Complexity: O(1)
	TextEditor() {
		head = new Node('#');  // Dummy head node to simplify edge cases
		tail = new Node('#');  // Dummy tail node to simplify edge cases

		head->next = tail;
		tail->prev = head;

		// Initially the document is empty ("|"), so `cursor` sits on `head`
		cursor = head;
	}

	// Destructor: Clean up all nodes to prevent memory leaks
	~TextEditor() {
		const Node* curr = head;
		while (curr != nullptr){
			const Node* nextNode = curr->next;
			delete curr;
			curr = nextNode;
		}
	}

	// Add text to the right of the cursor
	// Time Complexity: O(|text|) where |text| is the length of the input string
	// Space Complexity: O(|text|) for the new nodes created
	void addText(string text){
		for (const char c : text){
			Node* newNode = new Node(c);     // Create a new node for the character
			Node* rightNode = cursor->next;  // Store the right node (the one after the cursor)

			// Insert the new node between `cursor` and `rightNode`
			cursor->next = newNode;    // Link cursor to new node
			newNode->next = rightNode; // Link new node to the right node

			newNode->prev = cursor;    // Link new node back to cursor
			rightNode->prev = newNode; // Link right node back to new node

			cursor = newNode;         // Move `cursor` onto the newly typed character
		}
	}

	// Delete up to k characters to the left of the cursor
	// Time Complexity: O(k) where k is the number of characters to delete
	// Space Complexity: O(1) since we are not using any additional data structures
	int deleteText(int k) {
		int deleteCount = 0; // Count of characters actually deleted

		// Backspace `cursor` while characters exist to the left (`cursor != head`)
		while (k > 0 && cursor != head){
			const Node* toDelete = cursor;    // Node to be deleted
			Node* prevNode = cursor->prev;    // Node to the left of `cursor`
			Node* nextNode = cursor->next;    // Node to the right of `cursor` (could be `tail`)

			// Unlink the `toDelete` node from the list
			prevNode->next = nextNode;
			nextNode->prev = prevNode;

			// Move `cursor` 1 step left and free the deleted character
			cursor = prevNode;
			delete toDelete;

			deleteCount++;  // inrease the count
			k--;            // Decrease the number of characters left to delete
		}

		return deleteCount; // Return the number of characters actually deleted
	}

	// Move the cursor left k times and return the last min(10, len) characters to the left of the cursor
	// Time Complexity: O(k) where k is the number of moves requested
	// Space Complexity: O(1) since we are not using any additional data structures
	string cursorLeft(int k) {
		// Move the cursor left k times, but not beyond the head of the list
		while (k > 0 && cursor != head){
			cursor = cursor->prev;  // Move cursor left
			k--;                    // Decrease the number of moves left
		}

		// Return the last min(10, len) characters to the left of the cursor
		return getLeftString();
	}

	// Move the cursor right k times and return the last min(10, len) characters to the left of the cursor
	// Time Complexity: O(k) where k is the number of moves requested
	// Space Complexity: O(1) since we are not using any additional data structures
	string cursorRight(int k) {
		// Move the cursor right k times, but not beyond the tail of the list
		while (k > 0 && cursor->next != tail){
			cursor = cursor->next; // Move cursor right
			k--;                   // Decrease the number of moves left
		}

		// Return the last min(10, len) characters to the left of the cursor
		return getLeftString();
	}
};

static void solve(){
	int operationCount;

	// Input format:
	// operationCount
	// addText text
	// deleteText k
	// cursorLeft k
	// cursorRight k
	if (!(cin >> operationCount))
		return;

	TextEditor textEditor;
	vector<string> results;

	for (int operation = 0; operation < operationCount; ++operation) {
		string command;
		cin >> command;

		if (command == "addText") {
			string text;
			cin >> text;
			textEditor.addText(text);
			results.push_back("null");

			cout << "addText " << text << '\n';
			cout << "null\n";
		} else if (command == "deleteText") {
			int k;
			cin >> k;
			int result = textEditor.deleteText(k);
			results.push_back(to_string(result));

			cout << "deleteText " << k << '\n';
			cout << result << '\n';
		} else if (command == "cursorLeft") {
			int k;
			cin >> k;
			string result = textEditor.cursorLeft(k);
			results.push_back('"' + result + '"');

			cout << "cursorLeft " << k << '\n';
			cout << '"' << result << '"' << '\n';
		} else if (command == "cursorRight") {
			int k;
			cin >> k;
			string result = textEditor.cursorRight(k);
			results.push_back('"' + result + '"');

			cout << "cursorRight " << k << '\n';
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
