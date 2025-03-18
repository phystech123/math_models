#include<iostream>
#include<random>
#include<cmath>
#include<deque>
#include<iomanip>
#include<fstream>

using namespace std;

random_device r;
default_random_engine e1(r());

uniform_int_distribution<int> dist(1, 3);

double foo(int a, int b, int c, const int N){
    int res = 0;
    deque<int> seq = {0,0,0};

    for(int i = 0; i < N; i++){
        seq = {0,0,0};
        while(seq[0] != c || seq[1] != b || seq[2] != a){
            seq.push_front(dist(e1));
        }
        // cout << seq.size() - 3 << endl;
        res +=  seq.size() - 3;
    }
    return res/float(N);
}

int main(){
    ofstream fout("data.txt");
    // int a, b, c;
    int N = 10000;
    cin >> N;
    // cin >> a;
    // cin >> b;
    // cin >> c;

    // //test
    // for(int i = 0; i < 10; i++){
    //     cout << foo(a, b, c, N) << endl;
    // }

    for(int i = 1; i <= 3; i++){
        for(int j = 1; j <= 3; j++){
            for(int k = 1; k <= 3; k++){
                fout <<i<<j<<k<<", "<<foo(i, j, k, N) << endl;
            }
        }
    }
    fout.close();
    
    return 0;
}


// решается методом построения графов с введением штрафов, или построение плотности вероятности по честному. Вылазят числа фибоначи. Рассмотреть алфавит из двух букв.