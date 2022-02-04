/**
 * @author Natasha Bailey
 * @see Point.h
 */

#include <cmath>
#include "Point.h"

using namespace std;

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

/**
 * Calculates the straight-line distance between this point and another point
 * @param p point to calculate distance to
 * @return distance from this point to point p
 */
double Point::distanceTo(const Point& p) const {
    return sqrt(pow(p.x - x, 2) + pow(p.y - y, 2));
}
