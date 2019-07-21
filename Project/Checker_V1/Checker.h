/*
 * File:   checker.h
 * Author: Jiahan Chen
 * Created on 7/17/2019
 * Purpose:  Checker Implementation
 */
 
#pragma once
#include <iostream> //I/O Library
#include <fstream>  //File I/O
#include <iomanip>  //Format Library
#include <cstdlib>  //Rand/Srand
#include <ctime>    //Time
#include <string>  //String
#include <cmath>   //Math

using namespace std;

const int ROWS = 8;
const int COLS = 8;

enum class piece : short
{
	EMPTY = 1, RED, WHITE, REDKING, WHITEKING
};

void swap(int&, int&);
char SymbolConvert(int);
bool CheckWin(int state[][COLS]);
void DisplayBoard(int state[][COLS]);
bool PlayerTurn(int state[][COLS], int, int*);