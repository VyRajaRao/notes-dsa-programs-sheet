#include<iostream>
using namespace std;
#include<vector>

vector<int> allOccurence(vector<int> arr,vector<int> ans,int key,int i){
    if(i==arr.size()){
        if(ans.empty()) ans.push_back(-1);
        return ans;
    }
    if(arr[i]==key){
        ans.push_back(i);
    }
    return allOccurence(arr,ans,key,i+1);
}

int main(){
    vector<int> arr={3,4,2,1,12,2,2,3,4};
    vector<int> ans = allOccurence(arr,{},45,0);
    for(int idx : ans) {
        cout << idx << " ";
    }
    cout << endl;
}