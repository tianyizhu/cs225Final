#include <iostream>
#include <utility> 
#include "geo.hpp"
#include "../cs225/PNG.h" 

using namespace std;
using namespace cs225;

void draw(PNG& output, PNG& source, int size, double lo0)   {

    //get size of source:
    int sW = source.width();
    int sH = source.height();

    //resize output to size*size:
    output.resize(size, size);


    for (int x=0; x<size; x++)
        for (int y=0; y<size; y++) {
            
            // cout << x << " xy  "<<y <<endl;
            double lo = invr_ortho_proj(x, y, size, lo0, 30, 10).first;
            double la = invr_ortho_proj(x, y, size, lo0, 30, 10).second;
            // cout << la << " lalo "<<lo <<endl;
            if (lo<=-999)  {output.getPixel(x,y) = HSLAPixel(209, 0.24, 0.5);}
                else {
                    int sX = eq_rect_proj(lo, la, sW, sH).first;
                    int sY = eq_rect_proj(lo, la, sW, sH).second;
                    // cout << sX << " sxsy "<< sY << endl<<endl;
                    

                    //copy sX to x, sY to Y:
                    output.getPixel(x,y) = source.getPixel(sX, sY);
                }

        }

}
