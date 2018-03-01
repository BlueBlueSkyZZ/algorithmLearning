#include <iostream>
#include <algorithm>
#include "Heap.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "SortTestHelper.h"

using namespace std;



template<typename Item>
class IndexMaxHeap{

private:
    Item* data;//数组指针
    int* indexes;//索引数组
    int* reverse;//反向索引

    int count;//现在有的数字
    int capacity;//数组容量

    //保持最大堆定义,维护索引k位置的元素
    void shiftUp(int k){
        //与父节点进行比较
        while(k > 1 && data[indexes[k/2]] < data[indexes[k]]) {
            swap(indexes[k/2], indexes[k]);

            reverse[indexes[k/2]] = k/2;
            reverse[indexes[k]] = k;

            k /= 2;
        }
    }

    void shiftDown(int k){
        //存在左孩子则继续
        while(2*k <= count) {
            //data[k]与data[j]交换位置
            int j = 2*k;
            if(j + 1 <= count && data[indexes[j+1]] > data[indexes[j]] )
                j += 1;

            //如果位置正确直接跳出
            if(data[indexes[k]] >= data[indexes[j]])
                break;

            swap(indexes[k], indexes[j]);

            reverse[indexes[k]] = k;
            reverse[indexes[j]] = j;

            k = j;

        }
    }

public:
    //构造函数
    IndexMaxHeap(int capacity){
        //开辟空间
        data =  new Item[capacity + 1];
        indexes = new Item[capacity + 1];
        reverse = new Item[capacity + 1];
        for(int i = 0; i <= capacity; i++)
            reverse[i] = 0;

        count = 0;
        this->capacity = capacity;
    }

    ~IndexMaxHeap(){
        delete[] data;
        delete[] indexes;
        delete[] reverse;
    }

    int size(){
        return count;
    }

    bool isEmpty(){
        return count == 0;
    }

    //传入的i对用户而言，计算机从0开始
    void insert(int i, Item item){
        //检查是否超出了容量，可以进行修改
        assert(count + 1 <= capacity);
        assert( i +1 >= 1 && i + 1 <= capacity);

        i += 1;
        data[i] = item;
        indexes[count+1] = i;
        reverse[i] = count + 1;

        count++;
        shiftUp(count);
    }

    //取出最大值（根节点）
    Item extractMax(){
        assert(count > 0);

        Item ret = data[indexes[1]];

        //保持二叉堆性质
        swap(indexes[1], indexes[count]);

        reverse[indexes[1]] = 1;
        reverse[indexes[count]] = 0;

        count--;
        shiftDown(1);

        return ret;
    }

    //取出最大值（根节点）返回索引
    int extractMaxIndex(){
        assert(count > 0);

        int ret = indexes[1] - 1;

        //保持二叉堆性质
        swap(indexes[1], indexes[count]);

        reverse[indexes[1]] = 1;
        reverse[indexes[count]] = 0;

        count--;
        shiftDown(1);

        return ret;
    }

    /**
    判断是否存在于数组中
    */
    bool contain(int i) {
        assert(i + 1 >= 1 && i + 1 <= capacity);
        return reverse[i+1] != 0;
    }

    Item getItem(int i) {
        //判断索引i是否在堆中
        assert(contain(i));
        return data[i+1];
    }

    void change(int i, Item newItem) {
        //判断索引i是否在堆中
        assert(contain(i));

        //i与索引存放位置有关
        i += 1;
        data[i] = newItem;

        //找到索引i在indexes中的位置
        //尝试上移下移
//        for(int j = 1; j <= count; j++) {
//            if(indexes[j] == i) {
//                shiftUp(j);
//                shiftDown(j);
//                return;
//            }
//        }
        int j = reverse[i];
        shiftUp(j);
        shiftDown(j);
    }

public:
    // 以树状打印整个堆结构
    void testPrint(){

        // 我们的testPrint只能打印100个元素以内的堆的树状信息
        if( size() >= 100 ){
            cout<<"This print function can only work for less than 100 int";
            return;
        }

        // 我们的testPrint只能处理整数信息
        if( typeid(Item) != typeid(int) ){
            cout <<"This print function can only work for int item";
            return;
        }

        cout<<"The max heap size is: "<<size()<<endl;
        cout<<"Data in the max heap: ";
        for( int i = 1 ; i <= size() ; i ++ ){
            // 我们的testPrint要求堆中的所有整数在[0, 100)的范围内
            assert( data[i] >= 0 && data[i] < 100 );
            cout<<data[i]<<" ";
        }
        cout<<endl;
        cout<<endl;

        int n = size();
        int max_level = 0;
        int number_per_level = 1;
        while( n > 0 ) {
            max_level += 1;
            n -= number_per_level;
            number_per_level *= 2;
        }

        int max_level_number = int(pow(2, max_level-1));
        int cur_tree_max_level_number = max_level_number;
        int index = 1;
        for( int level = 0 ; level < max_level ; level ++ ){
            string line1 = string(max_level_number*3-1, ' ');

            int cur_level_number = min(count-int(pow(2,level))+1,int(pow(2,level)));
            bool isLeft = true;
            for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; index ++ , index_cur_level ++ ){
                putNumberInLine( data[index] , line1 , index_cur_level , cur_tree_max_level_number*3-1 , isLeft );
                isLeft = !isLeft;
            }
            cout<<line1<<endl;

            if( level == max_level - 1 )
                break;

            string line2 = string(max_level_number*3-1, ' ');
            for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; index_cur_level ++ )
                putBranchInLine( line2 , index_cur_level , cur_tree_max_level_number*3-1 );
            cout<<line2<<endl;

            cur_tree_max_level_number /= 2;
        }
    }

private:
    void putNumberInLine( int num, string &line, int index_cur_level, int cur_tree_width, bool isLeft){

        int sub_tree_width = (cur_tree_width - 1) / 2;
        int offset = index_cur_level * (cur_tree_width+1) + sub_tree_width;
        assert(offset + 1 < line.size());
        if( num >= 10 ) {
            line[offset + 0] = '0' + num / 10;
            line[offset + 1] = '0' + num % 10;
        }
        else{
            if( isLeft)
                line[offset + 0] = '0' + num;
            else
                line[offset + 1] = '0' + num;
        }
    }

    void putBranchInLine( string &line, int index_cur_level, int cur_tree_width){

        int sub_tree_width = (cur_tree_width - 1) / 2;
        int sub_sub_tree_width = (sub_tree_width - 1) / 2;
        int offset_left = index_cur_level * (cur_tree_width+1) + sub_sub_tree_width;
        assert( offset_left + 1 < line.size() );
        int offset_right = index_cur_level * (cur_tree_width+1) + sub_tree_width + 1 + sub_sub_tree_width;
        assert( offset_right < line.size() );

        line[offset_left + 1] = '/';
        line[offset_right + 0] = '\\';
    }

};



template<typename T>
void heapSort1(T arr[], int n) {

    //放入最大堆中
    MaxHeap<T> maxHeap = MaxHeap<T>(n);
    for(int i = 0; i < n; i++) {
        maxHeap.insert(arr[i]);
    }

    //从小到大排序
    for(int i = n-1; i >=0; i--) {
        arr[i] = maxHeap.extractMax();
    }
}

template<typename T>
void heapSort2(T arr[], int n) {

    //放入最大堆中
    MaxHeap<T> maxHeap = MaxHeap<T>(arr, n);

    //从小到大排序
    for(int i = n-1; i >=0; i--) {
        arr[i] = maxHeap.extractMax();
    }
}

template<typename T>
void __shiftDown(T arr[], int n, int k) {
    //存在左孩子则继续
    while(2*k + 1 < n) {
        //arr[k]arr[j]交换位置
        int j = 2*k + 1;
        if(j + 1 < n && arr[j+1] > arr[j] )
            j += 1;

        //如果位置正确直接跳出
        if(arr[k] >= arr[j])
            break;

        swap(arr[k], arr[j]);
        k = j;

    }
}


// 优化的shiftDown过程, 使用赋值的方式取代不断的swap,
// 该优化思想和我们之前对插入排序进行优化的思路是一致的
template<typename T>
void __shiftDown2(T arr[], int n, int k){

    T e = arr[k];
    while( 2*k+1 < n ){
        int j = 2*k+1;
        if( j+1 < n && arr[j+1] > arr[j] )
            j += 1;

        if( e >= arr[j] ) break;

        arr[k] = arr[j];
        k = j;
    }

    arr[k] = e;
}


/**
原地堆排序
*/
template<typename T>
void heapSort(T arr[], int n) {

    // 注意，此时我们的堆是从0开始索引的
    // 从(最后一个元素的索引-1)/2开始
    // 最后一个元素的索引 = n-1
    //heapify 构建一个堆
    for(int i = (n-1 - 1)/2; i >= 0; i--) {
        __shiftDown(arr, n, i);
    }

    for(int i = n-1; i > 0; i--) {
        swap(arr[0], arr[i]);
        __shiftDown(arr, i, 0);
    }
}

int main()
{
    int n = 100000;

    int* arr1 = SortTestHelper::generateRandomArray(n, 0, n);
    int* arr2 = SortTestHelper::copyArray(arr1, n);
    int* arr3 = SortTestHelper::copyArray(arr1, n);
    int* arr4 = SortTestHelper::copyArray(arr1, n);
    int* arr5 = SortTestHelper::copyArray(arr1, n);
    int* arr6 = SortTestHelper::copyArray(arr1, n);

    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
    SortTestHelper::testSort("Quick Sort", quickSort2, arr2, n);
    SortTestHelper::testSort("Quick Sort 3 Ways", quickSort3Ways, arr3, n);
    SortTestHelper::testSort("Heap Sort 1", heapSort1, arr4, n);
    SortTestHelper::testSort("Heap Sort 2", heapSort2, arr5, n);
    SortTestHelper::testSort("Heap Sort 3", heapSort, arr6, n);
//    heapSort(arr6, n);
//    SortTestHelper::printArray(arr6, n);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
    delete[] arr6;
}
