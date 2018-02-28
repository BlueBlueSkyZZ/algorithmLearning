#ifndef INSERTIONSORT_H_INCLUDED
#define INSERTIONSORT_H_INCLUDED
#include <iostream>
#include <algorithm>

using namespace std;

template<typename T>
void insertionSort(T arr[], int n) {

    for (int i = 1; i < n; i++) {

        // 寻找元素arr[i]合适的插入位置arr[j] < arr[j-1]
        T e = arr[i];
        int j; //j保存元素e应该插入的位置
        for (j = i; j > 0 && arr[j-1] > e; j--) {
            arr[j] = arr[j-1];
        }

        arr[j] = e;
    }
}

template<typename T>
void insertionSort(T arr[], int L, int R) {

    for (int i = L+1; i <= R; i++) {

        // 寻找元素arr[i]合适的插入位置arr[j] < arr[j-1]
        T e = arr[i];
        int j; //j保存元素e应该插入的位置
        for (j = i; j > L && arr[j-1] > e; j--) {
            arr[j] = arr[j-1];
        }

        arr[j] = e;
    }
}

#endif // INSERTIONSORT_H_INCLUDED
