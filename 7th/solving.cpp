#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<nlohmann/json.hpp> //import json as new type
#include<typeinfo>

#include"solving.hpp"
#include"equation.hpp"

using namespace std;
using json = nlohmann::json; //renaming namespace




// euler method
void eyler(double* arr, int N, double** DATA, int dim, void (f)(double*,double,double*,int, json), json data){
    double* X = new double[dim];
    double* X_ = new double[dim];
    double h = 0;

    for(int i = 1; i < N; i++){
        for(int j = 0; j < dim; j++)
            X[j] = DATA[j][i-1];
        h = arr[i] - arr[i-1];
        f(X, arr[i-1], X_, dim, data);

        for(int j = 0; j < dim; j++)
            DATA[j][i] = X[j] + X_[j]*h;
    }

    delete[] X;
    delete[] X_;
    return;
}

// // hoin method
// void hoin(double* arr, int N, double** DATA, int dim, double* (f)(double*, int)){
//     double* X = new double[dim];
//     double* X_ = new double[dim];
//     double h = 0;

//     for(int i = 1; i < N; i++){
//         for(int j = 0; j < dim; j++)
//             X[j] = DATA[j][i-1];
//         h = arr[i] - arr[i-1];
//         X_ = f(X, dim);

//         for(int j = 0; j < dim; j++)
//             DATA[j][i] = X[j] + (X_[j])*h;
//     }

//     delete[] X;
//     delete[] X_;
//     return;




//             double h = arr[i] - arr[i-1];
//             X[i] = X[i-1] + h*(V[i-1] + V[i-1] - h*pow(W, 2) * sin(X[i-1]))/2;
//             V[i] = V[i-1] - h*pow(W, 2) * sin((X[i-1] + X[i-1] + h*V[i-1])/2); 
// }

// Runge-Kutta method of order 4 (wrong realization)
void RK4(double* arr, int N, double** DATA, int dim, void (f)(double*,double,double*, int, json), json data){
    double* X = new double[dim];
    double* Xk1 = new double[dim];
    double* Xk2 = new double[dim];
    double* Xk3 = new double[dim];
    double h;
    double* k1 = new double[dim];
    double* k2 = new double[dim];
    double* k3 = new double[dim];
    double* k4 = new double[dim];

    for(int i = 1; i < N; i++){
// ---------------------------------------------------------------
        h = arr[i] - arr[i-1];
        for(int j = 0; j < dim; j++)
            X[j] = DATA[j][i-1];

        f(X, arr[i-1], k1, dim, data);

        for(int j = 0; j < dim; j++) Xk1[j] = X[j] + h/2*k1[j];
        f(Xk1, arr[i-1]+h/2, k2, dim, data);

        for(int j = 0; j < dim; j++) Xk2[j] = X[j] + h/2*k2[j];
        f(Xk2, arr[i-1]+h/2, k3, dim, data);

        for(int j = 0; j < dim; j++) Xk3[j] = X[j] + h*k3[j];
        f(Xk3, arr[i-1]+h, k4, dim, data);

        for(int j = 0; j < dim; j++)
            DATA[j][i] = X[j] + h;
        
    }
    delete[] k1;
    delete[] k2;
    delete[] k3;
    delete[] k4;
    delete[] X;
    delete[] Xk1;
    delete[] Xk2;
    delete[] Xk3;
}

// grid
void sep(double* arr, int N, double h){
    arr[0] = 0;
    for(int i = 1; i < N; i++){
        arr[i] = arr[i-1] + h;
    }
}

// output
void entry(double** DATA, double* t, int dim, int N, json data){
    auto output = data["output_files"];
    for(int i = 0; i < dim; i++){
        double* data = DATA[i];
        ofstream file;
        file.open(output[i]);
        file << "t;x\n";
        for(int j =0; j < N; j++){
            file << t[j]<<"; "<<data[j]<<"\n";
        }
        file.close();
    }
}