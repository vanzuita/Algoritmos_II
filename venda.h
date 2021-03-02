//---------------------------------------------------------------------------

#ifndef vendaH
#define vendaH
//---------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include "validador.h"
#include "mostrar.h"
#include "maper.h"

using namespace std;

class venda{
		string nomeArquivo;
		mostrar *m;
		maper *ma;
		string listaDeVendas[2000];
		void carregarListaDeVendas(int j, string total);
		bool is_number(const std::string& s);
		bool isFloat(string myString);
	public:
		venda(string n, mostrar *_m, maper *_ma);
		void carregarArquivoVendas(string n);
		void pesquisarCodigoDeVenda();
		void pesquisarVendaPorCodigo(string c);
		void pesquisarTotalPorCliente(string c);
		void pesquisarTotalPorCategoria(string c);
		void pesquisarTotalPorProduto(string c);
		void menuCabecalho();
		void menuCabecalho2();
		void iniciarVenda();
};

#endif
