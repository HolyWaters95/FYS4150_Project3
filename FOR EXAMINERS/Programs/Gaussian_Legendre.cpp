#include <iostream>
#include <fstream>
#include "lib.h"
#include <armadillo>
#include "time.h"

using namespace std;
using namespace arma;

double Gaussian_Legendre(double a, double b, int n, function<double(double)> f);
vector<int> readvalues(string file);

double int_function(double x1,double y1,double z1, double x2, double y2, double z2);

double test(double x){
    return x*x;
}

int main(){

  string save_runtimes;
  string save_results;
  cout << "do you want to save runtimes? y or n" << endl;
  cin >> save_runtimes;
  cout << "do you want to save results? y or n" << endl;
  cin >> save_results;


  vector<int> N_values = readvalues("Pro3_Nvalues.txt");
  vector<int> X_values = readvalues("Pro3_Xvalues.txt");
  vec runtimes(N_values.size());


  for (int g = 0;g < X_values.size(); g+=2){
  for (int h = 0;h < N_values.size(); h++){

  int N = N_values[h];
  double a = X_values[g];
  double b = X_values[g+1];
  double *x = new double[N];
  double *w = new double[N];

  time_t start, end;
  start = clock();
  gauleg(a,b,x,w,N);
  double I = 0;
  for (int i=0; i<N;i++){
      for (int j=0; j<N;j++){
          for (int k=0; k<N;k++){
              for (int l=0; l<N;l++){
                  for (int m=0; m<N;m++){
                      for (int n=0; n<N;n++){
                          I += w[i]*w[j]*w[k]*w[l]*w[m]*w[n]*int_function(x[i],x[j],x[k],x[l],x[m],x[n]);
  }}}}}}
  end = clock();

  if (g==0){runtimes(h) = (double)(end-start)/CLOCKS_PER_SEC;}

  //double I = Gaussian_Legendre(a,b,n,test);
  cout << "---------------------------------" << endl;
  cout << "N = " << N << " | L = " << b << endl;
  cout << "I= " << I << endl;
  //cout << 5*M_PI*M_PI/(256) << endl;
  cout << "Runtime = " << (double)(end-start)/CLOCKS_PER_SEC << endl;

  if (save_results == "y"){
      if(g == 0 and h == 0){
      string filenameresults = "Results_Legendre.txt";
      ofstream output;
      output.open("Results_Legendre.txt",ios::out);
      output << "a,b = " << a << " , " << b << "   " << "N = " << N << "   " << "I = " << I << endl;
      output.close();
  }
      else{
      string filenameresults = "Results_Legendre.txt";
      ofstream output;
      output.open("Results_Legendre.txt",ios::app);
      output << "a,b = " << a << " , " << b << "   " << "N = " << N << "   " << "I = " << I << endl;
      output.close();

      }
}

  } //End N loop
  } //End X loop

  if (save_runtimes == "y"){
  string filenameruntimes = "Gauss_Legendre_Runtimes.txt";
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

  return 0;}
