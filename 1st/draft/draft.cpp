#include<iostream>
#include<fstream>
using namespace std;
int main(){
 
    ifstream file;
    float n;
    file.open("main.bin", ios_base::binary);
    for(int i = 0; i<8; i++){
    file.read((char*)&n, sizeof(float));
    cout<<n<<endl;}
    file.close();
    return 0;
}