//lib.cc
#include "lib.h"
#include <cmath>
#include <cstdlib>

double rand_range(double min, double max){
	return min + (max-min) * (1. * rand()) / (1. * RAND_MAX);
}

double rand_CLT(double xMin, double xMax, int tries){
	double x= 0.;
	for (int i =0;i<tries;i++){
		x+=rand_range(xMin,xMax);
	}
	return x/tries;
}

double f_Cauchy(double x){
	double c = 1/(M_PI*(1+x*x));
	return c;
}
double rand_TAC(double xMin, double xMax, double yMin, double yMax){
	//usa il metodo try and catch
	double x=0., y=0.;
	do{
		x=rand_range(xMin,xMax);
		y=rand_range(yMin,yMax);
	} while(y>f_Cauchy(x));
	return x;
}

double rand_FCI_Exp(double mu){
	//funzione di densità di probabilità
	//uso la funzione cumulativa inversa
	double y = rand_range(0., 1.);
	while(y==1.){
		y=rand_range(0.,1.);
	}
	double x = -mu*log(1-y);
	return x;
}
