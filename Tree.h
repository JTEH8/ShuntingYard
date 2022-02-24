#ifndef TREE_H
#define TREE_H
#include <cstring>

class Tree{
int data;
Tree* left;
Tree* right;
    Tree(int val){
    data = val;
    left = NULL;
    right = NULL;
    }
void createTree();
};

#endif