#pragma once
#include<map>
#include<array>
#include<string>
#include<nlohmann/json.hpp>
#include"equations.hpp"

using json = nlohmann::json;

class Solver{
public:
    Solver(equation_base *const, json);
    // не нужное:
    // Solver(const Solver&);
    // Solver(Solver&&);
    // Solver& operator=(const Solver&);
    // Solver& operator=(Solver&&);
    ~Solver();

    void Evolution();
    void AFC(...);

    void Partitioning();
    
    void Partitioning(double *const, unsigned);
    void Euler(double**, double*);
    void Hoyne(double**, double*);

    void Runge_Kutta_45(double**, double*);

    double Get_amlitude();

    void Parser();
    void Print_Evolution(double *const, double *const, unsigned);

private:
    enum class Method{
        Runge_Kutta_45, Euler, Hoyne
    };

    equation_base* equation;
    json configuration;

    map<string, double> parameters;
    map<int, double> conditions;

    Method method;
    double fineness;
    unsigned number_of_iterations;

    string path_to_save;
    
    int dim;
};