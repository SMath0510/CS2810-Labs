#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class IntCell {
    public:
        IntCell(int initialValue=0) {
            storedValue = new int;
            *storedValue = initialValue;
        }
  		/* You may need to define copy/move constructors and assignment operators*/
        IntCell(const IntCell &rhs){
            storedValue = new int;
            *storedValue = *(rhs.storedValue);
        }
        IntCell & operator=(IntCell &rhs){
            *storedValue = *(rhs.storedValue);
            return *this;
        }
        IntCell (IntCell &&rhs){
            storedValue = rhs.storedValue;
            rhs.storedValue = nullptr;
        }
        IntCell & operator=(IntCell && rhs){
            swap(rhs.storedValue, storedValue);
            return *this;
        }
        int read() {return *storedValue;}
        void write(int x) {*storedValue = x;}
    private:
        int * storedValue;
};

class Collection {
  private:
  	IntCell * arr;
  	int size;
    int capacity;
  	/* You may need to define more members */
  
  public:
  	// Constructor which initializes arr with size inpSize

  	Collection(int inpSize=10) : size(inpSize)
    {
        arr = new IntCell[size];
        capacity = 0;
    }
  
  	~Collection()
    {
      	delete arr;
    }
      
    //You may need to define copy,move constructors, and copy/move assignment operators
    Collection(const Collection &rhs){
        arr = new IntCell[rhs.size];
        size = rhs.size;
        capacity = rhs.capacity;
        for(int i = 0; i<rhs.size; i++){
            arr[i] = rhs.arr[i];
        }
    }
    Collection & operator= (const Collection &rhs){
        delete arr;
        arr = new IntCell[rhs.size];
        size = rhs.size;
        capacity = rhs.capacity;
        for(int i = 0; i<rhs.size; i++){
            arr[i] = rhs.arr[i];
        }
        return *this;
    }
    Collection(Collection &&rhs){
        arr = rhs.arr;
        size = rhs.size;
        capacity = rhs.capacity;
        rhs.arr = nullptr;
    }
    Collection & operator= (Collection &&rhs){
        swap(arr, rhs.arr);
        size = rhs.size;
        capacity = rhs.capacity;
        return *this;
    }
      
    //Define public functions isEmpty, makeEmpty, insert, remove, contains
    bool isEmpty(){
        return capacity==0;
    }
    void makeEmpty(){
        arr = nullptr;
        arr = new IntCell[10];
        size = 10;
        capacity = 0;
    }
    void insert(IntCell &cell){
        // capacity++;
        if(size == capacity){
            size*=2;
            IntCell * tmp = new IntCell[size];
            for(int i = 0; i<(size/2); i++){
                tmp[i] = arr[i];
            }
            arr = tmp;
        }
        arr[capacity] = cell;
        // cout<<capacity<<endl;
        capacity++;
    }
    void remove(IntCell &cell){
        int tmpcapacity = 0;
        IntCell * tmp = new IntCell[size];
        int ptr = 0;
        for(int i = 0; i<capacity; i++){
            if(arr[i].read() != cell.read()){
                tmp[ptr] = arr[i];
                ptr++;
                tmpcapacity++;
            }
        }
        capacity = tmpcapacity;
        arr = tmp;
        // printAll();
    }
    bool contains(IntCell &cell){
        for(int i = 0; i<size; i++){
            if(arr[i].read() == cell.read()){
                return true;
            }
        }
        return false;
    }
    // void printAll(){
    //     for(int i = 0; i<capacity; i++){
    //         cout<<arr[i].read()<<" ";
    //     }
    //     cout<<endl;
    //     cout<<capacity<<endl;
    // }
    //Use call-by-constant-reference wherever applicable.
};


/*DO NOT MAKE ANY CHANGES TO THE CODE BELOW*/

int main() {
  int N;
  cin >> N;
  Collection c;
  int command;
  for (int i = 0; i < N; i++)
  {
    cin >> command;
    switch (command)
    {
      case 1 /*"initialize"*/:
        {
            int inpSize;
            cin >> inpSize;
            Collection c2(inpSize);
            c = c2;
        }
        break;

       case 2 /*"initializeWith"*/:
       {
            int size2;
            cin >> size2;
            Collection c2(size2);
            for (int j = 0; j < size2; j++)
            {
              int elem;
              cin >> elem;
              IntCell elemCell(elem);
              c2.insert(elemCell);
            }
            Collection c3 = c2;
            c = c3;
            break;
       }
      case 3 /*"insert"*/:
        {
            int elem;
            cin >> elem;
            IntCell elemCell(elem);
            c.insert(elemCell);
            break;
        }
      case 4 /*"remove"*/:
       {
            int elem;
            cin >> elem;
            IntCell elemCell(elem);
            c.remove(elemCell);
            break;
       } 
      case 5 /*"copy"*/:
       {
            int size2;
            cin >> size2;
            Collection c2(size2);
            for (int j = 0; j < size2; j++)
            {
              int elem;
              cin >> elem;
              IntCell elemCell(elem);
              c2.insert(elemCell);
            }
            c = c2;
            break;
       }
      case 6 /*"isEmpty"*/:
      {
            if (c.isEmpty())
            cout << "Collection is empty" << endl;
            else
            cout << "Collection is not empty" << endl;
            break;
      }
      case 7 /*"makeEmpty"*/:
            c.makeEmpty();
            break;
      case 8 /*"contains"*/:
      {
            int elem;
            cin >> elem;
            IntCell elemCell(elem);
            if (c.contains(elemCell))
            cout << "Collection contains " << elem << endl;
            else
            cout << "Collection does not contain " << elem << endl;
            break;
      }
        case 9 :{
            // c.printAll();
            // break;
        }
      default:
            cout << "Invalid command!" << endl;
    }
  }
  return 0;
}