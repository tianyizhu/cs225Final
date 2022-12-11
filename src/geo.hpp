#pragma once
#include<iostream>
#include<cmath>
#include <utility> 
#include <vector>

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

    // if (x<0) x+=w;
    // if (y<0) y+=h;
 
    return make_pair(x,y);
}

pair<double, double> invr_ortho_proj(int x, int y, int size, double lo0, double la0 = 0, int margin = 10) {

    size -= (margin*2);

    if (size < 0) return make_pair(-1000,-1000);
    
    x-=margin;
    y-=margin;


    if (x<0 || x>size || y<0 || y>size) return make_pair(-1000,-1000);

    x-=size/2;
    y-=size/2;
    

    y = -y;
    

    lo0 = lo0/180*pi;
    la0 = la0/180*pi;
    
    
    double rou = sqrt(x*x + y*y);

    if (rou>size/2) return make_pair(-1000,-1000);

    double c = asin(rou / (size/2));
    // double c = asin(rou / (size*sqrt(2)));

    double lo = lo0 + atan2( x*sin(c),(rou*cos(c)*cos(la0) - y*sin(c)*sin(la0)) );
    double la = asin(cos(c)*sin(la0)+y*sin(c)*cos(la0)/rou);

    lo = lo*180/pi;
    la = la*180/pi;
    
    if (lo>180) lo-=360;
    if (lo<-180) lo+=360;

    if (la>90) la-=180;
    if (la<-90) la+=180;


    return make_pair(lo,la);

}


void get_waypoint(vector<pair<double, double>>& ret, double la0,double lo0, double la1, double lo1, double res = 1)   {
    double d = cal_dis(la1, lo1, la0, lo0) / 6378;
    la1 = la1/180*pi;
    la0 = la0/180*pi;
    lo1 = lo1/180*pi;
    lo0 = lo0/180*pi;
    res = res/180*pi;
    ret = {};

    double delta = 1/(d/res);

    for (int i=1; i*delta < 1; i++) {
        double f = i*delta;
        
        double a = sin((1-f)*d) / sin(d);
        double b = sin(f*d) / sin(d);
        double x = a*cos(la0) * cos(lo0) + b * cos(la1) * cos(lo1);
        double y = a*cos(la0) * sin(lo0) + b * cos(la1) * sin(lo1);
        double z = a*sin(la0) + b*sin(la1);
        double la = atan2(z, sqrt(x*x + y*y))*180/pi;
        double lo = atan2(y, x)*180/pi;


        ret.push_back(make_pair(lo,la));
    }

}




    

