#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include <nlohmann/json.hpp> //import json as new type
#include<typeinfo>

using namespace std;
using json = nlohmann::json; //renaming namespace

// ----------------------------------------- new interface-------------------------------------------

// ------------------------- declaration of functions -----------------------------------
void sep(double* arr, int N, double h);
void eyler(double* arr, int N, double* X, double* V);
void entry(double* X, double* Y, int N, string FILE);
void hoin(double* arr, int N, double* X, double* V);
void RK4(double* arr, int N, double* X, double* V);
double Amlitude(double* arr, int N, double* X);

// ------------------------------------ parameters of system -----------------------------
double W = 0.;
// double g = 0.5;
double g = 0.;
double fr = 0.;
double Ampl = 0;

//-------------------------------- main --------------------------------------------------
int main(int argc, char* argv[]){
    if(argc != 3) return 1;   // bad check
    // cout << argv[1]<< endl;
    ifstream f(argv[1]);  // read config
    json data = json::parse(f);

    W = data["W"];
    g = data["g"];
    // fr = data["omega"];
    Ampl = data["Ampl"];
    fr = atof(argv[2]);

    double h = data["h"];  // renaming of param
    const int N = data["N"];
    
    double* arr = new double[N];  // partitioning grid
    sep(arr, N, h);

    double* X = new double[N];   // arrays of values
    double* V = new double[N];
    
    X[0] = data["X0"]; // initial conditions
    V[0] = data["V0"];

    // choice of algo
    if(data["algo"] == "eyler"){
        eyler(arr, N, X, V);
    }
    else if(data["algo"] == "hoin"){
        hoin(arr, N, X, V);
    }
    else if(data["algo"] == "RK4"){
        RK4(arr, N, X, V);
    }

    // json files = data["files"][0]; // not necessarily but makes easier

    // entry(arr, X, N, files["x"]); // output
    // entry(arr, V, N, files["v"]);
    
    int ampl = Amlitude(arr, N, X);
    cout << ampl << " ";


    delete[] arr; // clear
    delete[] X;
    delete[] V;
    return 0;
}





// grid
void sep(double* arr, int N, double h){
    arr[0] = 0;
    for(int i = 1; i < N; i++){
        arr[i] = arr[i-1] + h;
    }
}

// output
void entry(double* X, double* Y, int N, string FILE){ 
    ofstream file;
    file.open(FILE);
    file << "t; x\n";
    for(int i =0; i < N; i++){
        file << X[i]<<"; "<<Y[i]<<"\n";
    }
    file.close();
}

double get_ampl(){
    double ampl = 0;
    

    return ampl;
}



// euler method
void eyler(double* arr, int N, double* X, double* V){
    for(int i = 1; i < N; i++){
        // x(i+1) = xi + dT*Vi
        // V(i+1) = v(i) - w**2*x
        double h = arr[i] - arr[i-1];
        X[i] = X[i-1] + h*V[i-1];
        V[i] = V[i-1] - h*(pow(W, 2) * X[i-1] + 2*g*V[i-1] - Ampl * sin(fr*arr[i-1]));
    }
}

// hoin method
void hoin(double* arr, int N, double* X, double* V){
        for(int i = 1; i < N; i++){
        // x(i+1) = xi + dT*Vi
        // V(i+1) = v(i) - w**2*x
            double h = arr[i] - arr[i-1];
            X[i] = X[i-1] + h*(V[i-1] + V[i-1] + h*(-pow(W, 2) * X[i-1] - 2*g*V[i-1]) + Ampl * sin(fr*arr[i-1]))/2;
            V[i] = V[i-1] - h*(pow(W, 2) * ((X[i-1] + X[i-1] + h*V[i-1])/2) +2*g*(V[i-1] + V[i-1] - h*(pow(W, 2) * X[i-1] + 2*g*V[i-1] - Ampl * sin(fr*arr[i-1])))/2 - Ampl * sin(fr * (arr[i-1] + arr[i])/2)); 
        } 
}

// Runge-Kutta method of order 4
void RK4(double* arr, int N, double* X, double* V){

    for(int i = 1; i < N; i++){
// ---------------------------------------------------------------
        double h = arr[i] - arr[i-1];

        double k1_x = h*V[i-1];
        double k1_v = h*(-pow(W, 2)*(X[i-1]) - 2*g*V[i-1] + Ampl * sin(fr*arr[i-1]));

        double k2_x = h*(V[i-1] + k1_v/2.);
        double k2_v = h*(-pow(W, 2)*(X[i-1] + k1_x/2.) - 2*g*(V[i-1] + k1_v/2.) + Ampl * sin(fr*(arr[i-1] + h/2.)));

        double k3_x = h*(V[i-1] + k2_v/2.);
        double k3_v = h*(-pow(W, 2)*(X[i-1] + k2_x/2.) - 2*g*(V[i-1] + k2_v/2.) + Ampl * sin(fr*(arr[i-1] + h/2.)));

        double k4_x = h*(V[i-1] + k3_v);
        double k4_v = h*(-pow(W, 2)*(X[i-1] + k3_x)  - 2*g*(V[i-1] + k3_v) + Ampl * sin(fr*(arr[i-1] + h)));

        X[i] = X[i-1] + (1/6.)*(k1_x + 2*(k2_x+k3_x) + k4_x);
        V[i] = V[i-1] + (1/6.)*(k1_v + 2*(k2_v+k3_v) + k4_v);
    }
}


double Amlitude(double* arr, int N, double* X){
    int iter = 0;
    for(int i = 0; i < N; i++){
        iter = 0;
        for(int j = 0; j < 10; j++){
            if((X[i] - X[i]) < 1e-10){
                ++iter;
            }
        }
        if(iter == 100){
            return X[i];
        }
    }
    return -1;
}



// v` = -w**2x - 2gv
// x` = v