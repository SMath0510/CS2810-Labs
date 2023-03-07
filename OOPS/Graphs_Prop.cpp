#include<bits/stdc++.h>
using namespace std;

class Graph{
    private:
    int n;
    vector<vector<int>> M;
    
    public:
    Graph(int x){
        n = x;
        M.resize(n);
        for(int i = 0; i<n; i++){
            M[i].resize(n,0);
        }
    }
    void operator+=(pair<int,int> &p){
        M[p.first][p.second] = 1;
        M[p.second][p.first] = 1;
    }
    void operator-=(pair<int,int> &p){
        M[p.second][p.first] = 0;
        M[p.first][p.second] = 0;
    }
    bool DFSC(int node, int parent, vector<bool> &visited){
        bool ret = false;
        for(int i = 0; i<n; i++){
            if(M[node][i] == 1 && i != parent){
                if(visited[i]) return true;
                ret |= DFSC(i, node, visited);
            }
        }
        return ret;
    }
    bool detectCycle(){
        vector<bool> visited(n, false);
        for(int i = 0; i<n; i++){
            if(visited[i] == true ) continue;
            visited[i] = true;
            bool detected = DFSC(i, -1, visited);
            if(detected) return true;
        }
        return false;
    }
    int numComp(){
        vector<bool> visited(n,false);
        stack<int> s;
        int ret = 0;
        for(int i = 0; i<n; i++){
            if(visited[i]) continue;
            ret ++;
            s.push(i);
            while(!s.empty()){
                int node = s.top();
                s.pop();
                if(visited[node]) continue;
                visited[node] = true;
                for(int i = 0; i<n; i++){
                    if(M[node][i] == 1){
                        if(visited[i]) continue;
                        s.push(i);
                    }
                }
            }
        }
        return ret;
    }
    bool reach(int u, int v){
        vector<bool> visited(n,false);
        stack<int> s;
        s.push(u);
        while(!s.empty()){
            int node = s.top();
            s.pop();
            if(visited[true]) continue;
            visited[node] = true;
            for(int i = 0; i<n; i++){
                if(M[node][i] == 1){
                    if(visited[i]) continue;
                    s.push(i);
                }
            }
        }
        return visited[v];
    }
};

int main(){
    Graph G(5);
    vector<pair<int,int>> edges = {{0,1}, {1,2}, {2,3}, {3,4}, {4,0}};
    for(int i = 0; i<5; i++){
        G+=edges[i];
    }
    // cout<<G.detectCycle()<<endl;
    // cout<<G.numComp()<<endl;
    // cout<<G.reach(0,3)<<endl;
    
}