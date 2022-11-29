#include <string>
#include <vector>

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


void read_dat(string filename, vector<Airport>& airports, vector<Route>& routes);

