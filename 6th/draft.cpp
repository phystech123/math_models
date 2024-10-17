#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<nlohmann/json.hpp> //import json as new type
#include<typeinfo>
#include<vector>

using namespace std;
using json = nlohmann::json; //renaming namespace

class equality{
    string equation;
    equality(json config){
        equation = config["equation"];
    }
    ~equality(){

    }
    auto make_func(){
        if(equation == "simple_garmonic"){
            return simple_garmonic;
        }
        // else if(equation == ...){

        // }
        // else if(equation == ...){

        // }
    }
    double* simple_garmonic(double t){
        return()
    }

};

class counting{
    double* grid = nullptr;
    int order;
    double* params = nullptr;
    string algo;
    double h;
    int N;
    string* output_files = nullptr;
    double** arrays = nullptr;
    
    counting(json config){
        order = config["order"];
        N = config["N"];
        h = config["h"];
        algo = config["algo"];

        params = new double[order];
        for(int i = 0; i < order; i++){
            params[i] = config["params"][0][to_string(i)];
        }

        output_files = new string[order];
        for(int i = 0; i < order; i++){
            output_files[i] = config["output_files"][0][to_string(i)];
        }

        grid = new double[N];
        sep();

        arrays = new double*[order];
        for(int i = 0; i < order; i++){
            arrays[i] = new double[N];
        }
        

    }
    ~counting(){
        if(grid != nullptr) delete[] grid;
        if(params != nullptr) delete[] params;
        if(output_files != nullptr) delete[] output_files;
        // for(int i = 0; i < order; i++){
        //     delete[] arrays[i];
        // }
        // delete[] arrays;
    }
    
    void count(){
        if(algo == "eyler"){
        eyler();
    }
    else if(algo == "hoin"){
        hoin();
    }
    else if(algo == "RK4"){
        RK4();
    }
    }

    // grid
    void sep(){
        grid[0] = 0;
        for(int i = 1; i < N; i++){
            grid[i] = grid[i-1] + h;
        }
    }
    
    // euler method
    void eyler(){
        for(int i = 1; i < N; i++){
            // x(i+1) = xi + dT*Vi
            // V(i+1) = v(i) - w**2*x
            double h = grid[i] - grid[i-1];
            X[i] = X[i-1] + h*V[i-1];
            V[i] = V[i-1] - h*pow(W, 2) * sin(X[i-1]);
        }
    }

    
    // hoin method
    void hoin(){
            for(int i = 1; i < N; i++){
            // x(i+1) = xi + dT*Vi
            // V(i+1) = v(i) - w**2*x
                double h = grid[i] - grid[i-1];
                X[i] = X[i-1] + h*(V[i-1] + V[i-1] - h*pow(W, 2) * sin(X[i-1]))/2;
                V[i] = V[i-1] - h*pow(W, 2) * sin((X[i-1] + X[i-1] + h*V[i-1])/2); 
            } 
    }

    // Runge-Kutta method of order 4
    void RK4(){

        for(int i = 1; i < N; i++){
    // ---------------------------------------------------------------
            double h = grid[i] - grid[i-1];

            double k1_x = h*V[i-1];
            double k1_v = h*(-pow(W, 2)*sin(X[i-1]));

            double k2_x = h*(V[i-1] + k1_v/2.);
            double k2_v = h*(-pow(W, 2)*sin(X[i-1] + k1_x/2.));

            double k3_x = h*(V[i-1] + k2_v/2.);
            double k3_v = h*(-pow(W, 2)*sin(X[i-1] + k2_x/2.));

            double k4_x = h*(V[i-1] + k3_v);
            double k4_v = h*(-pow(W, 2)*sin(X[i-1] + k3_x));

            X[i] = X[i-1] + (1/6.)*(k1_x + 2*(k2_x+k3_x) + k4_x);
            V[i] = V[i-1] + (1/6.)*(k1_v + 2*(k2_v+k3_v) + k4_v);
        }
    }


};


class Matrix{
    double* arr;
    int order;
    Matrix(int N, int ord){
        arr = new double[N*N];
        order = ord;

    }
    ~Matrix(){
        delete[] arr;
    }
    double* operator*(double* X){
        double* Y = new double[order];
        for(int i = 0; i < order; i++){
            double sum = 0;
            for(int j = 0; j < order; j++){
                sum += arr[4*i + j] * X[j];
            }
            Y[i] = sum;
            sum = 0;
        }
        return Y;
    }
}






void entry(double* X, double* Y, int N, string FILE);

//-------------------------------- main --------------------------------------------------
int main(int argc, char* argv[]){
    if(argc != 2) return 1;   // bad check
    ifstream f(argv[1]);  // read config
    json config = json::parse(f);


    entry(grid, X, N, files["x"]); // output
    entry(grid, V, N, files["v"]);
    
    return 0;
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









