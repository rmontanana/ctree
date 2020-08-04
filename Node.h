//
// Created by Ricardo Montañana on 29/07/2020.
//

#ifndef CTREE_NODE_H
#define CTREE_NODE_H

template<class Type>
class Node {
private:
    Type value;
    Node *left, *right;
public:
    Node(const Type value) : value(value), left(nullptr), right(nullptr) {}

    Node<Type> *getLeft() const {
        return left;
    }

    void setLeft(Node *left) {
        Node::left = left;
    }

    void setRight(Node *right) {
        Node::right = right;
    }

    void setValue(const Type value) {
        Node::value = value;
    }

    Type getValue() const {
        return value;
    }

    Node<Type> *getRight() const {
        return right;
    }

    bool isLeaf() {
        return left == nullptr && right == nullptr;
    }

};


#endif //CTREE_NODE_H
