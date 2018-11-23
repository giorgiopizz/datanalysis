//inserire tutti gli include tranne analyzer_h e multiplot_h

/*Questa classe è molto simile ad analyzer.h e multiplot.h, pur non ereditando nulla da loro.
La classe datanalyzer può essere inizializzata con datanalyzer(), settando tutti i valori a 0.

Voglio fare in modo che per tracciare un grafico e il suo fit da datanalyzer_prova.cpp basti
scrivere datanalyzer(vettore di files,vettore di nomi, tipo); fit(TF1); display() o print();

*/

class datanalyzer{
public:

private:
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
};
