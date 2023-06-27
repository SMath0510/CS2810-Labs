#include<bits/stdc++.h>
using namespace std;

/* A class to implement the Text Justification */
class Justify{
    private:
        vector<vector<int>> bad;
        vector<vector<int>> len;
        vector<string> words;
        vector<int> split;
        vector<int> cost;
        int n, L;

    public:
        Justify(vector<string> data, int lim){
            words = data;
            L = lim;
            n = data.size();
            bad.resize(n, vector<int> (n, 1e8));
            len.resize(n, vector<int> (n, 1e8));
            split.resize(n, n);
            cost.resize(n, 0);
        }

        int cube(int x){
            /* Returns cube of a number */
            return x*x*x;
        }
        
        void fillBad(){
            for(int i = 0; i<len.size(); i++) len[i][i] = words[i].size();
            /* Counting the word lengths */
            for(int i = 0; i<len.size(); i++){
                for(int j = i+1; j<len.size(); j++){
                    len[i][j]= len[i][j-1] + words[j].size() + 1; // +1 for space before new word
                }
            }
            /* Defining the badness of a line using the given definition */
            for(int i = 0; i<len.size(); i++){
                for(int j = i; j<len.size(); j++){
                    if(len[i][j] <= L) bad[i][j] = cube(L - len[i][j]);
                }
            }
        }

        void fillSplitCost(){
            /* Calculating the optimal split for the new line */
            for(int i = n-1; i>=0; i--){
                cost[i] = bad[i][n-1];
                for(int j = n-1; j>i; j--){
                    /* Taking the jth word on the next line and the remaining on the same line */
                    int localCost = bad[i][j-1] + cost[j];
                    if(localCost <= cost[i]){
                        cost[i] = localCost;
                        split[i] = j;
                    }
                }
            }
        }

        void print(){
            /* Printing the entire Paragraph */
            fillBad();
            fillSplitCost();
            for(int i = 0; i<n;){
                int length = len[i][split[i]-1];
                int newSpaces = L - length;
                if(split[i] == n) newSpaces = 0;
                int orignalSpaces = split[i] - i - 1;
                int addSpace, extraSpace;
                if(orignalSpaces == 0){
                    addSpace = 0;
                    extraSpace = 0;
                }
                else {
                    addSpace = newSpaces / orignalSpaces;
                    extraSpace = newSpaces % orignalSpaces;
                }
                for(int j = i; j < split[i]; j++){
                    cout << words[j] << " ";
                    for(int k = 0; k < addSpace; k++){
                        cout << " ";
                    }
                    if(extraSpace > 0) {
                        cout << " ";
                        extraSpace--;
                    }
                }
                cout << "\n";
                i = split[i];
            }
        }
};

/* Instruction class to store the instructions */
class Instructions{
    public:
        string type;
        vector<string> data;
        Instructions(string t, vector<string> d){
            type = t;
            data = d;
        }
};


class Paragraph {
    private:
        vector<string> words;
        int L;
        int size;
        int lim;
        stack<Instructions> executed;
        stack<Instructions> undoed;
    
    public: 
        Paragraph(int l, int n, int w, vector<string> W){
            words = W;
            L = l;
            size = n;
            lim = w;
            Instructions ins("addSentence", W);
            executed.push(ins);
        }

        /* Declaring the exceptions */
        class LimitError{};
        class DeleteError{};
        class PrintError{};
        class UndoError{};
        class RedoError{};

        /* The operations on the paragraph */
        void add_word(string word){
            vector<string> data = {word};
            Instructions ins("addWord", data);
            if(size == lim){
                throw LimitError();
            }
            size ++;
            executed.push(ins);
            words.push_back(word);
        }
        
        void add_sentence(vector<string> &data){
            Instructions ins("addSentence", data);
            if(size + data.size() > lim){
                throw LimitError();
            }
            size += data.size();
            executed.push(ins);
            words.insert(words.end(), data.begin(), data.end());
        }
    
        void Delete(int x){
            if(size < x){
                throw DeleteError();
            }    
            vector<string> data;
            for(int i = x; i>=1; i--){
                data.push_back(words[size - i]);
            }
            size -= x;
            for(int i = x; i>=1; i--){
                words.pop_back();
            }         
            Instructions ins("delete", data);
            executed.push(ins);
        }
    
        void undo(){
            if(executed.size() == 0){
                throw UndoError();
            }
            Instructions ins = executed.top();
            executed.pop();
            undoed.push(ins);
            if(ins.type == "addWord"){
                size --;
                words.pop_back();
            }
            if(ins.type == "addSentence"){
                size -= (ins.data.size());
                for(int i = 0; i < ins.data.size(); i++) words.pop_back();
            }
            if(ins.type == "delete"){
                size += ins.data.size();
                words.insert(words.end(), ins.data.begin(), ins.data.end());
            }
        }

        void redo(){
            if(undoed.size() == 0){
                throw RedoError();
            }
            Instructions ins = undoed.top();
            undoed.pop();
            if(ins.type == "addWord"){
                add_word(ins.data[0]);
            }
            if(ins.type == "addSentence"){
                add_sentence(ins.data);
            }
            if(ins.type == "delete"){
                Delete(ins.data.size());
            }
        }

        void Print(){
            if(words.size() == 0){
                throw PrintError();
            }
            Justify O(words, L);
            O.print();
        }
};

int main() {
  	// your driver code here
    string p;
    int n, l, w;
    cin >> p >> n >> l >> w;
    vector<string> words(n);
    for(int i = 0; i<n; i++) cin >> words[i];
    Paragraph P(l, n, w, words);
    string command;
    cin >> command;
    while(command != "end"){
        if(command == "undo"){
            try{
                P.undo();
            }
            catch(Paragraph :: UndoError){
                cout << "UndoNotPossibleExceptionRaised\n";
            }
        }
        if(command == "redo"){
            try{
                P.redo();
            }
            catch(Paragraph :: RedoError){
                cout << "RedoNotPossibleExceptionRaised\n";
            }
            
        }
        if(command == "delete"){
            int x;
            cin >> x;
            try{
                P.Delete(x);
            }
            catch(Paragraph :: DeleteError){
                cout << "NothingToDeleteException\n";
            }
        }
        if(command == "print"){
            try{
                P.Print();
            }
            catch(Paragraph :: PrintError){
                cout << "EmptyParagraphException\n";
            }
        }
        if(command == "add_word"){
            string s;
            cin >> s;
            try{
                P.add_word(s);
            }
            catch(Paragraph :: LimitError){
                cout << "WordLimitExceededException\n";
            }
        }
        if(command == "add_sentence"){
            int n; 
            cin >> n;
            vector<string> data(n);
            for(int i = 0; i<n; i++) cin >> data[i];
            try{
                P.add_sentence(data);
            }
            catch(Paragraph :: LimitError){
                cout << "WordLimitExceededException\n";
            }
        }
        cin >> command;
    }
	return 0;
}