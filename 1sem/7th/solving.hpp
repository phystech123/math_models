#pragma once
#include<string>
#include<string>
#include <nlohmann/json.hpp> 
using namespace std;
using json = nlohmann::json; //renaming namespace


    
void eyler(double* arr, int N, double** DATA, int dim, void (f)(double*,double,double*,int, json), json);
// void hoin(double* arr, int N, double* X, double* V);
void RK4(double* arr, int N, double** DATA, int dim, void (f)(double*,double,double*, int, json), json);
void sep(double* arr, int N, double h);
void entry(double** DATA, double* t, int dim, int N, json data);