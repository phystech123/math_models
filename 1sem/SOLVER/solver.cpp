#include<map>
#include<array>
#include<iostream>
#include<string>
#include<nlohmann/json.hpp>
#include"equations.hpp"
#include"solver.hpp"

// using namespace std;
using json = nlohmann::json;





Solver::Solver(equation_base *const equation, json configuration):equation{equation}, configuration{configuration}{
    Parser();
    Evolution();
}

Solver::~Solver(){

}

void Solver::Evolution(){
    //underdefine
    unsigned N = number_of_iterations;

    //create
    double** X = new double*[dim];
    for(int i = 0; i < dim; i++){
        X[i] = new double[N];
        X[i][0] = conditions[i]; //initial conditions
    }
    double* t = new double[N];

    //main
    switch (method)
    {
    case Method::Euler:
        Euler(X, t);
        break;
    case Method::Hoyne:
        Hoyne(X, t);
        break;
    case Method::Runge_Kutta_45:
        Runge_Kutta_45(X, t);
        break;
    default:
        std::cout << "WRONG METHOD!";
        return;
    }



    // delete
    for(int i = 0; i < dim; i++){
        delete[] X[i];
    }
    delete[] X;
    delete[] t;
}

void Solver::AFC(...){

}

void Solver::Partitioning(){

}


void Solver::Runge_Kutta_45(double** X, double* t){
    double *k1, *k2, *k3, *k4;
    k1 = k2 = k3 = k4 = nullptr;
    for(int i = 1; i < number_of_iterations; i++){
        k1 = 
        k2 = 
        k3 = 
        k4 = 
        X[i] = X[i-1] + (t[i]-t[i-1])/6.*(k1+k2+k3+k4);
    }


}

double Solver::Get_amlitude(){

}

void Solver::Parser(){
    parameters = configuration["parameters"];
    conditions = configuration["conditions"];

    fineness = configuration["fineness"];
    number_of_iterations = configuration["number_of_iterations"];
    path_to_save = configuration["path_to_save"];

    int method_ = configuration["method"];
    switch (method_)
    {
    case 0:
        method = Method::Runge_Kutta_45;
        break;
    case 1:
        method = Method::Hoyne;
        break;
    case 2:
        method = Method::Euler;
        break;
    default:
        std::cout << "no one appropriate method" << std::endl;
        break;
    }

    dim = equation->get_dim();
}

void Solver::Print_Evolution(double *const, double *const, unsigned){

}
