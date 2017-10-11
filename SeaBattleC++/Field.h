#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <exception>

enum CellState {empty, sheep, wounded, killed, miss};

class Field
{
	CellState** field;

	void MissCells(int x, int y) {
		if (x < 9) {
			if (field[x + 1][y] == empty) field[x + 1][y] = miss;
			if (y < 9) {
				if (field[x + 1][y + 1] == empty) field[x + 1][y + 1] = miss;
			}
			if (y > 0) {
				if (field[x + 1][y - 1] == empty) field[x + 1][y - 1] = miss;
			}
		}
		if (x > 0) {
			if (field[x - 1][y] == empty) field[x - 1][y] = miss;
			if (y < 9) {
				if (field[x - 1][y + 1] == empty) field[x - 1][y + 1] = miss;
			}
			if (y > 0) {
				if (field[x - 1][y - 1] == empty) field[x - 1][y - 1] = miss;
			}
		}
		if (y < 9) {
			if (field[x][y + 1] == empty) field[x][y + 1] = miss;
		}
		if (y > 0) {
			if (field[x][y - 1] == empty) field[x][y - 1] = miss;
		}
	}

public:
	Field(std::string& file) {
		int x, y;
		std::ifstream reader(file);
		if (!reader) throw std::exception("Wrong file name");
		field = new CellState*[10];
		for (int i = 0; i < 10; i++) {
			field[i] = new CellState[10];
		}
		std::string str;
		while (getline(reader, str)) {
			x = atoi(str.substr(0, str.find(" ")).c_str());
			int count = (str.size() - str.find(" ") - 1);
			y = atoi(str.substr(str.find(" ") + 1, count).c_str());
			if ((0 >= x >= 10) || (0 >= y >= 10)) throw std::exception("Wrong cell");
			field[x - 1][y - 1] = sheep;
		}
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (field[i][j] != sheep) field[i][j] = empty;
			}
		}
	}

	void DrawForMe() {
		for (int j = 10; j > 0; j--)
		{
			if (j != 10)
			{
				std::cout << j << "   ";
			}
			else
			{
				std::cout << j << "  ";
			}
			for (int i = 1; i < 11; i++)
			{
				if (field[i - 1][j - 1] == sheep) std::cout << "1  ";
				else std::cout << "0  ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		std::cout << "    ";
		for (int i = 1; i < 11; i++)
		{
			std::cout << i << "  ";
		}
		std::cout << std::endl;
	}

	void DrawForPartner() {
		for (int j = 10; j > 0; j--)
		{
			if (j != 10)
			{
				std::cout << j << "   ";
			}
			else
			{
				std::cout << j << "  ";
			}
			for (int i = 1; i < 11; i++)
			{
				if (field[i - 1][j - 1] == killed) std::cout << "2  ";
				else {
					if (field[i - 1][j - 1] == wounded) std::cout << "1  ";
					else {
						if (field[i - 1][j - 1] == miss) std::cout << "!  ";
						else std::cout << "0  ";
					}
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		std::cout << "    ";
		for (int i = 1; i < 11; i++)
		{
			std::cout << i << "  ";
		}
		std::cout << std::endl;
	}

	CellState GetCell(std::pair<int, int>& shot) {
		return field[shot.first - 1][shot.second - 1];
	}

	void SetCell(std::pair<int, int>& shot, CellState state) {
		field[shot.first - 1][shot.second - 1] = state;
	}

	bool UnguessedSheepCells() {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (field[i][j] == sheep) return false;
			}
		}
		return true;
	}

	bool IsWounded(std::pair<int, int>& shot) {
		int x = shot.first - 1, y = shot.second - 1;
		bool HorisOrient = false;
		if (shot.first == 10) {
			if ((field[shot.first - 2][shot.second - 1] == sheep) || (field[shot.first - 2][shot.second - 1] == wounded)) HorisOrient = true;
		}
		else {
			if (shot.first == 1) {
				if ((field[shot.first][shot.second - 1] == sheep) || (field[shot.first][shot.second - 1] == wounded)) HorisOrient = true;
			}
			else {
				if ((field[shot.first][shot.second - 1] == sheep) || (field[shot.first - 2][shot.second - 1] == sheep) || (field[shot.first][shot.second - 1] == wounded) || (field[shot.first - 2][shot.second - 1] == wounded)) HorisOrient = true;
			}
		}
		int k = 0;
		if (HorisOrient == true) {
			while ((x < 9) && (field[x + 1][y] != empty) && (field[x + 1][y] != miss)) {
				if (field[x + 1][y] == sheep) k++;
				x++;
			}
			x = shot.first - 1; 
			y = shot.second - 1;
			while ((x > 0) && (field[x - 1][y] != empty) && (field[x - 1][y] != miss)) {
				if (field[x - 1][y] == sheep) k++;
				x--;
			}
		}
		else {
			while ((y < 9) && (field[x][y + 1] != empty) && (field[x][y + 1] != miss)) {
				if (field[x][y + 1] == sheep) k++;
				y++;
			}
			x = shot.first - 1;
			y = shot.second - 1;
			while ((y > 0) && (field[x][y - 1] != empty) && (field[x][y - 1] != miss)) {
				if (field[x][y - 1] == sheep) k++;
				y--;
			}
		}
		if (k > 0) return true;
		else return false;
	}

	void KillShip(std::pair<int, int>& shot) {
		bool HorisOrient = false;
		if (shot.first == 10) {
			if (field[shot.first - 2][shot.second - 1] == wounded) HorisOrient = true;
		}
		else {
			if (shot.first == 1) {
				if (field[shot.first][shot.second - 1] == wounded) HorisOrient = true;
			}
			else {
				if((field[shot.first][shot.second - 1] == wounded) || (field[shot.first - 2][shot.second - 1] == wounded)) HorisOrient = true;
			}
		}
		CellState state = wounded;
		int x = shot.first - 1, y = shot.second - 1;
		while (state == wounded) {
			field[x][y] = killed;
			if (HorisOrient == true) {
				if (x < 9) {
					if(y < 9) field[x][y + 1] = miss;
					if (y > 0) field[x][y - 1] = miss;
					x++;
					state = field[x][y];
				}
				else {
					if (y < 9) field[x][y + 1] = miss;
					if (y > 0) field[x][y - 1] = miss;
					break;
				}
			}
			else {
				if (y < 9) {
					if (x < 9) field[x + 1][y] = miss;
					if (x > 0) field[x - 1][y] = miss;
					y++;
					state = field[x][y];
				}
				else {
					if (x < 9) field[x + 1][y] = miss;
					if (x > 0) field[x - 1][y] = miss;
					break;
				}
			}
		}
		if ((x == shot.first - 1) && (y == shot.first - 1)) MissCells(x, y);
		else {
			if (HorisOrient == true) MissCells(x - 1, y);
			else MissCells(x, y - 1);
		}
		
		x = shot.first - 1; 
		y = shot.second - 1;
		state = field[x][y];
		if (HorisOrient == true) {
			if (x > 0) {
				state = field[x - 1][y];
				x--;
			}
		}
		else {
			if (y > 0) {
				state = field[x][y - 1];
				y--;
			}
		}
		while (state == wounded) {
			field[x][y] = killed;
			if (HorisOrient == true) {
				if (x > 0) {
					if (y < 9) field[x][y + 1] = miss;
					if (y > 0) field[x][y - 1] = miss;
					x--;
					state = field[x][y];
				}
				else {
					if (y < 9) field[x][y + 1] = miss;
					if (y > 0) field[x][y - 1] = miss;
					break;
				}
			}
			else {
				if (y > 0) {
					if (x < 9) field[x + 1][y] = miss;
					if (x > 0) field[x - 1][y] = miss;
					y--;
					state = field[x][y];
				}
				else {
					if (x < 9) field[x + 1][y] = miss;
					if (x > 0) field[x - 1][y] = miss;
					break;
				}
			}
		}
		if ((x == shot.first - 1) && (y == shot.first - 1)) MissCells(x, y);
		else {
			if (HorisOrient == true) MissCells(x + 1, y);
			else MissCells(x, y + 1);
		}
	}

	~Field() {
		for (int i = 0; i < 10; i++) {
			delete[] field[i];
		}
	}
};

