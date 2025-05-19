#include<iostream>
#include<random>
#include<vector>
#include<iterator>
#include<algorithm>
#include<lapacke.h>

using namespace std;

double t=0;
const double rep=10000;



class coord{
    public:
    double a, b;
    coord(double x, double y):a{x}, b{y}{}
    ~coord(){}
    coord operator+(coord sec){
        return coord(this->a+sec.a, this->b+sec.b);
    }
    coord operator-(coord sec){
        return coord(this->a-sec.a, this->b-sec.b);
    }
    float operator*(coord sec){
        return this->a*sec.a + this->b*sec.b;
    }
    coord& operator=(coord sec){
        this->a = sec.a;
        this->b = sec.b;
        return *this;
    }
};
coord operator*(double t, coord X){
    return coord(coord(X.a*t, X.b*t));
}
coord operator*(coord X, double t){
    return coord(coord(X.a*t, X.b*t));
}
coord operator/(coord X, double t){
    return coord(coord(X.a/t, X.b/t));
}



class foton{
public:
    vector<coord> coor;
    vector<coord> speed;
    foton(double a, double b,
        double c, double d){
            coor[0].a = a;
            coor[0].b = b;
            speed[0].a = c;
            speed[0].b = d;
        }
    ~foton(){}
};

class bond_p{
    public:
        static const int m = 2;
        static const int n = 2;
        double A,B,C,D,E,F;
        bond_p(double a, double b,
            double c, double d, double e, double f):A{a}, B{b}, C{c}, D{d}, E{e}, F{f}{}
        ~bond_p(){}
        double check(double x, double y){
            return A*pow(x,2) + 2*B*x*y + C*pow(y,2) + D*x + E*y + F;
        }
    };

class trace{
    double rep = 1e5;
    double t = 1e-3;
    vector<foton> light;
    vector<bond_p> bond;
    trace(vector<foton> light, vector<bond_p> bond):light{light}, bond{bond}{}
    ~trace(){}

    void solve(){
        for(int i = 1; i < rep; i++){
            for(foton fot:light){
                coord temp = fot.coor[i-1]+fot.speed[i-1]*t;
                for(bond_p b: bond){
                    if(b.check(fot.coor[i-1].a, fot.coor[i-1].b)*b.check(temp.a, temp.b) < 0){
                        // с помощью лапака ищем перечение, потом по формуле из жпт отражаем скорости
                    }
                    else{
                        fot.coor[i] = temp;
                        fot.speed[i]=fot.speed[i-1];
                    }
                }
            }
        }
        return;
    }
};


int main(){
    
    return 0;
}


/*
решаем так:
в дискретном времени проверяем на гран условия
когда графн условия решаем lapacke
хэндлим дальше
*/
