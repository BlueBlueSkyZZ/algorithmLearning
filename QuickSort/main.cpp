#include <iostream>
#include <algorithm>
#include "MergeSort.h"
#include "SortTestHelper.h"
#include "InsertionSort.h"

using namespace std;

/**
对arrp[L...R]部分进行partition操作
返回整型p，使得arr[L...p-1] < arr[p] && arr[p+1...R] > arr[p]
*/
template <typename T>
int __partition(T arr[], int L, int R)
{

    //改进1.0，随机选择一个数
    swap(arr[L], arr[rand()%(R-L+1) + L]);

    //取第一个元素为标准
    T v = arr[L];

    //arr[L+1...j] < v && arr[j+1...i) > v
    int j = L;
    for(int i = L + 1; i <= R; i++)
    {
        if(arr[i] < v)
        {
            swap(arr[j+1], arr[i]);
            j++;
        }
    }

    //最后将标准元素放置到中间
    swap(arr[L], arr[j]);

    return j;
}

/**
对arr[L...R]部分进行快速排序
*/
template <typename T>
void __quickSort(T arr[], int L, int R)
{

    //跳出条件
    if(L >= R)
        return;

    int p = __partition(arr, L, R);
    __quickSort(arr, L, p-1);
    __quickSort(arr, p+1, R);
}

template <typename T>
void quickSort(T arr[], int n)
{

    //改进1.0,随机选择标准而不是第一个，解决近乎有序情况下的问题
    srand(time(NULL));

    __quickSort(arr, 0, n-1);
}

/**
对arrp[L...R]部分进行partition操作
返回整型p，使得arr[L...p-1] < arr[p] && arr[p+1...R] > arr[p]
*/
template <typename T>
int __partition2(T arr[], int L, int R)
{

    //改进1.0，随机选择一个数
    swap(arr[L], arr[rand()%(R-L+1) + L]);

    //取第一个元素为标准
    T v = arr[L];

    //arr[L+1...i) < v && arr(j...r] > v i,j初始值保证一开始两个集合都不存在
    int i = L + 1, j = R;

    while(true)
    {
        //扫描
        while(i <= R && arr[i] < v) i++;
        while(j >= L + 1 && arr[j] > v) j--;
        //跳出条件
        if(i > j) break;
        //交换
        swap(arr[i], arr[j]);
        i++;
        j--;
    }

    //最后将标准元素放置到中间
    //最后完成j位于<=v的最后一个，i位于>=v的第一个
    swap(arr[L], arr[j]);

    return j;
}

/**
对arr[L...R]部分进行快速排序
*/
template <typename T>
void __quickSort2(T arr[], int L, int R)
{

    //跳出条件,可以改进
    if(L >= R)
        return;

    int p = __partition2(arr, L, R);
    __quickSort2(arr, L, p-1);
    __quickSort2(arr, p+1, R);
}

template <typename T>
void quickSort2(T arr[], int n)
{

    //改进1.0,随机选择标准而不是第一个，解决近乎有序情况下的问题
    srand(time(NULL));

    __quickSort2(arr, 0, n-1);
}

/**
三路快排处理arr[L...R]
将arr[L...R]分为<v; ==v; >v三部分
之后递归对<v ; >v两部分继续进行三路快速排序
*/
template <typename T>
void __quickSort3Ways(T arr[], int L, int R) {

    //跳出条件
    if(R - L <= 15) {
        insertionSort(arr, L, R);
        return;
    }

    //partition
    //随机取标准
    swap(arr[L], arr[rand()%(R-L+1) + L]);
    T v = arr[L];

    int lt = L; //arr[L+1...lt] < v
    int gt = R + 1; //arr[gt...R] > v
    int i = L + 1; // arr[lt...i) == v

    while(i < gt) {
        if(arr[i] < v) {
            swap(arr[i], arr[lt+1]);
            lt++;
            i++;
        }
        else if(arr[i] > v) {
            swap(arr[i], arr[gt-1]);
            gt--;
        }
        else{
            //arr[i] == v
            i++;
        }
    }

    swap(arr[L], arr[lt]);

    __quickSort3Ways(arr, L, lt-1);
    __quickSort3Ways(arr, gt, R);
}

template <typename T>
void quickSort3Ways(T arr[], int n) {

    srand(time(NULL));
    __quickSort3Ways(arr, 0, n-1);
}

int main()
{
    long int n = 100000;
//    int* arr1 = SortTestHelper::generateNearlyOrderedArray(n, 0);
    int* arr1 = SortTestHelper::generateRandomArray(n, 0, 1);
    int* arr2 = SortTestHelper::copyArray(arr1, n);
    int* arr3 = SortTestHelper::copyArray(arr1, n);
    int* arr4 = SortTestHelper::copyArray(arr1, n);

    SortTestHelper::testSort("Quick Sort 3 Ways", quickSort3Ways, arr3, n);
    SortTestHelper::testSort("Quick Sort2", quickSort2, arr1, n);
    SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);
    SortTestHelper::testSort("Merge Sort", mergeSort, arr4, n);



    SortTestHelper::printArray(arr2, n);


    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    return 0;
}
