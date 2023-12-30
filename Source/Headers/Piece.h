#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <vector>

class Piece
{
public:
	Piece(char type, char color);
	Piece(char type, char color, int x, int y);
	void move(int x, int y);
	void describe();
	std::string getName();
	virtual std::vector<std::pair<int, int>> getPossibleMoves(const std::vector<std::vector<Piece*>>& boardV);

private:
	char color;
	char type;
	
protected:

	int xpos{ -1 };
	int ypos{ -1 };	
	bool moved;
	

};

