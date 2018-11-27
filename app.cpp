//c++ app.cpp datanalyzer.cc -o app `root-config --cflags --glibs`
#include "datanalyzer.h"
using namespace std;


int main(){
	int n;
	cout << "Benvenuto! Quanti file devi analizzare?"<<endl;
	cin >> n;
	if(n==1){
		cout << "Inserisci il tipo se counts o measurement(c/m):" << endl;
		char tipo;
		cin >> tipo;
		char f;
		cout << "Fittare le funzioni?(y/n)" << endl;
		cin >> f;
		cout << "Inserisci il nome del file" <<endl;
		string file;
		cin >> file;
		string type;
		if(tipo=='c'){
			type="counts";
		}
		else if(tipo=='m'){

			type="measurement";
		}
		else{
			cout << "Tipo sbagliato" <<endl;
			exit (EXIT_FAILURE);
			type="none";
		}
		datanalyzer * dati= new datanalyzer(file,type);


		if(f=='y'){
			cout << "Inserisci la funzione da fittare" << endl;
			string funzione;
			cin >> funzione;
			TF1 * fitFunc1 =new TF1("funz",funzione.c_str());
			//aggiungere la possibilità di settare i parametri iniziali
			cout << "Inserisci i valori iniziali per i parametri,inserire * alla fine" <<endl;
			string par;
			cin >> par;
			int i=0;
			while(par!="*"){
				//parametri.push_back(stod(par));
				fitFunc1->SetParameter(i, stod(par));
				i++;
				cin >> par;
			}
			dati->fit(fitFunc1);
		}
		char scelta;
		cout << "Salvare su file o aprire applicazione?(p/d):"<<endl;
		cin >> scelta;
		if(scelta=='p'){
			dati->print();
		}
		else if(scelta=='d'){
			dati->display();
		}
	}
	else{
		vector<string> files;
		vector <TF1*> funzioni;
		cout << "Inserisci il tipo se counts o measurement(c/m):" << endl;
		char tipo;
		cin >> tipo;
		string file;
		string funzione;
		char f;
		cout << "Fittare le funzioni?(y/n)" << endl;
		cin >> f;
		for(int i=0;i<n;i++){
			cout << "Inserisci il nome del file" <<endl;
			cin >> file;
			files.push_back(file);
			if(f=='y'){
				cout << "Inserisci la funzione da fittare" << endl;
				cin >> funzione;
				TF1 * fitFunc =new TF1("funz",funzione.c_str());
				funzioni.push_back(fitFunc);
				//aggiungere la possibilità di settare i parametri iniziali
				cout << "Inserisci i valori iniziali per i parametri,inserire * alla fine" <<endl;
				string par;
				cin >> par;
				int i=0;
				while(par!="*"){
					//parametri.push_back(stod(par));
					fitFunc->SetParameter(i, stod(par));
					i++;
					cin >> par;
				}
			}
		}
		string type;
		if(tipo=='c'){
			type="counts";
		}
		else if(tipo=='m'){

			type="measurement";
		}
		else{
			cout << "Tipo sbagliato" <<endl;
			exit (EXIT_FAILURE);
			type="none";
		}
		datanalyzer * dati= new datanalyzer(files,type);
		if(f=='y'){
			dati->fit(funzioni);
		}
		char scelta;
		cout << "Salvare su file o aprire applicazione?(p/d):"<<endl;
		cin >> scelta;
		if(scelta=='p'){
			dati->print();
		}
		else if(scelta=='d'){
			dati->display();
		}

	}
}
