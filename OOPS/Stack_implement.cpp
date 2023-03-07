#include<bits/stdc++.h>
using namespace std;


struct Node{
    int value;
    Node * next;
    Node * prev;
};

class Stack{
    private:
    int size;
    Node * head;
    Node * tail;
    
    public:
    Stack(){
        size = 0;
        head = new Node;
        tail = new Node;
        head -> next = tail;
        tail -> prev = head;
    }
    void push(int N){
        Node * ptr = new Node;
        Node * last = new Node;
        last = tail -> prev;
        last -> next = ptr;
        ptr -> prev = last;
        ptr -> value = N;
        tail -> prev = ptr;
        ptr -> next = tail;
        size ++;
    }
    void pop(){
        Node *ptr = tail -> prev;
        ptr = ptr -> prev;
        ptr -> next = tail;
        tail -> prev = ptr;
        size --;
    }
    int top(){
        Node *ptr = tail -> prev;
        return ptr->value;
    }
    bool isEmpty(){
        return size == 0;
    }
};

int main(){
    Stack s;
    s.push(1);
    s.push(2);
    cout<<s.top()<<endl;
    s.pop();
    cout<<s.top()<<endl;
    s.pop();
    cout<<s.isEmpty()<<endl;
}