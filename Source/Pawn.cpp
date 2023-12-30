#include "Pawn.h"

Pawn::Pawn(int xPos, int yPos, char color) :Piece('p', color, xPos, yPos) {}

std::vector<std::pair<int, int>> Pawn::getPossibleMoves(std::vector<std::vector<Piece*>>& boardV)  {
	std::vector<std::pair<int, int>> possibleMoves;
	if (boardV[xpos + 1][ypos]->getName() == "nd") {
		possibleMoves.push_back(std::make_pair(xpos + 1, ypos));
		if (!moved) {
			if (boardV[xpos + 2][ypos]->getName() == "nd") {
				possibleMoves.push_back(std::make_pair(xpos + 2, ypos));
			}
		}
	}
	return possibleMoves;
}