//---------------------------------------------------------------------------

#pragma hdrstop

#include "maper.h"
//---------------------------------------------------------------------------



template <typename T>
string to_string_with_precision(const T a_value, const int n = 2)
{
	ostringstream out;
	out.precision(n);
	out << fixed << a_value;
	return out.str();
}

//-----------------------------------------------------------------------
// A funcao is_number eh usada para verificar se uma string eh um numero
//-----------------------------------------------------------------------
bool maper::is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

//-----------------------------------------------------------------------
// A funcao isFloat eh usada para verificar se uma string eh um float
//-----------------------------------------------------------------------
bool maper::isFloat( string myString ) {
	std::istringstream iss(myString);
	float f;
	iss >> noskipws >> f; // noskipws considers leading whitespace invalid
	// Check the entire string was consumed and if either failbit or badbit is set
	return iss.eof() && !iss.fail();
}

//-------------------------------------------------------------------------------------------
// inicializa a classe maper, preenchendo os maps com os dados contidos no arquivo texto
//-------------------------------------------------------------------------------------------
maper::maper(string n){

	makeCategoria(n);
	makeProduto(n);
	convertCodigoNome();
}

//-------------------------------------------------------------------------------------------
// preenche o map relativo aos nomes de categorias e seus codigos
//-------------------------------------------------------------------------------------------
void maper::makeCategoria(string n){

	string c, s;

	int num;

	ifstream myfile(n);

	myfile.clear();
	myfile.seekg(0, ios::beg);

	while (myfile >> c){
		if (c == "#") {

			string substr;
			getline(myfile,s);
			istringstream iss(s);

			while ((iss) && (substr != " ")){
				getline(iss,substr,' ');
				if (is_number(substr)) {
					istringstream ( substr ) >> num;
				}

				if (substr != " ") {
					if((substr.size() != 0) && (!is_number(substr)) && (!isFloat(substr))) {
						porCategoria[num] = substr;
						porNomeCategoria[substr] = num;
					}
				}
			}
		}
	}

	myfile.close();
}


//-------------------------------------------------------------------------------------------
// preenche o map relativo aos produtos, cujas keys sao pares de categoria e codigo
//-------------------------------------------------------------------------------------------
void maper::makeProduto(string nome){

	string c,s;

	int l = 0;
	int k = 0;

	int n,m;

	ifstream myfile(nome);

	myfile.clear();
	myfile.seekg(0, ios::beg);

	while (myfile >> c){
		if (c == ">") {

			string substr, substr2;
			getline(myfile,s);
			istringstream iss(s);

			while ((iss) && (substr != " ")){

				getline(iss,substr,' ');

				if ( (l == 0) && (substr != "")){
					istringstream ( substr ) >> n;
					substr2 = substr;
					l++;
				}

				if (l == 1) {
					getline(iss,substr,' ');
					istringstream ( substr ) >> m;
					l++;
				}

				if ((substr.size() != 0) && ((substr.find(',') == std::string::npos ))){

					if (l == 2) {
						porCodigo[make_pair(n,m)].push_back(substr2);
						porCodigo[make_pair(n,m)].push_back(substr);
						l++;
					}
					else {
						porCodigo[make_pair(n,m)].push_back(substr);
					}

				}

				if ((substr.size() != 0) && ((substr.find(',') != std::string::npos ) && (k == 0))){
					porCodigo[make_pair(n,m)].push_back(substr);
					k++;
				}
			}
			k = 0;
			l = 0;
		}
	}

	myfile.close();

}

void maper::clearAll(){

	porCategoria.clear();
	porNomeCategoria.clear();
	porCodigo.clear();
	porNomeProduto.clear();
}


//-------------------------------------------------------------------------------------------
// preenche um map de nome de produtos por categoria
//-------------------------------------------------------------------------------------------
void maper::makeListaCategorizada(int c){

	porListaCategorizada.clear();

	for(map<pair<int,int>, vector<string> >::iterator it=porCodigo.begin(); it!=porCodigo.end(); ++it) {

		if ((*it).first.first == c) {

			vector <string> inVect = (*it).second;

			porListaCategorizada[inVect[2]].push_back(inVect[0]);
			porListaCategorizada[inVect[2]].push_back(inVect[1]);
			porListaCategorizada[inVect[2]].push_back(inVect[3]);
			porListaCategorizada[inVect[2]].push_back(inVect[4]);
		}
	}
}

//-------------------------------------------------------------------------------------------
// retorna uma lista de produtos categorizada
//-------------------------------------------------------------------------------------------
map<string,vector<string>> maper::getListaCategorizada() {
	return porListaCategorizada;
}

//-------------------------------------------------------------------------------------------
// retorna um map cuja key eh o nome do produto
//-------------------------------------------------------------------------------------------
map<string,vector<string>> maper::getListaTotal(){
	return  porNomeProduto;
}

//-------------------------------------------------------------------------------------------
// retorna um map cuja key eh um par categoria/produto
//-------------------------------------------------------------------------------------------
map<pair<int,int>, vector<string>> maper::getListaPorCodigo(){
    return porCodigo;
}

//-------------------------------------------------------------------------------------------
// retorna uma lista de categorias por nome
//-------------------------------------------------------------------------------------------
map<string,int> maper::getCategoria(){
	return porNomeCategoria;
}

//-------------------------------------------------------------------------------------------
// esta funcao preenche um map de nomes de produtos atraves de um map de codigo de produto
//-------------------------------------------------------------------------------------------
void maper::convertCodigoNome()
{
	for(map<pair<int,int>, vector<string> >::iterator it=porCodigo.begin(); it!=porCodigo.end(); ++it) {

		vector <string> inVect = (*it).second;

		porNomeProduto[inVect[2]].push_back(inVect[0]);
		porNomeProduto[inVect[2]].push_back(inVect[1]);
		porNomeProduto[inVect[2]].push_back(inVect[3]);
		porNomeProduto[inVect[2]].push_back(inVect[4]);
	}
}

//-------------------------------------------------------------------------------------------
// esta funcao salva o map de produtos para um arquivo texto
//-------------------------------------------------------------------------------------------
void maper::salvarMapProdutos(string n){

	ofstream out(n);

	for(map<int,string>::iterator it=porCategoria.begin(); it!=porCategoria.end(); ++it){

		makeListaCategorizada((*it).first);

		out << "# " << (*it).first << " " << (*it).second << "\n";

		for(map<string,vector<string>>::iterator it2=porListaCategorizada.begin(); it2!=porListaCategorizada.end(); ++it2){

			 vector <string> inVect = (*it2).second;

			 out << "> " << inVect[0] << " " << inVect[1] << " " << (*it2).first << " " << inVect[2]
				<< " " << inVect[3] << "\n";

		}
	}
}
//-------------------------------------------------------------------------------------------
// testa se ja existe um nome de categoria, se nao, inclui sequencialmente uma nova catagoria
//-------------------------------------------------------------------------------------------
bool maper::incluirCategoria(string n){

	for(map<string,int>::iterator it=porNomeCategoria.begin(); it!=porNomeCategoria.end(); ++it){

		if ((*it).first == n) {
			return false;
		}
	}

	int i = 0;

	for(map<int, string>::iterator it=porCategoria.begin(); it!=porCategoria.end(); ++it){

		i++;

		bool last_iteration = it == (--porCategoria.end());
		
		if (i != (*it).first){
			break;
		}

		if (last_iteration) {
			i++;
		}
	}

	porNomeCategoria[n] = i;
	porCategoria[i] = n;

	return true;
}


//-------------------------------------------------------------------------------------------
// testa se existe a categoria, se existe, testa se ja existe o produto,
// se nao, inclui sequencialmente
//
// return:
//			0: ok
//			1: nao exite a categoria
//			2: ja existe o produto
//-------------------------------------------------------------------------------------------
int maper::incluirProduto(string p, int c, string tipo, string valor){

	string s = to_string(c);

	for(map<int, string>::iterator it=porCategoria.begin(); it!=porCategoria.end(); ++it){

		bool last_iteration = it == (--porCategoria.end());

		if (c == (*it).first){
			break;
		}

		if (last_iteration) {
			return 1;
		}
	}

	for(map<string,vector<string>>::iterator it=porNomeProduto.begin(); it!=porNomeProduto.end(); ++it){

		if (p == (*it).first) {
			return 2;
		}

	}

	int i = 0;

	for(map<pair<int,int>, vector<string>>::iterator it=porCodigo.begin(); it!=porCodigo.end(); ++it){

		i++;

		bool last_iteration = it == (--porCodigo.end());

		if (i != (*it).first.second){
			break;
		}

		if (last_iteration) {
			i++;
		}
	}

	string s2 = to_string(i);

	porCodigo[make_pair(c,i)].push_back(s);
	porCodigo[make_pair(c,i)].push_back(s2);
	porCodigo[make_pair(c,i)].push_back(p);
	porCodigo[make_pair(c,i)].push_back(tipo);
	porCodigo[make_pair(c,i)].push_back(valor);

	convertCodigoNome();

	return 0;
}


//-------------------------------------------------------------------------------------------
// verifica se existe a categoria, depois verifica se existem produtos na categoria
// se tiver, pergunta se deseja realmente excluir, retorna true se excluiu ou false se não
//-------------------------------------------------------------------------------------------
bool maper::excluirCategoria(int c){

	bool flag1, flag2 = false;

	string s2, s3;

	for(map<int, string>::iterator it=porCategoria.begin(); it!=porCategoria.end(); ++it){

		bool last_iteration = it == (--porCategoria.end());

		if (c == (*it).first){
			string s = to_string((*it).first);
			s2 = s;
			s3= (*it).second;
			flag1 = true;
			break;
		}

		if (last_iteration) {
			return false;
		}
	}

	char t;

	if (flag1) {

		for(map<pair<int,int>, vector<string>>::iterator it=porCodigo.begin(); it!=porCodigo.end(); ++it){

			vector <string> inVect = (*it).second;

			if (s2 == inVect[0]){

				if (!flag2) {
					cout << "\n\n" << "Todos os produtos vinculados a esta categoria serao excluidos. Deseja continuar? (S, N): ";
					fseek(stdin, 0, SEEK_END);
					cin >> t;
					if ((t == 's') || (t == 'S')){
						flag2 = true;
					}
					else {
						flag1 = false;
						break;
					}
				}

				if (flag2){
					porCodigo.erase(it);
				}
			}
		}
	}

	if (flag1) {

		for(map<int, string>::iterator it=porCategoria.begin(); it!=porCategoria.end(); ++it){

			bool last_iteration = it == (--porCategoria.end());

			if (c == (*it).first){
				porCategoria.erase(it);
				break;
			}
		}

		for(map<string,int>::iterator it=porNomeCategoria.begin(); it!=porNomeCategoria.end(); ++it){

			if(s3 == (*it).first){

				porNomeCategoria.erase(it);
				break;
			}
		}
		porNomeProduto.clear();
		convertCodigoNome();
	}
	else{
		return false;
    }
	return true;
}
//-------------------------------------------------------------------------------------------
// testa se existe o produto, se existe, exclui;
// retorna false se nao excluiu ou true se excluiu
// o correto é nao excluir um produto, pois na hora de gerar uma nova id
// para um novo produto sera calculada sequencialmente uma id que era desse
// produto excluido, e como sabemos um produto deve ter uma id unica
// como o codigo de barras EAN
// obs: deixada aqui so para titulo de didatica
//-------------------------------------------------------------------------------------------
bool maper::excluirProduto(int p){

	for(map<pair<int,int>, vector<string>>::iterator it=porCodigo.begin(); it!=porCodigo.end(); ++it){

		bool last_iteration = it == (--porCodigo.end());

		if (p == (*it).first.second){
			porCodigo.erase(it);
			break;
		}

		if (last_iteration) {
			return false;
		}
	}

	porNomeProduto.clear();
	convertCodigoNome();
	return true;
}

//-------------------------------------------------------------------------------------------
// testa se existe o produto e muda o valor da mercadoria
// retorna true se conseguiu mudar o valor ou false se nao
//-------------------------------------------------------------------------------------------
bool maper::mudarValor(int p, float valor){

	vector <string> temp;

	pair<int, int> temp2;

	string s;

	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << valor;
	s = stream.str();

	for(map<pair<int,int>, vector<string>>::iterator it=porCodigo.begin(); it!=porCodigo.end(); ++it){

		bool last_iteration = it == (--porCodigo.end());

		vector <string> inVect = (*it).second;

		if (p == (*it).first.second) {

			temp = inVect;
			temp[4] = s;
			temp2 = make_pair((*it).first.first, p);
			porCodigo[temp2] = temp;
			break;
		}

		if (last_iteration) {
			return false;
		}
	}

	porNomeProduto.clear();
	convertCodigoNome();

	return true;
}


//-------------------------------------------------------------------------------------------
// testa se existe a categoria, se existe, testa se ja existe uma categoria com esse nome,
// se nao, renomeia
//
// return:
//			0: ok
//			1: nao exite a categoria
//			2: ja existe uma categoria com este nome
//-------------------------------------------------------------------------------------------
int maper::renomearCategoria(int c, string novo){

	string s;

	for(map<int, string>::iterator it=porCategoria.begin(); it!=porCategoria.end(); ++it){

		bool last_iteration = it == (--porCategoria.end());

		if (c == (*it).first){
			s = (*it).second;
			break;
		}

		if (last_iteration) {
			return 1;
		}
	}

	for(map<string,int>::iterator it=porNomeCategoria.begin(); it!=porNomeCategoria.end(); ++it){

		if (novo == (*it).first){
			return 2;
		}
	}

	for(map<int, string>::iterator it=porCategoria.begin(); it!=porCategoria.end(); ++it){

		bool last_iteration = it == (--porCategoria.end());

		if (c == (*it).first){
			porCategoria[c] = novo;
			break;
		}

		if (last_iteration) {
			return false;
		}
	}

	for(map<string,int>::iterator it=porNomeCategoria.begin(); it!=porNomeCategoria.end(); ++it){

		if (s == (*it).first){
			porNomeCategoria.erase(it);
		}
	}

	porNomeCategoria[novo] = c;

	return 0;
}

//-------------------------------------------------------------------------------------------
// testa se existe o numero de produto, depois testa se ja exite um produto com o novo nome
// retorna 0 se renomeou, 1 se nao exite o numero de produto ou 2 se ja existe um produto com este nome
//-------------------------------------------------------------------------------------------
int maper::renomearProduto(int p, string novo){

    vector <string> temp;

	pair<int, int> temp2;

	for(map<pair<int,int>, vector<string>>::iterator it=porCodigo.begin(); it!=porCodigo.end(); ++it){

		bool last_iteration = it == (--porCodigo.end());

		vector <string> inVect = (*it).second;

		if (p == (*it).first.second) {
			break;
		}

		if (last_iteration) {
			return 1;
		}
	}

    for(map<pair<int,int>, vector<string>>::iterator it=porCodigo.begin(); it!=porCodigo.end(); ++it){

		bool last_iteration = it == (--porCodigo.end());

		vector <string> inVect = (*it).second;

		temp = inVect;
		temp[2] = novo;

		if (temp == (*it).second) {
			return 2;
		}

		if (last_iteration) {
			break;
		}
	}

	for(map<pair<int,int>, vector<string>>::iterator it=porCodigo.begin(); it!=porCodigo.end(); ++it){

		bool last_iteration = it == (--porCodigo.end());

		vector <string> inVect = (*it).second;

		if (p == (*it).first.second) {

			temp = inVect;
			temp[2] = novo;
			temp2 = make_pair( (*it).first.first, p );
			porCodigo[temp2] = temp;
			break;
		}
	}
	porNomeProduto.clear();
	convertCodigoNome();

	return 0;
}
//-------------------------------------------------------------------------------------------
// faz um vetor de lista de clientes a partir de um arquivo conforme especificacao
//-------------------------------------------------------------------------------------------
void maper::makeListaDeClientes(string n){

	char c;
	string nome[1000];
	string id[1000];

	int i = 0;

	string s;

	ifstream myfile(n);

	myfile.clear();
	myfile.seekg(0, ios::beg);

	while (myfile >> c){

		getline(myfile,s);

		size_t pos1 = s.find("<");
		size_t pos2 = s.find(">");

		string s2 = s.substr (pos1+1,pos2);

		pos1 = s.find("#");

		string s3 = s.substr (pos1+1);

		istringstream (s3) >> i;

		listaDeClientes.push_back(make_pair(s2,i));
	}
}
//-------------------------------------------------------------------------------------------
// retorna o vetor de lista de clientes
//-------------------------------------------------------------------------------------------
vector<pair<string, int>> maper::getListaDeClientes(){
	return listaDeClientes;
}

//-------------------------------------------------------------------------------------------
// salva a lista de clientes para um arquivo texto
//-------------------------------------------------------------------------------------------
void maper::salvarClientes(string n){

	ofstream out(n);

	for (auto const& x : listaDeClientes) {
		out << '<' << x.first << '>' << '#' << x.second << '\n';
	}
}

//-------------------------------------------------------------------------------------------
// funcao auxiliar a funcao sort para ordenar um vetor por valor
//-------------------------------------------------------------------------------------------
bool sortByVal(const pair<string, int> &a,	const pair<string, int> &b){

	return (a.second < b.second);

}

//-------------------------------------------------------------------------------------------
// insere um novo cliente e calcula a id sequencialmente
//-------------------------------------------------------------------------------------------
void maper::setCliente(string n){

	int i = 0;

	vector<pair<string, int>> temp;

	temp = listaDeClientes;

	sort(temp.begin(), temp.end(), sortByVal);

	for (auto const& elem : temp) {

		if (i != (elem.second) - 1) {
			break;
		}

		if (&elem == &temp.back()){
			i++;
			break;
		}

		i++;

	}
	listaDeClientes.push_back(make_pair(n,i+1));
}

void maper::clearClientes(){

	listaDeClientes.clear();
}

bool maper::renomearCliente(string n, int c){

	vector<pair<string, int>> temp;

	temp = listaDeClientes;

	int i = 0;

	for (auto const& elem : temp) {

		if (elem.second == c){
			listaDeClientes.push_back(make_pair(n,c));
			break;
		}

		if (&elem == &temp.back()){
			return false;
		}
		i++;
	}
	listaDeClientes.erase(listaDeClientes.begin()+i);
	return true;
}
