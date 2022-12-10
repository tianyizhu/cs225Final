#include <string>
#include <vector>
#include <utility>  
#include "../cs225/png.h" 

#include "geo.hpp"

using namespace std;
using namespace cs225;

int main() {

    PNG output;//runtime error
// undefined reference to `cs225::PNG::PNG(unsigned int, unsigned int)'
// /usr/bin/ld: main.cpp:(.text+0x18c6): undefined reference to `cs225::PNG::~PNG()'

    //read source from "../3840px-Blue_Marble_2002.png":

    draw(PNG& output, PNG& source, 720, -88);
    
    //output to "output0.png":

    return 0;
}
