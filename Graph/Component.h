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
    bool *visited;//�Ƿ񱻷���
    int ccount;//��¼��ͨ����
    int *id;//�жϽڵ��Ƿ�����

    void dfs(int v){
        visited[v] = true;
        id[v] = ccount;
        //����v���ڵĽڵ�
        typename Graph::adjIterator adj(G, v);
        for(int i = adj.begin(); !adj.end(); i = adj.next()){
            if(!visited[i])
                dfs(i);
        }
    }
public:
    Component(Graph &graph): G(graph){
        //��ʼ��
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
