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
    double distanceTo(const Point& p) const;
    bool equals(const Point& p) const;
    bool operator<(const Point& p) const;
};


#endif // TSP_POINT
