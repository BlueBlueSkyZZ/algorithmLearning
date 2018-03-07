#ifndef DENSEGRAPH_H_INCLUDED
#define DENSEGRAPH_H_INCLUDED

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

//稠密图 - 邻接矩阵
class DenseGraph{

private:
    int n, m;//点数和边数
    bool directed;//图是否是有向图
    vector< vector<bool> > g;//二维矩阵

public:
    DenseGraph(int n, bool directed){
        this->n = n;
        this->m = 0;
        this->directed = directed;
        //创建n*n矩阵
        for(int i = 0; i < n; i++)
            g.push_back(vector<bool>(n, false));
    }

    ~DenseGraph(){
    }

    int V(){
        return n;
    }

    int E(){
        return m;
    }

    //建立边,忽略平行边
    void addEdge(int v, int w){

        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);

        if(hasEdge(v, w))
            return;

        g[v][w] = true;

        //判断是否是有向图
        if(!directed)
            g[w][v] = true;

        m++;
    }

    bool hasEdge(int v, int w){
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);
        return g[v][w];
    }

    class adjIterator{
    private:
        DenseGraph &G;
        int v;
        int index;

    public:
        adjIterator(DenseGraph &graph, int v): G(graph){
            this->v = v;
            this->index = -1;

        }

        int begin(){

            index = -1;
            return next();
        }

        int next(){
            for(index += 1; index < G.V(); index++)
                if(G.g[v][index])
                    return index;

            return -1;
        }

        bool end(){
            return index >= G.V();
        }


    };
};

#endif // DENSEGRAPH_H_INCLUDED
