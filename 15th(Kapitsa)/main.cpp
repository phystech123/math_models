#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include <nlohmann/json.hpp> //import json as new type
#include<typeinfo>

using namespace std;
using json = nlohmann::json; //renaming namespace

// ------------------------- declaration of functions -----------------------------------
void sep(double* arr, int N, double h);
// void eyler(double* arr, int N, double* X, double* V);
void entry(double* X, double* Y, int N, string FILE);
// void hoin(double* arr, int N, double* X, double* V);
void RK4(double* arr, int N, double* , double*);

// ------------------------------------ parameters of system -----------------------------
double nu = 1000;
double l = 10;
double a = 0.1;
double g = 9.81;
double m = 2;

//-------------------------------- main --------------------------------------------------
int main(int argc, char* argv[]){
    if(argc != 2) return 1;   // bad check
    // cout << argv[1]<< endl;
    ifstream f(argv[1]);  // read config
    json data = json::parse(f);

    double h = data["h"];  // renaming of param
    const int N = data["N"];
    
    double* arr = new double[N];  // partitioning grid
    sep(arr, N, h);

    double* phi = new double[N];   // arrays of values
    double* omega = new double[N];
    phi[0] = data["phi"]; // initial conditions
    omega[0] = data["omega"];

    // choice of algo
    if(data["algo"] == "eyler"){
        // eyler(arr, N, phi, omega);
    }
    else if(data["algo"] == "hoin"){
        // hoin(arr, N, phi, omega);
    }
    else if(data["algo"] == "RK4"){
        RK4(arr, N, phi, omega);
    }

    json files = data["files"][0]; // not necessarily but makes easier

    entry(arr, phi, N, files["phi"]); // output
    entry(arr, omega, N, files["omega"]);
    
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



// euler method
// void eyler(double* arr, int N, double* phi, double* omega, double){
//     for(int i = 1; i < N; i++){
//         // x(i+1) = xi + dT*Vi
//         // V(i+1) = v(i) - w**2*x
//         phi[i] = phi[i-1] + (arr[i] - arr[i-1])*omega[i-1];
//         omega[i] = omega[i-1] - (arr[i] - arr[i-1])*pow(W, 2) * phi[i-1];
//     }
// }

// hoin method
// void hoin(double* arr, int N, double* X, double* V){
//         for(int i = 1; i < N; i++){
//         // x(i+1) = xi + dT*Vi
//         // V(i+1) = v(i) - w**2*x
//             X[i] = X[i-1] + (arr[i] - arr[i-1])*(V[i-1] + V[i-1] - (arr[i] - arr[i-1])*pow(W, 2) * X[i-1])/2;
//             V[i] = V[i-1] - (arr[i] - arr[i-1])*pow(W, 2) * (X[i-1] + X[i-1] + (arr[i] - arr[i-1])*V[i-1])/2; 
//         } 
// }



// Runge-Kutta method of order 4 (wrong realization)
void RK4(double* arr, int N, double* phi, double* omega){

    for(int i = 1; i < N; i++){
// ---------------------------------------------------------------
        double h = arr[i] - arr[i-1];

        double k1_phi = h*(omega[i-1]);
        double k1_omega = h*(-1*(a*pow(nu,2)*cos(nu*arr[i-1])+g) * sin(phi[i-1]) / l);

        double k2_phi = h*(omega[i-1] + k1_omega/2.);
        double k2_omega = h*(-1*(a*pow(nu,2)*cos(nu*(arr[i-1]) + h/2.)+g) * sin(phi[i-1] + k1_phi/2.) / l);

        double k3_phi = h*(omega[i-1] + k2_omega/2.);
        double k3_omega = h*(-1*(a*pow(nu,2)*cos(nu*(arr[i-1]) + h/2.)+g) * sin(phi[i-1] + k2_phi/2.) / l);

        double k4_phi = h*(omega[i-1] + k3_omega);
        double k4_omega = h*(-1*(a*pow(nu,2)*cos(nu*(arr[i-1]) + h)+g) * sin(phi[i-1] + k3_phi) / l);

        phi[i] = phi[i-1] + (1/6.)*(k1_phi + 2*(k2_phi+k3_phi) + k4_phi);
        omega[i] = omega[i-1] + (1/6.)*(k1_omega + 2*(k2_omega+k3_omega) + k4_omega);
    }
}