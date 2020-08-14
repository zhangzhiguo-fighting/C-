#ifndef _BETREE_H
#define _BETREE_H

#include <iostream>
#include <memory> //使用 C++ 提供的智能指针
using namespace std;

namespace haizei {

template<typename T>
class BSNode {
public:
    BSNode(const T &data) : data(data), lchild(nullptr), rchild(nullptr) {
        std::cout << "Node constructor" << endl;
    }
    bool operator<(const BSNode<T> &obj) {
        return this->data < obj.data;
    }
    bool operator>(const BSNode<T> &obj) {
        return obj.data < this->data;
    }
    bool operator!=(const BSNode<T> &obj) {
        return (this->data < obj.data) || (obj.data < this->data);
    }
    bool operator==(const BSNode<T> &obj) {
        return !(*this != obj);
    }
    std::shared_ptr<BSNode<T>> lchild, rchild;
    std::weak_ptr<BSNode<T> > father; // weak_ptr 弱指针类型，没有实际对象，只有调用自带的lock()方法才会产生对象
    ~BSNode() {
        std::cout << "destructor" << endl;
    }
    T data;
};

//寻找后继
template<typename T>
class BSTree_helper {
public:
    static std::shared_ptr<BSNode<T> > get_next(std::shared_ptr<BSNode<T> > p) {
        // 如果有右子树（右子树中最左边的节点）
        if (p->rchild != nullptr) {
            p = p->rchild;
            while (p->lchild != nullptr) p = p->lchild;
            return p;
        }
        // 如果没有右子树，那么该节点的父节点就是该节点的后继
        while (p->father.lock() != nullptr && p->father.lock()->rchild == p) p = p->father.lock();
        if (p->father.lock() == nullptr) return p;
        return p->father.lock();
    }
};

template<typename T>
class BSTree_iterator {
    using helper = BSTree_helper<T>; // 给 BSTree_helper<T> 命名为 helper
public:
    BSTree_iterator() : node(nullptr) {} // 默认构造函数
    BSTree_iterator(std::shared_ptr<BSNode<T> > node) : node(node) {} // 有参构造函数
    
    BSTree_iterator<T> &operator++() { //无参数的为前++
        node = helper::get_next(node);
        return *this;
    }
    BSTree_iterator<T> operator++(int) { // 有参数的为后++
        BSTree_iterator iter(*this);
        node = helper::get_next(node);
        return iter;
    }

    bool operator == (const BSTree_iterator<T> &iter) {
        return this->node == iter.node; // 这里node是一个智能指针类型，所以可以使用 == 直接比较。
    }
    bool operator != (const BSTree_iterator<T> &iter) {
        return this->node != iter.node;
    }
    T &operator*() {
        return node->data;
    }

private:
    std::shared_ptr<BSNode<T> > node;
};

template<typename T>
struct BSTree {
public:
    typedef BSTree_iterator<T> iterator;
    BSTree() : root(std::make_shared<BSNode<T> >(T())) {}
    void insert(const T &data) {
        std::shared_ptr<BSNode<T> > p = this->root;
        std::shared_ptr<BSNode<T> > new_node = std::make_shared<BSNode<T> >(data); 
        if (p->lchild == nullptr) { //存在一个虚拟节点
            p->lchild = new_node;
            new_node->father = p;
            return ;
        }
        p = p->lchild;
        while (*p != *new_node) {
            if (*p > *new_node) {
                if (p->lchild == nullptr) {
                    p->lchild = new_node;
                    new_node->father = p;
                    break;
                }
                p = p->lchild;
            } else {
                if (p->rchild == nullptr) {
                    p->rchild = new_node;
                    new_node->father = p;
                    break;
                }
                p = p->rchild;
            }
        }
        return ;
    }
    iterator begin() {
        if (root->lchild == nullptr) return iterator(root);
        return iterator(root->lchild);
    }
    iterator end() {
        return iterator(root);
    }
private:
    std::shared_ptr<BSNode<T> > root;
};

}

#endif
