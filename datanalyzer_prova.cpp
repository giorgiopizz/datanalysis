//c++ datanalyzer_prova.cpp datanalyzer.cc -o datanalyzer `root-config --cflags --glibs`
#include "datanalyzer.h"
using namespace std;

Double_t fun(Double_t * x, Double_t * par){
         //la funzione è una somma di una gaussiana e un'esponenziale
        //[p0]*exp(-0.5*pow(((x-[p1])/[p2]),2))+[p3]*(exp(-x/[p4]))/[p4]
	return par[0]*exp(-0.5*pow(((x[0]-par[1])/par[2]),2))+par[3]*(exp(-x[0]/par[4]))/par[4];
}

int main(){
        //datanalyzer con più files e grafici
        /*
        vector<string> files;
        vector<string> names;
	files.push_back("data5.txt");
        datanalyzer * dati= new datanalyzer(files,names, "counts");
        vector<TF1*> funzioni;
        //funzioni.push_back(new TF1 ("c","gaus"));
        for(int i=0;i<funzioni.size();i++){
                //settare tutti i paramentri della funzione
                //funzioni.at(i)->SetParameter(0,20);
        }
        dati->fit(funzioni);
        dati->display();*/
        //dati->print();
        //datanalyzer con un solo file

        //string name;

        string file1="data6.txt";
        /*TF1 * fitFunc1 =new TF1("funz", "gaus(0)",0, 100);
        string file2="data5.txt";
        TF1 * fitFunc =new TF1("fun", "gaus(0)+[p3]*(exp(-x/[p4]))/[p4]",0, 100);
        fitFunc->SetParameter(0,300);
        fitFunc->SetParameter(1,40);
        fitFunc->SetParameter(2,5);
        fitFunc->SetParameter(3,1);
        fitFunc->SetParameter(4,10);
        fitFunc->SetParName(0,"Ampl");
        fitFunc->SetParName(1,"Mean");
        fitFunc->SetParName(2,"Sigma");

        vector<string> files;
        files.push_back(file1);
        files.push_back(file2);
        vector <TF1*> funzioni;
        funzioni.push_back(fitFunc1);
        funzioni.push_back(fitFunc);
*/
        datanalyzer * dati= new datanalyzer(file1, "counts");
        //settare tutti i paramentri della funzione
        //dati->fit(funzioni);
        dati->display();
        //dati->print();
}
