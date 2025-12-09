#include<iostream>
#include<vector>
#include<bits/stdc++.h>
using namespace std;

class SegmentTree {
    vector<int> tree;
    int n;

    int rangeMaxUtil(int qi, int qj, int si, int sj, int node) {
        if(sj < qi || si > qj) {
            return INT_MIN;
        } 
        if(si >= qi && sj <= qj) {
            return tree[node];
        }
        int mid = si + (sj - si) / 2;
        return max(rangeMaxUtil(qi, qj, si, mid, 2*node+1), 
                   rangeMaxUtil(qi, qj, mid+1, sj, 2*node+2));

    }

    void rangeUpdateUtil(int idx, int newVal, int st, int end, int node) {
        if(st == end) {
            tree[node] = newVal;
            return;
        }
        int mid = st + (end - st) / 2;
        if(st >= idx && idx <= mid) {
            rangeUpdateUtil(idx, newVal, st, mid, 2*node+1);
        } else {
            rangeUpdateUtil(idx, newVal, mid+1, end, 2*node+2);
        }

        tree[node] = max(tree[2*node+1], tree[2*node+2]);
    }

public:
    SegmentTree(vector<int> &arr) {
        n = arr.size();
        tree.resize(4*n);
        buildSTree(arr, 0, n-1, 0);
    }

    void buildSTree(vector<int> &arr, int st, int end, int node) {
        if(st == end) {
            tree[node] = arr[st];
            return;
        }

        int mid = st + (end - st) / 2;
        buildSTree(arr, st, mid, 2*node+1);
        buildSTree(arr, mid+1, end, 2*node+2);

        tree[node] = max(tree[2*node+1], tree[2*node+2]);
    }

    void printTree() {
        for(int i = 0; i < tree.size(); i++) {
            cout << tree[i] << " ";
        }
        cout << endl;
    }

    int rangeMaxQuery(int qi, int qj) {
        return rangeMaxUtil(qi, qj, 0, n-1, 0);
    }

    void rangeUpdate(int idx, int newVal) {
        return rangeUpdateUtil(idx, newVal, 0, n-1, 0);
    }
};

int main() {
    vector<int> arr = {1, 2, 13, 4, 5, 6, 7, 8};
    SegmentTree segTree(arr);

    cout << "Max value in range (2, 5): " << segTree.rangeMaxQuery(2, 5) << endl; // Output: 6
    
    segTree.printTree();
    segTree.rangeUpdate(3, 15); // Update index 3 to value 15
    cout << "Max value in range (2, 5) after update: " << segTree.rangeMaxQuery(2, 5) << endl; // Output: 15
    segTree.printTree();
    return 0;
}