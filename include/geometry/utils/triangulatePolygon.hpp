#ifndef TRIANGULATE_POLYGON_HPP
#define TRIANGULATE_POLYGON_HPP

#include <vector>
#include "Point2.hpp"

bool isCounterClockwise(const std::vector<Point2>& polygon);
bool isEar(const std::vector<Point2>& polygon, int i, int j, int k);
std::vector<Point2> triangulatePolygon(std::vector<Point2> polygon);

#endif //TRIANGULATE_POLYGON_HPP
