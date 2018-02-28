#include <iostream>
#include <algorithm>
#include "SortTestHelper.h"
#include "MergeSort.h"

using namespace std;

/**
自底而上的归并排序
没有使用arr的索引，可用于链表的排序
*/
template <typename T>
void mergeSortBU(T arr[], int n) {

    for( int sz = 1; sz <= n; sz += sz) {
        //i+sz<n保证存在第二部分，min解决第二部分数量不足问题
        for(int i = 0; i + sz < n; i += sz * 2) {
            //对arr[i...i+sz-1]和arr[i+sz...i+2*sz-1]进行归并
            __merge( arr, i, i + sz -1, min(i + sz * 2 -1, n - 1) );
        }
    }
}

int main()
{
    int n = 500000;

    int* arr1 = SortTestHelper::generateRandomArray(n, 0, n);
    int* arr2 = SortTestHelper::copyArray(arr1, n);

    SortTestHelper::testSort("mergeSortt", mergeSort, arr1, n);
    SortTestHelper::testSort("mergeSortBU", mergeSortBU, arr2, n);



    delete[] arr1;
    delete[] arr2;
    return 0;
}
