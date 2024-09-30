#include<iostream>
#include<fstream>
#include<string>
#include<cmath>


using namespace std;
void sep(float* arr, int N);
void eyler(float* arr, int N, float* X, float* V);
void entry(float* X, float* Y, int N, string FILE);
void hoin(float* arr, int N, float* X, float* V);
void RK4(float* arr, int N, float* X, float* V);

int W = 10;

int main(){
    const int N = 100000;
    float arr[N];
    sep(arr, N);

    float X[N], V[N];
    X[0] = 1;
    V[0] = 0;
    eyler(arr, N, X, V);
    entry(arr, X, N, "dataX_eyler.csv");
    entry(arr, V, N, "dataV_eyler.csv");

    hoin(arr, N, X, V);
    entry(arr, X, N, "dataX_hoin.csv");
    entry(arr, V, N, "dataV_hoin.csv");

    RK4(arr, N, X, V);
    entry(arr, X, N, "dataX_RK4.csv");
    entry(arr, V, N, "dataV_RK4.csv");
    return 0;
}






void sep(float* arr, int N){
    for(int i = 0; i < N; i++){
        arr[i] = i/100.;
    }
}


void entry(float* X, float* Y, int N, string FILE){ 
    ofstream file;
    file.open(FILE);
    file << "t; x\n";
    for(int i =0; i < N; i++){
        file << X[i]<<"; "<<Y[i]<<"\n";
    }
    file.close();
}




void eyler(float* arr, int N, float* X, float* V){
    for(int i = 1; i < N; i++){
        // x(i+1) = xi + dT*Vi
        // V(i+1) = v(i) - w**2*x
        X[i] = X[i-1] + (arr[i] - arr[i-1])*V[i-1];
        V[i] = V[i-1] - (arr[i] - arr[i-1])*pow(W, 2) * X[i-1];
    }
}


void hoin(float* arr, int N, float* X, float* V){
        for(int i = 1; i < N; i++){
        // x(i+1) = xi + dT*Vi
        // V(i+1) = v(i) - w**2*x
            X[i] = X[i-1] + (arr[i] - arr[i-1])*(V[i-1] + V[i-1] - (arr[i] - arr[i-1])*pow(W, 2) * X[i-1])/2;
            V[i] = V[i-1] - (arr[i] - arr[i-1])*pow(W, 2) * (X[i-1] + X[i-1] + (arr[i] - arr[i-1])*V[i-1])/2; 
        } 
}

void RK4(float* arr, int N, float* X, float* V){
    for(int i = 1; i < N; i++){
        double h = arr[i] - arr[i-1];
        double k1 = h*V[i-1];
        double k2 = h*(V[i-1] - (h/2.)*X[i-1]*pow(W, 2));
        double k3 = h*(V[i-1] - (h/2.)*X[i-1]*pow(W, 2));
        double k4 = h*(V[i-1] - h*X[i-1]*pow(W, 2));
        X[i] = X[i-1] + (1/6.)*(k1 + 2*(k2+k3) + k4);

        double l1 = -h*pow(W, 2)*X[i-1];
        double l2 = -h*pow(W, 2)*(X[i-1] + (h/2.)*V[i-1]);
        double l3 = -h*pow(W, 2)*(X[i-1] + (h/2.)*V[i-1]);
        double l4 = -h*pow(W, 2)*(X[i-1] + h*V[i-1]);
        V[i] = V[i-1] + (1/6.)*(l1 + 2*(l2+l3) + l4);



        // double h = arr[i] - arr[i-1];
        // double k1 = h*V[i-1];
        // double k2 = h*(V[i-1] + k1/2.);
        // double k3 = h*(V[i-1] + k2/2.);
        // double k4 = h*(V[i-1] + k3);
        // X[i] = X[i-1] + (1/6.)*(k1 + 2*(k2+k3) + k4);

        // double l1 = h*(-pow(W, 2)*X[i-1]);
        // double l2 = h*(-pow(W, 2)*(X[i-1] + l1/2.));
        // double l3 = h*(-pow(W, 2)*(X[i-1] + l2/2.));
        // double l4 = h*(-pow(W, 2)*(X[i-1] + l3));
        // V[i] = V[i-1] + (1/6.)*(l1 + 2*(l2+l3) + l4);
    }
}