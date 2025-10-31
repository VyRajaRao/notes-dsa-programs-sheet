#include<iostream>
#include<vector>
#include<bits/stdc++.h>
using namespace std;
bool isSafe(vector<vector<char>> board,int row, int col, int n){
    //horizontal check
    for(int j=0;j<n;j++){
        if(board[row][j]=='Q'){
            return false;
        }
    }
    //vertical check
    for(int i=0;i<n;i++){
        if(board[i][col]=='Q'){
            return false;
        }
    }
    //left diagonal
    for(int i=row,j=col; i>=0&&j>=0; i--,j--){
        if(board[i][j]=='Q'){
            return false;
        }
    }
    //right diagonal
    for(int i=row,j=col; i>=0 && j<n; i--,j++){
        if(board[i][j]=='Q'){
            return false;
        }
    }
    return true;
}

void printQueens(vector<vector<char>> board, int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"-----------------------\n";
}
bool nQueens(vector<vector<char>> board, int row,int n){
    
    if(row==n){
        return 1;
    }
    int count=0;
    for(int j=0;j<n;j++){
        if(isSafe(board,row,j,n)){
            board[row][j]='Q';
            count+=nQueens(board,row+1,n);
            board[row][j]='.';
        }
    }
    if(count!=0){
        return true;
    }
    return false;
}
int main(){
    vector<vector<char>> board;
    int n=10;
    for(int i=0;i<n;i++){
        vector<char> newRow;
        for(int j=0;j<n;j++){
            newRow.push_back('.');
        }
        board.push_back(newRow);
    }
    
    cout<< nQueens(board,0,n);
}