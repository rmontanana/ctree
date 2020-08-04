//
// Created by Ricardo Montañana on 29/07/2020.
//

#include <iostream>
#include <string>

template<class Type>
Tree<Type>::Tree(const Type value) {
    root = insert(value);
}

template<class Type>
Node<Type> *Tree<Type>::insertValue(Node<Type> *node, const Type value) {
    if (node == nullptr) {
        return new Node(value);
    }
    if (value < node->getValue()) {
        node->setLeft(insertValue(node->getLeft(), value));
    } else if (value > node->getValue()) {
        node->setRight(insertValue(node->getRight(), value));
    } else {
        //if value already exists in tree return itself
        return node;
    }
}

template<class Type>
Node<Type> *Tree<Type>::insert(const Type value) {
    return root = insertValue(root, value);
}

template<class Type>
void Tree<Type>::preOrder(const Node<Type> *node) {
    std::cout << node->getValue() << ", ";
    if (node->getLeft() != nullptr) preOrder(node->getLeft());
    if (node->getRight() != nullptr) preOrder(node->getRight());
}

template<class Type>
void Tree<Type>::postOrder(const Node<Type> *node) {
    if (node->getLeft() != nullptr) postOrder(node->getLeft());
    if (node->getRight() != nullptr) postOrder(node->getRight());
    std::cout << node->getValue() << ", ";
}

template<class Type>
void Tree<Type>::inOrder(const Node<Type> *node) {
    if (node->getLeft() != nullptr) inOrder(node->getLeft());
    std::cout << node->getValue() << ", ";
    if (node->getRight() != nullptr) inOrder(node->getRight());
}

template<class Type>
void Tree<Type>::print2D(const Node<Type> *node, int spaces) {
    if (node == nullptr)
        return;
    spaces += 4;
    std::cout << std::endl << std::string(spaces - 4, '-') << node->getValue();
    print2D(node->getRight(), spaces);
    print2D(node->getLeft(), spaces);
}

template<class Type>
void Tree<Type>::print(enum typePrint type) {
    switch (type) {
        case typePrint::InOrder:
            inOrder(root);
            break;
        case typePrint::PreOrder:
            preOrder(root);
            break;
        case typePrint::PostOrder:
            postOrder(root);
            break;
        case typePrint::in2D:
            print2D(root, 0);
            break;
    }
    std::cout << std::endl;
}

template<class Type>
void Tree<Type>::balance() {
    std::vector<Type> nodes;
    storeList(root, nodes);
    erase(root);
    root = rebuild(nodes, 0, nodes.size() - 1);
}

template<class Type>
Node<Type> *Tree<Type>::rebuild(std::vector<Type> &nodes, int start, int end) {
    if (start > end)
        return nullptr;
    int mid = (start + end) / 2;
    Type nodeValue = nodes[mid];
    Node<Type> *node = new Node(nodeValue);
    node->setLeft(rebuild(nodes, start, mid - 1));
    node->setRight(rebuild(nodes, mid + 1, end));
    return node;
}

template<class Type>
void Tree<Type>::erase(Node<Type> *node) {
    if (node == nullptr)
        return;
    erase(node->getLeft());
    erase(node->getRight());
    delete node;
}

template<class Type>
void Tree<Type>::storeList(Node<Type> *node, std::vector<Type> &list) {
    if (node == nullptr) {
        return;
    }
    // create list in inorder (sorted values)
    storeList(node->getLeft(), list);
    list.push_back(node->getValue());
    storeList(node->getRight(), list);
}

template<class Type>
bool Tree<Type>::search(const Type value) {
    return searchValue(root, value) != nullptr;
}

template<class Type>
Node<Type> *Tree<Type>::searchValue(Node<Type> *node, const Type value) {
    if (node == nullptr || node->getValue() == value) {
        return node;
    }
    if (value > node->getValue()) {
        return searchValue(node->getRight(), value);
    }
    return searchValue(node->getLeft(), value);
}

template<class Type>
void Tree<Type>::searchValueAndFather(const Type value, Node<Type> **node, Node<Type> **father) {
    Node<Type> *current = getRoot(), *relative = nullptr;
    bool exitLoop = current == nullptr || current->getValue() == value;
    while (!exitLoop) {
        relative = current;
        current = value > current->getValue() ? current->getRight() : current->getLeft();
        exitLoop = current == nullptr || current->getValue() == value;
    }
    *node = current;
    *father = relative;
}

template<class Type>
bool Tree<Type>::remove(const Type value) {
    Node<Type> *node, *father;
    searchValueAndFather(value, &node, &father);
    if (node == nullptr)
        // value not found
        return false;
    if (node->isLeaf()) {
        //Case 1 Node has no children
        if (node == root) {
            root = nullptr;
        } else if (father->getLeft() == node)
            father->setLeft(nullptr);
        else
            father->setRight(nullptr);
        delete (node);
        return true;
    } else if (node->getRight() && node->getLeft()) {
        //Case 2 Node has two children
        Type leastValue = getLeastValue(node->getRight())->getValue();
        remove(leastValue);
        node->setValue(leastValue);
        return true;
    } else {
        //Case 3 Node has only one child
        if (father == nullptr) {
            // removing root
            root = node->getLeft() ? node->getLeft() : node->getRight();
        } else if (father->getLeft() == node) {
            father->setLeft(node->getLeft() ? node->getLeft() : node->getRight());
        } else {
            father->setRight(node->getLeft() ? node->getLeft() : node->getRight());
        }
        delete (node);
        return true;
    }
}

template<class Type>
Node<Type> *Tree<Type>::succesor(Node<Type> *node) {
    /*
     *
     *      Input: node, root // node is the node whose Inorder successor is needed.
     *      Output: succ // succ is Inorder successor of node.
     *      If right subtree of node is not NULL, then succ lies in right subtree. Do the following.
     *      Go to right subtree and return the node with minimum key value in the right subtree.
     *      If right subtree of node is NULL, then start from the root and use search like technique. Do the following.
     *      Travel down the tree, if a node’s data is greater than root’s data then go right side, otherwise, go to left side.
     *
     */
    if (node->getRight()) {
        return getLeastValue(node->getRight());
    }
    Node<Type> *p = getRoot(), *succesor = nullptr;
    while (p != nullptr) {
        if (node->getValue() < p->getValue()) {
            succesor = p;
            p = p->getLeft();
        } else if (node->getValue() > p->getValue())
            p = p->getRight();
        else
            // exit while
            p = nullptr;
    }
    return succesor;
}

template<class Type>
Node<Type> *Tree<Type>::getLeastValue(Node<Type> *node) {
    if (node == nullptr) {
        return nullptr;
    }
    while (node->getLeft() != nullptr)
        node = node->getLeft();
    return node;
}
