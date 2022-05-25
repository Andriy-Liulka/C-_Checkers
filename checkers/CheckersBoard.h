#pragma once
#include <iostream>
using namespace std;

enum GameCell { EMPTY = 0, WHITE_CHECKER = 1, BLACK_CHECKER = 2, WHITE_DAMKA = 3, BLACK_DAMKA=4,INVALID=5};


class Coordinats
{
public:
	int currentPositionI = 0;
	int currentPositionJ = 0;
	Coordinats(int i, int j)
	{
		currentPositionI = i;
		currentPositionJ = j;
	}
};


class CheckersBoard
{
public:
	GameCell **gameBoard=nullptr;
	const int BOARD_SIZE = 8;

	void fillStandartBoard()
	{
		int** gameBoard = new int* [BOARD_SIZE];
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			gameBoard[i] = new int[BOARD_SIZE];
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

	inline void setElement(int index1,int index2, currentCell value)
	{

		gameBoard[index1][index2] = value;
	}

	inline GameCell getElement(int index1, int index2)
	{
		if (index1 < 0|| index2<0|| index1>=BOARD_SIZE|| index2>=BOARD_SIZE) 
		{
			return INVALID;
		}
		return gameBoard[index1][index2];

	}
	//enum currentCell { EMPTY = 0, OUR_CHECKER = 1, COMPUTERS_CHECKER = 2, OUR_DAMKA = 3, COMPUTERS_DAMKA=4,INVALID=5};
	inline GameCell getElementOwner(int index1, int index2) 
	{
		GameCell element = getElement(index1,index2);
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
				return BLACK_CHECKER;
			}
			default:
			{
				return 	element;
			}

		}
	}

};