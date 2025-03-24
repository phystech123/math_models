#include <algorithm>
#include <array>
#include<iostream>
#include<cmath>
#include <iterator>
#include<vector>
#include<random>
#include<fstream>
#include<string>

// #include<pair>

using namespace std;

std::random_device r_;
std::default_random_engine e1(r_());
std::uniform_real_distribution<> dist1(0.1, 9.9);
std::uniform_real_distribution<> dist2(-1, 1);

class circle{
    public:
        int i;
        double R;
        double M;
        double* X;
        double* V;
        circle(double R, double M, double x_0, double v_0, int rep):R{R}, M{M}{
            X = new double[rep];
            V = new double[rep];
            X[0] = x_0;
            V[0] = v_0;
        }
        circle(){}
        ~circle(){
            // delete[] X;
            // delete[] V;
        }
};


class gas{
public:
    array<array<double, 2>, 2> CONF;

    const static int N = 3;
    int rep = 10000;
    double t = 0.001;

    vector<circle> AR;

    gas(){
        double R=0.1, M=1, r=0.1, m=1;
        CONF[0][0] = R;
        CONF[0][1] = M;
        CONF[1][0] = r;
        CONF[1][1] = m;

        vector<double> temp1;
        vector<double> temp2;
        // for(int i = 0; i < N; i++){
        //     temp1.push_back(dist1(e1));
        //     temp2.push_back(dist2(e1));
        // }
        temp1.push_back(4);
        temp1.push_back(5);
        temp1.push_back(6);
        temp2.push_back(1);
        temp2.push_back(0);
        temp2.push_back(-1);
        
        sort(temp1.begin(), temp1.end());

        AR.push_back(circle(0.1, 1, temp1[0], temp2[0], rep));
        AR.push_back(circle(0.1, 1, temp1[1], temp2[1], rep));
        AR.push_back(circle(0.1, 1, temp1[2], temp2[2], rep));

        // for(int i = 0; i < N; i++){
        //     AR.push_back(circle(0.1, 0.1, temp1[i], temp2[i], rep));
        //     // костыль, надо сдлать так чтоб не могли заспамиться в одной точке
        // }
    }
    ~gas(){}

    void solve(){
        for(int j = 1; j < rep; j++){ 
            for(int i = 0; i < N; i++){
                
                auto temp = AR[i].X[j-1] + AR[i].V[j-1]*t;


                if(i == 0){
                    if(temp - AR[i].R <= 0){
                        AR[i].V[j] = abs(AR[i].V[j-1]);
                        AR[i].X[j] = AR[i].V[j-1]*t - AR[i].X[j-1] + AR[i].R;
                    }
                    else{
                        AR[i].X[j] = temp;
                        AR[i].V[j] = AR[i].V[j-1];
                    }
                }


                else if(i == N-1){
                    if(temp + AR[i].R >= 10){
                        if(temp - AR[i].R <= AR[i-1].X[j]+AR[i-1].R){
                            AR[i].V[j] = -abs(AR[i].V[j-1]);
                            AR[i-1].V[j] = -abs(AR[i-1].V[j]);
                            AR[i].X[j] = 10 - AR[i].R;
                            AR[i-1].X[j] = 10 - 2*AR[i].R - AR[i-1].R;
                        }
                        else{
                            AR[i].X[j] = 10-AR[i].R;
                            AR[i].V[j] = -AR[i].V[j-1];
                        }
                    }
                    else{
                        if(temp - AR[i].R <= AR[i-1].X[j]+AR[i-1].R){
                            double v1 = ((AR[i].M - AR[i-1].M)*AR[i].V[j-1] + 2*AR[i-1].M*AR[i-1].V[j-1])/(AR[i].M + AR[i-1].M);
                            double v2 = ((AR[i-1].M - AR[i].M)*AR[i-1].V[j-1] + 2*AR[i].M*AR[i].V[j-1])/(AR[i].M + AR[i-1].M);
                            AR[i].V[j] = v1;
                            AR[i-1].V[j] = v2;
                            AR[i-1].X[j] = AR[i-1].X[j-1] + (AR[i].X[j-1] - AR[i].X[j-1] - AR[i-1].R - AR[i].R)/2; //(AR[i].V[j-1] + AR[i-1].V[j-1])*AR[i-1].V[j-1]
                            AR[i].X[j] = AR[i-1].X[j] + AR[i-1].R + AR[i].R;
                        }
                        else{
                            AR[i].X[j] = AR[i].X[j-1] + AR[i].V[j-1]*t;
                            AR[i].V[j] = AR[i].V[j-1];
                        }
                    }
                }


                else{
                    if(temp - AR[i].R <= AR[i-1].X[j]+AR[i-1].R){
                        double v1 = ((AR[i].M - AR[i-1].M)*AR[i].V[j-1] + 2*AR[i-1].M*AR[i-1].V[j-1])/(AR[i].M + AR[i-1].M);
                        double v2 = ((AR[i-1].M - AR[i].M)*AR[i-1].V[j-1] + 2*AR[i].M*AR[i].V[j-1])/(AR[i].M + AR[i-1].M);
                        AR[i].V[j] = v1;
                        AR[i-1].V[j] = v2;
                        AR[i-1].X[j] = AR[i-1].X[j-1] + (AR[i].X[j-1] - AR[i].X[j-1] - AR[i-1].R - AR[i].R)/2; //(AR[i].V[j-1] + AR[i-1].V[j-1])*AR[i-1].V[j-1]
                        AR[i].X[j] = AR[i-1].X[j] + AR[i-1].R + AR[i].R;
                    }
                    else{
                        AR[i].X[j] = AR[i].X[j-1] + AR[i].V[j-1]*t;
                        AR[i].V[j] = AR[i].V[j-1];
                    }
                }
            }
        }
        return;
    }

    // void sollve(){
    //     for(int j = 1; j < rep; j++){ 
    //         for(int i = 0; i < N; i++){
    //             auto it = AR[i];
    //             AR[i].X[j] = AR[i].X[j-1] + AR[i].V[j-1]*t;
    //             AR[i].V[j] = AR[i].V[j-1];
    //         }
    //     }
    // }

    void print(string file, int K){
        ofstream f(file);
        f << "i,x,v\n";
        for(int i = 0; i < rep; i++){
            f << i << "," << AR[K].X[i] << ',' << AR[K].V[i] << "\n";
        }
        return;
    }
    void printt(){
        for(int i = 0; i < N; i++){
            string d = "data/";
            d+='0'+i;
            d+=".csv";
            print(d, i);
        }
        return;
    }
};



int main(){
    gas op;
    op.solve();
    op.printt();
    return 0;
}
