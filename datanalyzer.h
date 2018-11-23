#ifndef datanalyzer_h
#define datanalyzer_h
/*Questa classe è molto simile ad analyzer.h e multiplot.h, pur non ereditando nulla da loro.
Voglio fare in modo che per tracciare un grafico e il suo fit da datanalyzer_prova.cpp basti
scrivere datanalyzer(vettore di files,vettore di nomi, tipo); fit(TF1); display() o print();
Ci sarà un overloading del costruttore, e di fit permettendo di passare o un vettore o un solo
dato.
*/
#include <iostream>
#include <vector>
#include <string>
//includi tutte le estensioni di root
#include <fstream>

#include <TStyle.h>
#include <TH1D.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TMath.h>
#include <TFormula.h>
#include <TApplication.h>
#include <TCanvas.h>
using namespace std;
class datanalyzer{
public:

        datanalyzer(vector<string> files, string type, vector<string> names=vector<string>());
        datanalyzer(string file,string type, string name="Grafico");
        bool setData (string fileName,string name,double min=numeric_limits<double>::max(), double max=-numeric_limits<double>::max());
        void clean();
        void fit(vector<TF1*> funzioni);
        void fit(TF1* funzione);
        void display();
        void print();
        vector<int> fatt(int n);
private:

        int             n;
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
        string type;
        vector <TH1D*>         histo_;
        vector <TGraphErrors*> graph_;
        TH1D* histo;
        TGraphErrors* graph;

        TApplication * app_;
        TCanvas * cnv_;
};
#endif
