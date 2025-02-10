#include<iostream>
#include<fstream>
#include<array>
// #include<list>
#include<vector>
// #include<string>
// #include<cmath>
// #include<typeinfo>
using namespace std;





int main(int argc, char* argv[]){
    const int n = atoi(argv[1]);
    float arr[n];
    for(int i = 1; i <= n; i++){
        arr[i-1] = 1.0/i;
    }
    for(float i:arr){
        cout<<scientific<<i<<endl;
    }
    return 0;
}
