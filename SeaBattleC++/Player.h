#pragma once
#include <iostream>;
#include <string>;

class Player
{
public:

	std::string GetFileWithFieldName() {
		std::cout << "Enter file name" << std::endl;
		std::string file;
		std::cin >> file;
		return file;
	}
	
	virtual std::pair<int, int>& MakeShot(Field* field) = 0;

	Player() {};
	~Player() {};
};