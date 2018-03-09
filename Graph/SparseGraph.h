#ifndef SPARSEGRAPH_H_INCLUDED
#define SPARSEGRAPH_H_INCLUDED

#include <iostream>
#include <vector>
#include <cassert>
#include "BST.h"
//稀疏图 - 邻接表
class SparseGraph{

private:
    int n, m;
    bool directed;
    vector< vector<int> > g;

public:
    SparseGraph(int n, bool directed){
        this->n = n;
        this->m = 0;
        this->directed = directed;
        //初始化 邻接表为空
        for(int i = 0; i < n; i++)
            g.push_back(vector<int>());
    }

    ~SparseGraph(){
    }

    int V(){
        return n;
    }

    int E(){
        return m;
    }

    void addEdge(int v, int w){
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);

        if(!judgeParallelEdges(g[w], v))
            return;

        g[v].push_back(w);
        //处理自环边及平行边
        if(v != w && !directed )
            g[w].push_back(v);

        m++;
    }

    bool hasEdge(int v, int w){
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);

        for(int i = 0; i < g[v].size(); i++)
            if(g[v][i] == w)
                return true;
        return false;
    }

    void show(){

        for(int i = 0; i < n; i++){
            cout<<"vertex "<<i<<":\t";
            for(int j = 0; j < g[i].size(); j++)
                cout<<g[i][j]<<"  ";
            cout<<endl;
        }
    }

    //判断两点之间是否已经存在连接
    //存在返回False,不存在返回True
    bool judgeParallelEdges(vector<int> v, int w){
        BST<int,int> bst = BST<int,int>();
        for(int i = 0; i < v.size(); i++){
            int key = v[i];
            int value = key;
            bst.insert(key, value);
        }

        if(bst.contain(w))
            return false;

        return true;
    }

    //迭代器迭代相邻的边
    class adjIterator{
    private:
        SparseGraph &G;//图的引用
        int v;//相邻节点
        int index;//迭代目前的位置
    public:
        adjIterator(SparseGraph &graph, int v): G(graph){
            this->v = v;
            this->index = 0;
        }

        //初始值
        int begin(){
            index = 0;
            if(G.g[v].size())
                return G.g[v][0];
            return -1;
        }

        int next(){
            index++;
            if(index < G.g[v].size())
                return G.g[v][index];

            return -1;
        }

        bool end(){
            return index >= G.g[v].size();
        }
    };
};

#endif // SPARSEGRAPH_H_INCLUDED
