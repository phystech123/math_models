#include<iostream>
#include<random>
#include<vector>
#include<iterator>
#include<algorithm>

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
    coord coor = {0,0};
    coord normal = {0,0};
    bond_p(double a, double b,
        double c, double d){
            coor.a = a;
            coor.b = b;
            normal.a = c;
            normal.b = d;
        }
    ~bond_p(){}
};

class boun_cond{
public:
    double width, lenght;
    // condition on bounder
    coord* check(coord c){
        // ...
        return nullptr;
    }
    coord* check(foton f, int i){
        coord c = f.coor[i-1];
        return check(c);
    }
};

class trace{
    boun_cond bound;
    vector<foton> light;
    trace(boun_cond bound,
        vector<foton> light):bound{bound}, light{light}{}
    ~trace(){}

    void solve(){
        for(int i = 0; i < rep; i++){
            for(foton f:light){
                coord c = f.coor[i-1] + f.speed[i-1]*t;
                coord* p_c = bound.check(c);
                if (p_c==nullptr){
                    f.coor[i] = c;
                    f.speed[i] = f.speed[i-1];
                }
                else{
                    coord p = *p_c;
                    double t_ = ((p-f.coor[i-1])*(p-f.coor[i-1]))/(f.speed[i-1]*f.speed[i-1]);
                    f.speed[i] = (2*(f.speed[i-1]*p)/(p*p))*p - f.speed[i-1];
                    f.coor[i] = f.speed[i]*(t-t_);
                }
            } 
        }
        return;
    }
};


int main(){
    
    return 0;
}
