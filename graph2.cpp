#include<iostream>
#include<bits/stdc++.h>
#include<queue>
using namespace std;

class Graph{
    int V;
    list<int>* l;
public:
    Graph(int V) {
        this->V = V;
        l = new list<int> [V];
    }

    void addEdges(int u, int v) {
        l[u].push_back(v); 
        l[v].push_back(u);
    }

    void print() {
        for(int u=0; u<V; u++) {
            list<int> neighbors = l[u];
            cout << u << ": " << " ";
            for(int v : neighbors) {
                cout << v << " ";
            }
            cout << endl;
        }
    }

    void dfs_helper(int u, vector<bool> &visit) {
        visit[u] = true;
        cout << u << " ";
        list<int> neighbors = l[u];
        for(int v : neighbors) {
            if(!visit[v]) {
                dfs_helper(v, visit);
            }
        }
    }
    void dfs() {
        vector<bool> visit(V, false);
        for(int i=0; i<V; i++) {
            if(!visit[i]) {
                dfs_helper(i, visit);
                cout << endl;
            }
        }
    }
    void bfsHelper(int st, vector<bool> &visit) {
        queue<int> q;
        q.push(st);
        visit[st] = true;
        while(q.size() > 0) {
            int u = q.front();
            q.pop();
            cout << u << " ";
            list<int> neighbors = l[u];
            for(int v : neighbors) {
                if(!visit[v]) {
                    visit[v] = true;
                    q.push(v);
                }
            }   
        }
    }

    void bfs() {
        vector<bool> visit(V, false);
        for(int i=0; i<V; i++) {
            if(!visit[i]) {
                bfsHelper(i, visit);
                cout << endl;
            }
        }
    }
};

int main() {
    Graph graph(10);

    graph.addEdges(6,1);
    graph.addEdges(6,4);
    graph.addEdges(4,9);
    graph.addEdges(4,3);
    graph.addEdges(3,8);
    graph.addEdges(3,7);
    graph.addEdges(2,5);
    graph.addEdges(2,0);

    // graph.print();

    graph.bfs();
}