#include "crossProduct.hpp"

/**
 * Calculate the cross product of vectors AB and AC.\n\n
 * If the result is :\n
 * positive, the point C is on the left side of the line AB.\n
 * negative, the point C is on the right side of the line AB.\n
 * zero, the point C is on the line AB.
 *
 * @param a A point
 * @param b B point
 * @param c C point
 *
 * @return The cross product of vectors AB and AC
 */
float crossProduct(const Point2& a, const Point2& b, const Point2& c)
{
    return (b.getRawX() - a.getRawX()) * (c.getRawY() - a.getRawY()) - (b.getRawY() - a.getRawY()) * (
               c.getRawX() - a.getRawX());
}
