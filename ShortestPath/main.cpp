#include <iostream>
#include "SparseGraph.h"
#include "DenseGraph.h"
#include "ReadGraph.h"
#include "Dijkstra.h"
#include "BellmanFord.h"
using namespace std;

// �������ǵ�Dijkstra���·���㷨
int main() {

//    string filename = "testG1.txt";
//    int V = 5;
//
//    SparseGraph<int> g = SparseGraph<int>(V, true);
//    // Dijkstra���·���㷨ͬ������������ͼ
//    //SparseGraph<int> g = SparseGraph<int>(V, false);
//    ReadGraph<SparseGraph<int>, int> readGraph(g, filename);
//
//    cout<<"Test Dijkstra:"<<endl<<endl;
//    Dijkstra<SparseGraph<int>, int> dij(g,0);
//    for( int i = 0 ; i < V ; i ++ ){
//        if(dij.hasPathTo(i)){
//            cout<<"Shortest Path to "<<i<<" : "<<dij.shortestPathTo(i)<<endl;
//            dij.showPath(i);
//        }
//        else
//            cout<<"No Path to "<<i<<endl;
//
//        cout<<"----------"<<endl;
//    }

    string filename = "testG2.txt";
    //string filename = "testG_negative_circle.txt";
    int V = 5;

    SparseGraph<int> g = SparseGraph<int>(V, true);
    ReadGraph<SparseGraph<int>, int> readGraph(g, filename);

    cout<<"Test Bellman-Ford:"<<endl<<endl;

    int s = 0;
    BellmanFord<SparseGraph<int>, int> bellmanFord(g, s);
    if( bellmanFord.negativeCycle() )
        cout<<"The graph contain negative cycle!"<<endl;
    else
        for( int i = 0 ; i < V ; i ++ ) {
            if(i == s)
                continue;

            if (bellmanFord.hasPathTo(i)) {
                cout << "Shortest Path to " << i << " : " << bellmanFord.shortestPathTo(i) << endl;
                bellmanFord.showPath(i);
            }
            else
                cout << "No Path to " << i << endl;

            cout << "----------" << endl;
        }

    return 0;
}
