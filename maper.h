//---------------------------------------------------------------------------

#ifndef maperH
#define maperH
//---------------------------------------------------------------------------

#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <iterator>
#include <iomanip>
#include <fstream>
#include <string>
#include <utility>
#include <algorithm>
#include "validador.h"

using namespace std;

using std::istream_iterator;

class maper{
		map<pair<int,int>, vector<string>> porCodigo;
		map<string,vector<string>> porNomeProduto;
		map<int, string> porCategoria;
		map<string,int> porNomeCategoria;
		map<string,vector<string>> porListaCategorizada;
		vector<pair<string, int>> listaDeClientes;
		bool is_number(const std::string& s);
		bool isFloat(string myString);
	public:
		maper(string n);
		void makeCategoria(string n);
		void makeProduto(string n);
		void clearAll();
		void makeListaCategorizada(int c);
		map<string,vector<string>> getListaCategorizada();
		map<string,vector<string>> getListaTotal();
		map<pair<int,int>, vector<string>> getListaPorCodigo();
		map<string,int> getCategoria();
		void convertCodigoNome();
		void salvarMapProdutos(string n);
		bool incluirCategoria(string n);
		int incluirProduto(string p, int c, string tipo, string valor);
		bool excluirCategoria(int c);
		bool excluirProduto(int p);
		bool mudarValor(int p, float valor);
		int renomearCategoria(int c, string novo);
		int renomearProduto(int p, string novo);
		void makeListaDeClientes(string n);
		void setCliente(string n);
        bool renomearCliente(string n, int c);
		void salvarClientes(string n);
		void clearClientes();
		vector<pair<string, int>> getListaDeClientes();
};

#endif
