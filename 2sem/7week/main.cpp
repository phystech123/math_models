#include <algorithm>
#include <array>
#include <iomanip>
#include <ios>
#include<iostream>
#include<cmath>
#include <iterator>
#include<vector>
#include<random>
#include<fstream>
#include<string>

// #include<pair>

using namespace std;

// for generating random coord's and speeds
std::random_device r_;
std::default_random_engine e1(r_());
std::uniform_real_distribution<> dist1(0.4, 9.6);
std::uniform_real_distribution<> dist2(-1, 1);
std::uniform_int_distribution<int> dist3 (0, 1);

// one molecule
class circle{
    public:
        int i; // sequence number
        double R; // radius
        double M; // mass
        double* X; // coord
        double* V; // speed

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

// class of molecular engine
class gas{
public:
    array<array<double, 2>, 2> CONF; // to do 2 types of molecules
    const static int N = 20; //num of malecules
    static const int rep = 100000; // value of repetition
    double t = 0.01; // one step
    vector<circle> AR; // main array with all molecules
    array<int, rep> collision;
    

    // init conf
    gas(){
        double R=0.0001, M=25, r=0.05, m=1;
        CONF[0][0] = R;
        CONF[0][1] = M;
        CONF[1][0] = r;
        CONF[1][1] = m;

        vector<double> temp1; //temporary coordinates - to sort
        vector<double> temp2; //temporary speeds

        // // ---- variation that provide chaotic of intial conditions
        for(int i = 0; i < N; i++){
            temp1.push_back(dist1(e1));
            temp2.push_back(dist2(e1));
        }
        sort(temp1.begin(), temp1.end());

        // // ---- variation that provide newton`s pendulum
        // temp1.push_back(4);
        // temp1.push_back(5);
        // temp1.push_back(6);
        // temp2.push_back(1);
        // temp2.push_back(0);
        // temp2.push_back(-1);


        // temp1.push_back(4.7);
        // temp1.push_back(5);
        // temp1.push_back(5.25);
        // temp2.push_back(1);
        // temp2.push_back(0);
        // temp2.push_back(-2);


        // temp1.push_back(9.1999999);
        // temp1.push_back(9.39999999);
        // temp1.push_back(9.599999999);
        // temp1.push_back(9.7999999999);

        // temp2.push_back(1);
        // temp2.push_back(0);
        // temp2.push_back(0);
        // temp2.push_back(-2);
        

        

        // // ---- variation that provide one molecule with big speed and triple collision
        // temp1.push_back(4.79);
        // temp1.push_back(5);
        // temp1.push_back(5.21);
        // temp2.push_back(10);
        // temp2.push_back(0);
        // temp2.push_back(0);

        // ---- variation that provide triple collision like 2 ball and 1 wall
        // temp1.push_back(8);
        // temp1.push_back(9.577);
        // temp1.push_back(9.899);
        // temp2.push_back(0);
        // temp2.push_back(1);
        // temp2.push_back(0);
        

        // // push to main array manually
        // AR.push_back(circle(0.1, 0.1, temp1[0], temp2[0], rep));
        // AR.push_back(circle(0.1, 0.1, temp1[1], temp2[1], rep));
        // AR.push_back(circle(0.1, 0.1, temp1[2], temp2[2], rep));
        // AR.push_back(circle(0.1, 0.1, temp1[3], temp2[3], rep));


        // // push to main array automatically with single type of molecules
        // for(int i = 0; i < N; i++){
        //     AR.push_back(circle(r, M, temp1[i], temp2[i], rep));
        //     // костыль, надо сдлать так чтоб не могли заспамиться в одной точке
        // }
        

        // push to main array automatically with random type of molecules
        for(int i = 0; i < N; i++){
            int tt = dist3(e1);
            AR.push_back(circle(CONF[tt][0], CONF[tt][1], temp1[i], temp2[i], rep));
            // костыль, надо сдлать так чтоб не могли заспамиться в одной точке
        }
    }






    ~gas(){}

    // solver
    void solve(){
        for(int j = 1; j < rep; j++){ 
            collision[j]=0;
            for(int i = 0; i < N; i++){
                auto temp = AR[i].X[j-1] + AR[i].V[j-1]*t;
                // first molecule
                if(i == 0){
                    if(temp - AR[i].R <= 0){
                        double t_ = (AR[i].X[j-1] - AR[i].R)/abs(AR[i].V[j-1]);
                        AR[i].V[j] = abs(AR[i].V[j-1]);
                        AR[i].X[j] = AR[i].X[j-1] + AR[i].V[j-1]*t_ + AR[i].V[j]*(t-t_);
                        collision[j]+=1;
                    }
                    else{
                        AR[i].X[j] = temp;
                        AR[i].V[j] = AR[i].V[j-1];
                    }
                }

                // last molecule
                else if(i == N-1){
                    AR[i].X[j] = AR[i].X[j-1] + AR[i].V[j-1]*t;
                    AR[i].V[j] = AR[i].V[j-1];
                    if(temp + AR[i].R >= 10){
                        double t__ = (10 -(AR[i].X[j-1] + AR[i].R))/abs(AR[i].V[j-1]);
                        double V__ = -abs(AR[i].V[j-1]);
                        double X__ = 10;
                        collision[j]+=1;

                        if(temp - AR[i].R <= AR[i-1].X[j]+AR[i-1].R){
                            double v1 = ((AR[i].M - AR[i-1].M)*V__ + 2*AR[i-1].M*AR[i-1].V[j-1])/(AR[i].M + AR[i-1].M);
                            double v2 = ((AR[i-1].M - AR[i].M)*AR[i-1].V[j-1] + 2*AR[i].M*V__)/(AR[i].M + AR[i-1].M);
                            double t_ = (AR[i].X[j-1] - AR[i-1].X[j-1] - AR[i-1].R - AR[i].R)/abs(V__ - AR[i-1].V[j-1]);
                            AR[i-1].X[j] = AR[i-1].X[j-1] + AR[i-1].V[j-1]*t_ + v1*(t-t__-t_);
                            AR[i].X[j] =  AR[i].X[j-1] + V__*t_ + v2*(t-t__-t_);
                            AR[i].V[j] = v1;
                            AR[i-1].V[j] = v2;
                            collision[j]+=1;
                        }
                        else{
                            AR[i].V[j] = -abs(AR[i].V[j-1]);
                            AR[i].X[j] = AR[i].X[j-1] + AR[i].V[j-1]*t__ + AR[i].V[j]*(t-t__);
                        }
                    }
                    // nolmal case for last molecule - copying of last item
                    else{
                        if(temp - AR[i].R <= AR[i-1].X[j]+AR[i-1].R){
                            double v1 = ((AR[i].M - AR[i-1].M)*AR[i].V[j] + 2*AR[i-1].M*AR[i-1].V[j])/(AR[i].M + AR[i-1].M);
                            double v2 = ((AR[i-1].M - AR[i].M)*AR[i-1].V[j] + 2*AR[i].M*AR[i].V[j])/(AR[i].M + AR[i-1].M);
                            double t_ = (AR[i].X[j-1] - AR[i-1].X[j-1] - AR[i-1].R - AR[i].R)/abs(AR[i].V[j] - AR[i-1].V[j]);
                            AR[i-1].X[j] = AR[i-1].X[j-1] + AR[i-1].V[j]*t_ + v2*(t-t_);
                            AR[i].X[j] =  AR[i].X[j-1] + AR[i].V[j]*t_ + v1*(t-t_);
                            AR[i].V[j] = v1;
                            AR[i-1].V[j] = v2;
                            collision[j]+=1;
                        }
                        else{
                            AR[i].X[j] = AR[i].X[j-1] + AR[i].V[j-1]*t;
                            AR[i].V[j] = AR[i].V[j-1];
                        }
                    }
                }

                // mean molecules (last item)
                else{
                    AR[i].X[j] = AR[i].X[j-1] + AR[i].V[j-1]*t;
                    AR[i].V[j] = AR[i].V[j-1];
                    if(temp - AR[i].R <= AR[i-1].X[j]+AR[i-1].R){
                        double v1 = ((AR[i].M - AR[i-1].M)*AR[i].V[j] + 2*AR[i-1].M*AR[i-1].V[j])/(AR[i].M + AR[i-1].M);
                        double v2 = ((AR[i-1].M - AR[i].M)*AR[i-1].V[j] + 2*AR[i].M*AR[i].V[j])/(AR[i].M + AR[i-1].M);
                        double t_ = (AR[i].X[j-1] - AR[i-1].X[j-1] - AR[i-1].R - AR[i].R)/abs(AR[i].V[j] - AR[i-1].V[j]);
                        AR[i-1].X[j] = AR[i-1].X[j-1] + AR[i-1].V[j]*t_ + v2*(t-t_);
                        AR[i].X[j] =  AR[i].X[j-1] + AR[i].V[j]*t_ + v1*(t-t_);
                        AR[i].V[j] = v1;
                        AR[i-1].V[j] = v2;
                        collision[j]+=1;
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

    // to take out results of one molecule
    void print(string file, int K){
        ofstream f(file);
        f << "i,m,x,v\n";
        for(int i = 0; i < rep; i++){
            f << setprecision(12) << i << "," << AR[K].M << "," << AR[K].X[i] << ',' << AR[K].V[i] << "\n";
        }
        return;
    }

    // to take out results of all molecules
    void printt(){
        for(int i = 0; i < N; i++){
            string d = "data/";
            d+=to_string(i);
            d+=".csv";
            print(d, i);
        }
        return;
    }
    

    void print_col(string file){
        ofstream f(file);
        f << "i,n\n";
        for(int i = 0; i < rep; i++){
            f << i << "," << collision[i] << "\n";
        }
        return;
    }
};


// calling solving and printing
int main(){
    gas op;
    op.solve();
    op.printt();
    op.print_col("data/col.csv");
    return 0;
}
