#include <iostream>
#include <cmath>

using namespace std;

// ряд сходится на всей числовой прямой, ннесовпадение из-за особеннотсей типа float
// можно пофиксить изменяя порядок суммирования

void sin_(float val, int n);
float absf_(float x);

int main(){
    while (true)
    {
        float x;
        int n;
        cin>>n;
        cin >> x >> n;
        if (n == 5101){
            break;
        }
        x = absf_(x);
        sin_(x, n);
    }
    return 0;
}



void sin_(float val, int n){
    float sum = val;
    float prev = val;
    for (int i = 2; i <= n; i++){
        prev = prev*(-1)*pow(val, 2)/((2*i-1)*(2*i-2));
        sum += prev;
    }
    cout << sum<<endl;
}

float absf_(float x){
    int nx = 0;
    for(int i = 0; fabs(x)-nx > M_PI;i++){
        nx = M_PI * i;
    }
    if (x>=0)
        x -= nx;
    else
        x += nx;
    return x;
}

/* плохо тем, мы доходим до высоких степеней в начале суммироавния, 
а затем нужные слагаемые убиваются, за неучетом потери точности, 
которая составляет порядка 1000 для 10-й степени, что неприлично много
можно использовать либо суммирование Кэхэна, либо брать синус по модулю(реализовано)
*/