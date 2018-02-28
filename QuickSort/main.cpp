#include <iostream>
#include <algorithm>
#include "MergeSort.h"
#include "SortTestHelper.h"
#include "InsertionSort.h"

using namespace std;

/**
��arrp[L...R]���ֽ���partition����
��������p��ʹ��arr[L...p-1] < arr[p] && arr[p+1...R] > arr[p]
*/
template <typename T>
int __partition(T arr[], int L, int R)
{

    //�Ľ�1.0�����ѡ��һ����
    swap(arr[L], arr[rand()%(R-L+1) + L]);

    //ȡ��һ��Ԫ��Ϊ��׼
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

    //��󽫱�׼Ԫ�ط��õ��м�
    swap(arr[L], arr[j]);

    return j;
}

/**
��arr[L...R]���ֽ��п�������
*/
template <typename T>
void __quickSort(T arr[], int L, int R)
{

    //��������
    if(L >= R)
        return;

    int p = __partition(arr, L, R);
    __quickSort(arr, L, p-1);
    __quickSort(arr, p+1, R);
}

template <typename T>
void quickSort(T arr[], int n)
{

    //�Ľ�1.0,���ѡ���׼�����ǵ�һ�������������������µ�����
    srand(time(NULL));

    __quickSort(arr, 0, n-1);
}

/**
��arrp[L...R]���ֽ���partition����
��������p��ʹ��arr[L...p-1] < arr[p] && arr[p+1...R] > arr[p]
*/
template <typename T>
int __partition2(T arr[], int L, int R)
{

    //�Ľ�1.0�����ѡ��һ����
    swap(arr[L], arr[rand()%(R-L+1) + L]);

    //ȡ��һ��Ԫ��Ϊ��׼
    T v = arr[L];

    //arr[L+1...i) < v && arr(j...r] > v i,j��ʼֵ��֤һ��ʼ�������϶�������
    int i = L + 1, j = R;

    while(true)
    {
        //ɨ��
        while(i <= R && arr[i] < v) i++;
        while(j >= L + 1 && arr[j] > v) j--;
        //��������
        if(i > j) break;
        //����
        swap(arr[i], arr[j]);
        i++;
        j--;
    }

    //��󽫱�׼Ԫ�ط��õ��м�
    //������jλ��<=v�����һ����iλ��>=v�ĵ�һ��
    swap(arr[L], arr[j]);

    return j;
}

/**
��arr[L...R]���ֽ��п�������
*/
template <typename T>
void __quickSort2(T arr[], int L, int R)
{

    //��������,���ԸĽ�
    if(L >= R)
        return;

    int p = __partition2(arr, L, R);
    __quickSort2(arr, L, p-1);
    __quickSort2(arr, p+1, R);
}

template <typename T>
void quickSort2(T arr[], int n)
{

    //�Ľ�1.0,���ѡ���׼�����ǵ�һ�������������������µ�����
    srand(time(NULL));

    __quickSort2(arr, 0, n-1);
}

/**
��·���Ŵ���arr[L...R]
��arr[L...R]��Ϊ<v; ==v; >v������
֮��ݹ��<v ; >v�����ּ���������·��������
*/
template <typename T>
void __quickSort3Ways(T arr[], int L, int R) {

    //��������
    if(R - L <= 15) {
        insertionSort(arr, L, R);
        return;
    }

    //partition
    //���ȡ��׼
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
