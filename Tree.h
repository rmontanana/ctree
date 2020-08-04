//
// Created by Ricardo Montañana on 29/07/2020.
//

#ifndef CTREE_TREE_H
#define CTREE_TREE_H

#include <vector>
#include "Node.h"

enum class typePrint {
    InOrder, PreOrder, PostOrder, in2D
};

template<class Type>
class Tree {
private:
    Node<Type> *root;

    void preOrder(const Node<Type> *);

    void postOrder(const Node<Type> *);

    void inOrder(const Node<Type> *);

    void print2D(const Node<Type> *, int);

    void erase(Node<Type> *); // deletes all nodes in the tree
    Node<Type> *rebuild(std::vector<Type> &, int, int);

    void storeList(Node<Type> *, std::vector<Type> &);

    Node<Type> *searchValue(Node<Type> *, const Type);

    void searchValueAndFather(const Type, Node<Type> **, Node<Type> **);

    Node<Type> *insertValue(Node<Type> *, const Type);

public:
    Node<Type> *getLeastValue(Node<Type> *);

    Node<Type> *getRoot() { return root; }

    Tree() : root(nullptr) {};

    explicit Tree(Type);

    Node<Type> *insert(const Type);

    void print(typePrint);

    bool search(const Type);

    void balance(); // make a balanced binary tree
    bool remove(const Type); // Remove node if exists
    Node<Type> *succesor(Node<Type> *);
};

#include "Tree.ipp"

#endif //CTREE_TREE_H
