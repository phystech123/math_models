#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include <nlohmann/json.hpp>
#include<typeinfo>

using namespace std;
using json = nlohmann::json;

class fuu{
public:
    double r = 0;
    int N = 0;
    double* x = new double[N]{};
    

    fuu(int n, double r, double x_0):r{r}, N{n}{
        x[0] = x_0;
    }

    void ff(){
        for(int i = 1; i < N; i++){
            x[i] = r * x[i-1] * (1 - x[i-1]);
        }
    }

    void print(){
        ofstream f("data/1.csv");
        f << "i,x\n";
        for(int i = 0; i < N; i++){
            f << i << "," << x[i] << "\n";
        }
    }    
};

int main(int argc, char* argv[]){
    double r = atof(argv[1]);
    double x = atof(argv[2]);
    int N = 200;
    
    fuu o(N, r, x);
    o.ff();
    o.print();
    cout<<r<<' '<<x;    
}