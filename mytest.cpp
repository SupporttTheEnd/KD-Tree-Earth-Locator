// UMBC - CMSC 341 - Fall 2023 - Proj2
// Title: mytest.cpp
// Author: Andrew Tang
// Date: 9/15/2023
// Description: This is a tester file for satnet.cpp

#include "geolocate.h"
#include <math.h>
#include <algorithm>
#include <random>
#include <vector>
using namespace std; 

class Tester{
    public:
};

int main(){
    Tester tester;
    KDTree tree;

    // Insert some GeoPoints into the KD tree
    tree.insert(GeoPoint(37.7749, -122.4194, "San Francisco"));
    tree.insert(GeoPoint(34.0522, -118.2437, "Los Angeles"));
    tree.insert(GeoPoint(41.8781, -87.6298, "Chicago"));
    tree.insert(GeoPoint(40.7128, -74.0060, "New York"));

    // Query for the nearest neighbor of a specific point
    GeoPoint queryPoint(38.8951, -77.0364, "Washington, D.C.");
    GeoPoint nearestNeighbor = tree.nearest(queryPoint);

    // Output the result
    cout << "Query Point: " << queryPoint.getName() << " (" << queryPoint.getLatitude() << ", " << queryPoint.getLongitude() << ")\n";
    cout << "Nearest Neighbor: " << nearestNeighbor.getName() << " (" << nearestNeighbor.getLatitude() << ", " << nearestNeighbor.getLongitude() << ")\n";

    tree.dump();
    return 0;
}