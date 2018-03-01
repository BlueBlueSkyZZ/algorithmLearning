#include <iostream>

using namespace std;

//二分查找法
//找到target，返回相应的索引index
//如果没有找到target,返回-1
template<typename T>
int binarySearch(T arr[], int n, T target) {

    //在arr[L...R]之中查找
    int L = 0, R = n-1;
    while(L <= R) {
        //可能存在溢出bug
//        int mid = (L+R)/2;
        int mid = L + (R-L)/2;
        if(arr[mid] == target)
            return mid;

        if(target < arr[mid])
            //在arr[L...mid-1]之中查找target
            R = mid - 1;
        else
            //在arr[mid+1...R]之中查找
            L = mid + 1;
    }

    return -1;
}


//递归方法实现
template<typename T>
int __binarySearch(T arr[], int L, int R, T target) {

    if(L > R)
        return -1;

    //在arr[L...R]之中查找
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
