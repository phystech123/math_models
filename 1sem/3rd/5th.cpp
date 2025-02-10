#include <iostream>
#include <cmath>

using namespace std;

// f = exp(-x**2)
// X = [0, +inf]
void Partitioning(float* arr, int len);
float RRectangle(float* arr, int len);
float LRectangle(float* arr, int len);
float Trapezoid(float* arr, int len);
float revTrapezoid(float* arr, int len);
void printbits_float (float v);

int main(){
    int len = 100000;
    float arr[len];
    Partitioning(arr, len);
    RRectangle(arr, len);
    LRectangle(arr, len);
    float a = Trapezoid(arr, len);
    float b = revTrapezoid(arr, len);
    cout << "Эталонное значение: " << scientific << sqrt(M_PI)/2 << endl;
    cout<<"\n\n\n\n\n";
    printbits_float(a);
    printbits_float(b);
    printbits_float(sqrt(M_PI)/2);
    return 0;
}

void Partitioning(float* arr, int len){
    for (int i = 0; i < len; i++){
        arr[i] = i/2.;
    }
}

float RRectangle(float* arr, int len){
    float sum = 0.;
    for(int i = 1; i < len; i++){
        sum += (arr[i] - arr[i-1]) * exp(-pow(arr[i], 2));
    }
    cout <<  "Посчитано методом правых прямоугольников: " << scientific << sum << endl;
    return sum;
}

float LRectangle(float* arr, int len){
    float sum = 0.;
    for(int i = 1; i < len; i++){
        sum += (arr[i] - arr[i-1]) * exp(-pow(arr[i-1], 2));
    }
    cout << "Посчитано методом левых прямоугольников: " << scientific << sum << endl;
    return sum;
}

float Trapezoid(float* arr, int len){
    float sum = 0;
    for(int i = 1; i < len; i++){
        sum += (arr[i] - arr[i-1]) * (exp(-pow(arr[i], 2)) + exp(-pow(arr[i-1], 2)))/2;
    }
    cout << "Посчитано методом трапеций: " << scientific << sum << endl;
    return sum;
}

float revTrapezoid(float* arr, int len){
    float sum = 0;
    for(int i = len; i > 0; i--){
        sum += (arr[i] - arr[i-1]) * (exp(-pow(arr[i], 2)) + exp(-pow(arr[i-1], 2)))/2;
    }
    cout << "Посчитано методом трапеций(обратная сумма): " << scientific << sum << endl;
    return sum;
}

void printbits_float (float v){
    int i;
    int *j = (int *) &v;
    int n = 8 * sizeof (v);

    for (i = n - 1; i >= 0; i--)
    {
    if ((i == 22) || (i == 30))
    putchar (' ');
    putchar ('0' + (((*j) >> i) & 1));
    }
    cout<<endl;
}

// различие от порядка суммирования в последнем знаке мантиссы, незначительное 
