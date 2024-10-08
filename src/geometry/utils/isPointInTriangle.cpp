#include "isPointInTriangle.hpp"

/**
 * Check if a point is inside a triangle.
 *
 * @param pt The point to check
 * @param v1 The first vertex of the triangle
 * @param v2 The second vertex of the triangle
 * @param v3 The third vertex of the triangle
 *
 * @return True if the point is inside the triangle, false otherwise
 */
bool isPointInTriangle(const Point2& pt, const Point2& v1, const Point2& v2, const Point2& v3)
{
    const float d1 = crossProduct(pt, v1, v2);
    const float d2 = crossProduct(pt, v2, v3);
    const float d3 = crossProduct(pt, v3, v1);

    const bool hasNeg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    const bool hasPos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(hasNeg && hasPos);
}