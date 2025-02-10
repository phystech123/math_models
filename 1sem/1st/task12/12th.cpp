#include<iostream>
#include<array>
#include<string>

using namespace std;

int main(){
    array<int, 8> arr {};
    for (int i=0;i<=65;i++){ // error
        arr[i] = i*i;
    }

    auto iter = arr.begin();
    auto end = arr.end();
    for (iter; iter!= end; iter++){    // solution
        cout<<*iter<<endl;   
    }
    return 0;
}
