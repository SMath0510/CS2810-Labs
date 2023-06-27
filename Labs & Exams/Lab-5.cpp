#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <queue>
using namespace std;

/* Defined the struct for storing the character information in it */
struct Node{
    char letter;
    int freq;
    int inTime;
    Node * left;
    Node * right;
};

/* Class to compare any two node in order to place them appropriately in Priority Queue */
class CompareNodes{
    public:
        bool operator() (const Node *n1, const Node *n2){
            if(n1 -> freq != n2 -> freq){
                // by the frequency
                return n1 -> freq > n2 -> freq;
            }
            else if(n1 -> inTime != n2 -> inTime){
                // by the inTimes of the nodes
                return n1 -> inTime > n2 -> inTime;
            }
            else{
                // by the ASCII value of characters
                return n1 -> letter > n2 -> letter;
            }
        }
};

/* Assigning the codes to the characters using recursive function */
void Traverse(map<char, string> & encodeChar, string currentEncoding, Node *currNode){
    if(currNode -> left == nullptr || currNode -> right == nullptr) {
        // If we see a terminal node, we assign encoding and return
        encodeChar[currNode -> letter] = currentEncoding;
        return;
    }
    // Traversing the left child
    Traverse(encodeChar, currentEncoding + "0", currNode -> left);
    // Traversing the right child
    Traverse(encodeChar, currentEncoding + "1", currNode -> right);
}

/* Assign Huffman Code to characters of given string */
map<char, string> EncodeHuffman(string &inString){
    map<char, int> freqMap; // storing the frequency of the characters
    for(int i = 0; i < inString.size(); i++){
        if(freqMap.find(inString[i]) == freqMap.end()){
            freqMap[inString[i]] = 1;
        }
        else{
            freqMap[inString[i]] ++;
        }
    }
    // Declaring the priority queue for picking the Nodes appropriately
    priority_queue<Node *, vector<Node *>, CompareNodes> encodingQueue;
    // Storing the terminal nodes in the queue
    for(auto ele : freqMap){
        Node *ins = new Node;
        ins -> letter = ele.first;
        ins -> freq = ele.second;
        ins -> inTime = 0;
        ins -> left = nullptr;
        ins -> right = nullptr;
        encodingQueue.push(ins);
    }
    int currTime = 1;
    // Pushing and constructing the Encoding Tree for traversing later
    while(encodingQueue.size() > 1){
        // The smallest frequency node
        Node *first = encodingQueue.top();
        encodingQueue.pop();
        // The second smallest frequency node
        Node *second = encodingQueue.top();
        encodingQueue.pop();
        // Combining the Nodes
        Node *combinedNode = new Node;
        combinedNode -> freq = first -> freq + second -> freq;
        combinedNode -> letter  = min(first -> letter, second -> letter);
        combinedNode -> inTime = currTime;
        combinedNode -> left = first;
        combinedNode -> right = second;
        currTime ++;
        encodingQueue.push(combinedNode);
    }
    // Getting the root of the encoding tree
    Node * rootTree = encodingQueue.top();
    encodingQueue.pop();
    string s = "";
    map<char, string> huffEncode;
    // Encoding the string 
    Traverse(huffEncode, s, rootTree);
    return huffEncode;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n, k;
    cin>>n>>k;
    string inString;
    cin>>inString;
    int prevIndex = 0;
    for(int i = k; i <= n; i = min(i + k, n)){
        // Getting the relevant substring
        string currStr = inString.substr(0, i);
        map<char, string> huffEncoding = EncodeHuffman(currStr);
        // Printing the current character encodings
        for(int j = prevIndex; j<i; j++){
            cout<<huffEncoding[inString[j]];
        }
        prevIndex = i;
        if(i == n) break;
    }
    return 0;
}