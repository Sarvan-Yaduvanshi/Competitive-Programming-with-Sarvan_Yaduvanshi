/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-16 10:46:30
*/

/*
  Problem: Spiral Matrix IV (LeetCode 2326)
   You are given two integers m and n, which represent the dimensions of a matrix.
   You are also given the head of a linked list of integers.
   Generate an m x n matrix that contains the integers in the linked list presented in spiral order (clockwise),
   starting from the top-left of the matrix. If there are remaining empty spaces, fill them with -1.

   Return the generated matrix.

   Example 1:
	   Input: m = 3, n = 5, head = [3,0,2,6,8,1,7,9,4,2,5,5,0]
	   Output: [[3,0,2,6,8],[5,0,-1,-1,1],[5,2,4,9,7]]
	   Explanation: top left -> right: 3, 0, 2, 6, 8
					top right -> bottom: 1, 7, 9
					bottom right -> left: 4, 2, 5
					bottom left -> top: 5, 0
					remaining empty cells are filled with -1.

	  Example 2:
	   Input: m = 1, n = 4, head = [0,1,2]
	   Output: [[0,1,2,-1]]
	   Explanation: The remaining empty cell is filled with -1.
   Constraints:
       1 <= m, n <= 10^5
       1 <= m * n <= 10^5
       The number of nodes in the given list is in the range [1, m * n
       0 <= Node.val <= 1000
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

class MyLinkedList{
private:
	struct ListNode{
		int val;
		ListNode* next;
		explicit ListNode(const int val) : val(val), next(nullptr) {}
	};

	ListNode* head;

public:
	MyLinkedList() : head(nullptr) {}

	static vector<vector<int>> spiralMatrix(const int m, const int n, ListNode* head){
		int left = 0;
		int right = n - 1;
		int top = 0;
		int bottom = m - 1;

		vector<vector<int>> matrix(m, vector<int>(n, -1));
		ListNode* temp = head;

		while (top <= bottom && left <= right){
			for (int i = left; i <= right && temp != nullptr; i++){
				matrix[top][i] = temp->val;
				temp = temp->next;
			}
			++top;

			for (int i = top; i <= bottom && temp != nullptr; i++){
				matrix[i][right] = temp->val;
				temp = temp->next;
			}
			--right;

			if (top <= bottom){
				for (int i = right; i >= left && temp != nullptr; i--){
					matrix[bottom][i] = temp->val;
					temp = temp->next;
				}
				--bottom;
			}

			if (left <= right){
				for (int i = bottom; i >= top && temp != nullptr; i--){
					matrix[i][left] = temp->val;
					temp = temp->next;
				}
				++right;
			}
		}

		return matrix;
	}

	// Helper function to build a linked list from a vector of integers
	static ListNode* buildList(const vector<int>& a){
		if (a.empty())
			return nullptr;

		auto* head = new ListNode(a[0]);
		ListNode* tail = head;
		for (int i = 1; i < a.size(); i++){
			tail->next = new ListNode(a[i]);
			tail = tail->next;
		}

		return head;
	}

	// Helper function to print the linked list
	static void printList(ListNode* head){
		if (head == nullptr){
			cout << "Empty List" << endl;
			return;
		}

		ListNode* current = head;
		while (current != nullptr){
			cout << current->val;
			if (current->next != nullptr)
				cout << " -> ";
			current = current->next;
		}
		cout << " -> nullptr\n";
	}
};

static void solve() {
    int m, n;
	cout << "Enter the dimensions of the matrix (m n): ";
	cin >> m >> n;

	int numberOfNodes;
	cout << "Enter the number of nodes in the linked list: ";
	cin >> numberOfNodes;
	vector<int> a(numberOfNodes);
	cout << "Enter the values of the linked list nodes: ";
	for (int& x : a)
		cin >> x;

	auto* head = MyLinkedList::buildList(a);
	cout << "Original List: ";
	MyLinkedList::printList(head);

	auto matrix = MyLinkedList::spiralMatrix(m, n, head);
	cout << "Spiral Matrix:\n";
	cout << "[\n";
	for (int i = 0; i < m; ++i) {
		cout << "  [";
		for (int j = 0; j < n; ++j) {
			cout << matrix[i][j];
			if (j < n - 1) cout << ", ";
		}
		cout << "]";
		if (i < m - 1) cout << ",";
		cout << "\n";
	}
	cout << "]\n";
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}

