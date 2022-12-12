#include <string>
#include <vector>
#include <map>
#include <utility>  
#include "drawing.hpp"
#include "../cs225/png.h"


#include "graph.hpp"
#include "geo.hpp"
#include "io.h"

using namespace std;
using namespace cs225;

int main() {
    // string file_route = "";
    
    // part 1: io
    vector<Airport> airports; 
    vector<Route> routes;
    read_airports_dat("airports.dat", airports);
    // cout << "read airport done!!" << endl;
    read_routes_dat("routes.dat", routes);
    // cout << "read done!!" << endl;



    //part 2: build graph
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
    // cout << "build graph done!!" << endl;
    cout << "Welcome to plane path finder!!" << endl;
    // g.print_graph(0,100);


    
    //part 3: get start and des
    cout << "Enter your start and destination ariport code:" << endl;
    string sString, dString;
    cin>>sString;
    cin>>dString;
    transform(sString.begin(), sString.end(), sString.begin(), ::toupper);
    transform(dString.begin(), dString.end(), dString.begin(), ::toupper);
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
    // g.print_graph(src, src);
    // g.print_graph(des, des);


    vector<unsigned> path;
    string respond, filename;
    float dis;

    cout << "Choose the flight route you prefer:" << endl;
    cout << "1) shortest distance onboard.  2) least transfer flights.  3) take a look at both." << endl << "your choices:";
    cin >> respond;


    if (respond != "1" && respond != "3" && respond != "2")   {
        cout << "invalid choice!" << endl;
        return 0;
    }



    //part 4: dijkstra
    if (respond == "1" || respond == "3")   {
        dis = dij(g, src, des, path);
        // cout<< "dij done!!"<<endl;

        if (path[0] == NULLV) cout<<"path not found"<<endl;
                        else {
            cout << "shortest distance path:"<<endl;
            for (int id : path)
                cout << " -- " << airports[id].iata ;
            cout << "  arrived"<<endl;
            cout << "total distance: " << dis << " km" << endl;
        }
    }
    
    //part 5: IDDFS
    if (respond == "2" || respond == "3")   {
        dis = IDDFS(g, src, des, path);
        // cout<< "IDDFS done!!"<<endl;

        if (dis < 0) cout<<"path not found"<<endl;
                        else {
            cout << "least transfer flights:"<<endl;
            for (int id : path)
                cout << " -- " << airports[id].iata ;
            cout << "  arrived"<<endl;
            cout << "total distance: " << dis << " km" << endl;
        }
    }


    // part 6: animation
    // PNG earth;
    cout<< "generate the path animation? (yes or no):";
    cin >> respond;
    if (respond != "yes") return 0;
    cout<< "Enter the name of the output file:";
    cin >> filename;

    PNG source;
    // you can choose which base map you want to use here:
    // source.readFromFile("../political-world-map.png");
    source.readFromFile("../3840px-Blue_Marble_2002.png");

    //if motion folder doesn't exist, add it. If exist, there will just be a warning:
    system("mkdir motion");

    makeAnimation(airports, path, source);
    cout << "animation done!" << endl;

    //combine the pngs of a walking of the path into a gif:
    system( ("convert motion/*.png "+filename+".gif").c_str() );

    return 0;
}
