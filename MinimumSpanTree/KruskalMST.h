#ifndef KRUSKALMST_H_INCLUDED
#define KRUSKALMST_H_INCLUDED

#include <iostream>
#include <vector>
#include "MinHeap.h"
#include "UF.h"
#include "Edge.h"

using namespace std;

// Kruskal�㷨
template <typename Graph, typename Weight>
class KruskalMST{

private:
    vector< Edge<Weight> > mst;   // ��С�����������������б�
    Weight mstWeight;           // ��С��������Ȩֵ

public:
    // ���캯��, ʹ��Kruskal�㷨����graph����С������
    KruskalMST(Graph &graph){

        // ��ͼ�е����бߴ�ŵ�һ����С����
        MinHeap< Edge<Weight> > pq( graph.E() );
        for( int i = 0 ; i < graph.V() ; i ++ ){
            typename Graph::adjIterator adj(graph,i);
            for( Edge<Weight> *e = adj.begin() ; !adj.end() ; e = adj.next() )
                if( e->v() < e->w() )
                    pq.insert(*e);
        }

        // ����һ�����鼯, ���鿴�Ѿ����ʵĽڵ����ͨ���
        UnionFind uf = UnionFind(graph.V());
        while( !pq.isEmpty() && mst.size() < graph.V() - 1 ){

            // ����С�������δ�С����ȡ�����еı�
            Edge<Weight> e = pq.extractMin();
            // ����ñߵ������˵�����ͨ��, ˵�����������߽�������, �ӵ�������
            if( uf.isConnected( e.v() , e.w() ) )
                continue;

            // ����, ����������ӽ���С������, ͬʱ��Ǳߵ������˵���ͨ
            mst.push_back( e );
            uf.unionElements( e.v() , e.w() );
        }

        mstWeight = mst[0].wt();
        for( int i = 1 ; i < mst.size() ; i ++ )
            mstWeight += mst[i].wt();
    }

    ~KruskalMST(){ }

    // ������С�����������б�
    vector< Edge<Weight> > mstEdges(){
        return mst;
    };

    // ������С��������Ȩֵ
    Weight result(){
        return mstWeight;
    };
};

#endif // KRUSKALMST_H_INCLUDED
