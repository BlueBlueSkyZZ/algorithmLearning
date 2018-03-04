#include <iostream>
#include <algorithm>
#include <queue>
#include <ctime>
#include <cassert>

using namespace std;

template <typename Key, typename Value>
class BST{

private:
    struct Node{
        Key key;
        Value value;
        Node *left;
        Node *right;

        Node(Key key, Value value) {
            this->key = key;
            this->value = value;
            this->left = this->right = NULL;
        }

        //����һ��
        Node(Node* node) {
            this->key = node->key;
            this->value = node->value;
            this->left = node->left;
            this->right = node->right;
        }
    };

    Node *root;
    int count;

public:
    BST(){
        root = NULL;
        count = 0;
    }

    ~BST(){
        destory(root);
    }

    int size(){
        return count;
    }

    bool isEmpty(){
        return count == 0;
    }

    void insert(Key key, Value value) {

        root = insert(root, key, value);
    }

    bool contain(Key key) {
        return contain(root, key);
    }
    /**
    ����ֵ������Node�������������ݽṹ
    ����Value���ܲ�����
    */
    Value* search(Key key){
        return search(root, key);
    }

    //ǰ�����
    void preOrder(){
        preOrder(root);
    }

    //�������
    void inOrder(){
        inOrder(root);
    }

    //�������
    void postOrder(){
        postOrder(root);
    }

    //�������
    void levelOrder(){

        queue<Node*> q;
        q.push(root);
        while(!q.empty()){
            //ȡ������
            Node* node = q.front();
            q.pop();

            cout<<node->key<<endl;

            if(node->left)
                q.push(node->left);
            if(node->right)
                q.push(node->right);
        }
    }

    //Ѱ����С�ļ�ֵ
    Key minimum(){
        assert(count != 0);
        Node* minNode = minimum(root);
        return minNode->key;
    }

    //Ѱ�����ļ�ֵ
    Key maximum(){
        assert(count != 0);
        Node* maxNode = maximum(root);
        return maxNode->key;
    }

    //�Ӷ�������ɾ����Сֵ���ڵĽڵ�
    void removeMin(){
        if(root)
            root = removeMin(root);
    }

    //�Ӷ�������ɾ�����ֵ���ڵĽڵ�
    void removeMax(){
        if(root)
            root = removeMax(root);
    }

    //�Ӷ�������ɾ����ֵΪkey�Ľڵ�
    void remove(Key key){
        remove(root, key);
    }

    void remove2(Key key){
        remove2(root, key);
    }

private:
    //����nodeΪ���Ķ����������в���ڵ�
    //���ز���ڵ�֮������������ĸ�
    Node* insert(Node *node, Key key, Value value) {

        //�ݹ鵽������
        if(node == NULL) {
            count++;
            return new Node(key, value);
        }

        if(key == node->key)
            node->value = value;
        else if(key < node->key)
            node->left = insert(node->left, key, value);
        else
            node->right = insert(node->right, key, value);

        return node;
    }

    //��nodeΪ���Ķ������������Ƿ������ֵΪkey�Ľڵ�
    bool contain(Node* node, Key key) {

        if(node == NULL)
            return false;

        if(key == node->key)
            return true;
        else if(key < node->key)
            return contain(node->left, key);
        else
            return contain(node->right, key);
    }

    //������nodeΪ���Ķ�����������key��Ӧ��value
    Value* search(Node* node, Key key){
        if(node == NULL) {
            return NULL;
        }

        if(key == node->key)
            return &(node->value);
        else if(key < node->key)
            return search(node->left, key);
        else
            return search(node->right, key);

    }

    //����nodeΪ���Ķ�������������ǰ�����
    void preOrder(Node* node){
        if(node != NULL){
            cout<<node->key<<endl;
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    //����nodeΪ���Ķ��������������������
    void inOrder(Node* node){
        if(node != NULL){
            inOrder(node->left);
            cout<<node->key<<endl;
            inOrder(node->right);
        }
    }

    //����nodeΪ���Ķ������������к������
    void postOrder(Node* node){

        if(node != NULL){
            postOrder(node->left);
            postOrder(node->right);
            cout<<node->key<<endl;
        }
    }

    //���ú������˼��
    void destory(Node* node){

        if(node != NULL){
            destory(node->left);
            destory(node->right);

            delete node;
            count--;

        }
    }

    //����nodeΪ���Ķ���������������Сֵ�ڵ�
    Node* minimum(Node* node){
        if(node->left == NULL)
            return node;

        return minimum(node->left);
    }

    //����nodeΪ���Ķ����������������ֵ�ڵ�
    Node* maximum(Node* node){
        if(node->right == NULL)
            return node;

        return maximum(node->right);
    }

    //ɾ����nodeΪ���Ķ�������������С�ڵ�
    //�����µĶ����������ĸ�
    Node* removeMin(Node* node){

        if(node->left == NULL){
            //�ҽڵ㲻����Ҳû��ϵ
            Node* rightNode = node->right;
            delete node;
            count--;

            return rightNode;
        }

        node->left = removeMin(node->left);
        return node;
    }

    //ɾ����nodeΪ���Ķ��������������ڵ�
    //�����µĶ����������ĸ�
    Node* removeMax(Node* node){

        if(node->right == NULL){
            //��ڵ㲻����Ҳû��ϵ
            Node* leftNode = node->right;
            delete node;
            count--;

            return leftNode;
        }

        node->right = removeMax(node->right);
        return node;
    }

    //ɾ����nodeΪ��������������key�Ľڵ�
    //����ɾ���ڵ������������ĸ�
    Node* remove(Node* node, Key key){

        //Ѱ��
        //������
        if(node == NULL)
            return NULL;

        if(key < node->key){
            node->left = remove(node->left, key);
            return node;
        }
        else if(key > node->key){
            node->right = remove(node->right, key);
            return node;
        }
        else{ //key == node->key
            if(node->left == NULL){
                Node *rightNode = node->right;
                delete node;
                count--;
                return rightNode;
            }

            if(node->right == NULL){
                Node *leftNode = node->left;
                delete node;
                count--;
                return leftNode;
            }

            //���Ҷ���Ϊ��
            //����һ�ݷ�ָֹ���,�õ���̽ڵ�
            Node *successor = new Node(minimum(node->right));
            count++;

            successor->right = removeMin(node->right);
            successor->left = node->left;

            delete node;
            count--;

            return successor;
        }
    }

    Node* remove2(Node* node, Key key) {
        if(node == NULL)
            return NULL;

        if(node->key > key){
            node->left = remove2(node->left, key);
            return node;
        }
        else if(node->key < key){
            node->right = remove2(node->right, key);
            return node;
        }
        else{
            //key == node->key
            if(node->left == NULL){
                Node* rightNode = node->right;
                delete node;
                count--;
                return rightNode;
            }
            else if(node->right == NULL){
                Node* leftNode = node->left;
                delete node;
                count--;
                return leftNode;
            }

            //if node->left && node->right != NULL
            Node* processor = new Node(maximum(node->left));
            count++;

            processor->left = removeMax(node->left);
            processor->right = node->right;

            delete node;
            count--;

            return processor;
        }

    }
};

int main()
{
    srand(time(NULL));
    BST<int,int> bst = BST<int,int>();

    // ȡn��ȡֵ��Χ��[0...m)����������Ž�������������
    int N = 10;
    int M = 20;
    for( int i = 0 ; i < N ; i ++ ){
        int key = rand()%M;
        // Ϊ�˺������Է���,����valueֵȡ��keyֵһ��
        int value = key;
        cout<<key<<" ";
        bst.insert(key,value);
    }

    cout<<endl;

    // ���Զ�����������size()
    cout<<"size: "<<bst.size()<<endl<<endl;

    // ���Զ�����������ǰ����� preOrder
    cout<<"preOrder: "<<endl;
    bst.preOrder();
    cout<<endl;

    // ���Զ������������������ inOrder
    cout<<"inOrder: "<<endl;
    bst.inOrder();
    cout<<endl;

    // ���Զ����������ĺ������ postOrder
    cout<<"postOrder: "<<endl;
    bst.postOrder();
    cout<<endl;


    bst.remove2(10);

    // ���Զ����������Ĳ������ levelOrder
    cout<<"levelOrder: "<<endl;
    bst.levelOrder();
    cout<<endl;

    return 0;
}
