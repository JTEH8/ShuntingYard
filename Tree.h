//Header guard
#ifndef TREE_H
#define TREE_H
#include <cstring>
//Help for Tree.h and Tree.cpp from Nihal Parthasarathy

//Tree Clas
class Tree{
public:
    //Vairables
    char data;
    Tree* left;
    Tree* right;
    Tree* next;
    //Constructor and Destructor
    Tree(char newVal);
    ~Tree();
//Function prototypes
void setValue(char newVal);
void setLeft(Tree* newLeft);
void setRight(Tree* newRight);
void setNext(Tree* newNext);
char getData();
Tree* getRight();
Tree* getLeft();
Tree* getNext();
};

#endif