#pragma once
#include "Gamer.h"
#include "Move.h"
#include "CheckerBoard.h"
#include "MoveValidator.h"
#include "CheckerBoardHelper.h"

class CheckersGameController //class for printing of board
{
public:
	Gamer *gamer1;
	Gamer* gamer2;
	CheckersBoard* board;
	CheckerBoardHelper* helper;

	CheckersGameController()
	{
		gamer1 = new RealGamer(); /*RealGamer*/
		gamer2 = new ComputerGamer()/*ComputerGamer()*/;
		board = new CheckersBoard();
		helper = new CheckerBoardHelper();

		board->fillStandartBoard();/*fillTestBoard()*/

	}
	void deletorObjects(CheckersBoard* board, CheckerBoardHelper* helper)
	{
		delete board;
		delete helper;
	}

	
	
	void startGame() 
	{
		bool firstGamerTurn = true;
		Position *lastCaptureSpreePosition=nullptr;
		while (true)
		{
			system("cls");
			board->printerOfBoard();
			Gamer* currentGamer = firstGamerTurn ? gamer1 : gamer2;
			bool isOnCaptureSpree = lastCaptureSpreePosition != nullptr;
			Move nextMove;
			switch (helper->isGameFinished(board, firstGamerTurn))
			{
				case FIRST_PLAYER_WIN:
				{
					delete gamer1;
					deletorObjects(board,helper);
					cout << "First Player Win" << endl;
					return;
				}
				case SECOND_PLAYER_WIN:
				{
					delete gamer2;
					deletorObjects(board, helper);
					cout << "Second Player Win" << endl;
					return;
				}
			}

			while (true) 
			{
				nextMove = currentGamer->requestNextMove(board, helper, firstGamerTurn, lastCaptureSpreePosition);
				//static bool chackIfMovePossible(CheckersBoard* board, CheckerBoardHelper* helper, Move move, bool isFirstPlayerTurn, Position* captureSpreePosition)
				MoveValidationResult validationResult = MoveValidator::chackIfMovePossible(board,helper,nextMove,firstGamerTurn, lastCaptureSpreePosition);
				if (validationResult == VALID)
				{
					break;
				}
				switch (validationResult) //винести в метод
				{
					case CURRENT_POSITION_SHOULD_BE_THE_SAME_AS_LAST_FROM_LAST_FIGHT:
					{
						cout << "You can fight again" << endl;
						break;
					}
					case PLACE_WITHOUT_YOUR_CHECKER:
					{
						cout << "It isn't you checker" << endl;
						break;
					}
					case INVALID_DISTINATION:
					{
						cout << "Bad distination" << endl;
						break;
					}
					case YOU_CANNOT_MOVE_WITH_CURRENT_CHECKER:
					{
						cout << "You cannot move with current checker" << endl;
						break;
					}
					case YOU_CAN_FIGHT:
					{
						cout << "You can fight" << endl;
						break;
					}
					case FALSE_SIZE_STEP:
					{
						cout << "False step" << endl;
						break;
					}
					case YOU_CANNOT_FIGHT:
					{
						cout << "You cannot fight" << endl;
						break;
					}
					
					case FALSE_STEP:
					{
						cout << "False step" << endl;
						break;	
					}
					case SUCH_MOVE_IS_IMPOSSIBLE:
					{
						cout << "Such move is impossible" << endl;
						break;
					}
					case YOU_MUST_FIGHT_THE_FIRST:
					{
						cout << "You must fight right now" << endl;
						break;
					}
					
					//couts for all errors
					default: 
					{
						cout << "Other error" << endl;
					}
				}
			}

			//delete lastCaptureSpreePosition;
			lastCaptureSpreePosition = nullptr;

			bool wasPieceCaptured = helper->performMove(board, nextMove, firstGamerTurn);

			if (wasPieceCaptured)
			{
				bool isOnCaptureSpree=helper->checkIfCanCapturePiece(board, *nextMove.to, firstGamerTurn);
				if (isOnCaptureSpree)
				{
					
					lastCaptureSpreePosition = new Position(*nextMove.to);

				}
			}
			if (lastCaptureSpreePosition == nullptr)
			{
				firstGamerTurn = !firstGamerTurn;
			}
			

		}

	}


};




