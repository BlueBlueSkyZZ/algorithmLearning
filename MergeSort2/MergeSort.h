#ifndef MERGESORT_H_INCLUDED
#define MERGESORT_H_INCLUDED

#include <iostream>
#include <algorithm>
#include "SortTestHelper.h"
#include "InsertionSort.h"

using namespace std;

/**
��arr[L,mid]��arr[mid+1,R]�����ֽ��й鲢
*/
template<typename T>
void __merge(T arr[], int L, int mid, int R) {

    //������ʱ�ռ�
    T tem[R - L + 1];
    //�洢ԭ��ֵ
    for(int i = L; i <= R; i++) {
        tem[i - L] = arr[i];
    }
    //��ʼ������λ��,iΪ�������,jΪ�Ҳ�
    int i = L, j = mid + 1;
    //kΪӦ�ò���arr��λ��
    for(int k = L; k <= R; k++) {

        //ǰ���������ж������Ϸ��ԣ�
        if(i > mid) {
        //���������
            arr[k] = tem[j - L];
            j++;
        } else if(j > R) {
        //�Ҳ�������
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
�ݹ�ʹ�ù鲢���򣬶�arr[L,R]��Χ��������
L,RΪ�����䣬R��ʾ���һ���������һ���ĺ���һ��
*/
template<typename T>
void __mergeSort(T arr[], int L, int R) {

    //��������
//    if(L >= R)
//        return;

    //�Ż�����2�������С��ʱ���ò������鲢,15��ȡֵ�д���ȶ
    if( R - L <= 15){
        insertionSort(arr, L, R);
        return;
    }

    //ע��L+R���ܻ����
    int mid = (L + R)/2;
    //�ݹ����
    __mergeSort(arr, L, mid);
    __mergeSort(arr, mid + 1, R);

    //�Ż�����1
    if(arr[mid] > arr[mid + 1])
        //�鲢����������
        __merge(arr, L, mid, R);
}

template<typename T>
void mergeSort(T arr[], int n) {

    __mergeSort(arr, 0, n-1);
}


#endif // MERGESORT_H_INCLUDED
