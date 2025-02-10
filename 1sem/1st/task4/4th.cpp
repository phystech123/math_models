#include<iostream>
#include<fstream>
#include<array>
// #include<list>
#include<vector>
// #include<string>
// #include<cmath>
// #include<typeinfo>
using namespace std;




int main(){
    ofstream f;
    f.open("main.txt", ios::out);
    for(int i = 1; i <=30; i++){
    f << i<<endl;
    }
    f.close();
    return 0;
}

