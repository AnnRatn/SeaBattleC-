#pragma once
#include "Field.h";
#include "Player.h";
#include "PlayerComputer.h";
#include "PlayerUser.h";

class Game
{
	Field* FieldPlayer1;
	Field* FieldPlayer2;
	Player* Player1;
	Player* Player2;

public:
	Game() {
		Player1 = new PlayerUser();
		Player2 = new PlayerComputer();
		FieldPlayer1 = new Field(Player1->GetFileWithFieldName());
		std::cout << "My field" << std::endl;
		FieldPlayer1->DrawForMe();
		system("pause");
		system("cls");
		FieldPlayer2 = new Field(Player2->GetFileWithFieldName());
		std::cout << "My field" << std::endl;
		FieldPlayer2->DrawForMe();
		system("pause");
		system("cls");
	}

	void Battle() {
		bool win = false;
		Player* TempPlayer;
		Field* TempField;
		while (win == false) {
			std::pair<int, int> shot = Player1->MakeShot(FieldPlayer2);
			std::cout << FieldPlayer2->GetCell(shot) << std::endl;
			//если не промазали
			if (FieldPlayer2->GetCell(shot) != empty) {
				//повторно выстрелили в ту же клетку
				if (FieldPlayer2->GetCell(shot) != sheep) {
					std::cout << "You've already shot here. Try again" << std::endl;
				}
				//попали в корабль
				else {
					//если корабль убили
					if (FieldPlayer2->IsWounded(shot) != true) {
						FieldPlayer2->KillShip(shot);
						std::cout << "Ship is killed" << std::endl;
						//проверка на победу, проверяетсся только при убийстве корабля
						win = FieldPlayer2->UnguessedSheepCells();
					}
					//если корабль ранили
					else {
						FieldPlayer2->SetCell(shot, wounded);
						std::cout << "Ship is wounded" << std::endl;
					}
				}
			}
			//если промазали
			else {
				FieldPlayer2->SetCell(shot, miss);
				TempPlayer = Player1;
				Player1 = Player2;
				Player2 = TempPlayer;
				TempField = FieldPlayer2;
				FieldPlayer2 = FieldPlayer1;
				FieldPlayer1 = TempField;
				std::cout << "No ship in this cell" << std::endl;
			}
			system("pause");
			system("cls");
		}
		std::cout << "Win!" << std::endl;
	}


	~Game() {
		delete FieldPlayer1;
		delete FieldPlayer2;
		delete Player1;
		delete Player2;
	}
};

