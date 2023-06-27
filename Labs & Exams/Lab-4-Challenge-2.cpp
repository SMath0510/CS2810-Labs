
#include <iostream>
#include <string>
#include <vector>

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

template <class Key, class Value>
class Database {
public:
    class Record {
    private:
        Key k;
        Value v;

    public:
        Record(const Key &ik = Key(), const Value &iv = Value()) : k(ik), v(iv) {}
        Key &getKey() { return k; }
        Value &getValue() { return v; }
        void setValue(Value &x){ v = x; }
    };

private:
    DoublyLinkedList<Record> list;
    int size = 0;
    /*use the DoublyLinkedList class created in challenge 1*/

public:
    /*TODO: Implement the methods here*/
    void insertRecord(Key k, Value v){
        /* Insert in sorted key order */
        Record latest(k, v);
        int l = 0, r = size;
        int m;
        while(r - l > 1){
            m = (l+r)/2;
            if((*(list.atIndex(m))).getKey() < k){
                l = m;
            }
            else if((*(list.atIndex(m))).getKey() == k){
                return;
            }
            else{
                r = m;
            }
        }
        if((*(list.atIndex(l))).getKey() > k){
            // cout<<"Inserted "<<k<<" at "<<l<<endl;
            list.insert(list.atIndex(l), latest);
        }
        else{
            // cout<<"Inserted "<<k<<" at "<<r<<endl;
            list.insert(list.atIndex(r), latest);
        }
        size++;
    }
    int itr_location(Key k){
        int l = 0, r = size-1;
        int m;
        while(r - l > 1){
            m = (l+r)/2;
            if((*(list.atIndex(m))).getKey() < k){
                l = m;
            }
            else{
                r = m;
            }
        }
        if((*(list.atIndex(l))).getKey() == k){
            return l;
        }
        return r;
    }
    int itr_location_next(Key k){
        int l = 0, r = size-1;
        int m;
        while(r - l > 1){
            m = (l+r)/2;
            if((*(list.atIndex(m))).getKey() < k){
                l = m;
            }
            else{
                r = m;
            }
        }
        if((*(list.atIndex(l))).getKey() >= k){
            return l;
        }
        return r;
    }
    bool isPresent(Key k){
        /* Binary Search on the sorted array*/
        auto itr = list.atIndex(itr_location(k));
        return ((*itr).getKey() == k);
    }
    Record & selectRecord(Key k){
        /* Find the record and return it using Binary Search */
        auto itr = list.atIndex(itr_location(k));
        if((*itr).getKey() == k) {return *itr;}
        return (*list.begin());
    }
    vector<Record> selectRangeRecord(Key start, Key end){
        /* Find the record start using BS and then print till the end */
        vector<Record> ret;
        auto itr = list.atIndex(itr_location_next(start));
        while(itr != list.end()){
            if((*itr).getKey() > end){
                break;
            }
            ret.push_back(*itr);
            ++itr;
        }
        return ret;
    }
    void updateRecord(Key k, Value v){
        /* Check if the key exists or not, if it does change the value, else skip*/
        if(!isPresent(k)) return;
        auto itr = list.atIndex(itr_location(k));
        (*itr).setValue(v);
    }
    void updateRangeRecord(Key start, Key end, Value v){
        /* Check for the start index, if present then try else move to the next till you are <= next */
        if(!isPresent(start)) return;
        auto itr =list.atIndex(itr_location_next(start));
        while(itr != list.end()){
            if((*itr).getKey() > end){
                break;
            }
            (*itr).setValue(v);
            ++itr;
        }
    }
    void deleteRecord(Key k){
        if(!isPresent(k)) return;
        auto itr = list.atIndex(itr_location(k));
        list.erase(itr);
        size --;
    }
    void deleteRangeRecord(Key start, Key end){
        if(!isPresent(start)) return;
        auto itr = list.atIndex(itr_location_next(start));
        while(itr != list.end()){
            if((*itr).getKey() > end){
                break;
            }
            list.erase(itr);
            size --;
            if(size == 0) break;
            ++itr;
        }
    }
    Record getMinRecord(){
        return *(list.begin());
    }
    Record getMaxRecord(){
        return *(--list.end());
    }
    vector<Record> getallRecords(){
        vector<Record> ret;
        for(auto itr = list.begin(); itr != list.end(); ++itr){
            ret.push_back(*itr);
        }
        return ret;
    }
};

class StudentsKey {
public:
    string rollNo;
    StudentsKey(const string &inp = "") : rollNo(inp) {}
    bool operator<(StudentsKey &rhs) { return rollNo < rhs.rollNo; }
    bool operator>(StudentsKey &rhs) { return rollNo > rhs.rollNo; }
    bool operator==(StudentsKey &rhs) { return rollNo == rhs.rollNo; }
    bool operator<=(StudentsKey &rhs) { return rollNo <= rhs.rollNo; }
    bool operator>=(StudentsKey &rhs) { return rollNo >= rhs.rollNo; }
    friend ostream & operator<<(ostream & out, StudentsKey &k);
};

ostream & operator<<(ostream & out, StudentsKey &k) { 
    out << k.rollNo;
      return out;
}

class StudentsValue {
public:
    string name;
    string hostel;
    float cgpa;
    StudentsValue(const string &n = "", const string &h = "", float c = 10.0) : name(n), hostel(h), cgpa(c) {}
    friend ostream & operator<<(ostream & out, StudentsValue &v);
};

ostream & operator<<(std::ostream & out, StudentsValue &v) {
    out << v.name << " " << v.hostel << " " << v.cgpa;
    return out;
}

class FacultyKey {
public:
    string empId;
    FacultyKey(const string &inp = "") : empId(inp) {}
    bool operator<(FacultyKey &rhs) { return empId < rhs.empId; }
    bool operator>(FacultyKey &rhs) { return empId > rhs.empId; }
    bool operator==(FacultyKey &rhs) { return empId == rhs.empId; }
    bool operator<=(FacultyKey &rhs) { return empId <= rhs.empId; }
    bool operator>=(FacultyKey &rhs) { return empId >= rhs.empId; }
    friend ostream & operator<<(ostream & out, FacultyKey &k);
};

ostream & operator<<(ostream & out, FacultyKey &k) { 
    out << k.empId;
     return out;
}

class FacultyValue {
public:
    string name;
    string designation;
    float salary;
    FacultyValue(const string &n = "", const string &d = "", float s = 10.0) : name(n), designation(d), salary(s) {}
    friend ostream & operator<<(ostream & out, FacultyValue &v);
};

ostream & operator<<(std::ostream & out, FacultyValue &v) {
    out << v.name << " " << v.designation << " " << v.salary;
    return out;
}

class CourseKey {
public:
    string courseId;
    CourseKey(const string &inp = "") : courseId(inp) {}
    bool operator<(CourseKey &rhs) { return courseId < rhs.courseId; }
    bool operator>(CourseKey &rhs) { return courseId > rhs.courseId; }
    bool operator==(CourseKey &rhs) { return courseId == rhs.courseId; }
    bool operator<=(CourseKey &rhs) { return courseId <= rhs.courseId; }
    bool operator>=(CourseKey &rhs) { return courseId >= rhs.courseId; }
    friend ostream & operator<<(ostream & out, CourseKey &k);
};

ostream & operator<<(ostream & out, CourseKey &k) { 
    out << k.courseId;
    return out;
}

class CourseValue {
public:
    string name;
    string semester;
    string facultyName;
    CourseValue(const string &n = "", const string &s = "", const string &f = "") : name(n), semester(s), facultyName(f) {}
    friend ostream & operator<<(ostream & out, FacultyValue &v);
};

ostream & operator<<(std::ostream & out, CourseValue &v) {
    out << v.name << " " << v.semester << " " << v.facultyName;
    return out;
}

int main() {
    int command;
    bool b;
    int BREAKING_COMMAND = 50;

    Database<StudentsKey, StudentsValue> student_db;
    Database<FacultyKey, FacultyValue> faculty_db;
    Database<CourseKey, CourseValue> course_db;

    while (true) {
        cin >> command;
        if (command == BREAKING_COMMAND) {
            break;
        }

        if (command == 1) { /*insert record*/
            int numberOfRecords = 0; /*number of records to be inserted*/
            cin >> numberOfRecords;

            while (numberOfRecords--) {

                string database;
                cin >> database;

                if (database == "STUDENT") {
                    string rollNo, name, hostel;
                    float cgpa;
                    cin >> rollNo >> name >> hostel >> cgpa;

                    StudentsKey k(rollNo);
                    StudentsValue v(name, hostel, cgpa);
                    student_db.insertRecord(k, v);
                } else if (database == "FACULTY") {
                    string empId, name, designation;
                    float salary;
                    cin >> empId >> name >> designation >> salary;

                    FacultyKey k(empId);
                    FacultyValue v(name, designation, salary);
                    faculty_db.insertRecord(k, v);
                } else {
                    string courseId, name, semester, facultyName;
                    cin >> courseId >> name >> semester >> facultyName;

                    CourseKey k(courseId);
                    CourseValue v(name, semester, facultyName);
                    course_db.insertRecord(k, v);
                }
            }

        } else if (command == 2) { /*check whether the key is present*/
            string database;
            cin >> database;

            if (database == "STUDENT") {
                string rollNo;
                cin >> rollNo;

                StudentsKey k(rollNo);
                b = student_db.isPresent(k);
                cout << b << endl;
            } else if (database == "FACULTY") {
                string empId;
                cin >> empId;

                FacultyKey k(empId);
                b = faculty_db.isPresent(k);
                cout << b << endl;
            } else {
                string courseId;
                cin >> courseId;

                CourseKey k(courseId);
                b = course_db.isPresent(k);
                cout << b << endl;
            }

        } else if (command == 3) {
            string database; /*returns the record containing the key*/
            cin >> database;

            if (database == "STUDENT") {
                string rollNo;
                cin >> rollNo;

                StudentsKey k(rollNo);
                auto r = student_db.selectRecord(k);
                cout << r.getKey() << " " << r.getValue() << endl;
            } else if (database == "FACULTY") {
                string empId;
                cin >> empId;

                FacultyKey k(empId);
                auto r = faculty_db.selectRecord(k);
                cout << r.getKey() << " " << r.getValue() << endl;
            } else {
                string courseId;
                cin >> courseId;

                CourseKey k(courseId);
                auto r = course_db.selectRecord(k);
                cout << r.getKey() << " " << r.getValue() << endl;
            }

        } else if (command == 4) { /*returns a vector containing all the records in the database
                                     whose key lies between rangeStart and rangeEnd (inclusive).*/
            string database;
            cin >> database;

            if (database == "STUDENT") {
                string rangeStart, rangeEnd;
                cin >> rangeStart >> rangeEnd;

                StudentsKey rs(rangeStart);
                StudentsKey re(rangeEnd);
                auto lst = student_db.selectRangeRecord(rs, re);
                for (auto r : lst) {
                    cout << r.getKey() << " " << r.getValue() << endl;
                }
            } else if (database == "FACULTY") {
                string rangeStart, rangeEnd;
                cin >> rangeStart >> rangeEnd;

                FacultyKey rs(rangeStart);
                FacultyKey re(rangeEnd);
                auto lst = faculty_db.selectRangeRecord(rs, re);
                for (auto r : lst) {
                    cout << r.getKey() << " " << r.getValue() << endl;
                }
            } else {
                string rangeStart, rangeEnd;
                cin >> rangeStart >> rangeEnd;

                CourseKey rs(rangeStart);
                CourseKey re(rangeEnd);
                auto lst = course_db.selectRangeRecord(rs, re);
                for (auto r : lst) {
                    cout << r.getKey() << " " << r.getValue() << endl;
                }
            }

        } else if (command == 5) { /*updates the record in the database whose key is k with value v.
                                     If k is not present, there is no change in the database.*/
            string database;
            cin >> database;

            if (database == "STUDENT") {
                string rollNo, name, hostel;
                float cgpa;
                cin >> rollNo >> name >> hostel >> cgpa;

                StudentsKey k(rollNo);
                StudentsValue v(name, hostel, cgpa);
                student_db.updateRecord(k, v);
            } else if (database == "FACULTY") {
                string empId, name, designation;
                float salary;
                cin >> empId >> name >> designation >> salary;

                FacultyKey k(empId);
                FacultyValue v(name, designation, salary);
                faculty_db.updateRecord(k, v);
            } else {
                string courseId, name, semester, facultyName;
                cin >> courseId >> name >> semester >> facultyName;

                CourseKey k(courseId);
                CourseValue v(name, semester, facultyName);
                course_db.updateRecord(k, v);
            }

        } else if (command == 6) { /*updates all records in the database whose key lies between
                                     rangeStart and rangeEnd, with value v (inclusive).*/
            string database;
            cin >> database;

            if (database == "STUDENT") {
                string rangeStart, rangeEnd, name, hostel;
                float cgpa;
                cin >> rangeStart >> rangeEnd >> name >> hostel >> cgpa;

                StudentsKey rs(rangeStart);
                StudentsKey re(rangeEnd);
                StudentsValue v(name, hostel, cgpa);
                student_db.updateRangeRecord(rs, re, v);
            } else if (database == "FACULTY") {
                string rangeStart, rangeEnd, name, designation;
                float salary;
                cin >> rangeStart >> rangeEnd >> name >> designation >> salary;

                FacultyKey rs(rangeStart);
                FacultyKey re(rangeEnd);
                FacultyValue v(name, designation, salary);
                faculty_db.updateRangeRecord(rs, re, v);
            } else {
                string rangeStart, rangeEnd, name, semester, facultyName;
                cin >> rangeStart >> rangeEnd >> name >> semester >> facultyName;

                CourseKey rs(rangeStart);
                CourseKey re(rangeEnd);
                CourseValue v(name, semester, facultyName);
                course_db.updateRangeRecord(rs, re, v);
            }

        } else if (command == 7) { /*deletes the record with key k.*/
            string database;
            cin >> database;

            if (database == "STUDENT") {
                string rollNo;
                cin >> rollNo;

                StudentsKey k(rollNo);
                student_db.deleteRecord(k);
            } else if (database == "FACULTY") {
                string empId;
                cin >> empId;

                FacultyKey k(empId);
                faculty_db.deleteRecord(k);
            } else {
                string courseId;
                cin >> courseId;

                CourseKey k(courseId);
                course_db.deleteRecord(k);
            }

        } else if (command == 8) { /*deletes all records with key between rangeStart and rangeEnd (inclusive).*/
            string database;
            cin >> database;

            if (database == "STUDENT") {
                string rangeStart, rangeEnd;
                cin >> rangeStart >> rangeEnd;

                StudentsKey rs(rangeStart);
                StudentsKey re(rangeEnd);
                student_db.deleteRangeRecord(rs, re);
            } else if (database == "FACULTY") {
                string rangeStart, rangeEnd;
                cin >> rangeStart >> rangeEnd;

                FacultyKey rs(rangeStart);
                FacultyKey re(rangeEnd);
                faculty_db.deleteRangeRecord(rs, re);
            } else {
                string rangeStart, rangeEnd;
                cin >> rangeStart >> rangeEnd;

                CourseKey rs(rangeStart);
                CourseKey re(rangeEnd);
                course_db.deleteRangeRecord(rs, re);
            }

        } else if (command == 9) { /*return the minimum record*/
            string database;
            cin >> database;

            if (database == "STUDENT") {
                auto r = student_db.getMinRecord();
                cout << r.getKey() << " " << r.getValue() << endl;
            } else if (database == "FACULTY") {
                auto r = faculty_db.getMinRecord();
                cout << r.getKey() << " " << r.getValue() << endl;
            } else {
                auto r = course_db.getMinRecord();
                cout << r.getKey() << " " << r.getValue() << endl;
            }

        } else if (command == 10) { /*return the maximum record*/
            string database;
            cin >> database;

            if (database == "STUDENT") {
                auto r = student_db.getMaxRecord();
                cout << r.getKey() << " " << r.getValue() << endl;
            } else if (database == "FACULTY") {
                auto r = faculty_db.getMaxRecord();
                cout << r.getKey() << " " << r.getValue() << endl;
            } else {
                auto r = course_db.getMaxRecord();
                cout << r.getKey() << " " << r.getValue() << endl;
            }

        } else if (command == 11) { /*returns a vector containing all the records in the database.*/
            string database;
            cin >> database;

            if (database == "STUDENT") {
                auto lst = student_db.getallRecords();
                for (auto r : lst) {
                    cout << r.getKey() << " " << r.getValue() << endl;
                }
            } else if (database == "FACULTY") {
                auto lst = faculty_db.getallRecords();
                for (auto r : lst) {
                    cout << r.getKey() << " " << r.getValue() << endl;
                }
            } else {
                auto lst = course_db.getallRecords();
                for (auto r : lst) {
                    cout << r.getKey() << " " << r.getValue() << endl;
                }
            }

        } else {
            cout << "INVALID COMMAND!" << endl;
            break;
        }
    }
}