#pragma once
#include "Player.h";

class PlayerUser :public Player
{
public:
	PlayerUser() {};

		std::pair<int, int>& MakeShot(Field* field) {
			field->DrawForPartner();
			int x, y;
			std::cout << "Make a shot" << std::endl;
			std::cin >> x;
			std::cin >> y;
			if ((0 >= x >= 10) || (0 >= y >= 10)) throw std::exception("Wrong cell");
			return std::pair<int, int>(x, y);
		}

	~PlayerUser() {};
};

