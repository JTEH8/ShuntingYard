#ifndef TREE_H
#define TREE_H
#include <cstring>
//Help for Tree.h and Tree.cpp from Nihal Parthasarathy

class Tree{
public:
    char data;
    Tree* left;
    Tree* right;
    Tree* next;
    Tree(char newVal);
    ~Tree();
void setValue(char newVal);
void setLeft(Tree* newLeft);
void setRight(Tree* newRight);
void setNext(Tree* newNext);
Tree* getRight();
Tree* getLeft();
Tree* getNext();
};

#endif