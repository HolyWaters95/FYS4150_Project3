#include <iostream>
#include <armadillo>
#include "lib.h"
#include <random>
#include <chrono>
#include "time.h"

using namespace std;
using namespace arma;
using namespace chrono;


// delcaration of function
double func_brute(double x1,double y1,double z1, double x2, double y2, double z2 );

vector<int> readvalues(string file);

int main()
{
    // computes brute force Monte Carlo with a uniform distribution


    string save_runtimes;
    string save_results;
    cout << "do you want to save runtimes? y or n" << endl;
    cin >> save_runtimes;
    cout << "do you want to save results? y or n" << endl;
    cin >> save_results;

    vector<int> N_values = readvalues("Pro3_Nvalues.txt");
    vector<int> X_values = readvalues("Pro3_Xvalues.txt");
    vec runtimes(N_values.size());



for (int p = 0;p<N_values.size();p++){
    int n = N_values[p];
    double average_I = 0;
    double average_V = 0;
    double average_runtime = 0;

    const double pi =3.141592653589793238463;
    double exact_solution = 5*pi*pi / (16*16);

    // setting up the jacobi
    int a = -3;
    int b = 3;
    double jacobi = pow((b-a),6);

    for (int counter = 0;counter < 10;counter++){

    double MCint = 0;
    double sum_sigma = 0;
    double fx = 0;


    // random number generator
    unsigned seed = system_clock::now().time_since_epoch().count();
    mt19937_64 generator (seed);


    // starting clock for time keeping
    time_t start, end;
    start = clock();



    for (int i = 1; i <= n; i++){
        // generating random numbers between -2,2 for each coordinate
        double g;
        g = generate_canonical< double, 128 > (generator);
        double x1 = double(g - 0.5)*6;
        g = generate_canonical< double, 128 > (generator);
        double y1 = double(g - 0.5)*6;
        g = generate_canonical< double, 128 > (generator);
        double z1 = double(g - 0.5)*6;
        g = generate_canonical< double, 128 > (generator);
        double x2 = double(g - 0.5)*6;
        g = generate_canonical< double, 128 > (generator);
        double y2 = double(g - 0.5)*6;
        g = generate_canonical< double, 128 > (generator);
        double z2 = double(g - 0.5)*6;



        // MC integrating
        fx = func_brute(x1,y1,z1,x2,y2,z2);
        MCint += fx;
        sum_sigma += fx*fx;
    }

    // stops the clock
    end = clock();
    double runtime = double (end-start)/CLOCKS_PER_SEC;

    average_runtime += runtime;



    // calculating the mean integration results and the variance
    MCint = MCint / (double (n));
    sum_sigma = sum_sigma / (double (n));
    double variance = sum_sigma - MCint*MCint;

    double I = jacobi*MCint;
    double V = jacobi*variance;
    average_I += I;
    average_V += V;

    } //end of average loop

    average_I = average_I/(double(10));
    average_V = average_V/(double(10));
    average_runtime = average_runtime/(double(10));
    runtimes(p) = average_runtime;

    cout << endl << "Monte Carlo brute force used " << average_runtime << " seconds" << endl << endl;
    cout << "Standard deviation = " << jacobi*sqrt(average_V/(double(n))) << endl
         << "Variance = " << average_V << endl
         << "Integral = " << average_I << endl
         << "Exact = " << exact_solution << endl << "N = " << n << endl;


    if (save_results == "y"){
        if(p == 0){
        ofstream output;
        output.open("Results_BFMC_L3.txt",ios::out);
        output << "a,b = " << a << " , " << b << "   " << "N = " << n << "   " << "I = " << average_I << "   " << "V = " << average_V << endl;
        output.close();
    }
        else{
        ofstream output;
        output.open("Results_BFMC_L3.txt",ios::app);
        output << "a,b = " << a << " , " << b << "   " << "N = " << n << "   " << "I = " << average_I << "   " << "V = " << average_V << endl;
        output.close();

        }
  }


} // end of N loop




if (save_runtimes == "y"){
string filenameruntimes = "BFMC_Runtimes.txt";
ofstream output;
output.open(filenameruntimes,ios::out);
for (int i = 0;i<N_values.size();i++){
    output << N_values[i] << endl;
}
output << endl;
output << runtimes << endl;
output.close();
}
else{}

}
// end of main


