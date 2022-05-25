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
	//{//�������� MoveValidator.h

	//	//�� �� ����� ������ � ������� �������
	//	//�� ������� �������
	//	//���� ��� �������� ,���� ����� �� ���� ��� ����� ������ �� ����� ����
	//	//�������� ����� ����  ���� ��������� �� �� ����� ������ 
	//	//rewrite
	//	GameCell from = board->getElement(move.from->x, move.from->y);
	//	GameCell to = board->getElement(move.to->x, move.to->y);
	//	GameCell fromOwner = board->getElementOwner(move.from->x, move.from->y);
	//	GameCell toOwner = board->getElementOwner(move.to->x, move.to->y);

	//	bool ifCheckerCanCapturePiece = checkIfCanCapturePiece(board, *(move.from), isFirstPlayerTurn);
	//	
	//	if(move.from== )//��������� �� move from ������� captureSpreePosition if captureSpreePosition
	//		//!=nullptr ���� ���� �� ���������� ,����� ������� ����� ���� �� ����� � ������������ ����� ��� ����� �� ��� ���� �������� 
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
	//			return ;//������� �������� �� �� ����� �������� ���� if ���� ���� ��������� �� ����� �������� ������ ���� ����� �� 
	//			//Okey ���� � �� INVALID �� ���� �������� �� ����� 
	//		}
	//		else 
	//		{
	//			//���������� �� ������� ����� ��������� ,���������� �� ���������� ������ ���������� ����� ,
	//			//���������� �� ������� �� ����� ����� ,to owner �� ���� ������
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
		//������� ���� � �������� ������������ ���� � ���� � ������� ����� �� � (��� ��� ����)
		GameCell element = board->getElement(move.from->x, move.from->y);
		//������� �������� ���� ������� �� ����� � �� ����� ����������� ���� ����� �� ����������� ��� ������� � �����
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
		//�������� �� ����� �� � ����� ���� ���� �� � ,���� ����� �� ����� ���� ������ � ������� ������� �
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
					return true;//�������� ����� ��� ���������
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
		//����� ����� ���� �� �
	}

	Position* returnCurrentMove(int x,int y) 
	{
		return new Position(x, y);
	}

	Position* getPossibleCapturePosition(CheckersBoard* board, Position position, bool isFirstPlayerTurn)
	{
		//�������� �� ����� �� � ����� ���� ���� �� � ,���� ����� �� ����� ���� ������ � ������� ������� �
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
		//����� ����� ���� �� �
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
					if (checkIfCanMove(board, *currentChecker, isFirstPlayerTurn))//�������� �� ����� ���� � ����� ������ � 4 ������� 
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