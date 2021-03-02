//---------------------------------------------------------------------------

#pragma hdrstop

#include "menu.h"
//---------------------------------------------------------------------------

//-----------------------------------------------------------------------
// A funcao is_number eh usada para verificar se uma string eh um numero
//-----------------------------------------------------------------------
bool menu::is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

//-----------------------------------------------------------------------
// A funcao isFloat eh usada para verificar se uma string eh um float
//-----------------------------------------------------------------------
bool menu::isFloat( string myString ) {
	std::istringstream iss(myString);
	float f;
	iss >> noskipws >> f; // noskipws considers leading whitespace invalid
	// Check the entire string was consumed and if either failbit or badbit is set
	return iss.eof() && !iss.fail();
}

void menu::menuCabecalho(){
	system("CLS");
	cout << setw(85) << setfill('-');
	cout << "\n\n";
	cout << setw(50) << setfill(' ') << "Vendas Varejo ver. 0.1" << "\n\n";
	cout << setw(85) << setfill('-') << "\n\n";
}

void menu::menuCadastrarCliente(){

	char nome[30];

	int length;

	menuCabecalho();
	cout << "\n\n\n\n\n" << "Digite o nome do novo cliente: ";

	fseek(stdin, 0, SEEK_END);
	fgets(nome,30,stdin);
	length = strlen(nome);
	nome[length-1] = '\0';
	string s = nome;

	a->setCliente(s);

	cout << "\n\n\n" << "Cliente cadastrado." << "\n\n" << "Pressione enter para continuar";
	fseek(stdin,0,SEEK_END);
	getchar();
	flag2 = true;
}

void menu::menuRenomearCliente(){

	string n;
	int n2;
	char n3[30];
	int length;

	do{
		menuCabecalho();
		cout << "\n\n\n\n\n" << "Digite o numero do cliente (digite p para pesquisar): ";
		fseek(stdin, 0, SEEK_END);
		cin >> n;
		if (n == "p") {
			m->mostraListaDeClientes();
		}
	} while (!is_number(n));

	istringstream ( n ) >> n2;

	cout << "\n\n" << "Digite o novo nome do cliente: ";

	fseek(stdin,0,SEEK_END);
	fgets(n3,30,stdin);
	length = strlen(n3);
	n3[length-1] = '\0';
	string s = n3;

	if (a->renomearCliente(n3,n2)) {
		cout << "\n\n" << "Cliente Renomeado" << "\n\n" << "Pressione enter para continuar";
		fseek(stdin,0,SEEK_END);
		getchar();
		flag2 = true;
	} else{
		cout << "\n\n" << "Nao existe este numero de cliente" << "\n\n" << "Pressione enter para continuar";
		fseek(stdin,0,SEEK_END);
		getchar();
	}
}

void menu::menuListarClientes(){

	m->mostraListaDeClientes();
}

void menu::menuPesquisarClienteNome(){

	char n[30];

	int length;

	menuCabecalho();

	cout << "\n\n" << "Pesquisa por nome. CUIDADO -> O algoritmo diferencia letra Maiuscula de Minuscula.";

	cout << "\n\n\n" << "Digite o nome que deseja pesquisar: ";

	fseek(stdin,0,SEEK_END);
	fgets(n,30,stdin);
	length = strlen(n);
	n[length-1] = '\0';
	string s = n;

	m->mostraPesquisaPorNomeCliente(s);
}

void menu::menuPesquisarClienteID(){

	string c;

	int c2;

	do{
		menuCabecalho();
		cout << "\n\n\n\n\n\n\n" << "Digite o codigo do cliente que deseja pesquisar: ";
		fseek(stdin,0,SEEK_END);
		cin >> c;
	} while (!is_number(c));

	istringstream ( c ) >> c2;

	m->mostraPesquisaPorIdCliente(c2);
}

void menu::menuCliente(){

	int op = -1;

	string op2;

	while (op != 0){

		menuCabecalho();
		cout << setw(30) << setfill(' ') << "1. Cadastrar Cliente" << '\n';
		cout << setw(29) << setfill(' ') << "2. Renomear Cliente" << '\n';
		cout << setw(28) << setfill(' ') << "3. Listar Clientes" << '\n';
		cout << setw(39) << setfill(' ') << "4. Pesquisar Cliente por Nome" << '\n';
		cout << setw(37) << setfill(' ') << "5. Pesquisar Cliente por ID" << '\n';
		cout << setw(19) << setfill(' ') << "0. Voltar" << '\n';
		cout << '\n' << setw(10) << setfill(' ') << "Opcao: ";
		fseek(stdin, 0, SEEK_END);
		cin >> op2;
		if (!is_number(op2)) {
			cout << "\n" << "Opcao invalida - Tecle enter para continuar";
			fseek(stdin,0,SEEK_END);
			getchar();
		}else{
			istringstream ( op2 ) >> op;
			switch (op){

				case 1: menuCadastrarCliente(); break;
				case 2: menuRenomearCliente(); break;
				case 3: menuListarClientes(); break;
				case 4: menuPesquisarClienteNome(); break;
				case 5: menuPesquisarClienteID(); break;
				case 0: break;


			default: cout << "\n" << "Opcao invalida - Tecle enter para continuar";
					fseek(stdin,0,SEEK_END);
					getchar();
					break;
			}
		}
	}
}

void menu::menuCadastrarProduto(){

	char nome[30];
	string c;
	int c2, length;
	string tipo;
	string f;
	float f2;

	menuCabecalho();

	cout << "\n\n\n\n\n" << "Digite o nome do produto (max 30 letras): ";

	fseek(stdin,0,SEEK_END);
	fgets(nome,30,stdin);
	length = strlen(nome);
	nome[length-1] = '\0';
	string s = nome;

	transform(s.begin(), s.end(), s.begin(), [](char ch) {
		return ch == ' ' ? '_' : ch;
	});

	cout << "\n\n" << "Digite o numero da categoria que deseja incluir o produto (digite p para pesquisar): ";
	fseek(stdin,0,SEEK_END);
	cin >> c;
	if (c == "p") {
		m->mostraListaDeCategorias();
	}

	if (!is_number(c)) {

		do{
			menuCabecalho();
			cout << "\n\n\n\n\n\n\n" << "Digite o numero da categoria que deseja incluir o produto (digite p para pesquisar): ";
			fseek(stdin,0,SEEK_END);
			cin >> c;
			if (c == "p") {
				m->mostraListaDeCategorias();
			}
		} while (!is_number(c));
	}

	istringstream ( c ) >> c2;

	cout << "\n\n" << "Digite o tipo de venda do produto (un ou kg): ";
	fseek(stdin,0,SEEK_END);
	cin >> tipo;

	if ((tipo != "un") && (tipo != "kg")){
		do{
			menuCabecalho();
			cout << "\n\n\n\n\n\n\n\n\n" << "Digite o tipo de venda do produto (un ou kg): ";
			fseek(stdin,0,SEEK_END);
			cin >> tipo;
		} while ((tipo != "un") && (tipo != "kg"));
	}

	cout << "\n\n" << "Digite o valor do produto (use virgula para o decimal): ";
	fseek(stdin,0,SEEK_END);
	cin >> f;

	if (is_number(f)) {
		f = f + ",00";
		f2 = stof(f);
	}

	if (!isFloat(f)) {
		do{
			menuCabecalho();
			cout << "\n\n\n\n\n\n\n\n\n\n\n" << "Digite o valor do produto (use virgula para o decimal): ";
			fseek(stdin,0,SEEK_END);
			cin >> f;
			if (is_number(f)) {
				f = f + ",00";
				f2 = stof(f);
			}
		} while (!isFloat(f));
	}

	if (isFloat(f)) {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << f2;
		f = stream.str();
	}

	switch (a->incluirProduto(s,c2,tipo,f)){

		case 0: cout << "\n" << "Produto cadastrado" << "\n\n" << "Pressione enter para continuar";
				fseek(stdin,0,SEEK_END);
				getchar();
				flag1 = true;
				break;
		case 1: cout << "\n" << "Nao existe a categoria" << "\n\n" << "Pressione enter para continuar";
				fseek(stdin,0,SEEK_END);
				getchar();
				break;
		case 2: cout << "\n" << "Ja existe um produto com esse nome" << "\n\n" << "Pressione enter para continuar";
				fseek(stdin,0,SEEK_END);
				getchar();
				break;
	}
}

void menu::menuMudaValorProduto(){

	string c;
	int c2;
	float f;
	string f2;

	menuCabecalho();

	cout << "\n\n\n\n\n" << "Digite o codigo do produto que deseja alterar o valor (digite p para pesquisar): ";

	fseek(stdin,0,SEEK_END);
	cin >> c;

	if (c == "p") {
		m->mostraTotal();
	}

	if (!is_number(c)) {

		do{
			system("CLS");
			cout << "\n\n";
			cout << setw(50) << setfill(' ') << "Vendas Varejo" << "\n\n";
			cout << setw(100) << setfill('-') << "\n\n";
			cout << "\n\n\n\n\n" << "Digite o codigo do produto que deseja alterar o valor (digite p para pesquisar): ";
			fseek(stdin,0,SEEK_END);
			cin >> c;
			if (c == "p") {
				m->mostraTotal();
			}
		} while (!is_number(c));
	}

	istringstream ( c ) >> c2;

	cout << "\n\n" << "Digite o valor do produto (use virgula para o decimal): ";
	fseek(stdin,0,SEEK_END);
	cin >> f2;

	if (!isFloat(f2)) {
		do{
			menuCabecalho();
			cout << "\n\n\n\n\n\n\n\n\n\n\n" << "Digite o valor do produto (use virgula para o decimal): ";
			fseek(stdin,0,SEEK_END);
			cin >> f2;
		} while (!isFloat(f2));
	}

	istringstream ( f2 ) >> f;

	if (a->mudarValor(c2,f)) {

		cout << "\n\n" << "Valor alterado" << "\n\n" << "Pressione enter para continuar";
		fseek(stdin,0,SEEK_END);
		getchar();
		flag1 = true;
	}else{
		cout << "\n\n" << "Nao existe produto cadastrado com este numero" << "\n\n" << "Pressione enter para continuar";
		fseek(stdin,0,SEEK_END);
		getchar();
	}
}

void menu::menuRenomearProduto(){

	string c;
	int c2;
	char n[30];
	int length;

	menuCabecalho();

	cout << "\n\n\n\n\n" << "Digite o codigo do produto que deseja renomear (digite p para pesquisar): ";

	fseek(stdin,0,SEEK_END);
	cin >> c;

	if (c == "p") {
		m->mostraTotal();
	}

	if (!is_number(c)) {

		do{
			menuCabecalho();
			cout << "\n\n\n\n\n" << "Digite o codigo do produto que deseja renomear (digite p para pesquisar): ";
			fseek(stdin,0,SEEK_END);
			cin >> c;
			if (c == "p") {
				m->mostraTotal();
			}
		} while (!is_number(c));
	}

	istringstream ( c ) >> c2;

	cout << "\n\n" << "Digite o novo nome do produto: ";

	fseek(stdin,0,SEEK_END);
	fgets(n,30,stdin);
	length = strlen(n);
	n[length-1] = '\0';
	string s = n;

	transform(s.begin(), s.end(), s.begin(), [](char ch) {
		return ch == ' ' ? '_' : ch;
	});

	switch (a->renomearProduto(c2,s)){

		case 0: cout << "\n" << "Produto Renomeado" << "\n\n" << "Pressione enter para continuar";
				fseek(stdin,0,SEEK_END);
				getchar();
				flag1 = true;
				break;
		case 1: cout << "\n" << "Nao existe este codigo de produto" << "\n\n" << "Pressione enter para continuar";
				fseek(stdin,0,SEEK_END);
				getchar();
				break;
		case 2: cout << "\n" << "Ja existe um produto com esse nome" << "\n\n" << "Pressione enter para continuar";
				fseek(stdin,0,SEEK_END);
				getchar();
				break;
	}
}

void menu::menuExcluirProduto(){

	string c;
	int c2;

	menuCabecalho();

	cout << "\n\n\n\n\n" << "Digite o codigo do produto que deseja excluir (digite p para pesquisar): ";

	fseek(stdin,0,SEEK_END);
	cin >> c;

	if (c == "p") {
		m->mostraTotal();
	}

	if (!is_number(c)) {

		do{
			system("CLS");
			cout << "\n\n";
			cout << setw(50) << setfill(' ') << "Vendas Varejo" << "\n\n";
			cout << setw(100) << setfill('-') << "\n\n";
			cout << "\n\n\n\n\n" << "Digite o codigo do produto que deseja excluir (digite p para pesquisar): ";
			fseek(stdin,0,SEEK_END);
			cin >> c;
			if (c == "p") {
				m->mostraTotal();
			}
		} while (!is_number(c));
	}

	istringstream ( c ) >> c2;

	if (a->excluirProduto(c2)) {
		cout << "\n\n" << "Produto excluido" << "\n\n" << "Pressione enter para continuar";
		fseek(stdin,0,SEEK_END);
		getchar();
		flag1 = true;
	}else{
		cout << "\n\n" << "Nao existe este codigo de produto" << "\n\n" << "Pressione enter para continuar";
		fseek(stdin,0,SEEK_END);
		getchar();
	}

}

void menu::menuPesquisarNome(){

    char n[30];

	int length;

	menuCabecalho();

	cout << "\n\n" << "Pesquisa por nome. CUIDADO -> O algoritmo diferencia letra Maiuscula de Minuscula.";

	cout << "\n\n\n" << "Digite o nome do produto que deseja pesquisar: ";

	fseek(stdin,0,SEEK_END);
	fgets(n,30,stdin);
	length = strlen(n);
	n[length-1] = '\0';
	string s = n;

	m->mostraPesquisaPorNomeProduto(s);

}

void menu::menuPesquisarProdutoID(){

    string c;

	int c2;

	do{
		menuCabecalho();
		cout << "\n\n\n\n\n\n\n" << "Digite o codigo do produto que deseja pesquisar: ";
		fseek(stdin,0,SEEK_END);
		cin >> c;
	} while (!is_number(c));

	istringstream ( c ) >> c2;

	m->mostraPesquisaPorIdProduto(c2);

}

void menu::menuListarPorCategoria(){

    string c;
	int c2;

	menuCabecalho();

	cout << "\n\n\n\n\n" << "Digite o codigo da categoria (digite p para pesquisar): ";

	fseek(stdin,0,SEEK_END);
	cin >> c;

	if (c == "p") {
		m->mostraListaDeCategorias();
	}

	if (!is_number(c)) {

		do{
			menuCabecalho();
			cout << "\n\n\n\n\n" << "Digite o codigo da categoria (digite p para pesquisar): ";
			fseek(stdin,0,SEEK_END);
			cin >> c;
			if (c == "p") {
				m->mostraListaDeCategorias();
			}
		} while (!is_number(c));
	}

	istringstream ( c ) >> c2;

	m->mostraCategorizada(c2);
}

void menu::menuListarTodos(){

	m->mostraTotal();
}

void menu::menuProduto(){

	int op = -1;
	string op2;

	while (op != 0){

		menuCabecalho();
		cout << setw(30) << setfill(' ') << "1. Cadastrar Produto" << '\n';
		cout << setw(40) << setfill(' ') << "2. Mudar o Valor de um Produto" << '\n';
		cout << setw(29) << setfill(' ') << "3. Renomear Produto" << '\n';
		cout << setw(28) << setfill(' ') << "4. Excluir Produto" << '\n';
		cout << setw(39) << setfill(' ') << "5. Pesquisar Produto por Nome" << '\n';
		cout << setw(37) << setfill(' ') << "6. Pesquisar Produto por ID" << '\n';
		cout << setw(42) << setfill(' ') << "7. Listar Produtos por Categoria" << '\n';
		cout << setw(37) << setfill(' ') << "8. Listar Todos os Produtos" << '\n';
		cout << setw(19) << setfill(' ') << "0. Voltar" << '\n';
		cout << '\n' << setw(10) << setfill(' ') << "Opcao: ";
		cin >> op2;
		if (!is_number(op2)) {
			cout << "\n" << "Opcao invalida - Tecle enter para continuar";
			fseek(stdin,0,SEEK_END);
			getchar();
		}else{
			istringstream ( op2 ) >> op;
			switch (op){

				case 1: menuCadastrarProduto(); break;
				case 2: menuMudaValorProduto(); break;
				case 3: menuRenomearProduto(); break;
				case 4: menuExcluirProduto(); break;
				case 5: menuPesquisarNome(); break;
				case 6: menuPesquisarProdutoID(); break;
				case 7: menuListarPorCategoria(); break;
				case 8: menuListarTodos(); break;
				case 0: break;

			default: cout << "\n" << "Opcao invalida - Tecle enter para continuar";
					fseek(stdin,0,SEEK_END);
					getchar();
					break;
			}
		}
	}
}

void menu::menuCadastrarCategoria(){

	char c[30];

	int length;

	menuCabecalho();
	cout << "\n\n\n\n\n\n" << setw(20) << setfill(' ') << "Digite o nome da categoria (max 30 letras): ";
	fseek(stdin, 0, SEEK_END);
	fgets(c,30,stdin);
	length = strlen(c);
	c[length-1] = '\0';
	string s = c;

	transform(s.begin(), s.end(), s.begin(), [](char ch) {
		return ch == ' ' ? '_' : ch;
	});

	if (a->incluirCategoria(s)){
		cout << "\n\n" << "Categoria Cadastrada" << "\n\n" << "Pressione enter para continuar";
		fseek(stdin,0,SEEK_END);
		getchar();
		flag1 = true;

	} else{
		cout << "\n\n" << "Ja existe esta categoria" << "\n\n" << "Pressione enter para continuar";
		fseek(stdin,0,SEEK_END);
		getchar();
	}
}

void menu::menuRenomearCategoria(){

	char c[30];
	string n;
	int n2;
	int length;

	do{
		menuCabecalho();
		cout << "\n\n\n\n\n" << "Digite o numero da categoria (digite p para pesquisar): ";
		fseek(stdin, 0, SEEK_END);
		cin >> n;
        if (n == "p") {
			m->mostraListaDeCategorias();
		}
	} while (!is_number(n));

	istringstream ( n ) >> n2;

	cout << "\n\n" << "Digite o novo nome da categoria (max 30 letras): ";

	fseek(stdin,0,SEEK_END);
	fgets(c,30,stdin);
	length = strlen(c);
	c[length-1] = '\0';
	string s = c;

	transform(s.begin(), s.end(), s.begin(), [](char ch) {
		return ch == ' ' ? '_' : ch;
	});

	switch (a->renomearCategoria(n2,s)){

		case 0: cout << "\n" << "Categoria Renomeada" << "\n\n" << "Pressione enter para continuar";
				fseek(stdin,0,SEEK_END);
				getchar();
				flag1 = true;
				break;
		case 1: cout << "\n" << "Nao existe a categoria" << "\n\n" << "Pressione enter para continuar";
				fseek(stdin,0,SEEK_END);
				getchar();
				break;
		case 2: cout << "\n" << "Ja existe uma categoria com esse nome" << "\n\n" << "Pressione enter para continuar";
				fseek(stdin,0,SEEK_END);
				getchar();
				break;
	}
}

void menu::menuExcluirCategoria(){

	string n;
	int n2;

	do{
		menuCabecalho();
		cout << "\n\n\n\n\n" << "Digite o numero da categoria (digite p para pesquisar): ";
		fseek(stdin, 0, SEEK_END);
		cin >> n;
		if (n == "p") {
			m->mostraListaDeCategorias();
		}
	} while (!is_number(n));


	istringstream ( n ) >> n2;

	if (a->excluirCategoria(n2)) {
		cout << "\n\n" << "Categoria Excluida" << "\n\n" << "Pressione enter para continuar";
		fseek(stdin,0,SEEK_END);
		getchar();
		flag1 = true;
	} else{
		cout << "\n\n" << "Categoria nao excluida" << "\n\n" << "Pressione enter para continuar";
		fseek(stdin,0,SEEK_END);
		getchar();
	}
}

void menu::menuListarCategorias(){

	m->mostraListaDeCategorias();
}

void menu::menuCategoria(){

	int op = -1;
	string op2;

	while (op != 0){

		menuCabecalho();
		cout << setw(32) << setfill(' ') << "1. Cadastrar Categoria" << '\n';
		cout << setw(31) << setfill(' ') << "2. Renomear Categoria" << '\n';
		cout << setw(30) << setfill(' ') << "3. Excluir Categoria" << '\n';
		cout << setw(30) << setfill(' ') << "4. Listar Categorias" << '\n';
		cout << setw(19) << setfill(' ') << "0. Voltar" << '\n';
		cout << '\n' << setw(10) << setfill(' ') << "Opcao: ";
		fseek(stdin, 0, SEEK_END);
		cin >> op2;
		if (!is_number(op2)) {
			cout << "\n" << "Opcao invalida - Tecle enter para continuar";
			fseek(stdin,0,SEEK_END);
			getchar();
		}else{
			istringstream ( op2 ) >> op;
			switch (op){

				case 1: menuCadastrarCategoria(); break;
				case 2: menuRenomearCategoria(); break;
				case 3: menuExcluirCategoria(); break;
				case 4: menuListarCategorias(); break;
				case 0: break;

			default: cout << "\n" << "Opcao invalida - Tecle enter para continuar";
					fseek(stdin,0,SEEK_END);
					getchar();
					break;
			}
		}
	}
}


void menu::menuSalvarListaProdutos(){

	string nome;
	char t;

	menuCabecalho();

	cout << "Digite o nome do arquivo sem extencao e sem espacos: ";

	fseek(stdin,0,SEEK_END);
	cin >> nome;

	if (arquivoExiste(nome+".pro")) {
		cout << "\n\n" << "Ja exite esse nome de arquivo, deseja subscrever? (S,N); ";
		fseek(stdin,0,SEEK_END);
		cin >> t;
		if ((t == 's') || (t == 'S')){
			a->salvarMapProdutos(nome+".pro");
			flag1 = false;
			cout << "\n" << "O arquivo foi salvo" << "\n\n" << "Pressione enter para continuar";
			fseek(stdin,0,SEEK_END);
			getchar();
		}else{
			cout << "\n" << "O arquivo nao foi salvo" << "\n\n" << "Pressione enter para continuar";
			fseek(stdin,0,SEEK_END);
			getchar();
		}
	} else {
		a->salvarMapProdutos(nome+".pro");
		flag1 = false;
		cout << "\n" << "O arquivo foi salvo" << "\n\n" << "Pressione enter para continuar";
		fseek(stdin,0,SEEK_END);
		getchar();
    }
}

void menu::menuSalvarListaClientes(){

	string nome;
	char t;

	menuCabecalho();

	cout << "Digite o nome do arquivo sem extencao e sem espacos: ";

	fseek(stdin,0,SEEK_END);
	cin >> nome;

	if (arquivoExiste(nome+".cli")) {
		cout << "\n\n" << "Ja existe esse nome de arquivo, deseja subscrever? (S,N): ";
		fseek(stdin,0,SEEK_END);
		cin >> t;
		if ((t == 's') || (t == 'S')){
			a->salvarClientes(nome+".cli");
			flag2 = false;
			cout << "\n" << "O arquivo foi salvo" << "\n\n" << "Pressione enter para continuar";
			fseek(stdin,0,SEEK_END);
			getchar();
		}else{
			cout << "\n" << "O arquivo nao foi salvo" << "\n\n" << "Pressione enter para continuar";
			fseek(stdin,0,SEEK_END);
			getchar();
		}
	} else {
		a->salvarClientes(nome+".cli");
		cout << "\n" << "O arquivo foi salvo" << "\n\n" << "Pressione enter para continuar";
		flag2 = false;
		fseek(stdin,0,SEEK_END);
		getchar();
	}
}

void menu::menuCarregarListaProdutos(){

	string nome;
	char t;

	menuCabecalho();

	if (flag1) {

		cout << "ATENCAO - Todos os dados nao salvos serao perdidos, deseja continuar? (S,N): ";
		fseek(stdin,0,SEEK_END);
		cin >> t;
		if ((t == 's') || (t == 'S')){

			cout << "\n" << "Digite o nome do arquivo sem extencao e sem espacos: ";

			fseek(stdin,0,SEEK_END);
			cin >> nome;

			if (!arquivoExiste(nome+".pro")) {
				cout << "\n\n" << "Nao existe este arquivo " << "\n\n" << "Pressione enter para continuar";
				fseek(stdin,0,SEEK_END);
				getchar();
			} else {
				a->clearAll();
				a->makeCategoria(nome+".pro");
				a->makeProduto(nome+".pro");
				a->convertCodigoNome();
				flag1 = false;
				cout << "\n" << "O arquivo foi carregado" << "\n\n" << "Pressione enter para continuar";
				fseek(stdin,0,SEEK_END);
				getchar();
			}
		}
	}else{
		cout << "\n" << "Digite o nome do arquivo sem extencao e sem espacos: ";

		fseek(stdin,0,SEEK_END);
		cin >> nome;

		if (!arquivoExiste(nome+".pro")) {
			cout << "\n\n" << "Nao existe este arquivo " << "\n\n" << "Pressione enter para continuar";
			fseek(stdin,0,SEEK_END);
			getchar();
		} else {
			a->clearAll();
			a->makeCategoria(nome+".pro");
			a->makeProduto(nome+".pro");
			a->convertCodigoNome();
			flag1 = false;
			cout << "\n" << "O arquivo foi carregado" << "\n\n" << "Pressione enter para continuar";
			fseek(stdin,0,SEEK_END);
			getchar();
		}
	}
}

void menu::menuCarregarListaClientes(){

	string nome;
	char t;

	menuCabecalho();

	if (flag2) {

		cout << "ATENCAO - Todos os dados nao salvos serao perdidos, deseja continuar? (S,N): ";
		fseek(stdin,0,SEEK_END);
		cin >> t;
		if ((t == 's') || (t == 'S')){

			cout << "\n" << "Digite o nome do arquivo sem extencao e sem espacos: ";

			fseek(stdin,0,SEEK_END);
			cin >> nome;

			if (!arquivoExiste(nome+".cli")) {
				cout << "\n\n" << "Nao existe este arquivo " << "\n\n" << "Pressione enter para continuar";
				fseek(stdin,0,SEEK_END);
				getchar();
			} else {
				a->clearClientes();
				a->makeListaDeClientes(nome+".cli");
				flag2 = false;
				cout << "\n" << "O arquivo foi carregado" << "\n\n" << "Pressione enter para continuar";
				fseek(stdin,0,SEEK_END);
				getchar();
			}
		}
	}else{
		cout << "\n" << "Digite o nome do arquivo sem extencao e sem espacos: ";

		fseek(stdin,0,SEEK_END);
		cin >> nome;

		if (!arquivoExiste(nome+".cli")) {
			cout << "\n\n" << "Nao existe este arquivo " << "\n\n" << "Pressione enter para continuar";
			fseek(stdin,0,SEEK_END);
			getchar();
		} else {
			a->clearClientes();
			a->makeListaDeClientes(nome+".cli");
			flag2 = false;
			cout << "\n" << "O arquivo foi carregado" << "\n\n" << "Pressione enter para continuar";
			fseek(stdin,0,SEEK_END);
			getchar();
		}
	}
}

void menu::menuCarregarListaVendas(){

		string nome;

		menuCabecalho();

		cout << "\n" << "Digite o nome do arquivo sem extencao e sem espacos: ";

		fseek(stdin,0,SEEK_END);
		cin >> nome;

		if (!arquivoExiste(nome+".ven")) {
			cout << "\n\n" << "Nao existe este arquivo " << "\n\n" << "Pressione enter para continuar";
			fseek(stdin,0,SEEK_END);
			getchar();
		} else {
			v->carregarArquivoVendas(nome+".ven");
			cout << "\n" << "O arquivo foi carregado" << "\n\n" << "Pressione enter para continuar";
			fseek(stdin,0,SEEK_END);
			getchar();
		}
}

void menu::menuArquivos(){

	int op = -1;
	string op2;

	while (op != 0){
		menuCabecalho();
		cout << setw(48) << setfill(' ') << "1. Salvar arquivo de lista de produtos" << '\n';
		cout << setw(48) << setfill(' ') << "2. Salvar arquivo de lista de clientes" << '\n';
		cout << setw(53) << setfill(' ') << "3. Carregar um arquivo de lista de produtos" << '\n';
		cout << setw(53) << setfill(' ') << "4. Carregar um arquivo de lista de clientes" << '\n';
		cout << setw(51) << setfill(' ') << "5. Carregar um arquivo de lista de vendas" << '\n';
		cout << setw(19) << setfill(' ') << "0. Voltar" << '\n';
		cout << '\n' << setw(10) << setfill(' ') << "Opcao: ";
		fseek(stdin, 0, SEEK_END);
		cin >> op2;
		if (!is_number(op2)) {
			cout << "\n" << "Opcao invalida - Tecle enter para continuar";
			fseek(stdin,0,SEEK_END);
			getchar();
		}else{
			istringstream ( op2 ) >> op;
			switch (op){

				case 1: menuSalvarListaProdutos(); break;
				case 2: menuSalvarListaClientes(); break;
				case 3: menuCarregarListaProdutos(); break;
				case 4: menuCarregarListaClientes(); break;
				case 5: menuCarregarListaVendas(); break;
				case 0: break;

			default: cout << "\n" << "Opcao invalida - Tecle enter para continuar";
					fseek(stdin,0,SEEK_END);
					getchar();
					break;
			}
		}
	}
}

void menu::menuIniciarVenda(){

	v->iniciarVenda();
}

void menu::menuHelp(){

	menuCabecalho();
	cout << "   Help:";
	cout << "\n\n" << "   -> O programa eh intuitivo, navegue pelos menus para registrar os produtos e os clientes.";
	cout << "\n" << "   -> Os clientes possuem apenas um nome e uma ID viculados a ele.";
	cout << "\n" << "   -> Os produtos possuem uma ID unica e sao vinculados a uma categoria para fins estatisticos.";
	cout << "\n" << "   -> Por questoes de compatibilidade com o compilador, nao use cedilha ou acentos para os nomes.";
	cout << "\n" << "   -> Inicie uma venda informando o ID do cliente ou 0 para nao vincular a venda a nenhum cliente.";
	cout << "\n" << "   -> Va informando o codigo do produto, que poderia ser via leitor de codigo de barras.";
	cout << "\n" << "   -> Informe a quantidade, ou se o produto eh por peso, informe seu peso em kilos (Ex. 0,300 para 300 gramas).";
	cout << "\n" << "   -> Use virgula para as casas decimais.";
	cout << "\n" << "   -> Os arquivos de lista de produtos, lista de clientes e fita de vendas estao na mesma pasta do programa.";
	cout << "\n" << "   -> Os arquivos tem um nome padrao: produtos.pro; clientes.cli e vendas.ven;";
	cout << "\n" << "   -> Salve as alteracoes com o nome de arquivo que quiser e depois carregue este arquivo para usa-lo.";
	cout << "\n" << "   -> Para mais informacoes sobre o programa va ate o menu ToDo.";
	cout << "\n" << "   -> ATENCAO - Nao altere a estrutura dos arquivos de dados, se nao da crash.";

	cout << "\n\n" << "Pressione enter para continuar";
	fseek(stdin,0,SEEK_END);
	getchar();
}

void menu::menuToDo(){

	menuCabecalho();
	cout << "   To Do:";
	cout << "\n\n" << "   -> Acrescentar validacoes de arquivos de dados;";
	cout << "\n" << "   -> Acrescentar validacoes de entradas de menu;";
	cout << "\n" << "   -> Melhorar interacoes do menu:";
	cout << "\n" << "      p.ex. usando teclas de funcoes dentre outras coisas;";
	cout << "\n" << "      nas telas de alteracoes, mostrar os dados atuais para o usuario saber o que ele esta alterando;";
	cout << "\n" << "   -> Salvar as alteracoes automaticamente no arquivo com os dados";
	cout << "\n" << "      no caso de dar crash e o usuario perder as alteracoes;";
	cout << "\n" << "   -> Usar um metodo de entrada/saida que aceite o portugues (com acentos):";
	cout << "\n" << "      no C++ Builder;";
	cout << "\n" << "   -> Pesquisar o ID do cliente e do produto antes de perguntar novos dados";
	cout << "\n" << "      para o usuario nao perder tempo;";
	cout << "\n" << "   -> Na pesquisa por nome, fazer o algoritmo nao diferenciar maiuscula de minuscula";
	cout << "\n" << "   -> Melhorar o tela de mostrar com mecanismos de voltar a tela anterior por exemplo;";
	cout << "\n" << "   -> Melhorar mecanismo de venda;";
	cout << "\n\n\n\n" << "Pressione enter para continuar";
	fseek(stdin,0,SEEK_END);
	getchar();
    menuCabecalho();
	cout << "   To Do:";
	cout << "\n\n" << "   -> Acrescentar data e hora da venda e possivelmente para todos os registros:";
	cout << "\n" << "      ou seja, fazer log de operacoes;";
	cout << "\n" << "   -> Acrescentar formularios de dados para produtos e clientes:";
	cout << "\n" << "      como fornecedores, enderecos, estoque, etc etc...";
	cout << "\n" << "      teria que alterar a estrutura dos maps e vetores para isso;";
	cout << "\n" << "   -> Incluir a possibilidade de se ter varios operadores do sistema:";
	cout << "\n" << "      por senha possivelmente;";

	cout << "\n\n\n\n" << "Pressione enter para continuar";
	fseek(stdin,0,SEEK_END);
	getchar();
}

void menu::menuPesquisarCodigoVenda(){

	v->pesquisarCodigoDeVenda();
}

void menu::menuPesquisarVendaPorCodigo(){

	string n;

    do{
		menuCabecalho();
		cout << "\n\n\n\n\n" << "Digite o numero da operacao: ";
		fseek(stdin, 0, SEEK_END);
		cin >> n;
	} while (!is_number(n));

	v->pesquisarVendaPorCodigo(n);
}

void menu::menuPesquisarTotalCliente(){

    string n;

    do{
		menuCabecalho();
		cout << "\n\n\n\n\n" << "Digite o numero do cliente: ";
		fseek(stdin, 0, SEEK_END);
		cin >> n;
	} while (!is_number(n));

	v->pesquisarTotalPorCliente(n);
}

void menu::menuPesquisarTotalCategoria(){

	string n;

	do{
		menuCabecalho();
		cout << "\n\n\n\n\n" << "Digite o numero da categoria: ";
		fseek(stdin, 0, SEEK_END);
		cin >> n;
	} while (!is_number(n));

	v->pesquisarTotalPorCategoria(n);
}

void menu::menuPesquisarTotalProduto(){

    string n;

	do{
		menuCabecalho();
		cout << "\n\n\n\n\n" << "Digite o numero do produto: ";
		fseek(stdin, 0, SEEK_END);
		cin >> n;
	} while (!is_number(n));

	v->pesquisarTotalPorProduto(n);
}

void menu::menuVendas(){

	int op = -1;
	string op2;

	while (op != 0){
		menuCabecalho();
		cout << setw(41) << setfill(' ') << "1. Pesquisar um codigo de venda" << '\n';
		cout << setw(43) << setfill(' ') << "2. Pesquisar uma venda por codigo" << '\n';
		cout << setw(50) << setfill(' ') << "3. Pesquisar total de vendas por cliente" << '\n';
		cout << setw(52) << setfill(' ') << "4. Pesquisar total de vendas por categoria" << '\n';
		cout << setw(50) << setfill(' ') << "5. Pesquisar total de vendas por produto" << '\n';
		cout << setw(19) << setfill(' ') << "0. Voltar" << '\n';
		cout << '\n' << setw(10) << setfill(' ') << "Opcao: ";
		fseek(stdin, 0, SEEK_END);
		cin >> op2;
		if (!is_number(op2)) {
			cout << "\n" << "Opcao invalida - Tecle enter para continuar";
			fseek(stdin,0,SEEK_END);
			getchar();
		}else{
			istringstream ( op2 ) >> op;
			switch (op){

				case 1: menuPesquisarCodigoVenda(); break;
				case 2: menuPesquisarVendaPorCodigo(); break;
				case 3: menuPesquisarTotalCliente(); break;
				case 4: menuPesquisarTotalCategoria(); break;
				case 5: menuPesquisarTotalProduto(); break;
				case 0: break;

			default: cout << "\n" << "Opcao invalida - Tecle enter para continuar";
					fseek(stdin,0,SEEK_END);
					getchar();
					break;
			}
		}
	}
}


menu::menu(){

	flag1 = false;
	flag2 = false;

	maper a1("produtos.pro");
	mostrar m1(&a1);

	a = &a1;
	m = &m1;

	venda vl("vendas.ven",m,a);

	v = &vl;

	a->makeListaDeClientes("clientes.cli");

	int op = -1;
	string op2;
	string sair = "s";

	do{
		menuCabecalho();
		cout << setw(30) << setfill(' ') << "1. Iniciar uma venda" << '\n';
		cout << setw(20) << setfill(' ') << "2. Cliente" << '\n';
		cout << setw(20) << setfill(' ') << "3. Produto" << '\n';
		cout << setw(22) << setfill(' ') << "4. Categoria" << '\n';
		cout << setw(19) << setfill(' ') << "5. Vendas" << '\n';
		cout << setw(21) << setfill(' ') << "6. Arquivos" << '\n';
		cout << setw(17) << setfill(' ') << "7. Help" << '\n';
		cout << setw(17) << setfill(' ') << "8. ToDo" << '\n';
		cout << setw(17) << setfill(' ') << "0. Sair" << '\n';
		cout << '\n' << setw(10) << setfill(' ') << "Opcao: ";
		fseek(stdin, 0, SEEK_END);
		cin >> op2;
		if (!is_number(op2)) {
			cout << "\n" << "Opcao invalida - Tecle enter para continuar";
			fseek(stdin,0,SEEK_END);
			getchar();
		}else{
			istringstream ( op2 ) >> op;

			switch (op){

				case 1: menuIniciarVenda(); break;
				case 2: menuCliente(); break;
				case 3: menuProduto(); break;
				case 4: menuCategoria(); break;
				case 5: menuVendas(); break;
				case 6: menuArquivos(); break;
				case 7: menuHelp(); break;
				case 8: menuToDo(); break;
				case 0: break;

				default: cout << "\n" << "Opcao invalida - Tecle enter para continuar";
					fseek(stdin,0,SEEK_END);
					getchar();
					break;
			}
		}
		if ((op == 0) && ((flag1) || (flag2))) {
			cout << "\n\n" << "   Houve alteracao na base de dados, deseja mesmo sair antes de salvar os arquivos? (S,N): ";
			fseek(stdin, 0, SEEK_END);
			cin >> sair;
		}
	} while ((op != 0) || ((sair != "s") && (sair != "S")));
}
