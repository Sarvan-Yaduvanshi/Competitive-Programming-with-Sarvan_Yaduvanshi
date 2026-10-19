#include <iostream>
#include <vector>
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


};


static void solve(){
	int n; cin >> n;
	vector<int> a(n);
	for (int& x : a)
		cin >> x;
}



int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}