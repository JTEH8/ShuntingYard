//This was done with reference tO: https://www.geeksforgeeks.org/binary-tree-set-1-introduction/
#include <iostream>
#include <cstring>
#include "Tree.h"

using namespace std;
//Constructors
Tree::Tree(char newValue){
    right = NULL;
    left = NULL;
    next = NULL;
    data = newValue;
}
//Setting methods
void Tree::setRight(Tree* newRight){
    right = newRight;
}

void Tree::setLeft(Tree* newLeft){
    left = newLeft;
}

void Tree::setNext(Tree* newNext){
    next = newNext;
}
//Get methods
Tree* Tree::getRight(){
    return right;
}

char Tree::getData(){
    return data;
}

Tree* Tree::getLeft(){
    return left;
}

Tree* Tree::getNext(){
    return next;
}
//Destructor
Tree::~Tree(){
    
}
