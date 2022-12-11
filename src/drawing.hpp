#include <iostream>
#include <utility> 
#include "geo.hpp"
#include "../cs225/PNG.h" 

using namespace std;
using namespace cs225;

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
