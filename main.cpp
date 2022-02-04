/**
 * @author Natasha Bailey
 * CSCI 406, Algorithms Project 1
 * Traveling Salesperson Problem
 * Greedy and Exhaustive heuristics
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
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
    // The first point which the path should return to
    Point rootPoint = points.at(0);

    // The current point being visited and its index
    Point currentPoint = rootPoint;
    int currentPointIndex = 0;

    // A vector of visited points which essentially stores the whole path
    vector<Point> visitedPoints;
    // A vector of unvisited points which grows smaller throughout the algorithm
    vector<Point> unvisitedPoints = points;

    // The total distance of the path
    double totalDistance = 0;

    // Loop until all points are visited
    while(!unvisitedPoints.empty()) {
        // Add current point to path and remove from unvisited
        visitedPoints.emplace_back(currentPoint);
        unvisitedPoints.erase(unvisitedPoints.begin() + currentPointIndex);

        // Search the unvisited points for the point with the smallest distance from the current point
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

        // Update the total distance and the current point
        totalDistance += minDistance;
        currentPoint = minPoint;
        currentPointIndex = minPointIndex;
    }

    // Return to the root point at the end of the path and update distance accordingly
    visitedPoints.emplace_back(rootPoint);
    totalDistance += currentPoint.distanceTo(rootPoint);

    // Print out distance and path
    cout << fixed << setprecision(2) << totalDistance << endl;
    for(Point p : visitedPoints) {
        cout << p.x << " " << p.y << endl;
    }
}
