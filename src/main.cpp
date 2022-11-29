#include <string>
#include <vector>
#include <map>


#include "graph.hpp"
#include "geo.hpp"
#include "io.h"

using namespace std;

int main() {
    string filename = "";
    vector<Airport> airports; 
    vector<Route> routes;
    read_dat(filename, airports, routes);

    map<sting, int> airportID;
    for (int i=0; i<airports.size(); i++)   {
        if (airports[i].iata.length() != 3)
            cout <<airports[i].iata <<"  exception!";

        airportID[airports[i].iata] = i;
    }

    Graph g;

    g.print_graph(0,100);

    for (Route r: routes)   {
        
        float dis = cal_dis(airports[r.src].la, airports[r.src].lo, airports[r.des].la, airports[r.des].lo);

        // int existing_distance get_dis(
        g.add_edge(r.src, r.des, dis);
    }  
    
    string sString, dString;
    cin<<sString<<endl<<dString;
    
    auto findS = airportID.find(sString);
    auto findD = airportID.find(dString);

    if (findS == airportID.end())   {
        cout<<"src doesn't exist!"<<endl;
        return 1;
    }

    if (findD == airportID.end())   {
        cout<<"DES doesn't exist!"<<endl;
        return 1;
    }

    unsigned src = *findS;
    unsigned des = *findD;

    g.print_graph(src,src);
    g.print_graph(des,des);


    return 0;
}
