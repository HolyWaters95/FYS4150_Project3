#include <iostream>
#include <armadillo>
#include "lib.h"
#include <random>
#include <chrono>

using namespace std;
using namespace arma;
using namespace chrono;


// delcaration of function
double func_brute(double x1,double y1,double z1, double x2, double y2, double z2 );


int main()
{
    // computes Monte Carlo with a uniform distribution without important sampling

    int n;
    cout << "Input for number of Monte Carlo samples:" << endl;
    cin >> n;
    double MCint = 0;
    double sum_sigma = 0;
    double fx = 0;
    const double pi =3.141592653589793238463;
    double exact_solution = 5*pi*pi / (16*16);



    // random number generator
    unsigned seed = system_clock::now().time_since_epoch().count();
    mt19937_64 generator (seed);



    // random number test
/*
    for (int i = 0; i < n; i++){
        double g;
        g = generate_canonical< double, 128 > (generator);
        cout << "rand numb 1 " << g << endl;
        g = generate_canonical< double, 128 > (generator);
        cout << "rand numb 2 " << g << endl;
    }
*/



    // starting clock for time keeping
    high_resolution_clock::time_point t1 = high_resolution_clock::now();



    for (int i = 1; i <= n; i++){
        // generating random numbers between -2,2 for each coordinate
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



        // MC integrating
        fx = func_brute(x1,y1,z1,x2,y2,z2);
        MCint += fx;
        sum_sigma += fx*fx;
    }

    // stops the clock
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double> >(t2 - t1);
    cout << endl << "Monte Carlo brute force used " << time_span.count() << " seconds" << endl;
    cout << endl;


    // setting up the jaocbi
    int a = -2;
    int b = 2;
    double jacobi = pow((b-a),6);

    // calculating the mean integration results and the variance
    MCint = MCint / (double (n));
    sum_sigma = sum_sigma / (double (n));
    double variance = sum_sigma - MCint*MCint;


    cout << "Variance = " << variance << endl
         << "Integral = " << jacobi * MCint << endl
         << "Exact = " << exact_solution << endl;


}

// end of main


