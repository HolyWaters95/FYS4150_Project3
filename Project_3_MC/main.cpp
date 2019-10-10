#include <iostream>
#include <armadillo>
#include "lib.h"
#include "lib.cpp"

using namespace std;
using namespace arma;

double func(double x1,double y1,double z1, double x2, double y2, double z2 );



int main()
{
    int n;
    double MCint, MCintsqr2, fx;
    cout << "Input for number of Monte Carlo samples:" << endl;
    cin >> n;
    double alpha = 2.0;
    MCint = 0;
    MCintsqr2 = 0;
    double inverse_period = 1.0/ RAND_MAX;
    srand(time(NULL));
    for (int i = 1; i <= n; i++){
        double x1 = double(rand() - 0.5)*4; // random number between -2,2
        double y1 = double(rand() - 0.5)*4;
        double z1 = double(rand() - 0.5)*4;
        double x2 = double(rand() - 0.5)*4;
        double y2 = double(rand() - 0.5)*4;
        double z2 = double(rand() - 0.5)*4;
        fx = func(x1,y1,z1,x2,y2,z2);
        MCint += fx;
        MCintsqr2 += fx*fx;
    }
    MCint = MCint / (double (n));
    MCintsqr2 = MCintsqr2 / (double (n));
    double variance = MCintsqr2 - MCint*MCint;

    cout << "Variance = " << variance << endl
         << "Integral = " << MCint << endl
         << "Exact = " << "put exact here" << endl;
}

double func(x1,y1,z1,x2,y2,z2){

    double r1 = sqrt(x1*x1 + y1*y1 + z1*z1);
    double r2 = sqrt(x2*x2 + y2*y2 + z2*z2);
    mat func_mat = exp(-2*alpha (r1 + r2));
    return func_mat;
}
