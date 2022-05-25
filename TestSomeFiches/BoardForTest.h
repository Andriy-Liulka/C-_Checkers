#pragma once
#include "Position.h"
#include <iostream>
using namespace std;

enum GameCell { EMPTY = 0, WHITE_CHECKER = 1, BLACK_CHECKER = 2, WHITE_DAMKA = 3, BLACK_DAMKA = 4, INVALID = 5, CHECKER = 6, DAMKA = 7 };


class CheckersBoard
{
private:
	GameCell** gameBoard = nullptr;
public:
	const int BOARD_SIZE = 8;

	void fillStandartBoard()
	{
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			delete[]gameBoard;
		}
		delete[]gameBoard;

		gameBoard = new GameCell * [BOARD_SIZE];
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			gameBoard[i] = new GameCell[BOARD_SIZE];
		}
		gameBoard[0][1] = BLACK_CHECKER;//checkers for computer
		gameBoard[0][3] = BLACK_CHECKER;
		gameBoard[0][5] = BLACK_CHECKER;
		gameBoard[0][7] = BLACK_CHECKER;

		gameBoard[1][0] = BLACK_CHECKER;
		gameBoard[1][2] = BLACK_CHECKER;
		gameBoard[1][4] = BLACK_CHECKER;
		gameBoard[1][6] = BLACK_CHECKER;

		gameBoard[2][1] = BLACK_CHECKER;
		gameBoard[2][3] = BLACK_CHECKER;
		gameBoard[2][5] = BLACK_CHECKER;
		gameBoard[2][7] = BLACK_CHECKER;


		gameBoard[5][0] = WHITE_CHECKER; //checkers for myself
		gameBoard[5][2] = WHITE_CHECKER;
		gameBoard[5][4] = WHITE_CHECKER;
		gameBoard[5][6] = WHITE_CHECKER;

		gameBoard[6][1] = WHITE_CHECKER;
		gameBoard[6][3] = WHITE_CHECKER;
		gameBoard[6][5] = WHITE_CHECKER;
		gameBoard[6][7] = WHITE_CHECKER;

		gameBoard[7][0] = WHITE_CHECKER;
		gameBoard[7][2] = WHITE_CHECKER;
		gameBoard[7][4] = WHITE_CHECKER;
		gameBoard[7][6] = WHITE_CHECKER;

		for (int i = 0; i < BOARD_SIZE; i++)//filling everithing with empty
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				if (gameBoard[i][j] != WHITE_CHECKER && gameBoard[i][j] != BLACK_CHECKER)
				{
					gameBoard[i][j] = EMPTY;
				}
			}
		}
	}

	void printerOfBoard()
	{
		//cout << "---------------------" << endl;
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			cout << BOARD_SIZE - i;
			cout << '|';
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				//cout << '|';
				switch (gameBoard[i][j])
				{
				case EMPTY:
				{
					cout << "_";
					break;
				}
				case WHITE_CHECKER:
				{
					cout << "o";
					break;
				}
				case BLACK_CHECKER:
				{
					cout << "*";
					break;
				}
				case WHITE_DAMKA:
				{
					cout << "D";
					break;
				}
				case BLACK_DAMKA:
				{
					cout << "B";
					break;
				}
				}
				cout << '|';
			}
			cout << endl;
		}

		//cout << "---------------------" << endl;
		cout << "  A B C D E F G H" << endl;

	}

	inline void setElement(int index1, int index2, GameCell value)
	{

		gameBoard[index1][index2] = value;
	}

	inline GameCell getElement(int index1, int index2)
	{
		if (index1 < 0 || index2 < 0 || index1 >= BOARD_SIZE || index2 >= BOARD_SIZE)
		{
			return INVALID;
		}
		return gameBoard[index1][index2];

	}

	inline GameCell getElementOwner(int index1, int index2)
	{
		GameCell element = getElement(index1, index2);
		switch (element)
		{
		case WHITE_CHECKER:
		case WHITE_DAMKA:
		{
			return WHITE_CHECKER;
		}
		case BLACK_CHECKER:
		case BLACK_DAMKA:
		{
			return DAMKA;
		}
		default:
		{
			return 	element;
		}

		}
	}

	inline GameCell getElementDamkaOrChecker(int index1, int index2)
	{
		GameCell element = getElement(index1, index2);
		switch (element)
		{
		case WHITE_CHECKER:
		case BLACK_CHECKER:
		{
			return CHECKER;
		}
		case WHITE_DAMKA:
		case BLACK_DAMKA:
		{
			return DAMKA;
		}
		default:
		{
			return 	element;
		}

		}
	}

	inline void reNullPosition(Position* position)
	{
		position->x = 0;
		position->y = 0;
	}

	bool isGameSpace(Position* position)
	{
		//write weither current position on black place
		if (position->x == 0 && position->y == 7) //7
		{
			return true;
		}
		else if (position->x == 2 && position->y == 7)
		{
			return true;
		}
		else if (position->x == 4 && position->y == 7)
		{
			return true;
		}
		else if (position->x == 6 && position->y == 7)
		{
			return true;
		}

		else if (position->x == 1 && position->y == 6)//6
		{
			return true;
		}
		else if (position->x == 3 && position->y == 6)
		{
			return true;
		}
		else if (position->x == 5 && position->y == 6)
		{
			return true;
		}
		else if (position->x == 7 && position->y == 6)
		{
			return true;
		}

		else if (position->x == 0 && position->y == 5)//5
		{
			return true;
		}
		else if (position->x == 2 && position->y == 5)
		{
			return true;
		}
		else if (position->x == 4 && position->y == 5)
		{
			return true;
		}
		else if (position->x == 6 && position->y == 5)
		{
			return true;
		}

		else if (position->x == 1 && position->y == 4)//4
		{
			return true;
		}
		else if (position->x == 3 && position->y == 4)
		{
			return true;
		}
		else if (position->x == 5 && position->y == 4)
		{
			return true;
		}
		else if (position->x == 7 && position->y == 4)
		{
			return true;
		}

		else if (position->x == 0 && position->y == 3)//3
		{
			return true;
		}
		else if (position->x == 2 && position->y == 3)
		{
			return true;
		}
		else if (position->x == 4 && position->y == 3)
		{
			return true;
		}
		else if (position->x == 6 && position->y == 3)
		{
			return true;
		}

		else if (position->x == 1 && position->y == 2)//2
		{
			return true;
		}
		else if (position->x == 3 && position->y == 2)
		{
			return true;
		}
		else if (position->x == 5 && position->y == 2)
		{
			return true;
		}
		else if (position->x == 7 && position->y == 2)
		{
			return true;
		}

		else if (position->x == 0 && position->y == 1)//1
		{
			return true;
		}
		else if (position->x == 2 && position->y == 1)
		{
			return true;
		}
		else if (position->x == 4 && position->y == 1)
		{
			return true;
		}
		else if (position->x == 6 && position->y == 1)
		{
			return true;
		}

		else if (position->x == 1 && position->y == 0)//0
		{
			return true;
		}
		else if (position->x == 3 && position->y == 0)
		{
			return true;
		}
		else if (position->x == 5 && position->y == 0)
		{
			return true;
		}
		else if (position->x == 7 && position->y == 0)
		{
			return true;
		}
		else
		{
			return false;
		}


	}


}; 