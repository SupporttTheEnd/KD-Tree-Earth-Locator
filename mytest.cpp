// Title: geolocate.cpp
// Author: Andrew Tang
// Date: 12/7/2023
// Description: This is the test file for geolocate.cpp

#include "geolocate.h"
#include <math.h>
#include <algorithm>
#include <random>
#include <vector>
using namespace std; 

class Tester{
    public:
    // Test the insertion function for a normal case.
    bool insertNormal () {
        cout << "TEST 1 RESULTS:" << endl;
        KDTree tree;
        vector<GeoPoint> points;

        // insert some nodes
        for (int i = -90; i < 90; i ++){
            GeoPoint point(double(i), double(2.0 * i), "Test");
            tree.insert(point);
            points.push_back(point);
        }

        // go through the tree and make sure that everything has been inserted
        for (vector<GeoPoint>::iterator it = points.begin(); it != points.end(); ++it) {
            if (!find(tree.m_root, *it)) {
                cout << "A inserted point not found in the tree: " << (*it).getName() << endl;
                return false;
            }
        }
        
        // check the kd tree property is maintained
        if (!kdProperty(tree.m_root, 0)){
            return false; 
        }
        return true; 
    }

    // Test the insertion function for a error case where an invalid node is attempted to be inserted.
    bool insertError() {
        cout << "TEST 2 RESULTS:" << endl;
        KDTree tree;
        vector<GeoPoint> points;

        // try inserting an invalid node
        GeoPoint point(100, -200, "Invalid");
        tree.insert(point);
        points.push_back(point);
        
        if (find(tree.m_root, point)) {
            return false;
        }
    
        return true; 
    }
    
    // Test the nearest neighbor function for a normal case with brute force
    bool nearestNormal() {
        cout << "TEST 3 RESULTS:" << endl;
        KDTree tree;
        vector<GeoPoint> points;
        // insert some nodes
        for (int i = -90; i < 90; i ++){
            GeoPoint point(double(i), double(2.0 * i), "Test");
            tree.insert(point);
            points.push_back(point);
        }

        // set a target point
        GeoPoint target(5, 11, "Target"); 
        GeoPoint closest; 

        // initialize the min distance to the max possible 
        double min = numeric_limits<double>::max();

        // loop through the vector and brute force find the min distance node
        for (vector<GeoPoint>::iterator it = points.begin(); it != points.end(); ++it) {
            double distance = calculateDistance(target, *it);
            if (distance < min) {
                min = distance;
                closest = *it;
            }
        }

        // find the nearest neighbor using the KD tree
        GeoPoint kdClosest = tree.nearest(target);

        // check if the brute force result matches the KD tree result
        if (!(kdClosest.getLatitude() == closest.getLatitude() &&
            kdClosest.getLongitude() == closest.getLongitude() &&
            kdClosest.getName() == closest.getName())) {
            return false;
        }

        // make sure the kd property is maintained
        if (!kdProperty(tree.m_root, 0)){
            return false; 
        }
        return true; 
    }

    // Test the nearest neighbor function for a error case where an nearest search is attempted on a empty kd tree.
    bool nearestError() {
        cout << "TEST 4 RESULTS:" << endl;
        KDTree tree;
        vector<GeoPoint> points;

        // set a target point
        GeoPoint target(5, 11, "Target"); 

        GeoPoint kdClosest = tree.nearest(target);

        // make sure that the returned closest is a empty node
        if (!(kdClosest.getLatitude() == 0.0 &&
            kdClosest.getLongitude() == 0.0 &&
            kdClosest.getName() == "")) {
            return false;
        }

        return true; 
    }

    private:
    // private find function
    bool find(GeoPoint* node, const GeoPoint& point) {
        // base case
        if (node == nullptr) {
            return false;
        }

        // if the patient is found
        if (node->getLatitude() == point.getLatitude() &&
            node->getLongitude() == point.getLongitude() &&
            node->getName() == point.getName()) {
            return true;
        }

        // recurse
        return find(node->m_left, point) || find(node->m_right, point);
    }

    // checks kd property for each node
    bool kdProperty(GeoPoint*& node, int depth) {
        // if we have reached nullptr, the property holds
        if (node == nullptr) {
            return true;
        }

        // determine what parameter we are comparing
        bool compLat = (depth % 2 == 0);

        // check the kd property for each node
        if ((compLat && node->m_left != nullptr && node->m_left->getLatitude() >= node->getLatitude()) ||
            (!compLat && node->m_left != nullptr && node->m_left->getLongitude() >= node->getLongitude())) {
            return false;
        }

        if ((compLat && node->m_right != nullptr && node->m_right->getLatitude() < node->getLatitude()) ||
            (!compLat && node->m_right != nullptr && node->m_right->getLongitude() < node->getLongitude())) {
            return false;
        }

        // recursive call
        return kdProperty(node->m_left, depth + 1) && kdProperty(node->m_right, depth + 1);
    }

    // calculates distances between two points
    double calculateDistance(const GeoPoint& point1, const GeoPoint& point2) {
        // for sphere convert everything to be in terms of radian
        double lat1 = toRadians(point1.getLatitude());
        double lon1 = toRadians(point1.getLongitude());
        double lat2 = toRadians(point2.getLatitude());
        double lon2 = toRadians(point2.getLongitude());

        double latDifference = lat2 - lat1;
        double lonDifference = lon2 - lon1;

        // use the haversine formula; proof is very tough, but I used the formula from https://www.movable-type.co.uk/scripts/latlong.html
        // Haversine formula:
        // a = sin²(Δφ/2) + cos φ1 ⋅ cos φ2 ⋅ sin²(Δλ/2)
        // c = 2 ⋅ atan2( √a, √(1−a) )
        // d = R ⋅ c
        // its used to calculate the distance between points on a spherical surface
        // this implementation is made to fit lat and long
        double a = sin(latDifference / 2.0) * sin(latDifference / 2.0) + cos(lat1) * cos(lat2) * sin(lonDifference / 2.0) * sin(lonDifference / 2.0);
        double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
        // 6371 is an approx estimate of the radius of earth in km
        return 6371.0 * c;
    }

    
    // changes degrees into radians
    double toRadians(const double& degree){
        return (((M_PI) / 180) * degree);
    }

};

int main(){
    Tester tester;
    cout << endl << "\033[1;31m=============================|Test Cases for the KD TREE Class|==============================\033[0m" << endl;

    cout << "________________________________________________________" << endl; 
    
    cout << "Test the insertion function for a normal case." << endl; 

    if (tester.insertNormal()) {
        cout << "\033[1;32mSUCCESS\033[0m insert function passed for a normal test" << endl;
    } 
    else {
        cout << "FAILURE: insert function failed for a normal test" << endl;
    }

    cout << "________________________________________________________" << endl; 
    
    cout << "Test the insertion function for a error case where an invalid node is attempted to be inserted." << endl; 

    if (tester.insertError()) {
        cout << "\033[1;32mSUCCESS\033[0m insert function passed for a error test" << endl;
    } 
    else {
        cout << "FAILURE: insert function failed for a error test" << endl;
    }

    cout << "________________________________________________________" << endl; 
    
    cout << "Test the nearest neighbor function for a normal case." << endl; 

    if (tester.nearestNormal()) {
        cout << "\033[1;32mSUCCESS\033[0m nearest function passed for a normal test" << endl;
    } 
    else {
        cout << "FAILURE: nearest function failed for a normal test" << endl;
    }

    cout << "________________________________________________________" << endl; 
    
    cout << "Test the nearest neighbor function for a error case where an nearest search is attempted on a empty kd tree." << endl; 

    if (tester.nearestError()) {
        cout << "\033[1;32mSUCCESS\033[0m nearest function passed for a error test" << endl;
    } 
    else {
        cout << "FAILURE: nearest function failed for a error test" << endl;
    }


    return 0;
}
