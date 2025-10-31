// #include<iostream>
// int pow(int x,int n){
//     if(n==0) return 1;
//     x*=x;
//     return pow(x,n-1);
// }
// int main(){
//     pow(8,4);
// }
 #include <iostream>
using namespace std;
int fibo(int n){
    if(n==0||n==1){
        return n;
    }
    return fibo(n-1) + fibo(n-2);
}
int main() {
    int n;
    cin >> n;
    // Update your code below this line
    fibo(n);
    return 0;
}