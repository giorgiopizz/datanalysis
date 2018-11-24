#include "datanalyzer.h"
using namespace std;

datanalyzer::datanalyzer(vector<string> files, string tipo, vector<string> names){
        type=tipo;
        if(files.empty()){
            throw invalid_argument("File is empty") ;
        }
        else{
            string nome="";
            for (int i = 0; i < files.size(); i++) {
                if(names.size()==files.size())
                        nome=names.at(i);
                else
                        nome=to_string(i+1);
                if(!setData(files.at(i), nome))
                        cout << "Errore nella lettura dei dati" <<endl;
            }
        }

}
datanalyzer::datanalyzer(string file, string tipo,string name ){
        type=tipo;
        if(file.empty()){
            throw invalid_argument("File is empty") ;
        }

        string nome="";

        if(name!="")
                nome=name;
        else
                nome=to_string(1);
        if(!setData(file, nome))
                cout << "Errore nella lettura dei dati" <<endl;

}
bool datanalyzer::setData (string fileName,string name, double min, double max){
      //questa funzione leggi i dati da un file, li memorizza in uno o più vettori
      //calcola il massimo, il minimo, il numero di dati e poi crea un istogrammma
      //o un TGraph
      clean();
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
              cout << "errore nel type" <<"\n"<<type<<endl;
      }
      if(InFile.eof()==true){
            //costruisco istogramma
            if(type=="counts"){
                    int nBins=100;
                    if(min==numeric_limits<double>::max()&&max==-numeric_limits<double>::max()){
                    	    histo=new TH1D(name.c_str(), name.c_str(), nBins, minX_, maxX_);
                    }
                    else{
                            //l'utente vuole che si faccia l'istogramma di solo una porzione di grafico
                            histo=new TH1D(name.c_str(), name.c_str(), nBins, min, max);
                    }
                    for(int j=0;j<dataNumber_;j++){
                            histo->Fill(xMeas_.at(j));
                    }
                    histo_.push_back(histo);
                    n=histo_.size();
           }
           else{
                   cout << fileName.c_str()<<endl;
                   //graph=new TGraphErrors(fileName.c_str());
                   double * xmeas = &xMeas_[0];
                   double * ymeas = &yMeas_[0];
                   double * xerr = &xErr_[0];
                   double * yerr = &yErr_[0];

                   graph=new TGraphErrors(dataNumber_,xmeas,ymeas,xerr,yerr);
                   graph->SetTitle("Measurements");
                   graph->GetXaxis()->SetTitle("x (units)");
                   graph->GetYaxis()->SetTitle("y (units)");
                   graph->SetMarkerStyle(20);
                   graph->SetMarkerSize(0.5);
                   graph_.push_back(graph);
                   n=graph_.size();
           }
      }

      return true;
}
void datanalyzer::clean(){
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
        histo=NULL;
        graph=NULL;
}
void datanalyzer::fit(vector<TF1*> funzioni){
        if (!histo_.empty()){
                if(funzioni.size()==histo_.size()){
                        for(int i=0;i<funzioni.size();i++){
                                histo_.at(i)->Fit(funzioni.at(i));
                        }
                }
                else{
                        cout <<"numero di funzioni inserite diverso da numero files"<<endl;
                }
        }
        else if (!graph_.empty()){
                if(funzioni.size()==graph_.size()){
                        for(int i=0;i<funzioni.size();i++){
                                graph_.at(i)->Fit(funzioni.at(i));
                        }
                }
                else{
                        cout <<"numero di funzioni inserite diverso da numero files"<<endl;
                }
        }
}
void datanalyzer::fit(TF1* funzione){
        if (!histo_.empty()) histo_.at(0)->Fit(funzione);
        if (!graph_.empty()) graph_.at(0)->Fit(funzione);
}
void datanalyzer::display(){
        //se [dati] è un oggetto valido parte l'applicazione, altrimenti blocco tutto e chiudo
        if(!histo_.empty() || !graph_.empty()) {

            app_ = new TApplication("myApp", NULL, NULL);
            cnv_ = new TCanvas("myCanv", "myCanv", 0, 0, 1200, 800);
            //fatt fattorizza n e divide la griglia secondo i suoi fattori

            if(n!=1){
            	if(fatt(n).size()!=0){
            	    cnv_->Divide(fatt(n).at(1),fatt(n).at(0));
           	 }
            	else{
            	    cout << "Il numero di file non va bene"<<endl;
            	    return;
            	}
            }

            for (int i = 0; i < n; i++) {
                cnv_->cd(i + 1);
                gStyle->SetOptFit(1111);
                if (type == "counts") {
                    histo_.at(i)->SetFillColor(i);
                    histo_.at(i)->Draw();
                }
                else if (type == "measurement") {

                    graph_.at(i)->Draw("AP");
                }
            }

            cnv_->Modified();
            cnv_->Update();
            app_->Run();
        }
        else{
                cout << "Could not start application: bad class object" <<endl;
        }

}

void datanalyzer::print(){
        //se [dati] è un oggetto valido parte l'applicazione, altrimenti blocco tutto e chiudo
        if(!histo_.empty() || !graph_.empty()) {
            cnv_ = new TCanvas("myCanv", "myCanv", 0, 0, 1200, 800);
            //fatt fattorizza n e divide la griglia secondo i suoi fattori

            if(n!=1){
            	if(fatt(n).size()!=0){
            	    cnv_->Divide(fatt(n).at(1),fatt(n).at(0));
           	 }
            	else{
            	    cout << "Il numero di file non va bene"<<endl;
            	    return;
            	}
            }
            TCanvas * tmp = new TCanvas("temp","temp",0,0,1200,800);
            for (int i = 0; i < n; i++) {

		tmp->cd();
                gStyle->SetOptFit(1111);
                if (type == "counts") {
                    histo_.at(i)->SetFillColor(i);
                    histo_.at(i)->Draw();
                }
                else if (type == "measurement") {
                    graph_.at(i)->Draw("AP");
                }
                string file="picss/"+to_string(i+1)+".png";
                tmp->Print(file.c_str());
                cnv_->cd(i + 1);
                tmp->DrawClonePad();
            }
            cnv_->Print("picss/finale.png");
	    delete tmp;
        }
        else{
                cout << "Could not start application: bad class object" <<endl;
        }
}
vector<int> datanalyzer::fatt(int n){
        vector<int> fattori;
        for(int i=0;i<=n;i++){
                for(int j=0;j<n;j++){
                        if(i*j==n&&(i!=1)){
                                fattori.push_back(i);
                                fattori.push_back(j);
                                break;
                        }
                }
        }
        return fattori;
}
