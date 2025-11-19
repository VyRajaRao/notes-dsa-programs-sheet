#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class Graph{
    int V;
    list<pair<int, int>>* l;
public:
    Graph(int V) {
        this->V = V;
        l = new list<pair<int, int>> [V];
    }

    void addEdges(int u, int v, int wt) {
        l[u].push_back(make_pair(v, wt)); 
    }

    void print() {
        for(int u=0; u<V; u++) {
            list<pair<int, int>> neighbors = l[u];
            cout << u << ": " << " ";
            for(pair<int, int> v : neighbors) {
                cout << "(" << v.first << "," << v.second <<") ";
            }
            cout << endl;
        }
    }
    void dfs_helper(int u, vector<bool> &vist) {
        vist[u] = true;
        cout << u << " ";
        list<int> neighbors = l[u];
        for(pair<int, int> v : neighbors) {
            if(!visit[v.first]) {
                dfs_helper(v.first, visit);
            }
        }
    }
    void dfs() {
        vector<bool> visit(V, false);
        for(int i=0; i<V; i++) {
            if(!visit[i]) {
                dfs_helper(i, visit);
            }
        }
    }
};
int main() {
    Graph graph(5);

    graph.addEdges(0,1,5);
    graph.addEdges(1,0,5);
    graph.addEdges(1,2,1);
    graph.addEdges(1,3,3);
    graph.addEdges(2,1,1);
    graph.addEdges(2,3,1);
    graph.addEdges(2,4,2);
    graph.addEdges(3,2,1);
    graph.addEdges(3,1,3);
    graph.addEdges(4,2,2);
    graph.print();
}