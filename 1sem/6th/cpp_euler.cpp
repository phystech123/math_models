#include<iostream>
#include<cmath>
#include <ctime> 
using namespace std;

int main(){
    timespec mt1, mt2;
    clock_gettime(CLOCK_REALTIME, &mt1);

    double h = 1, W = 10;
    int N = 100000000;
    double* X = new double[N];
    double* V = new double[N];
    
    X[0] = 10; 
    V[0] = 0;

    for(int i = 1; i < N; i++){
        // x(i+1) = xi + dT*Vi
        // V(i+1) = v(i) - w**2*x
        X[i] = X[i-1] + h*V[i-1];
        V[i] = V[i-1] - h*pow(W, 2) * sin(X[i-1]);
    }
    clock_gettime(CLOCK_REALTIME, &mt2);
    cout << (mt1.tv_nsec-mt2.tv_nsec)/1000000.;
    
    return 0;
}