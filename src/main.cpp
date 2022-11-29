#include <string>
#include <vector>
#include <map>

#include "graph.hpp"
#include "geo.hpp"
#include "io.h"

int main() {
    string filename = "";
    vector<Airport> airports; 
    vector<Route> routes;
    read_dat(filename, airports, routes);

    return 0;
}
