#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int n;
    cin>>n;
    map<string, vector<string>> similiarScore;
    for(int i = 0; i<n; i++){
        string str;
        cin>>str;
        string tmp = str;
        sort(tmp.begin(), tmp.end());
        similiarScore[tmp].push_back(str);
    }
    vector<string> maxScoreStrings;
    int maxScore = 0;
    for(auto mapElement : similiarScore){
        int currScore = mapElement.second.size();
        if(maxScore < currScore){
            maxScore = currScore;
        }
    }
    for(auto mapElement : similiarScore){
        int currScore = mapElement.second.size();
        if(maxScore == currScore){
            maxScoreStrings.push_back(mapElement.first);
        }
    }
    string retString;
    for(auto mainString : maxScoreStrings){
        for(auto str : similiarScore[mainString]){
            if(retString.size() == 0){
                retString = str;
            }
            else{
                retString = min(str, retString);
            }
        }
    }
    cout<<retString<<endl;
    return 0;
}
