/**
 * @author: Natasha Bailey
 * Represents a point in two-dimensional cartesian space
 */

#ifndef TSP_POINT
#define TSP_POINT


class Point {
public:
    int x, y;
    Point(int x, int y);
    double distanceTo(const Point& p);
};


#endif // TSP_POINT
