#include <iostream>
#include "lib.h"
#include <armadillo>
#include "time.h"

using namespace std;
using namespace arma;

vector<int> readvalues(string file);
double int_function_spherical(double r1,double r2,double t1,double t2,double p1,double p2);

void gauss_laguerre(double *x, double *w, int n, double alf);

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


  for (int h = 0;h < N_values.size(); h++){

  int N = N_values[h];


  double *xr = new double[N];
  double *wr = new double[N];

  double *xt = new double[N];
  double *wt = new double[N];

  double *xp = new double[N];
  double *wp = new double[N];

  time_t start, end;
  start = clock();

  //Array for Theta
  gauleg(0,M_PI,xt,wt,N);
  //Array for Phi
  gauleg(0,2*M_PI,xp,wp,N);
  //Array for radial part
  gauss_laguerre(xr,wr,N,0);

  //cout << *xr << endl;
  //cout << *wr << endl;
  //cout << *xt << endl;
  //cout << *wt << endl;
  //cout << *xp << endl;
  //cout << *wp << endl;
  double I = 0;
  for (int i=0; i<N;i++){
      for (int j=0; j<N;j++){
          for (int k=0; k<N;k++){
              for (int l=0; l<N;l++){
                  for (int m=0; m<N;m++){
                      for (int n=0; n<N;n++){
                          I += wr[i]*wr[j]*wt[k]*wt[l]*wp[m]*wp[n]*int_function_spherical(xr[i],xr[j],xt[k],xt[l],xp[m],xp[n]);
  }}}}}}
  end = clock();

  runtimes(h) = (double)(end-start)/CLOCKS_PER_SEC;

  //double I = Gaussian_Legendre(a,b,n,test);
  cout << I << endl;
  cout << 5*M_PI*M_PI/(256) << endl;

  if (save_results == "y"){
      if(h == 0){
      //string filenameresults = "Results_Laguerre.txt";
      ofstream output;
      output.open("Results_Laguerre.txt",ios::out);
      output << "N = " << N << "   " << "I = " << I << endl;
      output.close();
  }
      else{
      //string filenameresults = "Results_Laguerre.txt";
      ofstream output;
      output.open("Results_Laguerre.txt",ios::app);
      output << "N = " << N << "   " << "I = " << I << endl;
      output.close();

      }
}



  } //End N loop

  if (save_runtimes == "y"){
  string filenameruntimes = "Gauss_Laguerre_Runtimes.txt";
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
