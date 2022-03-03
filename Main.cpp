#include <iostream>
#include <cstring>
#include "Tree.h"

/*
Implementing stack referencing code from: https://www.geeksforgeeks.org/implement-a-stack-using-singly-linked-list/
Implementing queue referencing code from: https://www.geeksforgeeks.org/queue-linked-list-implementation/
Thanks to Jayden Huang for helping me with this project.
*/
using namespace std;

struct Node{
int data = 0;
Node* next;
};

void postfix(char* input, Node* &stack, Node* &queueFront, Node* &queueRear);
int order(char operation);
void pop(Node* &top);
void popTo(Node* &top, Node* &front, Node* &rear);
void push(char newData, Node* &top);
char peek(Node* top);
//void enqueue(Node* &front, Node* &rear, char newData);
char dequeue(Node* &front, Node* &rear);
void deleteQueue(Node* &front, Node* &rear);
void enqueue(Node* &front, Node* &rear, char newData);
void treePush(Tree* newTree, Tree* &top);
void treePop(Tree* &newTree, Tree* &top);
Tree* treePeek(Tree* top);
//Print functions done with the help of Ehan Masud
void printInfix(Tree* Tree);
void printPostfix(Tree* Tree);
void printPrefix(Tree* Tree);



int main(){
    //Initialize the Stack and Queue
    Node* Stack = NULL;
    Node* queueFront = NULL;
    Node* queueRear = NULL;
    Tree* head = NULL;
    cout << "Welcome to the Shunting Yard Algorithm! Please enter an equation in infix (normal) notation. Please don't use spaces to separate characters/numbers." << endl;
    char input[100];
    char temp[100];
    int num = 0;
    cin>>input;
    postfix(input,Stack,queueFront,queueRear);
    while(queueFront != NULL && queueRear != NULL){
        if(isdigit(dequeue(queueFront,queueRear))){
            Tree* branch = new Tree(dequeue(queueFront,queueRear));
            treePush(head,branch);
        }
        else{
            Tree* branch = new Tree(dequeue(queueFront,queueRear));
            Tree* temp = NULL;
            treePop(head, temp);
            branch->setRight(temp);
            treePop(head,temp);
            branch->setLeft(temp);
            treePush(head, branch);
        }
        deleteQueue(queueFront, queueRear);
        }
    printPostfix(head);
    cout << "Infix: ";
    printInfix(head);
    cout << endl;
    cout << "Postfix: ";
    printPostfix(head);
    cout << endl;
    cout << "Prefix: ";
    printPrefix(head);
    exit(0);
}

void push(char newData, Node* &top){
Node* temp = new Node();
temp->data = newData;
temp->next = top;
top = temp;
}

void pop(Node* &top){
if(top == NULL){
    cout << "The stack is empty!" << endl;
    return;    
}
else{
    Node* temp = top;
    top = top->next;
    delete temp;

}
}

void popTo(Node* &top, Node* &front, Node* &rear){
    if(top == NULL){
        return;  
    }
    
    else{
        Node* temp = top;
        enqueue(front, rear, top->data);
        top = top->next;
        delete temp;
    }
}

int order(char operation){
if(operation == '+' || operation == '-'){
    return 1;
}
if(operation == '*' || operation == '/'){
    return 2;
}
if(operation == '^'){
    return 3;
}
else{
    return 0;
}
}

char peek(Node* top){
    if(top != NULL){
        return top->data;
    }
    else{
        return ' ';
    }
}

void enqueue(Node* &front, Node* &rear, char newData){
    if(front == NULL && rear == NULL){
        Node* temp = new Node();
        temp->next = NULL;
        temp->data = newData;
        front = temp;
        rear = temp;
        temp->next = NULL;
    }
    else{
        Node* temp = new Node();
        temp->data = newData;
        temp->next = front;
        front = temp;
    }
}

char dequeue(Node* &tempFront, Node* &rear){
    if(rear == NULL){
        return 'A';
    }
    else if(tempFront == rear){
        Node* tempRear = rear;
        return tempRear->data;
        delete tempRear;
        tempFront = NULL;
        rear = NULL;
    }
    else if(tempFront->next == rear){
        Node* tempRear = rear;
        return tempRear->data;
        rear = tempFront;
        delete tempRear;
    }
    else{
        return dequeue(tempFront->next, rear);
}
}

void deleteQueue(Node* &front, Node* &rear){
    if(rear == NULL){
        return;
    }
    else if(front == rear){
        Node* tempRear = rear;
        delete tempRear;
        front = NULL;
        rear = NULL;
    }
    else if(front->next == rear){
        Node* tempRear = rear;
        rear = front;
        delete tempRear;
    }
    else{
        deleteQueue(front->next, rear);
    }
}

void postfix(char* input, Node* &stack, Node* &queueFront, Node* &queueRear){
    int i = 0; 
    while(i <= strlen(input)){
        char val = input[i];
        //If the characters is a number
        if(isdigit(val)){
            //Add it to the Queue
            enqueue(queueFront,queueRear,val);
        }
        else if(val == '^' || val == '*' || val == '+' || val == '-' || val == '/'){
          while(peek(stack) != 'A' && order(peek(stack)) != 5 && order(peek(stack)) >= order(val) && order(val) != 3){
                popTo(stack,queueFront, queueRear);
            }
             push(val, stack);
        }
        else if(val == '('){
            push(val, stack);
        }
        else if(val == ')'){
            bool runThrough = true;
            while(runThrough == true){
                if(peek(stack) == '('){
                    pop(stack);
                    runThrough = false; 
                }
                else{
                popTo(stack,queueFront, queueRear);
                }
            }
        }
        else{
            while(stack != NULL){
                popTo(stack,queueFront, queueRear);
            }
        }
        i++;
    }
}

void treePush(Tree* newTree, Tree* &top){
    Tree* temp =top;
    temp->setNext(newTree);
    newTree = temp;
}
void treePop(Tree* &newTree, Tree* &top){
    top = newTree;
    newTree = newTree->next;
}

Tree* treePeek(Tree* top){
    if(top != NULL){
        return top;
    }
    else{
        return NULL;
    }
}



void printInfix(Tree* Tree){
    if(Tree != NULL){
        if(isdigit(treePeek(Tree)->getData()) == false){
            cout << "(";
        }
    printInfix(Tree->left);
    cout << Tree->getData(); 
    printInfix(Tree->right);
    if(isdigit(treePeek(Tree)->getData()) == false){
            cout << "(";
        }
    }
}

void printPostfix(Tree* Tree){
    if(Tree == NULL){
        return;
    }
    printPostfix(Tree->left);
    printPostfix(Tree->right);
    cout << Tree->getData();  
    /*
    if(Tree->getLeft() != NULL){
        printInfix(Tree->getLeft());
    }
    if(Tree->getRight() != NULL){
        printInfix(Tree->getRight());
    }
    cout << Tree->getData();
    */
}  

void printPrefix(Tree* Tree){
    cout << Tree->getData();
    if(Tree->getLeft() != NULL){
        printInfix(Tree->getLeft());
    }
    if(Tree->getRight() != NULL){
        printInfix(Tree->getRight());
    }
}  