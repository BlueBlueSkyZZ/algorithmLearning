#ifndef DENSEGRAPH_H_INCLUDED
#define DENSEGRAPH_H_INCLUDED

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

//����ͼ - �ڽӾ���
class DenseGraph{

private:
    int n, m;//�����ͱ���
    bool directed;//ͼ�Ƿ�������ͼ
    vector< vector<bool> > g;//��ά����

public:
    DenseGraph(int n, bool directed){
        this->n = n;
        this->m = 0;
        this->directed = directed;
        //����n*n����
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

    //������,����ƽ�б�
    void addEdge(int v, int w){

        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);

        if(hasEdge(v, w))
            return;

        g[v][w] = true;

        //�ж��Ƿ�������ͼ
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
