//
// Created by Sarvan Yaduvanshi on 11/11/26.
//

#ifndef COMPETITIVE_PROGRAMMING_WITH_SARVAN_YADUVANSHI_PRINTTREE_H
#define COMPETITIVE_PROGRAMMING_WITH_SARVAN_YADUVANSHI_PRINTTREE_H

#endif //COMPETITIVE_PROGRAMMING_WITH_SARVAN_YADUVANSHI_PRINTTREE_H

#pragma once

#include <algorithm>
#include <climits>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace TreeVisualization {

namespace detail {

using Canvas = std::vector<std::vector<std::string>>;

// Max height of one edge (in rows). Extra horizontal distance is drawn as '_'
// on the parent's label row, so big trees do not get very tall edges.
constexpr int MAX_SLASH_ROWS = 3;

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
// 2. TREE MEASUREMENTS
// ==========================================

template <typename Node>
void collectByDepth(const Node* root, int depth, std::vector<std::vector<const Node*>>& levels) {
    if (!root)
        return;

    if (static_cast<int>(levels.size()) <= depth)
        levels.resize(depth + 1);

    levels[depth].push_back(root);
    collectByDepth(root->left,  depth + 1, levels);
    collectByDepth(root->right, depth + 1, levels);
}

// ==========================================
// 3. HORIZONTAL DISTANCE PER LEVEL
// ==========================================
//
// step[d] = distance from a node at depth d to each of its children (x -/+ step[d]).
// Same step for the whole level -> parent is always exactly centered over two children.
// step[] is computed bottom-up: smallest value that keeps subtrees apart.

struct Contour {
    std::vector<int> lo;   // leftmost column per relative depth
    std::vector<int> hi;   // rightmost column per relative depth
};

template <typename Node>
Contour getContour(const Node* root, int depth, const std::vector<int>& step) {
    Contour c;

    const std::string label = makeLabel(root->val);
    c.lo.push_back(-leftSpan(label));
    c.hi.push_back(rightSpan(label));

    auto merge = [&](const Node* child, int shift) {
        if (!child)
            return;

        Contour sub = getContour(child, depth + 1, step);

        if (c.lo.size() < sub.lo.size() + 1) {
            c.lo.resize(sub.lo.size() + 1, INT_MAX);
            c.hi.resize(sub.hi.size() + 1, INT_MIN);
        }

        for (size_t k = 0; k < sub.lo.size(); k++) {
            c.lo[k + 1] = std::min(c.lo[k + 1], sub.lo[k] + shift);
            c.hi[k + 1] = std::max(c.hi[k + 1], sub.hi[k] + shift);
        }
    };

    merge(root->left,  -step[depth]);
    merge(root->right, +step[depth]);

    return c;
}

template <typename Node>
std::vector<int> computeSteps(
    const std::vector<std::vector<const Node*>>& levels,
    int maxLen
) {
    constexpr int GAP = 2;                       // min spaces between neighbours
    const int height = static_cast<int>(levels.size());

    std::vector<int> step(height, 1);

    for (int d = height - 2; d >= 0; d--) {

        // Need at least 1 slash row: step >= maxLen - 1
        int best = std::max(1, maxLen - 1);

        for (const Node* node : levels[d]) {
            if (!node->left || !node->right)
                continue;

            Contour L = getContour(node->left,  d + 1, step);
            Contour R = getContour(node->right, d + 1, step);

            const size_t common = std::min(L.hi.size(), R.lo.size());

            int need = 0;
            for (size_t k = 0; k < common; k++)
                need = std::max(need, L.hi[k] - R.lo[k] + GAP + 1);

            best = std::max(best, (need + 1) / 2);
        }

        step[d] = best;
    }

    return step;
}

// ==========================================
// 4. POSITIONS (RELATIVE X) AND CANVAS SIZE
// ==========================================

template <typename Node>
void findBounds(
    const Node* root, int depth, int x,
    const std::vector<int>& step, int& minX, int& maxX
) {
    if (!root)
        return;

    const std::string label = makeLabel(root->val);
    minX = std::min(minX, x - leftSpan(label));
    maxX = std::max(maxX, x + rightSpan(label));

    findBounds(root->left,  depth + 1, x - step[depth], step, minX, maxX);
    findBounds(root->right, depth + 1, x + step[depth], step, minX, maxX);
}

// ==========================================
// 5. DRAW
// ==========================================

template <typename Node>
void draw(
    const Node* root,
    int depth,
    int x,
    int maxLen,                  // must be odd
    const std::vector<int>& step,
    const std::vector<int>& rowOf,
    Canvas& canvas
) {
    if (!root)
        return;

    const int row = rowOf[depth];

    const std::string label = makeLabel(root->val);
    const int start = x - leftSpan(label);
    const int end   = start + static_cast<int>(label.size()) - 1;

    for (size_t i = 0; i < label.size(); i++)
        canvas[row][start + static_cast<int>(i)] = std::string(1, label[i]);

    if (root->left || root->right) {

        const int a = (maxLen - 1) / 2;               // equal both sides (maxLen odd)
        const int fullRows  = step[depth] - maxLen + 2;
        const int slashRows = std::min(fullRows, MAX_SLASH_ROWS);
        const int run       = fullRows - slashRows;   // horizontal '_' length

        if (root->left) {
            const int s0 = x - a - run;               // first slash column
            if (run > 0)
                for (int c = s0; c < start; c++)
                    canvas[row][c] = "_";
            for (int k = 1; k <= slashRows; k++)
                canvas[row + k][s0 - (k - 1)] = "/";
        }

        if (root->right) {
            const int e0 = x + a + run;               // first backslash column
            if (run > 0)
                for (int c = end + 1; c <= e0; c++)
                    canvas[row][c] = "_";
            for (int k = 1; k <= slashRows; k++)
                canvas[row + k][e0 + (k - 1)] = "\\";
        }
    }

    draw(root->left,  depth + 1, x - step[depth], maxLen, step, rowOf, canvas);
    draw(root->right, depth + 1, x + step[depth], maxLen, step, rowOf, canvas);
}

// ==========================================
// 6. FALLBACK: SIDEWAYS PRINT (ANY SIZE TREE)
// ==========================================

template <typename Node>
void printSideways(const Node* root, int depth) {
    if (!root)
        return;

    printSideways(root->right, depth + 1);
    std::cout << std::string(depth * 6, ' ') << makeLabel(root->val) << '\n';
    printSideways(root->left, depth + 1);
}

} // namespace detail


// ==========================================
// 7. PUBLIC PRINT FUNCTION
// ==========================================

template <typename Node>
void printTree(
    Node* root,
    const std::string& title = "BINARY TREE",
    int maxWidth = 160
) {
    std::cout << "\n========== " << title << " ==========\n\n";

    if (!root) {
        std::cout << "(empty tree)\n\n";
        return;
    }

    std::vector<std::vector<const Node*>> levels;
    detail::collectByDepth<Node>(root, 0, levels);

    const int height = static_cast<int>(levels.size());

    int maxLen = 0;
    for (const auto& level : levels)
        for (const Node* node : level)
            maxLen = std::max(maxLen, static_cast<int>(detail::makeLabel(node->val).size()));

    if (maxLen % 2 == 0)   // odd -> left/right offsets equal -> symmetric edges
        maxLen++;

    const std::vector<int> step = detail::computeSteps<Node>(levels, maxLen);

    int minX = INT_MAX, maxX = INT_MIN;
    detail::findBounds<Node>(root, 0, 0, step, minX, maxX);

    const long long width = static_cast<long long>(maxX) - minX + 1;

    if (width > maxWidth) {
        std::cout << "(tree too wide, printing sideways)\n\n";
        detail::printSideways(root, 0);
        std::cout << '\n';
        return;
    }

    // Row of each depth
    std::vector<int> rowOf(height, 0);
    for (int d = 0; d + 1 < height; d++) {
        const int slashRows = std::min(step[d] - maxLen + 2, detail::MAX_SLASH_ROWS);
        rowOf[d + 1] = rowOf[d] + slashRows + 1;
    }

    detail::Canvas canvas(
        rowOf[height - 1] + 1,
        std::vector<std::string>(static_cast<size_t>(width) + 1, " ")
    );

    detail::draw<Node>(root, 0, -minX, maxLen, step, rowOf, canvas);

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

} // namespace TreeVisualization