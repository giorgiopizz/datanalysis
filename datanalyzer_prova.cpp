//c++ datanalyzer_prova.cpp datanalyzer.cc -o datanalyzer `root-config --cflags --glibs`
#include "datanalyzer.h"
using namespace std;

Double_t fun(Double_t * x, Double_t * par){
         //la funzione è una somma di una gaussiana e un'esponenziale
        //[p0]*exp(-0.5*pow(((x-[p1])/[p2]),2))+[p3]*(exp(-x/[p4]))/[p4]
	return par[0]*exp(-0.5*pow(((x[0]-par[1])/par[2]),2))+par[3]*(exp(-x[0]/par[4]))/par[4];
}

int main(){


        string file1="data7.txt";
        TF1 * fitFunc1 =new TF1("funz", "[0]*((([1]**2)*cos(x)-sqrt([1]**2-sin(x)*sin(x)))/(([1]**2)*cos(x)+sqrt([1]**2-sin(x)*sin(x))))**2+[2]");
	fitFunc1->SetParameter(0,600.0);
	fitFunc1->SetParameter(1, 1.50);
	fitFunc1->SetParameter(2, 2.0 );
	string file2="data8.txt";
	TF1 * fitFunc2 =new TF1("funz", "[0]+[1]*x");
	fitFunc2->SetParameter(0,0);
	fitFunc2->SetParameter(1, 0);


        vector<string> files;
        files.push_back(file1);
        files.push_back(file2);
        vector <TF1*> funzioni;
        funzioni.push_back(fitFunc1);
        funzioni.push_back(fitFunc2);

        datanalyzer * dati= new datanalyzer(files, "measurement");
        //settare tutti i paramentri della funzione
        dati->fit(funzioni);
        //dati->display();
        dati->print();
}
