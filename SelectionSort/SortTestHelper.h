#ifndef SORTTESTHELPER_H_INCLUDED
#define SORTTESTHELPER_H_INCLUDED

#include<iostream>
#include<ctime>
#include<cassert>
using namespace std;


namespace SortTestHelper{
    // 生成有n个元素的随机数组，每个元素的随机范围为rangeL到rangeR
    int * generateRandomArray(int n, int rangeL, int rangeR){

        assert(rangeL <= rangeR);

        int *arr = new int[n];
        //随机种子设置
        srand(time(NULL));

        for(int i = 0; i < n; i++) {
            //rand()返回随机整数
            arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
        }

        return arr;
    }

    template<typename T>
    void printArray(T arr[], int n){

        for (int i = 0; i < n; i++)
            cout << arr[i] << " ";
        cout << endl;

        return;
    }

    /**
    判断排序是否成功
    */
    template<typename T>
    bool isSorted(T arr[], int n) {
        for (int i = 0; i < n - 1; i++)
            if(arr[i] > arr[i+1])
                return false;

        return true;
    }

    /**
    测试函数性能
    sortName是排序名称
    第二个参数为函数指针
    */
    template<typename T>
    void testSort(string sortName, void(*sort)(T[], int), T arr[], int n) {
        //时钟周期
        clock_t startTime = clock();
        sort(arr, n);
        clock_t endTime = clock();

        assert(isSorted(arr, n));
        cout << sortName << ":" << double(endTime-startTime) / CLOCKS_PER_SEC << " s" << endl;
        return;
    }


}

#endif // SORTTESTHELPER_H_INCLUDED
