#pragma once

#include <iostream>
#include <utility> 
#include "geo.hpp"
#include "../cs225/png.h"

using namespace std;
using namespace cs225;

void draw(PNG& output, PNG& source, int size, double lo0)   {

    //get size of source:
    int sW = ;
    int sH = ;

    //resize output to size*size:


    for (int x=0; x<size; x++)
        for (int y=0; y<size; y++) {
            double lo = invr_ortho_proj(x, y, size, lo0).first;
            double la = invr_ortho_proj(x, y, size, lo0).second;

            int sX = eq_rect_proj(lo, la, sW, sH).first;
            int sY = eq_rect_proj(lo, la, sW, sH).second;

            //copy sX to x, sY to Y:

        }

}
