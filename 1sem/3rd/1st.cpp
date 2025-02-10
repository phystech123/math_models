// #include<iostream>

// using namespace std;
//  int main(){
//     cout<<0.1 + 0.2;
//     return 0;
//  }



/*
2 * print float in a binary form
3 */
#include <iostream>
#include <cmath>
using namespace std;
void printbits_float (float v);

int main(){
    int n;
    float sum = 0;
    cin >> n;
    for (int i = 1; i<=n; i++){
        printbits_float(sum);
        sum += 1/(pow(2, i));
    }
    cout<<sum;
    return 0;
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