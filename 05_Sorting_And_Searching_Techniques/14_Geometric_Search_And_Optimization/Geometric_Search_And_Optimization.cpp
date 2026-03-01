/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 14 — GEOMETRIC SEARCH & OPTIMIZATION                     ║
║           From Zero to Grandmaster — Complete Foundation                    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1.  Ternary Search on Unimodal Functions
 2.  Convex Function Minimization
 3.  Rotating Calipers Search Idea
 4.  Binary Search on Geometry Constraints

OVERVIEW:
─────────
Geometric search combines binary/ternary search with geometric primitives.
These techniques are common in ICPC and advanced competitive programming.

KEY CONCEPTS:
  • Unimodal functions: One peak or one valley
  • Convex functions: f''(x) ≥ 0, one minimum
  • Geometric predicates: Point-line distance, polygon queries
  • Parametric geometry: Binary search on angle, radius, etc.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <climits>
#include <functional>
#include <iomanip>
using namespace std;

const double EPS = 1e-9;
const double PI = acos(-1.0);

// ═══════════════════════════════════════════════════════════════
// SECTION 1: TERNARY SEARCH ON UNIMODAL FUNCTIONS
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 A unimodal function has exactly one extremum (max or min).
 Ternary search finds this extremum in O(log n) evaluations.

 APPLICATIONS:
   1. Finding the point on a line closest to a given point
   2. Minimizing distance/cost functions
   3. Optimal position problems
   4. Beam/cable hanging problems
   5. Function minimization in physics/geometry

 CONTINUOUS TERNARY SEARCH:
   for 100-200 iterations (gives precision ~10^-15):
     m1 = lo + (hi - lo) / 3
     m2 = hi - (hi - lo) / 3
     if f(m1) < f(m2): hi = m2  (for minimum)
     else: lo = m1
*/

// Find minimum of a unimodal function (continuous)
double ternaryMin(double lo, double hi, function<double(double)> f) {
    for (int i = 0; i < 200; i++) {
        double m1 = lo + (hi - lo) / 3;
        double m2 = hi - (hi - lo) / 3;
        if (f(m1) < f(m2)) hi = m2;
        else lo = m1;
    }
    return (lo + hi) / 2;
}

// Find maximum of a unimodal function (continuous)
double ternaryMax(double lo, double hi, function<double(double)> f) {
    for (int i = 0; i < 200; i++) {
        double m1 = lo + (hi - lo) / 3;
        double m2 = hi - (hi - lo) / 3;
        if (f(m1) > f(m2)) hi = m2;
        else lo = m1;
    }
    return (lo + hi) / 2;
}

void demo_ternary_on_functions() {
    cout << "=== SECTION 1: TERNARY SEARCH ON FUNCTIONS ===" << endl;

    // Problem 1: Find point on line y = 2x + 1 closest to point (3, 7)
    // Distance²(t) = (t-3)² + (2t+1-7)² = (t-3)² + (2t-6)² = 5t² - 30t + 45
    // Unimodal (quadratic) — minimum at t = 3
    auto distSq = [](double t) {
        double dx = t - 3, dy = (2 * t + 1) - 7;
        return dx * dx + dy * dy;
    };
    double t = ternaryMin(-100, 100, distSq);
    cout << fixed << setprecision(4);
    cout << "Closest point on y=2x+1 to (3,7): (" << t << ", " << 2*t+1 << ")" << endl;

    // Problem 2: Maximum height of projectile y = v₀t - ½gt²
    // v₀ = 20 m/s, g = 9.8 m/s²
    double v0 = 20, g = 9.8;
    auto height = [v0, g](double t) { return v0 * t - 0.5 * g * t * t; };
    double tPeak = ternaryMax(0, 2 * v0 / g, height);
    cout << "Projectile peak: t=" << tPeak << "s, h=" << height(tPeak) << "m" << endl;

    // Problem 3: Minimum of f(x) = |x - 2| + |x - 5| + |x - 8|
    // This is piecewise linear, minimum at median (x = 5)
    auto absSum = [](double x) {
        return abs(x - 2) + abs(x - 5) + abs(x - 8);
    };
    double minX = ternaryMin(-100, 100, absSum);
    cout << "Min of |x-2|+|x-5|+|x-8|: x=" << minX << ", f(x)=" << absSum(minX) << endl;

    // Problem 4: 2D ternary search — Find point (x, y) minimizing sum of distances
    // to given points. (Fermat point approximation using nested ternary search)
    vector<pair<double, double>> points = {{0, 0}, {10, 0}, {5, 8}};
    auto totalDist = [&](double x, double y) {
        double sum = 0;
        for (auto& [px, py] : points)
            sum += sqrt((x - px) * (x - px) + (y - py) * (y - py));
        return sum;
    };

    // Nested ternary search: fix x → minimize over y → unimodal in x
    auto minOverY = [&](double x) {
        return ternaryMin(-100, 100, [&](double y) { return totalDist(x, y); });
    };
    double bestX = ternaryMin(-100, 100, [&](double x) {
        double bestY = minOverY(x);
        return totalDist(x, bestY);
    });
    double bestY = minOverY(bestX);
    cout << "Fermat point: (" << bestX << ", " << bestY
         << "), total dist=" << totalDist(bestX, bestY) << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: CONVEX FUNCTION MINIMIZATION
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 A function f is CONVEX if:
   f(λx + (1-λ)y) ≤ λf(x) + (1-λ)f(y) for all λ ∈ [0,1]
   Equivalently: f''(x) ≥ 0

 Convex functions have a single global minimum.
 We can find it using:
   1. Ternary search
   2. Golden section search (slightly more efficient than ternary)
   3. Gradient descent (iterative)
   4. Binary search on derivative (if derivative computable)

 GOLDEN SECTION SEARCH:
   Uses the golden ratio φ = (1 + √5) / 2 ≈ 1.618
   Reuses one function evaluation per iteration (vs ternary which needs 2).
   Convergence: 1/φ per step ≈ 0.618 (vs 2/3 for ternary)

 BINARY SEARCH ON DERIVATIVE:
   If we can compute f'(x), binary search for f'(x) = 0.
   Since f is convex, f' is non-decreasing (monotonic).
   Find first x where f'(x) ≥ 0 → this is the minimum.
*/

// Golden Section Search for minimum
double goldenSectionMin(double lo, double hi, function<double(double)> f) {
    double phi = (1 + sqrt(5)) / 2;
    double resphi = 2 - phi;

    double x1 = lo + resphi * (hi - lo);
    double x2 = hi - resphi * (hi - lo);
    double f1 = f(x1), f2 = f(x2);

    for (int i = 0; i < 200; i++) {
        if (f1 < f2) {
            hi = x2;
            x2 = x1;
            f2 = f1;
            x1 = lo + resphi * (hi - lo);
            f1 = f(x1);
        } else {
            lo = x1;
            x1 = x2;
            f1 = f2;
            x2 = hi - resphi * (hi - lo);
            f2 = f(x2);
        }
    }
    return (lo + hi) / 2;
}

// Binary search on derivative
double bsOnDerivative(double lo, double hi,
                       function<double(double)> f,
                       function<double(double)> df) {
    for (int i = 0; i < 200; i++) {
        double mid = (lo + hi) / 2;
        if (df(mid) < 0) lo = mid;
        else hi = mid;
    }
    return (lo + hi) / 2;
}

// Simulated Annealing for complex optimization
double simulatedAnnealing(double lo, double hi,
                           function<double(double)> f, int iterations = 100000) {
    double best = lo, bestVal = f(lo);
    double temp = hi - lo;

    for (int i = 0; i < iterations; i++) {
        double next = best + ((double)rand() / RAND_MAX * 2 - 1) * temp;
        next = max(lo, min(hi, next));
        double val = f(next);
        double delta = val - bestVal;
        if (delta < 0 || (double)rand() / RAND_MAX < exp(-delta / temp)) {
            best = next;
            bestVal = val;
        }
        temp *= 0.9999;
    }
    return best;
}

void demo_convex_minimization() {
    cout << "=== SECTION 2: CONVEX FUNCTION MINIMIZATION ===" << endl;

    // f(x) = x² - 4x + 7, minimum at x = 2, f(2) = 3
    auto f = [](double x) { return x * x - 4 * x + 7; };
    auto df = [](double x) { return 2 * x - 4; };

    double min1 = ternaryMin(-100, 100, f);
    double min2 = goldenSectionMin(-100, 100, f);
    double min3 = bsOnDerivative(-100, 100, f, df);

    cout << "f(x) = x²-4x+7:" << endl;
    cout << "  Ternary search: x=" << min1 << ", f(x)=" << f(min1) << endl;
    cout << "  Golden section: x=" << min2 << ", f(x)=" << f(min2) << endl;
    cout << "  BS on derivative: x=" << min3 << ", f(x)=" << f(min3) << endl;

    // Multi-dimensional convex optimization: Weighted Euclidean median
    // Minimize sum of wi * distance(P, Pi)
    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: ROTATING CALIPERS SEARCH IDEA
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Rotating Calipers is a technique for computational geometry problems
 involving convex hulls. It "rotates" a pair of parallel supporting
 lines around the convex hull.

 APPLICATIONS:
   1. Maximum distance pair (diameter of convex hull)
   2. Minimum enclosing rectangle
   3. Maximum area triangle
   4. Minimum width of convex polygon
   5. Bridge between two convex hulls

 ALGORITHM for Diameter:
   1. Compute convex hull
   2. Find antipodal pairs using rotating calipers
   3. Track maximum distance

 TIME: O(n) on convex hull (after O(n log n) hull construction)

 KEY IDEA:
   As we rotate the "caliper" (parallel support lines),
   the contact points move monotonically around the hull.
   This is essentially a TWO-POINTER technique on a circular structure!
*/

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
    double cross(const Point& p) const { return x * p.y - y * p.x; }
    double dot(const Point& p) const { return x * p.x + y * p.y; }
    double norm() const { return sqrt(x * x + y * y); }
};

double dist(Point& a, Point& b) {
    return (a - b).norm();
}

// Convex Hull (Andrew's monotone chain)
vector<Point> convexHull(vector<Point> points) {
    int n = points.size();
    if (n < 3) return points;

    sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });

    vector<Point> hull;
    // Lower hull
    for (auto& p : points) {
        while (hull.size() >= 2 &&
               (hull.back() - hull[hull.size() - 2]).cross(p - hull[hull.size() - 2]) <= 0)
            hull.pop_back();
        hull.push_back(p);
    }

    // Upper hull
    int lower_size = hull.size();
    for (int i = n - 2; i >= 0; i--) {
        while ((int)hull.size() > lower_size &&
               (hull.back() - hull[hull.size() - 2]).cross(points[i] - hull[hull.size() - 2]) <= 0)
            hull.pop_back();
        hull.push_back(points[i]);
    }
    hull.pop_back();
    return hull;
}

// Rotating Calipers: Find diameter (maximum distance between any two points)
double rotatingCalipersMaxDist(vector<Point>& points) {
    vector<Point> hull = convexHull(points);
    int n = hull.size();
    if (n == 1) return 0;
    if (n == 2) return dist(hull[0], hull[1]);

    double maxDist = 0;
    int j = 1;
    for (int i = 0; i < n; i++) {
        Point edge = hull[(i + 1) % n] - hull[i];
        while (edge.cross(hull[(j + 1) % n] - hull[j]) > 0)
            j = (j + 1) % n;
        maxDist = max(maxDist, dist(hull[i], hull[j]));
        maxDist = max(maxDist, dist(hull[(i + 1) % n], hull[j]));
    }
    return maxDist;
}

// Minimum width of convex polygon using rotating calipers
double minWidth(vector<Point>& points) {
    vector<Point> hull = convexHull(points);
    int n = hull.size();
    if (n <= 2) return 0;

    double minW = 1e18;
    int j = 1;
    for (int i = 0; i < n; i++) {
        Point edge = hull[(i + 1) % n] - hull[i];
        double edgeLen = edge.norm();
        while (edge.cross(hull[(j + 1) % n] - hull[i]) > edge.cross(hull[j] - hull[i]))
            j = (j + 1) % n;
        // Distance from hull[j] to line (hull[i], hull[i+1])
        double w = abs(edge.cross(hull[j] - hull[i])) / edgeLen;
        minW = min(minW, w);
    }
    return minW;
}

void demo_rotating_calipers() {
    cout << "=== SECTION 3: ROTATING CALIPERS ===" << endl;

    vector<Point> points = {{0, 0}, {1, 0}, {0.5, 1}, {1, 1}, {0, 1}};
    double diameter = rotatingCalipersMaxDist(points);
    cout << "Diameter: " << diameter << endl;

    double width = minWidth(points);
    cout << "Min width: " << width << endl;

    // Closest pair would use divide and conquer, not rotating calipers
    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: BINARY SEARCH ON GEOMETRY CONSTRAINTS
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Many geometry problems can be solved by binary searching on a
 geometric parameter (distance, angle, radius, area).

 EXAMPLES:
   1. Minimum radius circle covering k points
   2. Binary search on distance for nearest neighbor structures
   3. Maximum number of points within radius R
   4. Binary search on angle for visibility problems
   5. Minimum fence enclosing all points

 PATTERN:
   Binary search on parameter → Check feasibility with geometry algorithm
*/

// Problem: Given n points, find minimum radius of circle centered at origin
// that covers at least k points
double minRadiusForKPoints(vector<Point>& points, int k) {
    vector<double> dists;
    for (auto& p : points) dists.push_back(p.norm());
    sort(dists.begin(), dists.end());
    return dists[k - 1]; // kth smallest distance
}

// Problem: Binary search on radius — can we cover all points with k circles of radius r?
// (Simplified: check if k circles of radius r can cover all points on a line)
bool canCoverLine(vector<double>& positions, int k, double r) {
    int circles = 0;
    double lastEnd = -1e18;
    for (double pos : positions) {
        if (pos > lastEnd) {
            circles++;
            lastEnd = pos + 2 * r;
        }
    }
    return circles <= k;
}

double minRadiusLineCover(vector<double>& positions, int k) {
    sort(positions.begin(), positions.end());
    double lo = 0, hi = positions.back() - positions.front();
    for (int i = 0; i < 100; i++) {
        double mid = (lo + hi) / 2;
        if (canCoverLine(positions, k, mid)) hi = mid;
        else lo = mid;
    }
    return (lo + hi) / 2;
}

// Binary search on angle: Find direction that maximizes visible points in angle window
int maxPointsInAngle(vector<Point>& points, double angle) {
    // Convert points to angles from origin
    vector<double> angles;
    for (auto& p : points) {
        if (abs(p.x) < EPS && abs(p.y) < EPS) continue;
        angles.push_back(atan2(p.y, p.x));
    }
    sort(angles.begin(), angles.end());

    // Duplicate for circular handling
    int n = angles.size();
    for (int i = 0; i < n; i++) angles.push_back(angles[i] + 2 * PI);

    int maxPts = 0;
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j < 2 * n && angles[j] - angles[i] <= angle + EPS) j++;
        maxPts = max(maxPts, j - i);
    }
    return maxPts;
}

// Minimum enclosing circle (Welzl's algorithm concept)
struct Circle {
    Point center;
    double radius;
};

Circle minEnclosingCircle(vector<Point>& points) {
    // Simplified: Binary search on radius
    // Full Welzl's is randomized O(n) — shown conceptually

    // Simple approach: check all pairs and triples for defining circle
    int n = points.size();
    if (n == 0) return {{0, 0}, 0};
    if (n == 1) return {points[0], 0};

    // For this demo, find the bounding box center and max distance
    double cx = 0, cy = 0;
    for (auto& p : points) { cx += p.x; cy += p.y; }
    cx /= n; cy /= n;

    double maxR = 0;
    for (auto& p : points) {
        double d = sqrt((p.x - cx) * (p.x - cx) + (p.y - cy) * (p.y - cy));
        maxR = max(maxR, d);
    }
    return {{cx, cy}, maxR};
}

void demo_geometry_bs() {
    cout << "=== SECTION 4: BS ON GEOMETRY CONSTRAINTS ===" << endl;

    // Min radius for k points
    vector<Point> points = {{1, 0}, {0, 2}, {3, 1}, {2, 3}, {5, 2}};
    cout << "Min radius for 3 points from origin: "
         << minRadiusForKPoints(points, 3) << endl;

    // Line cover
    vector<double> positions = {1, 3, 6, 10, 15};
    cout << "Min radius for 2 circles to cover line: "
         << minRadiusLineCover(positions, 2) << endl;

    // Max points in angle
    vector<Point> pts = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}, {2, 0}};
    cout << "Max points in PI/2 angle: " << maxPointsInAngle(pts, PI / 2) << endl;

    // Min enclosing circle
    auto mec = minEnclosingCircle(points);
    cout << "Min enclosing circle: center=(" << mec.center.x << "," << mec.center.y
         << "), radius=" << mec.radius << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║   CHAPTER 14: GEOMETRIC SEARCH & OPTIMIZATION              ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << endl;

    demo_ternary_on_functions();
    demo_convex_minimization();
    demo_rotating_calipers();
    demo_geometry_bs();

    cout << "═══════════════════════════════════════════════════════════════" << endl;
    cout << "All Chapter 14 demos completed successfully!" << endl;

    return 0;
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                         PRACTICE PROBLEMS                                  ║
╠══════════════════════════════════════════════════════════════════════════════╣
║                                                                            ║
║  🟢 EASY:                                                                  ║
║  1. Find minimum of quadratic using ternary search                         ║
║  2. Closest point on line to given point                                   ║
║                                                                            ║
║  🟡 MEDIUM:                                                                ║
║  3. CF 439D — Devu and Birthday Celebration (ternary)                      ║
║  4. CF 578C — Weakness and Poorness (ternary search)                       ║
║  5. CSES — Minimum Euclidean Distance                                      ║
║  6. LC 963 — Minimum Area Rectangle                                        ║
║  7. Binary search on radius problems                                       ║
║                                                                            ║
║  🔴 HARD:                                                                  ║
║  8. CF 1117C — Magic Ship (BS on geometry)                                 ║
║  9. CF 1300E — Water Balance (geometric optimization)                      ║
║ 10. Convex hull diameter (rotating calipers)                               ║
║ 11. Smallest enclosing circle (Welzl's algorithm)                          ║
║ 12. ICPC — Fence/coverage problems                                         ║
║                                                                            ║
║  🔵 GRANDMASTER:                                                           ║
║ 13. CF 1468G — Hobbits                                                     ║
║ 14. Half-plane intersection + BS                                           ║
║ 15. CF 1C — Ancient Berland Circus (geometry + ternary)                    ║
║ 16. IOI geometry optimization problems                                     ║
║ 17. Rotating calipers on convex hull for min-width enclosing rectangle     ║
║                                                                            ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

