#include<iostream>
using namespace std;
#include<string>

int countSubStrings(string str,int st,int end,int count){
    if(st>end) return count;
    if(str[st]==str[end]){
        count++;
    }
    return countSubStrings(str,st+1,end-1,count);
}

int main(){
    string str="abaaac";
    int st=0;
    int end=str.size()-1;
    int count=0;
    cout<<countSubStrings(str,st,end,count);
}