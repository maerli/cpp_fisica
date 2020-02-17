#include <iostream>
#include "reverse.h"
#include <vector>

double rand_ab(double a,double b){
    return a + (b-a)*((double) rand()/RAND_MAX );
}

using namespace std;
void montecarlo(auto f,double a,double b,int N){
    double somar_xs = 0,somar_ys = 0,integral;
    for(int i=0;i<N;i++){
        double n = rand_ab(a,b);
        somar_xs += n;
        somar_ys += f(n);

    }
    cout << (double) rand()/RAND_MAX << endl;
    integral = (b-a)*(1/(double)N)*somar_ys;
    cout << integral << endl;

}
int main()
{
 cout << "maerli" << endl;
 auto f = [](double x){
    return 4.0/(1 + x*x);
 };
 double a = 0,b = 1;
 montecarlo(f,a,b,1000000);
 return 0;
}
