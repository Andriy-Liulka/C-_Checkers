#pragma once
#include "CheckersBoard.h"
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <time.h>
using namespace std;




class CheckersGameController //class for printing of board
{
public:
	int currentPositon1 = 0;
	int currentPositon2 = 0;

	int futurePosition1 = 0;
	int futurePosition2 = 0;

	//void game()


	bool canThisCheckerFightNow(bool isThisCheckerOur, int** boardGame)
	{
		GameCell firstRevision;
		GameCell secondRevision;
		if (isThisCheckerOur)
		{
			firstRevision = BLACK_CHECKER;
			secondRevision = BLACK_DAMKA;
		}
		else
		{
			firstRevision = WHITE_CHECKER;
			secondRevision = WHITE_DAMKA;
		}

		if (boardGame[currentPositon1][currentPositon2] == WHITE_CHECKER)
		{
			if ((boardGame[currentPositon1 - 1][currentPositon2 - 1] == firstRevision || boardGame[currentPositon1 - 1][currentPositon2 - 1] == secondRevision) && boardGame[currentPositon1 - 2][currentPositon2 - 2] == EMPTY)
			{
				return true;
			}
			else if ((boardGame[currentPositon1 - 1][currentPositon2 + 1] == firstRevision || boardGame[currentPositon1 - 1][currentPositon2 + 1] == secondRevision) && boardGame[currentPositon1 - 2][currentPositon2 + 2] == EMPTY)
			{
				return true;
			}
			else if ((boardGame[currentPositon1 + 1][currentPositon2 + 1] == firstRevision || boardGame[currentPositon1 + 1][currentPositon2 + 1] == secondRevision) && boardGame[currentPositon1 + 2][currentPositon2 + 2] == EMPTY)
			{
				return true;
			}
			else if ((boardGame[currentPositon1 + 1][currentPositon2 - 1] == firstRevision || boardGame[currentPositon1 + 1][currentPositon2 - 1] == secondRevision) && boardGame[currentPositon1 + 2][currentPositon2 - 2] == EMPTY)
			{
				return true;
			}


		}


		return false;
	}



	int convertFromCharToInt(char symbol)
	{
		return (symbol - 'A');

	}

	CheckersGameController(int currentPositon1, int currentPositon2, int futurePosition1, int futurePosition2)
	{
		this->currentPositon1 = currentPositon1;
		this->currentPositon2 = currentPositon2;
		this->futurePosition1 = futurePosition1;
		this->futurePosition2 = futurePosition2;

	}

	CheckersGameController(string nextStep,string currentPosition)
	{

		if (nextStep.size() > 2 || nextStep.size() < 0|| currentPosition.size() > 2 || currentPosition.size() < 0)
		{
			return;
		}
		char temp1 = nextStep.at(0);
		const char* pointerOnTemp1 = &temp1;
		futurePosition1 = abs(atoi(pointerOnTemp1)-8);
		char currentPosition2Temp1 = nextStep.at(1);
		futurePosition2 = convertFromCharToInt(currentPosition2Temp1);

		char temp2 = currentPosition.at(0);
		const char* pointerOnTemp2 = &temp2;
		currentPositon1 = abs(atoi(pointerOnTemp2) - 8);
		char currentPosition2Temp2 = currentPosition.at(1);
		currentPositon2 = convertFromCharToInt(currentPosition2Temp2);
		if (!checkCanYouGoThere())
		{
			return;
		}
	}

	bool checkCanYouGoThere()
	{
		if (futurePosition1 > 7 || futurePosition1 < 0)
		{
			cout << "Incorrect datas" << endl;
			return false;
		}
		if (futurePosition2 > 7 || futurePosition2 < 0)
		{
			cout << "Incorrect datas" << endl;
			return false;
		}
		return true;
	}

	bool gameDamka()//to do as a damka
	{

		if (currentPositon1 != futurePosition1 && currentPositon2 != futurePosition2 && (currentPositon1 + currentPositon2 == futurePosition1 + futurePosition2 || currentPositon1 - currentPositon2 == futurePosition1 - futurePosition2))
		{
			return true;
		}

		return false;

	}

	bool gameSimpleCkeckerForGamer()
	{
		if (futurePosition1 == currentPositon1 + 1 && futurePosition2 == currentPositon2 - 1)
		{
			return true;
		}
		else if (futurePosition1 == currentPositon1 - 1 && futurePosition2 == currentPositon2 + 1)
		{
			return true;
		}
		else if (futurePosition1 == currentPositon1 - 1 && futurePosition2 == currentPositon2 - 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool gameSimpleCkeckerForComputer()
	{
		if (futurePosition1 == currentPositon1 - 1 && futurePosition2 == currentPositon2 - 1)
		{
			return true;
		}
		else if (futurePosition1 == currentPositon1 + 1 && futurePosition2 == currentPositon2 - 1)
		{
			return true;
		}
		else if (futurePosition1 == currentPositon1 + 1 && futurePosition2 == currentPositon2 + 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	 



	int** functionOfCheckingWeitherOneCheckerFightAnother(bool isItOurSimpleChecker,int **boardGame,int heigth,int width) 
	{

		//COMPUTERS_CHECKER
		//COMPUTERS_DAMKA
		int positionWhereShouldPut1 = 0, positionWhereShouldPut2 = 0;
		
		if (isItOurSimpleChecker) 
		{
			for (int i = 0; i < heigth; i++) 
			{
				for (int j = 0; j < heigth; j++)
				{
					if (boardGame[i][j] == WHITE_CHECKER)
					{
						//bool isThisCheckerOur, int** boardGame, int currentPosition1, int currentPosition2
						
					
							while (true) 
							{
								if (!canThisCheckerFightNow(true, boardGame) )
								{
									break;
								}
								cout << "Enter position where you think should be fight" << endl;
								cin >> positionWhereShouldPut1;
								cin >> positionWhereShouldPut2;
								if ((boardGame[currentPositon1 - 1][currentPositon2 - 1] == BLACK_CHECKER || boardGame[currentPositon1 - 1][currentPositon2 - 1] == BLACK_DAMKA) && boardGame[currentPositon1 - 2][currentPositon2 - 2] == EMPTY)
								{
									if (currentPositon1 - 2!= positionWhereShouldPut1|| currentPositon2 - 2!= positionWhereShouldPut2)
									{
										cout << "Error";
										continue;
									}
									boardGame[currentPositon1 - 1][currentPositon2 - 1] = EMPTY;
									boardGame[currentPositon1 ][currentPositon2] = EMPTY;
									boardGame[currentPositon1 - 2][currentPositon2 - 2] = WHITE_CHECKER;
								}
								else if ((boardGame[currentPositon1 - 1][currentPositon2 + 1] == BLACK_CHECKER || boardGame[currentPositon1 - 1][currentPositon2 + 1] == BLACK_DAMKA) && boardGame[currentPositon1 - 2][currentPositon2 + 2] == EMPTY)
								{
									if (currentPositon1 - 2 != positionWhereShouldPut1 || currentPositon2 + 2 != positionWhereShouldPut2)
									{
										cout << "Error";
										continue;
									}
									boardGame[currentPositon1 - 1][currentPositon2 + 1] = EMPTY;
									boardGame[currentPositon1][currentPositon2] = EMPTY;
									boardGame[currentPositon1 + 2][currentPositon2 + 2] = WHITE_CHECKER;
								}
								else if ((boardGame[currentPositon1 + 1][currentPositon2 + 1] == BLACK_CHECKER || boardGame[currentPositon1 + 1][currentPositon2 + 1] == BLACK_DAMKA) && boardGame[currentPositon1 + 2][currentPositon2 + 2] == EMPTY)
								{
									if (currentPositon1 + 2 != positionWhereShouldPut1 || currentPositon2 + 2 != positionWhereShouldPut2)
									{
										cout << "Error";
										continue;
									}
									boardGame[currentPositon1 + 1][currentPositon2 + 1] = EMPTY;
									boardGame[currentPositon1][currentPositon2] = EMPTY;
									boardGame[currentPositon1 + 2][currentPositon2 + 2] = WHITE_CHECKER;
								}
								else if ((boardGame[currentPositon1 + 1][currentPositon2 - 1] == BLACK_CHECKER || boardGame[currentPositon1 + 1][currentPositon2 - 1] == BLACK_DAMKA) && boardGame[currentPositon1 + 2][currentPositon2 - 2] == EMPTY)
								{
									if (currentPositon1 + 2 != positionWhereShouldPut1 || currentPositon2 - 2 != positionWhereShouldPut2)
									{
										cout << "Error";
										continue;
									}
									boardGame[currentPositon1 + 1][currentPositon2 - 1] = EMPTY;
									boardGame[currentPositon1][currentPositon2] = EMPTY;
									boardGame[currentPositon1 + 2][currentPositon2 - 2] = WHITE_CHECKER;
								}
	
						}
					}
				}

			}


		}



		if (!isItOurSimpleChecker)
		{
			for (int i = 0; i < heigth; i++)
			{
				for (int j = 0; j < heigth; j++)
				{
					if (boardGame[i][j] == WHITE_CHECKER)
					{
						//bool isThisCheckerOur, int** boardGame, int currentPosition1, int currentPosition2
						while (true)
						{
							if (!canThisCheckerFightNow(false, boardGame))
							{
								break;
							}

							if ((boardGame[currentPositon1 - 1][currentPositon2 - 1] == WHITE_CHECKER || boardGame[currentPositon1 - 1][currentPositon2 - 1] == WHITE_DAMKA) && boardGame[currentPositon1 - 2][currentPositon2 - 2] == EMPTY)
							{
								boardGame[currentPositon1 - 1][currentPositon2 - 1] = EMPTY;
								boardGame[currentPositon1][currentPositon2] = EMPTY;
								boardGame[currentPositon1 - 2][currentPositon2 - 2] = BLACK_CHECKER;
							}
							else if ((boardGame[currentPositon1 - 1][currentPositon2 + 1] == WHITE_CHECKER || boardGame[currentPositon1 - 1][currentPositon2 + 1] == WHITE_DAMKA) && boardGame[currentPositon1 - 2][currentPositon2 + 2] == EMPTY)
							{
								boardGame[currentPositon1 - 1][currentPositon2 + 1] = EMPTY;
								boardGame[currentPositon1][currentPositon2] = EMPTY;
								boardGame[currentPositon1 + 2][currentPositon2 + 2] = BLACK_CHECKER;
							}
							else if ((boardGame[currentPositon1 + 1][currentPositon2 + 1] == WHITE_CHECKER || boardGame[currentPositon1 + 1][currentPositon2 + 1] == WHITE_DAMKA) && boardGame[currentPositon1 + 2][currentPositon2 + 2] == EMPTY)
							{
								boardGame[currentPositon1 + 1][currentPositon2 + 1] = EMPTY;
								boardGame[currentPositon1][currentPositon2] = EMPTY;
								boardGame[currentPositon1 + 2][currentPositon2 + 2] = BLACK_CHECKER;
							}
							else if ((boardGame[currentPositon1 + 1][currentPositon2 - 1] == WHITE_CHECKER || boardGame[currentPositon1 + 1][currentPositon2 - 1] == WHITE_DAMKA) && boardGame[currentPositon1 + 2][currentPositon2 - 2] == EMPTY)
							{
								boardGame[currentPositon1 + 1][currentPositon2 - 1] = EMPTY;
								boardGame[currentPositon1][currentPositon2] = EMPTY;
								boardGame[currentPositon1 + 2][currentPositon2 - 2] = BLACK_CHECKER;
							}

						}
					}





				}

			}


		}




		return boardGame;



	}

	bool canThisOutCheckerFightNow(bool isThisCheckerOur,int** boardGame, int currentPosition1, int currentPosition2)
	{
		GameCell firstRevision;
		GameCell secondRevision;
		if (isThisCheckerOur)
		{
			firstRevision = BLACK_CHECKER;
			secondRevision = BLACK_CHECKER;
		}
		else
		{
			firstRevision = WHITE_CHECKER;
			secondRevision = WHITE_DAMKA;
		}





		if (boardGame[currentPosition1][currentPosition2] == WHITE_CHECKER) 
		{
			if ((boardGame[currentPosition1 - 1][currentPosition2 - 1] == firstRevision || boardGame[currentPosition1 - 1][currentPosition2 - 1] == secondRevision) && boardGame[currentPosition1 - 2][currentPosition2 - 2] == EMPTY)
			{
				return true;
			}
			else if ((boardGame[currentPosition1 - 1][currentPosition2 + 1] == firstRevision || boardGame[currentPosition1 - 1][currentPosition2 + 1] == secondRevision) && boardGame[currentPosition1 - 2][currentPosition2 + 2] == EMPTY)
			{
				return true;
			}
			else if ((boardGame[currentPosition1 + 1][currentPosition2 + 1] == firstRevision || boardGame[currentPosition1 + 1][currentPosition2 + 1] == secondRevision) && boardGame[currentPosition1 + 2][currentPosition2 + 2] == EMPTY)
			{
				return true;
			}
			else if ((boardGame[currentPosition1 + 1][currentPosition2 - 1] == firstRevision || boardGame[currentPosition1 + 1][currentPosition2 - 1] == secondRevision) && boardGame[currentPosition1 + 2][currentPosition2 - 2] == EMPTY)
			{
				return true;
			}
			

		}


		return false;
	}

		



};


class Gamer
{
public:
	virtual int** Game(int** array, const int heigth, const int width, const char isSimpleChecker, int currentPosition1, int currentPosition2, int futurePosition1, int futurePosition2) { return 0; }

	//isSimpleChecker to know which is kind of checker ,'D'- means Damka and 'C'- maens simple checker 
};

class RealGamer :public Gamer 
{
public:
	virtual int** Game(int** array, const int heigth, const int width, const char isSimpleChecker, int currentPosition1, int currentPosition2, int futurePosition1, int futurePosition2)
	{
		CheckersGameController* objectForRevision = new CheckersGameController(currentPosition1, currentPosition2, futurePosition1, futurePosition2);
		array = objectForRevision->functionOfCheckingWeitherOneCheckerFightAnother(true, array, heigth, width);

		switch (isSimpleChecker)
		{
			case 'C':
			{
				if (!objectForRevision->gameSimpleCkeckerForGamer())
				{
					return nullptr;
				}
				break;
			}
			case 'D':
			{
				if (!objectForRevision->gameDamka())
				{
					return nullptr;
				}
				break;
			}
		}

		array[currentPosition1][currentPosition2] = EMPTY;
		if (array[futurePosition1][futurePosition2] != EMPTY)
		{
			return nullptr;
		}
		switch (isSimpleChecker)
		{
		case 'C':
		{
			array[futurePosition1][futurePosition2] = WHITE_CHECKER;
			break;
		}
		case 'D':
		{
			array[futurePosition1][futurePosition2] = WHITE_DAMKA;
			break;
		}

		}
		




		return array;
	}

};

class ComputerGamer :public Gamer
{
public:
	virtual int** Game(int** array, const int heigth, const int width, const char isSimpleChecker, int currentPosition1, int currentPosition2, int futurePosition1, int futurePosition2)
	{
		srand(time(nullptr));
		int quantityOfYourCheckers=0;
		for (int i = 0; i < heigth; i++)
		{
			for (int j= 0; j < heigth; j++)
			{
				if (array[i][j] == BLACK_CHECKER || array[i][j] == BLACK_DAMKA) 
				{
					quantityOfYourCheckers++;
				}
			}
		}
		int** currentPositionsOfCheckersOnBoard = new int* [quantityOfYourCheckers];
		for (int i = 0; i < quantityOfYourCheckers; i++)
		{
			currentPositionsOfCheckersOnBoard[i] = new int[2];
		}
		int k = 0;
		for (int i = 0; i < heigth; i++)
		{
			for (int j = 0; j < heigth; j++)
			{
				if (array[i][j] == BLACK_CHECKER || array[i][j] == BLACK_DAMKA)
				{
					currentPositionsOfCheckersOnBoard[k][0] = i;
					currentPositionsOfCheckersOnBoard[k][1] = j;
					k++;
				}
			}
		}
		//for (int i = 0; i < quantityOfYourCheckers; i++)
		//{
		//	for (int j = 0; j < 2; j++)
		//	{

		//			cout<<currentPositionsOfCheckersOnBoard[i][j]<<" ";
		//	}
		//	cout << endl;
		//}
		int choiceOfChecker=0;
		int indexForChecking1 = 0, indexForChecking2 = 0;
		int  indexForCkecking1Future = 0, indexForCkecking2Future = 0;
		CheckersGameController* objectForRevision=new CheckersGameController(0,0,0,0);
		while (true) 
		{
			choiceOfChecker =rand() % (quantityOfYourCheckers + 1);
			indexForChecking1 = currentPositionsOfCheckersOnBoard[choiceOfChecker][0];
			indexForChecking2 = currentPositionsOfCheckersOnBoard[choiceOfChecker][1];

			switch (rand() % 2 + 1)
			{
			case 1:
			{
				indexForCkecking1Future = indexForChecking1 + 1;
				indexForCkecking2Future = indexForChecking2 - 1;
				break;
			}
			case 2:
			{
				indexForCkecking1Future = indexForChecking1 + 1;
				indexForCkecking2Future = indexForChecking2 + 1;
				break;
			}
			}
				objectForRevision->currentPositon1= indexForChecking1;
				objectForRevision->currentPositon2 = indexForChecking2;
				objectForRevision->futurePosition1 = indexForCkecking1Future;
				objectForRevision->futurePosition2 = indexForCkecking2Future;

				
				if (array[objectForRevision->futurePosition1][objectForRevision->futurePosition2] != EMPTY)
				{
					continue;
				}
				switch (isSimpleChecker)
				{
					case 'C':
					{
						array[objectForRevision->futurePosition1][objectForRevision->futurePosition2] = BLACK_CHECKER;
						break;
					}
					case 'D':
					{
						array[objectForRevision->futurePosition1][objectForRevision->futurePosition2] = BLACK_DAMKA;
						break;
					}
				}

				
				if (array[objectForRevision->futurePosition1][objectForRevision->futurePosition2] == BLACK_CHECKER || array[objectForRevision->futurePosition1][objectForRevision->futurePosition2] == BLACK_DAMKA)
				{
					array[objectForRevision->currentPositon1][objectForRevision->currentPositon2] = EMPTY;

					currentPositionsOfCheckersOnBoard[choiceOfChecker][0] = objectForRevision->futurePosition1;
					currentPositionsOfCheckersOnBoard[choiceOfChecker][1] = objectForRevision->futurePosition2;
					/*for (int i = 0; i < quantityOfYourCheckers; i++)
					{
						delete[]currentPositionsOfCheckersOnBoard;
					}
					delete []currentPositionsOfCheckersOnBoard;*/
					break; 
				}
				//peredebug this function
				return array;
		}
		//cout << indexForChecking1 << "     " << indexForChecking2 << endl;
		//cout << endl;
		//cout << indexForCkecking1Future << "     " << indexForCkecking2Future << endl;








	}
};






