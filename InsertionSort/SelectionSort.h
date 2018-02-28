#ifndef SELECTIONSORT_H_INCLUDED
#define SELECTIONSORT_H_INCLUDED

#include <iostream>
#include <algorithm>

using namespace std;

/**
ѡ������
*/
template<typename T>
void selectionSort(T arr[], int n){

    for(int i = 0 ; i < n ; i ++){
        // Ѱ��[i,n)�������Сֵ
        int minIndex = i;
        for( int j = i + 1 ; j < n ; j ++ )
            if( arr[j] < arr[minIndex] )
                minIndex = j;

        swap( arr[i] , arr[minIndex] );
    }
}

#endif // SELECTIONSORT_H_INCLUDED
