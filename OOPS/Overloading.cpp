#include<bits/stdc++.h>
using namespace std;

/* Constructors */

class Cell{
    private:
        int *n;
    public:
        friend ostream & operator<< (ostream & out, Cell &x);
        /* Default Constructor */
        Cell(){
            // cout<<"Default Constructor"<<endl;
            n = new int;
            *n = 1;
        }
        /* Overloaded Constructor */
        Cell(const char &x){ 
            // cout<<"Overloaded constructor"<<endl;
            // using reference operator to save space
            // using const to avoid any change in the orignal string
            n = new int;
            *n = x;
        }
        /* Overloading the unary operator pre-increment*/
        Cell & operator++(){
            ++(*n);
            return *this;
        }
        /* Overloading the unary operator post-increment*/
        Cell & operator++(int){
            (*n)++;
            return *this;
        }
        /* Overloading the comparator >*/
        bool operator>(Cell & other){
            // cout<< *n << " " << other.read()<<endl;
            return *n > other.read();
        }
        /* Overloading the Binary Operator +*/
        Cell operator+(Cell & other){
            Cell ret(*n + other.read());
            return ret;
        }
        /* Overloading the typecasting operator*/
        operator int() const{
            return *n;
        }
        int read(){
            return *n;
        }
        void write(int &value){
            *n = value;
        }
        void print(){
            cout<<*n<<endl;
        }
        
};

/* Defining the cin and cout for the operators*/
ostream & operator<< (ostream &out, Cell &x){
    return out<< *(x.n);
}
istream & operator>> (istream &in, Cell &x){
    int n;
    in>>n;
    x.write(n);
    return in;
}

int main(){
    Cell o1(10);
    o1.print();
    o1++;
    o1.print();
    ++o1;
    o1.print();
    Cell o2(9);
    if(o1 > o2){
        cout<<"Greater"<<endl;
    }
    Cell o3;
    cin>>o3;
    cout<<o3<<endl;
    cout<<(int)o1<<endl;
    return 0;
}