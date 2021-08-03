#include <iostream>
#include <ctime>
#include "TreeIterator.h"

using namespace std;

const int NUM_VALUES = 17;
const int MAX_VALUE = 50;

void buildTree(Tree<int> &);

void printTree(Tree<int>);

void balanceTree(Tree<int> *);

void searchTree(Tree<int>);

void removeNodes(Tree<int>);

void tryIterator(Tree<int>);

int main() {
    int value;
    Tree<int> tree = Tree<int>();
    srand((unsigned) time(0));
    cout << "Hello, World of binary trees!" << endl;
    buildTree(tree);
    printTree(tree);
    tryIterator(tree);
    balanceTree(&tree);
    printTree(tree);
    searchTree(tree);
    tryIterator(tree);
    removeNodes(tree);
    return 0;
}

void buildTree(Tree<int> &tree) {
    int value;
    for (int i = 0; i < NUM_VALUES; i++) {
        value = (rand() % MAX_VALUE) + 1;
        //value = i;
        cout << value << ", ";
        tree.insert(value);
    }
    cout << endl;
}

void printTree(Tree<int> tree) {
    cout << "Inorder .: ";
    tree.print(typePrint::InOrder);
    cout << "Preorder : ";
    tree.print(typePrint::PreOrder);
    cout << "Postorder: ";
    tree.print(typePrint::PostOrder);
    cout << "2D: ";
    tree.print(typePrint::in2D);
}

void balanceTree(Tree<int> *tree) {
    cout << "*** Balancing tree..." << endl;
    tree->balance();
}

void searchTree(Tree<int> tree) {
    int value;
    // Search for a random value
    value = (rand() % MAX_VALUE) + 1;
    cout << "Element " << value << (tree.search(value) ? " was found" : " was NOT found")
         << " in tree" << endl;
}

void removeNodes(Tree<int> tree) {
    int nodes[] = {0, 1, 3, 2, 4};
    cout << "Begin destruction..." << endl;
    for (int i = 0; i < 5; i++) {
        cout << "removing " << nodes[i] << endl;
        tree.remove(nodes[i]);
        tree.print(typePrint::InOrder);
    }
}

void tryIterator(Tree<int> tree) {
    TreeIterator<int> iterator = TreeIterator<int>(tree);
    Node<int> *next;
    iterator.begin();
    cout << "Begin iteration" << endl;
    while ((next = iterator.next())) {
        cout << "next value is: " << next->getValue() << endl;
    }
    cout << "And again..." << endl;
    iterator.begin();
    while ((next = iterator.next())) {
        cout << "next value is again: " << next->getValue() << endl;
    }

}
