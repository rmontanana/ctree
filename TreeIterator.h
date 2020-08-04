//
// Created by rmontanana on 3/8/20.
//

#ifndef CTREE_TREEITERATOR_H
#define CTREE_TREEITERATOR_H

#include "Tree.h"

template<class Type>
class TreeIterator {
private:
    Tree<Type> baseTree;
    Node<Type> *iterator;
public:
    TreeIterator(Tree<Type> &tree) : baseTree(tree), iterator(nullptr) {};

    void begin();

    Node<Type> *next();
};

template<class Type>
void TreeIterator<Type>::begin() {
    iterator = nullptr;
}

template<class Type>
Node<Type> *TreeIterator<Type>::next() {
    return iterator = iterator ? baseTree.succesor(iterator) : baseTree.getLeastValue(baseTree.getRoot());
}

#endif //CTREE_TREEITERATOR_H
