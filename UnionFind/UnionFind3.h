#ifndef UNIONFIND3_H_INCLUDED
#define UNIONFIND3_H_INCLUDED

#include <iostream>
#include <cassert>

using namespace std;

namespace UF3{

    class UnionFind{
    private:
        int* parent;
        int* sz; //sz[i]��ʾ��iΪ���ļ�����Ԫ�صĸ���
        int count;

    public:
        UnionFind(int count){
            parent = new int[count];
            this->count = count;
            for(int i = 0; i < count; i++){
                parent[i] = i;
                sz[i] = 1;
            }

        }


        ~UnionFind(){
            delete[] parent;
            delete[] sz;
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

            if(sz[pRoot] < sz[qRoot]){
                parent[pRoot] = qRoot;
                sz[qRoot] += sz[pRoot];
            }
            else{
                parent[qRoot] = pRoot;
                sz[pRoot] += sz[qRoot];
            }

        }
    };
}

#endif // UNIONFIND3_H_INCLUDED
