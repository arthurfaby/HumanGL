#include <algorithm>
#include <iostream>
#include "triangulatePolygon.hpp"
#include "crossProduct.hpp"
#include "isPointInTriangle.hpp"

/**
 * Check if a polygon is counter-clockwise.
 *
 * @param polygon The polygon to check
 *
 * @return True if the polygon is counter-clockwise, false otherwise
 */
bool isCounterClockwise(const std::vector<Point2>& polygon)
{
    float sum = 0.0f;
    const size_t n = polygon.size();

    for (size_t i = 0; i < n; ++i)
    {
        const Point2& current = polygon[i];
        const Point2& next = polygon[(i + 1) % n];

        sum += (next.getRawX() - current.getRawX()) * (next.getRawY() + current.getRawY());
    }

    return sum < 0;
}

/**
 * Check if a triangle is an ear.
 *
 * @param polygon The polygon
 * @param i The index of the first vertex of the triangle
 * @param j The index of the second vertex of the triangle
 * @param k The index of the third vertex of the triangle
 *
 * @return True if the triangle is an ear, false otherwise
 */
bool isEar(const std::vector<Point2>& polygon, const int i, const int j, const int k)
{
    const Point2& v1 = polygon[i];
    const Point2& v2 = polygon[j];
    const Point2& v3 = polygon[k];

    if (crossProduct(v1, v2, v3) <= 0)
        return false;

    for (size_t n = 0; n < polygon.size(); ++n)
    {
        if (n != i && n != j && n != k && isPointInTriangle(polygon[n], v1, v2, v3))
        {
            return false;
        }
    }
    return true;
}

/**
 * Triangulate a polygon.
 *
 * @param polygon The list of points of the polygon
 *
 * @return The one dimensional list of points of the triangles (3 points per triangle)
 */
std::vector<Point2> triangulatePolygon(std::vector<Point2> polygon)
{
    std::vector<Point2> triangles;

    if (polygon.size() < 3)
    {
        std::cerr << "Polygon has less than 3 points" << std::endl;
        return triangles;
    }

    if (!isCounterClockwise(polygon))
    {
        std::reverse(polygon.begin(), polygon.end());
    }

    std::vector<int> indices(polygon.size());
    for (int i = 0; i < indices.size(); ++i)
    {
        indices[i] = i;
    }

    int count = 0;
    while (indices.size() > 2)
    {
        bool earFound = false;
        for (int i = 0; i < indices.size(); ++i)
        {
            int prev = (i == 0) ? indices.size() - 1 : i - 1;
            int next = (i == indices.size() - 1) ? 0 : i + 1;

            if (isEar(polygon, indices[prev], indices[i], indices[next]))
            {
                triangles.push_back(polygon[indices[prev]]);
                triangles.push_back(polygon[indices[i]]);
                triangles.push_back(polygon[indices[next]]);

                indices.erase(indices.begin() + i);
                earFound = true;
                break;
            }
        }

        if (!earFound || (++count > polygon.size() * polygon.size()))
        {
            break;
        }
    }
    return triangles;
}