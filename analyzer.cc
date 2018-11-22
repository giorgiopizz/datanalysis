#include "analyzer.h"
/*ATTENZIONE! Se l'istogramma non contiene tutti i valori è da controllare
minX_ e maxX_ in quanto è possibile che il valore 0 iniziale sia da spostare*/

analyzer::analyzer(string name): nome(name){
        //setto tutte le variabili a zero e i pointer a NULL

        dataNumber_=0;
        minX_=numeric_limits<double>::max();
        maxX_=-std::numeric_limits<double>::max();
        meanX_=0;
        stdDevX_=0;
        meanError_=0;
        xMeas_.clear();
        yMeas_.clear();
        xErr_.clear();
        yErr_.clear();
        histo_=NULL;
        graph_=NULL;
        app_=NULL;
        cnv_=NULL;
}
analyzer::~analyzer (){
        //elimino i pointer
        if (histo_!=NULL)    delete histo_;
        if (graph_!=NULL)   delete graph_;
        if (app_!=NULL)      delete app_;
        if (cnv_!=NULL)      delete cnv_;
}
bool analyzer::setData (const string fileName, string type,double min, double max){
      //questa funzione leggi i dati da un file, li memorizza in uno o più vettori
      //calcola il massimo, il minimo, il numero di dati e poi crea un istogrammma
      //o un TGraph
      ifstream InFile(fileName.c_str());
      if(InFile.good()==false){
            cout <<"Errore nell'apertura del file"<<endl;
            return false;
      }
      double x;
      int i=0;
      if(type=="counts"){
            if(min==numeric_limits<double>::max()&&max==-numeric_limits<double>::max()){
                    while(true){
                            InFile >> x;
                            i++;
                            xMeas_.push_back(x);
                            if(minX_>x)      minX_=x;
                            if(maxX_<x)      maxX_=x;
                            if(InFile.eof()==true)
                                    break;
                    }
            }
            else{
                    while(true){
                           InFile >> x;
                           i++;
                           xMeas_.push_back(x);
                           if(InFile.eof()==true)
                                    break;
                       }
            }
            InFile.close();
            dataNumber_=i;
      }
      else if (type=="measurement"){
            //prendo i dati per il TGraph
            double y, xerr, yerr;
            while(true){
                    InFile >> x >> y>> xerr>> yerr;
                    i++;
                    xMeas_.push_back(x);
                    yMeas_.push_back(y);
                    xErr_.push_back(xerr);
                    yErr_.push_back(yerr);
                    if(InFile.eof()==true)
                            break;
            }
            InFile.close();
            dataNumber_=i;
      }
      else{
            cout << "Tipo sbagliato"<<endl;
            return false;
      }
      if(InFile.eof()==true){
            //costruisco istogramma e TGraph
            if(type=="counts"){
                    int nBins=100;
                    /*string init= "Counts ";
                    string init2= "Plot ";
                    string fin= init+to_string(n);
                    string fin2= init2+to_string(n);*/
                    if(min==numeric_limits<double>::max()&&max==-numeric_limits<double>::max()){
                    	histo_=new TH1D(nome.c_str(), nome.c_str(), nBins, minX_, maxX_);
                    }
                    else{
                    histo_=new TH1D(nome.c_str(), nome.c_str(), nBins, min, max);
                    }
                     for(int j=0;j<dataNumber_;j++){
                            histo_->Fill(xMeas_.at(j));
                    }
                    //computeMoments(&xMeas_,&xErr_,meanX_,stdDevX_,meanError_);
            }
            else{
                    //sono certo che sia un TGraph in questo caso
                    graph_=new TGraphErrors(fileName.c_str());
                    graph_->SetTitle("Measurements");
                    graph_->GetXaxis()->SetTitle("x (units)");
                    graph_->GetYaxis()->SetTitle("y (units)");
                    graph_->SetMarkerStyle(20);
                    graph_->SetMarkerSize(0.5);
            }
      }
      return true;
}

TH1D* analyzer::getHisto(void){
        if(histo_!=NULL){
                return histo_;
                delete histo_;
        }
        else{
                cout << "Non è ancora stato inizializzato correttamente l'istogramma"<<endl;
                return NULL;
        }
}
TGraphErrors* analyzer::getGraph(void){
        if(graph_!=NULL){
                return graph_;
                delete graph_;
        }
        else{
                cout << "Non è ancora stato inizializzato correttamente il grafico"<<endl;
                return NULL;
        }
}
void analyzer::fitData (TF1* fitFunc, double xMin, double xMax){

        fitFunc->SetParameter(0,300);
        fitFunc->SetParameter(1,40);
        fitFunc->SetParameter(2,5);
        fitFunc->SetParameter(3,1);
        fitFunc->SetParameter(4,10);
        fitFunc->SetParName(0,"Ampl");
        fitFunc->SetParName(1,"Mean");
        fitFunc->SetParName(2,"Sigma");

        if (histo_!=NULL) histo_->Fit(fitFunc,"","",xMin,xMax);
}

/*
void analyzer::computeMoments (vector<double>* values, vector<double>*  errors, double& mean, double& stdDev, double& meanError){

}

void analyzer::computeChi2 (TF1* fitFunc, double& chi2, int& NDF, double& pValue){

}

void analyzer::fitData (TF1* fitFunc, double xMin, double xMax){

}

bool analyzer::testCompatibility (double& pvalue, double meas1, double err1, double meas2, double err2, double significance, string testType, double n1 = 1, double n2 = 1){
  //lo lascio
}

TGraph* analyzer::computeContour (TF1* myFun, double delta, unsigned int parA, unsigned int parB){
  //lo lascio
}*/
void analyzer::Display(){
        app_ = new TApplication("myApp",NULL,NULL);
        cnv_ = new TCanvas("myCanv","myCanv",0,0,700,500);
        cnv_->cd();
        if(histo_!=NULL) histo_->Draw();
        if(graph_!=NULL) graph_->Draw("AP");
        cnv_->Modified();
        cnv_->Update();
        app_->Run();
}
