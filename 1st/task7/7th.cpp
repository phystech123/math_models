#include<iostream>
#include<fstream>
#include<array>
// #include<list>
#include<vector>
// #include<string>
// #include<cmath>
// #include<typeinfo>
using namespace std;





int main(int argc, char *argv[]){
    const int n = atoi(argv[1]);
    int arr[n];
    ofstream f;
    f.open("main.txt", ios::out);
    if(n == 1){
        f<<"1 1";
    }
    else{
        arr[0] = 1;
        arr[1] = 1;
        f<<"1 1"<<endl<<"2 1"<<endl;

        for(int i = 2; i <n; i++){
            arr[i] = arr[i-1] + arr[i-2];
            int t = arr[i];
            f<<i+1<<" "<<t<<endl;
        }
    }

    f.close();
    return 0;
}


