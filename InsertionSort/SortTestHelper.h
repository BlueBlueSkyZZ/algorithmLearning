#ifndef SORTTESTHELPER_H_INCLUDED
#define SORTTESTHELPER_H_INCLUDED

#include<iostream>
#include<ctime>
#include<cassert>
using namespace std;


namespace SortTestHelper{
    /**
    ������n��Ԫ�ص�������飬ÿ��Ԫ�ص������ΧΪrangeL��rangeR
    */
    int * generateRandomArray(int n, int rangeL, int rangeR){

        assert(rangeL <= rangeR);

        int *arr = new int[n];
        //�����������
        srand(time(NULL));

        for(int i = 0; i < n; i++) {
            //rand()�����������
            arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
        }

        return arr;
    }

    /**
    ����һ���������������
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
    ��ӡ����
    */
    template<typename T>
    void printArray(T arr[], int n){

        for (int i = 0; i < n; i++)
            cout << arr[i] << " ";
        cout << endl;

        return;
    }

    /**
    �ж������Ƿ�ɹ�
    */
    template<typename T>
    bool isSorted(T arr[], int n) {
        for (int i = 0; i < n - 1; i++)
            if(arr[i] > arr[i+1])
                return false;

        return true;
    }

    /**
    ���Ժ�������
    sortName����������
    �ڶ�������Ϊ����ָ��
    */
    template<typename T>
    void testSort(string sortName, void(*sort)(T[], int), T arr[], int n) {
        //ʱ������
        clock_t startTime = clock();
        sort(arr, n);
        clock_t endTime = clock();

        assert(isSorted(arr, n));
        cout << sortName << ":" << double(endTime-startTime) / CLOCKS_PER_SEC << " s" << endl;
        return;
    }

    /**
    ����һ����������
    ����һ�������飬���������볤��
    */
    int* copyIntArray(int a[], int n) {

        int* arr = new int[n];
        copy(a, a+n, arr);
        return arr;
    }

    /**
    ����һ������
    */
    template<typename T>
    T* copyArray(T a[], int n) {

        T* arr = new T[n];
        copy(a, a+n, arr);
        return arr;
    }
}

#endif // SORTTESTHELPER_H_INCLUDED