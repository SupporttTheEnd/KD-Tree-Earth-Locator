// UMBC - CMSC 341 - Fall 2023 - HW5
// Title: geolocate.cpp
// Author: Andrew Tang
// Date: 12/7/2023
// Description: This is the implementation file for geolocate.h
#include "geolocate.h"

// Name - KDTree()
// Desc - The constructor performs the required initializations. It creates an empty object.
KDTree::KDTree(){
    // set member variable to a null value
    m_root = nullptr;
}

// Name - ~KDTree()
// Desc - The destructor performs the required cleanup including memory deallocations and re-initializing.
KDTree::~KDTree(){
    // call clear since the destructor can't be recursively called
    clear(m_root);
    m_root = nullptr;
}

// Name - clear(Geopoint*& node)
// Desc - overloaded function to allow recursion
void KDTree::clear(GeoPoint*& node){
    // check if the node is populated; if it is, call clear recursively on the left and right
    if (node) {
        clear(node->m_left);
        clear(node->m_right);
        delete node;
        node = nullptr;
    }
}

// Name - insert(const GeoPoint& point)
// Desc - wrapper that calls overloaded insert and also checks for the validity of parameters. 
void KDTree::insert(const GeoPoint& point){
    // check for valid latitude
    if (point.getLatitude() < -90.0 || point.getLatitude() > 90.0) {
        cout << "Attempted to insert node with invalid parameters" << endl; 
        return; 
    }
    // check for valid longitude
    if (point.getLongitude() < -180.0 || point.getLongitude() > 180.0) {
        cout << "Attempted to insert node with invalid parameters" << endl; 
        return; 
    }
    insert(point, m_root, 0);
}

// Name - insert(const GeoPoint& point, GeoPoint*& node, int depth)
// Desc - inserts based off of KD tree principles
void KDTree::insert(const GeoPoint& point, GeoPoint*& node, int depth){
    // base case if empty
    if (node == nullptr) {
        node = new GeoPoint(point);
        return; 
    } 
    
    // see if we are compairing latitude or longitude
    bool compLat = (depth % 2 == 0);

    // compare and decide whether to insert into the left or right subtree
    if ((compLat && point.getLatitude() < node->getLatitude()) ||
        (!compLat && point.getLongitude() < node->getLongitude())) {
        insert(point, node->m_left, depth + 1);
    } 
    else {
        insert(point, node->m_right, depth + 1);
    }
    
}

// Name - nearest(const GeoPoint& point)
// Desc - wrapper for nearest neighbor search and also checks if tree is empty
GeoPoint KDTree::nearest(const GeoPoint& point) {
    GeoPoint close;
    // check if the tree is empty
    if (m_root == nullptr){
        cout << "Empty tree; simply returning empty node" << endl; 
        return close; 
    }
    // set the default closest to be the root first
    close = *m_root;
    nearest(point, m_root, 0, close);
    return close; 
}

void KDTree::nearest(const GeoPoint& point, GeoPoint*& node, int depth, GeoPoint& close) {
    // if the current node is null, return
    if (node == nullptr) {
        return; 
    }

    // determine whether to compare latitude or longitude based on the depth
    bool compLat = (depth % 2 == 0);

    // check if the current node is closer than the currently known closest
    if (calculateDistance(point, *node) < calculateDistance(point, close)) {
        close = *node;
    }

    // calculate the distance from the point to the boundary of the current node and considers the earth's curvature, maintianing the same lat/long
    double distance;
    if (compLat) {
        distance = calculateDistance(GeoPoint(point.getLatitude(),point.getLongitude()), GeoPoint(node->getLatitude(),point.getLongitude()));
    } else {
        distance = calculateDistance(GeoPoint(point.getLatitude(),point.getLongitude()), GeoPoint(point.getLatitude(),node->getLongitude()));
    }

    // visit subtrees in the most promising order
    if ((compLat && point.getLatitude() < node->getLatitude()) ||
        (!compLat && point.getLongitude() < node->getLongitude())) {
        nearest(point, node->m_left, depth + 1, close);

        // check if the other branch is worth exploring
        if (distance < calculateDistance(point, close)) {
            nearest(point, node->m_right, depth + 1, close);
        }
    } 
    else {
        nearest(point, node->m_right, depth + 1, close);

        // check if the other branch is worth exploring
        if (distance < calculateDistance(point, close)) {
            nearest(point, node->m_left, depth + 1, close);
        }
    }
}

// Name - calculateDistance(const GeoPoint& point1, const GeoPoint& point2)
// Desc - calculates the distance between two points using the haversine formula
double KDTree::calculateDistance(const GeoPoint& point1, const GeoPoint& point2) {
    // for sphere convert everything to be in terms of radian
    double lat1 = toRadians(point1.getLatitude());
    double long1 = toRadians(point1.getLongitude());
    double lat2 = toRadians(point2.getLatitude());
    double long2 = toRadians(point2.getLongitude());

    double latDifference = lat2 - lat1;
    double longDifference = long2 - long1;

    // use the haversine formula; proof is very tough, but I used the formula from https://www.movable-type.co.uk/scripts/latlong.html
    // Haversine formula:
    // a = sin²(Δφ/2) + cos φ1 ⋅ cos φ2 ⋅ sin²(Δλ/2)
    // c = 2 ⋅ atan2( √a, √(1−a) )
    // d = R ⋅ c
    // its used to calculate the distance between points on a spherical surface
    // this implementation is made to fit lat and long
    double a = sin(latDifference / 2.0) * sin(latDifference / 2.0) + cos(lat1) * cos(lat2) * sin(longDifference / 2.0) * sin(longDifference / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    // 6371 is an approx estimate of the radius of earth in km
    return 6371.0 * c;
}

// Name - toRadians(const double& degree)
// Desc - changes degrees into radians
double KDTree::toRadians(const double& degree){
    return (((M_PI) / 180) * degree);
}

// Name - dump()
// Desc - outputs the contents of the tree
void KDTree::dump() const{
    dump(m_root);
    cout << endl; 
}

// Name - dump(GeoPoint* point)
// Desc - overloaded function to allow recursion
void KDTree::dump(GeoPoint* point) const{
    if (point != nullptr){
        cout << "(";
        dump(point->m_left);//first visit the left child
        cout << point->m_name << ":" << point->m_latitude << ":" << point->m_longitude;//second visit the node itself
        dump(point->m_right);//third visit the right child
        cout << ")";
    }
}
