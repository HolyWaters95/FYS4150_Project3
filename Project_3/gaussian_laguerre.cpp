#include <iostream>
#include "lib.h"
#include <armadillo>
#include "time.h"

using namespace std;
using namespace arma;

double Gaussian_Legendre(double a, double b, int n, function<double(double)> f);
vector<int> readvalues(string file);

double int_function(double x1,double y1,double z1, double x2, double y2, double z2){
    double r1 = sqrt(x1*x1 + y1*y1 + z1*z1);
    double r2 = sqrt(x2*x2 + y2*y2 + z2*z2);
    double r1_r2 = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));
    if (r1_r2 < pow(10,-10)){return 0;}
    double I = exp(-4*(r1+r2))/r1_r2;
    return I;
}

double test(double x){
    return x*x;
}

int main(){

  string save_runtimes;
  cout << "do you want to save runtimes? y or n" << endl;
  cin >> save_runtimes;

  vector<int> N_values = readvalues("Pro3_Nvalues.txt");
  vector<int> X_values = readvalues("Pro3_Xvalues.txt");
  vec runtimes(N_values.size());


  for (int g = 0;g < X_values.size(); g+=2){
  for (int h = 0;h < N_values.size(); h++){

  int N = N_values[h];
  double a = X_values[g];
  double b = X_values[g+1];

  double *xr = new double[N];
  double *wr = new double[N];

  double *xt = new double[N];
  double *wt = new double[N];

  double *xp = new double[N];
  double *wp = new double[N];

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
  cout << I << endl;
  cout << 5*M_PI*M_PI/(256) << endl;


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
