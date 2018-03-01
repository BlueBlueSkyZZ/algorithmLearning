#include <iostream>

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
    };

    Node *root;
    int count;

public:
    BST(){
        root = NULL;
        count = 0;
    }

    ~BST(){
        // TODO:
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
            node->right = insert(node->left, key, value);

        return node;
    }
};

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
