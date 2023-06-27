#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
 
/* Overall Time Complexity is Linear in the size of the DNA Sequence :) */

struct Node{
    char x;
    bool isLeaf;
    int cnt;
    Node * par;
    vector<Node *> children;
};

class Trie{
    private:
        Node * root;
    
    public:
        Trie(){
            root = new Node;
            root -> x = '/';
            root -> isLeaf = false;
            root -> cnt = 1;
            root -> par = nullptr;
        }
    
        void construct(vector<string> &s){ // O(n * k)
            for(int i = 0; i < s.size(); i++){
                Node * currNode = root;
                for(int j = 0; j < s[i].size(); j++){
                    int index = -1;
                    for(int k = 0; k < (currNode -> children).size(); k++){
                        if((currNode -> children)[k] -> x == s[i][j]){
                            index = k;
                            break;
                        }
                    }
                    if(index == -1){
                        Node * addNode = new Node;
                        addNode -> x = s[i][j];
                        addNode -> par = currNode;
                        addNode -> cnt = 1;
                        (currNode -> children).push_back(addNode);
                        currNode = addNode;
                    }
                    else{
                        currNode = (currNode -> children)[index];
                        (currNode -> cnt)++ ;
                    }
                }
                currNode -> isLeaf = true;
            }
        }
    
        map<string, int>  update(vector<pair<string, int>> &s){ // O(n * k * log(n))
            map<string, int> freqDisease;
            for(int i = 0; i < s.size(); i++){
                Node * currNode = root;
                bool found = true;
                freqDisease[s[i].first] = 0;
                for(int j = 0; j < (s[i].first).size(); j++){
                    int index = -1;
                    for(int k = 0; k < (currNode -> children).size(); k++){
                        if((currNode -> children[k]) -> x == (s[i].first)[j]){
                            index = k;
                            break;
                        }
                    }
                    if(index == -1){
                        found = false;
                        break;
                    }
                    else{
                        currNode = (currNode -> children)[index];
                    }
                }
                if(found){
                    freqDisease[s[i].first] = currNode -> cnt;
                }
            }
            return freqDisease;
        }
    
        bool search(string &s){ // O(n)
            Node * currNode = root;
            bool found = true;
            for(int j = 0; j < s.size(); j++){
                int index = -1;
                for(int k = 0; k < (currNode -> children).size(); k++){
                    if((currNode -> children[k]) -> x == s[j]){
                        index = k;
                        break;
                    }
                }
                if(index == -1){
                    found = false;
                    break;
                }
                else{
                    currNode = (currNode -> children)[index];
                }
            }
            return found;
        }
    
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int k,n,p, isMutated;
    cin>>k>>n>>p>>isMutated;
    vector<string> DNA(n);
    for(int i = 0; i<n; i++) { // O(n)
        cin >> DNA[i];
    }
    vector<pair<string, int>> Disease(p);
    vector<string> pattern(p);
    for(int i = 0; i<p; i++) { // O(p)
        string dis; cin >> dis;
        int freq; cin >> freq;
        Disease[i] = {dis, freq};
        pattern[i] = dis;
    }
    
    Trie T;
    T.construct(DNA); // O(n)
    Trie P;
    P.construct(pattern); // O(p)
    
    map<string, int> freqMap = T.update(Disease); // O(p * log(p))
    
    vector<int> indexFound;
    for(int i = 0; i<n; i++){ // O(n * k)
        string dna = DNA[i];
        if(P.search(dna)){ 
            indexFound.push_back(i);
        }
    }
    
    if(indexFound.size() == 0){
        cout << "No match found" << endl;
    }
    else{
        for(int i = 0; i<indexFound.size(); i++){ // O(n)
            cout << indexFound[i] << " ";
        } 
        cout<<endl;
    }
    
    bool valid = true;
    for(int i = 0; i<p; i++){ // O(p)
        int reqFrequency = Disease[i].second;
        int presentFrequency = freqMap[Disease[i].first];
        if(presentFrequency < reqFrequency){
            valid = false;
        }
    }
    
    if(valid) cout << "Yes" <<endl;
    else cout << "No" <<endl;
    
    if(isMutated == 1){
        int x; // Number of the diseases that mutate
        cin >> x; 
        
        for(int i = 0; i<x; i++){ // O(n * x)
            string s, t;
            cin >> s >> t;
            for(int i = 0; i<p; i++){
                if(Disease[i].first == s){
                    Disease[i].first = t;
                }
                pattern[i] = Disease[i].first;
            }
        }
        
        Trie PMut;
        PMut.construct(pattern); // O(p)
        freqMap.clear();
        freqMap = T.update(Disease); // O(p * log(p))
        
        vector<int> indexFound;
        for(int i = 0; i<n; i++){ // O(n * k)
            string dna = DNA[i];
            if(PMut.search(dna)){ 
                indexFound.push_back(i);
            }
        }
        
        if(indexFound.size() == 0){
            cout << "No match found" << endl;
        }
        else{
            for(int i = 0; i<indexFound.size(); i++){ // O(n)
                cout << indexFound[i] << " ";
            } 
            cout<<endl;
        }
        
        bool valid = true;
        for(int i = 0; i<p; i++){ // O(p)
            int reqFrequency = Disease[i].second;
            int presentFrequency = freqMap[Disease[i].first];
            if(presentFrequency < reqFrequency){
                valid = false;
            }
        }
        
        if(valid) cout << "Yes" <<endl;
        else cout << "No" <<endl;

    }
    
    return 0;
}
