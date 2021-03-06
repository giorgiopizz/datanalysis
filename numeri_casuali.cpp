//c++ numeri_casuali.cpp lib.cc -o numeri_casuali
#include "lib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;
int main(){
	srand(time(NULL));
	double min=0;
	double max=100;
	int nEstrazioni=100;
	int N=100000;
	ofstream myfile;
 	myfile.open("data6.txt");

	for (int i = 0; i< N/3;i++){
		double numero_casuale = rand_CLT(min, max, nEstrazioni);
		std::cout << "Numero casuale: " << numero_casuale << std::endl;
		myfile << numero_casuale<<"\n";
	}
	for (int i = 0; i< N/3;i++){
		double numero_casuale = rand_FCI_Exp(10);
		std::cout << "Numero casuale: " << numero_casuale << std::endl;
		myfile << numero_casuale<<"\n";
	}
	for (int i = 0; i< N/3;i++){
		double numero_casuale = rand_TAC(0,100,0.,1/M_PI);
		std::cout << "Numero casuale: " << numero_casuale << std::endl;
		myfile << numero_casuale<<"\n";
	}
	myfile.close();

	return 0;
}
