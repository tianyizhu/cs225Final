#include <string>
#include <vector>

using namespace std;

struct Route{
    int src;
    int des;
    int stop;
    string plane;
    string airline; 
};


struct Airport{
    string name;
    string city;
    string country;
    string iata;    //三位IATA
    float la;       //纬度
    float lo;
};


void read_dat(string filename, vector<Airport>& airports, vector<Route>& routes);

bool is_airport_iata(string s);  //check if three upcase letters.

bool is_number(string s);
