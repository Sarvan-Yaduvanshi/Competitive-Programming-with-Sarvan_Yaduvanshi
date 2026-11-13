//
// Created by Sarvan Yaduvanshi on 12/11/26.
//

#define COMPETITIVE_PROGRAMMING_WITH_SARVAN_YADUVANSHI_04_PRINTNARYTREE_H
#define COMPETITIVE_PROGRAMMING_WITH_SARVAN_YADUVANSHI_04_PRINTNARYTREE_H

//
// N-ary tree visualization, same style as binary PrintTree.h
//
// Node needs:  int val  and  std::vector<Node*> children
//

#pragma once

#include <algorithm>
#include <array>
#include <climits>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace N_ary_TreeVisualization {

namespace detail {

using Canvas = std::vector<std::vector<std::string>>;

constexpr int EDGE_ROWS  = 2;   // height of every edge (rows between two levels)
constexpr int MIN_SPACES = 2;   // min spaces between two neighbours on same row

// ==========================================
// 1. NODE VALUE -> TEXT
// ==========================================

template <typename Value>
std::string makeLabel(const Value& value) {
    std::ostringstream out;
    out << '(' << value << ')';
    return out.str();
}

inline int leftSpan(const std::string& s)  { return (static_cast<int>(s.size()) - 1) / 2; }
inline int rightSpan(const std::string& s) { return static_cast<int>(s.size()) - 1 - leftSpan(s); }

// ==========================================
// 2. EDGE SHAPE (relative to parent center)
// ==========================================
//
// Left child : 45 degree '/' chain, last '/' sits above child's right corner.
// Right child: 45 degree '\' chain, last '\' sits above child's left corner.
// Middle     : straight '|'.
// If child is far away, chain is clamped next to parent and the rest of the
// distance is drawn as '_' on parent's label row (same as binary printer).

using EdgeCols = std::array<int, EDGE_ROWS>;

inline EdgeCols edgeCols(int dx, const std::string& childLabel) {
    EdgeCols cols{};

    if (dx < 0) {
        const int land = dx + rightSpan(childLabel);
        for (int k = 1; k <= EDGE_ROWS; k++)
            cols[k - 1] = std::min(land + (EDGE_ROWS - k), -1);
    }
    else if (dx > 0) {
        const int land = dx - leftSpan(childLabel);
        for (int k = 1; k <= EDGE_ROWS; k++)
            cols[k - 1] = std::max(land - (EDGE_ROWS - k), 1);
    }
    else {
        cols.fill(0);
    }

    return cols;
}

inline char edgeChar(const EdgeCols& cols, int k, int dx) {
    if (dx == 0)
        return '|';

    int move;
    if (k + 1 < EDGE_ROWS)      move = cols[k + 1] - cols[k];
    else if (EDGE_ROWS > 1)     move = cols[k] - cols[k - 1];
    else                        move = dx;

    if (move == 0)
        return '|';

    return move < 0 ? '/' : '\\';
}

// ==========================================
// 3. LAYOUT (contour based, no overlap)
// ==========================================
//
// offsets[node][i] = x of child i relative to node.
// Children are placed left to right, each one as close as possible to the
// already placed ones (compared level by level). All distances are even, so
// parent is exactly centered over first and last child.
// Contour row 0 of a node also covers its '_' runs, so neighbours keep
// MIN_SPACES away from them.

struct Contour {
    std::vector<int> lo;   // leftmost column per relative depth
    std::vector<int> hi;   // rightmost column per relative depth
};

template <typename Node>
using Offsets = std::unordered_map<const Node*, std::vector<int>>;

template <typename Node>
Contour layout(const Node* root, Offsets<Node>& offsets) {
    Contour c;

    const std::string label = makeLabel(root->val);
    c.lo.push_back(-leftSpan(label));
    c.hi.push_back(rightSpan(label));

    const size_t n = root->children.size();
    if (n == 0)
        return c;

    std::vector<int> pos(n, 0);
    std::vector<Contour> subs(n);
    Contour acc;   // merged contour of already placed children

    for (size_t i = 0; i < n; i++) {
        subs[i] = layout<Node>(root->children[i], offsets);
        const Contour& sub = subs[i];

        if (i > 0) {
            int p = INT_MIN;
            const size_t common = std::min(acc.hi.size(), sub.lo.size());

            for (size_t k = 0; k < common; k++)
                p = std::max(p, acc.hi[k] - sub.lo[k] + MIN_SPACES + 1);

            if (p % 2 != 0)
                p++;

            pos[i] = p;
        }

        if (acc.lo.size() < sub.lo.size()) {
            acc.lo.resize(sub.lo.size(), INT_MAX);
            acc.hi.resize(sub.hi.size(), INT_MIN);
        }

        for (size_t k = 0; k < sub.lo.size(); k++) {
            acc.lo[k] = std::min(acc.lo[k], sub.lo[k] + pos[i]);
            acc.hi[k] = std::max(acc.hi[k], sub.hi[k] + pos[i]);
        }
    }

    // Side children need room for a full diagonal edge (EDGE_ROWS slashes).
    // Widen all gaps evenly until every side child is far enough from parent.
    std::vector<int> base = pos;
    int delta = 0;
    int mid = 0;

    while (true) {
        for (size_t i = 0; i < n; i++)
            pos[i] = base[i] + static_cast<int>(i) * delta;

        mid = (pos.front() + pos.back()) / 2;

        bool ok = true;
        for (size_t i = 0; i < n && ok; i++) {
            if (2 * i + 1 == n)   // exact middle child never moves with delta
                continue;

            const int dx = pos[i] - mid;
            const std::string cl = makeLabel(root->children[i]->val);

            if (dx < 0 && dx + rightSpan(cl) > -EDGE_ROWS) ok = false;
            if (dx > 0 && dx - leftSpan(cl)  <  EDGE_ROWS) ok = false;
        }

        if (ok || n == 1 || delta > 60)
            break;

        delta += 2;
    }

    // rebuild merged contour with final positions
    acc = Contour();
    for (size_t i = 0; i < n; i++) {
        const Contour& sub = subs[i];

        if (acc.lo.size() < sub.lo.size()) {
            acc.lo.resize(sub.lo.size(), INT_MAX);
            acc.hi.resize(sub.hi.size(), INT_MIN);
        }

        for (size_t k = 0; k < sub.lo.size(); k++) {
            acc.lo[k] = std::min(acc.lo[k], sub.lo[k] + pos[i]);
            acc.hi[k] = std::max(acc.hi[k], sub.hi[k] + pos[i]);
        }
    }

    std::vector<int> off(n);
    for (size_t i = 0; i < n; i++)
        off[i] = pos[i] - mid;
    offsets[root] = off;

    // '_' runs on this node's own row
    int runLo = c.lo[0];
    int runHi = c.hi[0];

    for (size_t i = 0; i < n; i++) {
        const EdgeCols cols = edgeCols(off[i], makeLabel(root->children[i]->val));
        runLo = std::min(runLo, cols[0]);
        runHi = std::max(runHi, cols[0]);
    }

    c.lo[0] = runLo;
    c.hi[0] = runHi;

    for (size_t k = 0; k < acc.lo.size(); k++) {
        c.lo.push_back(acc.lo[k] - mid);
        c.hi.push_back(acc.hi[k] - mid);
    }

    return c;
}

template <typename Node>
int heightOf(const Node* root) {
    int h = 0;
    for (const Node* child : root->children)
        h = std::max(h, heightOf<Node>(child));
    return h + 1;
}

// ==========================================
// 4. DRAW
// ==========================================

template <typename Node>
void draw(
    const Node* root,
    int depth,
    int x,
    const Offsets<Node>& offsets,
    Canvas& canvas
) {
    const int row = depth * (EDGE_ROWS + 1);

    const std::string label = makeLabel(root->val);
    const int start = x - leftSpan(label);
    const int end   = x + rightSpan(label);

    for (size_t i = 0; i < label.size(); i++)
        canvas[row][start + static_cast<int>(i)] = std::string(1, label[i]);

    if (root->children.empty())
        return;

    const std::vector<int>& off = offsets.at(root);

    for (size_t i = 0; i < root->children.size(); i++) {
        const int dx = off[i];
        const EdgeCols cols = edgeCols(dx, makeLabel(root->children[i]->val));

        // '_' run only when at least 2 long (a single '_' next to label looks like noise)
        if (dx < 0 && x + cols[0] < start - 1)
            for (int c = x + cols[0]; c < start; c++)
                canvas[row][c] = "_";
        else if (dx > 0 && x + cols[0] > end + 1)
            for (int c = end + 1; c <= x + cols[0]; c++)
                canvas[row][c] = "_";

        for (int k = 0; k < EDGE_ROWS; k++)
            canvas[row + 1 + k][x + cols[k]] = std::string(1, edgeChar(cols, k, dx));
    }

    for (size_t i = 0; i < root->children.size(); i++)
        draw<Node>(root->children[i], depth + 1, x + off[i], offsets, canvas);
}

// ==========================================
// 5. FALLBACK: OUTLINE PRINT (ANY SIZE TREE)
// ==========================================

template <typename Node>
void printOutline(const Node* root, int depth) {
    std::cout << std::string(depth * 4, ' ') << makeLabel(root->val) << '\n';
    for (const Node* child : root->children)
        printOutline<Node>(child, depth + 1);
}

} // namespace detail


// ==========================================
// 6. PUBLIC PRINT FUNCTION
// ==========================================

template <typename Node>
void printNAryTree(
    Node* root,
    const std::string& title = "N-ARY TREE",
    int maxWidth = 160
) {
    std::cout << "\n========== " << title << " ==========\n\n";

    if (!root) {
        std::cout << "(empty tree)\n\n";
        return;
    }

    detail::Offsets<Node> offsets;
    const detail::Contour rc = detail::layout<Node>(root, offsets);

    const int minX = *std::min_element(rc.lo.begin(), rc.lo.end());
    const int maxX = *std::max_element(rc.hi.begin(), rc.hi.end());

    const long long width = static_cast<long long>(maxX) - minX + 1;

    if (width > maxWidth) {
        std::cout << "(tree too wide, printing as outline)\n\n";
        detail::printOutline<Node>(root, 0);
        std::cout << '\n';
        return;
    }

    const int height = detail::heightOf<Node>(root);

    detail::Canvas canvas(
        (height - 1) * (detail::EDGE_ROWS + 1) + 1,
        std::vector<std::string>(static_cast<size_t>(width) + 1, " ")
    );

    detail::draw<Node>(root, 0, -minX, offsets, canvas);

    for (const auto& row : canvas) {
        std::string line;

        for (const auto& cell : row)
            line += cell;

        while (!line.empty() && line.back() == ' ')
            line.pop_back();

        std::cout << line << '\n';
    }

    std::cout << '\n';
}

} // namespace N_ary_TreeVisualization