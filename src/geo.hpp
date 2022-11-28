#pragma once

#include<iostream>
#include<cmath>

#define pi 3.14159265358979323846

using namespace std;

double cal_dis(double lat1, double long1, double lat2, double long2) {
    double dist;
    double earthR;

    dist = sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(long1 - long2);
    dist = acos(dist);
    dist = (earthR * pi * dist) / 180;

    return dist;
}
