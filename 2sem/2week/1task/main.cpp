#include<iostream>
#include<random>
#include<cmath>
#include<array>
#include<iomanip>

using namespace std;

int main(){
    const int a = 0, b = 9, K = b - a +1;
    array<int, K> val = {0, 0,0,0,0,0,0,0,0,0};
    array<int, K> arr = {0, 0,0,0,0,0,0,0,0,0};

    int N;
    cin >> N;

    random_device r;
    default_random_engine e1(r());

    uniform_int_distribution<int> dist(a, b);
    for(int k = 0; k < N*N; k++){
        val = {0, 0,0,0,0,0,0,0,0,0};
        for(int i = 0; i < N; i++){
            int el = dist(e1);
            val[el] = 1;
        }
        for(int i = 0; i < K; i++){
            arr[i] += val[i];
        }
    }
    cout << "Для N = " << N << ",   K = " << K << endl;
    for(int i = 0; i < K; i++){
        cout << a + i << "   " << setprecision(8) << float(arr[i])/float(N*N) << endl;
    }
    cout << "Расчитанная вероятность для данного K и N " << 1. - pow((1.-1./float(K)), N);
    return 0;
}