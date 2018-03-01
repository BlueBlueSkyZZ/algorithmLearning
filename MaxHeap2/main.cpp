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
    Item* data;//����ָ��
    int* indexes;//��������
    int* reverse;//��������

    int count;//�����е�����
    int capacity;//��������

    //�������Ѷ���,ά������kλ�õ�Ԫ��
    void shiftUp(int k){
        //�븸�ڵ���бȽ�
        while(k > 1 && data[indexes[k/2]] < data[indexes[k]]) {
            swap(indexes[k/2], indexes[k]);

            reverse[indexes[k/2]] = k/2;
            reverse[indexes[k]] = k;

            k /= 2;
        }
    }

    void shiftDown(int k){
        //�������������
        while(2*k <= count) {
            //data[k]��data[j]����λ��
            int j = 2*k;
            if(j + 1 <= count && data[indexes[j+1]] > data[indexes[j]] )
                j += 1;

            //���λ����ȷֱ������
            if(data[indexes[k]] >= data[indexes[j]])
                break;

            swap(indexes[k], indexes[j]);

            reverse[indexes[k]] = k;
            reverse[indexes[j]] = j;

            k = j;

        }
    }

public:
    //���캯��
    IndexMaxHeap(int capacity){
        //���ٿռ�
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

    //�����i���û����ԣ��������0��ʼ
    void insert(int i, Item item){
        //����Ƿ񳬳������������Խ����޸�
        assert(count + 1 <= capacity);
        assert( i +1 >= 1 && i + 1 <= capacity);

        i += 1;
        data[i] = item;
        indexes[count+1] = i;
        reverse[i] = count + 1;

        count++;
        shiftUp(count);
    }

    //ȡ�����ֵ�����ڵ㣩
    Item extractMax(){
        assert(count > 0);

        Item ret = data[indexes[1]];

        //���ֶ��������
        swap(indexes[1], indexes[count]);

        reverse[indexes[1]] = 1;
        reverse[indexes[count]] = 0;

        count--;
        shiftDown(1);

        return ret;
    }

    //ȡ�����ֵ�����ڵ㣩��������
    int extractMaxIndex(){
        assert(count > 0);

        int ret = indexes[1] - 1;

        //���ֶ��������
        swap(indexes[1], indexes[count]);

        reverse[indexes[1]] = 1;
        reverse[indexes[count]] = 0;

        count--;
        shiftDown(1);

        return ret;
    }

    /**
    �ж��Ƿ������������
    */
    bool contain(int i) {
        assert(i + 1 >= 1 && i + 1 <= capacity);
        return reverse[i+1] != 0;
    }

    Item getItem(int i) {
        //�ж�����i�Ƿ��ڶ���
        assert(contain(i));
        return data[i+1];
    }

    void change(int i, Item newItem) {
        //�ж�����i�Ƿ��ڶ���
        assert(contain(i));

        //i���������λ���й�
        i += 1;
        data[i] = newItem;

        //�ҵ�����i��indexes�е�λ��
        //������������
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
    // ����״��ӡ�����ѽṹ
    void testPrint(){

        // ���ǵ�testPrintֻ�ܴ�ӡ100��Ԫ�����ڵĶѵ���״��Ϣ
        if( size() >= 100 ){
            cout<<"This print function can only work for less than 100 int";
            return;
        }

        // ���ǵ�testPrintֻ�ܴ���������Ϣ
        if( typeid(Item) != typeid(int) ){
            cout <<"This print function can only work for int item";
            return;
        }

        cout<<"The max heap size is: "<<size()<<endl;
        cout<<"Data in the max heap: ";
        for( int i = 1 ; i <= size() ; i ++ ){
            // ���ǵ�testPrintҪ����е�����������[0, 100)�ķ�Χ��
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

    //����������
    MaxHeap<T> maxHeap = MaxHeap<T>(n);
    for(int i = 0; i < n; i++) {
        maxHeap.insert(arr[i]);
    }

    //��С��������
    for(int i = n-1; i >=0; i--) {
        arr[i] = maxHeap.extractMax();
    }
}

template<typename T>
void heapSort2(T arr[], int n) {

    //����������
    MaxHeap<T> maxHeap = MaxHeap<T>(arr, n);

    //��С��������
    for(int i = n-1; i >=0; i--) {
        arr[i] = maxHeap.extractMax();
    }
}

template<typename T>
void __shiftDown(T arr[], int n, int k) {
    //�������������
    while(2*k + 1 < n) {
        //arr[k]arr[j]����λ��
        int j = 2*k + 1;
        if(j + 1 < n && arr[j+1] > arr[j] )
            j += 1;

        //���λ����ȷֱ������
        if(arr[k] >= arr[j])
            break;

        swap(arr[k], arr[j]);
        k = j;

    }
}


// �Ż���shiftDown����, ʹ�ø�ֵ�ķ�ʽȡ�����ϵ�swap,
// ���Ż�˼�������֮ǰ�Բ�����������Ż���˼·��һ�µ�
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
ԭ�ض�����
*/
template<typename T>
void heapSort(T arr[], int n) {

    // ע�⣬��ʱ���ǵĶ��Ǵ�0��ʼ������
    // ��(���һ��Ԫ�ص�����-1)/2��ʼ
    // ���һ��Ԫ�ص����� = n-1
    //heapify ����һ����
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
