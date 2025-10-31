#include<iostream>
#include<bits/stdc++.h>
#include<vector>
using namespace std;

class Solution {
public:
    bool check(vector<int>& nums) {
        int n=nums.size();
        int cnt=0;
        for(int i=1;i<n;i++){
            if(nums[i-1]>nums[i]){
                return ++cnt;
            }
        }
        if(nums[n-1]>nums[0]){
            return ++cnt;
        }
        return cnt;
    }
};

int main(){
    Solution s;
    vector<int>arr={7,8,9,1,2,3};
    cout<<s.check(arr);
}