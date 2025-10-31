// #include<iostream>
// using namespace std;
// int sum(int n){
//     if(n<0) return -1;
//     else if(n==0) return 0;
//     else return n+sum(n-1);
// }
// int main() {
//     cout<<sum(11);
// }

#include<iostream>
int pow(int x,int n){
    if(n==0) return 1;
    x*=x;
    return pow(x,n-1);
}
int main(){
    pow(8,4);
}