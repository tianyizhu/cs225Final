#include <string>
#include <vector>
#include "graph.hpp"
#include "geo.hpp"

using namespace std;

struct Route{
    int src;
    int des;
    int stop;
    string plane;
};



struct Airport{
    string name;
    string city;
    string country;
    string code;    //三位IATA
    float la;       //纬度
    float lo;
};


int main() {
    vector<Airport> airports;
    vector<Route> routes;
    return 0;
}

