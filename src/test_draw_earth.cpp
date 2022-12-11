#include <string>
#include <vector>
#include <utility>  
#include "../cs225/PNG.h" 

#include "geo.hpp"
#include "drawing.hpp"

using namespace std;
using namespace cs225;

int main() {

    PNG output;

    PNG source;
    // source.readFromFile("../political-world-map.png");
    source.readFromFile("../3840px-Blue_Marble_2002.png");
    draw(output, source, 720, -88);
    
    //output to "output0.png":
    // output.writeToFile("output.png");
    output.writeToFile("output1.png");


    return 0;
}



