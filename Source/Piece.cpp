#include "Piece.h"

Piece::Piece(char _type, char _color) {
	moved = false;
	type = _type;
	color = _color;
	//move(0, 0);
}
Piece::Piece(char _type, char _color, int x, int y) {
	moved = false;
	type = _type;
	color = _color;
	move(x, y);
}

void Piece::move(int x , int y) {
		xpos = x;
		ypos = y;
		std::cout << "x, y = " << x << ", " << y << "\n";
		
}
void Piece::describe() {
	std::cout << "type: " << type << "\n" << "color: " << color << "\n" << "(x, y):" << xpos << ", " << ypos << "\n";
}

std::vector<std::pair<int, int>> Piece::getPossibleMoves(const std::vector<std::vector<Piece*>>& boardV) {
	std::vector<std::pair<int, int>> dummy;
	return dummy;

}

std::string Piece::getName() {
	std::string name;
	name.push_back(color);
	name.push_back(type);
	return name;
}


