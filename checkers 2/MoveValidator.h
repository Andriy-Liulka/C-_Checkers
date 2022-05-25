#include "CheckerBoard.h"
#include <iostream>
//#include <Math.h>
#include "Move.h"
#include "CheckerBoardHelper.h"
#pragma once

enum MoveValidationResult { VALID = 0, CURRENT_POSITION_SHOULD_BE_THE_SAME_AS_LAST_FROM_LAST_FIGHT, 
	PLACE_WITHOUT_YOUR_CHECKER, INVALID_DISTINATION,YOU_CANNOT_MOVE_WITH_CURRENT_CHECKER, FALSE_SIZE_STEP,YOU_CAN_FIGHT, YOU_CANNOT_FIGHT, FALSE_STEP, SUCH_MOVE_IS_IMPOSSIBLE, YOU_MUST_FIGHT_THE_FIRST};//all errors

class MoveValidator
{
	static bool canSimpleCheckerMoveToCurrentPosition(CheckersBoard* board, Position currentPosition, bool isFirstPlayerTurn)
	{
		if (isFirstPlayerTurn) 
		{
			if (board->getElement(currentPosition.x - 1, currentPosition.y - 1) == EMPTY)
			{
				return true;
			}
			else if (board->getElement(currentPosition.x - 1, currentPosition.y + 1) == EMPTY)
			{
				return true;
			}
		}
		else if(!isFirstPlayerTurn)
		{
			if (board->getElement(currentPosition.x + 1, currentPosition.y - 1) == EMPTY)
			{
				return true;
			}
			else if (board->getElement(currentPosition.x + 1, currentPosition.y + 1) == EMPTY)
			{
				return true;
			}
		}
		return false;
	}

	static bool canSimpleCheckerGoToFuturePositio(CheckersBoard* board, Move move, bool isFirstPlayerTurn)
	{
		int fromX = move.from->x;
		int fromY = move.from->y;
		int toX= move.to->x;
		int toY = move.to->y;
		CheckerType currentPiece = board->getElementDamkaOrChecker(fromX, fromY);
		if (isFirstPlayerTurn )
		{
			if (currentPiece == CHECKER|| currentPiece == DAMKA)
			{
				if ((toX == fromX - 1 && toY == fromY - 1) || (toX == fromX - 1 && toY == fromY + 1)) 
				{
					return true;
				}
			}
			if (currentPiece == DAMKA) 
			{
				if ((toX == fromX + 1 && toY == fromY - 1) || (toX == fromX + 1 && toY == fromY + 1))
				{
					return true;
				}
			}
		}
		else if(!isFirstPlayerTurn)
		{
			if (currentPiece == CHECKER || currentPiece == DAMKA)
			{

				if ((toX == fromX + 1 && toY == fromY - 1) || (toX == fromX + 1 && toY == fromY + 1))
				{
					return true;
				}
			}
			if (currentPiece == DAMKA)
			{
				if ((toX == fromX - 1 && toY == fromY - 1) || (toX == fromX - 1 && toY == fromY + 1))
				{
					return true;
				}
			}





		}
		return false;
	}

	static bool checkWhetherCanFight(CheckersBoard* board, CheckerBoardHelper* helper, Move move, bool isFirstPlayerTurn)
	{
		if (!helper->checkIfCanCapturePiece(board, *move.from, isFirstPlayerTurn))
		{
			return false;
		}
		if (abs(move.from->x - move.to->x) != 2 || abs(move.from->y - move.to->y) != 2)
		{
			return false;
		}

		if (isFirstPlayerTurn)
		{
			if (board->getElementOwner(move.to->x, move.to->y) == EMPTY && board->getElementOwner(move.to->x / 2, move.to->y / 2) == BLACK_CHECKER)
			{
				return true;
			}
		}
		else
		{
			if (board->getElementOwner(move.to->x, move.to->y) == EMPTY && board->getElementOwner(move.to->x / 2, move.to->y / 2) == WHITE_CHECKER)
			{
				return true;
			}
		}
	}

public:
	static MoveValidationResult chackIfMovePossible(CheckersBoard* board, CheckerBoardHelper* helper, Move move, bool isFirstPlayerTurn, Position* captureSpreePosition)
	{
		GameCell from = board->getElement(move.from->x, move.from->y);
		GameCell to = board->getElement(move.to->x, move.to->y);
		GameCell fromOwner = board->getElementOwner(move.from->x, move.from->y);
		GameCell toOwner = board->getElementOwner(move.to->x, move.to->y);

		bool ifCheckerCanCapturePiece = helper->checkIfCanCapturePiece(board, *(move.from), isFirstPlayerTurn);
		if (captureSpreePosition != nullptr)
		{
			if (move.from->x == captureSpreePosition->x && move.from->y == captureSpreePosition->y)
			{
			}
			else 
			{
				return CURRENT_POSITION_SHOULD_BE_THE_SAME_AS_LAST_FROM_LAST_FIGHT;
			}
		}

		if (!helper->checkIfCanCapturePiece(board, *move.from, isFirstPlayerTurn))
		{
			if (abs(move.from->x- move.to->x)!=1|| abs(move.from->y - move.to->y) != 1) 
			{
				return FALSE_STEP;
			}
		}		

		if (isFirstPlayerTurn&&fromOwner!=WHITE_CHECKER)
		{
			return PLACE_WITHOUT_YOUR_CHECKER;
		}
		else if (!isFirstPlayerTurn && fromOwner != BLACK_CHECKER)
		{
			return PLACE_WITHOUT_YOUR_CHECKER;
		}
		else if (to!=EMPTY)
		{
			return INVALID_DISTINATION;

		}
		else if (!ifCheckerCanCapturePiece)
		{

			if (!canSimpleCheckerGoToFuturePositio(board, move, isFirstPlayerTurn))
			{
				return SUCH_MOVE_IS_IMPOSSIBLE;
			}
			/*std::cout << board->getElementDamkaOrChecker(move.from->x, move.from->y) << std::endl;
			std::cout << helper->checkIfCanMove(board, *move.from, isFirstPlayerTurn) << std::endl;*/
			if (canSimpleCheckerMoveToCurrentPosition(board, *move.from, isFirstPlayerTurn))
			{
			}
			else if (board->getElementDamkaOrChecker(move.from->x, move.from->y) == DAMKA && helper->checkIfCanMove(board, *move.from, isFirstPlayerTurn) )
			{
			}
			//else if(board->getElementDamkaOrChecker(move.from->x, move.from->y) == DAMKA &&)
			else
			{
				return YOU_CANNOT_MOVE_WITH_CURRENT_CHECKER;
			}
		}
		else
		{
			if (ifCheckerCanCapturePiece) 
			{
				if (abs(move.from->x - move.to->x)!=2 && abs(move.from->y - move.to->y)!=2)
				{
					return YOU_MUST_FIGHT_THE_FIRST;
				}
			}
			if (!ifCheckerCanCapturePiece)
			{
				return YOU_CANNOT_FIGHT;
			}
		}
		return VALID;
	}
};

