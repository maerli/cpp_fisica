#include <iostream>
#include <stdarg.h>
#include <list>
#include <algorithm>
#include <typeinfo>
#include <array>


using namespace std;
const int DESCENDENTE = 1;
const int ASCENDENTE = 2;

//Compiler version g++ 6.3.0
void teste(int a,...){
  va_list args;
  va_start(args,a);
  for(int i=1;i<=a;i++){
    int d = va_arg(args,int);
    cout << d << endl;
  }
  va_end(args);
}

class Children;
class D{
  public:
    double value;
    bool compute;
    list<Children> children;
    double grad_value;
    D(double value);
    D(const D &old);
    double grad();
    D &operator+(D &other);
    D &operator+(double other);
    D &operator*(D &other);
    D &operator*(double other);
    D &operator-(D &other);
    D &operator-(double other);
};
D::D(const D &old){
  value = old.value;
  grad_value = 0;
  compute = true;
}
D::D(double value){
  this->value = value;
  this->grad_value = 0;
  this->compute = true;
}
inline D &operator*(double i, D &a)
{
    return a * i;
}
inline D &operator+(double i, D &a)
{
    return a + i;
}
inline D &operator-(double i, D &a)
{
    return a - i;
}


class Children{
  public:
  double a;
  D *b;
  Children(const Children &other);
  Children(double a,D *b);
  ~Children();
};

D &D::operator+(D &other){
    D *z = new D(this->value + other.value);
    Children c1(1.0,z);
    Children c2(1.0,z);
    this->children.push_back(c1);
    other.children.push_back(c2);
    return *z;
}
D &D::operator+(double other){
    D *z = new D(this->value + other);
    Children c1(1.0,z);
    this->children.push_back(c1);
    return *z;
}
D &D::operator*(D &other){
    D *z = new D(this->value * other.value);
    Children c1(other.value,z);
    Children c2(this->value,z);
    this->children.push_back(c1);
    other.children.push_back(c2);
    return *z;
}
D &D::operator*(double other){
    D *z = new D(this->value * other);
    Children c1(other,z);
    this->children.push_back(c1);
    return *z;
}
D &D::operator-(D &other){
    D *z = new D(this->value - other.value);
    Children c1(1.0,z);
    Children c2(-1.0,z);
    this->children.push_back(c1);
    other.children.push_back(c2);
    return *z;
}
D &D::operator-(double other){
    D *z = new D(this->value - other);
    Children c1(1.0,z);
    this->children.push_back(c1);
    return *z;
}
void void_print(Children e){
    cout << e.a << endl;
}

double D::grad(){
    if(this->compute){
        double sum = 0;
        for (std::list<Children>::iterator it=this->children.begin(); it != this->children.end(); ++it){
            //cout << "children" << (*it).a << endl;
            sum += (*it).a;
        }
        this->compute = false;
        this->grad_value = sum;
    }
    return this->grad_value;
}
Children::Children(const Children &old){
  a = old.a;
  b = old.b;
}
Children::Children(double a, D *b){
    this->a = a;
    this->b = b;
  }
 Children::~Children(){
    //delete b;
}

void newtonMethod(auto f,D &x,double err){
  int i = 0;
  D z = f(x);
  while(abs(z.value) > err && i < 1000 ){
    z = f(x);
    z.grad_value = 1.0;
    double t = z.value/x.grad();
    x = x.value - t;
    x.grad_value = 0;
    x.compute = true;
    i += 1;
  }
}
void gradiente(auto f,D &x,long double lr,double err,int iter,int type){
    // Making somethings
    int i = 0;
    double xi = err + 1;
    while(xi > err && i < iter){
        D y = f(x);
        y.grad_value = 1.0;
        double t = 0;
        if(type == DESCENDENTE){
            t =  -x.grad();
        }else if(type == ASCENDENTE){
            t = x.grad();
        }
        cout << xi << endl;
        xi = abs(t);
        x = x.value + lr*t;
        x.grad_value = 0;
        x.compute = true;
        i += 1;
    }
    cout << "resolvido na iteração " << i << endl;
    cout << "com aproxim = " << abs(xi) << endl;
}
/*
void minimize(auto f,,double lr){
    auto err = [](auto &x,auto &y,auto a&,auto &b){
        return a*x + b - y;
    }
    xi = err + 1
    int iter = 1000;
    while(xi > err && i < iter){
        D y =
    }
}
*/
