#include <iostream>
#include <algorithm>
#include "SortTestHelper.h"
#include "MergeSort.h"

using namespace std;

/**
�Ե׶��ϵĹ鲢����
û��ʹ��arr�����������������������
*/
template <typename T>
void mergeSortBU(T arr[], int n) {

    for( int sz = 1; sz <= n; sz += sz) {
        //i+sz<n��֤���ڵڶ����֣�min����ڶ�����������������
        for(int i = 0; i + sz < n; i += sz * 2) {
            //��arr[i...i+sz-1]��arr[i+sz...i+2*sz-1]���й鲢
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
