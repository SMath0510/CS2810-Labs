#include<bits/stdc++.h>
using namespace std;

/* Constructors */

class Cell{
    private:
        char *s;
    public:
        /* Default Constructor */
        Cell(){
            cout<<"Default Constructor"<<endl;
            s = new char;
            *s = 'a';
        }
        /* Overloaded Constructor */
        Cell(const char &x){ 
            cout<<"Overloaded constructor"<<endl;
            // using reference operator to save space
            // using const to avoid any change in the orignal string
            s = new char;
            *s = x;
        }
        /* Deep Copying using the Copy Constructor */
        Cell(const Cell &cpy){
            cout<<"Copy Constructor"<<endl;
            // Here s hasn't been initialized in the Default Constructor
            s = new char; // making a new pointer called s
            *s = *(cpy.s); // assigning the value at cpy.s to s
        }
        /* Making a Deep Copy Assignment Operator */
        Cell & operator=(const Cell &cpy){
            cout<<"Copy Assignment Constructor"<<endl;
            *s = *(cpy.s);
            // Here the s has been already initialized in the default constructor 
            return *this;
        }
        /* The Destructor */
        ~Cell(){
            cout<<"Destructor"<<endl;
            delete s;
        }
        /* Move Constructor */
        Cell (Cell && mv){
            cout<<"Move Constructor"<<endl;
            // initializing the s
            s = new char;
            s = mv.s;
            mv.s  = nullptr;
            // After this mv.s gets deleted by the destructor and s points to the orignal mv.s
        }
        Cell & operator=(Cell && mv){
            cout<<"Move Assignment Construtor"<<endl;
            // s is already initialized
            swap(s, mv.s);
            // After this mv.s is deleted which stores the orignal value of s
            return *this;
        }
        void print(){
            cout<<*(s)<<endl;
        }

};

int main(){
    Cell o1; // Calls the default constructor
    Cell o2('c'); // Calls the default overloaded constructor
    Cell o3 = o2;
    Cell o4; 
    o4 = o2;
    Cell o5 = Cell('x');
    Cell o6;
    o6 = Cell('p');
    o1.print();
    o2.print();
    o3.print();
    o4.print();
    o5.print();
    o6.print();
}