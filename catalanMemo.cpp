#include <iostream>
#include <vector>
using namespace std;

int catalan(int n, vector<int> &dp) {
    if(n == 1 || n == 0) {
        return 1;
    }
    if(dp[n] != -1) {
        return dp[n];
    }

    for(int i=0; i<n; i++) {
        dp[n] += catalan(i, dp) * catalan(n-i-1, dp);
    }
}

int main() {
    int n = 5;
    vector<int> dp(n + 1, -1);
    cout << "Catalan number C(" << n << ") is: " << catalan(n, dp) << endl;
    return 0;
}