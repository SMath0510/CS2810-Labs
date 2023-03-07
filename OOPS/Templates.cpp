#include<bits/stdc++.h>
using namespace std;

/* A template function */
template<class Object>
Object sum(Object o1, Object o2){
    return o1 + o2;
}

template<class Object>
class List{
    private:
        struct Node{
            Object data;
            Node * next;
            Node * prev;
            
            Node(const Object &d = Object(), Node *p = nullptr, Node *n = nullptr ){
                data = d;
                next = n;
                prev = p;
            }
        };
        Node *head;
        Node *tail;
        int size;
        
    public:
        List(){
            size = 0;
            head = new Node;
            tail = new Node;
            head -> prev = nullptr;
            tail -> next = nullptr;
            head -> next = tail;
            tail -> prev = head;
        }
        class iter{
            private: 
                Node * current;
            public:
                iter(){
                    current = new Node;
                }
                iter(Node * ptr){
                    current = new Node;
                    current = ptr;
                }
                iter operator++(){
                    this -> current = this -> current -> next;
                    return *this;
                }
                iter operator++(int){
                    this -> current = this -> current -> next;
                    return *this;
                }
                iter operator--(){
                    this -> current = this -> current -> prev;
                    return *this;
                }
                iter operator--(int){
                    this -> current = this -> current -> prev;
                    return *this;
                }
                Object& operator*(){
                    return current->data;
                }
                bool operator==(const iter &other){
                    return current == other.current;
                }
                bool operator!=(const iter &other){
                    return !(*this == other);
                }
            friend class List<Object>;
        };
        iter begin(){
            return iter(head -> next);
        }
        iter end(){
            return iter(tail);
        }
        void insert(Object val, int idx){
            iter i = begin();
            for(int ii = 0; ii<idx ; ii++){
                ++i;
                if(i == end()) break;
            }
            Node * ptr = new Node;
            ptr -> data = val;
            Node * cur = i.current;
            Node * bef = cur -> prev;
            bef -> next = ptr;
            ptr -> next = cur;
            cur -> prev = ptr;
            ptr -> prev = bef;
        }
        void print(){
            iter i = begin();
            while(i != end()){
                cout<<*i<<" ";
                ++i;
            }
            cout<<endl;
        }
        void del(Object val){
            iter i = begin();
            while(i != end()){
                if(*i == val){
                    Node *ptr = i.current;
                    ptr -> prev -> next = ptr ->next;
                    ptr -> next -> prev = ptr -> prev;
                }
                ++i;
            }
        }
};

int main(){
    float f1 = 10.4, f2 = 10.9;
    int i1 = 10, i2 = 3;
    string s1 = "Hello ", s2 = "World";
    // cout<<sum(f1, f2)<<endl;
    // cout<<sum(i1, i2)<<endl;
    // cout<<sum(s1, s2)<<endl;
    List<int> L;
    L.insert(0,0);
    L.insert(1,0);
    L.insert(2,0);
    L.print();
    L.del(1);
    L.del(0);
    L.print();
}
