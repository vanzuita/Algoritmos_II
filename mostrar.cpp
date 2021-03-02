//---------------------------------------------------------------------------

#pragma hdrstop

#include "mostrar.h"
//---------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------
// inicia a classe com referencia a classe maper
//-------------------------------------------------------------------------------------------
mostrar::mostrar(maper *_a){
	a = _a;
}

//-------------------------------------------------------------------------------------------
// essa funcao mostra na tela em ordem alfabetica os produtos condidos em um map
//-------------------------------------------------------------------------------------------
void mostrar::mostra(map<string,vector<string>> m){

	int i = 0;

	system("CLS");

	cout << setw(32) << setfill(' ') << "Produto" << setw(19) << setfill(' ') << "Categoria"
			<< setw(19) << setfill(' ') << "Codigo" << setw(19) << setfill(' ') << "Tipo"
			<< setw(19) << setfill(' ') << "Valor" << "\n";
			cout << setw(109) << setfill('-') << "\n\n";

	for(map<string,vector<string>>::iterator ii=m.begin(); ii!=m.end(); ++ii){

			string s = (*ii).first;

			transform(s.begin(), s.end(), s.begin(), [](char ch) {
				return ch == '_' ? ' ' : ch;
			});

			cout << "(" << setw(30) << setfill('_') << s << ")";
			vector <string> inVect = (*ii).second;


			for (unsigned j=0; j <= 3; j++){

				cout << fixed << setw(12) << setfill('.') << "(" << setw(6) << setfill('_') << inVect[j] << ")";
			}

			if (i == 24) {
				cout << "\n\n" << "Pressione enter para continuar";
                fseek(stdin,0,SEEK_END);
				getchar();
				system("CLS");
				i = 0;
				cout << setw(32) << setfill(' ') << "Produto" << setw(19) << setfill(' ')
					<< "Categoria" << setw(19) << setfill(' ') << "Codigo" << setw(19)
					<< setfill(' ') << "Tipo" << setw(19) << setfill(' ') << "Valor" << "\n";
				cout << setw(109) << setfill('-') << "\n";
			}
			i++;
			cout << endl;
	}
	cout << "\n\n" << "Pressione enter para continuar";
	fseek(stdin,0,SEEK_END);
	getchar();
}

//-------------------------------------------------------------------------------------------
// mostra na tela uma lista de produtos conforme a categoria
//-------------------------------------------------------------------------------------------
void mostrar::mostraCategorizada(int n){
	a->makeListaCategorizada(n);
	mostra(a->getListaCategorizada());
}

//-------------------------------------------------------------------------------------------
// mostra na tela a lista total de produtos em ordem alfabetica
//-------------------------------------------------------------------------------------------
void mostrar::mostraTotal() {
	mostra(a->getListaTotal());
}

//-------------------------------------------------------------------------------------------
// mostra na tela a lista de categorias por ordem alfabetica
//-------------------------------------------------------------------------------------------
void mostrar::mostraListaDeCategorias(){

	int i = 0;

	system("CLS");

	map<string,int> m;

	m = a->getCategoria();

	cout << setw(32) << setfill(' ') << "Categoria" << setw(19) << setfill(' ') << "Codigo" << "\n";
	cout << setw(109) << setfill('-') << "\n\n";

	for(map<string,int>::iterator ii=m.begin(); ii!=m.end(); ++ii){

        string s = (*ii).first;

		transform(s.begin(), s.end(), s.begin(), [](char ch) {
				return ch == '_' ? ' ' : ch;
		});

		cout << "(" << setw(30) << setfill('_') << s << ")";

		cout << fixed << setw(12) << setfill('.') << "(" << setw(6) << setfill('_') << (*ii).second << ")";

		if (i == 24) {
				cout << "\n\n" << "Pressione enter para continuar";
				fseek(stdin,0,SEEK_END);
				getchar();
				system("CLS");
				i = 0;

				cout << setw(32) << setfill(' ') << "Categoria" << setw(19) << setfill(' ') << "Codigo" << "\n";
				cout << setw(109) << setfill('-') << "\n";
		}

		i++;
		cout << endl;

	}
	cout << "\n\n" << "Pressione enter para continuar";
	fseek(stdin,0,SEEK_END);
	getchar();
}

//-------------------------------------------------------------------------------------------
// funcao auxiliar a funcao sort para ordenar um vetor por valor
//-------------------------------------------------------------------------------------------
bool mostrar::sortByVal(const pair<string, int> &a,	const pair<string, int> &b){

	return (a.second < b.second);

}

//-------------------------------------------------------------------------------------------
// funcao que mostra na tela a lista de clientes em ordem alfabetica
//-------------------------------------------------------------------------------------------
void mostrar::mostraListaDeClientes(){

	vector<pair<string, int>> v;

	v = a->getListaDeClientes();

	unsigned int i = 0;
	int j = 0;

	system("CLS");

	cout << setw(52) << setfill(' ') << "Cliente" << setw(37) << setfill(' ') << "Codigo" << "\n";
	cout << setw(109) << setfill('-') << "\n\n";

	sort(v.begin(), v.end());

	for (i = 0; i < v.size(); i++) {

		cout << "(" << setw(50) << setfill('_') << v[i].first << ")";

		cout << fixed << setw(30) << setfill('.') << "(" << setw(6) << setfill('_') << v[i].second << ")";

		if (j == 24) {
				cout << "\n\n" << "Pressione enter para continuar";
				fseek(stdin,0,SEEK_END);
				getchar();
				system("CLS");
				j = 0;

				cout << setw(52) << setfill(' ') << "Cliente" << setw(37) << setfill(' ') << "Codigo" << "\n";
				cout << setw(109) << setfill('-') << "\n";
		}
		cout << endl;
	}

    cout << "\n\n" << "Pressione enter para continuar";
	fseek(stdin, 0, SEEK_END);
	getchar();
}

void mostrar::mostraPesquisaPorNomeCliente(string n){

	string s;

	unsigned int i = 0;
	int j = 0;

	bool flag = false;

	vector<pair<string, int>> cli;

	vector<pair<string, int>> result;

	cli = a->getListaDeClientes();

	for( vector<pair<string, int>>::const_iterator itr = cli.begin(); itr != cli.end(); ++itr ){

		   s = (*itr).first;

		   if (s.find(n) != string::npos){
				result.push_back(make_pair(s,(*itr).second));
				flag = true;
		   }
	}

	if (flag) {

		system("CLS");

		cout << setw(52) << setfill(' ') << "Cliente" << setw(37) << setfill(' ') << "Codigo" << "\n";
		cout << setw(109) << setfill('-') << "\n\n";

		sort(result.begin(), result.end());

		for (i = 0; i < result.size(); i++) {

			cout << "(" << setw(50) << setfill('_') << result[i].first << ")";

			cout << fixed << setw(30) << setfill('.') << "(" << setw(6) << setfill('_') << result[i].second << ")";

			if (j == 24) {
				cout << "\n\n" << "Pressione enter para continuar";
				fseek(stdin,0,SEEK_END);
				getchar();
				system("CLS");
				j = 0;

				cout << setw(52) << setfill(' ') << "Cliente" << setw(37) << setfill(' ') << "Codigo" << "\n";
				cout << setw(109) << setfill('-') << "\n";
			}
			cout << endl;
		}
	}else{
		cout << "\n\n" << "Nao foram encontradas correspondencias";
	}

	cout << "\n\n" << "Pressione enter para continuar";
	fseek(stdin,0,SEEK_END);
	getchar();
}

void mostrar::mostraPesquisaPorIdCliente(int c){

	string s;

	unsigned int i;
	int j = 0;

	bool flag = false;

	vector<pair<string, int>> cli;

	vector<pair<string, int>> result;

	cli = a->getListaDeClientes();

    for( vector<pair<string, int>>::const_iterator itr = cli.begin(); itr != cli.end(); ++itr ){

		   s = (*itr).first;

		   if (c == (*itr).second){
				result.push_back(make_pair(s,(*itr).second));
				flag = true;
		   }
	}

    if (flag) {

		system("CLS");

		cout << setw(52) << setfill(' ') << "Cliente" << setw(37) << setfill(' ') << "Codigo" << "\n";
		cout << setw(109) << setfill('-') << "\n\n";

		sort(result.begin(), result.end());

		for (i = 0; i < result.size(); i++) {

			cout << "(" << setw(50) << setfill('_') << result[i].first << ")";

			cout << fixed << setw(30) << setfill('.') << "(" << setw(6) << setfill('_') << result[i].second << ")";

			if (j == 24) {
				cout << "\n\n" << "Pressione enter para continuar";
				fseek(stdin,0,SEEK_END);
				getchar();
				system("CLS");
				j = 0;

				cout << setw(52) << setfill(' ') << "Cliente" << setw(37) << setfill(' ') << "Codigo" << "\n";
				cout << setw(109) << setfill('-') << "\n";
			}
			cout << endl;
		}
	}else{
		cout << "\n\n" << "Nao foram encontradas correspondencias";
	}

	cout << "\n\n" << "Pressione enter para continuar";
	fseek(stdin,0,SEEK_END);
	getchar();
}

void mostrar::mostraPesquisaPorNomeProduto(string n){

	string s;

	bool flag = false;

	map<string,vector<string>> pro;

	map<string,vector<string>> result;

	pro = a->getListaTotal();

	for( map<string,vector<string>>::const_iterator itr = pro.begin(); itr != pro.end(); ++itr ){

		   s = (*itr).first;

		   vector <string> inVect = (*itr).second;

		   if (s.find(n) != string::npos){
				result[s] = inVect;
				flag = true;
		   }
	}

	if (flag) {

		mostra(result);

	} else{
		cout << "\n" << "Nao foram encotradas correspondencias";
        cout << "\n\n" << "Pressione enter para continuar";
		fseek(stdin,0,SEEK_END);
		getchar();
	}
}

void mostrar::mostraPesquisaPorIdProduto(int p){

	string s;

	string s2 = to_string(p);

	bool flag = false;

	map<string,vector<string>> pro;

	map<string,vector<string>> result;

	pro = a->getListaTotal();

	for( map<string,vector<string>>::const_iterator itr = pro.begin(); itr != pro.end(); ++itr ){

		   s = (*itr).first;

		   vector <string> inVect = (*itr).second;

		   if (inVect[1] == s2){
				result[s] = inVect;
				flag = true;
		   }
	}

	if (flag) {

		mostra(result);

	} else{
		cout << "\n" << "Nao foram encotradas correspondencias";
        cout << "\n\n" << "Pressione enter para continuar";
		fseek(stdin,0,SEEK_END);
		getchar();
	}
}
