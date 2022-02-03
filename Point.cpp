//
// Created by luxra on 2/2/2022.
//

#include <cmath>
#include "Point.h"

using namespace std;

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

double Point::distanceTo(const Point &p) {
    return sqrt(pow(p.x - x, 2) + pow(p.y - y, 2));
}
