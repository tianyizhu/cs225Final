#pragma once

#define NULLV 10000
#define INF_DIS 384400

#include <vector>
#include <map>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <queue>
#include "io.h"
using namespace std;

class Graph {

    public:
    
    std::vector<std::map<unsigned, float>> adjList;

    bool is_adj(unsigned s, unsigned d)   const{
        if (s>=adjList.size() || d>=adjList.size())
            return false;

        return adjList[s].find(d) != adjList[s].end();
    }

    float get_dis(unsigned s, unsigned d)   {
        if (!is_adj(s,d)) return -1;
        float ret = adjList[s][d];
        return ret;
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
        

        for (unsigned i=from; i<=to; i++)    {
            
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



class cmp
{
//   bool reverse;
    
    public:

//   mycomparison(const bool& revparam=false)
//     {reverse=revparam;}
  bool operator() (pair<unsigned,float> a, pair<unsigned,float> b) const
  {
      return a.second > b.second;
  }
};

// bool cmp(pair<unsigned,float> a, pair<unsigned,float> b) {
//     return a.second > b.second;
// }

float dij(Graph& g, unsigned src, unsigned des, vector<unsigned>& path)    {

    priority_queue<pair<unsigned,float>, vector<pair<unsigned,float>>, cmp> pq;

    pq.push( make_pair(src, 0) );

    // float d[14110];
    // int p[14110];
    // bool visited[14110];

    float* d = new float[g.size()];
    int* p = new int[g.size()];
    bool* visited = new bool[g.size()];

    for (int i=0; i<g.size(); i++) {
        d[i] = INF_DIS;
        visited[i] = false;
        p[i] = NULLV;
    }

    d[src] = 0;
    // visited[src] = true;

    do {
        unsigned u = pq.top().first;
        // float dis = pq.top().second;
        pq.pop();

        if (!visited[u]) {

            vector<pair<int,float>> adjs;
            g.get_adj_dis(u, adjs);


            for (auto elem: adjs)  
                // if ((p[elem.first] == NULLV) || (g.get_dis(u, elem.first) + d[u] < d[elem.first]))   {
                //     d[elem.first] = g.get_dis(u, elem.first) + d[u];
                // if (!visited[elem.first]) {
                    if ((p[elem.first] == NULLV) || (elem.second + d[u] < d[elem.first]))   {
                        d[elem.first] = elem.second + d[u];
                        p[elem.first] = u;
                        pq.push( make_pair(elem.first, d[elem.first]) ); 
                    }
                
                // }
            
        }

        visited[u] = true;
    } while (!pq.empty());


    unsigned current = des; 
    path = {current};
    // cout << airports[current].iata;

    do {

        current = p[current];
        path.push_back(current);
        // cout << " -- "<< airports[current].iata;

    } while ( current!=NULLV &&  current!=src);

    reverse(path.begin(), path.end());
    delete[] p;
    delete[] d;
    delete[] visited;

    if (current == NULLV) {
        path = {NULLV};
        return -1;
    }
    // return;

    else return d[des];
    
}

bool onPath(vector<unsigned>& path, unsigned v) {
    for (auto elem: path)
        if (v==elem) return true;
    return false;
}


void DFS(Graph& g, unsigned root, unsigned des, vector<unsigned>& curPath, int maxDepth, float curDis, float& minDis, vector<unsigned>& minPath)    {
    if (maxDepth == 0) {
        if (root == des && curDis<minDis) {
            minDis = curDis;
            minPath = curPath;
        }
        return;
    }

    
    vector<pair<int,float>> adjs;
    g.get_adj_dis(root, adjs);
    
    for (auto elem: adjs)  {
        unsigned v = elem.first;
        float dis = elem.second;
        if (!onPath(curPath, v))    {
            curPath.push_back(v);

            DFS(g, v, des, curPath, maxDepth-1,curDis+dis, minDis, minPath);

            curPath.pop_back();
     
        }
    }        

}


float IDDFS(Graph& g, unsigned src, unsigned des, vector<unsigned>& path, int maxHeight = 15)    {
    
    float minDis = INF_DIS;

    for (int i=1; i<maxHeight; i++) {
        path = {};
        vector<unsigned> curPath = {src};


        DFS(g, src, des, curPath, i,0, minDis, path);
        if (minDis < INF_DIS) return minDis;
    }

    return -1;
}



// int DFS(Graph& g, unsigned src, unsigned des, vector<int>& path)    {

//     queue<unsigned> q;

//     // int* p = new int[g.size()];
//     bool* visited = new bool[g.size()];

//     for (int i=0; i<g.size(); i++) {
//         visited[i] = false;
//         // p[i] = NULLV;
//     }

//     q.push(src);

//     while (!q.empty())  {
//         unsigned curr = q.front();
//         q.pop();
        

