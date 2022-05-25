#include <iostream>
#include "Board.cpp"
#include "time.h"
using namespace std;

Position** getCurrentPositionsForPlayer(CheckersBoard* board, bool isFirstPlayer)
{
	GameCell targetCell = isFirstPlayer ? WHITE_CHECKER : BLACK_CHECKER;
	Position** playerPositions = new Position * [12] {nullptr};//can be bug

	int k = 0;
	for (int i = 0; i < board->BOARD_SIZE; i++)
	{
		for (int j = 0; j < board->BOARD_SIZE; j++)
		{
			if (board->getElementOwner(i, j) == targetCell)
			{
				playerPositions[k] = new Position(i, j);
				if (playerPositions[k] != nullptr) 
				{
					//cout << i << "  " << j << endl;
				}
				k++;
			}
		}
	}
	return playerPositions;
}

int getNumberOfPositions(Position** array)
{
	for (int i = 0; i < 12; i++)
	{
		if (array[i] == nullptr)
		{
			return i;
		}
	}
	return 12;
}

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
		//if (position.x == 2 && position.y == 1) 
		//{
		//	cout << "\n" << board->getElementOwner(position.x + 1, position.y + 1) << endl;
		//}

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

Position* getPossibleCaptureMove(Position** playerPositions, CheckersBoard* board, bool isFirstPlayerMove)
{
	for (int i = 0; i < getNumberOfPositions(playerPositions); i++)
	{
		if (checkIfCanCapturePiece(board, *playerPositions[i], isFirstPlayerMove))
		{
			return playerPositions[i];
		}
	}
	//_getch();
	return nullptr;
}

Position* whereShouldFightForBlack(Position position, CheckersBoard* board)//works
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
				futurePosition = new Position(position.x - 2, position.y - 2);
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


int main() {
	srand(time(NULL));
	CheckersBoard* board = new CheckersBoard();
	board->fillTestBoard();
	board->printerOfBoard();
	//getCurrentPositionsForPlayer(board,false);
	
	Position* from = new Position(3, 2);
	//Position *destination= getPossibleCaptureMove(getCurrentPositionsForPlayer(board, true), board, true);
	//getCurrentPositionsForPlayer(board,false);
	Position* destination = whereShouldFightForBlack(*from, board);
	if (destination != nullptr)
	{
		cout << destination->x << "   " << destination->y << endl;
	}
	

	delete board;
	delete from;
	delete destination;


}