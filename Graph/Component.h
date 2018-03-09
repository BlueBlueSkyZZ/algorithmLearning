#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

#include <algorithm>
#include <cassert>
#include "DenseGraph.h"
#include "SparseGraph.h"

using namespace std;

template <typename Graph>
class Component{

private:
    Graph &G;
    bool *visited;//是否被访问
    int ccount;//记录连通分量
    int *id;//判断节点是否相连

    void dfs(int v){
        visited[v] = true;
        id[v] = ccount;
        //遍历v相邻的节点
        typename Graph::adjIterator adj(G, v);
        for(int i = adj.begin(); !adj.end(); i = adj.next()){
            if(!visited[i])
                dfs(i);
        }
    }
public:
    Component(Graph &graph): G(graph){
        //初始化
        visited = new bool[G.V()];
        id = new int[G.V()];
        ccount = 0;
        for(int i = 0; i < G.V(); i++){
            visited[i] = false;
            id[i] = -1;
        }


        for(int i = 0; i < G.V(); i++)
            if(!visited[i]){
                //Depth-First-Search
                dfs(i);
                ccount++;
            }
    }

    ~Component(){
        delete[] visited;
        delete[] id;
    }

    int count(){
        return ccount;
    }

    bool isConnected(int v, int w){
        assert( v >= 0 && v < G.V() );
        assert( w >= 0 && w < G.V() );
        return id[v] == id[w];

    }
};

#endif // COMPONENT_H_INCLUDED
