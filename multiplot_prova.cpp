//c++ multiplot_prova.cpp multiplot.cc analyzer.cc -o multiplot `root-config --cflags --glibs`

#include "multiplot.h"

int main(){
	vector<string> files;
	files.push_back("data5.txt");

	vector<string> nomi;

	multiplot t(1,files,nomi,"counts");
	t.display();
	//t.print();
}
