#pragma once

#include<iostream>
#include<cmath>

#define pi 3.14159265359

using namespace std;

double cal_dis(double lat1, double long1, double lat2, double long2) {
    double dis;
    double earthR = 6378;
    lat1 = lat1/180*pi;
    lat2 = lat2/180*pi;
    long1 = long1/180*pi;
    long2 = long2/180*pi;

    dis = sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(long1 - long2);
    dis = acos(dis);
    dis = earthR * dis;

    return dis;
}
