#ifndef analyzer_h
#define analyzer_h

#include <string>
#include <vector>
#include <fstream>

#include <TStyle.h>
#include <TH1D.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TMath.h>

#include <TApplication.h>
#include <TCanvas.h>


using namespace std;

class analyzer
{
 public:
  // Default constructor
  analyzer (string nome);

  // Destrusctor (!!! delete pointers if present !!!)
  ~analyzer ();

  // Read data from file and fill plot and vectors (TH1D for type  "counts" , TGraphErrors for type "measuremente")
  //bool setData (const string fileName, string type);
  bool setData (const string fileName, string type,double min=numeric_limits<double>::max(), double max=-numeric_limits<double>::max());

  void computeMoments (vector<double>* values, vector<double>*  errors, double& mean, double& stdDev, double& meanError);

  // Compute Chi-2, NDF and pValue when fitFunc is used to fit the TH1D or the TGrapgErrors
  void computeChi2 (TF1* fitFunc, double& chi2, int& NDF, double& pValue);

  // Fit the TH1D or TGraphErrors with a given function in a specific range
  void fitData (TF1* fitFunc, double xMin, double xMax);

  // Test whether two measurements are compatible using a statistical test set with testType: "Normal" or "tStudent"

  // Esample of Normal test with significance = 5%
  //   two measurements M1+\-sigma1 and M2+\-sigma2
  //   testCompatibility (pvalue, M1, sigma1, M2, sigma2, 0.05, "Gaussian")

  // Esample of t-Student test with significance = 5%
  //   two measurements estimated from two sets of data:
  //     - n1 measurements with average M1 and standard deviation of the n1 measurements sigma1
  //     - n2 measurements with average M2 and standard deviation of the n2 measurements sigma2
  //   testCompatibility (pvalue, M1, sigma1, M2, sigma2, 0.05, "tStudent", n1, n2)

  // Esample of t-Student test with significance = 5%
  //   one measurement estimated from a set of data:
  //     - n1 measurements with average M1 and standard deviation of the n1 measurements sigma1
  //   a reference value M2
  //   testCompatibility (pvalue, M1, sigma1, M2, 0, 0.05, "tStudent", n1)
  bool testCompatibility (double& pvalue, double meas1, double err1, double meas2, double err2, double significance, string testType, double n1 = 1, double n2 = 1);

  // Produce contour plot for DMinChi2 = delta
  TGraph* computeContour (TF1* myFun, double delta, unsigned int parA, unsigned int parB);
  //FUNZIONE AGGIUNTA DA ME: permette di creare una TApplication e una canvas e far vedere il grafico
  void Display();

  TH1D*           getHisto      (void);
  TGraphErrors*   getGraph      (void);
  double          getMeanX      (void) { return meanX_     ;}
  double          getMinX       (void) { return minX_      ;}
  double          getMaxX       (void) { return maxX_      ;}
  double          getStdDevX    (void) { return stdDevX_   ;}
  double          getMeanError  (void) { return meanError_ ;}
  int             getDataNumber (void) { return dataNumber_;}

  vector<double>* getxMeas      (void) { return &xMeas_    ;}
  vector<double>* getyMeas      (void) { return &yMeas_	   ;}
  vector<double>* getxErr       (void) { return &xErr_	   ;}
  vector<double>* getyErr       (void) { return &yErr_	   ;}
  //int getN(){return n;}
 private:
  string          nome;
  int             dataNumber_;
  double          minX_;
  double          maxX_;
  double  	  meanX_;
  double          stdDevX_ ;
  double          meanError_;
  vector <double> xMeas_;
  vector <double> yMeas_;
  vector <double> xErr_;
  vector <double> yErr_;

  TH1D*         histo_;
  TGraphErrors* graph_;
  TApplication * app_;
  TCanvas* cnv_;
};
#endif
