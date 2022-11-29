#pragma once

#include <vector>
#include <map>
#include <unordered_map>
#include <iostream>
#include <algorithm>
using namespace std;

class graph {

    public:
    
    std::vector<std::map<int, float>> adjList;

    bool is_adj(unsigned s, unsigned d)   const{
        if (s>=adjList.size() || d>=adjList.size())
            return false;

        return adjList[s].find(d) != adjList[s].end();
    }

    float get_dis(unsigned s, unsigned d)   const{
        if (!is_adj(s,d)) return -1;
        return adjList[s][d];
    }

    bool add_edge(unsigned s, unsigned d, float dis=1)    {

        unsigned size = max(s,d);
        if (size>=adjList.size()) adjList.resize(size+1);


        if (s==d) return false;

        if (is_adj(s, d)) return false;

        // cout << size << ", "  << adjList.size() << endl;

        adjList[s][d]=dis;
        // adjList[d][s]=dis;
        // cout << "finished" << endl;

        return true;
    }

    int get_adjs(unsigned s, vector<int>& ret) const{
        if (s>=adjList.size()) return 0;

        ret = {};
        for (auto it : adjList[s])  
            ret.push_back(it.first);

        return ret.size();
    }

    int get_adj_dis(unsigned s, vector<pair<int,float>>& ret) const{
        if (s>=adjList.size()) return 0;

        ret = {};
        for (auto it : adjList[s])  
            ret.push_back(it);

        return ret.size();
    }

    void print_graph(unsigned from = 0, unsigned to = -1) {

        // to--;

        if (to<from || to > adjList.size())
            to = adjList.size()-1;
        

        for (unsigned i=0; i<=to; i++)    {
            
            cout<<"("<<i<<"):  ";

            vector<pair<int,float>> adjs;
            get_adj_dis(i, adjs);
            for (unsigned j=0; j<adjs.size(); j++)
                cout<<"-"<<adjs[j].second<<"-("<<adjs[j].first<<"), ";

            cout<<endl;
        }
        
        cout<<endl;
    }

    bool remove_edge(unsigned s, unsigned d)  {
        if (s>=adjList.size() || d>=adjList.size())
            return false;

        return adjList[s].erase(d);
    }

    int size()  const{
        return adjList.size();
    }

    void add_vertex(unsigned v) {
        if (v>=adjList.size()) adjList.resize(v+1);
    }
};
