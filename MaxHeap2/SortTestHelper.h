#ifndef SORTTESTHELPER_H_INCLUDED
#define SORTTESTHELPER_H_INCLUDED

#include<iostream>
#include<ctime>
#include<cassert>
using namespace std;


namespace SortTestHelper{
    /**
    生成有n个元素的随机数组，每个元素的随机范围为rangeL到rangeR
    */
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

    /**
    生成一个近乎有序的数组
    */
    int * generateNearlyOrderedArray(int n, int swapTimes) {
        int *arr = new int[n];
        for(int i = 0; i < n; i++)
            arr[i] = i;

        srand(time(NULL));
        for(int i = 0; i < swapTimes; i++) {
            int posx = rand()%n;
            int posy = rand()%n;
            swap(arr[posx], arr[posy]);
        }

        return arr;
    }

    /**
    打印数组
    */
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
    /**
    重写，可以返回时间
    flag任意取值（可以为0但不推荐）只为区别
    */
    template<typename T>
    double testSort(string sortName, void(*sort)(T[], int), T arr[], int n, int flag) {

        //时钟周期
        clock_t startTime = clock();
        sort(arr, n);
        clock_t endTime = clock();

        assert(isSorted(arr, n));
        cout << sortName << ":" << double(endTime-startTime) / CLOCKS_PER_SEC << " s" << endl;
        return double(endTime-startTime) / CLOCKS_PER_SEC;

    }

    /**
    拷贝一份整型数组
    参数一传入数组，参数二传入长度
    */
    int* copyIntArray(int a[], int n) {

        int* arr = new int[n];
        copy(a, a+n, arr);
        return arr;
    }

    /**
    拷贝一份数组
    */
    template<typename T>
    T* copyArray(T a[], int n) {

        T* arr = new T[n];
        copy(a, a+n, arr);
        return arr;
    }
}

#endif // SORTTESTHELPER_H_INCLUDED
