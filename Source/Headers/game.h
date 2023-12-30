#pragma once
#include "SDL.h"
#include "Pawn.h"
#include "dummy.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "king.h"
#include <vector>
#include <iostream>
#include <vector>
#include "SDL_image.h"
#include <memory.h>
#include <map>
#include "game.h"


class game
{
public:
	int start();
	

private:
	void printBoard();
	void loadTextures();
	void loadPieces();
	std::map< std::string, SDL_Texture*> textures;
	std::vector<std::string> board;
	std::map <std::pair<int, int>, Piece > pieces;
	int boardSize = 720;
	int n = 8;
	int rectSize = boardSize / n;
	SDL_Color dark = { 219, 168, 110, 255 };
	SDL_Color light = { 143, 87, 45, 255 };
	SDL_Color green = { 0, 255, 0, 150 };
	SDL_Renderer* renderer;
	void loadboard();
	std::vector<std::vector<Piece*>> boardV;
	void highlightMoves(const std::vector<std::pair<int, int>>& moves);
};

