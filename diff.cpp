#include <iostream>
#include "reverse.h"
#include <array>

using namespace std;
int main()
{
    auto f = [](auto &x){
        return x*x - 6*x + 16;
    };
    D x(7);
    double err = 0.01;
    long double lr = 0.01;
    double max_iteration = 1000;
    gradiente(f,x,lr,err,max_iteration,DESCENDENTE);

    //newtonMethod(sum_b,b,err);

    cout << x.value << endl;
}
