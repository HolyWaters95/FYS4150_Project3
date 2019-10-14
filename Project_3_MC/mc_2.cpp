
#include <iostream>
#include <armadillo>
#include "lib.h"
#include <random>
#include <chrono>

using namespace std;
using namespace arma;
using namespace chrono;


// delcaration of function
double func_important_samp(double r1, double r2, double t1, double t2, double p1, double p2);



// Monte Carlo with exponential distribution important sampling


int main()
{
    // computes Monte Carlo with an exponential distribution without important sampling


    int n;
    cout << "Input N for Monte Carlo importance samples:" << endl;
    cin >> n;
    double MCintIS = 0;
    double sum_sigmaIS = 0;
    double fy = 0;
    const double pi =3.141592653589793238463;
    double exact_solution = 5*pi*pi / (16*16);



    // random number generator
    unsigned seed = system_clock::now().time_since_epoch().count();
    mt19937_64 generator (seed);

    // starting clock for time keeping
    high_resolution_clock::time_point time1 = high_resolution_clock::now();

    for (int i = 1; i <= n; i++){
        // generating r1 and r2 with the exponential distribution
        double g;
        g = generate_canonical< double, 128 > (generator);  // random number [0,1]
        double r1 = -0.25*log(1.- g);                        // random number with exp dist
        g = generate_canonical< double, 128 > (generator);
        double r2 = -0.25*log(1.-g);

        /*
        // checks r1 and r2
        cout << "r1 and r2 " << endl << r1 << " " << r2 << endl;
        */


        // defining theta and phi
        // Initialize the seed and call the Mersienne algo
        random_device rd;
        mt19937_64 gen(rd());

        // Set up the uniform distribution for x \in [[0, pi]
        uniform_real_distribution<double> zero_to_pi(0.0,pi);
        uniform_real_distribution<double> zero_to_two_pi(0.0,2*pi);

        // Now use the RNG
        double t1 = double (zero_to_pi(gen));
        double t2 = double (zero_to_pi(gen));
        double p1 = double (zero_to_two_pi(gen));
        double p2 = double (zero_to_two_pi(gen));


        /*
        cout << endl << "printing theta and phi"  << endl;
        cout << t1 << " " << t2 << endl
             << p1 << " " << p2 << endl
             << endl;
        */


        // MC integrating
        fy = func_important_samp(r1, r2, t1, t2, p1, p2);
        MCintIS += fy;
        sum_sigmaIS += fy*fy;
    }

    // stops the clock
    high_resolution_clock::time_point time2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double> >(time2-time1);
    cout << endl << "Monte Carlo importance sampling used " << time_span.count()
         << " seconds" << endl;


    // setting up the jaocbi
    double jacobi = 4* pow(pi,4) / 16;

    // calculating the mean integration results and the variance
    MCintIS= MCintIS / (double (n));
    sum_sigmaIS = sum_sigmaIS / (double (n));
    double variance = sum_sigmaIS - MCintIS * MCintIS;




    // printing results for Important Samplng
    cout << endl << "Results for MC important sampling" << endl
         << "Variance = " << jacobi * variance << endl
         << "Integral = " << jacobi * MCintIS << endl
         << "Exact = " << exact_solution << endl;



}
