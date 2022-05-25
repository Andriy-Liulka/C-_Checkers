#include <iostream>
#include <conio.h>
#include "CheckersGameController.h"
#include "CheckersBoard.h";
using namespace std;

void errorDatas() 
{
	cout << "Incorrect datas...." << endl;
	_getch();
}


int main()
{


	CheckersBoard* pointerBoard=new CheckersBoard();
	pointerBoard->fillStandartBoard();
	//pointerBoard->printerOfBoard(board,heightOfBoard, widthOfBoard);
	string currentPosition = " ";
	string futurePosition = " ";
	int checkFight1 = 0, checkFight2 = 0;
	while (true)
	{
		system("cls");
		pointerBoard->printerOfBoard();
		CheckersGameController* gameController;
				//bool canThisOutCheckerFightNow(bool isThisCheckerOur, int** boardGame, int currentPosition1, int currentPosition2)
				//break;

		while (true)
		{
			/*for (int i = 0; i < heightOfBoard; i++)
			{

				for (int j = 0; j < widthOfBoard; j++)
				{
					if (board[i][j] == OUR_CHECKER)
					{
						if (gamePointerOfMoving->canThisOutCheckerFightNow(true, board, i, j))
						{
							cout << "No ,checker on position " << i << " " << j << " can fight" << endl;
						}
					}

				}

			}*/
			cout << "Enter position of your checker" << endl;
			cin >> currentPosition;
			cout << "Enter coordinat of future position" << endl;
			cin >> futurePosition;
			gameController = new CheckersGameController(futurePosition, currentPosition);
			if (board[gameController->futurePosition1][gameController->futurePosition2] == EMPTY )
				{
					break;
				}
			else
			{
				errorDatas();
			}

		}
	
		Gamer* gamer=new RealGamer();
		Gamer* computerGamer=new ComputerGamer();
		//GamerPeople* people = ;
		//GamerComputer* computer;
		//gamer = people;

		int** tempArray = gamer->Game(board, heightOfBoard, widthOfBoard ,'C', gameController->currentPositon1, gameController->currentPositon2, gameController->futurePosition1, gameController->futurePosition2);
		if (tempArray!=nullptr)
		{
			board = tempArray;
		}
		else
		{
			errorDatas();
		}
		
		computerGamer->Game(board, heightOfBoard, widthOfBoard, 'C', 0, 0, 0,0);



		//int** functionOfCheckingWeitherOneCheckerFightAnother(bool isItOurSimpleChecker, int** boardGame, int heigth, int width)

			//gamer->functionOfCheckingWeitherOneCheckerFightAnother(true, board, heightOfBoard, widthOfBoard);

		//errorDatas();

	}














	for (int i = 0; i < widthOfBoard; i++)
	{
		delete  board[i];
	}
	delete board;
}

