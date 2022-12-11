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
    for (int lo=-50; lo<50; lo++)  {

        draw(output, source, 400 ,lo , 30);
        
        //output to "output0.png":
        // output.writeToFile("output.png");
        stringstream optname;
        optname << "motion/" << lo+150 << ".png";
        output.writeToFile(optname.str());
    }

    
    // stringstream command;
    // command << "convert motion/"<<"*.png "<<"output.gif"
    // system("convert motion/*.png output1.gif");


    return 0;
}



