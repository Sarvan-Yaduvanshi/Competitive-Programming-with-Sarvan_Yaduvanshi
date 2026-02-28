/*
╔══════════════════════════════════════════════════════════════════════════════╗
║              🚀 HASHING QUICK REFERENCE CHEAT SHEET 🚀                        ║
║                    For Quick Revision & CP Contests                          ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <climits>
using namespace std;

/*
══════════════════════════════════════════════════════════════════════════════
📊 DATA STRUCTURE COMPARISON TABLE
══════════════════════════════════════════════════════════════════════════════

┌────────────────┬────────┬───────────┬────────────┬─────────────────────────┐
│ Structure      │ Sorted │ Duplicate │ Complexity │ When to Use             │
├────────────────┼────────┼───────────┼────────────┼─────────────────────────┤
│ set            │   ✅   │    ❌     │  O(log n)  │ Sorted unique elements  │
│ unordered_set  │   ❌   │    ❌     │  O(1) avg  │ Fast unique check       │
│ multiset       │   ✅   │    ✅     │  O(log n)  │ Sorted with duplicates  │
├────────────────┼────────┼───────────┼────────────┼─────────────────────────┤
│ map            │   ✅   │    ❌     │  O(log n)  │ Sorted key-value        │
│ unordered_map  │   ❌   │    ❌     │  O(1) avg  │ Fast key-value lookup   │
│ multimap       │   ✅   │    ✅     │  O(log n)  │ Multiple values per key │
└────────────────┴────────┴───────────┴────────────┴─────────────────────────┘
*/

// ══════════════════════════════════════════════════════════════════════════════
// 🔥 FREQUENCY COUNT TEMPLATES (COPY-PASTE READY!)
// ══════════════════════════════════════════════════════════════════════════════

// TEMPLATE 1: Integer Frequency (unordered_map) - MOST VERSATILE
void template_freq_map(vector<int>& arr) {
    unordered_map<int, int> freq;
    for (int x : arr) freq[x]++;

    // Access: freq[x] gives count of x
    // Check: if (freq.count(x)) or if (freq[x] > 0)
}

// TEMPLATE 2: Integer Frequency (vector) - FASTEST when range known
void template_freq_vector(vector<int>& arr, int maxVal) {
    vector<int> freq(maxVal + 1, 0);
    for (int x : arr) freq[x]++;

    // Access: freq[x] gives count of x
    // Use when: 0 <= arr[i] <= 10^6
}

// TEMPLATE 3: Character Frequency (26 lowercase) - SUPER FAST
void template_freq_char26(string& s) {
    int freq[26] = {0};  // or vector<int> freq(26, 0);
    for (char c : s) freq[c - 'a']++;

    // Access: freq['a' - 'a'] = freq[0] for 'a'
    // Convert back: char c = 'a' + i;
}

// TEMPLATE 4: All ASCII Characters
void template_freq_ascii(string& s) {
    int freq[256] = {0};
    for (char c : s) freq[(unsigned char)c]++;
}

// TEMPLATE 5: String Frequency
void template_freq_string(vector<string>& words) {
    unordered_map<string, int> freq;
    for (auto& w : words) freq[w]++;
}

// TEMPLATE 6: Pair Frequency (use map, not unordered_map)
void template_freq_pair(vector<pair<int,int>>& points) {
    map<pair<int,int>, int> freq;  // map because pair has no hash
    for (auto& p : points) freq[p]++;
}

// ══════════════════════════════════════════════════════════════════════════════
// ⚡ COMMON OPERATIONS QUICK REFERENCE
// ══════════════════════════════════════════════════════════════════════════════

/*
═══ COMMON OPERATIONS REFERENCE ═══

UNORDERED_MAP<K, V> mp:
    mp[key] = val;              // Insert/Update
    mp[key]++;                  // Increment (creates with 0 if not exists)
    mp.count(key);              // Returns 0 or 1
    mp.find(key) != mp.end();   // Check existence
    mp.erase(key);              // Delete
    mp.size();                  // Number of keys
    mp.clear();                 // Remove all
    if (mp.count(key)) cout << mp[key];  // Safe access
    for (auto& [k, v] : mp) {}  // Iterate

SET<T> s:
    s.insert(x);                // Add element
    s.erase(x);                 // Remove element
    s.count(x);                 // 0 or 1
    s.find(x) != s.end();       // Check existence
    *s.begin();                 // Minimum element
    *s.rbegin();                // Maximum element
    s.lower_bound(x);           // First >= x
    s.upper_bound(x);           // First > x

MULTISET<T> ms:
    ms.insert(x);               // Add (allows duplicates)
    ms.count(x);                // Returns actual count
    ms.erase(x);                // ⚠️ Removes ALL x!
    ms.erase(ms.find(x));       // Removes only ONE x

MAP<K, V> ordered_mp:
    (same as unordered_map, but sorted)
    Has lower_bound, upper_bound (on keys)
*/

// ══════════════════════════════════════════════════════════════════════════════
// 🎯 VECTOR vs UNORDERED_MAP DECISION
// ══════════════════════════════════════════════════════════════════════════════
/*
USE VECTOR[size] when:
✅ Values are non-negative (or shift them)
✅ Range is small (≤ 10^6)
✅ Need maximum speed
✅ Memory is not a constraint

USE UNORDERED_MAP when:
✅ Values can be negative
✅ Range is huge (10^9, 10^18)
✅ Sparse data (few unique values)
✅ Keys are strings/pairs/custom types
✅ Flexibility needed

USE MAP when:
✅ Need sorted output
✅ Need lower_bound/upper_bound
✅ Working with pairs as keys (no custom hash needed)
*/

// ══════════════════════════════════════════════════════════════════════════════
// 🛡️ SAFE HASH FOR CODEFORCES (ANTI-HACK!)
// ══════════════════════════════════════════════════════════════════════════════
struct SafeHash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
// Usage: unordered_map<long long, int, SafeHash> safe_mp;

// ══════════════════════════════════════════════════════════════════════════════
// 🔥 COMMON PATTERNS (1-LINER TEMPLATES)
// ══════════════════════════════════════════════════════════════════════════════

// Count distinct elements
int countDistinct(vector<int>& arr) {
    return unordered_set<int>(arr.begin(), arr.end()).size();
}

// Check anagram
bool isAnagram(string& a, string& b) {
    if (a.size() != b.size()) return false;
    int f[26] = {0};
    for (int i = 0; i < a.size(); i++) f[a[i]-'a']++, f[b[i]-'a']--;
    for (int i = 0; i < 26; i++) if (f[i]) return false;
    return true;
}

// Two Sum (return indices)
pair<int,int> twoSum(vector<int>& arr, int target) {
    unordered_map<int, int> seen;
    for (int i = 0; i < arr.size(); i++) {
        if (seen.count(target - arr[i])) return {seen[target - arr[i]], i};
        seen[arr[i]] = i;
    }
    return {-1, -1};
}

// Subarray sum equals K (count)
int subarraySumK(vector<int>& arr, int k) {
    unordered_map<long long, int> prefix;
    prefix[0] = 1;
    long long sum = 0;
    int count = 0;
    for (int x : arr) {
        sum += x;
        if (prefix.count(sum - k)) count += prefix[sum - k];
        prefix[sum]++;
    }
    return count;
}

// Majority Element (> n/2 times)
int majorityElement(vector<int>& arr) {
    unordered_map<int, int> f;
    for (int x : arr) if (++f[x] > arr.size() / 2) return x;
    return -1;
}

// First non-repeating character
int firstUnique(string& s) {
    int f[26] = {0};
    for (char c : s) f[c - 'a']++;
    for (int i = 0; i < s.size(); i++) if (f[s[i] - 'a'] == 1) return i;
    return -1;
}

// Longest substring without repeating characters
int longestUnique(string& s) {
    unordered_map<char, int> last;
    int maxLen = 0, start = 0;
    for (int i = 0; i < s.size(); i++) {
        if (last.count(s[i]) && last[s[i]] >= start) start = last[s[i]] + 1;
        last[s[i]] = i;
        maxLen = max(maxLen, i - start + 1);
    }
    return maxLen;
}

// Group Anagrams
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> groups;
    for (string& s : strs) {
        string key = s;
        sort(key.begin(), key.end());
        groups[key].push_back(s);
    }
    vector<vector<string>> result;
    for (auto& [k, v] : groups) result.push_back(v);
    return result;
}

// Longest consecutive sequence
int longestConsecutive(vector<int>& nums) {
    unordered_set<int> s(nums.begin(), nums.end());
    int maxLen = 0;
    for (int n : s) {
        if (!s.count(n - 1)) {  // Start of sequence
            int len = 1;
            while (s.count(n + len)) len++;
            maxLen = max(maxLen, len);
        }
    }
    return maxLen;
}

// Count distinct in every window of size k
vector<int> distinctInWindow(vector<int>& arr, int k) {
    unordered_map<int, int> freq;
    vector<int> result;
    for (int i = 0; i < arr.size(); i++) {
        freq[arr[i]]++;
        if (i >= k) {
            if (--freq[arr[i - k]] == 0) freq.erase(arr[i - k]);
        }
        if (i >= k - 1) result.push_back(freq.size());
    }
    return result;
}

/*
══════════════════════════════════════════════════════════════════════════════
📝 PRACTICE PROBLEMS QUICK LIST
══════════════════════════════════════════════════════════════════════════════

🌟 MUST-DO (Start Here):
1. LC 1 - Two Sum
2. LC 217 - Contains Duplicate
3. LC 242 - Valid Anagram
4. LC 387 - First Unique Character
5. LC 560 - Subarray Sum Equals K
6. LC 3 - Longest Substring Without Repeating Characters
7. LC 49 - Group Anagrams
8. LC 128 - Longest Consecutive Sequence
9. LC 347 - Top K Frequent Elements
10. LC 76 - Minimum Window Substring

🔥 CODEFORCES FAVORITES:
1. CF 4C - Registration System
2. CF 702B - Powers of Two
3. CF 1520D - Same Differences
4. CF 988C - Equal Sums
5. CF 1374D - Zero Remainder Array

══════════════════════════════════════════════════════════════════════════════
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Test the templates!
    vector<int> arr = {1, 2, 3, 2, 1, 3, 3, 4, 1};

    unordered_map<int, int> freq;
    for (int x : arr) freq[x]++;

    cout << "Frequency Count Demo:\n";
    for (auto& [num, cnt] : freq) {
        cout << num << " appears " << cnt << " times\n";
    }

    string s = "programming";
    int charFreq[26] = {0};
    for (char c : s) charFreq[c - 'a']++;

    cout << "\nCharacter Frequency in \"" << s << "\":\n";
    for (int i = 0; i < 26; i++) {
        if (charFreq[i] > 0) {
            cout << (char)('a' + i) << ": " << charFreq[i] << "\n";
        }
    }

    return 0;
}

