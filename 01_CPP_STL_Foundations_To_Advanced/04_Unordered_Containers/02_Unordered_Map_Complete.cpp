/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — UNORDERED_MAP COMPLETE GUIDE                                ║
║           From Zero to Grandmaster — O(1) Key-Value Store                  ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Basic Operations
 2. Frequency Map Pattern (THE #1 CP Pattern)
 3. Two Sum Pattern
 4. Subarray Sum Equals K Pattern
 5. Group Anagrams Pattern
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: BASIC OPERATIONS
// ═══════════════════════════════════════════════════════════════

void demonstrateBasics() {
    cout << "═══ UNORDERED_MAP BASICS ═══\n\n";

    unordered_map<string, int> um;
    um["alice"] = 95;
    um["bob"] = 87;
    um.insert({"charlie", 92});
    um.emplace("david", 88);

    // Access
    cout << "alice: " << um["alice"] << "\n";
    cout << "bob: " << um.at("bob") << "\n";

    // find
    if (um.find("charlie") != um.end())
        cout << "charlie found\n";

    // count
    cout << "count(alice)=" << um.count("alice") << "\n";
    cout << "count(eve)=" << um.count("eve") << "\n";

    // Iteration (UNORDERED!)
    cout << "\nAll entries:\n";
    for (auto& [k, v] : um)
        cout << "  " << k << " → " << v << "\n";

    // erase
    um.erase("bob");
    cout << "\nAfter erase(bob), size=" << um.size() << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: FREQUENCY MAP PATTERN
// ═══════════════════════════════════════════════════════════════
/*
 THE MOST COMMON PATTERN:
   for (auto x : arr) freq[x]++;

 DRY RUN: arr = [1, 2, 2, 3, 3, 3]
   freq[1]++ → {1:1}
   freq[2]++ → {1:1, 2:1}
   freq[2]++ → {1:1, 2:2}
   freq[3]++ → {1:1, 2:2, 3:1}
   freq[3]++ → {1:1, 2:2, 3:2}
   freq[3]++ → {1:1, 2:2, 3:3}
*/

void frequencyPattern() {
    cout << "═══ FREQUENCY MAP PATTERN ═══\n\n";

    vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    unordered_map<int, int> freq;
    for (int x : arr) freq[x]++;

    cout << "Frequencies:\n";
    for (auto& [val, cnt] : freq)
        cout << "  " << val << " → " << cnt << "\n";

    // Find element with max frequency
    int maxFreq = 0, maxElem = 0;
    for (auto& [val, cnt] : freq) {
        if (cnt > maxFreq) {
            maxFreq = cnt;
            maxElem = val;
        }
    }
    cout << "Most frequent: " << maxElem << " (" << maxFreq << " times)\n\n";

    // Check if all frequencies are same
    set<int> freqValues;
    for (auto& [_, cnt] : freq) freqValues.insert(cnt);
    cout << "All same frequency? " << (freqValues.size() == 1 ? "Yes" : "No") << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: TWO SUM PATTERN
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: Find two numbers in array that sum to target.

 APPROACH: For each element x, check if (target - x) exists in map.

 DRY RUN: arr = [2, 7, 11, 15], target = 9
   x=2: need 7, not in map → store {2:0}
   x=7: need 2, found at index 0! → return [0, 1]

 Time: O(n), Space: O(n)
*/

void twoSumPattern() {
    cout << "═══ TWO SUM PATTERN ═══\n\n";

    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    unordered_map<int, int> seen;  // value → index
    for (int i = 0; i < (int)nums.size(); i++) {
        int complement = target - nums[i];
        if (seen.count(complement)) {
            cout << "Two Sum " << target << ": indices ["
                 << seen[complement] << ", " << i << "] → "
                 << nums[seen[complement]] << " + " << nums[i] << "\n\n";
            break;
        }
        seen[nums[i]] = i;
    }
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: SUBARRAY SUM EQUALS K PATTERN
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: Count subarrays with sum = K.

 APPROACH: prefix_sum + hashmap
   If prefix[i] - prefix[j] = K, then subarray (j,i] has sum K.
   So we need prefix[j] = prefix[i] - K.
   Store frequency of prefix sums in map.

 DRY RUN: arr = [1, 1, 1], K = 2
   prefix = 0
   i=0: prefix=1, need 1-2=-1, count=0, store {0:1, 1:1}
   i=1: prefix=2, need 2-2=0, found 1 time! count=1, store {0:1, 1:1, 2:1}
   i=2: prefix=3, need 3-2=1, found 1 time! count=2, store {0:1, 1:1, 2:1, 3:1}
   Answer: 2 subarrays ([1,1] starting at 0 and [1,1] starting at 1)
*/

void subarraySumK() {
    cout << "═══ SUBARRAY SUM = K PATTERN ═══\n\n";

    vector<int> arr = {1, 2, 3, -2, 5};
    int K = 3;

    unordered_map<int, int> prefixCount;
    prefixCount[0] = 1;  // Empty prefix sum = 0
    int prefix = 0, count = 0;

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\nK = " << K << "\n\n";

    for (int i = 0; i < (int)arr.size(); i++) {
        prefix += arr[i];
        int need = prefix - K;
        if (prefixCount.count(need)) {
            count += prefixCount[need];
            cout << "  prefix=" << prefix << ", need=" << need
                 << ", found " << prefixCount[need] << " match(es)\n";
        }
        prefixCount[prefix]++;
    }
    cout << "\nTotal subarrays with sum " << K << ": " << count << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: GROUP ANAGRAMS PATTERN
// ═══════════════════════════════════════════════════════════════

void groupAnagrams() {
    cout << "═══ GROUP ANAGRAMS PATTERN ═══\n\n";

    vector<string> words = {"eat", "tea", "tan", "ate", "nat", "bat"};

    // Key: sorted version of word → same key for anagrams
    unordered_map<string, vector<string>> groups;
    for (auto& w : words) {
        string key = w;
        sort(key.begin(), key.end());
        groups[key].push_back(w);
    }

    cout << "Anagram groups:\n";
    for (auto& [key, group] : groups) {
        cout << "  [";
        for (int i = 0; i < (int)group.size(); i++) {
            if (i) cout << ", ";
            cout << group[i];
        }
        cout << "]\n";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demonstrateBasics();
    frequencyPattern();
    twoSumPattern();
    subarraySumK();
    groupAnagrams();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. unordered_map: O(1) avg lookup — fastest map\n";
    cout << "2. Frequency: for(x:arr) freq[x]++\n";
    cout << "3. Two Sum: check if complement exists in map\n";
    cout << "4. Subarray Sum K: prefix sum + hashmap\n";
    cout << "5. Group by key: sort string/encode → map to vector\n";
    cout << "6. Use reserve() and custom hash for safety!\n";

    return 0;
}

/*
 PRACTICE PROBLEMS:
 ──────────────────
 1. [LC Two Sum]           https://leetcode.com/problems/two-sum/
 2. [LC Subarray Sum = K]  https://leetcode.com/problems/subarray-sum-equals-k/
 3. [LC Group Anagrams]    https://leetcode.com/problems/group-anagrams/
 4. [CSES Sum of Two]      https://cses.fi/problemset/task/1640
*/

