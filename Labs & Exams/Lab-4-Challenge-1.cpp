#include<iostream>
using namespace std;

template<class Object>
class DoublyLinkedList
{
    private:
        struct Node
        {
            Object data;
            Node *next;
            Node *prev;
              Node(const Object & d = Object{ }, Node * p = nullptr, Node * n = nullptr) 
              : data(d), prev(p), next(n) {}
        };
          
        Node *head; //sentinel node at the beginning
        Node *rear; //sentinel node at the end
        int size;
    
    public:
  
        /*TODO: Define a constructor for DoublyLinkedList here, allocating the sentinel nodes*/
        
        DoublyLinkedList(){
            head = new Node;
            rear = new Node;
            head -> next = rear;
            rear -> prev = head;
            size = 0;
        }
        
        class Iterator
        {
            private:
                Node *current;        
            public:
                Iterator(Node *inp) : current(inp) {}
                Object & operator*() {return current->data;}
          
                /*TODO: You can add more methods here */
                
                Iterator & operator++ ( ){
                    this->current = this->current->next;
                    return *this;
                }
                Iterator & operator-- ( ){
                    this->current = this->current->prev;
                    return *this;
                }
                bool operator== ( const Iterator & rhs ){ 
                    return current == rhs.current;
                }
                bool operator!= ( const Iterator & rhs ){ 
                    return !( *this == rhs ); 
                }
          
            friend class DoublyLinkedList<Object>;
        };

        Iterator begin(){return Iterator(head->next);}    
        Iterator end(){return Iterator(rear);}
        Iterator insert(Iterator itr, Object & o){
            Node *present_node = itr.current;
            Node *prev_node = itr.current->prev;
            Node *to_add = new Node(o, prev_node, present_node);
            present_node -> prev = to_add;
            prev_node -> next = to_add;
            Iterator itr_ret(to_add);
            size++;
            return itr_ret;
        }
        Iterator erase(Iterator itr){
            Node *next_node = itr.current->next;
            Node *prev_node = itr.current->prev;
            next_node -> prev = prev_node;
            prev_node -> next = next_node;
            size--;
            return itr;
        }
        Iterator atIndex(int p){
            auto itr = begin();
            
            for(int i = 0; i<p; i++){
                ++itr;
            }
            return itr;
        }
        int indexOf(Iterator itr){
            int cnt = 0;
            for(auto it = begin(); it!= end(); ++it){
                if(it == itr) return cnt;
                cnt++;
            }  
            return cnt;
        }
        void display()
        {        
            Iterator itr(begin().current);
            for (; itr != end(); ++itr)
                cout << *itr << " ";
            cout << endl;
        }        
};

int main()
{
    int N;
    cin >> N;
    DoublyLinkedList<int> dl;
    int n;
    int index;
    int command;
    for (int i = 0; i < N; i++)
    {
        cin >> command;
        switch (command)
        {
            case 1: /*insert the element at an index*/
                cin >> index;
                cin >> n;
                dl.insert(dl.atIndex(index), n);
                break;
            
            case 2: /*erase the element at an index*/
                cin >> index;
                dl.erase(dl.atIndex(index));
                break;

            case 3: /*print the head element*/
                cout << *(dl.begin()) << endl;
                break;

            case 4: /*print the rear element*/
                cout << *(--dl.end()) << endl;
                break;

            case 5: /*print the element at an index*/
                cin >> index;
                cout << *(dl.atIndex(index)) << endl;
                break;

            case 6: /*display the list*/
                dl.display();
                break;

            case 7: /*print the index of the iterator*/
                cin >> index;
                cout << dl.indexOf(dl.atIndex(index)) << endl;
                break;
        }
    }
}