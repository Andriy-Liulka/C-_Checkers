#include "CheckerBoard.h"
#include "CheckerBoardHelper.h"
#include "Position.h"
#include "Move.h"
//#include <conio.h>
#include <time.h>
#pragma once

using namespace std;

class Gamer
{
public:
	virtual Move requestNextMove(CheckersBoard* board, CheckerBoardHelper* boardHelper, bool isFirstPlayerMove, Position* lastCaptureSpreePosition) = 0;
	int convertFromCharToInt(char symbol)
	{
		return (symbol - 'A');

	}

	bool isCurrentPositionSimpleChecker(CheckersBoard* board,Position currentPosition)
	{
		if (board->getElementDamkaOrChecker(currentPosition.x, currentPosition.y) == CHECKER)
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

	Position* convertAllDatasInElementsOfArray(string someString)
	{
		
		Position *finishPlace=new Position();
		if (someString.size() != 2)
		{
			return nullptr;
		}
		char temp1 = someString.at(0);
		const char* pointerOnTemp1 = &temp1;
		finishPlace->x = abs(atoi(pointerOnTemp1) - 8);
		char currentPosition2Temp1 = someString.at(1);
		finishPlace->y = convertFromCharToInt(currentPosition2Temp1);

		return finishPlace;
	}


};

class RealGamer :public Gamer
{
private:
	Move* currentMove = nullptr;
public:
	Move requestNextMove(CheckersBoard* board, CheckerBoardHelper* boardHelper,bool isFirstPlayerMove, Position* lastCaptureSpreePosition)
	{
		//to do 
		//input move ,revision wether
		
		while (true)
		{
			delete currentMove;
			currentMove = new Move();

			string movePositionRaw;
			bool isValidPosition;
			
			if (lastCaptureSpreePosition==nullptr)
			{
				cout << "Enter current position" << endl;
				cin >> movePositionRaw;

				currentMove->from = convertAllDatasInElementsOfArray(movePositionRaw);
				if (currentMove->from == nullptr) 
				{
					cout << "Incorrect data" << endl;
					continue;
				}
				isValidPosition = boardHelper->checkIfPositionPossible(board, currentMove->from, isFirstPlayerMove, CURRENT_PIECE);
				if (!isValidPosition)
				{
					cout << "Incorrect data" << endl;
					continue;
				}
			}
			else 
			{
				currentMove->from =new Position(*lastCaptureSpreePosition);
			}
			cout << "Enter future position" << endl;
			cin >> movePositionRaw;
			
 			currentMove->to = convertAllDatasInElementsOfArray(movePositionRaw);
			if (currentMove->to == nullptr)
			{
				cout << "Incorrect data" << endl;
				continue;
			}
			isValidPosition = boardHelper->checkIfPositionPossible(board, currentMove->to, isFirstPlayerMove, EMPTY_SPACE);
			if (!isValidPosition)
			{
				cout << "Incorrect data" << endl;
				continue;
			}

			return *currentMove;
		}
		
	}
};

class ComputerGamer :public Gamer
{
public :
	ComputerGamer()
	{
		srand(time(NULL));
	}
private:	
	static const int MAX_CHECKERS_NUMBER = 12;
	Move* currentMove = nullptr;

	Position** getCurrentPositionsForPlayer(CheckersBoard* board, bool isFirstPlayer)//cheched and works
	{
		GameCell targetCell = isFirstPlayer ? WHITE_CHECKER : BLACK_CHECKER;
		Position** playerPositions = new Position * [MAX_CHECKERS_NUMBER] {nullptr};

		int k = 0;
		for (int i = 0; i < board->BOARD_SIZE; i++)
		{
			for (int j = 0; j < board->BOARD_SIZE; j++)
			{
				if (board->getElementOwner(i, j) == targetCell)
				{
					playerPositions[k] = new Position(i, j);
					k++;
				}
			}
		}

		return playerPositions;
	}//cheched and works

	int getNumberOfPositions(Position** array)
	{
		for (int i = 0; i < MAX_CHECKERS_NUMBER; i++)
		{
			if (array[i] == nullptr)
			{
				return i;
			}
		}
		return MAX_CHECKERS_NUMBER;
	}//cheched and works

	Position* whichSideCheckerWillBeMove(Position from, bool isCurrentSimpleChecker, bool isFirstPlayer)//checked and workd
	{//ше з булеаном яка це фішка 
		int choice = 0;
		Position* to = new Position();
		if (isCurrentSimpleChecker)
		{
			choice = rand() % 2 + 1;
		}
		else
		{
			choice = rand() % 4 + 1;
		}
		if (isFirstPlayer && isCurrentSimpleChecker)
		{
			if (choice == 1)
			{
				to->x = from.x - 1;
				to->y = from.y - 1;
			}
			if (choice == 2)
			{
				to->x = from.x - 1;
				to->y = from.y + 1;
			}
			return to;
		}
		else if (!isFirstPlayer && isCurrentSimpleChecker)
		{
			if (choice == 1)
			{
				to->x = from.x + 1;
				to->y = from.y - 1;
			}
			if (choice == 2)
			{
				to->x = from.x + 1;
				to->y = from.y + 1;
			}
			return to;
		}
		if (!isCurrentSimpleChecker)
		{
			if (choice == 1)
			{
				to->x = from.x - 1;
				to->y = from.y - 1;
			}
			if (choice == 2)
			{
				to->x = from.x - 1;
				to->y = from.y + 1;
			}
			if (choice == 3)
			{
				to->x = from.x + 1;
				to->y = from.y - 1;
			}
			if (choice == 4)
			{
				to->x = from.x + 1;
				to->y = from.y + 1;
			}
			return to;
		}
		return nullptr;
	}

	//bool checkIfCanCapturePiece(CheckersBoard * board, Position position, bool isFirstPlayerTurn)
	Move* getPossibleCaptureMove(Position** playerPositions, CheckerBoardHelper* boardHelper, CheckersBoard* board, bool isFirstPlayerMove, Position* lastCaptureSpreePosition)//checked and works
	{
		Position* capturePosition = nullptr;
		
		if (lastCaptureSpreePosition != nullptr) 
		{
			capturePosition = boardHelper->getPossibleCapturePosition(board, *lastCaptureSpreePosition, isFirstPlayerMove);
			if (capturePosition!=nullptr) 
			{
				return new Move(lastCaptureSpreePosition, capturePosition);
			}
		}

		for (int i = 0; i < getNumberOfPositions(playerPositions); i++)
		{
			capturePosition = boardHelper->getPossibleCapturePosition(board, *playerPositions[i], isFirstPlayerMove);
			if (capturePosition!=nullptr)
			{
				
				return new Move(playerPositions[i], capturePosition);
			}
		}
		//_getch();
		return nullptr;
	}

	Position* whereShouldFight(Position position, CheckersBoard* board)//works and checked
	{
		Position* futurePosition = nullptr;
			if (board->getElementOwner(position.x, position.y) == BLACK_CHECKER)
			{
				if (board->getElementOwner(position.x + 1, position.y + 1) == WHITE_CHECKER && board->getElementOwner(position.x + 2, position.y + 2) == EMPTY)
				{
					board->setElement(position.x + 1, position.y + 1, EMPTY);
					futurePosition = new Position(position.x + 2, position.y + 2);
				}
				else if (board->getElementOwner(position.x + 1, position.y - 1) == WHITE_CHECKER && board->getElementOwner(position.x + 2, position.y - 2) == EMPTY)
				{
					board->setElement(position.x + 1, position.y - 1, EMPTY);
					futurePosition = new Position(position.x + 2, position.y - 2);
				}

				if (board->getElement(position.x, position.y) == BLACK_DAMKA)
				{
					if (board->getElementOwner(position.x - 1, position.y - 1) == WHITE_CHECKER && board->getElementOwner(position.x - 2, position.y - 2) == EMPTY)
					{
						board->setElement(position.x - 1, position.y - 1, EMPTY);
						futurePosition=new Position(position.x - 2, position.y - 2);
					}
					else if (board->getElementOwner(position.x - 1, position.y + 1) == WHITE_CHECKER && board->getElementOwner(position.x - 2, position.y + 2) == EMPTY)
					{
						board->setElement(position.x - 1, position.y + 1, EMPTY);
						futurePosition = new Position(position.x - 2, position.y + 2);
					}
				}
			}
			if (board->getElementOwner(position.x, position.y) == WHITE_CHECKER)
			{
				if (board->getElementOwner(position.x - 1, position.y - 1) == BLACK_CHECKER && board->getElementOwner(position.x - 2, position.y - 2) == EMPTY)
				{
					board->setElement(position.x - 1, position.y - 1, EMPTY);
					futurePosition = new Position(position.x - 2, position.y - 2);
				}
				else if (board->getElementOwner(position.x - 1, position.y + 1) == BLACK_CHECKER && board->getElementOwner(position.x - 2, position.y + 2) == EMPTY)
				{
					board->setElement(position.x - 1, position.y + 1, EMPTY);
					futurePosition = new Position(position.x - 2, position.y + 2);
				}
				if (board->getElement(position.x, position.y) == WHITE_DAMKA)
				{
					if (board->getElementOwner(position.x + 1, position.y + 1) == BLACK_CHECKER && board->getElementOwner(position.x + 2, position.y + 2) == EMPTY)
					{
						board->setElement(position.x + 1, position.y + 1, EMPTY);
						futurePosition = new Position(position.x + 2, position.y + 2);
					}
					else if (board->getElementOwner(position.x + 1, position.y - 1) == BLACK_CHECKER && board->getElementOwner(position.x + 2, position.y - 2) == EMPTY)
					{
						board->setElement(position.x + 1, position.y - 1, EMPTY);
						futurePosition = new Position(position.x + 2, position.y - 2);
					}
				}
			}
			return futurePosition;
	}

 public:

	Move  requestNextMove(CheckersBoard* board, CheckerBoardHelper* boardHelper, bool isFirstPlayerMove, Position* lastCaptureSpreePosition)//check
	{
		
		delete currentMove;
		currentMove = new Move();
		bool isValidPosition=false;
		bool isSimpleChecker=false;
		bool processInSpree = false;
		Position** playerPositions = getCurrentPositionsForPlayer(board, isFirstPlayerMove);
		Position* capturePosition = nullptr;
		Position* distinationWhenFightPossible = nullptr;
		Move* captureMove = nullptr;

		captureMove = getPossibleCaptureMove(playerPositions, boardHelper, board, isFirstPlayerMove, lastCaptureSpreePosition);
		
		if (captureMove != nullptr)
		{
			currentMove = captureMove;
			return *currentMove;
		}
		while(true) 
		{
			//зробити рандомний крок
			int randomPlace = rand() % getNumberOfPositions(playerPositions);

			currentMove->from = playerPositions[randomPlace];

			isSimpleChecker = isCurrentPositionSimpleChecker(board, *currentMove->from);

			currentMove->to = whichSideCheckerWillBeMove(*currentMove->from, isSimpleChecker, isFirstPlayerMove);

			isValidPosition = boardHelper->checkIfPositionPossible(board, currentMove->to, isFirstPlayerMove, EMPTY_SPACE);

			if (!isValidPosition)
			{
				continue;
			}
			
			return *currentMove;

		}
		delete[]playerPositions;
	}
};