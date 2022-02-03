#include <iostream>
#include "Point.h"

using namespace std;

int main() {
    Point p1(0, 0);
    Point p2(-1, 1);

    cout << "Distance: " << p1.distanceTo(p2) << endl;
}
