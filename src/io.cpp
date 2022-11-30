#include "io.h"
#include <fstream>
#include <iostream>

using namespace std;

void read_airports_dat(const string filename, vector<Airport>& airports) {
    ifstream file(filename);
    airports.resize(14111);

    while(!file.eof()) {
        //regular read into a vector
        string line;
        vector<string> temp;
        getline(file, line);
        SplitString(line, ',', temp);

        Airport airport;
        airport.name = temp[1];
        airport.city = temp[2];
        airport.country = temp[3];
        airport.iata = temp[4];
        // cout << temp[6] << temp[7] << endl;
        airport.la = stof(temp[6]);
        airport.lo = stof(temp[7]);
        airports[stoi(temp[0])] = airport;

    }
    file.close();
}
void read_routes_dat(const string filename, vector<Route>& routes) {
        ifstream file(filename);

    while(!file.eof()) {
        //regular read into a vector
        string line;
        vector<string> temp;
        getline(file, line);
        SplitString(line, ',', temp);

        

        Route route;
        // cout << temp[3] << "   "<<temp[5] << endl;
        if (temp[3]=="\\N" || temp[5]=="\\N") continue; 
        // if (temp[3]=="\\N")  
        //     route.src = 9000;
        // else
            route.src = stoi(temp[3]);
    
        // if (temp[5]=="\\N")  
        //     route.des = 9000;
        // else 
            route.des = stoi(temp[5]);
        
        route.stop = stoi(temp[7]);
        route.plane = temp[8];
        route.airline = temp[0];
        routes.push_back(route);
    }
    file.close();
}

bool is_airport_iata(string s) {
    return true;
}


bool is_number(string s) {
    return true;
}

int SplitString(const std::string & str1, char sep, std::vector<std::string> &fields) {
    std::string str = str1;
    std::string::size_type pos;
    while((pos=str.find(sep)) != std::string::npos) {
        fields.push_back(str.substr(0,pos));
        str.erase(0,pos+1);  
    }
    fields.push_back(str);
    return fields.size();
}

