// SeaBattleC++.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Field.h";
#include "Game.h";
#include "Player.h";


int main()
{
	try {
		Game* g = new Game();
		g->Battle();
		system("pause");
	}
	catch (std::exception ex) {
		std::cout << ex.what() << std::endl;
		system("pause");
	}
    return 0;
}

