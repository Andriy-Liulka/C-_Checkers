#include "Move.h"
#include "CheckerBoard.h"
#include "Position.h"
//#include "MoveValidator.h"
#pragma once



enum PositionValidationMode {CURRENT_PIECE=0,EMPTY_SPACE=1};
enum WinnerCheckResult {GAME_IN_PROGRESS,FIRST_PLAYER_WIN, SECOND_PLAYER_WIN};
class CheckerBoardHelper
{
public:
	bool checkIfPositionPossible(CheckersBoard* board, Position* position, bool isFirstPlyerTurn, PositionValidationMode mode)
	{
		if (position->x > board->BOARD_SIZE - 1 || position->x < 0 || position->y>board->BOARD_SIZE - 1 || position->y < 0)
		{
			return false;
		}
		GameCell cell = board->getElementOwner(position->x, position->y);
		if (cell == INVALID)
		{
			return false;
		}
		if (mode == CURRENT_PIECE)
		{
			return cell == (isFirstPlyerTurn ? WHITE_CHECKER : BLACK_CHECKER);//might me fault-
			//return cell == (isFirstPlyerTurn ? BLACK_CHECKER : WHITE_CHECKER);
		}
		if (mode == EMPTY_SPACE)
		{
			//bool checkIfCanCapturePiece(CheckersBoard * board, Position position, bool isFirstPlayerTurn)
			return (cell == EMPTY);/*&& board->isGameSpace(position) || ((cell== EMPTY)&&checkIfCanCapturePiece(board,*position, isFirstPlyerTurn)) && board->isGameSpace(position)*///to do
		}
		return false;


	}


	//MoveValidationResult checkIfMovePossible(CheckersBoard* board, Move move, bool isFirstPlayerTurn, Position* captureSpreePosition)
	//chackIfMovePossible(CheckersBoard* board, CheckerBoardHelper* helper, Move move, bool isFirstPlayerTurn, Position* captureSpreePosition);
	//{//п≥друбати MoveValidator.h

	//	//чи ти можеш ходити з поточноњ позиц≥њ
	//	//вс≥ остальн≥ правила
	//	//€кшо х≥д можливий ,€кшо н≥кого не побЇш але можеш подиби ти мусиш бити
	//	//написати метод €кий  буде перев≥р€ти €к ти будеш ходити 
	//	//rewrite
	//	GameCell from = board->getElement(move.from->x, move.from->y);
	//	GameCell to = board->getElement(move.to->x, move.to->y);
	//	GameCell fromOwner = board->getElementOwner(move.from->x, move.from->y);
	//	GameCell toOwner = board->getElementOwner(move.to->x, move.to->y);

	//	bool ifCheckerCanCapturePiece = checkIfCanCapturePiece(board, *(move.from), isFirstPlayerTurn);
	//	
	//	if(move.from== )//пор≥вн€нн€ чи move from дор≥внюЇ captureSpreePosition if captureSpreePosition
	//		//!=nullptr €кшо вона не виконуЇтьс€ ,вертаЇ помилку такою €кою ти побив в попередньому кроц≥ тою самою ти маЇш зара рухатись 
	//	if (isFirstPlayerTurn)
	//	{
	//		
	//		if (fromOwner != WHITE_CHECKER)
	//		{
	//			return PLACE_WITHOUT_YOUR_CHECKER;
	//		}
	//		else if (to!=EMPTY)
	//		{
	//			return INVALID_DESTINATION;
	//		}
	//		else if (!ifCheckerCanCapturePiece)
	//		{
	//			return ;//зробити перев≥рку чи ти можеш походити буде if €кий буде перев≥р€ти чи можеш походити взагал≥ €кшо можеш то 
	//			//Okey €кшо нЇ то INVALID маЇ бути перев≥рка на дамку 
	//		}
	//		else 
	//		{
	//			//подивитись чи довжина кроку правильна ,подивитись чи правильний напр€м враховуючи дамку ,
	//			//подивитись чи захопив ти чорну ф≥шку ,to owner маЇ бути чорний
	bool isDistinationForFight(Move move)
	{
		if (abs(move.from->x - move.to->x) == 2 || abs(move.from->y - move.to->y) == 2)
		{
			return true;
		}
		return false;
	}

	bool performMove(CheckersBoard* board, Move move, bool isFirstPlayer)//works
	{
		//зробити крок ≥ зберегти результуючий стан в борд ≥ вернути побив чи нЇ (тру або фолс)
		GameCell element = board->getElement(move.from->x, move.from->y);
		//зробити перев≥рку €кщо елемент це ф≥шка ≥ ти дос€г правильного к≥нц€ карти то перетворити цей елемент в дамку
		board->setElement(move.to->x, move.to->y, element);
		
		board->setElement(move.from->x, move.from->y, EMPTY);
		if (board->getElementDamkaOrChecker(move.to->x, move.to->y) == CHECKER)
		{
			if (isFirstPlayer && move.to->x == 0)
			{
				board->setElement(move.to->x, move.to->y, WHITE_DAMKA);
			}
			else if (!isFirstPlayer && move.to->x == 7)
			{
				board->setElement(move.to->x, move.to->y, BLACK_DAMKA);
			}
		}
		if (isDistinationForFight(move))
		{
			board->setElement(move.from->x + ((move.to->x - move.from->x) / 2), move.from->y + ((move.to->y - move.from->y) / 2), EMPTY);
			return true;
		}
		return false;
	}

	//this method check weither some checker in corner from current position is enermy and next place is empty  
	bool checkIfCanCapturePiece(CheckersBoard* board, Position position, bool isFirstPlayerTurn)
	{
		//написати чи можеш ти з цього м≥сц€ бити чи нЇ ,€кшо дамка то можеш бити назада в другому випадку нЇ
		//GameCell targetCell= isFirstPlayerTurn? WHITE_CHECKER: BLACK_CHECKER;

		if (isFirstPlayerTurn)
		{
			if (board->getElementOwner(position.x - 1, position.y - 1) == BLACK_CHECKER && board->getElementOwner(position.x - 2, position.y - 2) == EMPTY)
			{
				return true;
			}
			else if (board->getElementOwner(position.x - 1, position.y + 1) == BLACK_CHECKER && board->getElementOwner(position.x - 2, position.y + 2) == EMPTY)
			{
				return true;
			}
			if (board->getElement(position.x, position.y) == WHITE_DAMKA)
			{
				if (board->getElementOwner(position.x + 1, position.y + 1) == BLACK_CHECKER && board->getElementOwner(position.x + 2, position.y + 2) == EMPTY)
				{
					return true;//написати метод дл€ пор≥вн€нн€
				}
				else if (board->getElementOwner(position.x + 1, position.y - 1) == BLACK_CHECKER && board->getElementOwner(position.x + 2, position.y - 2) == EMPTY)
				{
					return true;
				}
			}
			return false;
		}
		else
		{
			if (board->getElementOwner(position.x + 1, position.y + 1) == WHITE_CHECKER && board->getElementOwner(position.x + 2, position.y + 2) == EMPTY)
			{
				return true;
			}
			else if (board->getElementOwner(position.x + 1, position.y - 1) == WHITE_CHECKER && board->getElementOwner(position.x + 2, position.y - 2) == EMPTY)
			{
				return true;
			}

			if (board->getElement(position.x, position.y) == BLACK_DAMKA)
			{
				if (board->getElementOwner(position.x - 1, position.y - 1) == WHITE_CHECKER && board->getElementOwner(position.x - 2, position.y - 2) == EMPTY)
				{
					return true;
				}
				else if (board->getElementOwner(position.x - 1, position.y + 1) == WHITE_CHECKER && board->getElementOwner(position.x - 2, position.y + 2) == EMPTY)
				{
					return true;
				}
			}
		}
		return false;
		//вертаЇ мусиш бити чи нЇ
	}

	Position* returnCurrentMove(int x,int y) 
	{
		return new Position(x, y);
	}

	Position* getPossibleCapturePosition(CheckersBoard* board, Position position, bool isFirstPlayerTurn)
	{
		//написати чи можеш ти з цього м≥сц€ бити чи нЇ ,€кшо дамка то можеш бити назада в другому випадку нЇ
		//GameCell targetCell= isFirstPlayerTurn? WHITE_CHECKER: BLACK_CHECKER;
		if (isFirstPlayerTurn)
		{
			if (board->getElementOwner(position.x - 1, position.y - 1) == BLACK_CHECKER && board->getElementOwner(position.x - 2, position.y - 2) == EMPTY)
			{
				return returnCurrentMove(position.x - 2, position.y - 2);//make to the end
			}
			else if (board->getElementOwner(position.x - 1, position.y + 1) == BLACK_CHECKER && board->getElementOwner(position.x - 2, position.y + 2) == EMPTY)
			{
				return returnCurrentMove(position.x - 2, position.y + 2);
			}
			if (board->getElement(position.x, position.y) == WHITE_DAMKA)
			{
				if (board->getElementOwner(position.x + 1, position.y + 1) == BLACK_CHECKER && board->getElementOwner(position.x + 2, position.y + 2) == EMPTY)
				{
					return returnCurrentMove(position.x + 2, position.y + 2);
				}
				else if (board->getElementOwner(position.x + 1, position.y - 1) == BLACK_CHECKER && board->getElementOwner(position.x + 2, position.y - 2) == EMPTY)
				{
					return returnCurrentMove(position.x + 2, position.y - 2);
				}
			}
			return nullptr;
		}
		else
		{
			if (board->getElementOwner(position.x + 1, position.y + 1) == WHITE_CHECKER && board->getElementOwner(position.x + 2, position.y + 2) == EMPTY)
			{
				return returnCurrentMove(position.x + 2, position.y + 2);
			}
			else if (board->getElementOwner(position.x + 1, position.y - 1) == WHITE_CHECKER && board->getElementOwner(position.x + 2, position.y - 2) == EMPTY)
			{
				return returnCurrentMove(position.x + 2, position.y - 2);
			}

			if (board->getElement(position.x, position.y) == BLACK_DAMKA)
			{
				if (board->getElementOwner(position.x - 1, position.y - 1) == WHITE_CHECKER && board->getElementOwner(position.x - 2, position.y - 2) == EMPTY)
				{
					return returnCurrentMove(position.x - 2, position.y - 2);
				}
				else if (board->getElementOwner(position.x - 1, position.y + 1) == WHITE_CHECKER && board->getElementOwner(position.x - 2, position.y + 2) == EMPTY)
				{
					return returnCurrentMove(position.x - 2, position.y + 2);
				}
			}
		}
		return nullptr;
		//вертаЇ мусиш бити чи нЇ
	}

	bool checkIfCanMove(CheckersBoard* board, Position currentChecker, bool isFirstPlayerTurn)
	{
		GameCell checkerElement = board->getElement(currentChecker.x, currentChecker.y);
		if (checkerElement == INVALID)
		{
			return false;
		}

		if (isFirstPlayerTurn|| checkerElement==BLACK_DAMKA)
		{
			if (board->getElement(currentChecker.x - 1, currentChecker.y - 1) == EMPTY)
			{
				return true;
			}
			else if (board->getElement(currentChecker.x - 1, currentChecker.y + 1) == EMPTY)
			{
				return true;
			}
		}
		if(!isFirstPlayerTurn || checkerElement == WHITE_DAMKA)
		{
			if (board->getElement(currentChecker.x + 1, currentChecker.y - 1) == EMPTY)
			{
				return true;
			}
			else if (board->getElement(currentChecker.x + 1, currentChecker.y + 1) == EMPTY)
			{
				return true;
			}
		}
		return false;
	}

	bool checkIfPlayerCanCaptureOrMove(CheckersBoard* board,bool isFirstPlayerTurn)
	{
		GameCell checker = isFirstPlayerTurn ? WHITE_CHECKER : BLACK_CHECKER;
		for (int i = 0; i < board->BOARD_SIZE; i++)
		{
			for (int j = 0; j < board->BOARD_SIZE; j++)
			{
				if (board->getElementOwner(i, j) == checker)
				{
					Position* currentChecker = new Position(i, j);
					if (checkIfCanCapturePiece(board, *currentChecker, isFirstPlayerTurn))
					{
						return true;
					}
					if (checkIfCanMove(board, *currentChecker, isFirstPlayerTurn))//перев≥р€Ї чи можеш опше в апр≥ор≥ ходити в 4 сторони 
					{
						return true;
					}
				}
			}
		}
		return false;

	}

	WinnerCheckResult isGameFinished(CheckersBoard* board, bool isFirstPlayerTurn)
	{
		bool  isPlayerInGame= false;
		GameCell targetCell= isFirstPlayerTurn?WHITE_CHECKER:BLACK_CHECKER;
		WinnerCheckResult potentialWinner= isFirstPlayerTurn ? SECOND_PLAYER_WIN : FIRST_PLAYER_WIN;

		for (int i = 0; i < board->BOARD_SIZE; i++)
		{
			for (int j = 0; j < board->BOARD_SIZE; j++)
			{
				if (board->getElementOwner(i, j) == targetCell)
				{
					isPlayerInGame = true;
				}

			}
		}
		if (!isPlayerInGame)
		{
			return potentialWinner;
		}

		if (checkIfPlayerCanCaptureOrMove(board, isFirstPlayerTurn))
		{
			return GAME_IN_PROGRESS;
		}
		return potentialWinner;
	}

};