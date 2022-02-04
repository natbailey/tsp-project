#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Point.h"

using namespace std;

void greedyHeuristic(const vector<Point>&);

int main() {
    int n;
    vector<Point> points;
    ifstream inputFile;

    string fileName;
    cout << "Enter file name: ";
    cin >> fileName;
    inputFile.open("example-data/" + fileName);

    if(inputFile.fail()) {
        cerr << "Failed to open file" << endl;
        return 1;
    }

    inputFile >> n;
    cout << n << endl;

    for(int i = 0; i < n; i++) {
        int x, y;
        inputFile >> x;
        inputFile >> y;
        points.emplace_back(Point(x, y));
    }

    for(Point p : points) {
        cout << p.x << " " << p.y << endl;
    }

    cout << endl;
    greedyHeuristic(points);

    inputFile.close();
}

void greedyHeuristic(const vector<Point>& points) {
    Point rootPoint = points.at(0);
    Point currentPoint = rootPoint;
    int currentPointIndex = 0;
    vector<Point> visitedPoints;
    vector<Point> unvisitedPoints = points;
    double totalDistance = 0;

    while(!unvisitedPoints.empty()) {
        visitedPoints.emplace_back(currentPoint);
        unvisitedPoints.erase(unvisitedPoints.begin() + currentPointIndex);

        double minDistance = currentPoint.distanceTo(unvisitedPoints.front());
        Point minPoint = unvisitedPoints.front();
        int minPointIndex = 0;
        for (int i = 0; i < unvisitedPoints.size(); i++) {
            if (currentPoint.distanceTo(unvisitedPoints.at(i)) < minDistance) {
                minDistance = currentPoint.distanceTo(unvisitedPoints.at(i));
                minPoint = unvisitedPoints.at(i);
                minPointIndex = i;
            }
        }

        totalDistance += minDistance;
        currentPoint = minPoint;
        currentPointIndex = minPointIndex;
    }

    visitedPoints.emplace_back(rootPoint);
    totalDistance += currentPoint.distanceTo(rootPoint);

    cout << totalDistance << endl;
    for(Point p : visitedPoints) {
        cout << p.x << " " << p.y << endl;
    }
}
