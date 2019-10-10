#include <iostream>
#include "lib.h"
#include <armadillo>

using namespace std;
using namespace arma;

double Gaussian_Legendre(double a, double b, int n);

int main(){


  int n;
  double a, b;
  cout << "Read in the number of integration points" << endl;
  cin >> n;
  cout << "Read in integration limits" << endl;
  cin >> a >> b;
 
  double I = Gaussian_Legendre(a,b,n);
  cout << I << endl;
  return 0;}
