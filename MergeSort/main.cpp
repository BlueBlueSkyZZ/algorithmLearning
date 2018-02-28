#include <iostream>
#include <algorithm>
#include "SortTestHelper.h"
#include "InsertionSort.h"

using namespace std;

/**
将arr[L,mid]和arr[mid+1,R]两部分进行归并
*/
template<typename T>
void __merge(T arr[], int L, int mid, int R) {

    //开辟临时空间
    T tem[R - L + 1];
    //存储原数值
    for(int i = L; i <= R; i++) {
        tem[i - L] = arr[i];
    }
    //初始化索引位置,i为左侧索引,j为右侧
    int i = L, j = mid + 1;
    //k为应该插入arr的位置
    for(int k = L; k <= R; k++) {

        //前面两个先判断索引合法性，
        if(i > mid) {
        //左侧排完了
            arr[k] = tem[j - L];
            j++;
        } else if(j > R) {
        //右侧排完了
            arr[k] = tem[i - L];
            i++;
        } else if(tem[i - L] < tem[j - L]){
            arr[k] = tem[i - L];
            i++;
        } else {
            arr[k] = tem[j - L];
            j++;
        }
    }
}


/**
递归使用归并排序，对arr[L,R]范围进行排序
L,R为闭区间，R表示最后一个而非最后一个的后面一个
*/
template<typename T>
void __mergeSort(T arr[], int L, int R) {

    //跳出条件
//    if(L >= R)
//        return;

    //优化代码2，数组较小的时候用插入代替归并,15的取值有待商榷
    if( R - L <= 15){
        insertionSort(arr, L, R);
        return;
    }

    //注意L+R可能会溢出
    int mid = (L + R)/2;
    //递归二分
    __mergeSort(arr, L, mid);
    __mergeSort(arr, mid + 1, R);

    //优化代码1
    if(arr[mid] > arr[mid + 1])
        //归并左右两部分
        __merge(arr, L, mid, R);
}

template<typename T>
void mergeSort(T arr[], int n) {

    __mergeSort(arr, 0, n-1);
}

int main()
{
    int n = 500000;

    int* arr1 = SortTestHelper::generateRandomArray(n, 0, n);
    int* arr2 = SortTestHelper::copyArray(arr1, n);

    double time1 = SortTestHelper::testSort("Insertion Sort", insertionSort, arr1, n, 1);
    double time2 = SortTestHelper::testSort("Merge Sort", mergeSort, arr2, n, 1);




    if(time1 < time2) {
        cout << "insertion fast!" << endl;
    } else {
        cout << "merge fast" << endl;
    }

    delete[] arr1;
    delete[] arr2;

}
