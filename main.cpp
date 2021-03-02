
#include <iostream>
#include <locale>
#include <Windows.h>
#include "menu.h"

using namespace std;

int main(){

	SetConsoleOutputCP(1252);
	SetConsoleCP ( 1252 );

	std::locale::global( std::locale( "Portuguese_Brazil.1252" ));
	std::cout.imbue(std::locale( "" ));
	std::cin.imbue(std::locale( "" ));

	system("mode 112, 32");

	menu m;

	cout << "\n\n" << "   Ate mais!";
	fseek(stdin,0,SEEK_END);
	getchar();

	return 0;
}
