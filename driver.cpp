// Title: geolocate.cpp
// Author: Andrew Tang
// Date: 12/7/2023
// Description: This is the main file for geolocate.cpp

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
    KDTree tree;

    // insert some famous cities with latitude, longitude, and place
    tree.insert(GeoPoint(37.7749, -122.4194, "San Francisco, USA"));
    tree.insert(GeoPoint(34.0522, -118.2437, "Los Angeles, USA"));
    tree.insert(GeoPoint(41.8781, -87.6298, "Chicago, USA"));
    tree.insert(GeoPoint(40.7128, -74.0060, "New York, USA"));
    tree.insert(GeoPoint(39.2904, -76.6122, "Baltimore, USA"));
    tree.insert(GeoPoint(51.5074, -0.1278, "London, United Kingdom"));
    tree.insert(GeoPoint(48.8566, 2.3522, "Paris, France"));
    tree.insert(GeoPoint(55.7558, 37.6176, "Moscow, Russia"));
    tree.insert(GeoPoint(-34.6085, -58.3735, "Buenos Aires, Argentina"));
    tree.insert(GeoPoint(-33.8688, 151.2093, "Sydney, Australia"));
    tree.insert(GeoPoint(35.6895, 139.6917, "Tokyo, Japan"));
    tree.insert(GeoPoint(-23.5505, -46.6333, "Sao Paulo, Brazil"));
    tree.insert(GeoPoint(19.4326, -99.1332, "Mexico City, Mexico"));
    tree.insert(GeoPoint(37.5665, 126.9780, "Seoul, South Korea"));
    tree.insert(GeoPoint(31.2304, 121.4737, "Shanghai, China"));
    tree.insert(GeoPoint(39.9042, 116.4074, "Beijing, China"));
    tree.insert(GeoPoint(23.1291, 113.2644, "Guangzhou, China"));
    tree.insert(GeoPoint(30.5728, 114.3625, "Wuhan, China"));
    tree.insert(GeoPoint(22.5431, 114.0579, "Shenzhen, China"));
    tree.insert(GeoPoint(34.3416, 108.9398, "Xi'an, China"));
    tree.insert(GeoPoint(31.9686, 99.9018, "Lhasa, China"));
    tree.insert(GeoPoint(-33.8678, 151.2073, "Sydney, Australia"));
    tree.insert(GeoPoint(55.7558, 37.6176, "Moscow, Russia"));
    tree.insert(GeoPoint(40.7128, -74.0060, "New York, USA"));
    tree.insert(GeoPoint(34.0522, -118.2437, "Los Angeles, USA"));
    tree.insert(GeoPoint(41.9028, 12.4964, "Rome, Italy"));
    tree.insert(GeoPoint(-6.2088, 106.8456, "Jakarta, Indonesia"));
    tree.insert(GeoPoint(-22.9068, -43.1729, "Rio de Janeiro, Brazil"));
    tree.insert(GeoPoint(35.6895, 139.6917, "Tokyo, Japan"));
    tree.insert(GeoPoint(37.7749, -122.4194, "San Francisco, USA"));
    tree.insert(GeoPoint(-34.6085, -58.3735, "Buenos Aires, Argentina"));
    tree.insert(GeoPoint(1.3521, 103.8198, "Singapore"));
    tree.insert(GeoPoint(55.9533, -3.1883, "Edinburgh, United Kingdom"));
    tree.insert(GeoPoint(45.4215, -75.6993, "Ottawa, Canada"));
    tree.insert(GeoPoint(-26.2041, 28.0473, "Johannesburg, South Africa"));
    tree.insert(GeoPoint(19.0760, 72.8777, "Mumbai, India"));
    tree.insert(GeoPoint(51.1657, 10.4515, "Berlin, Germany"));
    tree.insert(GeoPoint(50.1109, 8.6821, "Frankfurt, Germany"));
    tree.insert(GeoPoint(-33.918861, 18.423300, "Cape Town, South Africa"));
    tree.insert(GeoPoint(6.5244, 3.3792, "Lagos, Nigeria"));
    tree.insert(GeoPoint(-1.286389, 36.817223, "Nairobi, Kenya"));
    tree.insert(GeoPoint(53.3498, -6.2603, "Dublin, Ireland"));
    tree.insert(GeoPoint(38.8951, -77.0364, "Washington, D.C., USA"));
    tree.insert(GeoPoint(78.2232, 15.6267, "Longyearbyen, Svalbard, Norway"));
    tree.insert(GeoPoint(-77.8469, 166.6681, "McMurdo Station, Antarctica"));
    tree.insert(GeoPoint(90.0, 0.0, "North Pole"));
    tree.insert(GeoPoint(-90.0, 0.0, "South Pole"));
       
    cout << "\t\t    \033[1;31mWelcome\033[0m " << "\033[1;32mto\033[0m " << "\033[1;33mGeoLocate\033[0m" << endl;

    cout <<"\033[1;34m                             |                                 "<< endl; 
    cout <<"                       --====|====--                           "<< endl; 
    cout <<"                             |                                 "<< endl; 
    cout <<"                         .-\"\"\"\"\"-.                             "<< endl; 
    cout <<"                       .'_________'.                           "<< endl; 
    cout <<"                      /_/_|__|__|_\\_\\                          "<< endl; 
    cout <<"                     ;'-._       _.-';                         "<< endl; 
    cout <<",--------------------|    `-. .-'    |--------------------,    "<< endl; 
    cout <<"   ``""--..__    ___   ;       '       ;   ___    __..--""``     "<< endl; 
    cout <<"           `\"-// \\\\.._\\             /_..// \\\\\"`               "<< endl; 
    cout <<"              \\\\_//    '._       _.'    \\\\_//                  \033[0m"<< endl << endl; 

    cout << "\t      \033[1;31mFIND\033[0m " << "\033[1;32mTHE\033[0m " << "\033[1;33mNEAREST\033[0m "<< "\033[1;34mCITY\033[0m " << "\033[1;35mTO\033[0m " << "\033[1;36mYOU!\033[0m" << endl;
    
    // Accept user input for a query location
    double userLatitude;
    double userLongitude;

    // this will read in first valid number
    cout << "    \033[1;37mThe first valid number in the line will be accepted\033[0m" << endl; 

    // loop until a valid double in entered in 
    bool validLatitude = false;
    while (!validLatitude) {
        cout << "Enter the latitude of your location (-90,90) [inclusive]: " << endl;
        if (cin >> userLatitude && userLatitude >= -90.0 && userLatitude <= 90.0) {
            validLatitude = true;
        } else {
            // clear the error and the buffer
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a valid number within the range -90 to 90." << endl;
        }
    }

    // clear the buffer before next read in 
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // loop until a valid double in entered in 
    bool validLongitude = false;
    while (!validLongitude) {
        cout << "Enter the longitude of your location (-180,180) [inclusive]: " << endl;
        if (cin >> userLongitude && userLongitude >= -180.0 && userLongitude <= 180.0) {
            validLongitude = true;
        } else {
            // clear the error and the buffer
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid input! Please enter a valid number within the range -180 to 180." << endl;
        }
    }

    // make a geopoint and find nearest neighbor
    GeoPoint userPoint(userLatitude, userLongitude);
    GeoPoint nearestNeighbor = tree.nearest(userPoint);

    // output the result
    cout << "Query Point: (" << userPoint.getLatitude() << ", " << userPoint.getLongitude() << ")" << endl;
    
    cout << "\t\t     \033[1;31mNEAREST\033[0m " << "\033[1;32mCITY\033[0m " << "\033[1;33mIS\033[0m "<< "\033[1;34m:\033[0m " << endl;

    cout << "Nearest Neighbor: " << nearestNeighbor.getName() << " (" << nearestNeighbor.getLatitude() << ", " << nearestNeighbor.getLongitude() << ")" << endl;

    cout << "\t\t     \033[1;31mHAVE\033[0m " << "\033[1;32mA\033[0m " << "\033[1;33mNICE\033[0m "<< "\033[1;34mDAY!\033[0m " << endl;
    return 0;
}
