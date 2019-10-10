#include <iostream>
#include <armadillo>
#include "lib.h"
//#include "lib.cpp"
#include <random>
#include <chrono>

using namespace std;
using namespace arma;
using namespace chrono;

double func(double x1,double y1,double z1, double x2, double y2, double z2 );



int main()
{
    // computes monte carlo with a uniform distribution without important sampling
    int n;
    cout << "Input for number of Monte Carlo samples:" << endl;
    cin >> n;
    double MCint = 0;
    double MCintsqr2 = 0;
    double fx = 0;
    const double pi =3.141592653589793238463;
    double exact_solution = 5*pi*pi / (16*16);

    // random number generator

    typedef high_resolution_clock myclock;
    myclock::time_point beginning = myclock::now();

    unsigned seed = system_clock::now().time_since_epoch().count();
    mt19937_64 generator (seed);

/*
    // random number test
    for (int i = 0; i < n; i++){
        double g;
        g = generate_canonical< double, 128 > (generator);
        cout << "rand numb 1 " << g << endl;
        g = generate_canonical< double, 128 > (generator);
        cout << "rand numb 2 " << g << endl;
    }
*/



    for (int i = 1; i <= n; i++){
        // generating random numbers between -2,2
        double g;
        g = generate_canonical< double, 128 > (generator);
        double x1 = double(g - 0.5)*4;
        g = generate_canonical< double, 128 > (generator);
        double y1 = double(g - 0.5)*4;
        g = generate_canonical< double, 128 > (generator);
        double z1 = double(g - 0.5)*4;
        g = generate_canonical< double, 128 > (generator);
        double x2 = double(g - 0.5)*4;
        g = generate_canonical< double, 128 > (generator);
        double y2 = double(g - 0.5)*4;
        g = generate_canonical< double, 128 > (generator);
        double z2 = double(g - 0.5)*4;

        fx = func(x1,y1,z1,x2,y2,z2);
        MCint += fx;
        MCintsqr2 += fx*fx;
    }
    MCint = MCint / (double (n));
    MCintsqr2 = MCintsqr2 / (double (n));
    double variance = MCintsqr2 - MCint*MCint; // standard deviation



    cout << "Variance = " << setw(25) << setprecision(20) << variance << endl
         << "Integral = " << setw(25) << setprecision(20) << MCint << endl
         << "Exact = " << exact_solution << endl;

}


//
double func(double x1, double y1,double z1, double x2, double y2, double z2){
    double alpha = 2.0;
    double r1 = sqrt(x1*x1 + y1*y1 + z1*z1);
    double r2 = sqrt(x2*x2 + y2*y2 + z2*z2);
    double r1_r2 = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));
    if (r1_r2 < pow(10,-10)){return 0;}
    double I = exp(-2*alpha*(r1+r2)) / r1_r2;
    return I;
}


