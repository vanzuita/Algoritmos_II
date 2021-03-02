//---------------------------------------------------------------------------

#ifndef menuH
#define menuH
//---------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include "maper.h"
#include "mostrar.h"
#include "validador.h"
#include "venda.h"

using namespace std;

class menu {
		maper *a;
		mostrar *m ;
        venda *v;
		bool flag1;
        bool flag2;
		bool is_number(const std::string& s);
		bool isFloat(string myString);
	public:
		menu();
        void menuCabecalho();
        void menuRenomearCliente();
		void menuCadastrarCliente();
		void menuPesquisarClienteNome();
		void menuPesquisarClienteID();
		void menuCliente();
        void menuListarClientes();
		void menuCadastrarProduto();
        void menuMudaValorProduto();
		void menuRenomearProduto();
		void menuExcluirProduto();
		void menuPesquisarNome();
		void menuPesquisarProdutoID();
		void menuListarPorCategoria();
		void menuListarTodos();
		void menuProduto();
		void menuCadastrarCategoria();
		void menuRenomearCategoria();
		void menuExcluirCategoria();
		void menuListarCategorias();
		void menuCategoria();
		void menuHelp();
		void menuSalvarListaProdutos();
		void menuSalvarListaClientes();
		void menuCarregarListaProdutos();
		void menuCarregarListaClientes();
		void menuCarregarListaVendas();
		void menuArquivos();
		void menuIniciarVenda();
		void menuToDo();
		void menuPesquisarCodigoVenda();
		void menuPesquisarVendaPorCodigo();
		void menuPesquisarTotalCliente();
		void menuPesquisarTotalCategoria();
		void menuPesquisarTotalProduto();
		void menuVendas();
};

#endif
