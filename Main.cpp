#include <iostream>
#include <cstring>
#include "Tree.h"

/*
Implementing stack referencing code from: https://www.geeksforgeeks.org/implement-a-stack-using-singly-linked-list/
Implementing queue referencing code from: https://www.geeksforgeeks.org/queue-linked-list-implementation/
`Thanks to Jayden Huang for helping me with this project.
*/
using namespace std;
//Node Struct
struct Node{
int data = 0;
Node* next;
};
//Function Prototypes
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
void treePush(Tree* &newTree, Tree* &top);
void treePop(Tree* &newTree, Tree* &top);
Tree* treePeek(Tree* top);
//Print functions done with the help of Ehan Masud
void printInfix(Tree* Tree);
void printPostfix(Tree* Tree);
void printPrefix(Tree* Tree);


//Main Method
int main(){
    //Initialize the Stack and Queue
    Node* Stack = NULL;
    Node* queueFront = NULL;
    Node* queueRear = NULL;
    Tree* head = NULL;
    //Text Prompt
    cout << "Welcome to the Shunting Yard Algorithm! Please enter an equation in infix (normal) notation. Please don't use spaces to separate characters/numbers." << endl;
    char input[100];
    int num = 0;
    //Entering User input
    cin >> input;
    postfix(input,Stack,queueFront,queueRear);
    //While the queue's front and rear aren't NULL
    while(queueFront != NULL && queueRear != NULL){
    //If the input char is a digit
      if(isdigit(dequeue(queueFront,queueRear))){
    //Make a branch
            Tree* branch = new Tree(dequeue(queueFront,queueRear));
            treePush(head,branch);
        }
        else{
            //Make a branch
            Tree* branch = new Tree(dequeue(queueFront,queueRear));
            Tree* temp = NULL;
            //Create left and right branches from that, and push it to the tree.=
            treePop(head, temp);
            branch->setRight(temp);
            treePop(head,temp);
            branch->setLeft(temp);
            treePush(head, branch);
        }
        //Get rid of the end of the queue.
        deleteQueue(queueFront, queueRear);
        }
    //Printing out Postfix, Infix, and Prefix
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
//Push method
void push(char newData, Node* &top){
Node* temp = new Node();
temp->data = newData;
temp->next = top;
top = temp;
}
//Popping off the top of the stack
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
//Popps off the top of the stack and moves it to the queue
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
//Set order of operations for operands
int order(char operation){
if(operation == '+' || operation == '-'){
    return 1;
}
 else if(operation == '*' || operation == '/'){
    return 2;
}
 else if(operation == '^'){
    return 3;
}
 else if(operation == '('){
   return 5;
 }
else{
    return 0;
}
}
//Returns the value at the top of the stack
char peek(Node* top){
    if(top != NULL){
        return top->data;
    }
    else{
        return ' ';
    }
}
//Add values to the queue
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
//Returns the value at the front of the queue
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
//Deletes the rear of the queue
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
//Turn infix notation into postfix
void postfix(char* input, Node* &stack, Node* &queueFront, Node* &queueRear){
    int i = 0; 
    //Going through the length of the input
    while(i <= strlen(input)){
        char val = input[i];
        //If the characters is a number
        if(isdigit(val)){
            //Add it to the Queue
            enqueue(queueFront,queueRear,val);
        }
        //If the character is an operand
        else if(val == '^' || val == '*' || val == '+' || val == '-' || val == '/'){
        //While it isn't a parentheses or until an operand with a different order is read in
          while(peek(stack) != 'A' && order(peek(stack)) != 5 && order(peek(stack)) >= order(val) && order(val) != 3){
                //Pop it to the queue
                popTo(stack,queueFront, queueRear);
            }
            //Push it to the stack
             push(val, stack);
        }
        //If it is a parentheses
        else if(val == '('){
            //Push it to the stack
            push(val, stack);
        }
        //If it's an end parentheses
        else if(val == ')'){
            //Run through the in between
            bool runThrough = true;
            while(runThrough == true){
                if(peek(stack) == '('){
                    pop(stack);
                    runThrough = false; 
                }
                else{
                //Pop it to the stack
                popTo(stack,queueFront, queueRear);
                }
            }
        }
        else{
            //While the stack isn't NULL
            while(stack != NULL){
                //Pop it to the queue
                popTo(stack,queueFront, queueRear);
            }
        }
        i++;
    }
}
//Pushing a new branch to the tree
void treePush(Tree* &newTree, Tree* &top){
    Tree* temp =top;
    temp->setNext(newTree);
    newTree = temp;
}
//Popping a branch off the tree
void treePop(Tree* &newTree, Tree* &top){
    top = newTree;
    newTree = newTree->next;
}
//Getting the top of the tree
Tree* treePeek(Tree* top){
    if(top != NULL){
        return top;
    }
    else{
        return NULL;
    }
}

//Printing in infix notation
void printInfix(Tree* Tree){
    if(Tree != NULL){
        if(isdigit(treePeek(Tree)->getData()) == false){
            cout << "(";
        }
    printInfix(Tree->left);
    cout << Tree->getData(); 
    printInfix(Tree->right);
    if(isdigit(treePeek(Tree)->getData()) == false){
            cout << ")";
        }
    }
}
//Printing in postfix notation
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
//Printing in prefix notation
void printPrefix(Tree* Tree){
    cout << Tree->getData();
    if(Tree->getLeft() != NULL){
        printPrefix(Tree->getLeft());
    }
    if(Tree->getRight() != NULL){
        printPrefix(Tree->getRight());
    }
}  
