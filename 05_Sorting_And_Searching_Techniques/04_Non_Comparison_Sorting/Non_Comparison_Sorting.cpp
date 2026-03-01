/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 04 — NON-COMPARISON SORTING                              ║
║           From Zero to Grandmaster — Complete Foundation                    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1.  Counting Sort — Basic, Stable, Negative Values
 2.  Radix Sort — LSD (Least Significant Digit), MSD
 3.  Bucket Sort — Uniform Distribution, Float Sorting
 4.  Coordinate Compression — Technique & Applications
 5.  Frequency Sort — Sort by Frequency
 6.  Sorting Small Range Values — Tricks & Optimizations

OVERVIEW:
─────────
Non-comparison sorts bypass the Ω(n log n) lower bound by NOT using
pairwise comparisons. Instead, they exploit the STRUCTURE of values
(integers, bounded range, distribution).

┌──────────────────┬──────────┬──────────┬──────────┬───────┬────────┐
│ Algorithm        │ Best     │ Average  │ Worst    │ Space │ Stable │
├──────────────────┼──────────┼──────────┼──────────┼───────┼────────┤
│ Counting Sort    │ O(n+k)   │ O(n+k)   │ O(n+k)   │ O(k)  │ Yes    │
│ Radix Sort (LSD) │ O(d(n+b))│ O(d(n+b))│ O(d(n+b))│ O(n+b)│ Yes    │
│ Bucket Sort      │ O(n+k)   │ O(n+k)   │ O(n²)    │ O(n+k)│ Yes    │
└──────────────────┴──────────┴──────────┴──────────┴───────┴────────┘
  k = range of values, d = number of digits, b = base

WHEN TO USE:
  • Counting Sort: Integer values in range [0, k] where k = O(n)
  • Radix Sort: Large integers with fixed number of digits
  • Bucket Sort: Uniformly distributed floating-point numbers
  • All three: When n is huge and k is manageable
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <map>
#include <unordered_map>
#include <cmath>
#include <string>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: COUNTING SORT
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Counting Sort works by counting the frequency of each value,
 then using cumulative counts to place elements in correct position.

 REQUIREMENTS:
   • Elements must be integers (or mappable to integers)
   • Range of values k must be reasonable (k = O(n) ideally)
   • If k >> n, counting sort wastes space and is slower

 ALGORITHM:
   1. Find max element k
   2. Create count array of size k+1, initialize to 0
   3. Count frequency: count[arr[i]]++
   4. Cumulative sum: count[i] += count[i-1]
   5. Build output: output[count[arr[i]]-1] = arr[i]; count[arr[i]]--
      (Iterate reverse for stability)

 COMPLEXITY: O(n + k) time, O(n + k) space

 WHY IS IT STABLE?
   In step 5, we iterate RIGHT TO LEFT through the input.
   This ensures elements with the same value maintain their
   original relative order.

 VARIANTS:
   1. Simple counting (just count frequencies, no stability needed)
   2. Stable counting sort (preserves relative order)
   3. With negative numbers (shift all values to non-negative)
*/

// Version 1: Simple Counting Sort (positive integers only)
void countingSort_simple(vector<int>& arr) {
    if (arr.empty()) return;
    int maxVal = *max_element(arr.begin(), arr.end());
    vector<int> count(maxVal + 1, 0);

    for (int x : arr) count[x]++;

    int idx = 0;
    for (int i = 0; i <= maxVal; i++) {
        while (count[i]-- > 0) {
            arr[idx++] = i;
        }
    }
}

// Version 2: Stable Counting Sort
vector<int> countingSort_stable(vector<int>& arr) {
    if (arr.empty()) return {};
    int n = arr.size();
    int maxVal = *max_element(arr.begin(), arr.end());

    vector<int> count(maxVal + 1, 0);
    for (int x : arr) count[x]++;

    // Cumulative count: count[i] = number of elements ≤ i
    for (int i = 1; i <= maxVal; i++) count[i] += count[i - 1];

    // Build output (reverse iteration for stability)
    vector<int> output(n);
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    return output;
}

// Version 3: Counting Sort with Negative Numbers
void countingSort_negative(vector<int>& arr) {
    if (arr.empty()) return;
    int minVal = *min_element(arr.begin(), arr.end());
    int maxVal = *max_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;

    vector<int> count(range, 0);
    for (int x : arr) count[x - minVal]++;

    int idx = 0;
    for (int i = 0; i < range; i++) {
        while (count[i]-- > 0) {
            arr[idx++] = i + minVal;
        }
    }
}

// Version 4: Counting Sort for characters (useful for string problems)
void countingSort_chars(string& s) {
    vector<int> count(256, 0);
    for (char c : s) count[(unsigned char)c]++;

    int idx = 0;
    for (int i = 0; i < 256; i++) {
        while (count[i]-- > 0) {
            s[idx++] = (char)i;
        }
    }
}

// Version 5: Stable Counting Sort on specific digit (used by Radix Sort)
void countingSort_byDigit(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    vector<int> count(10, 0);

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    arr = output;
}

void demo_counting_sort() {
    cout << "=== SECTION 1: COUNTING SORT ===" << endl;

    // Simple counting sort
    vector<int> arr1 = {4, 2, 2, 8, 3, 3, 1};
    countingSort_simple(arr1);
    cout << "Simple: ";
    for (int x : arr1) cout << x << " ";
    cout << endl;

    // Stable counting sort
    vector<int> arr2 = {4, 2, 2, 8, 3, 3, 1};
    vector<int> result = countingSort_stable(arr2);
    cout << "Stable: ";
    for (int x : result) cout << x << " ";
    cout << endl;

    // With negatives
    vector<int> arr3 = {-5, 3, -1, 0, -3, 2, 1};
    countingSort_negative(arr3);
    cout << "Negatives: ";
    for (int x : arr3) cout << x << " ";
    cout << endl;

    // Character sort
    string s = "competitive";
    countingSort_chars(s);
    cout << "Char sort: " << s << endl;

    cout << "Time: O(n+k), Space: O(k)" << endl;
    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: RADIX SORT
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Radix Sort sorts numbers digit by digit, from least significant
 to most significant (LSD) or vice versa (MSD).

 Each digit-level sort uses a STABLE sort (usually Counting Sort).

 LSD RADIX SORT (most common):
   for each digit position d (ones, tens, hundreds, ...):
     stable sort all numbers by digit d

 WHY LSD WORKS:
   After sorting by ones digit, elements with same ones digit are
   in correct relative order. When we sort by tens digit, stability
   preserves the ones-digit ordering. And so on.

 COMPLEXITY: O(d × (n + b))
   d = number of digits (log_b(maxVal))
   b = base (10 for decimal, 256 for byte-level)
   n = number of elements

 FOR 32-bit INTEGERS with base 256:
   d = 4, b = 256 → O(4 × (n + 256)) = O(n) !!

 MSD RADIX SORT:
   Sort from most significant digit first.
   More complex (recursive, needs to handle variable-length digits).
   Used for strings (like trie-based sorting).

 HANDLING NEGATIVES:
   Option 1: Separate negative and positive, sort each, combine
   Option 2: Add offset to make all non-negative
   Option 3: Use signed-aware digit extraction
*/

// Version 1: LSD Radix Sort (non-negative integers)
void radixSort_LSD(vector<int>& arr) {
    if (arr.empty()) return;
    int maxVal = *max_element(arr.begin(), arr.end());

    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSort_byDigit(arr, exp);
    }
}

// Version 2: Radix Sort with base 256 (faster for large numbers)
void radixSort_base256(vector<int>& arr) {
    if (arr.empty()) return;
    int n = arr.size();

    for (int shift = 0; shift < 32; shift += 8) {
        vector<int> count(256, 0);
        vector<int> output(n);

        for (int i = 0; i < n; i++)
            count[(arr[i] >> shift) & 0xFF]++;

        for (int i = 1; i < 256; i++)
            count[i] += count[i - 1];

        for (int i = n - 1; i >= 0; i--) {
            int bucket = (arr[i] >> shift) & 0xFF;
            output[count[bucket] - 1] = arr[i];
            count[bucket]--;
        }

        arr = output;
    }
}

// Version 3: Radix Sort with negative number support
void radixSort_withNegatives(vector<int>& arr) {
    if (arr.empty()) return;

    // Separate negative and positive
    vector<int> neg, pos;
    for (int x : arr) {
        if (x < 0) neg.push_back(-x);
        else pos.push_back(x);
    }

    // Sort each group
    if (!pos.empty()) radixSort_LSD(pos);
    if (!neg.empty()) radixSort_LSD(neg);

    // Combine: reversed negatives + positives
    int idx = 0;
    for (int i = (int)neg.size() - 1; i >= 0; i--)
        arr[idx++] = -neg[i];
    for (int x : pos)
        arr[idx++] = x;
}

// Version 4: Radix Sort for strings (MSD approach, simplified)
void radixSort_strings(vector<string>& arr, int maxLen) {
    // Pad all strings to maxLen with null characters
    for (auto& s : arr) {
        while ((int)s.size() < maxLen) s += '\0';
    }

    // LSD radix sort on characters from right to left
    int n = arr.size();
    for (int d = maxLen - 1; d >= 0; d--) {
        // Counting sort by character at position d
        vector<int> count(257, 0); // 256 chars + 1
        vector<string> output(n);

        for (int i = 0; i < n; i++)
            count[(unsigned char)arr[i][d] + 1]++;

        for (int i = 1; i < 257; i++)
            count[i] += count[i - 1];

        for (int i = 0; i < n; i++) {
            int c = (unsigned char)arr[i][d];
            output[count[c]++] = arr[i];
        }

        arr = output;
    }

    // Remove padding
    for (auto& s : arr) {
        while (!s.empty() && s.back() == '\0') s.pop_back();
    }
}

void demo_radix_sort() {
    cout << "=== SECTION 2: RADIX SORT ===" << endl;

    // LSD Radix Sort
    vector<int> arr1 = {170, 45, 75, 90, 802, 24, 2, 66};
    radixSort_LSD(arr1);
    cout << "LSD Radix: ";
    for (int x : arr1) cout << x << " ";
    cout << endl;

    // With negatives
    vector<int> arr2 = {-5, 3, -1, 0, -3, 2, 1, 100, -100};
    radixSort_withNegatives(arr2);
    cout << "With negatives: ";
    for (int x : arr2) cout << x << " ";
    cout << endl;

    // String radix sort
    vector<string> strs = {"cat", "bat", "art", "car", "bar"};
    int maxLen = 0;
    for (auto& s : strs) maxLen = max(maxLen, (int)s.size());
    radixSort_strings(strs, maxLen);
    cout << "String radix: ";
    for (auto& s : strs) cout << s << " ";
    cout << endl;

    cout << "Time: O(d*(n+b)), d=digits, b=base" << endl;
    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: BUCKET SORT
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Bucket Sort divides elements into "buckets" based on their value,
 sorts each bucket individually, then concatenates.

 ALGORITHM:
   1. Create n empty buckets (or k buckets)
   2. Put each element into the appropriate bucket
   3. Sort each bucket (using insertion sort or any sort)
   4. Concatenate all buckets

 COMPLEXITY:
   Best/Average: O(n + k) when elements are uniformly distributed
   Worst: O(n²) when all elements go into one bucket
   Space: O(n + k)

 BUCKET ASSIGNMENT:
   For values in [0, 1): bucket_index = floor(n * value)
   For values in [minVal, maxVal]: bucket_index = floor(n * (val - minVal) / (maxVal - minVal))

 KEY INSIGHT:
   If data is uniformly distributed, each bucket has O(1) elements
   on average, so sorting each bucket is O(1), total = O(n).

 APPLICATIONS:
   • Sorting floating-point numbers in [0, 1)
   • External sorting (buckets = files)
   • Maximum Gap problem (LC 164)
*/

// Version 1: Bucket Sort for floats in [0, 1)
void bucketSort_float(vector<float>& arr) {
    int n = arr.size();
    if (n <= 1) return;

    vector<vector<float>> buckets(n);

    // Put elements into buckets
    for (float x : arr) {
        int idx = (int)(n * x);
        if (idx >= n) idx = n - 1;
        buckets[idx].push_back(x);
    }

    // Sort each bucket
    for (auto& bucket : buckets) {
        sort(bucket.begin(), bucket.end());
    }

    // Concatenate
    int idx = 0;
    for (auto& bucket : buckets) {
        for (float x : bucket) {
            arr[idx++] = x;
        }
    }
}

// Version 2: Bucket Sort for integers
void bucketSort_int(vector<int>& arr) {
    if (arr.empty()) return;
    int n = arr.size();
    int minVal = *min_element(arr.begin(), arr.end());
    int maxVal = *max_element(arr.begin(), arr.end());

    if (minVal == maxVal) return; // All same

    int bucketCount = n;
    double range = (double)(maxVal - minVal + 1) / bucketCount;
    vector<vector<int>> buckets(bucketCount);

    for (int x : arr) {
        int idx = (int)((x - minVal) / range);
        if (idx >= bucketCount) idx = bucketCount - 1;
        buckets[idx].push_back(x);
    }

    for (auto& bucket : buckets)
        sort(bucket.begin(), bucket.end());

    int idx = 0;
    for (auto& bucket : buckets)
        for (int x : bucket)
            arr[idx++] = x;
}

// Version 3: Maximum Gap using Bucket Sort concept (LC 164)
// Find the maximum difference between successive elements in sorted form
// Must be O(n) time and space
int maximumGap(vector<int>& nums) {
    int n = nums.size();
    if (n < 2) return 0;

    int minVal = *min_element(nums.begin(), nums.end());
    int maxVal = *max_element(nums.begin(), nums.end());
    if (minVal == maxVal) return 0;

    // Bucket size and count
    int bucketSize = max(1, (maxVal - minVal) / (n - 1));
    int bucketCount = (maxVal - minVal) / bucketSize + 1;

    vector<int> bucketMin(bucketCount, INT_MAX);
    vector<int> bucketMax(bucketCount, INT_MIN);
    vector<bool> used(bucketCount, false);

    for (int x : nums) {
        int idx = (x - minVal) / bucketSize;
        used[idx] = true;
        bucketMin[idx] = min(bucketMin[idx], x);
        bucketMax[idx] = max(bucketMax[idx], x);
    }

    // Max gap is between consecutive non-empty buckets
    int maxGap = 0;
    int prevMax = minVal;
    for (int i = 0; i < bucketCount; i++) {
        if (!used[i]) continue;
        maxGap = max(maxGap, bucketMin[i] - prevMax);
        prevMax = bucketMax[i];
    }

    return maxGap;
}

void demo_bucket_sort() {
    cout << "=== SECTION 3: BUCKET SORT ===" << endl;

    // Float bucket sort
    vector<float> arr1 = {0.897f, 0.565f, 0.656f, 0.1234f, 0.665f, 0.3434f};
    bucketSort_float(arr1);
    cout << "Float: ";
    for (float x : arr1) printf("%.3f ", x);
    cout << endl;

    // Integer bucket sort
    vector<int> arr2 = {54, 12, 84, 3, 67, 29, 41, 95};
    bucketSort_int(arr2);
    cout << "Integer: ";
    for (int x : arr2) cout << x << " ";
    cout << endl;

    // Maximum Gap
    vector<int> arr3 = {3, 6, 9, 1};
    cout << "Max Gap of {3,6,9,1}: " << maximumGap(arr3) << endl; // 3

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: COORDINATE COMPRESSION
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Coordinate Compression maps a set of values to a smaller, contiguous
 range [0, k-1] while preserving relative order.

 WHY NEEDED:
   • Values can be up to 10^9 but count is ≤ 10^5
   • We need to use values as array indices
   • Required for BIT/Fenwick Tree, Segment Tree on values
   • Required for counting sort when range is large but count is small

 ALGORITHM:
   1. Copy all values to a temporary array
   2. Sort the temporary array
   3. Remove duplicates (unique)
   4. For each original value, find its compressed index
      using binary search (lower_bound)

 EXAMPLE:
   Original:   [100, 5, 200, 5, 1000]
   Sorted unique: [5, 100, 200, 1000]
   Compressed: [1, 0, 2, 0, 3]

 COMPLEXITY: O(n log n) for sorting + O(n log n) for binary searches

 APPLICATIONS:
   • BIT-based inversion counting
   • Segment tree on value range
   • Sweep line algorithms
   • Many CP problems with large coordinates
*/

// Version 1: Basic Coordinate Compression
vector<int> coordinateCompress(vector<int>& arr) {
    int n = arr.size();
    vector<int> sorted_unique = arr;
    sort(sorted_unique.begin(), sorted_unique.end());
    sorted_unique.erase(unique(sorted_unique.begin(), sorted_unique.end()), sorted_unique.end());

    vector<int> compressed(n);
    for (int i = 0; i < n; i++) {
        compressed[i] = lower_bound(sorted_unique.begin(), sorted_unique.end(), arr[i])
                        - sorted_unique.begin();
    }
    return compressed;
}

// Version 2: Coordinate Compression using map (preserves mapping)
pair<vector<int>, map<int, int>> coordinateCompress_map(vector<int>& arr) {
    map<int, int> compress_map;
    vector<int> sorted_unique = arr;
    sort(sorted_unique.begin(), sorted_unique.end());
    sorted_unique.erase(unique(sorted_unique.begin(), sorted_unique.end()), sorted_unique.end());

    for (int i = 0; i < (int)sorted_unique.size(); i++) {
        compress_map[sorted_unique[i]] = i;
    }

    vector<int> compressed(arr.size());
    for (int i = 0; i < (int)arr.size(); i++) {
        compressed[i] = compress_map[arr[i]];
    }
    return {compressed, compress_map};
}

// Version 3: Coordinate Compression with decompression support
struct CoordCompressor {
    vector<int> sorted_vals;

    void build(vector<int>& vals) {
        sorted_vals = vals;
        sort(sorted_vals.begin(), sorted_vals.end());
        sorted_vals.erase(unique(sorted_vals.begin(), sorted_vals.end()), sorted_vals.end());
    }

    int compress(int val) {
        return lower_bound(sorted_vals.begin(), sorted_vals.end(), val) - sorted_vals.begin();
    }

    int decompress(int idx) {
        return sorted_vals[idx];
    }

    int size() { return sorted_vals.size(); }
};

void demo_coordinate_compression() {
    cout << "=== SECTION 4: COORDINATE COMPRESSION ===" << endl;

    vector<int> arr = {100, 5, 200, 5, 1000, 100};
    cout << "Original: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    // Basic compression
    vector<int> comp = coordinateCompress(arr);
    cout << "Compressed: ";
    for (int x : comp) cout << x << " ";
    cout << endl;

    // With compressor object
    CoordCompressor cc;
    cc.build(arr);
    cout << "Compressor: ";
    for (int x : arr) cout << cc.compress(x) << " ";
    cout << endl;
    cout << "Decompress 2 → " << cc.decompress(2) << endl;
    cout << "Unique values: " << cc.size() << endl;

    // Application: Use compressed values as array indices
    // Count inversions using BIT after compression
    cout << "Now values fit in array of size " << cc.size()
         << " instead of " << *max_element(arr.begin(), arr.end()) + 1 << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: FREQUENCY SORT
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Sort elements by their frequency of occurrence.

 VARIATIONS:
   1. Sort by frequency (descending), tiebreak by value (ascending)
   2. Sort by frequency (ascending), tiebreak by first occurrence
   3. Elements with same frequency maintain their order (stable)

 APPROACH 1: Count frequency + custom sort
 APPROACH 2: Count frequency + counting sort by frequency
 APPROACH 3: Count frequency + bucket by frequency

 PROBLEMS:
   • LC 451: Sort Characters By Frequency
   • LC 1636: Sort Array by Increasing Frequency
   • CF various problems
*/

// Version 1: Frequency Sort using custom comparator
void frequencySort_desc(vector<int>& arr) {
    unordered_map<int, int> freq;
    for (int x : arr) freq[x]++;

    sort(arr.begin(), arr.end(), [&](int a, int b) {
        if (freq[a] != freq[b]) return freq[a] > freq[b]; // Higher freq first
        return a < b; // Tiebreak: smaller value first
    });
}

// Version 2: Frequency Sort ascending (LC 1636)
void frequencySort_asc(vector<int>& arr) {
    unordered_map<int, int> freq;
    for (int x : arr) freq[x]++;

    sort(arr.begin(), arr.end(), [&](int a, int b) {
        if (freq[a] != freq[b]) return freq[a] < freq[b]; // Lower freq first
        return a > b; // Tiebreak: larger value first
    });
}

// Version 3: Frequency Sort preserving first occurrence order
void frequencySort_stable(vector<int>& arr) {
    unordered_map<int, int> freq, firstOccurrence;
    for (int i = 0; i < (int)arr.size(); i++) {
        freq[arr[i]]++;
        if (firstOccurrence.find(arr[i]) == firstOccurrence.end())
            firstOccurrence[arr[i]] = i;
    }

    stable_sort(arr.begin(), arr.end(), [&](int a, int b) {
        if (freq[a] != freq[b]) return freq[a] > freq[b];
        return firstOccurrence[a] < firstOccurrence[b];
    });
}

// Version 4: Frequency Sort using bucket technique (O(n) if values small)
vector<int> frequencySort_bucket(vector<int>& arr) {
    unordered_map<int, int> freq;
    for (int x : arr) freq[x]++;

    int maxFreq = 0;
    for (auto& [val, f] : freq) maxFreq = max(maxFreq, f);

    // Bucket by frequency
    vector<vector<int>> buckets(maxFreq + 1);
    for (auto& [val, f] : freq) {
        buckets[f].push_back(val);
    }

    vector<int> result;
    for (int f = maxFreq; f >= 1; f--) {
        sort(buckets[f].begin(), buckets[f].end());
        for (int val : buckets[f]) {
            for (int i = 0; i < f; i++) {
                result.push_back(val);
            }
        }
    }
    return result;
}

// Version 5: Sort Characters By Frequency (LC 451)
string sortCharsByFrequency(string s) {
    vector<int> freq(128, 0);
    for (char c : s) freq[c]++;

    // Create pairs and sort
    vector<pair<int, char>> pairs;
    for (int i = 0; i < 128; i++) {
        if (freq[i] > 0) pairs.push_back({freq[i], (char)i});
    }
    sort(pairs.rbegin(), pairs.rend());

    string result;
    for (auto& [f, c] : pairs) {
        result += string(f, c);
    }
    return result;
}

void demo_frequency_sort() {
    cout << "=== SECTION 5: FREQUENCY SORT ===" << endl;

    vector<int> arr1 = {1, 1, 1, 2, 2, 3};
    frequencySort_desc(arr1);
    cout << "Freq desc: ";
    for (int x : arr1) cout << x << " ";
    cout << endl;

    vector<int> arr2 = {1, 1, 2, 2, 2, 3};
    frequencySort_asc(arr2);
    cout << "Freq asc: ";
    for (int x : arr2) cout << x << " ";
    cout << endl;

    vector<int> arr3 = {2, 3, 1, 3, 2};
    vector<int> bucketed = frequencySort_bucket(arr3);
    cout << "Bucket freq: ";
    for (int x : bucketed) cout << x << " ";
    cout << endl;

    string s = "tree";
    cout << "Char freq sort: " << sortCharsByFrequency(s) << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 6: SORTING SMALL RANGE VALUES
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 When values have a SMALL RANGE, specialized techniques are faster:

 1. DUTCH NATIONAL FLAG (3 values):
    Sort array with only 0, 1, 2 in O(n) time, O(1) space
    → LC 75: Sort Colors

 2. COUNTING SORT for small k:
    When k ≤ 100, counting sort is practically O(n)

 3. BOOLEAN SORT (2 values):
    Partition into two groups → O(n), O(1) space
    → Even/Odd partition, Positive/Negative partition

 4. K-WAY PARTITION:
    Generalization of Dutch National Flag for k values

 CP TRICKS:
   • If values ∈ {0, 1}: simple counting or partition
   • If values ∈ {0, 1, 2}: Dutch National Flag
   • If values ∈ [0, k] where k small: counting sort
   • If values ∈ [0, 10^9] but only n values: coordinate compression
*/

// Dutch National Flag: Sort 0s, 1s, 2s
void sortColors(vector<int>& nums) {
    int lo = 0, mid = 0, hi = (int)nums.size() - 1;
    while (mid <= hi) {
        if (nums[mid] == 0) {
            swap(nums[lo], nums[mid]);
            lo++;
            mid++;
        } else if (nums[mid] == 1) {
            mid++;
        } else { // nums[mid] == 2
            swap(nums[mid], nums[hi]);
            hi--;
        }
    }
}

// Boolean partition: Separate even and odd
void partitionEvenOdd(vector<int>& arr) {
    int lo = 0, hi = (int)arr.size() - 1;
    while (lo < hi) {
        while (lo < hi && arr[lo] % 2 == 0) lo++;
        while (lo < hi && arr[hi] % 2 == 1) hi--;
        if (lo < hi) swap(arr[lo], arr[hi]);
    }
}

// Sort array with values in small range [0, k]
void sortSmallRange(vector<int>& arr, int k) {
    vector<int> count(k + 1, 0);
    for (int x : arr) count[x]++;
    int idx = 0;
    for (int i = 0; i <= k; i++)
        while (count[i]-- > 0) arr[idx++] = i;
}

// Move all zeros to end (maintaining relative order of non-zeros)
void moveZerosToEnd(vector<int>& arr) {
    int writeIdx = 0;
    for (int i = 0; i < (int)arr.size(); i++) {
        if (arr[i] != 0) {
            arr[writeIdx++] = arr[i];
        }
    }
    while (writeIdx < (int)arr.size()) arr[writeIdx++] = 0;
}

// Segregate 0s and 1s
void segregate01(vector<int>& arr) {
    int lo = 0, hi = (int)arr.size() - 1;
    while (lo < hi) {
        while (lo < hi && arr[lo] == 0) lo++;
        while (lo < hi && arr[hi] == 1) hi--;
        if (lo < hi) swap(arr[lo++], arr[hi--]);
    }
}

void demo_small_range() {
    cout << "=== SECTION 6: SMALL RANGE SORTING ===" << endl;

    // Dutch National Flag
    vector<int> colors = {2, 0, 2, 1, 1, 0};
    sortColors(colors);
    cout << "Sort Colors: ";
    for (int x : colors) cout << x << " ";
    cout << endl;

    // Even/Odd partition
    vector<int> arr1 = {1, 2, 3, 4, 5, 6, 7, 8};
    partitionEvenOdd(arr1);
    cout << "Even|Odd: ";
    for (int x : arr1) cout << x << " ";
    cout << endl;

    // Small range
    vector<int> arr2 = {3, 0, 1, 2, 0, 3, 1, 2, 0};
    sortSmallRange(arr2, 3);
    cout << "Small range [0,3]: ";
    for (int x : arr2) cout << x << " ";
    cout << endl;

    // Move zeros
    vector<int> arr3 = {0, 1, 0, 3, 12};
    moveZerosToEnd(arr3);
    cout << "Move zeros: ";
    for (int x : arr3) cout << x << " ";
    cout << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║   CHAPTER 04: NON-COMPARISON SORTING                        ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << endl;

    demo_counting_sort();
    demo_radix_sort();
    demo_bucket_sort();
    demo_coordinate_compression();
    demo_frequency_sort();
    demo_small_range();

    cout << "═══════════════════════════════════════════════════════════════" << endl;
    cout << "All Chapter 04 demos completed successfully!" << endl;

    return 0;
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                         PRACTICE PROBLEMS                                  ║
╠══════════════════════════════════════════════════════════════════════════════╣
║                                                                            ║
║  🟢 EASY:                                                                  ║
║  1. Sort Colors (LC 75) — Dutch National Flag                              ║
║  2. Relative Sort Array (LC 1122)                                          ║
║  3. Sort Array by Increasing Frequency (LC 1636)                           ║
║  4. Move Zeroes (LC 283)                                                   ║
║                                                                            ║
║  🟡 MEDIUM:                                                                ║
║  5. Sort Characters By Frequency (LC 451)                                  ║
║  6. Maximum Gap (LC 164) — Bucket Sort / Pigeonhole                        ║
║  7. Top K Frequent Elements (LC 347) — Frequency + Bucket                  ║
║  8. H-Index (LC 274) — Counting Sort                                       ║
║  9. CF 1353D — Constructing the Array                                      ║
║                                                                            ║
║  🔴 HARD:                                                                  ║
║ 10. CSES — Distinct Numbers (coordinate compression concept)               ║
║ 11. CF 1312D — Count the Arrays                                            ║
║ 12. Suffix Array construction via Radix Sort                               ║
║ 13. CF 1551D — Domino (frequency analysis)                                 ║
║                                                                            ║
║  🔵 GRANDMASTER:                                                           ║
║ 14. Suffix Array in O(n log n) using Radix Sort                            ║
║ 15. Coordinate Compression + BIT for inversion counting                    ║
║ 16. CF 1523E — Crypto Investor (radix-based technique)                     ║
║                                                                            ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

