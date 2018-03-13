#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED

#include <iostream>
#include <vector>
#include <stack>
#include "Edge.h"
#include "IndexMinHeap.h"

using namespace std;

template<typename Graph, typename Weight>
class Dijkstra{

private:
    Graph &G;//图的引用
    int s;//源节点

    Weight *distTo;//最短距离
    bool *marked;//节点是否被访问
    vector< Edge<Weight>* > from;

public:
    Dijkstra(Graph &graph, int s):G(graph){

        assert( s >= 0 && s < G.V() );

        //初始化
        this->s = s;
        distTo = new Weight[G.V()];
        marked = new bool[G.V()];
        for(int i = 0; i < G.V(); i++){
            distTo[i] = Weight();
            marked[i] = false;
            from.push_back(NULL);
        }

        IndexMinHeap<Weight> ipq(G.V());

        //Dijkstra
        //初始化
        distTo[s] = Weight();//默认构造函数为0
        marked[s] = true;//访问s
        from[s] = new Edge<Weight>(s, s, Weight());
        ipq.insert( s, distTo[s] );//压入最小索引堆

        while( !ipq.isEmpty() ){
            int v = ipq.extractMinIndex();

            //distTo[v]就是s到v的最短距离
            marked[v] = true;

            typename Graph::adjIterator adj(G, v);
            for( Edge<Weight>* e = adj.begin(); !adj.end(); e = adj.next() ){
                int w = e->other(v);
                if( !marked[w] ){
                    if( from[w] == NULL || distTo[v] + e->wt() < distTo[w] ){
                        distTo[w] = distTo[v] + e->wt();
                        from[w] = e;
                        //维护最小索引堆
                        if(ipq.contain(w))
                            ipq.change(w, distTo[w]);
                        else
                            ipq.insert(w, distTo[w]);
                    }
                }
            }
        }
    }

    ~Dijkstra(){
        delete[] distTo;
        delete[] marked;
    }

    Weight shortestPathTo(int w){
        return distTo[w];
    }

    //判断是否连通
    bool hasPathTo(int w){
        return marked[w];
    }

    void shortestPath(int w, vector< Edge<Weight> > &vec){

        stack<Edge<Weight>*> s;
        Edge<Weight> *e = from[w];
        while(e->v() != e->w()){
            s.push(e);
            e = from[e->v()];
        }

        while(!s.empty()){
            e = s.top();
            vec.push_back(*e);
            s.pop();
        }
    }

    void showPath(int w){

        assert( w >= 0 && w < G.V() );

        vector< Edge<Weight> > vec;
        shortestPath(w, vec);
        for(int i = 0; i < vec.size(); i++){
            cout<<vec[i].v()<<" -> ";
            if( i == vec.size() - 1)
                cout<<vec[i].w()<<endl;
        }
    }
};

#endif // DIJKSTRA_H_INCLUDED
