#include <iostream>
#include <utility> 
#include <vector>
#include <cmath>
#include "geo.hpp"
#include "io.h"
#include "../cs225/PNG.h" 

using namespace std;
using namespace cs225;



void drawSquare(PNG& source, double lo, double la, double size, HSLAPixel& color) {

    int sW = source.width();
    int sH = source.height();

    double lo0 = lo - size;
    double la0 = la - size;
    
    if (la0<-90) la0 = -90;
    if (lo0<-180) lo0 = -180;

    double lo1 = lo + size;
    double la1 = la + size;

    if (la1>90) la1 = 90;
    if (lo1>180) lo1 = 180;

    
    auto reti = eq_rect_proj(lo0, la0, sW, sH);
    int x0 = reti.first;
    int y0 = reti.second;
    
    reti = eq_rect_proj(lo1, la1, sW, sH);
    int x1 = reti.first;
    int y1 = reti.second;

    for (int x=x0; x<=x1; x++)
        for (int y=y0; y>=y1; y--)
            source.getPixel(x,y) = color;
}





void draw(PNG& output, PNG& source, int size, double lo0, double la0)   {

    //get size of source:
    int sW = source.width();
    int sH = source.height();

    //resize output to size*size:
    output.resize(size, size);


    for (int x=0; x<size; x++)
        for (int y=0; y<size; y++) {
            
            // cout << x << " xy  "<<y <<endl;
            auto retd = invr_ortho_proj(x, y, size, lo0, la0, 10);
            double lo = retd.first;
            double la = retd.second;
            // cout << la << " lalo "<<lo <<endl;
            if (lo<=-999)  {output.getPixel(x,y) = HSLAPixel(209, 0.24, 0.5);}
                else {
                    auto reti = eq_rect_proj(lo, la, sW, sH);
                    int sX = reti.first;
                    int sY = reti.second;
                    // cout << sX << " sxsy "<< sY << endl<<endl;
                    
                    //copy sX to x, sY to Y:
                    output.getPixel(x,y) = source.getPixel(sX, sY);
                }

        }

}


void makeAnimation(vector<Airport>& airports, vector<unsigned>& path, PNG source, int size = 360)   {
    
    PNG output;
    int idx = 100;

    HSLAPixel red(0,1,0.5);
    HSLAPixel grey(0,0,0.5);
    HSLAPixel white(0,0, 1);
        
    double lo0, la0, lo1, la1;
    vector<pair<double, double>> waypoints;

    for (int i=0; i<path.size(); i++)   {
        lo1 = airports[path[i]].lo;
        la1 = airports[path[i]].la;

        if (i==0)   {

            draw(output, source, size ,lo1 , la1/2);

            stringstream optname1;
            optname1 << "motion/" << idx << ".png";
            idx+=1;
            output.writeToFile(optname1.str());
        }
        else {
            // double dislo = lo1 - lo0;
            // if (dislo > 180) dislo = dislo-360;
            // if (dislo < -180) dislo = dislo+360;

            // double dis = sqrt(dislo*dislo+(la1-la0)*(la1-la0));

            // double dlo = dislo/dis*2;
            // double dla = (la1-la0)/dis*2;

            // double lo = lo0 + dlo;
            // double la = la0 + dla;
            // int count = 0;
            // do{
                
            //     drawSquare(source, lo, la, 0.2, grey);
            //     // draw(output, source, 400 ,lo , la/1.5);
            //     // stringstream optname;
            //     // optname << "motion/" << idx << ".png";
            //     // idx+=1;
            //     // output.writeToFile(optname.str());

            //     lo+=dlo;
            //     la+=dla;
            //     if (lo > 180) lo = lo-360;
            //     if (lo < -180) lo = lo+360;

            //     cout << lo << " , " << la << endl;
            //     count ++;

            // }   while (cal_dis( la1, lo1, la, lo) > 100 && count<500);
            get_waypoint(waypoints, la0,lo0, la1, lo1);
            for (auto it : waypoints)   {
                // cout << it.first << " , "<< it.second <<endl;
                drawSquare(source, it.first, it.second, 0.4, white);

                draw(output, source, size , it.first , it.second/2);
                stringstream optname1;
                optname1 << "motion/" << idx << ".png";
                idx+=1;
                output.writeToFile(optname1.str());
            }
            
        }


        drawSquare(source, lo1, la1, 0.6, red);
        draw(output, source, size ,lo1 , la1/2);
        
        stringstream optname;
        optname << "motion/" << idx << ".png";
        idx+=1;
        output.writeToFile(optname.str());

        lo0 = lo1;
        la0 = la1;
    }


    source.writeToFile("output-source.png");

}


