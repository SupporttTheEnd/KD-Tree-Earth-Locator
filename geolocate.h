// CMSC 341 - Fall 2023 - HW5

#ifndef GEOLOCATE_H
#define GEOLOCATE_H
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
class Tester;
class KDTree;

class GeoPoint {
public:
    friend class KDTree;
    friend class Tester;
    // constructor with default values 
    GeoPoint(double latitude = 0.0, double longitude = 0.0, string name = "") {
        m_latitude = latitude;
        m_longitude = longitude;
        m_name = name;
        m_left = nullptr;
        m_right = nullptr;
    }

    // standard getters
    double getLatitude() const {return m_latitude;}
    double getLongitude() const {return m_longitude;}
    string getName() const {return m_name;}
    GeoPoint* getLeft() const {return m_left;}
    GeoPoint* getRight() const {return m_right;}

    // standard setters
    void setLatitude(double latitude) {m_latitude = latitude;}
    void setLongitude(double longitude) {m_longitude = longitude;}
    void setName(string name) {m_name = name;}
    void setLeft(GeoPoint* left) {m_left = left;}
    void setRight(GeoPoint* right) {m_right = right;}

private:
    // private member variables
    double m_latitude;
    double m_longitude;
    string m_name;
    GeoPoint* m_left;
    GeoPoint* m_right;
};

class KDTree {
public:
    friend class Tester;
    KDTree();
    ~KDTree();
    void insert(const GeoPoint& point);
    GeoPoint nearest(const GeoPoint& point);
    void dump() const;
private:
    GeoPoint* m_root; 

    // ***************************************************
    // Any private helper functions must be delared here!
    // ***************************************************
    // overloaded functions
    void dump(GeoPoint* point) const;
    void clear(GeoPoint*& node);
    void insert(const GeoPoint& point, GeoPoint*& node, int depth);
    void nearest(const GeoPoint& point, GeoPoint*& node, int depth, GeoPoint& nearest);
    double calculateDistance(const GeoPoint& point1, const GeoPoint& point2);
    double toRadians(const double& degree);
};

#endif