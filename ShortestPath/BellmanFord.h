#ifndef BELLMANFORD_H_INCLUDED
#define BELLMANFORD_H_INCLUDED

#include <stack>
#include <vector>
#include "Edge.h"

using namespace std;

template <typename Graph, typename Weight>
class BellmanFord{

private:
    Graph &G;//ͼ������
    int s;//Դ
    Weight* distTo;// distTo[i]�洢����ʼ��s��i�����·������
    vector< Edge<Weight>* > from;//from[i]��¼���·����, ����i��ı�����һ��
    bool hasNegativeCycle;//�Ƿ��и�Ȩ��

    bool detectNegativeCycle(){
        //����V-1�β�������Ȼ�и�С�ģ�˵���и�Ȩ��
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
        distTo[s] = Weight();//��ʼ��Ϊ0
        from[s] = new Edge<Weight>(s, s, Weight()); // ��������from[s]��������new������, ע��Ҫ������������delete��

        //�����е���ڱ߽����ɳڲ���������V-1��
        for(int pass = 1; pass < G.V(); pass++){
            //�ɳڲ���Relaxation
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

        // ��ջ������ȡ��Ԫ��, ���˳��Ĵ�s��w��·��
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
