#include <iostream>
#include <cmath>
using namespace std;
void printbits_float (float v);

int main(){
    float sum = 0;
    float prev = 2;
    for (int i = 1;; i++){
        printbits_float(sum);
        prev = sum;
        sum += 1./i;
        if (sum == prev)
            break;
    }
    cout<<scientific<<sum;
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
