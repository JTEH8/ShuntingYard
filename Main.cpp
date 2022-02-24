#include <iostream>
#include <cstring>
#include "Tree.h"

/*
Implementing stack referencing code from: https://www.geeksforgeeks.org/implement-a-stack-using-singly-linked-list/
Implementing queue referencing code from: https://www.geeksforgeeks.org/queue-linked-list-implementation/
Thanks to Jayden Huang for helping me with this project.
*/
using namespace std;

Node* pop();
void push(char newData, Node* &top);
void peek(Node* &top);
void display(Node* &top);
void enqueue(Node* &front, Node* &rear, char newData);
void dequeue(Node* &tempFront, Node* &rear);

struct Node{
int data = 0;
Node* next;
};

int main(){
    cout << "Welcome to the Shunting Yard Algorithm! Please enter an equation in infix (normal) notation. Please don't use spaces to separate characters/numbers." << endl;
    char input[100];
    cin >> input;
    //Initialize the Stack and Queue
    Node* Stack = NULL;
    Node* QueueFront = NULL;
    Node* QueueBack = NULL;
    cout << "Here is your expression in postfix: ";
    cout << "Do you want to output the expression as infix, prefix, or postfix?" << endl;
    Node* head1;
    Node* head2;
}

void push(char newData, Node* &top){
Node* temp = new Node();
temp->data = newData;
temp->next = top;
top = temp;
}

int peek(){
    if(isEmpty != NULL){
        return top->data;
    }
    else{
        exit(1);
    }
}