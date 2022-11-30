#include <string>
#include <vector>
#include <map>

#include "graph.hpp"
#include "geo.hpp"
#include "io.h"

using namespace std;

int main() {
    // string file_route = "";
    vector<Airport> airports; 
    vector<Route> routes;
    read_airports_dat("airports.dat", airports);
    cout << "read airport done!!" << endl;
    read_routes_dat("routes.dat", routes);

    cout << "read done!!" << endl;
    map<string, int> airportID;
    for (int i=0; i<airports.size(); i++)   {
        // if (airports[i].iata.length() != 5)
        //     cout <<airports[i].iata <<"  exception!";

        airportID[airports[i].iata] = i;
    }

    Graph g;

    // g.print_graph(0,100);

    for (Route r: routes)   {
        
        // cout <<r.src <<"   " << r.des << endl;
        float dis = cal_dis(airports[r.src].la, airports[r.src].lo, airports[r.des].la, airports[r.des].lo);

        // int existing_distance get_dis(
        // cout <<r.src <<"   " << r.des << endl;
        g.add_edge(r.src, r.des, dis);
    }  
    
    cout << "build graph done!!" << endl;
    // g.print_graph(0,100);
    
    string sString, dString;
    cin>>sString;
    cin>>dString;

    sString = '"'+sString+'"';
    dString = '"'+dString+'"';
    
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

    unsigned src = findS->second;
    unsigned des = findD->second;

    g.print_graph(src, src);
    g.print_graph(des, des);

    dij(g, src, des, airports);

    return 0;
}
