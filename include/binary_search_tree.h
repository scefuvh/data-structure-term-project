/*
 * Copyright 2020 David Hu, all rights reserved.
 * Email: 1697552203@qq.com
 */


#ifndef __hhz_binary_search_tree
#ifndef NULL
#define NULL 0
#endif


enum BalanceFactor
{
    rr = -2, r, b, l, ll
};


template<typename T>
struct BinaryNode
{
    T value;
    BinaryNode<T> *left_child, *right_child;
    int balance = b;
    unsigned height = 0;
    BinaryNode(T valuer, BinaryNode<T> *left_childr = NULL, BinaryNode<T> *right_childr = NULL);
};


template<typename T>
class BinarySearchTree
{
    public:
        BinarySearchTree(){}
        ~BinarySearchTree();
        BinarySearchTree(BinarySearchTree &a);
        BinarySearchTree& operator=(const BinarySearchTree &a);
        void insert(T &value);
        void remove(const T &value);
        BinaryNode<T>*  search(const T &value)const;

    private:
        BinaryNode<T> *root = NULL;
        unsigned numbers = 0;
        void search_and_destroy(BinaryNode<T> * &sub_root, const T &target, bool &shorter);
        void remove_root(BinaryNode<T> * &sub_roota, bool &shorter);
        void rotater(BinaryNode<T> *node);
        void rotatel(BinaryNode<T> *node);
        void rebalancel(BinaryNode<T> *node);
        void rebalancer(BinaryNode<T> *node);
        void recursive_insert(T &value, BinaryNode<T> *node, bool &taller);
};

#include "../source/binary_search_tree.cpp"
#define __hhz_binary_search_tree
#endif
