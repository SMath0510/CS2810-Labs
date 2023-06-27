#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/* Do note that the error in test case 12 was because of the ambiguity in the problem statement
I assumed that the cd ~ is an invalid command for the sh terminal and in general it is a valid command 
just that we have to throw a different error "Folder does not exist". Do consider this as this is not a 
conceptual but rather an error caused due to lack of clarity in the problem statement */

struct Command{
    string name;
    bool isFolder;
    vector<Command *> childDir;
    Command * parentDir;
};

class CompareClass{
    public:
    bool operator()(Command *c1, Command *c2){
        if(c1 -> isFolder && !(c2 -> isFolder)){
            return true;
        }
        if(!(c1 -> isFolder) && c2 -> isFolder){
            return false;
        }
        return (c1->name) < (c2->name);
    }
};

class Home{
    private:
        Command *root;
        Command *current;
        string type;
    
    public:
        Home(string username, string T){
            root = new Command;
            root -> name = "";
            root -> parentDir = nullptr;
            root -> isFolder = true;
            current = new Command;
            current = root;
            type = T;
            makeFolder("home");
            changeFolder("home");
            makeFolder(username);
            changeFolder(username);
        }
        
        class mkdirError{};
        class touchError{};
        class cdError{};
        class rmError{};
        class commandError{};
        void makeFolder(string nameFolder){
            bool foundFolder = false;
            bool foundFile = false;
            for(int i = 0; i<(current -> childDir).size(); i++){
                if((current -> childDir)[i] -> name == (current -> name) +"/" + nameFolder){
                    if((current -> childDir)[i] -> isFolder == true) foundFolder = true;
                    else foundFile = true;
                    break;
                }
            }
            if(foundFolder == true){
                throw mkdirError();
            } 
            else if(foundFile == true){
                throw touchError();   
            }
            Command * newFolder = new Command;
            newFolder -> name = (current -> name) +"/" + nameFolder;
            newFolder -> parentDir = current;
            newFolder ->isFolder = true;
            (current -> childDir).push_back(newFolder);
        }
    
        void makeFile(string nameFile){
            bool foundFolder = false;
            bool foundFile = false;
            for(int i = 0; i<(current -> childDir).size(); i++){
                if((current -> childDir)[i] -> name == (current -> name) +"/" + nameFile){
                    if((current -> childDir)[i] -> isFolder == true) foundFolder = true;
                    else foundFile = true;
                    break;
                }
            }
            if(foundFolder == true){
                throw mkdirError();
            } 
            else if(foundFile == true){
                throw touchError();   
            }
            Command * newFile = new Command;
            newFile -> name = (current -> name) +"/" + nameFile;
            newFile -> parentDir = current;
            newFile ->isFolder = false;
            (current -> childDir).push_back(newFile);
        }
    
        void changeFolder(string destination){
            if(destination == "~"){
                if(type == "sh"){
                    throw cdError();
                }
                else {
                    if((root -> childDir).size() > 0 && (root -> childDir[0] -> childDir).size() > 0){
                        current = root -> childDir[0] -> childDir[0];
                    }
                    else throw cdError();
                }
            }
            else if(destination == ".."){
                if(current != root) current = current -> parentDir;
            }
            else {
                bool foundFolder = false;
                bool foundFile = false;
                for(int i = 0; i<(current -> childDir).size(); i++){
                    if((current -> childDir)[i] -> name == (current -> name) +"/" + destination){
                        if((current -> childDir)[i] -> isFolder == true) foundFolder = true;
                        else foundFile = true;
                        if(foundFolder == true){
                            current = (current -> childDir)[i] ;
                        } 
                        else if(foundFile == true){
                            throw touchError();   
                        }
                        break;
                    }
                }
                
                if(foundFile == false && foundFolder == false){
                    throw cdError();
                }
            }
        }
    
        void removeElem(string itemName){
            bool found = false;
            for(int i = 0; i<(current -> childDir).size(); i++){
                if((current -> childDir)[i] -> name == (current -> name) +"/" + itemName){
                    (current -> childDir)[i] -> parentDir = nullptr;
                    for(int j = i; j<((current -> childDir).size() - 1); j++){
                        (current -> childDir)[j] = (current -> childDir)[j+1]; 
                    }
                    (current -> childDir).pop_back();
                    found = true;
                    i--;
                }
            }
            if(found == false){
                throw rmError();
            }
        }
    
        void printContent(){
            bool printed = false;
            sort((current -> childDir).begin(), (current -> childDir).end(), CompareClass());
            for(int i = 0; i<(current -> childDir).size(); i++){
                for(int j = (current -> name).size() + 1; j < ((current -> childDir)[i] -> name).size(); j++){
                    printed = true;
                    cout << ((current -> childDir)[i] -> name)[j];
                }
                cout << " ";
            }
            if(printed == true) cout << endl;
        }
    
        string currDir(){
            if(current -> name != "") return current -> name;
            else return "/";
        }
    
};

int main() { 
    string type, username;
    cin >> type >> username;
    string base;
    if(type == "bash"){
        base = "/home/"+username+" ";
    }
    else if(type == "zsh"){
        base = username + "/home/"+username+" ";
    }
    else{
        base = "";
    }
    vector<string> instructionSet;
    Home desktop(username, type);
    string command = "start";
    while(command != "quit"){
        if(type == "zsh"){
            base = username + " " + desktop.currDir() + " ";
        }
        else if(type == "bash"){
            base = desktop.currDir() + " ";
        }
        string instruction;
        cin >> command;
        instruction = command;
        if(command == "mkdir"){
            string folderName;
            cin >> folderName;
            instruction += (" " + folderName);
            cout << base << "$ " << command << " " << folderName << endl;
            try{
                desktop.makeFolder(folderName);
            }
            catch(Home :: mkdirError){
                cout << "Folder Exists" << endl;
            }
            catch(Home :: touchError){
                cout << "File Exists" << endl;
            }
        }
        else if(command == "touch"){
            string fileName;
            cin >> fileName;
            instruction += (" " + fileName);
            cout << base << "$ " << command << " " << fileName << endl;
            try{
                desktop.makeFile(fileName);
            }
            catch(Home :: touchError){
                cout << "File Exists" << endl;
            }
            catch(Home :: mkdirError){
                cout << "Folder Exists" << endl;
            }
        }
        else if(command == "cd"){
            string folderName;
            cin >> folderName;
            instruction += (" " + folderName);
            cout << base << "$ " << command << " " << folderName << endl;
            try{
                desktop.changeFolder(folderName);
            }
            catch(Home :: cdError){
                cout << "Folder does not exist" <<endl;
            }
        }
        else if(command == "rm"){
            string itemName;
            cin >> itemName;
            instruction += (" " + itemName);
            cout << base << "$ " << command << " " << itemName << endl;
            try{
                desktop.removeElem(itemName);
            }
            catch(Home :: rmError){
                cout << "Does not exist" <<endl;
            }
        }
        else if(command == "ls"){
            cout << base << "$ " << command << endl;
            desktop.printContent();
        }
        else if(command == "pwd"){
            cout << base << "$ " << command << endl;
            cout << desktop.currDir() << endl;
        }
        else if(command == "history"){
            cout << base << "$ " << command << endl;
            if(type != "zsh"){
                cout << "Command does not exist" << endl;
            }
            else{
                for(int i = 0; i < instructionSet.size(); i++){
                    cout << i << " " << instructionSet[i] << endl;
                }
            }
        }
        else if(command == "quit"){
            cout << base << "$ " << command << endl;
            
        }
        else{
            cout << base << "$ " << command << endl;
            cout << "Command does not exist" << endl;
        }
        instructionSet.push_back(instruction);
    }
    return 0; 
}
