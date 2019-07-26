/*
 * File:   main.cpp
 * Author: Jiahan Chen
 * Created on 7/22/2019
 * Purpose:  core gameplay
 */

#include"Checker.h"

int main()
{
	//Set the random number seed
	srand(static_cast<unsigned int>(time(NULL)));

	//Declare Variables
	char symbol[]{ ' ', '_','r','w','R','W','\0' };
	string inputF, inputT; //move input (from & to)
	vector<int> move; //store row_start, column_start, row_end, column_end in order for each move

	//Save the game data into a file.
	ofstream gamData;
	gamData.open("checker.txt");

	// initial board state, optimized using 1-d array
	const int size = SIZE * SIZE;
	int* bState = new int[size];
	
	BubbleSort(bState, size); // bubble sort
	SelectionSort(bState, size); // selection sort	
	assert(-1 == BinarySearch(bState, 0, size, -1)); // binary search
	
	int checker[]{
		0, 2, 0, 2, 0, 2, 0, 2,
		2, 0, 2, 0, 2, 0, 2, 0,
		0, 2, 0, 2, 0, 2, 0, 2,
		1, 0, 1, 0, 1, 0, 1, 0,
		0, 1, 0, 1, 0, 1, 0, 1,
		3, 0, 3, 0, 3, 0, 3, 0,
		0, 3, 0, 3, 0, 3, 0, 3,
		3, 0, 3, 0, 3, 0, 3, 0
	};

	bState = checker;

	// display board state
	DisplayBoard(bState, symbol);

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

			if (PlayerTurn(bState, (int)piece::RED, move))
			{
				gamData << "R: From " << inputF;
				gamData << " To " << inputT << endl;
				break;
			}
		}

		//display board
		DisplayBoard(bState, symbol);

		//check win
		if (CheckWin(bState))
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
			
			if (PlayerTurn(bState, (int)piece::WHITE, move))
			{
				gamData << "W: From " << inputF;
				gamData << " To " << inputT << endl;
				break;
			}
		}

		//display board
		DisplayBoard(bState, symbol);

		//check win
		if (CheckWin(bState))
		{
			break;
		}
	} while (true);

	gamData.close();

	//Exit program
	system("PAUSE");
	return 0;
}