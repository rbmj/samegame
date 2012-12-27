#ifndef GAMEBOARD_H_INC
#define GAMEBOARD_H_INC

#include "util.h"
#include "element.h"

#include <memory>
#include <iostream>

struct GameBoard;

GameBoard* GameBoardCreate(unsigned, unsigned, unsigned);
GameBoard* GameBoardCreate(Pointer<GameBoard>);
void GameBoardDestroy(GameBoard*);

typedef util::deleter<GameBoard>::bind<GameBoardDestroy> GameBoardDeleter;
typedef std::unique_ptr<GameBoard, GameBoardDeleter> UniqueGameBoard;

UniqueGameBoard GameBoardInstance(unsigned, unsigned, unsigned);
UniqueGameBoard GameBoardInstance(Pointer<GameBoard>);

unsigned GameBoardWidth(Pointer<GameBoard>);
unsigned GameBoardHeight(Pointer<GameBoard>);

element& GameBoardAt(Pointer<GameBoard>, unsigned, unsigned);
bool GameBoardMark(Pointer<GameBoard>, unsigned, unsigned);
void GameBoardCollapse(Pointer<GameBoard>);

void GameBoardPrint(Pointer<GameBoard>, std::ostream&);

void GameBoardFill(Pointer<GameBoard>);

#endif
