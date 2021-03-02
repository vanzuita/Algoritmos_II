//---------------------------------------------------------------------------

#ifndef mostrarH
#define mostrarH
//---------------------------------------------------------------------------

#include <algorithm>
#include "maper.h"




class mostrar{
		void mostra(map<string,vector<string>> m);
		maper *a;
		bool sortByVal(const pair<string, int>& a, const pair<string, int>& b);
	public:
		mostrar(maper *_a);
		void mostraCategorizada(int n);
		void mostraTotal();
		void mostraListaDeCategorias();
		void mostraListaDeClientes();
		void mostraPesquisaPorNomeCliente(string n);
		void mostraPesquisaPorIdCliente(int c);
		void mostraPesquisaPorNomeProduto(string n);
		void mostraPesquisaPorIdProduto(int p);
};


#endif
