#include<bits/stdc++.h>
using namespace std;


/* Inheritance */

/* Parent Class */
class Parent{
    private :
        int pvt;
    protected :
        int prot;
    public:
        int pub; 
        /* Creating a constuctor */
        Parent(){
            pvt = 0;
            prot = 1;
            pub = 2;
        }
        /* Overloading a constructor */
        Parent(int a, int b = 1, int c = 1){
            pvt = a;
            prot = b;
            pub = c;
        }
        void print(){
            cout<<"In the main (parent) class"<<endl;
            cout<<pvt<<" "; 
            cout<<prot<<" ";
            cout<<pub<<" ";
            cout<<endl;
        }
};

/* Publically inherited Child*/
class ChildPub : public Parent{

    public:
        void print(){
            cout<<"In the child class"<<endl;
            // cout<<pvt<<" ";  : Can't access private elements
            cout<<prot<<" ";
            cout<<pub<<" ";
            cout<<endl;
        }
};

/* Third Party Class */
class Rest{
    public:
        void print(){
            cout<<"In a non - child class"<<endl;
            // cout<<pvt<<" ";  : Can't access private elements
            // cout<<prot<<" "; : Can't access protected elements
            Parent o1;
            cout<<o1.pub<<" ";
            cout<<endl;
        }
};

/* Seperating the interface and implementation */
class Demo{
    private :
        int a;
    public:
        void setData(int x);
        int getData();
};

void Demo :: setData(int x){
    a = x;
}

int Demo :: getData(){
    return a;
}

int main(){
    /* Creating the objects of the classes */
    Parent c1;
    ChildPub c2;
    Rest c3; 
    Demo d1;
    /* Creating the pointer of the class Parent */
    Parent *p1 = new Parent(3,3,3);
    c1.print();
    c2.print();
    c3.print();
    p1->print();
    d1.setData(5);
    cout<<d1.getData()<<endl;
}