/*
 * File:   main.cpp
 * Author: Jiahan Chen
 * Created on 7/17/2019
 * Purpose:  core gameplay
 */

#include"Checker.h"

int main()
{
	//Set the random number seed
	srand(static_cast<unsigned int>(time(NULL)));

	//Declare Variables
	char symbol[]{ ' ', '_','r','w','R','W' };
	string inputF, inputT; //move input (from & to)
	int move[4]; //indicate row_start, column_start, row_end, column_end in order

	//Save the game data into a file.
	ofstream gameData;
	gameData.open("checker.txt");

	// initial board state
	int boardState[]{
		0,2,0,2,0,2,0,2,
		2,0,2,0,2,0,2,0,
		0,2,0,2,0,2,0,2,
		1,0,1,0,1,0,1,0,
		0,1,0,1,0,1,0,1,
		3,0,3,0,3,0,3,0,
		0,3,0,3,0,3,0,3,
		3,0,3,0,3,0,3,0
	};

	// display board state
	DisplayBoard(boardState, symbol);

	//game in loop
	do
	{
		// red turn
		while (true)
		{
			cout << "RED's turn" << endl;
			cout << "from: ";
			cin >> inputF;

			move[0] = inputF[0] - '1';
			move[1] = inputF[1] - 'a';

			cout << "to: ";
			cin >> inputT;

			move[2] = inputT[0] - '1';
			move[3] = inputT[1] - 'a';

			if (PlayerTurn(boardState, (int)piece::RED, move))
			{
				gameData << "R: From " << inputF;
				gameData << " To " << inputT << endl;
				break;
			}
		}

		//display board
		DisplayBoard(boardState, symbol);

		//check win
		if (CheckWin(boardState))
		{
			break;
		}

		//WHITE turn
		while (true)
		{
			cout << "WHITE's turn:" << endl;
			cout << "from: ";
			cin >> inputF;

			move[0] = inputF[0] - '1';
			move[1] = inputF[1] - 'a';

			cout << "to: ";
			cin >> inputT;

			move[2] = inputT[0] - '1';
			move[3] = inputT[1] - 'a';
			
			if (PlayerTurn(boardState, (int)piece::WHITE, move))
			{
				gameData << "W: From " << inputF;
				gameData << " To " << inputT << endl;
				break;
			}
		}

		//display board
		DisplayBoard(boardState, symbol);

		//check win
		if (CheckWin(boardState))
		{
			break;
		}
	} while (true);

	gameData.close();

	//Exit program
	system("PAUSE");
	return 0;
}