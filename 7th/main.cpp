#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include <nlohmann/json.hpp> //import json as new type
#include<typeinfo>

#include"solving.hpp"
#include"equation.hpp"

using namespace std;
using json = nlohmann::json; //renaming namespace


//-------------------------------- main --------------------------------------------------
int main(int argc, char* argv[]){
    if(argc != 2) return 1;   // bad check
    ifstream f(argv[1]);  // read config
    json data = json::parse(f);
    cout << data["params"][0];

    double h = data["fineness"];  // renaming of param
    const int N = data["time_limit"];
    int dim = data["dim"];
    
    double* arr = new double[N];  // partitioning grid
    sep(arr, N, h);

    double** DATA = new double*[dim];
    for(int i = 0; i < dim;i++){
        DATA[i] = new double[N];
        DATA[i][0] = data["conditions"][i];
    }

    
    RK4(arr, N, DATA, dim, f_1, data);

    entry(DATA, arr, dim, N, data);

    delete[] arr; // clear
    for(int i = 0; i < dim; i++){
        delete[] DATA[i];
    }
    delete[] DATA;
    
    return 0;
}








