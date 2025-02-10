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
    vector<float> vec;
    int n = atoi(argv[1]);
    for(int i = 0; i < n; i++){
        vec.push_back(1./(i+1));
    }
    ofstream file;
    file.open("main.bin", ios_base::binary);
    for(float i:vec){
        file.write((char*)&i, sizeof(float));
    }
    file.close();
    return 0;
}
