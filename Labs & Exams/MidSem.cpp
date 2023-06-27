#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/* Forward Declaration of the classes */
class Currency;
class Wallet;

/* Declaring the global variables */
vector<Currency> Bank;
vector<Wallet> W;
vector<vector<float>> Conversion;

/* floating point comparator */
const float eps = 1e-6;

/* Creating the struct pair */
struct pair{
    int first;
    float second;
};

class Currency{
    private:
    string name;
    int numD;
    vector<float> Denominations;
    
    public:
    Currency(){
        cin>>name;
        cin>>numD;
        for(int i = 0; i < numD; i++){
            float x; cin>>x;
            Denominations.push_back(x);
        }
    }
    
    /* To print the info of the object */
    /*
    void getInfo(){
        cout<<name<<" "<<numD<<endl;
        for(int i = 0; i < numD; i++){
            cout<<Denominations[i]<<" ";
        }
        cout<<endl;
    }
    */
    
    string getName(){
        return name;
    }
    
    /* Declaring the friend class */
    friend class Wallet;
};

/* Linear searching to find the Bank ID */
int search(const string &id){
    for(int i = 0; i<Bank.size(); i++){
        if(Bank[i].getName() == id){
            return i;
        }
    }
    return 0;
}

bool Checker(int source){
    /* Checking if or not there exist an unbalanced triangle */
    for(int i = 0; i<Conversion.size(); i++){
        if(i == source) continue;
        for(int j = 0; j<Conversion.size(); j++){
            if(j == source || j == i) continue;
            float p1 = Conversion[source][i];  /* Direct Path rate change */
            float p2 = Conversion[source][j] * Conversion[j][i]; /* Indirect Path rate change */
            if(abs(p1 - p2) < eps){  /* floating point comparator */
                continue;
            }
            else {
                return true;
            }
        }
    }
    return false;
}

class Wallet{
    private:
    string from;
    string to;
    vector<int> Notes_from;
    vector<int> Notes_to;
    float rate;
    float sum;
    float sum_final;
    
    public:
    Wallet(){
        
        /* Searching the index : from */
        cin>>from;
        int f = search(from);
        Currency present = Bank[f];
        
        /* Getting the Denomination count */
        for(int i = 0; i < present.numD; i++){
            int x;
            cin>>x;
            Notes_from.push_back(x);
        }
        
        /* Calculating the sum */
        vector<float> Value = present.Denominations;
        sum = 0;
        for(int i = 0; i < Value.size(); i++){
            sum += Notes_from[i]*Value[i];
        }  
        
        /* Searching the index : to */
        cin>>to;
        int t = search(to);
        Currency want = Bank[t];
        
        /* Calculating the final sum */
        rate = Conversion[f][t];
        sum_final = sum*rate;
        
        /* Filling up the new wallet */
        float tmp = sum_final;
        Value = want.Denominations;
        Notes_to.resize(want.numD,0);
        for(int i = 0; i < want.numD; i++){
            while(tmp >= Value[i]){
                tmp -= Value[i];
                Notes_to[i]++;
            }
        }
        
        /* Printing the output */
        cout<<to<<" ";
        for(int i = 0; i<want.numD; i++){
            cout<<'('<<Value[i]<<" "<<Notes_to[i]<<") ";
        }
        cout<<endl;
        
    }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    cin>>n;
    
    for(int i = 0; i<n; i++){
        Currency x;
        Bank.push_back(x);
    }
    
    /* The content of the wallet */
    
    // for(int i = 0; i<n; i++){
    //     Bank[i].getInfo();
    // }
    
    /* Filling in the conversion rates */
    Conversion.resize(n);
    
    for(int i = 0; i<n; i++){
        Conversion[i].resize(n);
    }
    for(int i = 0; i < (n*(n-1))/2; i++){
        int x,y;
        float r;
        cin>>x>>y>>r;
        x--; y--;
        Conversion[x][y] = r;
        Conversion[y][x] = 1/r;
    }
    
    /* Conversion rates */
    
    // for(int i = 0; i<n; i++){
    //     for(int j = 0; j<n; j++){
    //         cout<<Conversion[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    
    
    int part;
    cin>>part;
    if(part == 1){
        int w;
        cin>>w;
        for(int i = 0; i<w; i++){
            Wallet obj;
            W.push_back(obj);
        }
    }
    else{
        int p;
        cin>>p;
        p--;
        bool op = Checker(p);
        if(op == true){
            cout<<"Yes"<<endl;
        }
        else{
            cout<<"No"<<endl;
        }
    }
    return 0;
}
