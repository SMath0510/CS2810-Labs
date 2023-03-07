#include<bits/stdc++.h>
using namespace std;

class Graphs{
    private:
        vector<vector<pair<int,int>>> adj_list;
        int size;
        vector<bool> visited;
        vector<pair<pair<int,int>,int>> edges;
        vector<int> color;
        vector<int> dist;
    public:
        Graphs(int n){
            size = n;
            adj_list.resize(size);
            visited.resize(size, false);
            color.resize(size, 0);
            dist.resize(size, 1e9);
        }
        void addEdge(int a, int b, int w = 1){
            adj_list[a].push_back({b, w});
            adj_list[b].push_back({a, w});
            edges.push_back({{a, b}, w});
            edges.push_back({{b, a}, w});
        }
        void BFS(int root){
            queue<int> Q;
            Q.push(root);
            while(!Q.empty()){
                int node = Q.front();
                Q.pop();
                if(visited[node]) continue;
                visited[node] = true;
                for(auto child : adj_list[node]){
                    if(visited[child.first]) continue;
                    Q.push(child.first);
                }
            }
        }
        void DFS(int root){
            stack<int> S;
            S.push(root);
            while(!S.empty()){
                int node = S.top();
                if(color[node] != 0){
                    color[node] = 2;
                    S.pop();
                    continue;
                }
                color[node] = 1;
                for(auto child: adj_list[node]){
                    if(color[child.first] != 0) continue;
                    // if color == 1 means there is a cycle
                    S.push(child.first);
                }
            }
        }
        void Traverse(int mode, int root){
            if(mode == 1){
                visited.resize(size, false);
                BFS(root);
            }
            else{
                color.resize(size, 0);
                DFS(root);
            }
        }
        void print(int mode){
            if(mode == 1){
                for(int i = 0; i < size; i++){
                    cout<<visited[i]<<" ";
                }
                cout<<endl;
            }
            else if(mode == 2){
                for(int i = 0; i < size; i++){
                    cout<<color[i]<<" ";
                }
                cout<<endl;
            }
            else{
                for(int i = 0; i < size; i++){
                    cout<<dist[i]<<" ";
                }
                cout<<endl;
            }
        }
        void Dijkstras(int source){
            dist.resize(size, 1e9);
            visited.resize(size, false);
            dist[source] = 0;
            priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> PQ;
            PQ.push({0,source});
            while(!PQ.empty()){
                pair<int,int> node = PQ.top();
                PQ.pop();
                if(visited[node.first]) continue;
                visited[node.first] = true;
                for(auto child : adj_list[node.first]){
                    if(visited[child.first]) continue;
                    if(dist[child.first] > dist[node.first] + child.second){
                        dist[child.first] = dist[node.first] + child.second;
                        PQ.push({child.first, dist[child.first]});
                    }
                }
            }
        }
        void Bellman(int source){
            dist.resize(size, 1e9);
            dist[source] = 0;
            for(int i = 0; i < size; i++){
                bool relaxed = false;
                for(auto edge: edges){
                    int v1 = edge.first.first;
                    int v2 = edge.first.second;
                    int w = edge.second;
                    if(dist[v2] > dist[v1] + w){
                        dist[v2] = dist[v1] + w;
                        relaxed = true;
                    }
                }
                if(relaxed && i == size-1){
                    // Negative cycle exists
                }
                if(!relaxed){
                    break;
                }
            }
        }
};

int main(){
    Graphs g1(5);
    g1.addEdge(0,1,2);
    g1.addEdge(0,2,2);
    g1.addEdge(1,2,4);
    g1.addEdge(2,4,1);
    g1.addEdge(2,3,1);
    // g1.Dijkstras(0);
    // g1.Bellman(0);
    g1.Traverse(1, 0);
    g1.print(1);
}