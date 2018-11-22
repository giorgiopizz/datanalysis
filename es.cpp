//c++ es.cpp analyzer.cc -o es `root-config --cflags --glibs`
#include <iostream>
#include "analyzer.h"
/* display() e analyzer::Display() fanno praticamente la stessa cosa
solo che display() permette di lavorare con più analyzer e quindi fare
un grafico unico o un istogramma unico
*/
void display(TH1D* histo){
        TApplication* app= new TApplication("myApp",NULL,NULL);
        TCanvas* cnv = new TCanvas("myCanv","myCanv",0,0,700,500);

        cnv->cd();
        histo->Draw();
        //if(graph_!=NULL) graph_->Draw("AP");
        cnv->Modified();
        cnv->Update();
        app->Run();
}
int main(){
        analyzer * p=new analyzer("grafico");
        p->setData("data5.txt", "counts");
        //display(p->getHisto());
        p->Display();
        delete p;
        return 0;
}
