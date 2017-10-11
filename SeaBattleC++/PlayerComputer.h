#pragma once
#include <list>;
#include "Player.h";

class PlayerComputer :public Player
{
public:
	PlayerComputer() {};

		std::pair<int, int>& MakeShot(Field* field) {
			int rand, x, y;
			bool pairexist = false;
			std::list<std::pair<int, int>> WoundeedShip;
			field->DrawForPartner();
			//ищем раненый корабль
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (field->GetCell(std::pair<int, int>(i + 1, j + 1)) == wounded) {
						WoundeedShip.push_back(std::pair<int, int>(i, j));
					}
				}
			}

			//если ранений нет
			if (WoundeedShip.size() == 0) {
				while (pairexist == false) {
					x = std::rand() % 10 + 1;
					y = std::rand() % 10 + 1;
					if ((field->GetCell(std::pair<int, int>(x, y)) != miss) && (field->GetCell(std::pair<int, int>(x, y)) != killed)) {
						pairexist = true;
						std::cout << x << std::endl;
						std::cout << y << std::endl;
						return std::pair<int, int>(x, y);
					}
				}
			}

			//если ранение одно
			if (WoundeedShip.size() == 1) {
				while (pairexist == false) {
					rand = std::rand() % 4;
					if (rand == 0) {
						if ((WoundeedShip.front().first > 0) && (field->GetCell(std::pair<int, int>(WoundeedShip.front().first - 1 + 1, WoundeedShip.front().second + 1)) != miss)) {
							pairexist = true;
							x = WoundeedShip.front().first - 1 + 1;
							y = WoundeedShip.front().second + 1;
							std::cout << x << std::endl;
							std::cout << y << std::endl;
							return std::pair<int, int>(x, y);
						}
					}
					if (rand == 1) {
						if ((WoundeedShip.front().first < 9) && (field->GetCell(std::pair<int, int>(WoundeedShip.front().first + 1 + 1, WoundeedShip.front().second + 1)) != miss)) {
							pairexist = true;
							x = WoundeedShip.front().first + 1 + 1;
							y = WoundeedShip.front().second + 1;
							std::cout << x << std::endl;
							std::cout << y << std::endl;
							return std::pair<int, int>(x, y);
						}
					}
					if (rand == 2) {
						if ((WoundeedShip.front().second > 0) && (field->GetCell(std::pair<int, int>(WoundeedShip.front().first + 1, WoundeedShip.front().second - 1 + 1)) != miss)) {
							pairexist = true;
							x = WoundeedShip.front().first + 1;
							y = WoundeedShip.front().second - 1 + 1;
							std::cout << x << std::endl;
							std::cout << y << std::endl;
							return std::pair<int, int>(x, y);
						}
					}
					if (rand == 3) {
						if ((WoundeedShip.front().second < 9) && (field->GetCell(std::pair<int, int>(WoundeedShip.front().first + 1, WoundeedShip.front().second + 1 + 1)) != miss)) {
							pairexist = true;
							x = WoundeedShip.front().first + 1;
							y = WoundeedShip.front().second + 1 + 1;
							std::cout << x << std::endl;
							std::cout << y << std::endl;
							return std::pair<int, int>(x, y);
						}
					}
				}
			}

			//если ранений несколько
			if (WoundeedShip.size() > 1) {
				//горизонтальная ориентация
				if (WoundeedShip.front().second == WoundeedShip.back().second) {
					while (pairexist == false) {
						rand = std::rand() % 2;
						if (rand == 0) {
							if ((WoundeedShip.front().first > 0) && (field->GetCell(std::pair<int, int>(WoundeedShip.front().first - 1 + 1, WoundeedShip.front().second + 1)) != miss)) {
								pairexist = true;
								x = WoundeedShip.front().first - 1 + 1;
								y = WoundeedShip.front().second + 1;
								std::cout << x << std::endl;
								std::cout << y << std::endl;
								return std::pair<int, int>(x, y);
							}
						}
						if (rand == 1) {
							if ((WoundeedShip.back().first < 9) && (field->GetCell(std::pair<int, int>(WoundeedShip.back().first + 1 + 1, WoundeedShip.back().second + 1)) != miss)) {
								pairexist = true;
								x = WoundeedShip.back().first + 1 + 1;
								y = WoundeedShip.back().second + 1;
								std::cout << x << std::endl;
								std::cout << y << std::endl;
								return std::pair<int, int>(x, y);
							}
						}
					}
				}
				//вертикальная ориентация
				else {
					while (pairexist == false) {
						rand = std::rand() % 2;
						if (rand == 0) {
							if ((WoundeedShip.front().second > 0) && (field->GetCell(std::pair<int, int>(WoundeedShip.front().first + 1, WoundeedShip.front().second - 1 + 1)) != miss)) {
								pairexist = true;
								x = WoundeedShip.front().first + 1;
								y = WoundeedShip.front().second - 1 + 1;
								std::cout << x << std::endl;
								std::cout << y << std::endl;
								return std::pair<int, int>(x, y);
							}
						}
						if (rand == 1) {
							if ((WoundeedShip.back().second < 9) && (field->GetCell(std::pair<int, int>(WoundeedShip.back().first + 1, WoundeedShip.back().second + 1 + 1)) != miss)) {
								pairexist = true;
								x = WoundeedShip.back().first + 1;
								y = WoundeedShip.back().second + 1 + 1;
								std::cout << x << std::endl;
								std::cout << y << std::endl;
								return std::pair<int, int>(x, y);
							}
						}
					}
				}
			}


		}

	~PlayerComputer() {};
};

