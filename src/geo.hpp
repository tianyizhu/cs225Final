#pragma once

#include<iostream>
#include<cmath>
#include <utility> 

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

pair<int, int> eq_rect_proj(double lo, double la, int w, int h, double lo0 = -180, double la0 = 90, double la1 = 0) {
    double dis;
    // la = la/180*pi;
    // lo = lo/180*pi;
    // lo0 = lo0/180*pi;
    // la0 = la0/180*pi;
    // la1 = la1/180*pi;
    double fx = (lo-lo0)*w/360;
    double fy = (la0-la)*h/180;

    int x = (int)fx % w;
    int y = (int)fy % h;

    return make_pair(x,y);
}

pair<double, double> invr_ortho_proj(int x, int y, int size, double lo0, double la0 = 0, int margin = 10) {

    size -= (margin*2);

    if (size < 0) return make_pair(-1000,-1000);
    
    x-+margin;
    y-=margin;

    x-=size/2;
    y-=size/2;

    lo0 = lo0/180*pi;
    
    double rou = sqrt(x*x + y*y);
    double c = asin(rou / (size/2*sqrt(2)));

    double lo = lo0 + atan( x*sin(c) / (rou*cos(c)*cos(lo0) - y*sin(c)*sin(lo0)) );

    double la = asin(cos(c)*sin(la0)+y*sin(c)*cos(la0)/rou);

    lo = lo/180*pi;
    la = la/180*pi;

    return make_pair(lo,la);

}
