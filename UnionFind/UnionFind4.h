#ifndef UNIONFIND4_H_INCLUDED
#define UNIONFIND4_H_INCLUDED

#include <iostream>
#include <cassert>

using namespace std;

namespace UF4{

    class UnionFind{
    private:
        int* parent;
        int* rank; //sz[i]��ʾ��iΪ���ļ�����Ԫ�صĸ���
        int count;

    public:
        UnionFind(int count){
            parent = new int[count];
            this->count = count;
            for(int i = 0; i < count; i++){
                parent[i] = i;
                rank[i] = 1;
            }

        }


        ~UnionFind(){
            delete[] parent;
            delete[] rank;
        }

        //�ҵ������ĸ��ڵ�
        int find(int p){
            assert(p >= 0 && p < count);
            //ֱ��p��Ϊ���ڵ�
            while(p != parent[p])
                p = parent[p];

            return p;
        }

        bool isConnected(int p, int q){
            return find(p) == find(q);
        }

        void unionElements(int p, int q){

            int pRoot = find(p);
            int qRoot = find(q);

            if(pRoot == qRoot)
                return;

            if(rank[pRoot] < rank[qRoot]){
                parent[pRoot] = qRoot;
            }
            else if(rank[qRoot] < rank[pRoot]){
                parent[qRoot] = pRoot;
            }
            else{ //rank[qRoot] == rank[pRoot]
                parent[qRoot] = pRoot;
                rank[pRoot] += 1;
            }

        }
    };
}

#endif // UNIONFIND4_H_INCLUDED
