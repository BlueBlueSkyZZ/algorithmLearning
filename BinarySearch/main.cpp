#include <iostream>

using namespace std;

//���ֲ��ҷ�
//�ҵ�target��������Ӧ������index
//���û���ҵ�target,����-1
template<typename T>
int binarySearch(T arr[], int n, T target) {

    //��arr[L...R]֮�в���
    int L = 0, R = n-1;
    while(L <= R) {
        //���ܴ������bug
//        int mid = (L+R)/2;
        int mid = L + (R-L)/2;
        if(arr[mid] == target)
            return mid;

        if(target < arr[mid])
            //��arr[L...mid-1]֮�в���target
            R = mid - 1;
        else
            //��arr[mid+1...R]֮�в���
            L = mid + 1;
    }

    return -1;
}


//�ݹ鷽��ʵ��
template<typename T>
int __binarySearch(T arr[], int L, int R, T target) {

    if(L > R)
        return -1;

    //��arr[L...R]֮�в���
    int mid = L + (R-L)/2;

    if(arr[mid] == target)
        return mid;
    else if(arr[mid] > target)
        return __binarySearch(arr, L, mid-1, target);
    else
        return __binarySearch(arr, mid+1, R, target);

}

template<typename T>
int binarySearch2(T arr[], int n, T target) {

    int result = __binarySearch(arr, 0, n-1, target);

    return result;
}



int main()
{
    int arr[5] = {3,5,4,1,2};

    cout << binarySearch2(arr, 5, 4) << endl;
    return 0;
}
