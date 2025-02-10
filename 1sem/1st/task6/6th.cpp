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
    // cout<<n<<endl;
    ofstream f;
    f.open("main.txt", ios::out);
    for(int i = 1; i <=n; i++){
    f << i<<endl;
    }
    f.close();
    return 0;
}
