#include<iostream>
#include <ostream>
#include<vector>
#include<random>
// #include<nlohmann/json.hpp>
#include<fstream>
#include<cmath>

using namespace std;
// using json = nlohmann::json;

namespace ramb{
    bool ramb_one(float& val){
        static random_device r;
        static default_random_engine e1(r());
        static bernoulli_distribution dist(0.5);
        static uniform_int_distribution<int> ampl(0, 20);
        val += ampl(e1)*2*(0.5 - dist(e1));

        // // штука для того на каком шаге упадет матрос
        // if(val < 0){
        //     return 1;
        // }
        // else{
        //     cout<<val<<endl;
        // }
        // return 0;

        // // for seeing
        // cout<<val<<endl;

        return 0;
    }

    void ramb(float& val, int n){
        for(int i = 0; i < n; i++){
            if(ramb_one(val) == 1){
                cout<<"break";
                break;
            }
        }
    }
}

namespace anal{
    const int STEPS = 1000;
    void main(void func(float&, int), float& val, int RES){
        float mean[STEPS] = {};
        float abs_mean[STEPS] = {};
        float sq_mean[STEPS] = {};
        float begin = val;
        ofstream f("./mean.txt");
        f<<"num,mean,abs_mean,sq_mean\n";
        for(int i = 0; i < RES; i++){
            for(int j = 0; j < STEPS; j+=100){
                ramb::ramb(val, j);
                mean[j] += val-begin;
                abs_mean[j] += abs(val-begin);
                sq_mean[j] += pow(val-begin, 2);
            }
            val = begin;
        }
        for(int j = 0; j < STEPS; j+=100){
            mean[j] /= RES;
            abs_mean[j] /= RES;
            sq_mean[j] = sqrt(sq_mean[j]/RES);
            f<<j<<", "<<mean[j]<<", "<<abs_mean[j]<<", "<<sq_mean[j]<<'\n';
        }
        val = begin;
        return ;
    }

    void local(float val){
        float begin = val;
        ofstream f("./local.txt");
        f<<"step,value\n";
        for(int i = 0; i < STEPS; i++){
            ramb::ramb_one(val);
            f<<i<<", "<<val<<'\n';
        }
        val = begin;
        return ;
    }

    void std_err(float val, int maxRES){
        float begin = val;
        int step = 100;
        ofstream f("./std_err.txt");
        f<<"num,err\n";
        float temp[] = {0, 0};
        for(int RES = 1; RES < maxRES; RES+=1000){
            for(int j = 0; j < 2; j++){
                for(int i = 0; i < RES; i++){
                    ramb::ramb(val, step);
                    temp[j]+=val;
                    val = begin;
                }
            }
            temp[0]/=RES;
            temp[1]/=RES;
            f<<RES<<", "<<abs(temp[0] - temp[1])<<'\n';
            temp[0] = 0;
            temp[1] = 0;
            val = begin;
        }
        val = begin;
        return ;
    }

    void limit(float val){
        int step = 10000;
        float begin = val;
        ofstream f("./limit.txt");
        float temp = 0;
        for(int j = 0; j < 10000; j+=1){
            ramb::ramb(val, step);
            f<<val-begin<<", ";
            val = begin;
        }
        return ;
    }
}


int main(int argc, char* argv[]){
    // if(argc != 3) return 1;   // bad check
    // // cout << argv[1]<< endl;
    // ifstream f(argv[1]);  // read config
    // json data = json::parse(f);
    // // cout << data["n"]<<'\n';

    float val = 100;
    int RES = 10000;
    // anal::main(ramb::ramb, val, RES);
    // anal::local(val);
    // anal::std_err(val, 50000);
    // anal::limit(val);
    return 0;
}