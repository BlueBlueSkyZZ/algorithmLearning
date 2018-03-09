#include <iostream>
#include <algorithm>
#include <ctime>
#include "SparseGraph.h"
#include "DenseGraph.h"
#include "ReadGraph.h"
#include "Component.h"
#include "Path.h"
#include "ShortestPath.h"

using namespace std;


int main() {

//    int N = 20;
//    int M = 100;
//
//    srand( time(NULL) );
//
//
//    // Sparse Graph
//    SparseGraph g1(N , false);
//    for( int i = 0 ; i < M ; i ++ ){
//        int a = rand()%N;
//        int b = rand()%N;
//        g1.addEdge( a , b );
//    }
//
//    // O(E)
//    for( int v = 0 ; v < N ; v ++ ){
//        cout<<v<<" : ";
//        SparseGraph::adjIterator adj( g1 , v );
//        for( int w = adj.begin() ; !adj.end() ; w = adj.next() )
//            cout<<w<<" ";
//        cout<<endl;
//    }
//
//    cout<<endl;
//
//
//    // Dense Graph
//    DenseGraph g2(N , false);
//    for( int i = 0 ; i < M ; i ++ ){
//        int a = rand()%N;
//        int b = rand()%N;
//        g2.addEdge( a , b );
//    }
//
//    // O(V^2)
//    for( int v = 0 ; v < N ; v ++ ){
//        cout<<v<<" : ";
//        DenseGraph::adjIterator adj( g2 , v );
//        for( int w = adj.begin() ; !adj.end() ; w = adj.next() )
//            cout<<w<<" ";
//        cout<<endl;
//    }

//    string filename = "testG1.txt";
//
//    SparseGraph g1(13, false);
//    ReadGraph<SparseGraph> readGraph1(g1, filename);
//    Component<SparseGraph> component1(g1);
//    cout<<"TestGF1.txt, Component Count:"<<component1.count()<<endl;
//
//    cout<<endl;
//
//    string filename2 = "testG2.txt";
//    SparseGraph g2(6, false);
//    ReadGraph<SparseGraph> readGraph2(g2, filename2);
//    Component<SparseGraph> component2(g2);
//    cout<<"TestG2.txt, Component Count:"<<component2.count()<<endl;

    string filename = "testG2.txt";
    SparseGraph g = SparseGraph(6, false);
    ReadGraph<SparseGraph> readGraph(g, filename);
    g.show();

    cout<<endl;

    Path<SparseGraph> dfs(g, 0);
    cout<<"DFS: ";
    dfs.showPath(5);

    cout<<endl;

    ShortestPath<SparseGraph> bfs(g, 0);
    cout<<"BFS: ";
    bfs.showPath(5);

    return 0;
}
