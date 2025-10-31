// #include<iostream>
// using namespace std;
// int pow(int x,int n) {
//     if(n==0) return 1;
//     return x*pow(x,n-1);
// }
// int main(){
//     cout<<pow(8,4);
// }
#include <iostream>
using namespace std;

int main() {
    // Write your code here
    int num;
    cin >> num;
    int i=1;
    
    while(i!=num){
        int a=i*i;
        cout << a << " ";
        i++;
    }
    cout << i*i;
    return 0;
}