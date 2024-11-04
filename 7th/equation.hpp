#pragma once
#include<nlohmann/json.hpp> //import json as new type
using namespace std;
using json = nlohmann::json; //renaming namespace

void f_1(double* X, double t,double* X_,  int dim, json data);