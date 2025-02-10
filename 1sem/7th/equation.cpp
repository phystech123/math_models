#include"equation.hpp"
#include<cmath>
#include<nlohmann/json.hpp> //import json as new type
using namespace std;
using json = nlohmann::json; //renaming namespace


void f_1(double* X, double t, double* X_, int dim, json data){
    X_[0] = X[1];
    X_[1] = -1*pow((double)data["params"][0], 2)*X[0];
    return;
}