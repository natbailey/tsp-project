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

double Point::distanceTo(const Point& p) const {
    return sqrt(pow(p.x - x, 2) + pow(p.y - y, 2));
}

bool Point::equals(const Point& p) const {
    return x == p.x && y == p.y;
}

bool Point::operator<(const Point& p) const {
    return x < p.x;
}
