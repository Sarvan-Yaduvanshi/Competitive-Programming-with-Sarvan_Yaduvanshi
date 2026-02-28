/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Palindrome Linked List + More String Palindrome Problems
 *  Level   : Easy → Medium
 * ============================================================================
 *
 *  LC 234  — Palindrome Linked List
 *            https://leetcode.com/problems/palindrome-linked-list/
 *  LC 2108 — Find First Palindromic String in the Array
 *            https://leetcode.com/problems/find-first-palindromic-string-in-the-array/
 *  LC 1332 — Remove Palindromic Subsequences
 *            https://leetcode.com/problems/remove-palindromic-subsequences/
 *  LC 1793 — Maximum Score of a Good Subarray
 *            https://leetcode.com/problems/maximum-score-of-a-good-subarray/
 *
 *  TECHNIQUE FOR LC 234 (Palindrome Linked List):
 *  ──────────────────────────────────────────────
 *  1. Find MIDDLE using fast/slow pointers
 *  2. REVERSE the second half
 *  3. COMPARE first half with reversed second half
 *  4. (Optional) Restore the list by reversing again
 *
 *  Time: O(N), Space: O(1)
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ============================================================================
// LC 234: Palindrome Linked List — Fast/Slow + Reverse + Compare
// ============================================================================
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

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

bool isPalindrome(ListNode* head) {
    if (!head || !head->next) return true;

    // Step 1: Find middle (slow ends at start of second half)
    ListNode *slow = head, *fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Step 2: Reverse second half
    ListNode* secondHalf = reverseList(slow->next);

    // Step 3: Compare first half with reversed second half
    ListNode* p1 = head;
    ListNode* p2 = secondHalf;
    bool result = true;
    while (p2) {
        if (p1->val != p2->val) {
            result = false;
            break;
        }
        p1 = p1->next;
        p2 = p2->next;
    }

    // Step 4: Restore (optional but good practice)
    slow->next = reverseList(secondHalf);

    return result;
}

// ============================================================================
// LC 2108: Find First Palindromic String in the Array
// ============================================================================
bool isPalindromeStr(const string& s) {
    int l = 0, r = (int)s.size() - 1;
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++; r--;
    }
    return true;
}

string firstPalindrome(vector<string>& words) {
    for (auto& w : words)
        if (isPalindromeStr(w)) return w;
    return "";
}

// ============================================================================
// LC 1332: Remove Palindromic Subsequences
// ============================================================================
/*
 * String of only 'a' and 'b'. Remove palindromic SUBSEQUENCES.
 * Min removals to make empty.
 *
 * TRICK: If already palindrome → 1 removal.
 *        Else → 2 removals (remove all 'a's first, then all 'b's —
 *        each is a palindromic subsequence!)
 *        Empty string → 0.
 */
int removePalindromeSub(string s) {
    if (s.empty()) return 0;
    if (isPalindromeStr(s)) return 1;
    return 2;
}

// ============================================================================
// LC 1793: Maximum Score of a Good Subarray — Two Pointer Expand
// ============================================================================
/*
 * Good subarray contains index k. Score = min(subarray) * length.
 * Expand from k outward greedily — always expand toward the taller side.
 *
 * Similar to "Container With Most Water" in reverse — expanding, not shrinking.
 */
int maximumScore(vector<int>& nums, int k) {
    int n = nums.size();
    int left = k, right = k;
    int minVal = nums[k];
    int best = minVal;

    while (left > 0 || right < n - 1) {
        // Expand toward the side with the taller boundary
        int leftVal = (left > 0) ? nums[left - 1] : 0;
        int rightVal = (right < n - 1) ? nums[right + 1] : 0;

        if (leftVal >= rightVal) {
            left--;
            minVal = min(minVal, nums[left]);
        } else {
            right++;
            minVal = min(minVal, nums[right]);
        }
        best = max(best, minVal * (right - left + 1));
    }
    return best;
}

int main() {
    // Palindrome Linked List
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(2);
    head->next->next->next = new ListNode(1);
    cout << "Palindrome LL: " << isPalindrome(head) << "\n"; // 1

    // First Palindromic String
    vector<string> words = {"abc", "car", "ada", "racecar", "cool"};
    cout << "First palindrome: " << firstPalindrome(words) << "\n"; // "ada"

    // Remove Palindromic Subsequences
    cout << "Remove palins (ababb): " << removePalindromeSub("ababb") << "\n"; // 2

    // Maximum Score
    vector<int> nums = {1, 4, 3, 7, 4, 5};
    cout << "Max score (k=3): " << maximumScore(nums, 3) << "\n"; // 15

    return 0;
}

