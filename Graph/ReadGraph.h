#ifndef READGRAPH_H_INCLUDED
#define READGRAPH_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;

template <typename Graph>
class ReadGraph{

public:
    ReadGraph(Graph &graph, const string &filename){

        ifstream file(filename);//读取file
        string line;//一行一行读取
        int V, E;

        assert(file.is_open());

        assert(getline(file, line));
        stringstream ss(line);
        ss>> V >> E;

        assert(V == graph.V());

        for(int i = 0; i < E; i++){

            assert(getline(file, line));
            stringstream ss(line);

            int a, b;
            ss >> a >> b;
            assert(a >= 0 && a < V);
            assert(b >= 0 && b < V);

        }
    }

};

#endif // READGRAPH_H_INCLUDED
