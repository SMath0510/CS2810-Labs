#include<bits/stdc++.h>
using namespace std;

class Residence{
    private:
        int numRooms;
        int numKitchens;
        int price;
    public:
        Residence(){
            numRooms = 2;
            numKitchens = 1;
            price = 10000;
        }
        void setData(){
            int R,K,P;
            cout<<"Enter details of the residence"<<endl;
            cin>>R>>K>>P;
            numRooms = R;
            numKitchens = K;
            price = P;
        }
        void getData(){
            cout<<"Details of the residence --"<<endl;
            cout<<" Rooms : "<<numRooms<<endl;
            cout<<" Kitchens : "<<numKitchens<<endl;
            cout<<" Price : "<<price<<endl;
        }
};

class Flat : public Residence{
    private:
        float area;
        bool attached_washroom;
    
    public:
        Flat(){
            area = 100;
            attached_washroom = false;
        }
        void setData(){
            /* Overriding on the parent class function*/
            Residence :: setData();
            cout<<"Enter the details of the flat"<<endl;
            int A;
            bool W;
            cin>>A>>W;
            area = A;
            attached_washroom = W;
        }
        void getData(){
            /* If not overrided then the derived class function is only called*/
            // Residence :: getData();
            cout<<"The details of the flat "<<endl;
            cout<<"The area is "<<area<<endl;
            cout<<"The attached bathroom is "<<attached_washroom<<endl;
        }
};

/* Normal Class with a virtual function, we can initialize the objects of this class */
class Base{
    public:
        /* This makes sure that the function is overwritten by the derived class functions*/
        virtual void greet(){
            cout<<"We are in the Base Virtual"<<endl;
        }
        virtual void greet(string s){
            cout<<"Hello "<<s<<endl;
        }
};

/* Abstract Base Class : Can't initialize an object of this class, only pointers */
class AbsBase{
    public:
        virtual void greet() = 0;
};

class Derv1 : public Base, AbsBase{
    public:
        // using Base :: greet; // Bringing all the overloaded versions of this function
        void greet(){
            cout<<"We are in the Derv 1 class"<<endl;
        }
};

class Derv2 : public Base, AbsBase{
    public:
        void greet(){
            cout<<"We are in the Derv 2 class"<<endl;
        }
};

int main(){
    Residence r1;
    // r1.setData();
    Flat f1;
    // f1.setData();
    Base * o1;
    Derv1 d1;
    Derv2 d2;
    o1 = &d1;
    o1->greet("Shaun");
    o1 = &d2;
    o1 ->greet();

    /* Dynamic Binding */
    int a = 1, b = 2;
    if(a > b){
        o1 = &d1;
    }
    else{
        o1 = &d2;
    }
    o1->greet();
}