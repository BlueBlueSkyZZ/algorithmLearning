#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

#include <algorithm>
#include <cassert>
#include <stack>
#include "DenseGraph.h"
#include "SparseGraph.h"

using namespace std;

template <typename Graph>
class Path{

private:
    Graph &G;
    int s;//Դ�ڵ�
    bool *visited;//�Ƿ񱻷���
    int *from;

    void dfs(int v){
        visited[v] = true;
        //����v���ڵĽڵ�
        typename Graph::adjIterator adj(G, v);
        for(int i = adj.begin(); !adj.end(); i = adj.next()){
            if(!visited[i]){
                from[i] = v;
                dfs(i);
            }
        }
    }

public:
    Path(Graph &graph, int s):G(graph){
        //�㷨��ʼ��
        assert( s >= 0 && s < G.V() );

        visited = new bool[G.V()];
        from = new int[G.V()];
        for(int i = 0; i < G.V(); i++){
            visited[i] = false;
            from[i] = -1;
        }
        this->s = s;

        //Ѱ·
        dfs(s);
    }

    ~Path(){
        delete[] visited;
        delete[] from;
    }

    bool hasPath(int w){
        assert( w >= 0 && w < G.V() );
        return visited[w];
    }

    void path(int w, vector<int> &vec){

        assert( w >= 0 && w < G.V() );

        stack<int> s;

        //����ջ��
        int p = w;
        while(p != -1){
            s.push(p);
            p = from[p];
        }

        //˳�����vector
        vec.clear();
        while( !s.empty() ){
            vec.push_back( s.top() );
            s.pop();
        }
    }

    //wΪĿ��ڵ�
    void showPath(int w){

        vector<int> vec;
        path(w, vec);
        for(int i = 0; i < vec.size(); i++){
            cout<<vec[i];
            if( i == vec.size() - 1 )
                cout<<endl;
            else
                cout<<" -> ";
        }
    }
};

#endif // PATH_H_INCLUDED
