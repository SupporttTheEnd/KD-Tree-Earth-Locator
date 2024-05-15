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


void KDTree::insert(const GeoPoint& point){
    if (point.getLatitude() < -90.0 || point.getLatitude() > 90.0) {
        return; 
    }

    if (point.getLongitude() < -180.0 || point.getLongitude() > 180.0) {
        return; 
    }
    insert(point, m_root, 0);
}

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
    } else {
        insert(point, node->m_right, depth + 1);
    }
    
}

GeoPoint KDTree::nearest(const GeoPoint& point) {
    GeoPoint close; 
    nearest(point, m_root, 0, close); 
    return close;
}

void KDTree::nearest(const GeoPoint& point, GeoPoint*& node, int depth, GeoPoint& close) {
    // Base case: If the current node is NULL, return
    if (node == nullptr) {
        return;
    }

    bool compLat = (depth % 2 == 0);

    // Check if the current node is closer than the currently known nearest neighbor
    if (calculateDistance(point, *node) < calculateDistance(point, close)) {
        close = *node;
    }

    // Visit subtrees in the most promising order
    if ((compLat && point.getLatitude() < node->getLatitude()) ||
        (!compLat && point.getLongitude() < node->getLongitude())) {
        nearest(point, node->m_left, depth + 1, close);
        nearest(point, node->m_right, depth + 1, close);
    } 
    else {
        nearest(point, node->m_left, depth + 1, close);
        nearest(point, node->m_right, depth + 1, close);
    }
}


double KDTree::calculateDistance(const GeoPoint& point1, const GeoPoint& point2) {
    // Calculate differences in latitude and longitude
    double latDiff = point2.getLatitude() - point1.getLatitude();
    double lonDiff = point2.getLongitude() - point1.getLongitude();

    if (abs(lonDiff) > 180.0) {
        lonDiff = 360.0 - abs(lonDiff);
    }

    // Simple distance approximation (ignoring curvature)
    double distance = sqrt(latDiff * latDiff + lonDiff * lonDiff);

    return distance;
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
