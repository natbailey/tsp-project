/**
 * @author Natasha Bailey
 * CSCI 406, Algorithms Project 1
 * Traveling Salesperson Problem
 * Greedy-Heuristic and Exhaustive Search
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include "Point.h"

using namespace std;

void greedyHeuristic(const vector<Point>&);
void exhaustiveSearch(const vector<Point>&);
vector<vector<Point>> generatePermutations(const vector<Point>&);
void recursePermutations(vector<vector<Point>>&, const vector<Point>&, const vector<Point>&);
vector<Point> makePath(Point rootPoint, const vector<Point>&);
double pathDistance(const vector<Point>&);

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
    cout << endl;
    exhaustiveSearch(points);

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
    cout << fixed << setprecision(3) << totalDistance << endl;
    for(Point p : visitedPoints) {
        cout << p.x << " " << p.y << endl;
    }
}

void exhaustiveSearch(const vector<Point>& points) {
    Point rootPoint = points.front();
    vector<Point> nonRootPoints = points;
    nonRootPoints.erase(nonRootPoints.begin());
    vector<vector<Point>> permutations = generatePermutations(nonRootPoints);
    vector<Point> currentPath = makePath(rootPoint, permutations.front());

    double minDistance = pathDistance(currentPath);
    vector<Point> minPath = currentPath;
    for(vector<Point> permutation : permutations) {
        currentPath = makePath(rootPoint, permutation);
        if(pathDistance(currentPath) < minDistance) {
            minDistance = pathDistance(currentPath);
            minPath = currentPath;
        }
    }

    cout << fixed << setprecision(3) << minDistance << endl;
    for(Point p : minPath) {
        cout << p.x << " " << p.y << endl;
    }
}

/**
 * Source: https://www.baeldung.com/cs/array-generate-all-permutations
 * Very helpful article that describes the recursive algorithm below.
 */
vector<vector<Point>> generatePermutations(const vector<Point>& points) {
    vector<vector<Point>> generatedPermutations;
    vector<Point> emptyStartingVector;
    recursePermutations(generatedPermutations, emptyStartingVector, points);

    return generatedPermutations;
}

void recursePermutations(vector<vector<Point>>& generatedPermutations, const vector<Point>& currentPermutation,
                         const vector<Point>& pointsLeft) {
    if(!pointsLeft.empty()) {
        for(int i = 0; i < pointsLeft.size(); i++) {
            vector<Point> nextPermutation = currentPermutation;
            nextPermutation.push_back(pointsLeft.at(i));
            vector<Point> newPointsLeft = pointsLeft;
            newPointsLeft.erase(newPointsLeft.begin() + i);
            recursePermutations(generatedPermutations, nextPermutation, newPointsLeft);
        }
    } else {
        generatedPermutations.push_back(currentPermutation);
    }
}

vector<Point> makePath(Point rootPoint, const vector<Point>& otherPoints) {
    vector<Point> path = otherPoints;
    path.push_back(rootPoint);
    path.insert(path.begin(), rootPoint);
    return path;
}

double pathDistance(const vector<Point>& path) {
    double distance = 0;
    for(int i = 0; i < path.size() - 1; i++) {
        distance += path.at(i).distanceTo(path.at(i + 1));
    }
    return distance;
}
