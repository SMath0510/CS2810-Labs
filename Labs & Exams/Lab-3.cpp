#include<bits/stdc++.h>
using namespace std;

struct ListEle{
    int vertex_number;
    ListEle * next;
    ListEle * prev;
};

class Vertex{
    private:
    int vertex_number;
    public:
    Vertex(){
        vertex_number = 0;
    }
    Vertex(int number){
        vertex_number = number;
    }
    int getData(){
        return vertex_number;
    }
};

class Edge{
    private:
    Vertex from, to;
    public:
    Edge(Vertex F, Vertex T){
        from = F;
        to = T;
    }
    int getFrom(){
        return from.getData();
    }
    int getTo(){
        return to.getData();
    }
};

class List{
    private:
    ListEle * head;
    ListEle * tail;
    int size;
    
    public:
    List(){
        size = 0;
        head = new ListEle;
        head -> vertex_number = -1;
        tail = new ListEle;
        tail -> vertex_number = -1;
    }
    void Add(int number){
        if(size == 0){
            ListEle *vertex = new ListEle;
            vertex -> vertex_number = number;
            vertex -> next = NULL;
            vertex -> prev = NULL;
            head = vertex;
            tail = vertex;
        }
        else{
            ListEle *vertex = new ListEle;
            vertex -> vertex_number = number;
            vertex -> next = NULL;
            vertex -> prev = tail;
            tail -> next = vertex;
            tail = vertex;
        }
        size++;
    }
    ListEle * getHead(){
        return head;
    }
    int getSize(){
        return size;
    }
};

class Graph
{
  protected:
    int numVertices;
    int numEdges;
  
  public:
    Graph(){};
    Graph(int nv, int ne){
        numVertices = nv;
        numEdges = ne;
    }
    virtual void addEdge(Edge E) = 0;
    virtual bool reach(Vertex v1, Vertex v2) = 0;
    virtual bool detectCycle() = 0;
    virtual int OutDegree(Vertex v) = 0;
    virtual int inDegree(Vertex v) = 0;

  /* Define virtual functions here*/ 
};


class GraphUsingList : public Graph{
    public:
    vector<List> adjacency_List;
    
    public:
    GraphUsingList(int number_vertices, int number_edges){
        adjacency_List.resize(number_vertices);
    }
    void addEdge(Edge E){
        int from = E.getFrom();
        int to = E.getTo();
        adjacency_List[from].Add(to);
    }
    void DFS(int vertex, vector<bool> &visited){
        if(visited[vertex]){
            return;
        }
        // cout<<"Visiting the source "<<vertex<<endl;
        visited[vertex] = true;
        ListEle * ptr = adjacency_List[vertex].getHead();
        while(ptr != NULL){
            // cout<<"Going to the child "<<ptr->vertex_number<<endl;
            int child = ptr->vertex_number;
            if(child == -1) {
                ptr = ptr->next;
                continue;
            }
            if(visited[child] == false){
                DFS(child, visited);
            }
            ptr = ptr->next;
        }
    }
    bool reach(Vertex v1, Vertex v2){
        int from = v1.getData();
        int to = v2.getData();
        vector<bool> visited(adjacency_List.size());
        DFS(from, visited);
        return visited[to];
    }
    bool detectCycle(){
        stack<int> DFS_stack;
        vector<int> color(adjacency_List.size(), 0);
        vector<int> parent(adjacency_List.size(), -1);
        // vector<int> out_time(adjacency_List.size(), -1);
        for(int i = 0; i < adjacency_List.size(); i++){
            if(color[i] != 0) continue;
            // cout<<"Starting the DFS with "<<i<<endl;
            DFS_stack.push(i);
            while(DFS_stack.size() > 0){
                // cout<<"The element count of stack is "<<DFS_stack.size()<<endl;
                int vertex = DFS_stack.top();
                if(color[vertex] != 0){
                    color[vertex] = 2;
                    // cout<<"Changing the color to "<<color[vertex]<<endl;
                    // cout<<"Popping the vertexxxxxx "<<(vertex)<<" mark = "<<(color[vertex])<<endl;
                    DFS_stack.pop();
                    continue;
                }
                // cout<<"Visiting the source "<<vertex<<endl;
                color[vertex] = 1;
                ListEle * ptr = adjacency_List[vertex].getHead();
                while(ptr != NULL){
                    // cout<<"Going to the child "<<ptr->vertex_number<<endl;
                    int child = ptr->vertex_number;
                    if(child == -1) {
                        ptr = ptr -> next;
                        continue;
                    }
                    if(color[child] == 1){
                        // cout<<"Child "<<child<<" is visited "<<color[child]<<endl;
                        return true;
                    }
                    else if(color[child] == 0){
                        // cout<<"Pushing into the stack "<<child<<endl;
                        parent[child] = vertex;
                        DFS_stack.push(child);
                    }
                    ptr = ptr->next;
                }
            }
            // cout<<"The element count of stack is "<<DFS_stack.size()<<endl;
        }
        return false;
    }
    int inDegree(Vertex v){
        int vertex = v.getData();
        int inD = 0;
        for(int i = 0; i < adjacency_List.size(); i++){
            ListEle * ptr = adjacency_List[i].getHead();
            while(ptr != NULL){
                if(vertex == ptr->vertex_number){
                    // cout<<"In from "<<i<<" to "<<vertex<<endl;
                    inD++;
                }
                ptr = ptr->next;
            }
        }
        return inD;
    }
    int OutDegree(Vertex v){
        int vertex = v.getData();
        int outD = adjacency_List[vertex].getSize();
        if(adjacency_List[vertex].getHead() -> vertex_number == -1) return 0;
        return outD;
    }
};

class GraphUsingMatrix : public Graph{
    public:
    vector<vector<int>> adjacency_Matrix;
    int number_vertices;
    int number_edges;
    
    public:
    GraphUsingMatrix(int number_vertices, int number_edges){
        number_vertices = number_vertices;
        number_edges = number_edges;
        adjacency_Matrix.resize(number_vertices);
        for(int i = 0; i < number_vertices; i++){
            adjacency_Matrix[i].resize(number_vertices);
        }
        for(int i = 0; i < adjacency_Matrix.size(); i++){
            for(int j = 0; j < adjacency_Matrix[i].size(); j++) adjacency_Matrix[i][j] = 0;
        }
        // cout<<"Vertices "<<number_vertices<<"  and Edges "<<number_edges<<endl;
    }
    void addEdge(Edge E){
        int from = E.getFrom();
        int to = E.getTo(); 
        adjacency_Matrix[from][to] = 1;
    }
    bool reach(Vertex v1, Vertex v2){
        // cout<<"Calculating the reach"<<endl;
        for(int i = 0; i < adjacency_Matrix.size(); i++){
            for(int j = 0; j < adjacency_Matrix[i].size(); j++) cout<<adjacency_Matrix[i][j]<<" ";
            cout<<endl;
        }
        int from = v1.getData();
        int to = v2.getData();
        vector<bool> visited(adjacency_Matrix.size(), false);
        DFS(from, visited);
        // cout<<"Source "<<from<<" : "<<endl;
        for(int i = 0; i < visited.size(); i++) cout<<visited[i]<<" ";
        cout<<endl;
        return visited[to];
    }
    void DFS(int vertex, vector<bool> &visited){
        if(visited[vertex] == true){
            return;
        }
        // cout<<"Visiting the source "<<vertex<<endl;
        visited[vertex] = true;
        for(int j = 0; j < adjacency_Matrix[vertex].size(); j++) cout<<adjacency_Matrix[vertex][j]<<" ";
        cout<<endl;
        for(int i = 0; i < adjacency_Matrix[vertex].size(); i++){
            if(adjacency_Matrix[vertex][i] == 1){
                // cout<<"The child vertex is "<<i<<endl;
                DFS(i,visited);
            }
        }
    }
    bool detectCycle(){
        int count = 0;
        stack<int> DFS_stack;
        vector<bool> color(adjacency_Matrix.size(), 0);
        vector<int> parent(adjacency_Matrix.size(), -1);
        // vector<int> out_time(adjacency_List.size(), -1);
        for(int i = 0; i < adjacency_Matrix.size(); i++){
            // cout<<"Starting the DFS with "<<i<<endl;
            DFS_stack.push(i);
            while(DFS_stack.size() > 0){
                int vertex = DFS_stack.top();
                if(color[vertex] != 0){
                    color[vertex] = 2;
                    DFS_stack.pop();
                }
                // cout<<"Visiting the source "<<vertex<<endl;
                color[vertex] = 1;
                for(int i = 0; i < adjacency_Matrix.size(); i++){
                    // cout<<"Going to the child "<<ptr->vertex_number<<endl;
                    if(adjacency_Matrix[vertex][i] == 1 && color[i] == 1){
                        // cout<<"Child "<<child<<" is visited"<<endl;
                        // cout<<"Child : "<<in_time[child]<<endl;
                        // cout<<"Vertex : "<<in_time[vertex]<<endl;
                        if(parent[vertex] != i){
                            return true;
                        }
                    }
                    else if(adjacency_Matrix[vertex][i] == 1 && color[i] == 0){
                        // cout<<"Pushing into the stack "<<child<<endl;
                        parent[i] = vertex;
                        DFS_stack.push(i);
                    }
                }
            }
        }
        return false;
    }
    int inDegree(Vertex v){
        int vertex = v.getData();
        int inD = 0;
        for(int i = 0; i < adjacency_Matrix.size(); i++){
            if(adjacency_Matrix[i][vertex] == 1) inD++; 
        }
        return inD;
    }
    int OutDegree(Vertex v){
        int vertex = v.getData();
        int outD = 0;
        for(int i = 0; i < adjacency_Matrix[vertex].size(); i++){
            if(adjacency_Matrix[vertex][i] == 1) outD++; 
        }
        return outD;
    }
};
/*Define the derived classes here*/


/* DO NOT CHANGE THE CODE BELOW */
int main()
{
  int N;
  cin >> N;
  Graph * g;
  int command;
  const int SPARSITYRATIO = 5;
  for (int i = 0; i < N; i++)
  {
    cin >> command;
    switch (command)
    {
      case 1: /* initialize number of vertices and edges */
      {
        int nv,ne;
        cin >> nv >> ne;
        if (ne/nv > SPARSITYRATIO)
          g = new GraphUsingMatrix(nv,ne);
        else
          g = new GraphUsingList(nv,ne);
        break;
      }
      
      case 2: /* Add edge */
      {
        int v,w;
        cin >> v >> w;
        g->addEdge(Edge(Vertex(v), Vertex(w)));
        break;
      }
      
      case 3: /* Reachability query */
      {
        int v,w;
        cin >> v >> w;
        cout << g->reach(Vertex(v), Vertex(w)) << endl;
        break;
      }

      case 4: /* Detect Cycle */
      {
        cout << g->detectCycle() << endl;
        break;
      }
        
      case 5: /* In-degree */
      {
        int v;
        cin >> v;
        cout << g->inDegree(Vertex(v)) << endl;
        break;
      }

      case 6: /* Out-degree */
      {
        int v;
        cin >> v;
        cout << g->OutDegree(Vertex(v)) << endl;
        break;
      }
      
      default:
        break;
    }
  }
}