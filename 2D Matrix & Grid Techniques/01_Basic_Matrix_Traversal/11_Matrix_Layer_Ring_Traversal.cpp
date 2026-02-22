/*
 * ============================================================================
 *         MATRIX LAYER / RING TRAVERSAL - ZERO TO GM MASTERY
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Topic   : Ring-by-Ring Traversal, Layer Rotation, Ring Operations
 * Level   : 0 (Beginner) → 5 (GM)
 * ============================================================================
 *
 *  TABLE OF CONTENTS
 *  ─────────────────
 *  Level 0 : Understanding Layers/Rings
 *  Level 1 : Print Matrix Ring by Ring
 *  Level 2 : Extract Ring Elements
 *  Level 3 : Rotate Matrix Ring by K positions
 *  Level 4 : Ring Sum, Ring Max/Min
 *  Level 5 : Reconstruct Matrix from Rings
 *
 * ============================================================================
 *  WHAT IS A RING/LAYER?
 *  ─────────────────────
 *  Ring k = all elements at distance k from the border
 *
 *  For 5×5 matrix:
 *  Ring 0 (outermost):
 *  [0][0][0][0][0]
 *  [0]            [0]
 *  [0]            [0]
 *  [0]            [0]
 *  [0][0][0][0][0]
 *
 *  Ring 1:
 *           [1][1][1]
 *           [1]   [1]
 *           [1][1][1]
 *
 *  Ring 2 (center):
 *              [2]
 *
 *  Layer index: min(i, j, N-1-i, M-1-j)
 *  Total rings = ceil(min(N, M) / 2)
 *
 *  Related Problems:
 *  - LC #1914: Cyclically Rotating a Grid
 * ============================================================================
 *  Time Complexity: O(N × M) per full ring traversal
 *  Space Complexity: O(N + M) per ring extraction
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

void printMatrix(const vector<vector<int>>& mat, const string& title = "") {
    if (!title.empty()) cout << "--- " << title << " ---" << endl;
    for (const auto& row : mat) {
        for (int val : row) cout << setw(4) << val;
        cout << "\n";
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 0: UNDERSTANDING LAYERS
// ─────────────────────────────────────────────────────────────────────────────
void layerVisualization(int n, int m) {
    cout << "=== Layer Visualization " << n << "x" << m << " ===" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int layer = min({i, j, n - 1 - i, m - 1 - j});
            cout << setw(3) << layer;
        }
        cout << "\n";
    }
    int totalRings = (min(n, m) + 1) / 2;
    cout << "Total rings: " << totalRings << "\n\n";
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 1: PRINT MATRIX RING BY RING
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  For each ring k, traverse in clockwise order:
 *  1. Top row:    left → right
 *  2. Right col:  top+1 → bottom
 *  3. Bottom row: right-1 → left  (if top != bottom)
 *  4. Left col:   bottom-1 → top+1  (if left != right)
 */
vector<int> extractRing(const vector<vector<int>>& mat, int ring) {
    int n = mat.size(), m = mat[0].size();
    int top = ring, bottom = n - 1 - ring;
    int left = ring, right = m - 1 - ring;
    vector<int> elements;

    if (top > bottom || left > right) return elements;

    // Top row
    for (int j = left; j <= right; j++)
        elements.push_back(mat[top][j]);

    // Right column
    for (int i = top + 1; i <= bottom; i++)
        elements.push_back(mat[i][right]);

    // Bottom row (if exists)
    if (top < bottom) {
        for (int j = right - 1; j >= left; j--)
            elements.push_back(mat[bottom][j]);
    }

    // Left column (if exists)
    if (left < right) {
        for (int i = bottom - 1; i > top; i--)
            elements.push_back(mat[i][left]);
    }

    return elements;
}

void printRingByRing(const vector<vector<int>>& mat) {
    cout << "=== Ring by Ring Traversal ===" << endl;
    int n = mat.size(), m = mat[0].size();
    int totalRings = (min(n, m) + 1) / 2;

    for (int ring = 0; ring < totalRings; ring++) {
        auto elements = extractRing(mat, ring);
        cout << "Ring " << ring << ": ";
        for (int x : elements) cout << x << " ";
        cout << "(size = " << elements.size() << ")" << endl;
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 2: PLACE RING ELEMENTS BACK
// ─────────────────────────────────────────────────────────────────────────────
void placeRing(vector<vector<int>>& mat, int ring, const vector<int>& elements) {
    int n = mat.size(), m = mat[0].size();
    int top = ring, bottom = n - 1 - ring;
    int left = ring, right = m - 1 - ring;
    int idx = 0;

    // Top row
    for (int j = left; j <= right; j++)
        mat[top][j] = elements[idx++];

    // Right column
    for (int i = top + 1; i <= bottom; i++)
        mat[i][right] = elements[idx++];

    // Bottom row
    if (top < bottom) {
        for (int j = right - 1; j >= left; j--)
            mat[bottom][j] = elements[idx++];
    }

    // Left column
    if (left < right) {
        for (int i = bottom - 1; i > top; i--)
            mat[i][left] = elements[idx++];
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 3: ROTATE RING BY K POSITIONS — LC #1914
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Cyclically rotate each ring by k positions.
 *
 *  Algorithm:
 *  1. Extract ring elements
 *  2. Rotate the 1D array by k positions
 *  3. Place elements back
 *
 *  LC #1914: Cyclically Rotating a Grid
 *  Time: O(N×M), Space: O(N+M) per ring
 */
void rotateRing(vector<vector<int>>& mat, int ring, int k) {
    auto elements = extractRing(mat, ring);
    int sz = elements.size();
    if (sz == 0) return;

    k = ((k % sz) + sz) % sz; // Normalize
    rotate(elements.begin(), elements.begin() + k, elements.end());
    placeRing(mat, ring, elements);
}

void rotateAllRings(vector<vector<int>>& mat, int k) {
    cout << "=== Rotate All Rings by " << k << " ===" << endl;
    printMatrix(mat, "Before Rotation");

    int n = mat.size(), m = mat[0].size();
    int totalRings = (min(n, m) + 1) / 2;

    for (int ring = 0; ring < totalRings; ring++)
        rotateRing(mat, ring, k);

    printMatrix(mat, "After Rotation");
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 4: RING AGGREGATION (SUM, MAX, MIN)
// ─────────────────────────────────────────────────────────────────────────────
void ringAggregation(const vector<vector<int>>& mat) {
    cout << "=== Ring Aggregation ===" << endl;
    int n = mat.size(), m = mat[0].size();
    int totalRings = (min(n, m) + 1) / 2;

    for (int ring = 0; ring < totalRings; ring++) {
        auto elements = extractRing(mat, ring);
        if (elements.empty()) continue;

        int sum = accumulate(elements.begin(), elements.end(), 0);
        int mx = *max_element(elements.begin(), elements.end());
        int mn = *min_element(elements.begin(), elements.end());
        double avg = (double)sum / elements.size();

        cout << "Ring " << ring << ": sum=" << sum
             << ", max=" << mx << ", min=" << mn
             << ", avg=" << fixed << setprecision(1) << avg
             << ", size=" << elements.size() << endl;
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 5: BUILD MATRIX FROM CONCENTRIC RINGS
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Given a 1D array, fill matrix in ring-by-ring spiral order.
 *  This is essentially "Spiral Matrix II" done ring by ring.
 */
vector<vector<int>> buildFromRings(int n, int m) {
    cout << "=== Build Matrix from Rings " << n << "x" << m << " ===" << endl;
    vector<vector<int>> mat(n, vector<int>(m, 0));
    int val = 1;
    int totalRings = (min(n, m) + 1) / 2;

    for (int ring = 0; ring < totalRings; ring++) {
        int top = ring, bottom = n - 1 - ring;
        int left = ring, right = m - 1 - ring;

        // Calculate ring size
        vector<int> elements;
        // Top
        for (int j = left; j <= right; j++) elements.push_back(val++);
        // Right
        for (int i = top + 1; i <= bottom; i++) elements.push_back(val++);
        // Bottom
        if (top < bottom)
            for (int j = right - 1; j >= left; j--) elements.push_back(val++);
        // Left
        if (left < right)
            for (int i = bottom - 1; i > top; i--) elements.push_back(val++);

        placeRing(mat, ring, elements);
    }

    printMatrix(mat);
    return mat;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 5B: ANTI-CLOCKWISE RING ROTATION
// ─────────────────────────────────────────────────────────────────────────────
void rotateRingAntiClockwise(vector<vector<int>>& mat, int ring, int k) {
    auto elements = extractRing(mat, ring);
    int sz = elements.size();
    if (sz == 0) return;

    // Anti-clockwise rotation = clockwise by (sz - k)
    k = ((k % sz) + sz) % sz;
    rotate(elements.begin(), elements.end() - k, elements.end());
    placeRing(mat, ring, elements);
}

void rotateAllRingsAntiCW(vector<vector<int>>& mat, int k) {
    cout << "=== Rotate All Rings Anti-CW by " << k << " ===" << endl;
    printMatrix(mat, "Before");

    int n = mat.size(), m = mat[0].size();
    int totalRings = (min(n, m) + 1) / 2;

    for (int ring = 0; ring < totalRings; ring++)
        rotateRingAntiClockwise(mat, ring, k);

    printMatrix(mat, "After Anti-CW Rotation");
}

// ─────────────────────────────────────────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   LAYER/RING TRAVERSAL - ZERO TO GM MASTERY     ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;
    cout << endl;

    // Level 0: Layer Visualization
    layerVisualization(5, 5);
    layerVisualization(4, 6);

    // Level 1: Ring by Ring
    vector<vector<int>> mat = {
        {1,  2,  3,  4,  5},
        {6,  7,  8,  9,  10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}
    };
    printMatrix(mat, "Original 5x5 Matrix");
    printRingByRing(mat);

    // Rectangular
    vector<vector<int>> rect = {
        {1,  2,  3,  4,  5,  6},
        {7,  8,  9,  10, 11, 12},
        {13, 14, 15, 16, 17, 18},
        {19, 20, 21, 22, 23, 24}
    };
    printMatrix(rect, "Original 4x6 Matrix");
    printRingByRing(rect);

    // Level 3: Rotate Rings
    vector<vector<int>> mat3 = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9,  10, 11, 12},
        {13, 14, 15, 16}
    };
    rotateAllRings(mat3, 2);

    // Level 4: Ring Aggregation
    ringAggregation(mat);

    // Level 5: Build from Rings
    buildFromRings(4, 4);
    buildFromRings(3, 5);

    // Level 5B: Anti-CW Rotation
    vector<vector<int>> mat5 = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    rotateAllRingsAntiCW(mat5, 1);

    return 0;
}

