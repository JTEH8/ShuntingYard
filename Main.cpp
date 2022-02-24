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
void push(char newData, Node* &top);
void peek(Node* &top);
void display(Node* &top);
void enqueue(Node* &front, Node* &rear, char newData);
void dequeue(Node* &tempFront, Node* &rear);



int main(){
    cout << "Welcome to the Shunting Yard Algorithm! Please enter an equation in infix (normal) notation. Please don't use spaces to separate characters/numbers." << endl;
    char input[];
    cin >> input;
    //Initialize the Stack and   Queue
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

void pop(Node* &top){
if(top == NULL){
    break;    
}
else{
    Node* temp = top;
    top = top->next;
    delete temp;

}
}

int order(char operation){
if(prio == '+' || prio == '-'){
    return 1;
}
if(prio == '*' || prio == '/'){
    return 2;
}
if(prio == '^'){
    return 3;
}
else{
    return 0;
}
}

void display(Node* &top){
    if(top == NULL){
        break;
    }
    else{
        Node* temp = top;
        while(temp != NULL){
            cout << temp->data << endl;
            temp = temp->next;
        }
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

void dequeue(Node* &tempFront, Node* &rear){
    if(rear == NULL){
        break;
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
    for(int i = 0; i < input.size(); i++){
        char c = input[i];
        char output[100];
        if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')){
            output += c;
        }
        else if(c == '('){
            push('(', stack);
        }
        
    }
}