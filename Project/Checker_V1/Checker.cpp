/*
 * File:   checker.cpp
 * Author: Jiahan Chen
 * Created on 7/17/2019
 * Purpose:  game implementation
 */
 
#include"Checker.h"

bool CheckWin(int state[][COLS])
{
	int redNum(0), whiteNum(0);

	for (int row = 0; row < ROWS; ++row)
		for (int column = 0; column < COLS; ++column)
		{
			if (state[row][column] == (int)piece::RED || state[row][column] == (int)piece::REDKING) redNum++;
			if (state[row][column] == (int)piece::WHITE || state[row][column] == (int)piece::WHITEKING) whiteNum++;
		}

	if (redNum*whiteNum)
	{
		return false;
	}

	return true;
}

void DisplayBoard(int state[][COLS])
{
	cout << endl << "  .___.___.___.___.___.___.___.___." << endl;

	for (int row = 0; row < ROWS; ++row)
	{
		cout << row + 1 << " |";

		for (int column = 0; column < COLS; ++column)
		{
			cout << ' ' << SymbolConvert(state[row][column]) << " |";
		}

		cout << endl << "  .___.___.___.___.___.___.___.___." << endl;
	}

	cout << "    a   b   c   d   e   f   g   h" << endl;
}

void swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}

//Convert pawn to symbol
char SymbolConvert(int i)
{
	switch (i)
	{
	case 1:
		return '_';//Expected Move
	case 2:
		return 'r';//Red
	case 3:
		return 'w';//White
	case 4:
		return 'R';//RedKing
	case 5:
		return 'W';//WhiteKing
	default:
		return ' ';//Empty Space
	}
}

bool PlayerTurn(int state[][COLS], int player, int* move)
{
	//check delimitation bounds
	if (0 > move[0] || ROWS <= move[0])
	{
		cout << "Start row is out of bound" << endl;
		return false;
	}

	if (0 > move[1] || COLS <= move[1])
	{
		cout << "Start column is out of bound" << endl;
		return false;
	}

	if (0 > move[2] || ROWS <= move[2])
	{
		cout << "End row is out of bound" << endl;
		return false;
	}

	if (0 > move[3] || COLS <= move[3])
	{
		cout << "End column is out of bound" << endl;
		return false;
	}

	//check the moving pattern
	if ((int)piece::RED == player) 
	{
		if (state[move[0]][move[1]] != (int)piece::REDKING
			&& move[0] >= move[2])
		{
			cout << "RED piece must move down!" << endl;
			return false;
		}
	}
	else 
	{
		if (state[move[0]][move[1]] != (int)piece::WHITEKING
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
		swap(state[move[0]][move[1]], state[move[2]][move[3]]);

		if (player == (int)piece::RED && move[2] == ROWS - 1)
		{
			state[move[2]][move[3]] = (int)piece::REDKING;
		}
		else if (player == (int)piece::WHITE && move[2] == 0)
		{
			state[move[2]][move[3]] = (int)piece::WHITEKING;
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

		if ((player == (int)piece::RED && state[enemyR][enemyC] != (int)piece::WHITE)
			|| (player == (int)piece::WHITE && state[enemyR][enemyC] != (int)piece::RED))
		{
			cout << "There's no enemy at " << enemyR + 1 << enemyC + 'a' << '!' << endl;
			return false;
		}

		state[enemyR][enemyC] = 1;
		swap(state[move[0]][move[1]], state[move[2]][move[3]]);

		if (player == (int)piece::RED && move[2] == ROWS - 1)
		{
			state[move[2]][move[3]] = (int)piece::REDKING;
		}
		else if (player == (int)piece::WHITE && move[2] == 0)
		{
			state[move[2]][move[3]] = (int)piece::WHITEKING;
		}

		return true;
	}

	cout << "Invalid move!" << endl;
	return false;
}