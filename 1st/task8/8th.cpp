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
    int n = atoi(argv[1]);
    array<int, 10> arr{};
    array<int, 2> temp{1,1};
    for (n; n > 8; n-=8){
        arr[0] = temp[0];
        arr[1] = temp[1];

        for (int i = 2; i < 10; i++)
            arr[i] = arr[i-1] + arr[i-2];

        temp[0] = arr[8];
        temp[1] = arr[9];

        for(int i = 0; i < 8; i++)
            cout<<arr[i]<<endl;
    }

    
    {arr[0] = temp[0];
    arr[1] = temp[1];

    for (int i = 2; i < n; i++)
        arr[i] = arr[i-1] + arr[i-2];

    for(int i = 0; i < n; i++)
        cout<<arr[i]<<endl;
    }
    

    return 0;
}
