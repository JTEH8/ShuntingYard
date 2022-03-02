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

void postfix(char* input, Node* stack, Node* queueFront, Node* queueRear);
int order(char operation);
void pop(Node* &top);
void popTo(Node* &top, Node* &front, Node* &rear);
void push(char newData, Node* &top);
char peek(Node* top);
//void enqueue(Node* &front, Node* &rear, char newData);
void dequeue(Node* &tempFront, Node* &rear);
void newTree(char c, Node* &head, Tree* &tree);
//Print functions done with the help of Ehan Masud
void printInfix(Tree* Tree);
void printPostfix(Tree* Tree);
void printPrefix(Tree* Tree);
void printTree(Tree* Tree);



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
    cin.getline(input,100);
    //Removing spaces from input (From Nihal Parthasarathy)
    for (int i = 0; i <strlen(input); i++) {
    if (input[i] != ' ') {
      temp[num] = input[i];
      num++;
    }
  }
    postfix(input,Stack,queueFront,queueRear);
    //Creating the Tree (From Nihal Parthasarathy)
    while(queueFront != NULL){
        char c = peek(queueFront);
        if(isdigit(c)){
            push(c, Stack));
            queueFront = queueFront->next;
        }
        else if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^'){
            newTree(c,Stack, head);
            push(c, Stack));
            queueFront = queueFront->next;
        }
    }
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
        cout << "The stack is empty!" << endl;
        return;  
    }
    else if(top->data == '('){
    Node* temp = top;
    top = top->next;
    delete temp;
    cout << "Here's the top of the stack's data: ";
    cout << top->data << endl;
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
/*
void display(Node* &top){
    if(top == NULL){
        return;
    }
    else{
        Node* temp = top;
        while(temp != NULL){
            cout << temp->data << endl;
            temp = temp->next;
        }
    }
}
*/
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

void dequeue(Node* &tempFront, Node* &rear){
    if(rear == NULL){
        return;
    }
    else if(tempFront == rear){
        Node* tempRear = rear;
        cout << tempRear->data << endl;
        delete tempRear;
        tempFront = NULL;
        rear = NULL;
    }
    else if(tempFront->next == rear){
        Node* tempRear = rear;
        cout << tempRear->data << endl;
        rear = tempFront;
        delete tempRear;
    }
    else{
        dequeue(tempFront->next, rear);
}
}
void postfix(char* input, Node* stack, Node* queueFront, Node* queueRear){
    int i = 0; 
    while(i <= strlen(input)){
        char val = input[i];
        //If the characters is a number
        if(isdigit(val)){
            //Add it to the Queue
            enqueue(queueFront,queueRear,val);
        }
        else if(val == '^' || val == '*' || val == '+' || val == '-' || val == '/'){
            if(order(peek(stack)) > order(val) && order(peek(stack)) != 5){
                popTo(stack,queueFront, queueRear);
                push(val, stack);
            }
        }
        else if(val == '('){
            push('(', stack);
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

void printInfix(Tree* Tree){
    if(Tree->getLeft() != NULL){
        printInfix(Tree->getLeft());
    }
    cout << Tree->getData();
    if(Tree->getRight() != NULL){
        printInfix(Tree->getRight());
    }
}

void printPostfix(Tree* Tree){
    if(Tree->getLeft() != NULL){
        printInfix(Tree->getLeft());
    }
    if(Tree->getRight() != NULL){
        printInfix(Tree->getRight());
    }
    cout << Tree->getData();
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