//---------------------------------------------------------------------------

#pragma hdrstop

#include "venda.h"
//---------------------------------------------------------------------------

//-----------------------------------------------------------------------
// A funcao is_number eh usada para verificar se uma string eh um numero
//-----------------------------------------------------------------------
bool venda::is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

//-----------------------------------------------------------------------
// A funcao isFloat eh usada para verificar se uma string eh um float
//-----------------------------------------------------------------------
bool venda::isFloat( string myString ) {
	std::istringstream iss(myString);
	float f;
	iss >> noskipws >> f; // noskipws considers leading whitespace invalid
	// Check the entire string was consumed and if either failbit or badbit is set
	return iss.eof() && !iss.fail();
}

void venda::menuCabecalho(){
	system("CLS");
	cout << setw(85) << setfill('-');
	cout << "\n\n";
	cout << setw(50) << setfill(' ') << "Vendas Varejo ver. 0.1" << "\n\n";
	cout << setw(85) << setfill('-') << "\n\n";
}

void venda::menuCabecalho2(){

	system("CLS");
	cout << setw(85) << setfill('-');
	cout << "\n\n";
	cout << setw(50) << setfill(' ') << "Vendas Varejo ver. 0.1" << "\n\n";
	cout << setw(85) << setfill('-') << "\n";
	cout << "   Digite (f) a qualquer momento para finalizar" << "\n";
	cout << setw(85) << setfill('-') << "\n";

}

venda::venda(string n, mostrar *_m, maper *_ma){

	m = _m;
	ma = _ma;
	nomeArquivo = n;
}

void venda::carregarArquivoVendas(string n){

	nomeArquivo = n;
}

void venda::pesquisarCodigoDeVenda(){

	string fim = "<fim>";
	string inicio = "<inicio>";

	string s;

	string temp;

	string operacao;
	string cliente;
	string total;

	int i = 0;

	ifstream myfile(nomeArquivo);

	myfile.clear();
	myfile.seekg(0, ios::beg);

	menuCabecalho();
	cout << setw(32) << setfill(' ') << "Operacao" << setw(19) << setfill(' ')
		<< "Cliente" << setw(19) << setfill(' ') << "Total" << "\n";

	getline(myfile,s);

	while (!myfile.eof()){

		getline(myfile,s);

		while (s.find(fim) == std::string::npos){

			if (s.find(inicio) != std::string::npos){

				size_t pos1 = s.find("~");
				size_t pos2 = s.find("#");
				size_t pos3 = pos2-pos1-1;

				cliente = s.substr (pos1+1,pos3);
				operacao = s.substr (pos2+1);

				getline(myfile,s);

				cout << setw(32) << setfill(' ') << operacao << setw(19) << setfill(' ') <<  cliente;
			}

			if (s.find("$") != std::string::npos) {

				getline(myfile,s);
			}

			if (s.find("?") != std::string::npos){

				istringstream iss(s);
				getline(iss,temp,' ');
				getline(iss,total,' ');

				getline(myfile,s);

				cout << setw(19) << setfill(' ') << total << "\n";

				i++;
			}

			if (s.find("%") != std::string::npos) {

				getline(myfile,s);
			}

			if (s.find("@") != std::string::npos) {

				getline(myfile,s);
			}

			if (i == 16) {
				cout << "\n\n" << "Pressione enter para continuar";
				fseek(stdin,0,SEEK_END);
				getchar();
				system("CLS");
				i = 0;

				menuCabecalho();
				cout << setw(32) << setfill(' ') << "Operacao" << setw(19) << setfill(' ')
					<< "Cliente" << setw(19) << setfill(' ') << "Total" << "\n";
			}
		}
	}

	cout << "\n\n" << "Pressione enter para continuar";
	fseek(stdin,0,SEEK_END);
	getchar();
}

void venda::pesquisarVendaPorCodigo(string c){

	string fim = "<fim>";
	string inicio = "<inicio>";

	string s;

	string temp;

	string operacao;
	string cliente;
	string total;
	string categoria;
	string produto;
	string nomeProduto;
	string tipo;
	string quantidade;
	string valor;
	string dinheiro;
	string troco;

	int i = 0;

	bool flag = false;
	bool flag2 = true;

	ifstream myfile(nomeArquivo);

	myfile.clear();
	myfile.seekg(0, ios::beg);

	menuCabecalho();

	getline(myfile,s);

	while (!myfile.eof()){

		getline(myfile,s);

		while ((s.find(fim) == std::string::npos) && (flag2)){

			if ((s.find(inicio) != std::string::npos) && (s.find("#"+c) != std::string::npos)){

				size_t pos1 = s.find("~");
				size_t pos2 = s.find("#");
				size_t pos3 = pos2-pos1-1;

				cliente = s.substr (pos1+1,pos3);
				operacao = s.substr (pos2+1);

				cout << setw(32) << setfill(' ') << "Operacao: " << operacao << "\n"
					<< setw(32) << setfill(' ') <<  "Cliente: " << cliente << "\n\n";

				cout << setw(10) << setfill(' ') << "Categoria" << setw(10) << setfill(' ')
					<< "Produto" << setw(30) << setfill(' ') << "Nome"
					<< setw(5) << setfill(' ') << "Tipo" << setw(12) << setfill(' ')
					<< "Quantidade" << setw(8) << setfill(' ') << "Valor" << "\n";

				getline(myfile,s);

				flag = true;
			}

			if ((s.find("$") != std::string::npos) && (flag)){

                istringstream iss(s);
				getline(iss,temp,' ');
				getline(iss,categoria,' ');
				getline(iss,produto,' ');
				getline(iss,nomeProduto,' ');
				getline(iss,tipo,' ');
				getline(iss,quantidade,' ');
				getline(iss,valor,' ');

				cout << setw(10) << setfill(' ') << categoria << setw(10) << setfill(' ')
					<< produto << setw(30) << setfill(' ') << nomeProduto
					<< setw(5) << setfill(' ') << tipo << setw(12) << setfill(' ')
					<< quantidade << setw(8) << setfill(' ') << valor << "\n";

				getline(myfile,s);

				i++;

			}

			if ((s.find("?") != std::string::npos) && (flag)){

				istringstream iss(s);
				getline(iss,temp,' ');
				getline(iss,total,' ');

				getline(myfile,s);

				cout << setw(76) << setfill ('-') << '\n';

				cout << setw(70) << setfill(' ') << "Total: " << total << "\n";
			}

			if ((s.find("%") != std::string::npos) && (flag)){

				istringstream iss(s);
				getline(iss,temp,' ');
				getline(iss,dinheiro,' ');

				getline(myfile,s);

				cout << setw(70) << setfill(' ') << "Recebido: " << dinheiro << "\n";
			}

			if ((s.find("@") != std::string::npos) && (flag)){

				istringstream iss(s);
				getline(iss,temp,' ');
				getline(iss,troco,' ');

				getline(myfile,s);

				cout << setw(70) << setfill(' ') << "Troco: " << troco << "\n";

				flag = false;
				flag2 = false;
			}

			if (i == 10) {
				cout << "\n\n" << "Pressione enter para continuar";
				fseek(stdin,0,SEEK_END);
				getchar();
				system("CLS");
				i = 0;

				menuCabecalho();
                cout << setw(10) << setfill(' ') << "Categoria" << setw(10) << setfill(' ')
					<< "Produto" << setw(30) << setfill(' ') << "Nome"
					<< setw(5) << setfill(' ') << "Tipo" << setw(12) << setfill(' ')
					<< "Quantidade" << setw(8) << setfill(' ') << "Valor" << "\n";
			}

			if (!flag) {
				getline(myfile,s);
			}

		}

	}
	cout << "\n\n" << "Pressione enter para continuar";
	fseek(stdin,0,SEEK_END);
	getchar();
}

void venda::pesquisarTotalPorCliente(string c){

    string fim = "<fim>";
	string inicio = "<inicio>";

	string s;

	string temp;

	bool flag = false;
	bool flag2 = false;

	float f;

	float t = 0;

	string operacao;
	string cliente;
	string total;

    int i = 0;

	ifstream myfile(nomeArquivo);

	myfile.clear();
	myfile.seekg(0, ios::beg);

	menuCabecalho();
	cout << setw(32) << setfill(' ') << "Operacao" << setw(19) << setfill(' ')
		<< "Cliente" << setw(19) << setfill(' ') << "Total" << "\n";

	getline(myfile,s);

	while (!myfile.eof()){

		getline(myfile,s);

		while (s.find(fim) == std::string::npos){

			if ((s.find(inicio) != std::string::npos) && (s.find("~"+c) != std::string::npos)){

				size_t pos1 = s.find("~");
				size_t pos2 = s.find("#");
				size_t pos3 = pos2-pos1-1;

				cliente = s.substr (pos1+1,pos3);
				operacao = s.substr (pos2+1);

				getline(myfile,s);

				cout << setw(32) << setfill(' ') << operacao << setw(19) << setfill(' ') <<  cliente;

				flag = true;
				flag2 = true;
			}

			if ((s.find("$") != std::string::npos) && (flag)) {

				getline(myfile,s);
			}

			if ((s.find("?") != std::string::npos) && (flag)){

				istringstream iss(s);
				getline(iss,temp,' ');
				getline(iss,total,' ');

				getline(myfile,s);

				istringstream ( total ) >> f;

				t = t + f;

				cout << setw(19) << setfill(' ') << total << "\n";

				i++;

				flag2 = false;
			}

			if ((s.find("%") != std::string::npos) && (flag)) {

				getline(myfile,s);
			}

			if ((s.find("@") != std::string::npos) && (flag)) {

				getline(myfile,s);
				flag = false;
			}

			if (i == 16) {
				cout << "\n\n" << "Pressione enter para continuar";
				fseek(stdin,0,SEEK_END);
				getchar();
				system("CLS");
				i = 0;

				menuCabecalho();
				cout << setw(32) << setfill(' ') << "Operacao" << setw(19) << setfill(' ')
					<< "Cliente" << setw(19) << setfill(' ') << "Total" << "\n";
			}

           if (!flag2){
				getline(myfile,s);
				flag = false;
			}
		}
	}

	cout << "\n" << setw(84) << setfill('-');
	cout << "\n" << setw(70) << setfill(' ') << "Total Cliente: " << setprecision(2) << fixed << t;

	cout << "\n\n" << "Pressione enter para continuar";
	fseek(stdin,0,SEEK_END);
	getchar();
}

void venda::pesquisarTotalPorCategoria(string c){

	string fim = "<fim>";
	string inicio = "<inicio>";

	string s;

	string temp;

	bool flag = false;

	float f;

	float t = 0;

	string valor;
	string categoria;

	int i = 0;

	ifstream myfile(nomeArquivo);

	myfile.clear();
	myfile.seekg(0, ios::beg);

	menuCabecalho();
	cout << setw(32) << setfill(' ') << "Categoria" << setw(19) << setfill(' ') << "Total";

	getline(myfile,s);

	while (!myfile.eof()){

		getline(myfile,s);

		while (s.find(fim) == std::string::npos){

			if ((s.find(inicio) != std::string::npos)){

				getline(myfile,s);

				flag = true;
			}

			if ((s.find("$") != std::string::npos) && (flag)) {

				istringstream iss(s);
				getline(iss,temp,' ');
				getline(iss,categoria,' ');
				if (categoria == c) {

					getline(iss,temp,' ');
					getline(iss,temp,' ');
					getline(iss,temp,' ');
					getline(iss,temp,' ');
					getline(iss,valor,' ');

					istringstream ( valor ) >> f;

					t = t + f;
				}
				getline(myfile,s);
			}

			if ((s.find("?") != std::string::npos) && (flag)){

				getline(myfile,s);
			}

			if ((s.find("%") != std::string::npos) && (flag)) {

				getline(myfile,s);
			}

			if ((s.find("@") != std::string::npos) && (flag)) {

				getline(myfile,s);
				flag = false;
			}

			if (!flag) {
				getline(myfile,s);
			}
		}
	}

	cout << "\n" << setw(84) << setfill('-');
	cout << "\n" << setw(32) << setfill(' ') << c << setw(19) << setfill(' ') << setprecision(2) << fixed << t;

	cout << "\n\n" << "Pressione enter para continuar";
	fseek(stdin,0,SEEK_END);
	getchar();
}

void venda::pesquisarTotalPorProduto(string c){

	string fim = "<fim>";
	string inicio = "<inicio>";

	string s;

	string temp;

	bool flag = false;

	float f;

	float t = 0;

	string valor;
	string produto;

	int i = 0;

	ifstream myfile(nomeArquivo);

	myfile.clear();
	myfile.seekg(0, ios::beg);

	menuCabecalho();
	cout << setw(32) << setfill(' ') << "Produto" << setw(19) << setfill(' ') << "Total";

	getline(myfile,s);

	while (!myfile.eof()){

		getline(myfile,s);

		while (s.find(fim) == std::string::npos){

			if ((s.find(inicio) != std::string::npos)){

				getline(myfile,s);

				flag = true;
			}

			if ((s.find("$") != std::string::npos) && (flag)) {

				istringstream iss(s);
				getline(iss,temp,' ');
				getline(iss,temp,' ');
				getline(iss,produto,' ');
				if (produto == c) {

					getline(iss,temp,' ');
					getline(iss,temp,' ');
					getline(iss,temp,' ');
					getline(iss,valor,' ');

					istringstream ( valor ) >> f;

					t = t + f;
				}
				getline(myfile,s);
			}

			if ((s.find("?") != std::string::npos) && (flag)){

				getline(myfile,s);
			}

			if ((s.find("%") != std::string::npos) && (flag)) {

				getline(myfile,s);
			}

			if ((s.find("@") != std::string::npos) && (flag)) {

				getline(myfile,s);
				flag = false;
			}

			if (!flag) {
				getline(myfile,s);
			}
		}
	}

	cout << "\n" << setw(84) << setfill('-');
	cout << "\n" << setw(32) << setfill(' ') << c << setw(19) << setfill(' ') << setprecision(2) << fixed << t;

	cout << "\n\n" << "Pressione enter para continuar";
	fseek(stdin,0,SEEK_END);
	getchar();
}

void venda::carregarListaDeVendas(int j, string total){

	int i; 
	
	menuCabecalho2();

	for (i = 7; i >= 0 ; i--) {
		if (listaDeVendas[j-i] != "\0") {
			cout << "\n" << "      " << listaDeVendas[j-i];
		}
	
	}
	cout << "\n";
	cout << "\n" << setw(50) << setfill('-');
	if (total != "0") {
		cout << "\n" << setw(32) << setfill(' ') << "Total: " << total << "\n";		
	}
	

}

void venda::iniciarVenda(){

	string fim = "<fim>";
	string inicio = "<inicio>";
	string input;
	int input_to_int;
	int j = 7;
	int k;
	map<pair<int,int>, vector<string>> produtos;
	vector<pair<string, int>> clientes;
	produtos = ma->getListaPorCodigo();
	clientes = ma->getListaDeClientes();
	int n_operacao;
	int c,p;
	float v;
	float totalP;
	string t;
	string codigoCliente = "0";
	string codigoProduto;
	string codigoCategoria;
	string tipo;
	string quantidade;
	string valor;
	string nomeProduto;
	string total;
	string recebido;
	string troco;
	string s;
	string s2 = "0";
	string s3;
	int length;
	int q;
	float q2;
	float contagem = 0;
	float quant;
	float rec;
	float tr;
	bool flag1 = false;
	bool flag2 = false;
	bool flag3 = false;
	bool flag4 = false;
	bool flag5 = false;
	bool flag6 = false;
	bool flag7 = false;
	

	for (k=0; k<=1999; k++) {
		listaDeVendas[k] = "\0";
	}

	ifstream myfile(nomeArquivo);
	myfile.clear();
	myfile.seekg(0, ios::beg);

	getline(myfile,s3);

	length = s3.length();

	length = length - 12;

	size_t pos1 = s3.find("n_operacao->");
	
	string op = s3.substr (12,length);
	istringstream ( op ) >> n_operacao;

	n_operacao++;

	string s4;

	s4 = to_string(n_operacao);

	string s5;
	
	s5 = "n_operacao->"+s4;

	ofstream out1 ("vendas.tmp");
	out1 << s5;
	while(getline(myfile,s3)){

		out1 << "\n" << s3;
	}

	out1 << "\n" << inicio;
	
   //	out1.open("vendas.tmp", std::ios::app);

	while ((input != "f") && (input != "F")){
		while (!flag2){
			carregarListaDeVendas(j,s2);
			cout << "\n" << "Codigo do cliente (p para pesquisar ou 0 para nao registrar cliente): ";
			fseek(stdin,0,SEEK_END);
			cin >> input;
			if ((input == "f") || (input == "F")){
				flag2 = true;
				flag1 = false;
				out1 << " ~0" << " #" << s4;
			} else{
				if (input == "0") {
					flag1 = true;
					flag2 = true;
					out1 << " ~" << input << " #" << s4;
				}else{
					if ((input == "p") || (input == "P")) {
						m->mostraListaDeClientes();
					} else{
						if (!is_number(input)) {
							cout << "Codigo invalido - Pressione Enter";
							fseek(stdin,0,SEEK_END);
							getchar();
						} else {
							istringstream ( input ) >> input_to_int;
						
							for (auto const& x : clientes) {
								if (x.second == input_to_int) {
									codigoCliente = to_string(input_to_int);
									out1 << " ~" << codigoCliente << " #" << s4;
									flag1 = true; 
									flag2 = true; 
									flag7 = true; 
								}
							
								if ((&x == &clientes.back()) && (!flag1)){
									cout << "Nao existe um cliente com este codigo - Pressione Enter";
									fseek(stdin,0,SEEK_END);
									getchar();
								}
							}
						}
					}
				}
			}
		}

		if (flag1) {
			carregarListaDeVendas(j,s2);
			if (flag6) {
				cout << "\n" << "Codigo do produto para estornar (p para pesquisar): ";
				fseek(stdin,0,SEEK_END);
				cin >> input;
				flag3 = false;   
			}
			if (!flag6) {
                cout << "\n" << "Codigo do produto (p para pesquisar, e para estornar): ";
				fseek(stdin,0,SEEK_END);
				cin >> input;
				flag3 = false;
			}
			while (!flag3){
				if ((input == "f") || (input == "F")){
					flag3 = true;
					flag1 = false;
				} else{
					if ((input == "p") || (input == "P")) {
						m->mostraTotal();
						break;
					} else {
						if ((input == "e") || (input == "E")){
							flag6 = true;
							break;
						} else {
							if (!is_number(input)) {
								cout << "Codigo invalido - Pressione Enter";
								fseek(stdin,0,SEEK_END);                          
								getchar();
								break;
							} else {

								flag5 = false;
						
								istringstream ( input ) >> input_to_int;

								for(map<pair<int,int>, vector<string>>::iterator it=produtos.begin(); it!=produtos.end(); ++it){

									bool last_iteration = it == (--produtos.end());

									vector <string> inVect = (*it).second;

									if (input_to_int == (*it).first.second) {

										c = (*it).first.first;
										codigoCategoria = to_string(c);
										p = (*it).first.second;
										codigoProduto = to_string(p);
									
										nomeProduto = inVect[2];
										tipo = inVect[3];
											
										if (tipo == "un") {
											carregarListaDeVendas(j,s2);
											cout << "\n" << "Informe a quantidade: ";
											fseek(stdin, 0, SEEK_END);
											cin >> quantidade;
											istringstream(quantidade) >> q;

											if ((quantidade == "f") || (quantidade == "F")) {
												flag4 = true;
												flag1 = true;
												flag3 = true;
												input = quantidade;
												if (flag6) {
													flag6 = false;
												}
												break;
											}
									
											while ((!is_number(quantidade) || (q == 0))&& (!flag4)){
												cout << "Quantidade invalida - Pressione Enter";
												fseek(stdin,0,SEEK_END);
												getchar();
												carregarListaDeVendas(j,s2);
												cout << "\n" << "Informe a quantidade: ";
												fseek(stdin, 0, SEEK_END);
												cin >> quantidade;
												istringstream(quantidade) >> q;
												if ((quantidade == "f") || (quantidade == "F")) {
													flag4 = true;
													flag1 = true;
													flag3 = true;
													input = quantidade;
													if (flag6) {
														flag6 = false;
													}
													break;
												}											
											}	
										}

										if (tipo == "kg") {
											carregarListaDeVendas(j,s2);
											cout << "\n" << "Informe o peso em kilos: ";
											fseek(stdin, 0, SEEK_END);
											cin >> quantidade;
											if (is_number(quantidade)) {
												quantidade = quantidade + ",000";
												q2 = stof(quantidade);
											}
											else {
												if (isFloat(quantidade)) {
													q2 = stof(quantidade);
												}
											}
											if ((quantidade == "f") || (quantidade == "F")) {
												flag4 = true;
												flag1 = false;
												flag3 = true;
												if (flag6) {
													flag6 = false;
												}
												input = quantidade;
												break;
											}

											while ((!isFloat(quantidade) || (q2 == 0)) && (!flag4)) {
												cout << "Peso invalido - Pressione Enter";
												fseek(stdin,0,SEEK_END);
												getchar();
												carregarListaDeVendas(j,s2);
												cout << "\n" << "Informe o peso em kilos: ";
												fseek(stdin, 0, SEEK_END);
												cin >> quantidade;
												if (is_number(quantidade)) {
													quantidade = quantidade + ",000";
													q2 = stof(quantidade);
												}
												else {
													if (isFloat(quantidade)) {
														q2 = stof(quantidade);
													}
												}
												if ((quantidade == "f") || (quantidade == "F")) {
													flag4 = true;
													flag1 = false;
													flag3 = true;
													if (flag6) {
														flag6 = false;
													}
													input = quantidade;
													break;
												}
											}
										}

										if (flag4) {
											break;
										}

										flag4 = false;
										v = stof(inVect[4]);
										quant = stof(quantidade);
										totalP = quant * v;
										if (flag6) {
											totalP = totalP * -1;
											flag6 = false;
										}
										t = to_string(totalP);
										std::stringstream stream;
										stream << std::fixed << std::setprecision(2) << totalP;
										s = stream.str();
										contagem = contagem + totalP;
										std::stringstream stream2;
										stream2 << std::fixed << std::setprecision(2) << contagem;
										s2 = stream2.str();
										listaDeVendas[j] = "       " + codigoCategoria + "  " + codigoProduto + " " + nomeProduto +
											" " + quantidade + " " + tipo + " " + s;

										j++;

										flag5 = true;
										flag3 = true;

										out1 << "\n" << "$ " << codigoCategoria << " " << codigoProduto
											<< " " << nomeProduto << " " << tipo << " " << quantidade
											<< " " << s;
									}
									
									if ((last_iteration) && (!flag5)){
										cout << "Nao existe este codigo de produto - Pressione Enter";
										fseek(stdin,0,SEEK_END);
										getchar();
										flag3 = true;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	if ((!flag1) && (flag3) && (flag2))

		carregarListaDeVendas(j, s2);
		cout << "\n" << "Total: " << s2;

		if ((s2 != "0") && (s2 != "0,00")){
			cout << "\n" << "Informe o valor recebido: ";
			fseek(stdin, 0, SEEK_END);
			cin >> recebido;
			while (!isFloat(recebido)){
				carregarListaDeVendas(j, s2);
				cout << "\n" << "Total: " << s2;
				cout << "\n" << "Informe o valor recebido: ";
				fseek(stdin, 0, SEEK_END);
				cin >> recebido;
			}

			rec = stof(recebido);

			std::stringstream stream3;
			stream3 << std::fixed << std::setprecision(2) << rec;
			string s3 = stream3.str();

			tr = rec - contagem;

			std::stringstream stream4;
			stream4 << std::fixed << std::setprecision(2) << tr;
			string s4 = stream4.str();

			cout << "Troco: " << s4;

			out1 << "\n" << "? " << s2;
			out1 << "\n" << "% " << s3;
			out1 << "\n" << "@ " << s4;

			cout << "\n" << "Operacao finalizada - Numero da operacao: " << n_operacao;
		}else{
			if (s2 == "0,00") {
				out1 << "\n" << "? " << "0,00";
				cout << "\n" << "Operacao sem movimentacao financeira.";
				cout << "\n" << "Operacao finalizada - Numero da operacao: " << n_operacao;
			} else {
				if ((s2 == "0") && (!flag7)) {
					out1 << "\n" << "? " << "0,00";
					cout << "\n" << "Operacao sem movimentacao financeira.";
					cout << "\n" << "Operacao finalizada - Numero da operacao: " << n_operacao;
				}else {
					if ((s2 == "0") && (flag7)){
						out1 << "\n" << "? " << "0,00";
						cout << "\n" << "Operacao sem movimentacao financeira.";
						cout << "\n" << "Operacao finalizada - Numero da operacao: " << n_operacao;
					}
				}
			}
		}

	out1 << "\n" << fim;

	myfile.close();
	out1.close();

	char *file = &(nomeArquivo[0]);

	remove(file);
	rename("vendas.tmp",file);

	cout << "\n\n" << "Pressione enter para continuar";
	fseek(stdin,0,SEEK_END);
	getchar();
}
