#pragma once
#include "Piece.h"
class Pawn : public Piece
{
public:
	Pawn(int x, int y, char color);

private:
	std::vector<std::pair<int, int>> getPossibleMoves(std::vector<std::vector<Piece*>>& boardV);


};

