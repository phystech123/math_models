#pragma once
#include<map>
#include<array>
using namespace std;

class equation_base{
public:
    equation_base();
    equation_base(const equation_base&);
    equation_base(equation_base&&);
    equation_base& operator=(const equation_base&);
    equation_base& operator=(equation_base&&);
    ~equation_base();
    double get_dim();
private:
    const static unsigned dim;
};




class Equation: public equation_base{

};