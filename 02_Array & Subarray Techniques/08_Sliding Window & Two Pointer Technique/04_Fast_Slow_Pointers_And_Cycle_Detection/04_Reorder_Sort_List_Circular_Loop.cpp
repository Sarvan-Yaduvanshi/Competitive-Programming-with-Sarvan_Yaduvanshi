/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Reorder List, Sort List, Circular Array Loop — Advanced Fast/Slow
 *  Level   : Medium → Hard
 * ============================================================================
 *
 *  LC 143  — Reorder List (Medium)
 *            https://leetcode.com/problems/reorder-list/
 *            Find middle → reverse 2nd half → merge alternately
 *
 *  LC 148  — Sort List (Medium)
 *            https://leetcode.com/problems/sort-list/
 *            Merge sort: fast/slow to find middle, split, sort, merge
 *
 *  LC 457  — Circular Array Loop (Medium)
 *            https://leetcode.com/problems/circular-array-loop/
 *            Floyd's on circular array with direction constraint
 *
 *  LC 61   — Rotate List (Medium)
 *            https://leetcode.com/problems/rotate-list/
 *            Find length, connect tail to head, find new tail
 *
 * ============================================================================
 */
#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// ============================================================================
// LC 143: Reorder List — L0→Ln→L1→Ln-1→L2→Ln-2→...
// ============================================================================
/*
 * Step 1: Find middle (fast/slow)
 * Step 2: Reverse second half
 * Step 3: Merge first half and reversed second half alternately
 */
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    while (head) {
        ListNode* next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

void reorderList(ListNode* head) {
    if (!head || !head->next) return;

    // Find middle
    ListNode *slow = head, *fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Reverse second half
    ListNode* second = reverseList(slow->next);
    slow->next = nullptr; // Cut first half

    // Merge alternately
    ListNode* first = head;
    while (second) {
        ListNode* tmp1 = first->next;
        ListNode* tmp2 = second->next;
        first->next = second;
        second->next = tmp1;
        first = tmp1;
        second = tmp2;
    }
}

// ============================================================================
// LC 148: Sort List — Merge Sort using Fast/Slow to Split
// ============================================================================
/*
 * Merge sort on linked list:
 * 1. Fast/Slow to find middle → split into two halves
 * 2. Recursively sort both halves
 * 3. Merge two sorted halves
 *
 * Time: O(N log N), Space: O(log N) recursion stack
 */
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    while (l1 && l2) {
        if (l1->val <= l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    tail->next = l1 ? l1 : l2;
    return dummy.next;
}

ListNode* sortList(ListNode* head) {
    if (!head || !head->next) return head;

    // Find middle
    ListNode *slow = head, *fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Split
    ListNode* mid = slow->next;
    slow->next = nullptr;

    // Sort halves
    ListNode* left = sortList(head);
    ListNode* right = sortList(mid);

    // Merge
    return mergeTwoLists(left, right);
}

// ============================================================================
// LC 457: Circular Array Loop — Floyd's with Direction Check
// ============================================================================
/*
 * Array where each element tells how many steps to move (positive = forward,
 * negative = backward). Detect if there's a cycle that:
 *   1. Has length > 1
 *   2. All elements in cycle have same direction (all + or all -)
 *
 * For each unvisited element, run Floyd's. Check direction consistency.
 */
#include <vector>
#include <cmath>

bool circularArrayLoop(vector<int>& nums) {
    int n = nums.size();

    auto nextIdx = [&](int i) -> int {
        return ((i + nums[i]) % n + n) % n;
    };

    for (int i = 0; i < n; i++) {
        if (nums[i] == 0) continue;

        int slow = i, fast = i;
        // Check if all same direction
        while (nums[slow] * nums[nextIdx(slow)] > 0 &&
               nums[fast] * nums[nextIdx(fast)] > 0 &&
               nums[nextIdx(fast)] * nums[nextIdx(nextIdx(fast))] > 0) {
            slow = nextIdx(slow);
            fast = nextIdx(nextIdx(fast));
            if (slow == fast) {
                // Check cycle length > 1
                if (slow == nextIdx(slow)) break; // Length 1
                return true;
            }
        }

        // Mark visited elements as 0 (optimization)
        int j = i;
        int dir = nums[i];
        while (nums[j] * dir > 0) {
            int next = nextIdx(j);
            nums[j] = 0;
            j = next;
        }
    }
    return false;
}

int main() {
    // Reorder List: 1→2→3→4 → 1→4→2→3
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    reorderList(head);
    cout << "Reordered: ";
    for (ListNode* p = head; p; p = p->next) cout << p->val << " ";
    cout << "\n"; // 1 4 2 3

    // Sort List: 4→2→1→3 → 1→2→3→4
    ListNode* h2 = new ListNode(4);
    h2->next = new ListNode(2);
    h2->next->next = new ListNode(1);
    h2->next->next->next = new ListNode(3);
    h2 = sortList(h2);
    cout << "Sorted: ";
    for (ListNode* p = h2; p; p = p->next) cout << p->val << " ";
    cout << "\n"; // 1 2 3 4

    // Circular Array Loop
    vector<int> arr = {2, -1, 1, 2, 2};
    cout << "Circular loop: " << circularArrayLoop(arr) << "\n"; // 1

    return 0;
}

