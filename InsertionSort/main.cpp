#include <iostream>
#include <algorithm>
#include "SortTestHelper.h"
#include "SelectionSort.h"

using namespace std;

template<typename T>
void insertionSort(T arr[], int n) {

    for (int i = 1; i < n; i++) {

        // 寻找元素arr[i]合适的插入位置arr[j] < arr[j-1]
//        1.0
//        for(int j = i; j > 0; j--) {
//            if(arr[j] < arr[j-1])
//                swap(arr[j], arr[j-1]);
//            else
//                break;
//        }

//        改写2.0
//        for(int j = i; j > 0 && arr[j] < arr[j-1]; j--) {
//            swap(arr[j], arr[j-1]);
//        }

//        优化3.0
        T e = arr[i];
        int j; //j保存元素e应该插入的位置
        for (j = i; j > 0 && arr[j-1] > e; j--) {
            arr[j] = arr[j-1];
        }

        arr[j] = e;
    }
}

template<typename T>
void bubbleSort(T arr[], int n) {

    for (int i = n - 1; i > 0; i--)
        for (int j = i; j > 0; j--)
            if (arr[j] < arr[j - 1])
                swap(arr[j], arr[j - 1]);
}

int main()
{
    int n = 10000;
    int *arr = SortTestHelper::generateNearlyOrderedArray(n, 1);
    int *arr2 = SortTestHelper::copyArray(arr, n);

//    SortTestHelper::testSort("Insertion sort", insertionSort, arr, n);
//    SortTestHelper::testSort("Selection sort", selectionSort, arr2, n);

    bubbleSort(arr, n);
    SortTestHelper::printArray(arr, n);


    delete[] arr;
    delete[] arr2;
    return 0;
}
