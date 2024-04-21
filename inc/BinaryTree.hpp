#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP
 
#include <iostream>

template <typename Type>
struct Node {
    Type item{};
    Node<Type>* left{ nullptr };
    Node<Type>* right{ nullptr };
};

template <typename Type>
class BinaryTree {
public:
    BinaryTree(){}
    BinaryTree(const BinaryTree<Type>& objToCopy);
    BinaryTree<Type>& operator=(const BinaryTree& b); 
    ~BinaryTree();
    void insert(Type item);
    void preOrder(std::ostringstream& out);
    void inOrder(std::ostringstream& out);
    void postOrder(std::ostringstream& out);
    int nodeCount();
    Node<Type>* find(Type item);
    Node<Type>* findRightMostNode(Node<Type>* find);
    void remove(Type item);
    int  height();
    int leavesCount();

protected:
    Node<Type>* root{ nullptr };

private:
    void destroy(Node<Type>* curr);
    void copyTree(Node<Type> * curr);
    void insert(Type item, Node<Type>* curr);
    void preOrder(std::ostringstream& out, Node<Type>* curr);
    void postOrder(std::ostringstream& out, Node<Type>* curr);
    void inOrder(std::ostringstream& out, Node<Type>* curr);
    int nodeCount(Node<Type>* curr);
    int leavesCount(Node<Type>* curr);
    Node<Type>* find(Type item, Node<Type>* curr);
    Node<Type>* remove(Type item, Node<Type>* curr);
    int height(Node<Type>* curr);
};

template <typename Type>
BinaryTree<Type>::~BinaryTree(){
    destroy(root);
}

template <typename Type>
BinaryTree<Type>::BinaryTree(const BinaryTree<Type>& b) {
    copyTree(b.root);
}

template <typename Type>
void BinaryTree<Type>::copyTree(Node<Type> * curr) {
    if (curr){
        insert(curr->item);
        copyTree(curr->left);
        copyTree(curr->right);
    }
}

template <typename Type>
BinaryTree<Type>& BinaryTree<Type>::operator=(const BinaryTree<Type>& b) {
    copyTree(b.root);
    return *this;
}

template <typename Type>
void BinaryTree<Type>::destroy(Node<Type>* curr){
    if (curr != nullptr) {
        destroy(curr->left);
        destroy(curr->right);
        delete curr;
    }
}

template <typename Type>
void BinaryTree<Type>::insert(Type item){
    if (root == nullptr){
        root = new Node<Type>;
        root->item = item;
        root->left = nullptr;
        root->right = nullptr;
    }
    else {
        insert(item, root);
    }
}

template <typename Type>
void BinaryTree<Type>::insert(Type item, Node<Type>* curr){
    if (item < curr->item) {
        if (curr->left == nullptr) {
            auto temp = new Node<Type>;
            temp->item = item;
            temp->left = nullptr;
            temp->right = nullptr;
            curr->left = temp;
        }
        else {
            insert(item, curr->left);
        }
    }
    else {
        if (curr->right == nullptr) {
            auto temp = new Node<Type>;
            temp->item = item;
            temp->left = nullptr;
            temp->right = nullptr;
            curr->right = temp;
        }
        else {
            insert(item, curr->right);
        }
    }
}

template <typename Type>
void BinaryTree<Type>::preOrder(std::ostringstream& out){
    preOrder(out, root);
}

template <typename Type>
void BinaryTree<Type>::preOrder(std::ostringstream& out, Node<Type>* curr){
    if (curr) {
        out << curr->item << " ";
        preOrder(out, curr->left);
        preOrder(out, curr->right);
    }
}

template <typename Type>
void BinaryTree<Type>::inOrder(std::ostringstream& out){
    inOrder(out, root);
}

template <typename Type>
void BinaryTree<Type>::inOrder(std::ostringstream& out, Node<Type>* curr){
    if (curr) {
        inOrder(out, curr->left);
        out << curr->item << " ";
        inOrder(out, curr->right);
    }
}

template <typename Type>
void BinaryTree<Type>::postOrder(std::ostringstream& out){
    postOrder(out, root);
}

template <typename Type>
void BinaryTree<Type>::postOrder(std::ostringstream& out, Node<Type>* curr){
    if (curr){
        postOrder(out, curr->left);
        postOrder(out, curr->right);
        out << curr->item << " ";
    }
}

template <typename Type>
int BinaryTree<Type>::nodeCount(){
    return nodeCount(root);
}

template <typename Type>
int BinaryTree<Type>::nodeCount(Node<Type>* curr){
     if (curr){
        return 1 + nodeCount(curr->left) + nodeCount(curr->right);
    }
    else {
        return 0;
    }
}

template <typename Type>
int BinaryTree<Type>::leavesCount(){
    return leavesCount(root);
}

template <typename Type>
int BinaryTree<Type>::leavesCount(Node<Type>* curr){
    if (curr == nullptr) {
        return 0;
    } 
    else if (curr->left == nullptr && curr->right == nullptr) {
        return 1;
    } 
    else {
        return leavesCount(curr->left) + leavesCount(curr->right);
    }
}


template <typename Type>
Node<Type>*BinaryTree<Type>::find(Type item){
    return find(item, root);
}


template <typename Type>
Node<Type>* BinaryTree<Type>::find(Type item, Node<Type>* curr){
    if (curr == nullptr) {
        return nullptr;
    } 
    else if (item == curr->item) {
        return curr;
    } 
    else if (item < curr->item) {
        return find(item, curr->left);
    } 
    else {
        return find(item, curr->right);
    }
}

template <typename Type>
Node<Type>* BinaryTree<Type>::findRightMostNode(Node<Type>* curr){
    if (curr == nullptr) {
        return nullptr;
    } 
    else if (curr->right == nullptr) {
        return curr;
    } 
    else {
        return findRightMostNode(curr->right);
    }
}

template <typename Type>
void BinaryTree<Type>::remove(Type item) {
    root = remove(item, root);
}

template <typename Type>
Node<Type>* BinaryTree<Type>::remove(Type item, Node<Type>* curr) {
    if (curr == nullptr) {
        return nullptr;
    } 
    else if (item < curr->item) {
        curr->left = remove(item, curr->left);
    } 
    else if (item > curr->item) {
        curr->right = remove(item, curr->right);
    } 
    else {
        if (curr->left == nullptr && curr->right == nullptr) {
            delete curr;
            curr = nullptr;
        } 
        else if (curr->left == nullptr) {
            Node<Type>* temp = curr;
            curr = curr->right;
            delete temp;
        } 
        else if (curr->right == nullptr) {
            Node<Type>* temp = curr;
            curr = curr->left;
            delete temp;
        } 
        else {
            Node<Type>* temp = findRightMostNode(curr->left);
            curr->item = temp->item;
            curr->left = remove(temp->item, curr->left);
        }
    }
    return curr;
}

template <typename Type>
int BinaryTree<Type>::height(){
    return height(root) - 1;
}

template <typename Type>
int BinaryTree<Type>::height(Node<Type>* curr){
    if (curr == nullptr) {
        return 0;
    }
    else {
        return 1 + std::max(height(curr->left), height(curr->right));
    }
}

#endif // BINARY_TREE_HPP
