//---------------------------------------------------------------------------

#pragma hdrstop

#include "validador.h"
#include <fstream> 
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// testa se um arquivo com nome especificado existe
//---------------------------------------------------------------------------
bool arquivoExiste(string filename){
	ifstream Infield(filename);
	return Infield.good();
}

//---------------------------------------------------------------------------
// teste simples para ver se as linhas do arquivo texto correspondem
// a especificacao, soh verifica o numero de elementos.
//
// obs: os nomes dos produtos nao podem ter espaco, pois nao foi utilizado
// tags para eles e sim espacos para definir um elemento do outro, por isso
// os nomes dos produtos devem ter underline para os espacos
//---------------------------------------------------------------------------
bool arquivoEspecificacao(string n){

	string c,s;

	int i = 0;

	ifstream myfile(n);

	myfile.clear();
	myfile.seekg(0, ios::beg);

	while (myfile >> c){
		if (c == "#") {

			string substr;
			getline(myfile,s);
			istringstream iss(s);

			while (iss){

				getline(iss,substr,' ');
				i++;

			}

			if (i != 4) {
				return false;
			}

		}
		i = 0;
	}

	i = 0;

    myfile.clear();
	myfile.seekg(0, ios::beg);

    while (myfile >> c){
		if (c == ">") {

			string substr;
			getline(myfile,s);
			istringstream iss(s);

			while (iss){

				getline(iss,substr,' ');
				i++;

			}

			if (i != 7) {
				return false;
			}
		}
		i = 0;
	}

	myfile.close();

	return true;
}
