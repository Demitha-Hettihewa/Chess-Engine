#include "game.h"

void game::printBoard() {

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for (int row = 0; row < n; row++) {
         for (int col = 0; col < n; col++) {
             SDL_Rect rect = { row * rectSize, col * rectSize, rectSize, rectSize };
             if ((row + col) % 2) {
                 SDL_SetRenderDrawColor(renderer, light.r, light.g, light.b, light.a);
             }
             else {
                 SDL_SetRenderDrawColor(renderer, dark.r, dark.g, dark.b, dark.a);
             }
             SDL_RenderFillRect(renderer, &rect);
         }
    }

}
int game::start() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }
    int imgFlags = IMG_INIT_PNG;
    if (IMG_Init(imgFlags) != imgFlags) {
        SDL_Log("Unable to initialize SDL_png: %s", SDL_GetError());
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("ChessD", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, boardSize, boardSize, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return 1;
    }
    board.push_back("br,bk,bb,bq,bK,bb,bk,br");
    board.push_back("bp,bp,bp,bp,bp,bp,bp,bp");
    board.push_back("  ,  ,  ,  ,  ,  ,  ,  ");
    board.push_back("  ,  ,  ,  ,  ,  ,  ,  ");
    board.push_back("  ,  ,  ,  ,  ,  ,  ,  ");
    board.push_back("  ,  ,  ,  ,  ,  ,  ,  ");
    board.push_back("wp,wp,wp,wp,wp,wp,wp,wp");
    board.push_back("wr,wk,wb,wq,wK,wb,wk,wr");

    loadTextures();
    
    bool update = true;
    // Event loop
    SDL_Event event;
    bool quit = false;
    int yPrev{ 1 }, xPrev{ 0 };
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int yPos = event.button.x / rectSize;
                    int xPos = event.button.y / rectSize;
                    
                    std::cout << xPos / rectSize << ", " << yPos / rectSize << "\n";
                    Piece* selected = boardV[xPos][yPos];
                    std::vector<std::pair<int, int>> possibleMoves;
                    possibleMoves = selected->getPossibleMoves(boardV);
                    highlightMoves(possibleMoves);
                    if (selected->getName() != "nd") {
                        yPrev = yPos;
                        xPrev = xPos;
                        std::cout << selected->getName() << "\n";
                    }
                    else {
                        update = true;
                        //board[xPos].replace(yPos*3, 2, board[xPrev].substr(yPrev*3, 2));
                        std::swap(boardV[xPos][yPos], boardV[xPrev][yPrev]);
                    }
                }
            }
        }
        if (update) {
            update = false;
            printBoard();
            loadPieces();
            
            loadboard();
            

            SDL_RenderPresent(renderer);
        }
    }

    // Clean up and quit
    IMG_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
}

void game::loadTextures() {
    SDL_Texture* pawnW = IMG_LoadTexture(renderer, "../Project1/Icons/PawnW.png");
    SDL_Texture* rookW = IMG_LoadTexture(renderer, "../Project1/Icons/RookW.png");
    SDL_Texture* knightW = IMG_LoadTexture(renderer, "../Project1/Icons/KnightW.png");
    SDL_Texture* bishopW = IMG_LoadTexture(renderer, "../Project1/Icons/BishopW.png");
    SDL_Texture* queenW = IMG_LoadTexture(renderer, "../Project1/Icons/QueenW.png");
    SDL_Texture* kingW = IMG_LoadTexture(renderer, "../Project1/Icons/kingW.png");

    SDL_Texture* pawnB = IMG_LoadTexture(renderer, "../Project1/Icons/PawnB.png");
    SDL_Texture* rookB = IMG_LoadTexture(renderer, "../Project1/Icons/RookB.png");
    SDL_Texture* knightB = IMG_LoadTexture(renderer, "../Project1/Icons/KnightB.png");
    SDL_Texture* bishopB = IMG_LoadTexture(renderer, "../Project1/Icons/BishopB.png");
    SDL_Texture* queenB = IMG_LoadTexture(renderer, "../Project1/Icons/QueenB.png");
    SDL_Texture* kingB = IMG_LoadTexture(renderer, "../Project1/Icons/kingB.png");

    textures["br"] = rookB;
    textures["bk"] = knightB;
    textures["bb"] = bishopB;
    textures["bq"] = queenB;
    textures["bK"] = kingB;
    textures["bp"] = pawnB;
    textures["wr"] = rookW;
    textures["wk"] = knightW;
    textures["wb"] = bishopW;
    textures["wq"] = queenW;
    textures["wK"] = kingW;
    textures["wp"] = pawnW;
}

void game::loadPieces() {
    std::vector<std::vector<Piece*>> chessBoard(n, std::vector<Piece*>(n));
    int r = 0;
    for (std::string row : board) {
        int i = 0;
        while (i*3 <= row.size()) {
            std::string item = row.substr(i*3, 2);
            std::cout << item << "\n";
            char x = item[1];
            char col = item[0];
            switch (x) {
            case 'r':
                chessBoard[r][i] = new rook(r, i, col);
                break;
                
            case 'k':
                chessBoard[r][i] = new knight(r, i, col);
                break;
            case 'b':
                chessBoard[r][i] = new bishop(r, i, col);
                break;
            case 'q':
                chessBoard[r][i] = new queen(r, i, col);
                break;
            case 'K':
                chessBoard[r][i] = new king(r, i, col);
                break;
            case 'p':
                chessBoard[r][i] = new Pawn(r, i, col);
                break;
            default:
                chessBoard[r][i] = new dummy(r, i, col);
                break;

            } 
            
            i ++;
        }
        r++;

    }
    boardV = chessBoard;

}
void game::loadboard() {
    int r = 0;
    for (std::vector<Piece*> row : boardV) {
         for(int i = 0; i < n ; i++){
            std::string item = row[i]->getName();
            std::cout << item << "oiiii\n";
            int h, w;
            float alp = 0.4;
            SDL_QueryTexture(textures[item], nullptr, nullptr, &w, &h);
            std::cout << h << ", " << w << ", " << rectSize << std::endl;
            float scale = rectSize * (1 - alp) / h;
            float w_ = scale * w;
            float h_ = scale * h;

            SDL_Rect destination = { i * rectSize + (rectSize - w_) / 2, r * rectSize + (rectSize - h_) / 2, w_, h_ };
            SDL_RenderCopy(renderer, textures[item], nullptr, &destination);
        }
        r++;
    }
}

void game::highlightMoves(const std::vector<std::pair<int, int>>& moves) {
    for (auto point : moves) {
        SDL_Rect rect = { point.first * rectSize, point.second * rectSize, rectSize, rectSize };
        SDL_SetRenderDrawColor(renderer, green.r, green.g, green.b, green.a);
        SDL_RenderFillRect(renderer, &rect);

    }
}

