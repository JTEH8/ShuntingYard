//This was done with reference tO: https://www.geeksforgeeks.org/binary-tree-set-1-introduction/
#include <iostream>
#include <cstring>
#include "Tree.h"

using namespace std;

Tree::Tree(char newValue){
    right = NULL;
    left = NULL;
    next = NULL;
    data = newValue;
}

void Tree::setRight(Tree* newRight){
    right = newRight;
}

void Tree::setLeft(Tree* newLeft){
    left = newLeft;
}

void Tree::setNext(Tree* newNext){
    next = newNext;
}

Tree* Tree::getRight(){
    return right;
}

Tree* Tree::getLeft(){
    return left;
}

Tree* Tree::getNext(){
    return next;
}

Tree::~Tree(){
    
}
