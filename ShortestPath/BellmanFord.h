#ifndef BELLMANFORD_H_INCLUDED
#define BELLMANFORD_H_INCLUDED

#include <stack>
#include <vector>
#include "Edge.h"

using namespace std;

template <typename Graph, typename Weight>
class BellmanFord{

private:
    Graph &G;//图的引用
    int s;//源
    Weight* distTo;// distTo[i]存储从起始点s到i的最短路径长度
    vector< Edge<Weight>* > from;//from[i]记录最短路径中, 到达i点的边是哪一条
    bool hasNegativeCycle;//是否有负权环

    bool detectNegativeCycle(){
        //进行V-1次操作后仍然有更小的，说明有负权环
        for(int i = 0; i < G.V(); i++){
            typename Graph::adjIterator adj(G, i);
            for( Edge<Weight>* e = adj.begin(); !adj.end(); e = adj.next() )
                if(from[e->v()] && distTo[e->v()] + e->wt() < distTo[e->w()])
                    return true;
        }

        return false;
    }

public:
    BellmanFord(Graph &graph, int s):G(graph){
        this->s = s;
        distTo = new Weight[G.V()];
        for(int i = 0; i < G.V(); i++){
            from.push_back(NULL);
        }

        //Bellman-Ford
        distTo[s] = Weight();//初始化为0
        from[s] = new Edge<Weight>(s, s, Weight()); // 这里我们from[s]的内容是new出来的, 注意要在析构函数里delete掉

        //对所有点的邻边进行松弛操作，进行V-1次
        for(int pass = 1; pass < G.V(); pass++){
            //松弛操作Relaxation
            for(int i = 0; i < G.V(); i++){
                typename Graph::adjIterator adj(G, i);
                for(Edge<Weight>* e = adj.begin(); !adj.end(); e = adj.next())
                    if( from[e->v()] && (!from[e->w()] || distTo[e->v()] + e->wt() < distTo[e->w()]) ){
                        distTo[e->w()] = distTo[e->v()] + e->wt();
                        from[e->w()] = e;
                    }
            }
        }

        hasNegativeCycle = detectNegativeCycle();
    }

    ~BellmanFord(){

        delete[] distTo;
        delete from[s];
    }

    bool negativeCycle(){
        return hasNegativeCycle;
    }

    Weight shortestPathTo(int w){
        assert( w >= 0 && w < G.V() );
        assert( !hasNegativeCycle);
        return distTo[w];
    }

    bool hasPathTo(int w){
        assert( w >= 0 && w < G.V() );
        return from[w] != NULL;
    }

    void shortestPath(int w, vector< Edge<Weight> > &vec){
        assert( w >= 0 && w < G.V() );
        assert( !hasNegativeCycle );

        stack<Edge<Weight>*> s;
        Edge<Weight> *e = from[w];
        while( e->v() != this->s ){
            s.push(e);
            e = from[e->v()];
        }
        s.push(e);

        // 从栈中依次取出元素, 获得顺序的从s到w的路径
        while( !s.empty() ){
            e = s.top();
            vec.push_back( *e );
            s.pop();
        }
    }

    void showPath(int w){
        assert( w >= 0 && w < G.V() );
        assert( !hasNegativeCycle );

        vector< Edge<Weight> > vec;
        shortestPath(w, vec);
        for(int i = 0; i < vec.size(); i++){
            cout<<vec[i].v()<<" -> ";
            if( i == vec.size()-1 )
                cout<<vec[i].w()<<endl;
        }
    }
};

#endif // BELLMANFORD_H_INCLUDED
