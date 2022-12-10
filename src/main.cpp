#include <string>
#include <vector>
#include <map>
#include <utility>  
#include "../cs225/png.h"


#include "graph.hpp"
#include "geo.hpp"
#include "io.h"

using namespace std;
using namespace cs225;

int main() {
    // string file_route = "";
    
    pair<int,int> xy = eq_rect_proj(-88,40,3840,1920);

    cout << xy.first << " , " << xy.second << endl;

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

    vector<unsigned> path;
    float dis = dij(g, src, des, path);
    cout<< "dij done!!"<<endl;

    if (path[0] == NULLV) cout<<"path not found"<<endl;
                    else {
        cout << "shortest distance path:"<<endl;
        for (int id : path)
            cout << " -- " << airports[id].iata ;
        cout << "  arrived"<<endl;
        cout << "total distance: " << dis << " km" << endl;
    }
    

    dis = IDDFS(g, src, des, path);
    cout<< "IDDFS done!!"<<endl;

    if (dis < 0) cout<<"path not found"<<endl;
                    else {
        cout << "least transfer flights:"<<endl;
        for (int id : path)
            cout << " -- " << airports[id].iata ;
        cout << "  arrived"<<endl;
        cout << "total distance: " << dis << " km" << endl;
    }

    // PNG earth;

    return 0;
}
