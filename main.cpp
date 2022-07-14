#include <iostream>
#include <utility>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string>
#include <bitset>
#include <algorithm>
#include <utility>

#include "Point.hpp"

using namespace std;

/* Global Data */
const int n_data = 5000;
const int dimensions = 10;
const int bits = 5;

typedef Point<dimensions,int> point;
typedef unsigned long ul;

vector<point> myPoints(n_data);
vector<pair<ul,point*>> z_curve;

/* TO POINTS */
int get_RandomValue ()
{
    return rand() % 20;
}

point generate_Point ()
{
    point p;

    for (int i = 0; i < dimensions; ++i)
        p[i] = get_RandomValue();
    
    return p;
}

void fill_Vector ()
{
    for (int i = 0; i < n_data; ++i)
        myPoints[i] = generate_Point();
}

double absolute(ul n)
{
    if (n > 0)
        return double(n);
    return n * -1;
}

/* Z CURVE */
vector<string> get_Bits(point P)
{
    vector<string> bits_coordinates;
    
    for (int j = 0; j < dimensions; ++j)
        bits_coordinates.push_back(bitset<bits>(P.m_coordinates[j]).to_string());
    
    return bits_coordinates;
}

ul z_value(vector<string> bits_coordinates)
{
    string z;
    
    for (int i = 0; i < bits; i++)
        for (int j = 0; j < dimensions; j++)
                z += bits_coordinates[j][i];
    return bitset<bits*dimensions>(z).to_ulong();
}

void z_order()
{
    vector<string> bits_coordinates;
    ul z_val;

    for (int i = 0; i < n_data; ++i)
    {
        bits_coordinates = get_Bits(myPoints[i]);    
        z_val = z_value(bits_coordinates);

        z_curve.push_back(make_pair(z_val,&myPoints[i]));
        myPoints[i].z_value = z_val;

        bits_coordinates.clear();
    }

    sort(z_curve.begin(),z_curve.end());
}

/* NN */
typedef pair<double,point*> dist_point;

/* "BRUTE FORCE" */
vector<dist_point> knn(point p, int k)
{
    vector<dist_point> distances;

    for (int i = 0; i < n_data; ++i)
        distances.push_back(make_pair(euclideanDistance(p, myPoints[i]),&myPoints[i]));
    
    sort(distances.begin(),distances.end());

    return vector<dist_point>(distances.begin() + 1, distances.begin() + k + 1);
}

vector<dist_point> z_knn(point p, int k)
{
    int i;
    
    vector<dist_point> distances;
    
    for (i = 0; i < n_data; ++i)
        distances.push_back(make_pair(absolute(p.z_value - z_curve[i].second->z_value),z_curve[i].second));
    
    sort(distances.begin(), distances.end());
    
    return vector<dist_point>(distances.begin() + 1, distances.begin() + k + 1);
}


void match_queries(vector<dist_point>& knn1, vector<dist_point>& knn2)
{
    int equals = 0;
    for (int i = 0; i < knn1.size(); ++i)
    {
        for (int j = 0; j < knn1.size(); ++j)
        {
            if (knn1[i].first == knn2[j].first)
            {
                cout << "POINT[N]: ";
                knn1[i].second->printContent();
                cout << "POINT[Z]: ";
                knn2[j].second->printContent();
                cout << "\n";
                equals++;
            }
        }
    }

    cout << "EQUAL PERCENTAGE -> " << (double(equals)/double(knn1.size()))*100 << "%" << endl;

}

int main()
{
    /* Random Values */
    srand(time(NULL)); 
    fill_Vector();
    
    /* Z-ORDER */
    z_order();
    
    int k[] = {5, 10, 15, 20};
    int size = sizeof(k)/sizeof(k[0]);
    
    for ( int i = 0; i < size; ++i )
    {
        /* NN */
        vector<dist_point> knn_real = knn(myPoints[500], k[i]);
        vector<dist_point> knn_z_ord = z_knn(myPoints[500], k[i]);
        
        /* MATCH RESULTS */
        cout << "-------------   "<< k[i] << "   -------------\n";
        match_queries(knn_real, knn_z_ord);
        cout << "-------------   *     -------------\n";
    }

    return 0;
}
