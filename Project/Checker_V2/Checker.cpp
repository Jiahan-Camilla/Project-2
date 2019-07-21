/*
 * File:   checker.cpp
 * Author: Jiahan Chen
 * Created on 7/17/2019
 * Purpose:  game implementation
 */
 
#include"Checker.h"

void swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}

bool CheckWin(int* state)
{
	int redNum(0), whiteNum(0);

	for (int row = 0; row < SIZE; ++row)
		for (int column = 0; column < SIZE; ++column)
		{
			if (state[row * SIZE + column] == (int)piece::RED || state[row * SIZE + column] == (int)piece::REDKING) redNum++;
			if (state[row * SIZE + column] == (int)piece::WHITE || state[row * SIZE + column] == (int)piece::WHITEKING) whiteNum++;
		}

	if (redNum * whiteNum)
	{
		return false;
	}

	return true;
}

void DisplayBoard(int* state, char* symbol)
{
	system("cls");
	cout << endl << "  .___.___.___.___.___.___.___.___." << endl;

	for (int row = 0; row < SIZE; ++row)
	{
		cout << row + 1 << " |";

		for (int column = 0; column < SIZE; ++column)
		{
			cout << ' ' << symbol[state[row * SIZE + column]] << " |";
		}

		cout << endl << "  .___.___.___.___.___.___.___.___." << endl;
	}

	cout << "    a   b   c   d   e   f   g   h" << endl;
}

bool PlayerTurn(int* state, int player, int* move)
{
	//check delimitation bounds
	if (0 > move[0] || SIZE <= move[0])
	{
		cout << "Start row is out of bound" << endl;
		return false;
	}

	if (0 > move[1] || SIZE <= move[1])
	{
		cout << "Start column is out of bound" << endl;
		return false;
	}

	if (0 > move[2] || SIZE <= move[2])
	{
		cout << "End row is out of bound" << endl;
		return false;
	}

	if (0 > move[3] || SIZE <= move[3])
	{
		cout << "End column is out of bound" << endl;
		return false;
	}

	//check the moving pattern
	if ((int)piece::RED == player)
	{
		if (state[move[0] * SIZE + move[1]] != (int)piece::REDKING
			&& move[0] >= move[2])
		{
			cout << "RED piece must move down!" << endl;
			return false;
		}
	}
	else
	{
		if (state[move[0] * SIZE + move[1]] != (int)piece::WHITEKING
			&& move[0] <= move[2])
		{
			cout << "WHITE piece must move up!" << endl;
			return false;
		}
	}

	int enemyR;
	int enemyC;

	//check if it's a regular move
	if (1 == abs(move[0] - move[2]) || 1 == abs(move[1] - move[3]))
	{
		swap(state[move[0] * SIZE + move[1]], state[move[2] * SIZE + move[3]]);

		if (player == (int)piece::RED && move[2] == SIZE - 1)
		{
			state[move[2] * SIZE + move[3]] = (int)piece::REDKING;
		}
		else if (player == (int)piece::WHITE && move[2] == 0)
		{
			state[move[2] * SIZE + move[3]] = (int)piece::WHITEKING;
		}

		return true;
	}
	//check if it's a jump move
	else if (2 == abs(move[0] - move[2]) || 2 == abs(move[1] - move[3]))
	{
		if (move[0] < move[2])
		{
			enemyR = move[0] + 1;
		}
		else
		{
			enemyR = move[0] - 1;
		}

		if (move[1] < move[3])
		{
			enemyC = move[1] + 1;
		}
		else
		{
			enemyC = move[1] - 1;
		}

		if ((player == (int)piece::RED && state[enemyR * SIZE + enemyC] != (int)piece::WHITE)
			|| (player == (int)piece::WHITE && state[enemyR * SIZE + enemyC] != (int)piece::RED))
		{
			cout << "There's no enemy at " << enemyR + 1 << enemyC + 'a' << '!' << endl;
			return false;
		}

		state[enemyR * SIZE + enemyC] = 1;
		swap(state[move[0] * SIZE + move[1]], state[move[2] * SIZE + move[3]]);

		if (player == (int)piece::RED && move[2] == SIZE - 1)
		{
			state[move[2] * SIZE + move[3]] = (int)piece::REDKING;
		}
		else if (player == (int)piece::WHITE && move[2] == 0)
		{
			state[move[2] * SIZE + move[3]] = (int)piece::WHITEKING;
		}

		return true;
	}

	cout << "Illegal move, try one more" << endl;
	return false;
}