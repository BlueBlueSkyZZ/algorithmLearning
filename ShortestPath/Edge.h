#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

#include <iostream>
#include <cassert>

using namespace std;


template<typename Weight>
class Edge{
private:
    int a,b;
    Weight weight;

public:
    Edge(int a, int b, Weight weight){
        this->a = a;
        this->b = b;
        this->weight = weight;
    }

    Edge(){}

    ~Edge(){}
    //���ص�һ������
    int v(){ return a;}
    //���صڶ�������
    int w(){ return b;}
    //����Ȩֵ
    Weight wt(){ return weight;}
    // ����һ������, ������һ������
    int other(int x){
        assert( x == a || x == b );
        return x == a ? b : a;
    }

    friend ostream& operator<<(ostream &os, const Edge &e){
        os<<e.a<<"-"<<e.b<<": "<<e.weight;
        return os;
    }

    bool operator<(Edge<Weight>& e){
        return weight < e.wt();
    }

    bool operator<=(Edge<Weight>& e){
        return weight <= e.wt();
    }

    bool operator>(Edge<Weight>& e){
        return weight > e.wt();
    }

    bool operator>=(Edge<Weight>& e){
        return weight >= e.wt();
    }

    bool operator==(Edge<Weight>& e){
        return weight == e.wt();
    }
};

#endif // EDGE_H_INCLUDED
