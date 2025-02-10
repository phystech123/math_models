#include<map>
#include<array>
#include<fstream>
#include<string>
#include<nlohmann/json.hpp>
#include"equations.hpp"
#include"solver.hpp"

using namespace std;
using json = nlohmann::json;

int main(int argc, char* argv[]){
    if(argc =! 2){return 1;}

    ifstream f(argv[1]);
    json data = json::parse(f);

    equation_base* ptr = nullptr;
    Equation equation;
    ptr = &equation;

    Solver solver(ptr, data);
    // solver.Evolution();
    // solver.AFC();

    return 0;
}